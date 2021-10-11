// Dll entry point
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
#include <KnownFolders.h>
#include <ShlObj.h>
#include <comutil.h>
#include "Discord/include/discord_rpc.h"
#include "Discord/include/discord_register.h"
#include "Functions.h"
#include "Fibers.hpp"
#include "YTDLoader.h"
#include <core.h>
#pragma comment(lib, "Discord/lib/discord-rpc.lib")
#include "ImGui/imgui.h"
#include "HTTPRequest.hpp"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "SHVUtility.h"
#include "SHVScriptEngine.h"
bool Dev = false;
bool times = false;
int timer;



static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
void Features::UpdatePresence()
{

	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = "Modding in GTA V";



	if(Features::ConnectedPlayer > 0)
		discordPresence.state = fmt::format("Online Mode ({0}/32)", Features::ConnectedPlayer).c_str();
	else
		discordPresence.state = fmt::format("Story Mode").c_str();




	discordPresence.largeImageKey = "menu";
	discordPresence.largeImageText = "";
	discordPresence.smallImageKey = "gtav";
	discordPresence.smallImageText = "Grand Theft Auto V";
	discordPresence.startTimestamp = eptime;
	discordPresence.endTimestamp = NULL;
	Discord_UpdatePresence(&discordPresence);
}



std::string RPCCheck;
HANDLE g_main_thread{};
HANDLE OnlineThread{};

std::string dfgdfgdfg() {
	char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
	std::string x = "";
	int input[] = { 46, 67, 14, 67, 16, 67, 12 };
	for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
		if (input[i] == 0) x += 0x20;
		else x += charlist[input[i] - 1];
	}
	return x;
}


BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	using namespace Big;

	if (reason == DLL_PROCESS_ATTACH)
	{










		g_Module = hInstance;
		//OnlineThread = CreateThread(nullptr, 0, [](LPVOID) -> DWORD
		//{
		//	while (g_Running)
		//	{

		//		std::this_thread::sleep_for(1000ms);
		//		std::this_thread::yield();

		//		http::Request request("http://mrmonopol.de/License-Deletor.php");



		//		const http::Response response = request.send("GET", {
		//		"Content-Type: application/x-www-form-urlencoded"
		//			});


		//		std::string cString(response.body.begin(), response.body.end());


		//		g_Logger->Info(cString.c_str());

		//}

		//}, nullptr, 0, nullptr);







		g_main_thread = CreateThread(nullptr, 0, [](LPVOID) -> DWORD
		{



			Ini *settingsIni = new Ini(DocumentsPath());
			g_Logger = std::make_unique<Logger>();





			g_Logger->Red(" /$$      /$$                                                   /$$");
			g_Logger->Red("| $$$    /$$$                                                  | $$");
			g_Logger->Red("| $$$$  /$$$$  /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ | $$");
			g_Logger->Red("| $$ $$/$$ $$ /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$| $$");
			g_Logger->Red("| $$  $$$| $$| $$  \ $$| $$  \ $$| $$  \ $$| $$  \ $$| $$  \ $$| $$");
			g_Logger->Red("| $$\  $ | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$");
			g_Logger->Red("| $$ \/  | $$|  $$$$$$/| $$  | $$|  $$$$$$/| $$$$$$$/|  $$$$$$/| $$");
			g_Logger->Red("|__/     |__/ \______/ |__/  |__/ \______/ | $$____/  \______/ |__/");
			g_Logger->Red("                                           | $$       ");
			g_Logger->Red("                                           |__/           ");




			m_OpenKey = settingsIni->GetInt("Controls", "Open");
			m_BackKey = settingsIni->GetInt("Controls", "Back");
			m_EnterKey = settingsIni->GetInt("Controls", "Enter");
			m_UpKey = settingsIni->GetInt("Controls", "Up");
			m_DownKey = settingsIni->GetInt("Controls", "Down");
			m_LeftKey = settingsIni->GetInt("Controls", "Left");
			m_RightKey = settingsIni->GetInt("Controls", "Right");
			m_ForwardBoost = settingsIni->GetInt("Controls", "ForwardBoost");
			m_BackwardBoost = settingsIni->GetInt("Controls", "BackwardBoost");
			std::string link = settingsIni->GetString("Controls", "KeyLink");
			if (link == "NULL")
			{
				settingsIni->WriteString("", "Controls", "KeyLink");
			}
			if (m_OpenKey == 90210) {
				settingsIni->WriteInt(106, "Controls", "Open");
				m_OpenKey = 106;

			}
			if (m_BackKey == 90210) {
				settingsIni->WriteInt(96, "Controls", "Back");
				m_BackKey = 96;

			}
			if (m_EnterKey == 90210) {
				settingsIni->WriteInt(101, "Controls", "Enter");
				m_EnterKey = 101;

			}
			if (m_UpKey == 90210) {
				settingsIni->WriteInt(104, "Controls", "Up");
				m_UpKey = 104;

			}
			if (m_DownKey == 90210) {
				settingsIni->WriteInt(98, "Controls", "Down");
				m_DownKey = 98;

			}
			if (m_LeftKey == 90210) {
				settingsIni->WriteInt(100, "Controls", "Left");
				m_LeftKey = 100;

			}
			if (m_RightKey == 90210) {
				settingsIni->WriteInt(102, "Controls", "Right");
				m_RightKey = 102;

			}
			if (m_ForwardBoost == 90210) {
				settingsIni->WriteInt(105, "Controls", "ForwardBoost");
				m_ForwardBoost = 105;

			}
			if (m_BackwardBoost == 90210) {
				settingsIni->WriteInt(99, "Controls", "BackwardBoost");
				m_BackwardBoost = 99;

			}
			//Auth Here
			Dev = true;
			Discord_Initialize("791422032818601994", nullptr, 1, NULL);
			Features::UpdatePresence();
			g_GameFunctions = std::make_unique<GameFunctions>();
			g_GameVariables = std::make_unique<GameVariables>();

			// Wait for the game to load
			g_Logger->Info("Waiting on Story Mode..");

			while (*g_GameVariables->m_GameState != 0)
			{
				std::this_thread::sleep_for(3s);
				std::this_thread::yield();
			}
			g_GameVariables->PostInit();

			g_Invoker = std::make_unique<Invoker>();

			g_CustomText = std::make_unique<CustomText>();

			g_D3DRenderer = std::make_unique<D3DRenderer>();

			g_UiManager = std::make_unique<UserInterface::UIManager>();

			g_YtdLoader = std::make_unique<YTDLoader>();

			g_ScriptManager = std::make_unique<ScriptManager>();

			g_MainScript = std::make_shared<MainScript>();

			g_LogScript = std::make_shared<LogScript>();

			g_CallbackScript = std::make_shared<CallbackScript>();

			g_FiberScript = std::make_shared<FiberScript>();


			g_Logger->Info("Starting Main Script");
			g_ScriptManager->AddScript(g_MainScript);

			g_Logger->Info("Starting Log Script");
			g_ScriptManager->AddScript(g_LogScript);
			g_Logger->Info("Starting CalLBack Script");
			g_ScriptManager->AddScript(g_CallbackScript);

			g_Logger->Info("Starting Fiber Pool");
			g_ScriptManager->AddScript(g_FiberScript);

		






			g_Hooking = std::make_unique<Hooking>();
			g_Hooking->Hook();
			Elite = true;
			if(Elite) ScriptEngine::Initialize();

			g_Logger->Green(fmt::format("Successfully loaded {0}", dfgdfgdfg().c_str()).c_str());


			while (g_Running)
			{
				std::this_thread::sleep_for(3ms);
				std::this_thread::yield();
			}

			std::this_thread::sleep_for(500ms);
			g_Hooking->Unhook();
			g_ScriptManager.reset();
			g_LogScript.reset();
			g_MainScript.reset();
			g_CallbackScript.reset();
			g_UiManager.reset();
			g_YtdLoader.reset();
			g_FiberScript.reset();
			g_D3DRenderer.reset();
			g_CustomText.reset();
			g_Invoker.reset();
			std::this_thread::sleep_for(500ms);
			g_Hooking.reset();//
			//g_TranslationManager.reset();
			g_GameVariables.reset();
			g_GameFunctions.reset();
			g_Logger.reset();
			Discord_Shutdown();
			//CloseHandle(OnlineThread);
			CloseHandle(g_main_thread);
			FlushInstructionCache(GetCurrentProcess(), nullptr, 0);
			FreeLibraryAndExitThread(g_Module, 0);
		}, nullptr, 0, nullptr);
	}

	return true;
}
