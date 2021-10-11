#pragma once
#include "Structs.h"
#include "Types.hpp"
#include "enums.h"
#include "srcEngine.h"
#include "pgCollection.h"

namespace rage
{
	struct scrNativeRegistration;
}
struct twoBytes
{
	BYTE	byte[2];

	bool	empty();
};
bool	twoBytes::empty()
{
	bool r = true;
	for (int i = 0; i < 2; ++i)
		if (this->byte[i] != 0)
		{
			r = false;
			break;
		}
	return r;
}
namespace Big
{
	class GameVariables
	{
	public:
		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;

		void PostInit();
		void Update();
		void OwnedExplosionBypass(bool toggle);
		void defuseEvent(RockstarEvent e, bool toggle);
		void EnableNativePatch();
		void DisableNativePatch();
		void* GetNativeReturnAddress();//
		std::uint32_t* m_GameState;
		std::uint32_t* m_FrameCount;
		std::vector<NetGameEvent_t> m_NetGameEvents;
		pgCollection<scrThread*>* script_threads;
		CNetGamePlayers* g_players[32];
		bool* is_session_started;
		uint64_t m_WorldPtr;
		uint64_t PlayerListPtr;
		uint32_t activeThreadTlsOffset;
		//uint64_t M_cWorld;
		std::vector<void*> m_EventPtr;
		twoBytes* m_ownedExplosionBypass;



		HWND m_GameWindow;
		IDXGISwapChain* m_Swapchain;
		rage::scrNativeRegistration** m_NativeRegistrations;
		std::uint64_t** m_GlobalBase;
		char* m_NativeRetn;
		char m_OriginalNativeRetn[2];
		__int64** m_globalPtr;
		CBlipList* m_blipList;
		MemoryPool** m_MemoryPool;
		void* m_onlineName;
		char* m_GameBuild;
	};

	class GameFunctions
	{
	public:
		explicit GameFunctions();
		~GameFunctions() noexcept = default;
		GameFunctions(GameFunctions const&) = delete;
		GameFunctions(GameFunctions&&) = delete;
		GameFunctions& operator=(GameFunctions const&) = delete;
		GameFunctions& operator=(GameFunctions&&) = delete;
		using IsDlcPresent = bool(std::uint32_t hash);
		IsDlcPresent* m_IsDlcPresent;

		using ScriptVM = int(void* stack, signed __int64** globals, void* program, scrThreadContext* threadContext);
		ScriptVM* m_ScriptVM;



		using IsEntityUpsideDown = bool(std::int32_t Entity);
		IsEntityUpsideDown* m_IsEntityUpsideDown;

		using TriggerScriptEvent = int(bool unk0, uint64_t* args, int argCount, int bitFlags);
		TriggerScriptEvent* m_TriggerScriptEvent;

		using EventMgr = bool(CScriptedGameEvent* events, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer);
		EventMgr* m_EventManager;

		PVOID m_model_spawn_bypass;


		using NetworkMgr = void(__int64 a1, CNetGamePlayers* a2, __int64 a3, unsigned __int16 a4, int a5, int a6, __int64 a7, __int64 a8);
		NetworkMgr* m_NetworkEvents;

		using GetEventData = int(int eventGroup, int eventIndex, int* argStruct, int argStructSize);
		GetEventData* m_GetEventData;
		using ChatSensor = int(__int64 chat_menu, const char* user_text, const char** output_text);
		ChatSensor* m_ChatSensor;

		using DisableErrorScreen = void(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background);
		DisableErrorScreen* m_DisableErrorScreen;
		using GetNumOfEvents = int(int eventgroup);
		GetNumOfEvents* m_GetNumOfEvents;
		using ChatMessage = void(void* thisptr, __int64 unk1, __int64 unk2, const char* message);
		ChatMessage* m_ChatMessage;
		using pEventQue = void(void* thisptr, netGameEvent* event);
		pEventQue* m_EventQue;
		using pResourcePrevent = void(std::uint32_t errorHash, bool terminateProcess);
		pResourcePrevent* m_ResourceError;
		using pResourceCall = bool(std::uint32_t errorHash);
		pResourceCall* m_ResourceCall;
		using TestHook = bool(__int64 a, __int64 b);
		TestHook* m_TestHook;
		using GetPlayerNetworkId = CNetGamePlayers * (int player);
		GetPlayerNetworkId* m_GetPlayerNetworkId;
		using GetPlayerNetworkIds = CNetGamePlayer * (int player);
		GetPlayerNetworkIds* m_GetPlayerNetworkIds;

		using GiveWantedLevel = void(CNetGamePlayers* a1, int64_t wantedLevel, int a3, char a4);
		GiveWantedLevel* m_GiveWantedLevel;


		using RandomPat = char(int a1, __int64 a2, unsigned int a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7);
		RandomPat* m_Pattern;

		using EventPat = void(__int64 a1, unsigned int a2, unsigned int a3, unsigned int a4);
		EventPat* m_EventPat;

		using SessionTime = void(int hour, int min);
		SessionTime* m_SessionTime;


		clockTime* m_ClockTime;

		using pMetricHook = void(uint64_t, bool);
		pMetricHook* m_pMetricHook;

		/* Metric AAC Hooks

		using pMetricHook1 = char(rlMetric *src);
		pMetricHook1* m_pMetricHook1;
		using pMetricHook2 = char(unsigned int a1, __int64 a2, char a3);
		pMetricHook2* m_pMetricHook2;
		using pMetricHook3 = char(unsigned int a1, __int64 a2);
		pMetricHook3* m_pMetricHook3;
		*/





		using pDenyDrops = bool(void* classidonthave, void* unk, CPed* ped);
		pDenyDrops* m_DenyDrops;

		using pReceiveEvent = void(CEventMgr* this_, netGameEvent* event, datBitBuffer* buffer, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer, std::uint16_t unk1, std::uint32_t unk2, std::int32_t unk3);
		pReceiveEvent* m_ReceiveEvent;

		using pReportMyselfEvent = bool(void* thisptr, CNetGamePlayer* sourcePlayer, CNetGamePlayer* targetPlayer);
		pReportMyselfEvent* m_ReportMyselfEvent;
		using pNetworkInfoChange = bool(void* thisptr, CNetGamePlayer* sourcePlayer, CNetGamePlayer* targetPlayer);
		pNetworkInfoChange* m_NetworkInfoChange;
		using pJoinPattern = int(__int64 a1, int a2, __int64* a3, int a4);
		pJoinPattern* m_JoinPattern;
		using pNetworkCanBail = bool();
		pNetworkCanBail* m_pNetworkCanBail;

		using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WndProc* m_WndProc;

		using GetLabelText = const char* (void* unk, const char* label);
		GetLabelText* m_GetLabelText;

	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
}
