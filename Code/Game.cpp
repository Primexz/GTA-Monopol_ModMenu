#include "Game.hpp"
#include "Invoker.hpp"
#include "Types.hpp"
#include "enums.h"
#include "srcEngine.h"
#include <cstdint>
#include "core.h"
#include "Functions.h"
void(*rage::scrNativeCallContext::SetVectorResults)(rage::scrNativeCallContext*) = nullptr;
inline const NetGameEvent_t* FindNetGameEventById(std::uint16_t id)
{
	for (auto const& event : g_GameVariables->m_NetGameEvents)
	{
		if (event.m_Id == id)
			return &event;
	}

	return nullptr;
}
void GameVariables::Update()
{
}
void Hooks::ReceiveEvent(Big::CEventMgr* this_, netGameEvent* event, datBitBuffer* buffer, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer, std::uint16_t unk1, std::uint32_t unk2, std::int32_t unk3)
{
	std::uintptr_t* m_EventMgr = Signature("48 8B E9 48 8B 0D ? ? ? ? 0F 29 70 E8 33 DB 0F 28 F2 8B F2 8B FB", "EM").Scan().Add(6).Rip().As<std::uintptr_t*&>();
	auto registerEventFunc = Signature("66 83 FA ? 73 13 0F B7 C2 4C 89 84 C1 ? ? ? ? 4C 89 8C C1 ? ? ? ? C3", "REF");
	std::ptrdiff_t m_EventNameOffset = registerEventFunc.Scan().Add(21).As<std::uint32_t&>();
	std::ptrdiff_t m_EventFuncOffset = registerEventFunc.Scan().Add(13).As<std::uint32_t&>();
	std::size_t m_NumNetEvents = registerEventFunc.Scan().Add(3).As<std::uint8_t&>();
	if (g_GameVariables->m_NetGameEvents.empty() && *m_EventMgr)
	{
		for (std::size_t i = 0; i < m_NumNetEvents; ++i)
		{
			auto name = *(const char**)(*m_EventMgr + (8 * i) + m_EventNameOffset);
			auto func = *(void**)(*m_EventMgr + (8 * i) + m_EventFuncOffset);

			if (name && func)
				g_GameVariables->m_NetGameEvents.emplace_back(static_cast<std::uint16_t>(i), name, func);
		}
	}
	if (event && sourcePlayer && targetPlayer)
	{
		if (auto e = FindNetGameEventById(event->eventId))
		{
			g_Logger->Info(to_string(e->m_Hash).c_str());
			switch (e->m_Hash)
			{
			case CONSTEXPR_JOAAT("NETWORK_CLEAR_PED_TASKS_EVENT"):
			{
				string a = sourcePlayer->PlayerInfo->sName + (std::string)"has tried to freeze you";
				PrintBottomLeft((char*)a.c_str());
				return;
				break;
			}
			case CONSTEXPR_JOAAT("PLAYER_CARD_STAT_EVENT"):
			{
				string ab = sourcePlayer->PlayerInfo->sName + (std::string)"has tried to stat you";
				PrintBottomLeft((char*)ab.c_str());
				return;
				break;
			}
			case CONSTEXPR_JOAAT("SCRIPT_ENTITY_STATE_CHANGE_EVENT"):
			{
				string ac = sourcePlayer->PlayerInfo->sName + (std::string)"has tried to state you";
				PrintBottomLeft((char*)ac.c_str());
				return;
				break;
			}
			}
		}

		static_cast<decltype(&ReceiveEvent)>(g_Hooking->m_OriginalReceiveEvent)(this_, event, buffer, sourcePlayer, targetPlayer, unk1, unk2, unk3);
	}
}
std::vector<void*> getEvents(char* b)
{
	std::vector<void*> events;
	auto i = 0, j = 0, matches = 0, found = 0;
	char* eventHookPattern = const_cast<char*>("\x4C\x8D\x05");
	while (found != 84)
	{
		if (b[i] == eventHookPattern[j])
		{
			if (++matches == 3)
			{
				events.push_back(
					reinterpret_cast <void*>(reinterpret_cast <uint64_t>(b + i - j) + *
						reinterpret_cast <int*>(
							b + i + 1) + 7));
				found++;
				j = matches = 0;
			}
			j++;
		}
		else
		{
			matches = j = 0;
		}
		i++;
	}
	return events;
}
namespace Big
{
	GameVariables::GameVariables() :


		/*m_GameState(Signature("48 85 C9 74 4B 83 3D", "GST").Scan().Add(7).Rip().As<decltype(m_GameState)>()),*/
		//m_GameState(Signature("83 3D ? ? ? ? ? 75 17 8B 42 20 25", "GST").Scan().Add(7).Rip().As<decltype(m_GameState)>()),
		m_GameState(Signature("83 3D ? ? ? ? ? 75 17 8B 42 20 25", "GST").Scan().Add(2).Rip().As<decltype(m_GameState)>()),


		m_FrameCount(Signature("F3 0F 10 0D ? ? ? ? 44 89 6B 08", "FC").Scan().Add(4).Rip().Sub(8).As<decltype(m_GameState)>()),
		m_GameWindow(FindWindowA("grcWindow", "Grand Theft Auto V")),


		//D3D hook
		//m_Swapchain(Signature("48 8B 0D ? ? ? ? 48 8D 55 A0 48 8B 01", "SWapC").Scan().Add(3).Rip().As<decltype(m_Swapchain)&>()),
		m_Swapchain(Signature("48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", "SWapC").Scan().Add(3).Rip().As<decltype(m_Swapchain)&>()),

		m_NativeRegistrations(Signature("48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B7 15 ? ? ? ? 33 FF", "NR").Scan().Add(7).Rip().As<decltype(m_NativeRegistrations)>()),
		m_GlobalBase(Signature("4C 8D 4D 08 48 8D 15 ? ? ? ? 4C 8B C0", "GB").Scan().Add(7).Rip().As<decltype(m_GlobalBase)>()),



		script_threads(Signature("48 8B 01 FF 50 20 0F B7 15 ? ? ? ? FF C3 0F B7 C2 3B D8 7C C9 48 8B 5C 24", "ST").Scan().Sub(30).Rip().As<decltype(script_threads)>()),



		//is_session_started(Signature("44 38 1D ? ? ? ? 0F 84 ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 48 8B 85", "ISS").Scan().Add(3).Rip().As<bool*>()),
		is_session_started(Signature("40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", "ISS").Scan().Add(3).Rip().As<bool*>()),


		m_NativeRetn(Signature("44 89 75 9F 49 8D 0C C1", "NR").Scan().Add(19).As<char*>())
	{
		std::copy_n(m_NativeRetn, 2, m_OriginalNativeRetn);
		char* c_location = nullptr;

		//auto pScrThreadCollection = Memory::pattern("48 8B C8 EB 03 48 8B CB 48 8B 05").count(1).get(0).get<char>(11);
		//script_threads = reinterpret_cast<decltype(script_threads)>(pScrThreadCollection + *(int32_t*)pScrThreadCollection + 4);


		activeThreadTlsOffset = *Memory::pattern("48 8B 04 D0 4A 8B 14 00 48 8B 01 F3 44 0F 2C 42 20").count(1).get(0).get<uint32_t>(-4);

		auto sig = Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8", "GameB").Scan().Sub(17);
		m_GameBuild = sig.Add(265 + 3).Rip().As<decltype(m_GameBuild)>();



		auto p_fixVector3Result = Memory::pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA");
		//auto p_fixVector3Result = Memory::pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18");
		auto void_location = p_fixVector3Result.count(1).get(0).get<void>(0);
		if (void_location != nullptr) scrNativeCallContext::SetVectorResults = (void(*)(scrNativeCallContext*))(void_location);



		auto p_bypass = Memory::pattern("3B F8 40 0F 94 C7");
		c_location = p_bypass.count(1).get(0).get<char>(0);
		m_ownedExplosionBypass = (twoBytes*)c_location;




		auto p_worldPtr = Memory::pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
		c_location = p_worldPtr.count(1).get(0).get<char>(0);
		m_WorldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

		//auto p_globalPtr = Memory::pattern("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11");
		//c_location = p_globalPtr.count(1).get(0).get<char>(0);




		auto p_globalPtr = Memory::pattern("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D");
		c_location = p_globalPtr.count(3).get(0).get<char>(0);




		__int64 patternAddr = NULL;
		patternAddr = reinterpret_cast<decltype(patternAddr)>(c_location);
		m_globalPtr = (__int64**)(patternAddr + *(int*)(patternAddr + 3) + 7);



		auto p_PlayerList = Memory::pattern("48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 8B CF");
		c_location = p_PlayerList.count(1).get(0).get<char>(0);
		PlayerListPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

		auto p_blipList = Memory::pattern("4C 8D 05 ? ? ? ? 0F B7 C1");
		c_location = p_blipList.count(1).get(0).get<char>(0);
		m_blipList = (CBlipList*)(c_location + *reinterpret_cast<int*>(c_location + 3) + 7);
	}

	void GameVariables::PostInit()
	{
	}
	void GameVariables::OwnedExplosionBypass(bool toggle)
	{
		constexpr twoBytes patched = { 0x39, 0xDB };
		constexpr twoBytes restore = { 0x3B, 0xF8 };
		if (g_GameVariables->m_ownedExplosionBypass == nullptr)
			return;
		*g_GameVariables->m_ownedExplosionBypass = toggle ? patched : restore;
	}
	static char EventRestore[83] = {};
	void GameVariables::defuseEvent(RockstarEvent e, bool toggle)
	{
		static const unsigned char retn = 0xC3;
		char* p = (char*)g_GameVariables->m_EventPtr[e];
		if (toggle)
		{
			if (EventRestore[e] == 0)
				EventRestore[e] = p[0];
			*p = retn;
		}
		else
		{
			if (EventRestore[e] != 0)
				*p = EventRestore[e];
		}
	}
	void GameVariables::EnableNativePatch()
	{
		std::uint8_t data[2] = { (std::uint8_t)0xFF, (std::uint8_t)0x23 };
		std::copy(std::begin(data), std::end(data), (std::uint8_t*)m_NativeRetn);
	}

	void GameVariables::DisableNativePatch()
	{
		std::copy(std::begin(m_OriginalNativeRetn), std::end(m_OriginalNativeRetn), m_NativeRetn);
	}
	void* GameVariables::GetNativeReturnAddress()
	{
		return m_NativeRetn;
	}
	GameFunctions::GameFunctions() :
		m_ScriptVM(Signature("4D 8B F9 4D 8B F0 4C 8B C2 4D 63 57 0C 49 63 47 14 4D 8B 6E 10 48 FF C8 49 8B D2", "ScriptVM").Scan().Sub(0x26).As<decltype(m_ScriptVM)>()),
		m_IsDlcPresent(Signature("84 C0 74 0D 8D 53 0C", "IDP").Scan().Sub(63).As<decltype(m_IsDlcPresent)>()),
		m_TriggerScriptEvent(Signature("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9", "TSE").Scan().As<decltype(m_TriggerScriptEvent)>()),

		/*m_model_spawn_bypass(Signature("48 8B C8 FF 52 30 84 C0 74 05 48").Scan().Add(8).As<decltype(m_model_spawn_bypass)>()),*/

		m_EventManager(Signature("40 53 48 81 EC ? ? ? ? 44 8B 81 ? ? ? ? 4C 8B CA 41 8D 40 FF 3D ? ? ? ? 77 42", "EM").Scan().As<decltype(m_EventManager)>()),
		m_ChatMessage(Signature("40 88 B3 ? ? ? ? 89 73 08 48 39 B3 ? ? ? ? 75 24 48 8D 05 ? ? ? ? 48 8B CB 48 89 B3", "CM").Scan().Add(0x16).Rip().As<decltype(m_ChatMessage)>()),
		m_ClockTime(Signature("48 8D 0D ? ? ? ? 8B FA E8 ? ? ? ? 44 8D 0C 5B", "CT").Scan().Add(3).Rip().As<decltype(m_ClockTime)>()),
		m_ChatSensor(Signature("E8 ? ? ? ? 83 F8 FF 75 B9", "CS").Scan().Add(1).Rip().As<decltype(m_ChatSensor)>()),
		m_SessionTime(Signature("48 89 5C 24 08 57 48 83 EC 20 8B F9 48 8B 0D ? ? ? ? 48 8B DA 33 D2 E9 ? ? ? ?", "ST").Scan().As<decltype(m_SessionTime)>()),
		m_GetEventData(Signature("48 85 C0 74 14 4C 8B 10", "GED").Scan().Sub(28).As<decltype(m_GetEventData)>()),
		m_NetworkEvents(Signature("66 41 83 F9 ? 0F 83 ? ? ? ?", "NE").Scan().As<decltype(m_NetworkEvents)>()),
		m_GetPlayerNetworkId(Signature("80 F9 20 73 13 48 8B", "GPNID").Scan().As<decltype(m_GetPlayerNetworkId)>()),
		m_ReportMyselfEvent(Signature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 40 48 8B D9 48 8B 0D ? ? ? ? 48 8B F2", "RMSE").Scan().As<decltype(m_ReportMyselfEvent)>()),
		m_JoinPattern(Signature("48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 48 89 48 08 55 41 54 41 55 41 56 41 57 48 8D 68 A8", "JP").Scan().As<decltype(m_JoinPattern)>()),
		m_Pattern(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 40 44 8B F9 B9 ? ? ? ? 49 8B F1 41 8B E8 4C 8B F2 33 DB E8 ? ? ? ? 48 8B F8 48 85 C0 74 56 48 8B C8 E8 ? ? ? ? 48 8B 84 24 ? ? ? ? 44 8B CD 48 89 47 40 48 8B 84 24 ? ? ? ? 4D 8B C6 48 89 44 24 ? 8B 84 24 ? ? ? ? 41 8B D7 89 44 24 28 48 8B CF 48 89 74 24 ? E8 ? ? ? ? 84 C0 74 10 48 8B CF E8 ? ? ? ? 84 C0 74 04 B3 01 EB 08 48 8B CF E8", "Pat").Scan().As<decltype(m_Pattern)>()),
		m_NetworkInfoChange(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 48 8B F1 48 8B 0D ? ? ? ? 48 8B FA", "NIC").Scan().As<decltype(m_NetworkInfoChange)>()),
		m_GetPlayerNetworkIds(Signature("74 0A 83 F9 1F 77 05 E8 ? ? ? ? 48", "GPNID").Scan().Sub(12).As<decltype(m_GetPlayerNetworkIds)>()),
		m_GiveWantedLevel(Signature("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 44 88 48 20 57 41 54 41 55 41 56 41 57 48 83 EC 30 4C 8B F1 48 8B 0D ? ? ? ? 44 8B E2 B2 01 41 8A D9 45 8B E8 E8 ? ? ? ? 48 8B 0D ? ? ? ?", "GWL").Scan().As<decltype(m_GiveWantedLevel)>()),
		m_pNetworkCanBail(Signature("48 8B 0D ? ? ? ? 33 C0 48 85 C9 74 25", "NetCB").Scan().As<decltype(m_pNetworkCanBail)>()),
		m_DisableErrorScreen(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 60 4C 8B F2 48 8B 94 24 ? ? ? ? 33 DB", "DSES").Scan().As<decltype(m_DisableErrorScreen)>()),
		m_DenyDrops(Signature("49 8B 80 ? ? ? ? 48 85 C0 74 0C F6 80 ? ? ? ? ? 75 03 32 C0 C3", "DenyD").Scan().As<decltype(m_DenyDrops)>()),
		m_GetNumOfEvents(Signature("48 83 EC 28 33 D2 85 C9", "GNOE").Scan().As<decltype(m_GetNumOfEvents)>()),
		m_WndProc(Signature("48 8B 0D ? ? ? ? 48 8D 55 EF FF 15", "WndP").Scan().Sub(853).As<decltype(m_WndProc)>()),
		m_GetLabelText(Signature("75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9", "GLT").Scan().Sub(19).As<decltype(m_GetLabelText)>())
		//m_ResourceError(Signature("45 33 F6 40 8A F2 8B D9 66 85 C0 74 31 44 0F B7 C0 33 D2 8B C1").Scan().Sub(0x2D).As<decltype(m_ResourceError)>()),
		//m_ResourceCall(Signature("48 83 EC 28 33 D2 E8 ? ? ? ? CC").Scan().As<decltype(m_ResourceCall)>()),
		//m_EventQue(Signature("48 8D 71 28 4C 8B F2 48 8B E9 48 8B 3E EB 41 48 8B 5F 08").Scan().Sub(0x25).As<decltype(m_EventQue)>())
		//m_ReceiveEvent(Signature("48 89 1D ? ? ? ? 48 8B 03 4D 8B C4 48 8B D5 48 8B CB FF 50 38 84 C0 0F 84 ? ? ? ? 49 8B CE E8").Scan().Sub(0xD6).As<decltype(m_ReceiveEvent)>())
	{//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 48 8B F1 48 8B 0D ? ? ? ? 48 8B FA
	}
}