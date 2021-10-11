#include "Hooking.hpp"
#include "Game.hpp"
#include "ScriptManager.hpp"
#include "CustomText.hpp"
#include "srcEngine.h"
#include "Util.hpp"
#include "D3DRenderer.hpp"
#include "UI/UIManager.hpp"
#include <MinHook.h>
#include "Hashes.h"
#include "remotehashes.h"
#include "SHVScriptManager.h"
DWORD wakeAt;

#ifdef GX_DEBUG
#  pragma comment(lib, "MinHook-Debug.lib")
#else
#  pragma comment(lib, "MinHook-Release.lib")

#endif

namespace Big
{
	namespace
	{
		std::uint32_t g_HookFrameCount{};
	}
	scrThread* ActiveThread()
	{
		return *(scrThread**)(*(std::uintptr_t*)(__readgsqword(0x58)) + 0x830);
	}
	void notifyBlocked(char* fmt, ...)
	{
		g_Logger->Info(fmt);

		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		UI::_SET_NOTIFICATION_BACKGROUND_COLOR(6);
		UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		UI::_DRAW_NOTIFICATION(1, 1);
	} void notifyBlocked(std::string str) { notifyBlocked(&str[0]); }

	bool Hooks::IsDlcPresent(std::uint32_t hash)
	{
		if (Features::DevMode)
		{
			if (hash == 2532323046UL)
			{
				return true;
			}
		}
		return static_cast<decltype(&IsDlcPresent)>(g_Hooking->m_OriginalIsDlcPresent)(hash);
	}
	bool Hooks::IsEntityUpsideDown(std::uint32_t entity)
	{
		if (g_Running && g_HookFrameCount != *g_GameVariables->m_FrameCount)
		{
			g_HookFrameCount = *g_GameVariables->m_FrameCount;
			g_ScriptManager->OnGameTick();
		}
		return static_cast<decltype(&IsEntityUpsideDown)>(g_Hooking->m_OriginalIsEntityUpsideDown)(entity);
	}

	bool Hooks::GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount)
	{
		auto result = static_cast<decltype(&GetEventData)>(g_Hooking->m_OriginalGetEventData)(eventGroup, eventIndex, args, argCount);

		if (result && Features::LogEvent)
		{
			g_Logger->Info("Script event group: %i", eventGroup);
			g_Logger->Info("Script event index: %i", eventIndex);
			g_Logger->Info("Script event argcount: %i", argCount);
			for (std::uint32_t i = 0; i < argCount; ++i)
				g_Logger->Info("Script event args[%u] : %" PRIi64, i, args[i]);
		}

		return result;
	}

	bool Hooks::TestHook(__int64 a, __int64 b, int c, char d)
	{
		string int1 = to_string(a);
		string int2 = to_string(b);
		string int3 = to_string(c);
		string int4 = to_string(d);
		//g_Logger->Info(int1.c_str());
		//g_Logger->Info(int2.c_str());
		//g_Logger->Info(int3.c_str());
		//g_Logger->Info(int4.c_str());
		return true;
	}
	struct RttiCompleteObjectLocator
	{
		std::uint32_t m_Signature;
		std::uint32_t m_OffsetFromBase;
		std::uint32_t m_ConstructorDisplacement;
		std::uint32_t m_TypeDescRva;
		std::uint32_t m_HierarchyDescRva;
		std::uint32_t m_BaseClassRva;
	};

	struct RttiTypeDesc
	{
		virtual ~RttiTypeDesc() = 0;
		char* m_UnmangledName;
		char m_MangledName[1];
	};

	inline const char* GetDynamicTypeName(void* obj)
	{
		__try
		{
			auto vtable = *(RttiCompleteObjectLocator***)obj;
			RttiCompleteObjectLocator* locator = *(vtable - 1);

			HMODULE base;
			if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)locator, &base))
			{
				RttiTypeDesc* desc = (RttiTypeDesc*)((std::uintptr_t)(base) + locator->m_TypeDescRva);
				return desc->m_MangledName;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
		}

		return nullptr;
	}
	/*Metric AAC Detours*/















	static bool is_script_thread_good(scrThread* thread)
	{
		if (!thread || !thread->m_handler)
		{
			return false;
		}
		return !*g_GameVariables->is_session_started || thread->m_handler->is_networked();
	}
#include "SHVScriptEngine.h"
	int Hooks::GetNumOfEvents(int eventgroup)
	{
		if (g_Running && g_HookFrameCount != *g_GameVariables->m_FrameCount && is_script_thread_good(ActiveThread()))//
		{
			g_HookFrameCount = *g_GameVariables->m_FrameCount;
			g_ScriptManager->OnGameTick();
			switch (g_HookState)
			{
			case HookStateRunning:
			{
				SHVScriptManager::MainFiber();
			} break;

			case HookStateExiting:
			{
			} break;

			default:
				break;
			}
		}//
		return static_cast<decltype(&GetNumOfEvents)>(g_Hooking->m_OriginalGetNumOfEvents)(eventgroup);
	}

	int Hooks::ScriptVM(void* stack, signed __int64** globals, void* program, scrThreadContext* threadContext)
	{
		for (auto thread : *g_GameVariables->script_threads)
		{
			if (!thread)
			{
				continue;
			}
			if (thread->m_context.m_state != eThreadState::running)
			{
				continue;
			}
			if (thread->m_context.m_script_hash == CONSTEXPR_JOAAT("freemode") || CONSTEXPR_JOAAT("main_persistent"))
			{
				if (g_Running && g_HookFrameCount != *g_GameVariables->m_FrameCount && is_script_thread_good(ActiveThread()) && !PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()))//
				{
					g_HookFrameCount = *g_GameVariables->m_FrameCount;
					g_ScriptManager->OnGameTick();
					if (Elite)
					{
						switch (g_HookState)
						{
						case HookStateRunning:
						{
							SHVScriptManager::MainFiber();
						} break;

						case HookStateExiting:
						{
						} break;

						default:
							break;
						}
					}
				}//
			}
		}
		return static_cast<decltype(&ScriptVM)>(g_Hooking->m_OriginalScriptVM)(stack, globals, program, threadContext);

	}
















	bool Hooks::NetworkCanBail()
	{
		return false;
	}
	int Hooks::TriggerScriptEvent(bool unk0, uint64_t* args, int argCount, int bitFlags)
	{
		/*if (Features::LogEvent)
		{
			//g_Logger->Info("-------------------------");
			//g_Logger->Info("TSE");
			for (int i = 0; i < argCount; i++)
				//g_Logger->Info("args[%i]: 0x%016llx => %d", i, args[i], args[i]);
			//g_Logger->Info("-------------------------");
		}*/
		return static_cast<decltype(&TriggerScriptEvent)>(g_Hooking->m_OriginalTriggerScriptEvent)(unk0, args, argCount, bitFlags);
	}

	void Hooks::DisableErrorScreen(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background)
	{
		if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == GAMEPLAY::GET_HASH_KEY("shop_controller"))
		{
			return;
		}


		return static_cast<decltype(&DisableErrorScreen)>(g_Hooking->m_OriginalDisableErrorScreen)(entryHeader, entryLine1, instructionalKey, entryLine2, p4, p5, p6, p7, background);
	}
	bool command_check(std::string& str, std::string check)
	{
		for (int i = 0; i < str.size(); i++)
			str[i] = tolower(str[i]);

		std::size_t found = str.find_first_of(' ');
		if (found != std::string::npos)
		{
			if (str.substr(0, found) == check)
			{
				str = str.substr(found + 1, str.size());
				return true;
			}
		}
		else
		{
			if (str == check)
				return true;
		}
		return false;
	}




	void Hooks::CheatMessage(void* thisptr, __int64 unk1, __int64 unk2, const char* message)
	{
		g_Logger->Info(message);
		if (Features::ChatCommands)
		{
			auto func = Signature("E8 ? ? ? ? 83 BD ? ? ? ? ? 48 8B D8 0F 8D ? ? ? ? 48 8B 4D 20 E8", "CM").Scan().Add(0x1).Rip().As<CNetGamePlayers* (*)(__int64)>();
			if (message == nullptr) { return static_cast<decltype(&CheatMessage)>(g_Hooking->m_OriginalChatMesage)(thisptr, unk1, unk2, message); }
			if (func(unk2) == nullptr) { return static_cast<decltype(&CheatMessage)>(g_Hooking->m_OriginalChatMesage)(thisptr, unk1, unk2, message); }
			if (func(unk2)->PlayerInfo->sName == nullptr) { return static_cast<decltype(&CheatMessage)>(g_Hooking->m_OriginalChatMesage)(thisptr, unk1, unk2, message); }
			std::string str(message);
			int playername = getPlayerId(func(unk2)->PlayerInfo->sName);
			std::string log;

			g_Logger->Info(message);

			if (Features::SlashVehicle)
			{
				if (command_check(str, "/vehicle"))
				{
					log = (std::string)"Vehicle spawned for" + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					//g_Logger->Info(str.c_str());
					spawn_vehicle(str.c_str(), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(playername));
				}
			}
			if (Features::SlashCash)
			{
				if (command_check(str, "/cash"))
				{
					log = (std::string)"Cash drop toggled for" + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					if (!Features::CashDropRemote[playername])
					{
						Features::CashDropRemote[playername] = 1;
					}
					else
					{
						Features::CashDropRemote[playername] = 0;
					}
				}
			}
			if (Features::SlashOtr)
			{
				if (command_check(str, "/otr"))
				{
					log = (std::string)"Remote OTR toggled for" + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					if (!Features::RemoteOTRBool[playername])
					{
						Features::RemoteOTRBool[playername] = 1;
					}
					else
					{
						Features::RemoteOTRBool[playername] = 0;
					}
				}

			}
			if (Features::SlashDay)
			{
				if (command_check(str, "/day"))
				{
					log = (std::string)"Time set to day by" + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					Features::SetLobbyTime(15, 0, 0);
				}
			}
			if (Features::SlashNight)
			{
				if (command_check(str, "/night"))
				{
					log = (std::string)"Time set to night by" + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					Features::SetLobbyTime(1, 0, 0);
				}
			}
			if (Features::SlashSnow)
			{
				if (command_check(str, "/snow"))
				{
					log = (std::string)"Weather set to snow by" + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					Features::SetWeather(11);
				}
			}
			if (Features::SlashClear)
			{
				if (command_check(str, "/clear"))
				{
					log = (std::string)"Weather set to clear by " + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					Features::SetWeather(1);
				}
			}
			if (Features::SlashWeapons)
			{
				if (command_check(str, "/weapons"))
				{
					log = (std::string)"Weapons given to " + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					for (int i = 0; i < (sizeof(Weaponss) / 4); i++) {
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(playername), Weaponss[i], 9999, 1);
					}
				}
			}
			if (Features::SlashNeverWanted)
			{
				if (command_check(str, "/neverwanted"))
				{
					log = (std::string)"Never wanted toggled for" + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					if (!Features::RemoteNeverWanted[playername])
					{
						Features::RemoteNeverWanted[playername] = 1;
					}
					else
					{
						Features::RemoteNeverWanted[playername] = 0;
					}
				}

			}
			if (Features::SlashClone)
			{
				if (command_check(str, "/clone"))
				{
					log = (std::string)"Player cloned by " + func(unk2)->PlayerInfo->sName;
					//g_Logger->Info(log.c_str());
					PED::CLONE_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(playername), ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(playername)), *g_GameVariables->is_session_started, false);
				}
			}
		}
		return static_cast<decltype(&CheatMessage)>(g_Hooking->m_OriginalChatMesage)(thisptr, unk1, unk2, message);
	}
	const char* Hooks::GetLabelText(void* unk, const char* label)
	{
		if (g_Running)
			if (auto text = g_CustomText->GetText(Joaat(label)))
				return text;

		return static_cast<decltype(&GetLabelText)>(g_Hooking->m_OriginalGetLabelText)(unk, label);
	}
	bool Hooks::DenyDrops(void* classidonthave, void* unk, CPed* ped)
	{
		if (Features::AntiMoneyDrop)
		{
			return false;
		}
		return static_cast<decltype(&DenyDrops)>(g_Hooking->m_OriginalDenyDrops)(classidonthave, unk, ped);
	}
	LRESULT Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		SHVScriptManager::WndProc(hWnd, msg, wParam, lParam);
		g_D3DRenderer->WndProc(hWnd, msg, wParam, lParam);
		return static_cast<decltype(&WndProc)>(g_Hooking->m_OriginalWndProc)(hWnd, msg, wParam, lParam);
	}

	HRESULT Hooks::Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags)
	{
		if (g_Running)
		{
			g_D3DRenderer->BeginFrame();
			g_ScriptManager->OnD3DTick();
			g_D3DRenderer->EndFrame();
		}

		return g_Hooking->m_D3DHook.GetOriginal<decltype(&Present)>(PresentIndex)(dis, syncInterval, flags);
	}
	HRESULT Hooks::ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		if (g_Running)
		{
			g_D3DRenderer->PreResize();
			auto hr = g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
			if (SUCCEEDED(hr))
			{
				g_D3DRenderer->PostResize();
			}

			return hr;
		}
		return g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	}
#include "Functions.h"
	bool Hooks::NetworkManager(__int64 a1, CNetGamePlayers* a2, CNetGamePlayers* a3, unsigned __int16 a4, int a5, int a6, __int64 a7, __int64 a8)
	{
		auto ptr = Memory::pattern("66 83 FA ? 73 13 0F B7 C2 4C 89 84 C1 ? ? ? ? 4C 89 8C C1").count(1).get(0).get<char>(0);
		auto num_events = *(std::uint8_t*)(ptr + 3);
		auto name_offset = *(std::int32_t*)(ptr + 21);
		auto eventName = reinterpret_cast<char*>(*reinterpret_cast<__int64*>(a1 + 8 * a4 + name_offset));





			if (a4 == 0x11) //EXPLOSION_EVENT
			{
				return false;
			}

			if (a4 == 0x0C) //GIVE_WEAPON_EVENT
			{
				return false;
			}


			if (a4 == 0x0D) //*
			{
				return false;
			}

			if (a4 == 0x40) //KICK_VOTES_EVENT
			{
				return false;
			}

			if (a4 == 4) //REQUEST_CONTROL_EVENT
			{

				return false;
			}

			if (a4 == 5) //GIVE_CONTROL_EVENT
			{
				return false;
			}

			if (a4 == 9) //GAME_CLOCK_EVENT
			{

				return false;
			}

			if (a4 == 0x0A) //GAME_WEATHER_EVENT
			{
				return false;
			}

			if (a4 == 0x10) //FIRE_EVENT
			{
				return false;
			}

			if (a4 == 0x23) //CLEAR_AREA_EVENT - CLEAR_RECTANGLE_AREA_EVENT
			{
				return false;
			}

			if (a4 == 0x24) //NETWORK_REQUEST_SYNCED_SCENE_EVENT
			{
				return false;
			}

			if (a4 == 0x25) //NETWORK_START_SYNCED_SCENE_EVENT
			{
				return false;
			}

			if (a4 == 0x27) //NETWORK_UPDATE_SYNCED_SCENE_EVENT
			{

				return false;
			}

			if (a4 == 0x26) //NETWORK_STOP_SYNCED_SCENE_EVENT
			{
				return false;
			}



			if (a4 == 0x29) //GIVE_PED_SCRIPTED_TASK_EVENT
			{

		
				return false;
			}

			if (a4 == 0x2A) //GIVE_PED_SEQUENCE_TASK_EVENT
			{

				return false;
			}

			if (a4 == 0x2B) //NETWORK_CLEAR_PED_TASKS_EVENT
			{

		

				return false;
			}

			if (a4 == 0x4B) //NETWORK_PTFX_EVENT
			{

		

				return false;
			}

			if (a4 == 0x54) //REPORT_MYSELF_EVENT - REPORT_CASH_SPAWN_EVENT
			{

			

				return false;
			}

			if (a4 == 0x20) //NETWORK_INCREMENT_STAT_EVENT
			{

				return false;

			}

	

		return static_cast<decltype(&NetworkManager)>(g_Hooking->m_OriginalNetworkManager)(a1, a2, a3, a4, a5, a6, a7, a8);
	}
	bool Hooks::EventManager(void* events, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer)
	{

		Features::TotalEvents += 1;

			auto args = (std::int64_t*)(((std::uintptr_t)events) + 0x70);
			auto argCount = *(std::uint32_t*)(((std::uintptr_t)events) + 0x224) / sizeof(std::int64_t);
			auto SenderID = *reinterpret_cast<std::int8_t*>(targetPlayer + 0x2D);



		//if (targetPlayer == g_GameFunctions->m_GetPlayerNetworkId(PLAYER::PLAYER_ID()))
		//{

		//	auto args = (std::int64_t*)(((std::uintptr_t)events) + 0x70);
		//	auto argCount = *(std::uint32_t*)(((std::uintptr_t)events) + 0x224) / sizeof(std::int64_t);

		//	}

	
			switch (args[0])
			{

			case TRANSACION_ERROR:
				if (protex9)
				{
					Features::BlockedEvents += 1;
	
			
							if (Features::EventNotif)
								notifyBlocked("Event: Transaction Error Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");
							return true;
					
				}
				break;


			case MESSAGE_SPAM:
				if (protex8)
				{

				
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Message Spam Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");
						return true;
					
				}
				break;


			case SOUND_SPAM:
				if (protex8)
				{
				
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Sound Spam Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");
						return true;
					
				}
				break;
			case TELEPORT_AP:
				if (protex7)
				{
					Features::BlockedEvents += 1;
					if (Features::EventNotif)
						notifyBlocked("Event: Teleport Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

					return true;
				}
				break;
			case KICK_5:
				if (protex4)
				{

					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Remote OTR Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;



			case CayoPericoTeleport:
				if (CayoPericoProt)
				{
					Features::BlockedEvents += 1;
					if (Features::EventNotif)
						notifyBlocked("Event: CayoP. TP Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

					return true;

				}
				break;



			case BOUNTY:
				if (protex11)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Bounty\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
			case TSE_JUMBO1:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [1] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case TSE_JUMBO2:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [2] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case TSE_JUMBO3:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [3] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case Force_Kick:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [4] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case TSE_JUMBO5:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [5] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case TSE_ROUNDHOUSE1:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [6] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case TSE_ROUNDHOUSE2:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [7] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case TSE_ROUNDHOUSE3:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [8] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case TSE_ROUNDHOUSE4:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [9] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case NON_HOST_KICK2:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [10] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case TSE_ROUNDHOUSE6:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [11] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case TSE_ROUNDHOUSE7:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [12] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case NON_HOST_KICK3:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [13] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case NON_HOST_KICK1:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [14] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_PP11:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [15] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case UNKNOWN_3:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [16] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case KICK_PP9:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [18] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case NON_HOST_KICK11:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [19] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_PP8:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [20] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

				

						return true;
					
				}
				break;
			case SUPERFORCE_4:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [21] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case REMOVE_WANTED_LEVEL:
				if (protex12)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Remove Wanted Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case SEND_TO_MISSION:
				if (protex6)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Send To Job Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}

			case FORCE_MISSION:
				if (protex6)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Send To Job Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}

				break;
			case CEO_KICK:
				if (protex2)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: CEO Kick Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case CEO_BAN:
				if (protex3)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: CEO Ban Event\nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case NON_HOST_KICK8:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [22] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case SUPERFORCE_2:
				if (protex1)
				{
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [24] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case KICK_18:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [25] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case NON_HOST_KICK7:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [26] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case NON_HOST_KICK6:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [27] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case KICK_NEW_SESSION:
				if (protex1)
				{
				
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [28] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_1:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [29] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case UNKNOWN_4:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [30] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_5:
				if (protex1)
				{
				
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [31] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case UNKNOWN_6:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [32] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_7:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [33] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_8:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [34] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case SHOW_BANNER2:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Show-Banner \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_9:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [35] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_10:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [36] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_11:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [37] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_12:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [38] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_13:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [39] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case UNKNOWN_14:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [40] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case UNKNOWN_15:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [41] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_16:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [42] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_17:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [43] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_18:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [44] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case AFK_KICK:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: AFK Kick \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case UNKNOWN_19:
				if (protex1)
				{
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [45] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_20:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [45] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_21:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [46] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;



			case NOTIFICATION:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Notitifcation \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case REMOTE_CRASH:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Remote-Crash \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


			case SHOW_BANNER1:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: ShowBanner \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_23:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [48] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_24:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [49] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case UNKNOWN_25:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [50] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKKNOWN_26:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [51] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;



			case UNKNOWN_27:
				if (protex1)
				{
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [52] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;



			case UNKNOWN_29:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [54] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;




			case UNKNOWN_30:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [55] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_31:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [56] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case UNKNOWN_32:
				if (protex1)
				{
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [57] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;








			case KICK_4:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [58] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_6:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [59] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_7:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [60] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_9:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [61] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_12:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [62] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_13:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [63] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_14:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [64] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_16:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [65] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_17:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [66] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_20:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [68] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_21:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [69] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_22:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [70] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;





			case KICK_24:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [71] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
			
				}
				break;

			case KICK_25:
				if (protex1)
				{
				
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [72] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_30:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [73] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_31:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [74] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_33:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [75] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_36:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [76] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_37:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [77] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_38:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [78] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;
			case KICK_40:
				if (protex1)
				{
				
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Kick Event [79] \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;

			case VEHICLE_KICK:
				if (protex1)
				{
					
						Features::BlockedEvents += 1;
						if (Features::EventNotif)
							notifyBlocked("Event: Vehicle-Kick \nFrom: " + (std::string)PLAYER::GET_PLAYER_NAME(SenderID) + "\nStatus: Blocked");

						return true;
					
				}
				break;


		}

		return static_cast<decltype(&EventManager)>(g_Hooking->m_OriginalEventManager)(events, sourcePlayer, targetPlayer);
	}
	CNetGamePlayers* Hooks::GetPlayerByIndex(int index)
	{
		if (index < 0 || index >= 32)
		{
			return nullptr;
		}

		return g_GameVariables->g_players[index];
	}
	bool Hooks::InfoEvent(void* thisptr, CNetGamePlayer* source, CNetGamePlayer* target)
	{
		//g_Logger->Info(source->GetName());
		Modders[source->m_player_id] = true;
		return static_cast<decltype(&InfoEvent)>(g_Hooking->m_OriginalInfoEvent)(thisptr, source, target);
	}
	bool Hooks::ReportMyselfEvent(void* thisptr, CNetGamePlayer* source, CNetGamePlayer* target)
	{
		if (source = nullptr) 		return static_cast<decltype(&ReportMyselfEvent)>(g_Hooking->m_OriginalReportMyselfEvent)(thisptr, source, target);
		if (target = nullptr) 		return static_cast<decltype(&ReportMyselfEvent)>(g_Hooking->m_OriginalReportMyselfEvent)(thisptr, source, target);
		if (thisptr = nullptr)		return static_cast<decltype(&ReportMyselfEvent)>(g_Hooking->m_OriginalReportMyselfEvent)(thisptr, source, target);
		Modders[source->m_player_id] = true;
		return static_cast<decltype(&ReportMyselfEvent)>(g_Hooking->m_OriginalReportMyselfEvent)(thisptr, source, target);
	}
	void Hooks::ResourceError(std::uint32_t errorHash, bool terminateProcess)
	{
		if (errorHash == 2207393597) {
			//g_Logger->Info("Same Hash, passed to Resource Error");
			terminateProcess = 0;
			return;
		}
		terminateProcess = 0;
		//g_Logger->Info(to_string(errorHash).c_str());
		//g_Logger->Info(to_string(terminateProcess).c_str());
		return;
	}
	bool Hooks::ResourceCall(std::uint32_t errorHash)
	{
		if (errorHash == 2207393597)
		{
			//g_Logger->Info("Same hash...");
			return 1;
		}
		errorHash = 0;
		//g_Logger->Info(to_string(errorHash).c_str());
		return 1;
	}
	//2207393597
	void Hooks::EventQue(void* thisptr, netGameEvent* event)
	{
		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			if (event != nullptr)
			{
				if (event->eventId == 0x4Au)
				{
					delete event;
					return;
				}
				if (event->eventId == 0x52u)
				{
					delete event;
					return;
				}
				if (event->eventId == 0x53u)
				{
					delete event;
					return;
				}
				if (event->eventId == 0x49u)
				{
					delete event;
					return;
				}
				if (event->eventId == 0x4Du)
				{
					delete event;
					return;
				}
			}
		}
		return static_cast<decltype(&EventQue)>(g_Hooking->m_OriginalEventQue)(thisptr, event);
	}
	int Hooks::JoinPlayer(__int64 a1, int a2, __int64* a3, int a4) {
		if (Joiner)
		{
			if (a3 == 0)
			{
				return static_cast<decltype(&JoinPlayer)>(g_Hooking->m_OriginalJoinPlayer)(a1, a2, a3, a4);
			}
			*a3 = Join;

		}
		return static_cast<decltype(&JoinPlayer)>(g_Hooking->m_OriginalJoinPlayer)(a1, a2, a3, a4);
	}
	int Hooks::Pattern(int a1, __int64 a2, unsigned int a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7)
	{
		if (Joiner) {
			a2 = Join;
			Joiner = false;
		}
		//g_Logger->Info("----------------");
		//g_Logger->Info(to_string(a1).c_str());
		//g_Logger->Info(to_string(a2).c_str());
		//g_Logger->Info(to_string(a3).c_str());
		//g_Logger->Info(to_string(a4).c_str());
		//g_Logger->Info(to_string(a5).c_str());
		//g_Logger->Info(to_string(a6).c_str());
		//g_Logger->Info(to_string(a7).c_str());
		//g_Logger->Info("----------------");
		return static_cast<decltype(&Pattern)>(g_Hooking->m_OriginalPattern)(a1, a2, a3, a4, a5, a6, a7);
	}
	int Hooks::SensorChat(__int64 chat_menu, const char* user_text, const char** output_text)
	{
		if (Features::ChatSensor)
		{
			return -1;
		}
		return static_cast<decltype(&SensorChat)>(g_Hooking->m_OriginalSensorChat)(chat_menu, user_text, output_text);
	}
	void Hooks::EventPat(__int64 a1, unsigned int a2, unsigned int a3, unsigned int a4)
	{
		//g_Logger->Info("-----Event Pat-------");
		//g_Logger->Info(to_string(a1).c_str());
		//g_Logger->Info(to_string(a2).c_str());
		//g_Logger->Info(to_string(a3).c_str());
		//g_Logger->Info(to_string(a4).c_str());
		//g_Logger->Info("---------------------");
	}
	Hooking::Hooking() :
		m_D3DHook(g_GameVariables->m_Swapchain, 18)
	{
		MH_Initialize();
		//MH_CreateHook(g_GameFunctions->m_IsEntityUpsideDown, &Hooks::IsEntityUpsideDown, &m_OriginalIsEntityUpsideDown); Old Hook
		MH_CreateHook(g_GameFunctions->m_ScriptVM, &Hooks::ScriptVM, &m_OriginalScriptVM);
		//		MH_CreateHook(g_GameFunctions->m_GetNumOfEvents, &Hooks::GetNumOfEvents, &m_OriginalGetNumOfEvents);
		MH_CreateHook(g_GameFunctions->m_IsDlcPresent, &Hooks::IsDlcPresent, &m_OriginalIsDlcPresent);
		MH_CreateHook(g_GameFunctions->m_TriggerScriptEvent, &Hooks::TriggerScriptEvent, &m_OriginalTriggerScriptEvent);
		MH_CreateHook(g_GameFunctions->m_EventManager, &Hooks::EventManager, &m_OriginalEventManager);
		MH_CreateHook(g_GameFunctions->m_NetworkEvents, &Hooks::NetworkManager, &m_OriginalNetworkManager);
		MH_CreateHook(g_GameFunctions->m_ChatSensor, &Hooks::SensorChat, &m_OriginalSensorChat);
		MH_CreateHook(g_GameFunctions->m_GetLabelText, &Hooks::GetLabelText, &m_OriginalGetLabelText);
		//	MH_CreateHook(g_GameFunctions->m_GetEventData, &Hooks::HK_GET_EVENT_DATA, &m_OriginalSensorChat);

		//GameVariables::defuseEvent(REPORT_MYSELF_EVENT, true);
		//GameVariables::defuseEvent(REPORT_CASH_SPAWN_EVENT, true);


		MH_CreateHook(g_GameFunctions->m_EventPat, &Hooks::EventPat, &m_OriginalEventPat);
		MH_CreateHook(g_GameFunctions->m_DenyDrops, &Hooks::DenyDrops, &m_OriginalDenyDrops);
		MH_CreateHook(g_GameFunctions->m_DisableErrorScreen, &Hooks::DisableErrorScreen, &m_OriginalDisableErrorScreen);
		MH_CreateHook(g_GameFunctions->m_GetEventData, &Hooks::GetEventData, &m_OriginalGetEventData);
		MH_CreateHook(g_GameFunctions->m_JoinPattern, &Hooks::JoinPlayer, &m_OriginalJoinPlayer);
		MH_CreateHook(g_GameFunctions->m_WndProc, &Hooks::WndProc, &m_OriginalWndProc);
		m_D3DHook.Hook(&Hooks::Present, Hooks::PresentIndex);
		m_D3DHook.Hook(&Hooks::ResizeBuffers, Hooks::ResizeBuffersIndex);
	}

	Hooking::~Hooking() noexcept
	{
		MH_RemoveHook(g_GameFunctions->m_WndProc);
		MH_RemoveHook(g_GameFunctions->m_ScriptVM);
		MH_RemoveHook(g_GameFunctions->m_GetLabelText);
		MH_RemoveHook(g_GameFunctions->m_GetNumOfEvents);
		MH_RemoveHook(g_GameFunctions->m_DenyDrops);
		MH_RemoveHook(g_GameFunctions->m_IsDlcPresent);
		MH_RemoveHook(g_GameFunctions->m_DisableErrorScreen);//
		MH_RemoveHook(g_GameFunctions->m_EventPat);//
		//MH_RemoveHook(g_GameFunctions->m_GetEventData);//
		MH_RemoveHook(g_GameFunctions->m_ChatSensor);//
		MH_RemoveHook(g_GameFunctions->m_NetworkEvents);
		MH_RemoveHook(g_GameFunctions->m_ChatMessage);
		MH_RemoveHook(g_GameFunctions->m_EventManager);
		MH_RemoveHook(g_GameFunctions->m_TriggerScriptEvent);
		MH_RemoveHook(g_GameFunctions->m_GetEventData);
		MH_Uninitialize();
	}
	void Hooking::Hook()
	{
		m_D3DHook.Enable();
		MH_EnableHook(MH_ALL_HOOKS);
	}

	void Hooking::Unhook()
	{
		m_D3DHook.Disable();
		MH_DisableHook(MH_ALL_HOOKS);
		//Discord_Shutdown();//
	}
	void set_active_thread(scrThread* thread)
	{
		*(scrThread**)(*(std::uintptr_t*)(__readgsqword(0x58)) + 0x830) = thread;
	}
	scrThread* find_networked(std::uint32_t hash)
	{
		for (auto thread : *g_GameVariables->script_threads)
		{
			if (!thread)
			{
				continue;
			}
			if (thread->m_context.m_state != eThreadState::running)
			{
				continue;
			}
			if (thread->m_context.m_script_hash != hash)
			{
				continue;
			}
			return thread;
		}
		return nullptr;
	}
	void Hooks::tick()
	{
		scrThread* networked_thread{};
		if (*g_GameVariables->is_session_started && (networked_thread = find_networked(CONSTEXPR_JOAAT("freemode"))) != nullptr)
		{
			if (g_GameVariables->is_session_started)
			{
				auto og_thread = ActiveThread();

			}
		}
		else
		{
			g_ScriptManager->OnGameTick();
		}
	}
}
