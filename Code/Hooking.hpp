#pragma once
#include "VMTHook.hpp"
#include "Structs.h"
#include "srcEngine.h"
namespace Big
{
	struct Hooks
	{
		static int GetNumOfEvents(int eventgroup);
		static int JoinPlayer(__int64 a1, int a2, __int64* a3, int a4);
		static void EventPat(__int64 a1, unsigned int a2, unsigned int a3, unsigned int a4);
		static int Pattern(int a1, __int64 a2, unsigned int a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7);
		static int ScriptVM(void* stack, signed __int64** globals, void* program, scrThreadContext* threadContext);
		static int SensorChat(__int64 chat_menu, const char* user_text, const char** output_text);
		static bool IsDlcPresent(std::uint32_t hash);
		static bool EventManager(void* events, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer);
		static bool ReportMyselfEvent(void* events, CNetGamePlayer* source, CNetGamePlayer* target);
		static bool InfoEvent(void* events, CNetGamePlayer* source, CNetGamePlayer* target);
		static bool NetworkManager(__int64 a1, CNetGamePlayers* a2, CNetGamePlayers* a3, unsigned __int16 a4, int a5, int a6, __int64 a7, __int64 a8);
		static bool DenyDrops(void* classidonthave, void* unk, CPed* ped);
		static bool IsEntityUpsideDown(std::uint32_t entity);
		static void ReceiveEvent(Big::CEventMgr* this_, netGameEvent* event, datBitBuffer* buffer, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer, std::uint16_t unk1, std::uint32_t unk2, std::int32_t unk3);
		static void DisableErrorScreen(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background);
		static bool GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		static int TriggerScriptEvent(bool unk0, uint64_t* args, int argCount, int bitFlags);
		static void MetricHook(void* unk1, bool unk2);
		static bool TestHook(__int64 a, __int64 b, int c, char d);
		static void ResourceError(std::uint32_t errorHash, bool terminateProcess);
		static bool ResourceCall(std::uint32_t errorHash);
		static void EventQue(void* thisptr, netGameEvent* event);
		static char sub_7FF6A853F9EC(rlMetric* Src);
		static char sub_7FF6A8902B0C(unsigned int a1, rlMetric* a2, char a3);
		static char sub_7FF6A89027C4(unsigned int a1, rlMetric* a2);
		static bool NetworkCanBail();
		static CNetGamePlayers* GetPlayerByIndex(int index);
		static void tick();
		static void CheatMessage(void* thisptr, __int64 unk1, __int64 unk2, const char* message);
		static const char* GetLabelText(void* unk, const char* label);
		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		static constexpr auto PresentIndex = 8;
		static HRESULT Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags);

		static constexpr auto ResizeBuffersIndex = 13;
		static HRESULT ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	};

	class Hooking
	{
	public:
		explicit Hooking();
		~Hooking() noexcept;
		Hooking(Hooking const&) = delete;
		Hooking(Hooking&&) = delete;
		Hooking& operator=(Hooking const&) = delete;
		Hooking& operator=(Hooking&&) = delete;
		void* m_OriginalTriggerScriptEvent{};
		void Hook();
		void Unhook();

		friend struct Hooks;
	private:
		void* m_NtQueryVirtualMemory{};

		void* m_OriginalIsDlcPresent{};
		void* m_OriginalScriptVM{};
		void* m_OriginalGetNumOfEvents{};
		void* m_OriginalDisableErrorScreen{};
		void* m_OriginalChatMesage{};
		void* m_OriginalIsEntityUpsideDown{};
		void* m_OriginalReceiveEvent{};
		void* m_OriginalEventManager{};
		void* m_OriginalResourceError{};
		void* m_OriginalEventQue{};
		void* m_OriginalResourceCall{};
		void* m_OriginalReportMyselfEvent{};
		void* m_OriginalInfoEvent{};
		void* m_OriginalNetworkManager{};
		void* m_OriginalSensorChat{};
		void* m_OriginalEventPat{};
		void* m_OriginalpMetricHook{};
		void* m_OriginalTestHook{};
		void* m_OriginalpNetworkCanBail{};
		void* m_OriginalGetEventData{};
		void* m_OriginalJoinPlayer{};
		void* m_OriginalPattern{};
		void* m_Originalsub_7FF6A853F9EC{};
		void* m_Originalsub_7FF6A8902B0C{};
		void* m_Originalsub_7FF6A89027C4{};
		CNetGamePlayers* m_OriginalGetPlayerByIndexNet{};

		void* m_OriginalGetLabelText{};
		void* m_OriginalWndProc{};
		void* m_OriginalDenyDrops{};
		VMTHook m_D3DHook;

		char* m_ObjectBypass;
		char m_OriginalObjectBypass[2];
		char* m_ObjectCheck;
		char m_OriginalObjectCheck[24];
		char* m_ModelSpawn;
		char m_OriginalModelSpawn[2];
	};

	inline std::unique_ptr<Hooking> g_Hooking;
}
