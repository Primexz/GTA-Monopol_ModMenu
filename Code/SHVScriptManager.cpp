#include "SHVScriptManager.h"
#include "SHVScriptThread.h"
#include "SHVScriptEngine.h"
#include "SHVASILoader.h"
#include "SHVUtility.h"
#include "enums.h"
#include "Game.hpp"
#include "Hooking.hpp"
#include "ScriptManager.hpp"
#include "LogScript.hpp"
#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Invoker.hpp"
#include "CustomText.hpp"
#include "D3DRenderer.hpp"
#include "UI/UIManager.hpp"
#include "Translation.hpp"
#include "Functions.h"
#include <KnownFolders.h>
#include <ShlObj.h>
#include <comutil.h>
#include "Functions.h"
#include "Fibers.hpp"
#include "YTDLoader.h"
#define DLL_EXPORT __declspec( dllexport )

SHVScriptThread	g_ScriptThread;
SHVScriptThread	g_AdditionalThread;
HANDLE          g_MainFiber;
SHVScript* g_CurrentScript;

std::uint32_t g_ThreadHash = "main_persistent"_joaat;

//#######################SHV Script Stuff###########################

void SHVScript::Tick()
{
	if (timeGetTime() < wakeAt)
	{
		if (GetCurrentFiber() != g_MainFiber) SwitchToFiber(g_MainFiber); return;
	}

	else if (scriptFiber)
	{
		g_CurrentScript = this;
		SwitchToFiber(scriptFiber);
		g_CurrentScript = nullptr;
	}

	else
	{
		scriptFiber = CreateFiber(NULL, [](LPVOID handler) {reinterpret_cast<SHVScript*>(handler)->Run(); }, this);
	}

	SwitchToFiber(g_MainFiber);
}

void SHVScript::Run()
{
	callbackFunction();
}

void SHVScript::Wait(uint32_t time)
{
	if (g_MainFiber && GetCurrentFiber() != g_MainFiber)
		SwitchToFiber(g_MainFiber);
	wakeAt = timeGetTime() + time;
}

void SHVScriptThread::DoRun()
{
	scriptMap thisIterScripts(m_scripts);
	for (auto& pair : thisIterScripts)
	{
		pair.second->Tick();
	}
}
void write_text_to_log_file(const std::string& text)
{
	std::ofstream log_file(
		"log_file.txt", std::ios_base::out | std::ios_base::app);
	log_file << text;
}
void SHVScriptThread::AddScript(HMODULE module, void(*fn)())
{
	std::string moduleName = Utility::GetModuleNameWithoutExtension(module).c_str();
	if (m_scripts.find(module) != m_scripts.end())
	{
		g_Logger->Info("Script '%s' is already registered", moduleName.c_str());
		return;
	}
	else
	{
		m_scripts[module] = std::make_unique<SHVScript>(fn);
	}
}

void SHVScriptThread::RemoveScript(HMODULE module)
{
	std::string msg = FMT("Removed '%s'", Utility::GetModuleNameWithoutExtension(module).c_str());
	std::shared_ptr<SHVScript> script;

	if (Utility::GetMapValue(m_scripts, module, script))
	{
		script->Wait(0);
		m_scripts.erase(module);
		FreeLibrary(module);
		CloseHandle(module);
		//script.reset();
	}
	g_Logger->Info(msg.c_str());
	/*
		if (Utility::GetMapValue(m_scripts, module, script))
	{
		script->Wait(0);
		m_scripts.erase(module);
		FreeLibrary(module);
		CloseHandle(module);
		//script.reset();
	}
	*/
}

void SHVScriptThread::RemoveScript(void(*fn)())
{
	for (const auto& pair : m_scripts)
	{
		if (pair.second->GetCallbackFunction() == fn)
		{
			RemoveScript(pair.first);
		}
	}
}

void SHVScriptThread::RemoveAllScripts()
{
	if (ScriptCount())
	{
		for (auto& pair : m_scripts)
		{
			RemoveScript(pair.first);
		}
		//ScriptEventLog("~g~All ASI mods have been unloaded successfully.");
	}
}

size_t SHVScriptThread::ScriptCount()
{
	return m_scripts.size();
}















namespace SHVScriptManager
{
	bool isKeyPressedOnce(bool& bIsPressed, DWORD vk)
	{
		if (IsKeyPressed(vk))
		{
			if (bIsPressed == false)
			{
				bIsPressed = true;
				return true;
			}
		}
		else if (bIsPressed == true)
		{
			bIsPressed = false;
		}
		return false;
	}
	void WndProc(HWND /*hwnd*/, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		for (auto& function : g_WndProcCb) function(uMsg, wParam, lParam);

		if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP)
		{
			for (auto& function : g_keyboardFunctions) function((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
		}
	}
	void MainFiber()
	{
		g_MainFiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(nullptr);

		if (g_MainFiber)
		{
			static SHVscrThread* target_thread = nullptr;

			SHVscrThread* current_thread = GetActiveThread();

			// do this while script::wait
			g_AdditionalThread.DoRun();
			g_ScriptThread.DoRun();
			//	SetActiveThread(target_thread);
			//	SetActiveThread(current_thread);


			static bool RemoveAllScriptsBool = false; const uint32_t RemoveAllScriptsKey = VK_NEXT; //Page Down
			static bool LoadAllScriptsBool = false; const uint32_t LoadAllScriptsKey = VK_PRIOR;//Page Up
			static bool RemoveScriptHookBool = false; const uint32_t RemoveScriptHookKey = VK_END;

			if (IsKeyPressed(RemoveAllScriptsKey))
			{
				g_AdditionalThread.RemoveAllScripts();
				g_ScriptThread.RemoveAllScripts();
			}
		}
	}
}
//###########################################ASI Loader Imports################################################
DLL_EXPORT void WndProcHandlerRegister(TWndProcFn function)
{
	g_WndProcCb.insert(function);
}

DLL_EXPORT void WndProcHandlerUnregister(TWndProcFn function)
{
	g_WndProcCb.erase(function);
}

/* keyboard */
DLL_EXPORT void keyboardHandlerRegister(KeyboardHandler function)
{
	g_keyboardFunctions.insert(function);
}

DLL_EXPORT void keyboardHandlerUnregister(KeyboardHandler function)
{
	g_keyboardFunctions.erase(function);
}

/* D3d SwapChain */
typedef void(*PresentCallback)(void*);

DLL_EXPORT void presentCallbackRegister(PresentCallback cb)
{
	return;
}

DLL_EXPORT void presentCallbackUnregister(PresentCallback cb)
{
	return;
}

/* textures */
DLL_EXPORT int createTexture(const char* texFileName)
{
	return 0;
}

DLL_EXPORT void drawTexture(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a)
{
	return;
}

/* scripts */
DLL_EXPORT void changeScriptThread(UINT32 hash)
{
	if (g_ThreadHash != hash)
		g_ThreadHash = hash;
}

DLL_EXPORT void scriptWait(DWORD time)
{
	g_CurrentScript->Wait(time);
}

DLL_EXPORT void scriptRegister(HMODULE module, void(*function)())
{
	g_ScriptThread.AddScript(module, function);
}

DLL_EXPORT void scriptRegisterAdditionalThread(HMODULE module, void(*function)())
{
	g_AdditionalThread.AddScript(module, function);
}

DLL_EXPORT void scriptUnregister(HMODULE module)
{
	g_AdditionalThread.RemoveScript(module);
	g_ScriptThread.RemoveScript(module);
}

DLL_EXPORT void scriptUnregister(void(*function)())
{
	// deprecated
	g_AdditionalThread.RemoveScript(function);
	g_ScriptThread.RemoveScript(function);
}
uint64_t g_hash;
/* natives */
DLL_EXPORT void nativeInit(UINT64 hash)
{
	g_hash = hash;
	g_Invoker->BeginCall();
}

DLL_EXPORT void nativePush64(UINT64 val)
{
	g_Invoker->Push(val);
}

DLL_EXPORT uint64_t* nativeCall()
{
	g_Invoker->EndCall(g_hash);
	return g_Invoker->ReturnAdd();
}

/* global variables */
DLL_EXPORT UINT64* getGlobalPtr(int globalId)
{
	return reinterpret_cast<PUINT64>(&g_GameVariables->m_GlobalBase[globalId >> 18 & 0x3F][globalId & 0x3FFFF]);
}

/* world pools */
DLL_EXPORT int worldGetAllPeds(int* arr, int arrSize)
{
	return 0;
}

DLL_EXPORT int worldGetAllVehicles(int* arr, int arrSize)
{
	return 0;
}

DLL_EXPORT int worldGetAllObjects(int* arr, int arrSize)
{
	return 0;
}

DLL_EXPORT int worldGetAllPickups(int* arr, int arrSize)
{
	return 0;
}

/* game version */
DLL_EXPORT eGameVersion getGameVersion()
{
	return static_cast<bool>(GetModuleHandleA("steam_api64.dll")) ? VER_1_0_1493_0_STEAM : VER_1_0_1493_0_NOSTEAM;
}

/* misc */
DLL_EXPORT BYTE* getScriptHandleBaseAddress(int handle)
{
	return 0;
}

DLL_EXPORT int registerRawStreamingFile(const std::string& fileName, const std::string& registerAs)
{
	return 0;
}