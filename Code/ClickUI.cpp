#include "Game.hpp"
#include "LogScript.hpp"
#include "UI/UIManager.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "MainScript.hpp"
#include "Natives.hpp"
#include "MainScript.hpp"
#include "Functions.h"
#include "Fibers.hpp"
#include "Encryptor.h"
#include "Hashes.h"
#include "Discord/include/discord_rpc.h"
#include "stb_image.h"
#include "ClipboardXX.hpp"
#include "xstring"
#include "Hooking.hpp"
#include "ImGui/imgui_impl_dx11.h"
#include <string>
#include "ScriptCallback.hpp"
#include "Auth.h"
#include "remotehashes.h"
#include "string"
#include "Lists.hpp"
#include <core.h>
#define STB_IMAGE_IMPLEMENTATION
#ifdef _WIN32
#define IM_NEWLINE "\r\n"

#else
#define IM_NEWLINE "\n"
#endif
#define IM_MAX(_A,_B)       (((_A) >= (_B)) ? (_A) : (_B))


namespace ImGui {
	struct TabsDesc {
		__int32	lableCount;
		float lableWidth;
		__int32 currentidx;

	};

	struct Tabs {
		TabsDesc* tbd;
		ImGuiID ID;
		__int32 selectedIdx;
	};

	static   ImVector<Tabs*> CacheTabs;
	static   Tabs* CurTabs;




	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
	{
		static ID3D11Device* g_pd3dDevice = NULL;

		// Load from disk into a raw RGBA buffer
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create texture
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = image_width;
		desc.Height = image_height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		ID3D11Texture2D* pTexture = NULL;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem = image_data;
		subResource.SysMemPitch = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;
		g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
		pTexture->Release();

		*out_width = image_width;
		*out_height = image_height;
		stbi_image_free(image_data);

		return true;
	}


	inline bool AddTab(const char* label, const char* tooltip)
	{
		TabsDesc* tbs = CurTabs->tbd;
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec2 itemSpacing = style.ItemSpacing;
		ImVec4 color = style.Colors[ImGuiCol_Button];
		ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
		ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
		style.ItemSpacing.x = 0;

		if (tbs->currentidx > 0)
			ImGui::SameLine();

		// push the style
		if (tbs->currentidx == CurTabs->selectedIdx)
		{
			style.Colors[ImGuiCol_Button] = colorActive;
			style.Colors[ImGuiCol_ButtonActive] = colorActive;
			style.Colors[ImGuiCol_ButtonHovered] = colorActive;
		}
		else
		{
			style.Colors[ImGuiCol_Button] = color;
			style.Colors[ImGuiCol_ButtonActive] = colorActive;
			style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		}

		// Draw the button
		if (ImGui::Button(label, ImVec2(tbs->lableWidth, 0))) {
			CurTabs->selectedIdx = tbs->currentidx;
		}

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("%s", tooltip);
			ImGui::EndTooltip();
		}

		// Restore the style
		style.Colors[ImGuiCol_Button] = color;
		style.Colors[ImGuiCol_ButtonActive] = colorActive;
		style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		style.ItemSpacing = itemSpacing;

		tbs->currentidx++;
		return CurTabs->selectedIdx == tbs->currentidx;
	}
}


namespace Big
{

	int BBulletType = 0;
	float BBulletDamage = 5;
	float BBulletCameraShake = 5;
	bool BBulletAudible = true;
	bool BBulletInvisible = false;


	const char* Name;
	const char* RID;
	const char* GodMode;
	const char* Wanted;
	const char* Street;
	const char* Zone;
	const char* Veh;



	std::string encryptedstring2() {
		char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
		std::string x = "";
		int input[] = { 46, 67, 14, 67, 16, 67, 12 };
		for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
			if (input[i] == 0) x += 0x20;
			else x += charlist[input[i] - 1];
		}
		return x;
	}


	void Overlay(bool* p_open)
	{

		const float DISTANCE = 10.0f;
		static int corner = 0;
		ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		if (corner != -1)
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
		if (ImGui::Begin("Example: Simple Overlay", p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{

			ImGui::Text(encryptedstring2().c_str());


			ImGui::Separator();
			ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate/2);
			ImGui::Text("Frametime %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
			ImGui::Text(fmt::format("Lobby: {0}", Features::ConnectedPlayer).c_str());
			ImGui::Text(fmt::format("Blocked Events: {0}", Features::BlockedEvents).c_str());

			if (Features::MoneyDropBool || Features::ALLMoneyDropBool || Features::RPDropBool || Features::ForceShowMoneyStat)
			{
				ImGui::Text(fmt::format("Total Money Droped: {0}$", Features::TotalDropedMoney).c_str());
				ImGui::Text(fmt::format("Total Bags: {0}", Features::TotalMoneyBags).c_str());
			}

			ImGui::Text("Menu Version: 1.7");
		}
		ImGui::End();
	}





	bool kick = false;
	float armorper;

	const char* speed;
	int updatede;




	static void OwnedExplosion(Ped ped, float x, float y, float z, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake)
	{


		auto nword = Memory::pattern("F3 0F 11 45 ? F3 0F 11 55 ? 89 5C 24 30 4C 89 75 9F 4C 89 75 AF 44 89 75 B7 48 C7 45").count(1).get(0).get<char>(120);
		nword += *reinterpret_cast<std::int32_t*>(nword);
		nword += sizeof(std::int32_t);

		*nword = 1;
		invoke<Void>(0x172AA1B624FA1013, ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake);
		*nword = 0;
	}

	static void ShowHelpMarker(const char* desc)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}








	int correction = 0;
	int instant = 0;
	bool asasd(uint vehID)
	{
		int Tries = 0;
		bool
			hasControl = false,
			giveUp = false;
		do
		{
			hasControl = NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehID);
			Tries++;
			if (Tries > 300)
				giveUp = true;
		} while (!hasControl && !giveUp);

		if (giveUp)
			return false;
		else return true;
	}

	void dothis(char* anim, char* animid)
	{
		int pPlayer = PLAYER::PLAYER_PED_ID();
		asasd(pPlayer);
		STREAMING::REQUEST_ANIM_DICT(anim);
		if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
		{
			AI::TASK_PLAY_ANIM(pPlayer, anim, animid, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		}
	}
	float bulletpp = 0.2f;

	void ptfx(char* call1, char* call2, char* name, int bone) {
		float fx = bulletpp;
		STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(call2);
		int ptfx = GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(name, PLAYER::PLAYER_PED_ID(), 0.00f, 0.00f, 0.00f,
			0.00f, 0.00f, 0.0f, bone, fx, 1, 1, 1);
		STREAMING::REMOVE_PTFX_ASSET();

	}

	void tpdich(Vector3 Coords)
	{
		int Handle = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
		{
			ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
		}
		else
			ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}

	int INSTR_CONTAINER;
	int INSTR_COUNTER;
	void IDKINIT() {
		INSTR_COUNTER = 0;
		INSTR_CONTAINER = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(INSTR_CONTAINER, 255, 255, 255, 0, 0);
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "CLEAR_ALL");
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "SET_CLEAR_SPACE");
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(200);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}


	bool asdasd(uint vehID)
	{
		int Tries = 0;
		bool
			hasControl = false,
			giveUp = false;
		do
		{
			hasControl = NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehID);
			Tries++;
			if (Tries > 300)
				giveUp = true;
		} while (!hasControl && !giveUp);

		if (giveUp)
			return false;
		else return true;
	}

	void machanimation(char* anim, char* animid)
	{
		int pPlayer = PLAYER::PLAYER_PED_ID();
		asdasd(pPlayer);
		STREAMING::REQUEST_ANIM_DICT(anim);
		if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
		{
			AI::TASK_PLAY_ANIM(pPlayer, anim, animid, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		}
	}

	void IDKADD(char* text, int button) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "SET_DATA_SLOT");
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(INSTR_COUNTER);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(button);
		GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		INSTR_COUNTER++;
	}


	void IDKEND() {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "DRAW_INSTRUCTIONAL_BUTTONS");
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "SET_BACKGROUND_COLOUR");
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(80);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}


	static void ShowExampleMenuFile()
	{

		ImGui::MenuItem("(dummy menu)", NULL, false, false);
		if (ImGui::MenuItem("New")) {}
		if (ImGui::MenuItem("Open", "Ctrl+O")) {}
		if (ImGui::BeginMenu("Open Recent"))
		{
			ImGui::MenuItem("fish_hat.c");
			ImGui::MenuItem("fish_hat.inl");
			ImGui::MenuItem("fish_hat.h");
			if (ImGui::BeginMenu("More.."))
			{
				ImGui::MenuItem("Hello");
				ImGui::MenuItem("Sailor");
				if (ImGui::BeginMenu("Recurse.."))
				{
					ShowExampleMenuFile();
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Save", "Ctrl+S")) {}
		if (ImGui::MenuItem("Save As..")) {}
		ImGui::Separator();
		if (ImGui::BeginMenu("Options"))
		{
			static bool enabled = true;
			ImGui::MenuItem("Enabled", "", &enabled);
			ImGui::BeginChild("child", ImVec2(0, 60), true);
			for (int i = 0; i < 10; i++)
				ImGui::Text("Scrolling Text %d", i);
			ImGui::EndChild();
			static float f = 0.5f;
			static int n = 0;
			static bool b = true;
			ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
			ImGui::InputFloat("Input", &f, 0.1f);
			ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
			ImGui::Checkbox("Check", &b);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Colors"))
		{
			float sz = ImGui::GetTextLineHeight();
			for (int i = 0; i < ImGuiCol_COUNT; i++)
			{
				const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
				ImVec2 p = ImGui::GetCursorScreenPos();
				ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
				ImGui::Dummy(ImVec2(sz, sz));
				ImGui::SameLine();
				ImGui::MenuItem(name);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Disabled", false)) // Disabled
		{
			IM_ASSERT(0);
		}
		if (ImGui::MenuItem("Checked", NULL, true)) {}
		if (ImGui::MenuItem("Quit", "Alt+F4")) {}
	}

	static float damage1 = { 0.f };
	static float spread1 = { 0.f };
	static float recoil1 = { 0.f };
	static float range1 = { 0.f };
	static float reloadtime1 = { 0.f };
	static float muzzlevelocity1 = { 0.f };
	static char numberplatetxt[99] = "";
	static const char* platten[] = {
	"Blue/White", "Yellow/Black","Yellow/Blue", "Blue/White2", "Blue/White3", "Yankton"
	};
	int Headdlight = { 0 };
	bool LogScript::IsInitialized()
	{
		return m_Initialized;

	}

	ScriptType LogScript::GetType()
	{
		return ScriptType::D3D;
	}

	static const char* wetter[] = {
"Clear", "Clearing","Snowlight", "Thunder", "Blizzard", "Overcast", "Foggy", "Smog", "Clouds"
	};

	static const char* lobbywetter[]  =
	{
		"EXTRASUNNY",
		"CLEAR",
		"CLOUDS",
		"SMOG",
		"FOGGY",
		"OVERCAST",
		"RAIN",
		"THUNDER",
		"CLEARING",
		"NEUTRAL",
		"SNOW",
		"BLIZZARD",
		"SNOWLIGHT",
		"XMAS",
		"HALLOWEEN",
		"BLACK SCREEN"
	};
	void TPPPP(Vector3 Coords)
	{
		g_FiberScript->addTask([Coords] {
		int Handle = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
		{
			ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
		}
		else
			ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
		});
	}










	int rp;
	int money;
	int rank;
	int kills2;
	int deaths2;
	int handle;
	int handle2;
	int bank;
	int raceswon;
	int raceslost;
	float kd;
	int earnings;
	int tempMoney;
	int death;
	int deathlost;
	int races;
	int isOtr;
	std::string PlayerIP;
	std::string port_str;
	bool deleteveh = false;
	bool kickplayerxd = false;
	bool SetNumberPlateTXT = false;
	bool setlevelinstant = false;
	bool correctlevel = false;
	bool crash1 = false;
	bool tptoplayer = false;
	bool tpintoveh = false;
	bool airstrike = false;
	bool ramplayer = false;
	bool setalpha = false;;
	bool cageallplayer = false;
	bool kickoutcar = false;
	bool cageplayer = false;
	bool normalkill = false;
	bool shootkill = false;
	bool cloneped = false;
	bool skipcut = false;
	bool randomoutfit = false;
	bool unlockall = false;
	bool removeattach = false;
	bool startautopilot = false;
	bool stopautopilot = false;


	char status_text[2048] = { 0 };
	void update_status_text()
	{


		if (GetTickCount() < 2500)
		{
			UI::SET_TEXT_FONT(0);
			UI::SET_TEXT_SCALE(0.55f, 0.55f);
			UI::SET_TEXT_COLOUR(255, 255, 255, 255);
			UI::SET_TEXT_WRAP(0.0f, 1.0f);
			UI::SET_TEXT_CENTRE(1);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
			UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
			UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(status_text);
			UI::END_TEXT_COMMAND_DISPLAY_TEXT(0.5, 0.5);
		}
	}
	void notifyBottom(char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		UI::BEGIN_TEXT_COMMAND_PRINT((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		UI::END_TEXT_COMMAND_PRINT(4000, 1);
	}	void notifyBottom(std::string str) { notifyBottom(&str[0]); }



	void notifyCenter(char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		sprintf_s(status_text, "%s", buf);
	}	void notifyCenter(std::string str) { notifyCenter(&str[0]); }


	void Big::UpdateNativeShit()
	{


		if (removeattach)
		{
			Features::ClearProps();

			removeattach = false;
		}

		if (startautopilot)
		{
			int WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

			if (UI::DOES_BLIP_EXIST(WaypointHandle)) {
				Vector3 WaypointPos = UI::GET_BLIP_COORDS(WaypointHandle);
				AI::TASK_VEHICLE_DRIVE_TO_COORD(PLAYER::PLAYER_PED_ID(), VehID, WaypointPos.x, WaypointPos.y, WaypointPos.z, 18.f, 0, VehID, DrivingStyleNormal, 1.f, true);
			}
			else
				ScriptEventLog((char*)"No Waypoint found!");


			startautopilot = false;

		}

		if (stopautopilot)
		{
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());

			stopautopilot = false;
		}

		if (unlockall)
		{

			ScriptEventLog("~y~Starting Unlock All..");
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_12"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_12"), -1, 1);




			STATS::STAT_SET_INT($("MP0_AWD_FMHORDWAVESSURVIVE"), 10, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMPICKUPDLCCRATE1ST"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_WIN_CAPTURE_DONT_DYING"), 25, 1);
			STATS::STAT_SET_INT($("MP0_AWD_DO_HEIST_AS_MEMBER"), 25, 1);
			STATS::STAT_SET_INT($("MP0_AWD_PICKUP_CAP_PACKAGES"), 100, 1);
			STATS::STAT_SET_BOOL($("MP0_AWD_FINISH_HEIST_NO_DAMAGE"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_WIN_GOLD_MEDAL_HEISTS"), 25, 1);
			STATS::STAT_SET_INT($("MP0_AWD_KILL_TEAM_YOURSELF_LTS"), 25, 1);
			STATS::STAT_SET_INT($("MP0_AWD_KILL_PSYCHOPATHS"), 100, 1);
			STATS::STAT_SET_INT($("MP0_AWD_DO_HEIST_AS_THE_LEADER"), 25, 1);
			STATS::STAT_SET_BOOL($("MP0_AWD_STORE_20_CAR_IN_GARAGES"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMHORDWAVESSURVIVE"), 10, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMPICKUPDLCCRATE1ST"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_WIN_CAPTURE_DONT_DYING"), 25, 1);
			STATS::STAT_SET_INT($("MP1_AWD_DO_HEIST_AS_MEMBER"), 25, 1);
			STATS::STAT_SET_INT($("MP1_AWD_PICKUP_CAP_PACKAGES"), 100, 1);
			STATS::STAT_SET_BOOL($("MP1_AWD_FINISH_HEIST_NO_DAMAGE"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_WIN_GOLD_MEDAL_HEISTS"), 25, 1);
			STATS::STAT_SET_INT($("MP1_AWD_KILL_TEAM_YOURSELF_LTS"), 25, 1);
			STATS::STAT_SET_INT($("MP1_AWD_KILL_PSYCHOPATHS"), 100, 1);
			STATS::STAT_SET_INT($("MP1_AWD_DO_HEIST_AS_THE_LEADER"), 25, 1);
			STATS::STAT_SET_BOOL($("MP1_AWD_STORE_20_CAR_IN_GARAGES"), 1, 1);




			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_7"), -1, 1);





			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMRALLYWONDRIVE"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMRALLYWONNAV"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMWINSEARACE"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMWINAIRRACE"), 1, 1);
			STATS::STAT_SET_INT($("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
			STATS::STAT_SET_INT($("MP0_USJS_COMPLETED"), 50, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
			STATS::STAT_SET_INT($("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMRALLYWONDRIVE"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMRALLYWONNAV"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMWINSEARACE"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMWINAIRRACE"), 1, 1);
			STATS::STAT_SET_INT($("MP1_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
			STATS::STAT_SET_INT($("MP1_USJS_COMPLETED"), 50, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
			STATS::STAT_SET_INT($("MP1_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
			STATS::STAT_SET_FLOAT($("BADSPORT_RESET_MINUTES"), 1.0, true);
			STATS::STAT_SET_FLOAT($("MP0_BADSPORT_RESET_MINUTES"), 1.0, true);
			STATS::STAT_SET_FLOAT($("MP0_BADSPORT_RESET_MINUTES"), 1.0, true);
			STATS::STAT_SET_FLOAT($("MP0_BADSPORT_RESET_MINUTES"), 1.0, true);
			STATS::STAT_SET_FLOAT($("MP0_MPPLY_OVERALL_BADSPORT"), 0, true);
			STATS::STAT_SET_BOOL($("MP0_MPPLY_CHAR_IS_BADSPORT"), false, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, true);
			STATS::STAT_SET_INT($("MP0_BAD_SPORT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP0_CHEAT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_REPORT_STRENGTH"), 32, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_COMMEND_STRENGTH"), 100, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_FRIENDLY"), 100, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_HELPFUL"), 100, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_GRIEFING"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_LANGUAGE"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_UGC"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_VC_HATE"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_GAME_EXPLOITS"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_ISPUNISHED"), 0, true);
			STATS::STAT_SET_FLOAT($("MP0_MPPLY_OVERALL_BADSPORT"), 0, true);
			STATS::STAT_SET_BOOL($("MP0_MPPLY_CHAR_IS_BADSPORT"), false, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, true);
			STATS::STAT_SET_INT($("MP0_BAD_SPORT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP0_CHEAT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_REPORT_STRENGTH"), 32, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_COMMEND_STRENGTH"), 100, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_FRIENDLY"), 100, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_HELPFUL"), 100, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_GRIEFING"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_LANGUAGE"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_UGC"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_VC_HATE"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_GAME_EXPLOITS"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_ISPUNISHED"), 0, true);
			STATS::STAT_SET_FLOAT($("MP0_MPPLY_OVERALL_BADSPORT"), 0, true);
			STATS::STAT_SET_BOOL($("MP0_MPPLY_CHAR_IS_BADSPORT"), false, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, true);
			STATS::STAT_SET_INT($("MP0_BAD_SPORT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP0_CHEAT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_REPORT_STRENGTH"), 32, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_COMMEND_STRENGTH"), 100, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_FRIENDLY"), 100, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_HELPFUL"), 100, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_GRIEFING"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_LANGUAGE"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_UGC"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_VC_HATE"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_GAME_EXPLOITS"), 0, true);
			STATS::STAT_SET_INT($("MP0_MPPLY_ISPUNISHED"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_FLOAT($("BADSPORT_RESET_MINUTES"), 1.0, 1);
			STATS::STAT_SET_FLOAT($("MP0_BADSPORT_RESET_MINUTES"), 1.0, 1);
			STATS::STAT_SET_FLOAT($("MP0_BADSPORT_RESET_MINUTES"), 1.0, 1);
			STATS::STAT_SET_FLOAT($("MP0_BADSPORT_RESET_MINUTES"), 1.0, 1);
			STATS::STAT_SET_FLOAT($("MP0_MPPLY_OVERALL_BADSPORT"), 0, 1);
			STATS::STAT_SET_BOOL($("MP0_MPPLY_CHAR_IS_BADSPORT"), false, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BAD_SPORT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP0_CHEAT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_REPORT_STRENGTH"), 32, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_COMMEND_STRENGTH"), 100, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_FRIENDLY"), 100, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_HELPFUL"), 100, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_GRIEFING"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_UGC"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_VC_HATE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_GAME_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_ISPUNISHED"), 0, 1);
			STATS::STAT_SET_FLOAT($("MP0_MPPLY_OVERALL_BADSPORT"), 0, 1);
			STATS::STAT_SET_BOOL($("MP0_MPPLY_CHAR_IS_BADSPORT"), false, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BAD_SPORT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP0_CHEAT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_REPORT_STRENGTH"), 32, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_COMMEND_STRENGTH"), 100, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_FRIENDLY"), 100, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_HELPFUL"), 100, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_GRIEFING"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_UGC"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_VC_HATE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_GAME_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_ISPUNISHED"), 0, 1);
			STATS::STAT_SET_FLOAT($("MP0_MPPLY_OVERALL_BADSPORT"), 0, 1);
			STATS::STAT_SET_BOOL($("MP0_MPPLY_CHAR_IS_BADSPORT"), false, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, 1);
			STATS::STAT_SET_INT($("MP0_BAD_SPORT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP0_CHEAT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_REPORT_STRENGTH"), 32, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_COMMEND_STRENGTH"), 100, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_FRIENDLY"), 100, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_HELPFUL"), 100, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_GRIEFING"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_OFFENSIVE_UGC"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_VC_HATE"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_GAME_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT($("MP0_MPPLY_ISPUNISHED"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, true);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, true);
			STATS::STAT_SET_FLOAT($("BADSPORT_RESET_MINUTES"), 1.0, true);
			STATS::STAT_SET_FLOAT($("MP1_BADSPORT_RESET_MINUTES"), 1.0, true);
			STATS::STAT_SET_FLOAT($("MP1_BADSPORT_RESET_MINUTES"), 1.0, true);
			STATS::STAT_SET_FLOAT($("MP1_BADSPORT_RESET_MINUTES"), 1.0, true);
			STATS::STAT_SET_FLOAT($("MP1_MPPLY_OVERALL_BADSPORT"), 0, true);
			STATS::STAT_SET_BOOL($("MP1_MPPLY_CHAR_IS_BADSPORT"), false, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_BECAME_BADSPORT_NUM"), 0, true);
			STATS::STAT_SET_INT($("MP1_BAD_SPORT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP1_CHEAT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_REPORT_STRENGTH"), 32, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_COMMEND_STRENGTH"), 100, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_FRIENDLY"), 100, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_HELPFUL"), 100, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_GRIEFING"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_LANGUAGE"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_UGC"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_VC_HATE"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_GAME_EXPLOITS"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_ISPUNISHED"), 0, true);
			STATS::STAT_SET_FLOAT($("MP1_MPPLY_OVERALL_BADSPORT"), 0, true);
			STATS::STAT_SET_BOOL($("MP1_MPPLY_CHAR_IS_BADSPORT"), false, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_BECAME_BADSPORT_NUM"), 0, true);
			STATS::STAT_SET_INT($("MP1_BAD_SPORT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP1_CHEAT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_REPORT_STRENGTH"), 32, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_COMMEND_STRENGTH"), 100, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_FRIENDLY"), 100, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_HELPFUL"), 100, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_GRIEFING"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_LANGUAGE"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_UGC"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_VC_HATE"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_GAME_EXPLOITS"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_ISPUNISHED"), 0, true);
			STATS::STAT_SET_FLOAT($("MP1_MPPLY_OVERALL_BADSPORT"), 0, true);
			STATS::STAT_SET_BOOL($("MP1_MPPLY_CHAR_IS_BADSPORT"), false, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_BECAME_BADSPORT_NUM"), 0, true);
			STATS::STAT_SET_INT($("MP1_BAD_SPORT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP1_CHEAT_BITSET"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_REPORT_STRENGTH"), 32, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_COMMEND_STRENGTH"), 100, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_FRIENDLY"), 100, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_HELPFUL"), 100, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_GRIEFING"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_LANGUAGE"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_UGC"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_VC_HATE"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_GAME_EXPLOITS"), 0, true);
			STATS::STAT_SET_INT($("MP1_MPPLY_ISPUNISHED"), 0, true);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_1ST_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_2ND_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_3RD_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_4TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_5TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_6TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_7TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_8TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_9TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BADSPORT_NUMDAYS_10TH_OFFENCE"), 0, 1);
			STATS::STAT_SET_FLOAT($("BADSPORT_RESET_MINUTES"), 1.0, 1);
			STATS::STAT_SET_FLOAT($("MP1_BADSPORT_RESET_MINUTES"), 1.0, 1);
			STATS::STAT_SET_FLOAT($("MP1_BADSPORT_RESET_MINUTES"), 1.0, 1);
			STATS::STAT_SET_FLOAT($("MP1_BADSPORT_RESET_MINUTES"), 1.0, 1);
			STATS::STAT_SET_FLOAT($("MP1_MPPLY_OVERALL_BADSPORT"), 0, 1);
			STATS::STAT_SET_BOOL($("MP1_MPPLY_CHAR_IS_BADSPORT"), false, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_BECAME_BADSPORT_NUM"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BAD_SPORT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP1_CHEAT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_REPORT_STRENGTH"), 32, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_COMMEND_STRENGTH"), 100, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_FRIENDLY"), 100, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_HELPFUL"), 100, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_GRIEFING"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_UGC"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_VC_HATE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_GAME_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_ISPUNISHED"), 0, 1);
			STATS::STAT_SET_FLOAT($("MP1_MPPLY_OVERALL_BADSPORT"), 0, 1);
			STATS::STAT_SET_BOOL($("MP1_MPPLY_CHAR_IS_BADSPORT"), false, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_BECAME_BADSPORT_NUM"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BAD_SPORT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP1_CHEAT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_REPORT_STRENGTH"), 32, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_COMMEND_STRENGTH"), 100, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_FRIENDLY"), 100, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_HELPFUL"), 100, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_GRIEFING"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_UGC"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_VC_HATE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_GAME_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_ISPUNISHED"), 0, 1);
			STATS::STAT_SET_FLOAT($("MP1_MPPLY_OVERALL_BADSPORT"), 0, 1);
			STATS::STAT_SET_BOOL($("MP1_MPPLY_CHAR_IS_BADSPORT"), false, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_BECAME_BADSPORT_NUM"), 0, 1);
			STATS::STAT_SET_INT($("MP1_BAD_SPORT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP1_CHEAT_BITSET"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_REPORT_STRENGTH"), 32, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_COMMEND_STRENGTH"), 100, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_FRIENDLY"), 100, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_HELPFUL"), 100, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_GRIEFING"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_LANGUAGE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_OFFENSIVE_UGC"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_VC_HATE"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_GAME_EXPLOITS"), 0, 1);
			STATS::STAT_SET_INT($("MP1_MPPLY_ISPUNISHED"), 0, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 99999999, 0);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_BOURGE_BOUGHT"), 99999999, 0);
			STATS::STAT_SET_INT($("LIFETIME_BIKER_BUY_COMPLET"), 1200, 1);
			STATS::STAT_SET_INT($("LIFETIME_BIKER_BUY_COMPLET"), 1200, 1);
			STATS::STAT_SET_INT($("LIFETIME_BIKER_BUY_UNDERTA"), 1200, 1);
			STATS::STAT_SET_INT($("LIFETIME_BIKER_SELL_COMPLET"), 1200, 1);
			STATS::STAT_SET_INT($("LIFETIME_BIKER_SELL_UNDERTA"), 1200, 1);
			STATS::STAT_SET_INT($("LIFETIME_BKR_SELL_EARNINGS0"), 1200, 1);
			STATS::STAT_SET_INT($("MP0_LIFETIME_BUY_COMPLETE"), 1223, 0);
			STATS::STAT_SET_INT($("MP0_LIFETIME_BUY_UNDERTAKEN"), 1223, 0);
			STATS::STAT_SET_INT($("MP0_LIFETIME_SELL_COMPLETE"), 434, 0);
			STATS::STAT_SET_INT($("MP0_LIFETIME_SELL_UNDERTAKEN"), 434, 0);
			STATS::STAT_SET_INT($("MP0_LIFETIME_CONTRA_EARNINGS"), 1220000000, 0);
			STATS::STAT_SET_INT($("MP1_LIFETIME_BUY_COMPLETE"), 1223, 0);
			STATS::STAT_SET_INT($("MP1_LIFETIME_BUY_UNDERTAKEN"), 1223, 0);
			STATS::STAT_SET_INT($("MP1_LIFETIME_SELL_COMPLETE"), 434, 0);
			STATS::STAT_SET_INT($("MP1_LIFETIME_SELL_UNDERTAKEN"), 434, 0);
			STATS::STAT_SET_INT($("MP1_LIFETIME_CONTRA_EARNINGS"), 1220000000, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_STL"), 100, 0);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_12"), -1, 1);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
			STATS::STAT_SET_INT($("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_USJS_COMPLETED"), 50, 0);
			STATS::STAT_SET_INT($("MP0_USJS_FOUND"), 50, 0);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMWINALLRACEMODES"), 1, 0);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 0);
			STATS::STAT_SET_INT($("MP0_DB_PLAYER_KILLS"), 1000, 0);
			STATS::STAT_SET_INT($("MP0_KILLS_PLAYERS"), 1000, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
			STATS::STAT_SET_INT($("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_TDM_MVP"), 60, 0);
			STATS::STAT_SET_INT($("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
			STATS::STAT_SET_INT($("MP0_AWD_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT($("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMATTGANGHQ"), 1, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FMBBETWIN"), 50000, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_DM_WINS"), 51, 0);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMFULLYMODDEDCAR"), 1, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
			STATS::STAT_SET_INT($("MP0_PLAYER_HEADSHOTS"), 623, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_DM_WINS"), 63, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_TDM_WINS"), 13, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_GOLF_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_TENNIS_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
			STATS::STAT_SET_INT($("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
			STATS::STAT_SET_INT($("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
			STATS::STAT_SET_INT($("MP0_GRENADE_ENEMY_KILLS"), 50, 0);
			STATS::STAT_SET_INT($("MP0_AWD_20_KILLS_MELEE"), 50, 0);
			STATS::STAT_SET_INT($("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_PISTOL50_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_SMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_MG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ASLTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_PUMP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_SAWNOFF_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_BULLPUP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_RPG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_GRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_STKYBMB_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_31"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_STL"), 100, 0);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_12"), -1, 1);
			STATS::STAT_SET_BOOL($("MP1_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
			STATS::STAT_SET_INT($("MP1_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_USJS_COMPLETED"), 50, 0);
			STATS::STAT_SET_INT($("MP1_USJS_FOUND"), 50, 0);
			STATS::STAT_SET_BOOL($("MP1_AWD_FMWINALLRACEMODES"), 1, 0);
			STATS::STAT_SET_BOOL($("MP1_AWD_FMWINEVERYGAMEMODE"), 1, 0);
			STATS::STAT_SET_INT($("MP1_DB_PLAYER_KILLS"), 1000, 0);
			STATS::STAT_SET_INT($("MP1_KILLS_PLAYERS"), 1000, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FMHORDWAVESSURVIVE"), 21, 0);
			STATS::STAT_SET_INT($("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_TDM_MVP"), 60, 0);
			STATS::STAT_SET_INT($("MP1_AWD_HOLD_UP_SHOPS"), 20, 0);
			STATS::STAT_SET_INT($("MP1_AWD_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT($("MP1_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
			STATS::STAT_SET_BOOL($("MP1_AWD_FMATTGANGHQ"), 1, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FMBBETWIN"), 50000, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_DM_WINS"), 51, 0);
			STATS::STAT_SET_BOOL($("MP1_AWD_FMFULLYMODDEDCAR"), 1, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_DM_TOTALKILLS"), 500, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
			STATS::STAT_SET_INT($("MP1_PLAYER_HEADSHOTS"), 623, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_DM_WINS"), 63, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_TDM_WINS"), 13, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_GTA_RACES_WON"), 12, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_GOLF_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_TENNIS_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TOTAL_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TOTAL_RACES_LOST"), 36, 0);
			STATS::STAT_SET_INT($("MP1_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
			STATS::STAT_SET_INT($("MP1_AWD_50_KILLS_GRENADES"), 50, 0);
			STATS::STAT_SET_INT($("MP1_GRENADE_ENEMY_KILLS"), 50, 0);
			STATS::STAT_SET_INT($("MP1_AWD_20_KILLS_MELEE"), 50, 0);
			STATS::STAT_SET_INT($("MP1_MOLOTOV_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_PISTOL50_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_APPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_MICROSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_SMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ASLTSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ADVRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_MG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_CMBTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ASLTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_PUMP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_SAWNOFF_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_BULLPUP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_SNIPERRFL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_HVYSNIPER_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_RPG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_MINIGUNS_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_GRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_SMKGRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_STKYBMB_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_MOLOTOV_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_TORSO"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_DECL"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_TEETH"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_TORSO"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_DECL"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_TEETH"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_0"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_12"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_13"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_14"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_15"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_16"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_17"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_18"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_19"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_21"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_22"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_23"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_25"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_26"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_27"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_28"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_29"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_30"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_31"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_32"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_33"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_34"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_35"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_36"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_37"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_38"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_39"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_40"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			AUDIO::PLAY_SOUND_FRONTEND(-1, "MP_AWARD", "HUD_FRONTEND_DEFAULT_SOUNDSET", 1);




			STATS::STAT_SET_FLOAT($("MPPLY_OVERALL_BADSPORT"), 0.0f, TRUE);
			STATS::STAT_SET_INT($("MPPLY_DESTROYED_PVEHICLES"), 0, TRUE);
			STATS::STAT_SET_INT($("MPPLY_BADSPORT_MESSAGE"), 0, TRUE);




			STATS::STAT_SET_INT($("MP0_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_CIGARETTES_BOUGHT"), 2000000000, 1);




			STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);




			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_1_RED"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_2_RED"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_3_RED"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_4_RED"), 2000000000, 1);
			STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);


			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
			STATS::STAT_SET_INT($("MP0_SCRIPT_INCREASE_STL"), 100, 0);
			STATS::STAT_SET_INT($("MP0_script_increase_stam"), 100, 1);
			STATS::STAT_SET_INT($("MP0_script_increase_strn"), 100, 1);
			STATS::STAT_SET_INT($("MP0_script_increase_lung"), 100, 1);
			STATS::STAT_SET_INT($("MP0_script_increase_driv"), 100, 1);
			STATS::STAT_SET_INT($("MP0_script_increase_fly"), 100, 1);
			STATS::STAT_SET_INT($("MP0_script_increase_sho"), 100, 1);
			STATS::STAT_SET_INT($("MP0_script_increase_stl"), 100, 1);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
			STATS::STAT_SET_INT($("MP1_SCRIPT_INCREASE_STL"), 100, 0);
			STATS::STAT_SET_INT($("MP1_script_increase_stam"), 100, 1);
			STATS::STAT_SET_INT($("MP1_script_increase_strn"), 100, 1);
			STATS::STAT_SET_INT($("MP1_script_increase_lung"), 100, 1);
			STATS::STAT_SET_INT($("MP1_script_increase_driv"), 100, 1);
			STATS::STAT_SET_INT($("MP1_script_increase_fly"), 100, 1);
			STATS::STAT_SET_INT($("MP1_script_increase_sho"), 100, 1);
			STATS::STAT_SET_INT($("MP1_script_increase_stl"), 100, 1);



			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_tattoo_fm_unlocks_12"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_tattoo_fm_unlocks_12"), -1, 1);


			STATS::STAT_SET_INT($("MP0_MOLOTOV _ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_PISTOL50_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_SMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_MG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ASLTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_PUMP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_SAWNOFF_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_BULLPUP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_RPG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_GRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_STKYBMB_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_MOLOTOV _ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_PISTOL50_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_APPISTOL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_MICROSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_SMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ASLTSMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ADVRIFLE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_MG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_CMBTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ASLTMG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_PUMP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_SAWNOFF_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_BULLPUP_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_SNIPERRFL_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_HVYSNIPER_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_RPG_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_MINIGUNS_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_GRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_SMKGRENADE_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_STKYBMB_ENEMY_KILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_MOLOTOV_ENEMY_KILLS"), 600, 0);




			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_31"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 1);
			STATS::STAT_SET_INT($("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_FEET_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_BERD_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_FEET_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_BERD_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_TORSO"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_DECL"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_TEETH"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_TORSO"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_DECL"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_TEETH"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_0"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_12"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_13"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_14"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_15"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_16"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_17"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_18"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_19"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_21"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_22"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_23"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_24"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_25"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_26"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_27"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_28"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_29"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_30"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_31"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_32"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_33"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_34"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_35"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_36"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_37"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_38"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_39"), -1, 1);
			STATS::STAT_SET_INT($("MP1_DLC_APPAREL_ACQUIRED_40"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
			AUDIO::PLAY_SOUND_FRONTEND(-1, "MP_AWARD", "HUD_FRONTEND_DEFAULT_SOUNDSET", 1);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
			STATS::STAT_SET_INT($("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP0_USJS_COMPLETED"), 50, 0);
			STATS::STAT_SET_INT($("MP0_USJS_FOUND"), 50, 0);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMWINALLRACEMODES"), 1, 0);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 0);
			STATS::STAT_SET_INT($("MP0_DB_PLAYER_KILLS"), 1000, 0);
			STATS::STAT_SET_INT($("MP0_KILLS_PLAYERS"), 1000, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
			STATS::STAT_SET_INT($("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_TDM_MVP"), 60, 0);
			STATS::STAT_SET_INT($("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
			STATS::STAT_SET_INT($("MP0_AWD_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT($("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMATTGANGHQ"), 1, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FMBBETWIN"), 50000, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_DM_WINS"), 51, 0);
			STATS::STAT_SET_BOOL($("MP0_AWD_FMFULLYMODDEDCAR"), 1, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
			STATS::STAT_SET_INT($("MP0_PLAYER_HEADSHOTS"), 623, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_DM_WINS"), 63, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_TDM_WINS"), 13, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_GOLF_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_AWD_FM_TENNIS_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
			STATS::STAT_SET_INT($("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
			STATS::STAT_SET_INT($("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
			STATS::STAT_SET_INT($("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
			STATS::STAT_SET_INT($("MP0_GRENADE_ENEMY_KILLS "), 50, 0);
			STATS::STAT_SET_INT($("MP0_AWD_20_KILLS_MELEE"), 50, 0);

			STATS::STAT_SET_BOOL($("MP1_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
			STATS::STAT_SET_INT($("MP1_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
			STATS::STAT_SET_INT($("MP1_USJS_COMPLETED"), 50, 0);
			STATS::STAT_SET_INT($("MP1_USJS_FOUND"), 50, 0);
			STATS::STAT_SET_BOOL($("MP1_AWD_FMWINALLRACEMODES"), 1, 0);
			STATS::STAT_SET_BOOL($("MP1_AWD_FMWINEVERYGAMEMODE"), 1, 0);
			STATS::STAT_SET_INT($("MP1_DB_PLAYER_KILLS"), 1000, 0);
			STATS::STAT_SET_INT($("MP1_KILLS_PLAYERS"), 1000, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FMHORDWAVESSURVIVE"), 21, 0);
			STATS::STAT_SET_INT($("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_TDM_MVP"), 60, 0);
			STATS::STAT_SET_INT($("MP1_AWD_HOLD_UP_SHOPS"), 20, 0);
			STATS::STAT_SET_INT($("MP1_AWD_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT($("MP1_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
			STATS::STAT_SET_BOOL($("MP1_AWD_FMATTGANGHQ"), 1, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FMBBETWIN"), 50000, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_DM_WINS"), 51, 0);
			STATS::STAT_SET_BOOL($("MP1_AWD_FMFULLYMODDEDCAR"), 1, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_DM_TOTALKILLS"), 500, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
			STATS::STAT_SET_INT($("MP1_PLAYER_HEADSHOTS"), 623, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_DM_WINS"), 63, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_TDM_WINS"), 13, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_GTA_RACES_WON"), 12, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_GOLF_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_AWD_FM_TENNIS_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TOTAL_RACES_WON"), 101, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
			STATS::STAT_SET_INT($("MP1_MPPLY_TOTAL_RACES_LOST"), 36, 0);
			STATS::STAT_SET_INT($("MP1_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
			STATS::STAT_SET_INT($("MP1_AWD_50_KILLS_GRENADES"), 50, 0);
			STATS::STAT_SET_INT($("MP1_GRENADE_ENEMY_KILLS "), 50, 0);
			STATS::STAT_SET_INT($("MP1_AWD_20_KILLS_MELEE"), 50, 0);
			AUDIO::PLAY_SOUND_FRONTEND(-1, "MP_AWARD", "HUD_FRONTEND_DEFAULT_SOUNDSET", 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);
			AUDIO::PLAY_SOUND_FRONTEND(-1, "MP_AWARD", "HUD_FRONTEND_DEFAULT_SOUNDSET", 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_1_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_2_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_3_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_4_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_5_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_6_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_7_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_8_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_9_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_10_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_11_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_12_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE7"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE8"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE9"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE10"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE11"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_KIT_FM_PURCHASE12"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_1_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_2_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_3_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_4_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_5_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_6_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_7_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_8_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_9_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_10_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_11_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_12_FM_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE8"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE9"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE10"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE11"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_KIT_FM_PURCHASE12"), -1, 1);





			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_RACES_WON"), 50, 1);

			Hash Stats50[] = { 0xcfe6e176, 0x2f5bf8f, 0xe4c4cc91, 0x95546c90, 0xaa71df87, 0xD9C9649, 0x2037F997, 0x5550EA43, 0xB957BDE2, 0x512FC8F4 };
			for (Hash h : Stats50)
				STATS::STAT_SET_INT(h, 50, 1);


			Hash Stats100[] = { 0x624901df, 0xbc4421b6, 0x3c9d6f53, 0x47AE528D, 0x2A8544EF, 0x77D6EA19 };
			for (Hash h : Stats100)
				STATS::STAT_SET_INT(h, 100, 1);

			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_CAPTURES"), 25, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_DROPOFF_CAP_PACKAGES"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_KILL_CARRIER_CAPTURE"), 100, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEISTS"), 50, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_SETUP_JOB"), 50, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_NIGHTVISION_KILLS, 100"), 1, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50, 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, 1);



			STATS::STAT_SET_INT($("MP0_AWD_FMHORDWAVESSURVIVE"), 10, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMPICKUPDLCCRATE1ST"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_WIN_CAPTURE_DONT_DYING"), 25, 1);
			STATS::STAT_SET_INT($("MP0_AWD_DO_HEIST_AS_MEMBER"), 25, 1);
			STATS::STAT_SET_INT($("MP0_AWD_PICKUP_CAP_PACKAGES"), 100, 1);
			STATS::STAT_SET_BOOL($("MP0_AWD_FINISH_HEIST_NO_DAMAGE"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_WIN_GOLD_MEDAL_HEISTS"), 25, 1);
			STATS::STAT_SET_INT($("MP0_AWD_KILL_TEAM_YOURSELF_LTS"), 25, 1);
			STATS::STAT_SET_INT($("MP0_AWD_KILL_PSYCHOPATHS"), 100, 1);
			STATS::STAT_SET_INT($("MP0_AWD_DO_HEIST_AS_THE_LEADER"), 25, 1);
			STATS::STAT_SET_BOOL($("MP0_AWD_STORE_20_CAR_IN_GARAGES"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMHORDWAVESSURVIVE"), 10, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMPICKUPDLCCRATE1ST"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_WIN_CAPTURE_DONT_DYING"), 25, 1);
			STATS::STAT_SET_INT($("MP1_AWD_DO_HEIST_AS_MEMBER"), 25, 1);
			STATS::STAT_SET_INT($("MP1_AWD_PICKUP_CAP_PACKAGES"), 100, 1);
			STATS::STAT_SET_BOOL($("MP1_AWD_FINISH_HEIST_NO_DAMAGE"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_WIN_GOLD_MEDAL_HEISTS"), 25, 1);
			STATS::STAT_SET_INT($("MP1_AWD_KILL_TEAM_YOURSELF_LTS"), 25, 1);
			STATS::STAT_SET_INT($("MP1_AWD_KILL_PSYCHOPATHS"), 100, 1);
			STATS::STAT_SET_INT($("MP1_AWD_DO_HEIST_AS_THE_LEADER"), 25, 1);
			STATS::STAT_SET_BOOL($("MP1_AWD_STORE_20_CAR_IN_GARAGES"), 1, 1);
			AUDIO::PLAY_SOUND_FRONTEND(-1, "MP_AWARD", "HUD_FRONTEND_DEFAULT_SOUNDSET", 1);

			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMRALLYWONDRIVE"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMRALLYWONNAV"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMWINSEARACE"), 1, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FMWINAIRRACE"), 1, 1);
			STATS::STAT_SET_INT($("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
			STATS::STAT_SET_INT($("MP0_USJS_COMPLETED"), 50, 1);
			STATS::STAT_SET_INT($("MP0_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
			STATS::STAT_SET_INT($("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_3_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_4_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_5_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_6_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_CARMOD_7_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMRALLYWONDRIVE"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMRALLYWONNAV"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMWINSEARACE"), 1, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FMWINAIRRACE"), 1, 1);
			STATS::STAT_SET_INT($("MP1_NUMBER_TURBO_STARTS_IN_RACE"), 50, 1);
			STATS::STAT_SET_INT($("MP1_USJS_COMPLETED"), 50, 1);
			STATS::STAT_SET_INT($("MP1_AWD_FM_RACES_FASTEST_LAP"), 50, 1);
			STATS::STAT_SET_INT($("MP1_NUMBER_SLIPSTREAMS_IN_RACE"), 100, 1);


			STATS::STAT_SET_INT($("MP0_FM_CHANGECHAR_ASKED"), 0, 1);
			STATS::STAT_SET_INT($("MP1_FM_CHANGECHAR_ASKED"), 0, 1);


			STATS::STAT_SET_INT($("MP0_NO_MORE_TUTORIALS"), 1, 1);
			STATS::STAT_SET_INT($("MP1_NO_MORE_TUTORIALS"), 1, 1);




			STATS::STAT_SET_INT($("MPPLY_HEIST_ACH_TRACKER"), -1, 1);
			STATS::STAT_SET_INT($("MPPLY_HEIST_ACH_TRACKER"), -1, 1);



			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
			AUDIO::PLAY_SOUND_FRONTEND(-1, "MP_AWARD", "HUD_FRONTEND_DEFAULT_SOUNDSET", 1);





			STATS::STAT_SET_INT($("MPPLY_VEHICLE_ID_ADMIN_WEB"), 117401876, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_WEAPON_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_WEAPON_GV_BS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_ADMIN_WEAPON_GV_BS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_BOTTLE_IN_POSSESSION"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_WEAP_UNLOCKED"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_WEAP_UNLOCKED2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_WEAP_FM_PURCHASE"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_WEAP_FM_PURCHASE2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_WEAP_ADDON_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_WEAP_ADDON_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_WEAP_ADDON_3_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_WEAP_ADDON_4_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_CHAR_FM_WEAP_ADDON_5_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP0_WEAP_FM_ADDON_PURCH"), -1, 1);
			STATS::STAT_SET_INT($("MP0_WEAP_FM_ADDON_PURCH2"), -1, 1);
			STATS::STAT_SET_INT($("MP0_WEAP_FM_ADDON_PURCH3"), -1, 1);
			STATS::STAT_SET_INT($("MP0_WEAP_FM_ADDON_PURCH4"), -1, 1);
			STATS::STAT_SET_INT($("MP0_WEAP_FM_ADDON_PURCH5"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_WEAPON_GV_BS_1"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_WEAPON_GV_BS_2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_ADMIN_WEAPON_GV_BS_3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_BOTTLE_IN_POSSESSION"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_WEAP_UNLOCKED"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_WEAP_UNLOCKED2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_WEAP_FM_PURCHASE"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_WEAP_FM_PURCHASE2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_WEAP_ADDON_1_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_WEAP_ADDON_2_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_WEAP_ADDON_3_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_WEAP_ADDON_4_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_CHAR_FM_WEAP_ADDON_5_UNLCK"), -1, 1);
			STATS::STAT_SET_INT($("MP1_WEAP_FM_ADDON_PURCH"), -1, 1);
			STATS::STAT_SET_INT($("MP1_WEAP_FM_ADDON_PURCH2"), -1, 1);
			STATS::STAT_SET_INT($("MP1_WEAP_FM_ADDON_PURCH3"), -1, 1);
			STATS::STAT_SET_INT($("MP1_WEAP_FM_ADDON_PURCH4"), -1, 1);
			STATS::STAT_SET_INT($("MP1_WEAP_FM_ADDON_PURCH5"), -1, 1);

			ScriptEventLog("~g~Unlock All finished!");

			unlockall = false;
		}



		if (randomoutfit)
		{
			Features::randomoutfit();

			randomoutfit = false;
		}

		if (skipcut)
		{
			CUTSCENE::STOP_CUTSCENE;
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();

			skipcut = false;
		}

		if (cloneped)
		{
			PED::CLONE_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1, 1, 1);

			cloneped = false;
		}

		if (shootkill)
		{
			Vector3 old_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), TRUE);
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(TRUE, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
			Vector3 ped_head_coords = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0x796e, 0, 0, 0);
			Vector3 ped_skel_coords = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0xe0fd, 0, 0, 0);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), ped_skel_coords.x, ped_skel_coords.y, ped_skel_coords.z + 10, 0, 0, 1);
			for (int i = 0; i <= 50; i++)
			{
				Hash weaponhash;
				WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(ped_skel_coords.x, ped_skel_coords.y, ped_skel_coords.z, ped_head_coords.x, ped_head_coords.y, ped_head_coords.z, 50, 1, GAMEPLAY::GET_HASH_KEY("weapon_microsmg"), 0, 1, 1, 0xbf800000);
			}
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(FALSE, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), old_coords.x, old_coords.y, old_coords.z, 0, 0, 1);

			shootkill = false;
		}

		if (normalkill)
		{
			Ped selectdenfick = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectdenfick, 1);

			g_GameVariables->OwnedExplosionBypass(true);
			FIRE::ADD_OWNED_EXPLOSION(selectdenfick, pos, 29, 999.0f, 0, false, 0.f);
			g_GameVariables->OwnedExplosionBypass(false);


			//OwnedExplosion(selectdenfick, pos.x, pos.y, pos.z, 29, 999.f, false, false, 0.f);

			normalkill = false;
		}

		if (cageplayer)
		{
			Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
			Object obj;
			OBJECT::CREATE_OBJECT($("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1, true, 1, -1, &obj, true, false, false);

			cageplayer = false;
		}



		if (kickoutcar)
		{
			Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			RequestControlOfEnt(playerPed);
			AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
			AI::CLEAR_PED_TASKS(playerPed);
			AI::CLEAR_PED_SECONDARY_TASK(playerPed);
			kickoutcar = false;
		}


		if (cageallplayer)
		{
			for (int i123 = 0; i123 <= 32; i123++) {
				if (PLAYER::PLAYER_ID() != i123) {

					Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i123), 0);
					Object obj;
					OBJECT::CREATE_OBJECT($("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1, true, 1, -1, &obj, true, false, false);
				}
			}
			cageallplayer = false;
		}

		if (setalpha)
		{
			ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), Features::alpha, false);

			setalpha = false;
		}

		if (ramplayer)
		{
			Features::RamPlayer();
			ramplayer = false;
		}

		if (airstrike)
		{
			Features::AirStrikeKill();
			airstrike = false;
		}

		if (tpintoveh)
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
			for (int i = -1; i < 32; i++)
			{
				if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i))
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, i);
				}
			}

			tpintoveh = false;
		}

		if (tptoplayer)
		{
			Entity handle;
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
			PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
			ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);

			tptoplayer = false;
		}

		if (crash1)
		{

			Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			STREAMING::REQUEST_MODEL(0x2D7030F3);
			while (!STREAMING::HAS_MODEL_LOADED(0x2D7030F3)) SYSTEM::WAIT(0);
			Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
			STREAMING::REQUEST_MENU_PED_MODEL(0x856cfb02);
			*(PUINT16)g_GameFunctions->m_model_spawn_bypass = 0x9090;
			PED::CREATE_PED(1, 0x856cfb02, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
			*(PUINT16)g_GameFunctions->m_model_spawn_bypass = 0x0574;

			crash1 = false;
		}

		if (setlevelinstant)
		{
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), Features::Levels[(instant - 1)], 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_XP_FM"), Features::Levels[(instant - 1)], 1);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP2_CHAR_XP_FM"), Features::Levels[(instant - 1)], 1);

			setlevelinstant = false;
		}

		if (correctlevel)
		{

			Features::SetRank(instant);

			correctlevel = false;
		}

		if (deleteveh)
		{
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(playerVeh);
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(playerVeh))
				{
					if (ENTITY::DOES_ENTITY_EXIST(playerVeh))
					{
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(playerVeh, 1, 1);
						VEHICLE::DELETE_VEHICLE(&playerVeh);
					}
				}
			}
			deleteveh = false;
		}

		if (SetNumberPlateTXT)
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			RequestControlOfEnt(veh);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, numberplatetxt);

			SetNumberPlateTXT = false;
		}

		if (kickplayerxd)
		{
			DWORD64 args1[4] = { KICK_1, g_SelectedPlayer };
			Hooks::TriggerScriptEvent(1, args1, 4, 1 << g_SelectedPlayer);


			DWORD64 args2[3] = { KICK_2, g_SelectedPlayer };
			Hooks::TriggerScriptEvent(1, args2, 3, 1 << g_SelectedPlayer);


			DWORD64 args3[4] = { KICK_3, g_SelectedPlayer };
			Hooks::TriggerScriptEvent(1, args3, 4, 1 << g_SelectedPlayer);


			DWORD64 args4[5] = { KICK_4, g_SelectedPlayer, 0, 111 };
			Hooks::TriggerScriptEvent(1, args4, 5, 1 << g_SelectedPlayer);

			DWORD64 args5[3] = { KICK_5, g_SelectedPlayer };
			Hooks::TriggerScriptEvent(1, args5, 3, 1 << g_SelectedPlayer);


			DWORD64 args6[4] = { KICK_6, g_SelectedPlayer, 50 };
			Hooks::TriggerScriptEvent(1, args6, 4, 1 << g_SelectedPlayer);


			DWORD64 args7[4] = { KICK_7, g_SelectedPlayer, 20, 1 };
			Hooks::TriggerScriptEvent(1, args7, 4, 1 << g_SelectedPlayer);


			DWORD64 args8[4] = { KICK_8, g_SelectedPlayer, 20 };
			Hooks::TriggerScriptEvent(1, args8, 4, 1 << g_SelectedPlayer);


			DWORD64 args9[4] = { KICK_9, g_SelectedPlayer, 20, 1 };
			Hooks::TriggerScriptEvent(1, args9, 4, 1 << g_SelectedPlayer);


			DWORD64 args10[4] = { KICK_10, g_SelectedPlayer, 20 };
			Hooks::TriggerScriptEvent(1, args10, 4, 1 << g_SelectedPlayer);


			DWORD64 args11[4] = { KICK_11, g_SelectedPlayer, 20 };
			Hooks::TriggerScriptEvent(1, args11, 4, 1 << g_SelectedPlayer);


			DWORD64 args12[6] = { KICK_12, g_SelectedPlayer, 0, 0, 0, 36 };
			Hooks::TriggerScriptEvent(1, args12, 6, 1 << g_SelectedPlayer);


			DWORD64 args13[3] = { KICK_13, g_SelectedPlayer, 36 };
			Hooks::TriggerScriptEvent(1, args13, 3, 1 << g_SelectedPlayer);


			DWORD64 asd[3] = { KICK_14, g_SelectedPlayer, -4294967260/*36*/ };
			Hooks::TriggerScriptEvent(1, asd, 3, 1 << g_SelectedPlayer);

			DWORD64 adasdasd[4] = { KICK_15, g_SelectedPlayer, 32 };
			Hooks::TriggerScriptEvent(1, adasdasd, 4, 1 << g_SelectedPlayer);


			DWORD64 sadfas[5] = { KICK_16, g_SelectedPlayer, 0, 0, 32 };
			Hooks::TriggerScriptEvent(1, sadfas, 5, 1 << g_SelectedPlayer);


			DWORD64 asasdads[5] = { KICK_17, g_SelectedPlayer, 0, 0, 32 };
			Hooks::TriggerScriptEvent(1, asasdads, 5, 1 << g_SelectedPlayer);


			DWORD64 dffgdfgd[5] = { KICK_18, g_SelectedPlayer, 4 };
			Hooks::TriggerScriptEvent(1, dffgdfgd, 5, 1 << g_SelectedPlayer);


			DWORD64 fdfgdhfgh[5] = { KICK_19, g_SelectedPlayer, 7 };
			Hooks::TriggerScriptEvent(1, fdfgdhfgh, 5, 1 << g_SelectedPlayer);


			DWORD64 fddfgfdg[6] = { KICK_20, g_SelectedPlayer, 0, 59 };
			Hooks::TriggerScriptEvent(1, fddfgfdg, 6, 1 << g_SelectedPlayer);

			DWORD64 arfghhfgffgs[5] = { KICK_21, g_SelectedPlayer, 0, 59 };
			Hooks::TriggerScriptEvent(1, arfghhfgffgs, 5, 1 << g_SelectedPlayer);

			DWORD64 asdasdasd[4] = { KICK_22, g_SelectedPlayer, 0, 59 };
			Hooks::TriggerScriptEvent(1, asdasdasd, 4, 1 << g_SelectedPlayer);


			DWORD64 tzhjtzhhjtgghjgjh[4] = { KICK_23, g_SelectedPlayer, 62 };
			Hooks::TriggerScriptEvent(1, tzhjtzhhjtgghjgjh, 4, 1 << g_SelectedPlayer);


			DWORD64 qwqweqweqwe[4] = { KICK_24, g_SelectedPlayer, 0, 26 };
			Hooks::TriggerScriptEvent(1, qwqweqweqwe, 4, 1 << g_SelectedPlayer);


			DWORD64 sijhdgfbsduhfsbvdhgfsdf[5] = { KICK_25, g_SelectedPlayer, 0, 26 };
			Hooks::TriggerScriptEvent(1, sijhdgfbsduhfsbvdhgfsdf, 5, 1 << g_SelectedPlayer);


			DWORD64 hjgkhjkhjk[4] = { KICK_26, g_SelectedPlayer, 0, 26 };
			Hooks::TriggerScriptEvent(1, hjgkhjkhjk, 4, 1 << g_SelectedPlayer);


			DWORD64 jkljkljkl[3] = { KICK_27, g_SelectedPlayer, 3 };
			Hooks::TriggerScriptEvent(1, jkljkljkl, 3, 1 << g_SelectedPlayer);


			DWORD64 qwqwweqqwe[24] = { KICK_28, g_SelectedPlayer, 180 };
			Hooks::TriggerScriptEvent(1, qwqwweqqwe, 24, 1 << g_SelectedPlayer);


			DWORD64 zuizuizuizu[5] = { KICK_29, g_SelectedPlayer, 64 };
			Hooks::TriggerScriptEvent(1, zuizuizuizu, 5, 1 << g_SelectedPlayer);


			DWORD64 qweqweqwe[3] = { KICK_30, g_SelectedPlayer, 32 };
			Hooks::TriggerScriptEvent(1, qweqweqwe, 3, 1 << g_SelectedPlayer);


			DWORD64 uhijewhizuwerhb[4] = { KICK_31, g_SelectedPlayer, 62 };
			Hooks::TriggerScriptEvent(1, uhijewhizuwerhb, 4, 1 << g_SelectedPlayer);


			DWORD64 asdasdasdasdasd[18] = { KICK_32, g_SelectedPlayer };
			Hooks::TriggerScriptEvent(1, asdasdasdasdasd, 18, 1 << g_SelectedPlayer);

			DWORD64 asdasdasdasf[3] = { KICK_33, g_SelectedPlayer };
			Hooks::TriggerScriptEvent(1, asdasdasdasf, 3, 1 << g_SelectedPlayer);


			DWORD64 djkfgndejgnkd[13] = { KICK_34, g_SelectedPlayer, 123 }; //fix
			Hooks::TriggerScriptEvent(1, djkfgndejgnkd, 13, 1 << g_SelectedPlayer);


			DWORD64 asdasdfgddfgdfg[4] = { KICK_35, g_SelectedPlayer };
			Hooks::TriggerScriptEvent(1, asdasdfgddfgdfg, 4, 1 << g_SelectedPlayer);


			DWORD64 dfgdfgdfg[21];
			*dfgdfgdfg = KICK_36;
			dfgdfgdfg[1] = g_SelectedPlayer;
			dfgdfgdfg[19] = 125;
			Hooks::TriggerScriptEvent(1, dfgdfgdfg, 21, 1 << g_SelectedPlayer);

			DWORD64 sdfsdfsdfsdf[4] = { KICK_37, g_SelectedPlayer, 1, 124 };//need check false alarm
			Hooks::TriggerScriptEvent(1, sdfsdfsdfsdf, 4, 1 << g_SelectedPlayer);


			DWORD64 hjzhjkzhjkzhjkhjkhjk[10] = { KICK_38, g_SelectedPlayer, 1, 10000, 32/*n0*/, 0, 1, 46, 1, 40 };
			Hooks::TriggerScriptEvent(1, hjzhjkzhjkzhjkhjkhjk, 10, 1 << g_SelectedPlayer);


			DWORD64 ghfgfhfghfghfgh[10] = { KICK_39, g_SelectedPlayer, 1, 10000, 32, 0, 1, 36, 1, 40 };
			Hooks::TriggerScriptEvent(1, ghfgfhfghfghfgh, 10, 1 << g_SelectedPlayer);


			DWORD64 dfghfgfghhfghfg[25];
			*dfghfgfghhfghfg = KICK_40, dfghfgfghhfghfg[1] = g_SelectedPlayer, dfghfgfghhfghfg[2] = 180;
			Hooks::TriggerScriptEvent(1, dfghfgfghhfghfg, 25, 1 << g_SelectedPlayer);
			kickplayerxd = false;
		}






		if (Features::UpdateInfo)
		{
			if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer))
			{
				char ipBuf[32] = {};

				static auto nigNog = (std::uintptr_t(*)(int))(Memory::pattern("40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C").count(1).get(0).get<void>(0));
				auto nigger = nigNog(g_SelectedPlayer);

				auto faggot = *(uintptr_t*)(nigger + 0x10C8);
				auto ip = (BYTE*)(faggot + 0x44);
				std::snprintf(ipBuf, sizeof(ipBuf) - 1, "~r~IP: %u.%u.%u.%u", ip[3], ip[2], ip[1], *ip);
				PlayerIP = std::to_string(ip[3]) + "." + std::to_string(ip[2]) + "." + std::to_string(ip[1]) + "." + std::to_string(*ip);

				auto port = reinterpret_cast<uint16_t*>(faggot + 0x1F4EBA0);
				char buffer[5 + 1];
				std::snprintf(buffer, sizeof(buffer), "%i", *port);
				port_str = buffer;


				Player player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);


				Hash street[2]{};
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(player, false);
				PATHFIND::GET_STREET_NAME_AT_COORD(coords.x, coords.y, coords.z, &street[0], &street[1]);

				int netHandle[13];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, netHandle, 13);


				Hash vehHash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(player, 0));
				bool isInAnyVehicle = PED::IS_PED_IN_ANY_VEHICLE(player, true);



				Features::Name = PLAYER::GET_PLAYER_NAME(g_SelectedPlayer);

				Features::RID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);



				Features::GodeModeInfo = PLAYER::GET_PLAYER_INVINCIBLE(g_SelectedPlayer) ? "Yes" : "No";

				Features::Wanted = PLAYER::GET_PLAYER_WANTED_LEVEL(g_SelectedPlayer);

				Features::Street = UI::GET_STREET_NAME_FROM_HASH_KEY(street[0]);

				Features::Zone = UI::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(coords.x, coords.y, coords.z));

				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(player, false);



				Features::Veh = isInAnyVehicle ? UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehHash)) : "No Vehicle";

				rp = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(5).As<int>();
				money = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(3).As<int>();
				rank = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(6).As<int>();
				kills2 = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(28).As<int>();
				deaths2 = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(29).As<int>();
				handle = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(56).As<int>();
				handle2 = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(3).As<int>();
				bank = handle - 10 - handle2 + (5 * 1 + 3 + 2);
				raceswon = globalHandle(1590682).At(g_SelectedPlayer, 883).At(122).At(1).As<int>();
				raceslost = globalHandle(1590682).At(g_SelectedPlayer, 883).At(122).At(1).At(1).As<int>();
				kd = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(26).As<float>();
				earnings = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(56).As<int>();
				tempMoney = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(3).As<int>();
				death = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(20).As<int>();
				deathlost = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(21).As<int>();
				races = globalHandle(1590682).At(g_SelectedPlayer, 883).At(211).At(15).As<int>();
				isOtr = globalHandle(1590682).At(g_SelectedPlayer, 883).At(208).As<int>();

			}
			Features::UpdateInfo = false;
		}








		
		

	}

	std::string encryptedstring() {
		char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
		std::string x = "";
		int input[] = { 46, 67, 14, 67, 16, 67, 12 };
		for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
			if (input[i] == 0) x += 0x20;
			else x += charlist[input[i] - 1];
		}
		return x;
	}



	int kohle = 5000;
	bool vehmultiplier = false;
	void LogScript::Initialize()
	{
		ImGuiIO& io = ImGui::GetIO();
		auto font = io.Fonts->AddFontFromFileTTF("ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		ImGui::PushFont(font);
		io.FontDefault = font;
		ImGui::StyleColorsClassic();
		
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const char* name = ImGui::GetStyleColorName(i);
			if (!strcmp(name, "Text"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 255, 255, 255 };
			}
			else if (!strcmp(name, "TextDisabled"))
			{
				ImGui::GetStyle().Colors[i] = { 128, 128, 128, 255 };
			}
			else if (!strcmp(name, "WindowBg"))
			{
				ImGui::GetStyle().Colors[i] = { 0, 0, 0, 255 };
			}
			else if (!strcmp(name, "PopupBg"))
			{
				ImGui::GetStyle().Colors[i] = { 20, 20, 20, 233 };
			}
			else if (!strcmp(name, "Border"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 21, 0, 240 };
			}
			else if (!strcmp(name, "BorderShadow"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 0, 0, 255 };
			}
			else if (!strcmp(name, "FrameBg"))
			{
				ImGui::GetStyle().Colors[i] = { 232, 9, 9, 70 };
			}
			else if (!strcmp(name, "FrameBgHovered"))
			{
				ImGui::GetStyle().Colors[i] = { 93, 0, 0, 255 };
			}
			else if (!strcmp(name, "FrameBgActive"))
			{
				ImGui::GetStyle().Colors[i] = { 65, 0, 0, 171 };
			}
			else if (!strcmp(name, "TitleBg"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 0, 0, 255 };
			}
			else if (!strcmp(name, "TitleBgActive"))
			{
				ImGui::GetStyle().Colors[i] = { 15, 0, 0, 255 };
			}
			else if (!strcmp(name, "MenuBarBg"))
			{
				ImGui::GetStyle().Colors[i] = { 122, 0, 0, 255 };
			}
			else if (!strcmp(name, "ScrollbarBg"))
			{
				ImGui::GetStyle().Colors[i] = { 102, 5, 0, 85 };
			}
			else if (!strcmp(name, "ScrollbarGrab"))
			{
				ImGui::GetStyle().Colors[i] = { 79, 0, 0, 255 };
			}
			else if (!strcmp(name, "ScrollbarGrabHovered"))
			{
				ImGui::GetStyle().Colors[i] = { 105, 0, 0, 255 };
			}
			else if (!strcmp(name, "ScrollbarGrabActive"))
			{
				ImGui::GetStyle().Colors[i] = { 130, 2, 0, 255 };
			}
			else if (!strcmp(name, "CheckMark"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 0, 0, 255 };
			}
			else if (!strcmp(name, "SliderGrab"))
			{
				ImGui::GetStyle().Colors[i] = { 140, 0, 0, 255 };
			}
			else if (!strcmp(name, "SliderGrabActive"))
			{
				ImGui::GetStyle().Colors[i] = { 66, 0, 0, 255 };
			}
			else if (!strcmp(name, "Button"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 0, 0, 102 };
			}
			else if (!strcmp(name, "ButtonHovered"))
			{
				ImGui::GetStyle().Colors[i] = { 66, 0, 0, 255 };
			}
			else if (!strcmp(name, "ButtonActive"))
			{
				ImGui::GetStyle().Colors[i] = { 15, 0, 1, 255 };
			}
			else if (!strcmp(name, "Header"))
			{
				ImGui::GetStyle().Colors[i] = { 138, 0, 0, 79 };
			}
			else if (!strcmp(name, "HeaderHovered"))
			{
				ImGui::GetStyle().Colors[i] = { 66, 0, 0, 204 };
			}
			else if (!strcmp(name, "HeaderActive"))
			{
				ImGui::GetStyle().Colors[i] = { 66, 0, 0, 255 };
			}
			else if (!strcmp(name, "Seperator"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 0, 0, 128 };
			}
			else if (!strcmp(name, "SeperatorHovered"))
			{
				ImGui::GetStyle().Colors[i] = { 26, 0, 0, 199 };
			}
			else if (!strcmp(name, "SeperatorActive"))
			{
				ImGui::GetStyle().Colors[i] = { 26, 0, 0, 255 };
			}
			else if (!strcmp(name, "ResizeGrip"))
			{
				ImGui::GetStyle().Colors[i] = { 66, 0, 0, 64 };
			}
			else if (!strcmp(name, "ResizeGripHovered"))
			{
				ImGui::GetStyle().Colors[i] = { 66, 0, 0, 171 };
			}
			else if (!strcmp(name, "ResizeGripActive"))
			{
				ImGui::GetStyle().Colors[i] = { 66, 0, 0, 242 };
			}
			else if (!strcmp(name, "PlotLines"))
			{
				ImGui::GetStyle().Colors[i] = { 156, 0, 0, 255 };
			}
			else if (!strcmp(name, "PlotLinesHovered"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 0, 0, 255 };
			}
			else if (!strcmp(name, "PlotLinesHovered"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 0, 0, 255 };
			}
			else if (!strcmp(name, "PlotHistogram"))
			{
				ImGui::GetStyle().Colors[i] = { 230, 0, 0, 255 };
			}
			else if (!strcmp(name, "PlotHistogramHovered"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 0, 0, 255 };
			}
			else if (!strcmp(name, "TextSelectedBg"))
			{
				ImGui::GetStyle().Colors[i] = { 66, 0, 0, 89 };
			}
			else if (!strcmp(name, "DragDropTarget"))
			{
				ImGui::GetStyle().Colors[i] = { 255, 0, 0, 230 };
			}
			else if (!strcmp(name, "NavHighlight"))
			{
				ImGui::GetStyle().Colors[i] = { 66, 0, 0, 255 };
			}

		}

		ImGui::StyleColorsLight();

		m_Initialized = true;
	}

	void LogScript::Destroy()
	{
	}

	namespace
	{
		std::size_t s_LastLogCount = 0;
	}



	std::string outfitotto() {
		char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
		std::string x = "";
		int input[] = { 48, 21, 20, 6, 9, 20, 81, 36, 8, 1, 14, 7, 5, 18 };
		for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
			if (input[i] == 0) x += 0x20;
			else x += charlist[input[i] - 1];
		}
		return x;
	}

	bool uwu = false;
	int loc_wantedLevel = 0;
	bool loc_Running = false;
	bool HideKey = false;
	static char SpawnByName[99] = "";
	bool Status = false;
	bool ModelChanger = false;
	bool StatusEditor = false;
	static float color[3]{};
	static int color_type{};
	int JobEarned;
	int earned;
	int reportstrength;
	int killstat;
	int deathstat;
	int commendstrength;
	int friendlyy;
	int helpfull;
	int grify;
	int vchatee;
	int gameplayex;
	int raciswon;
	int armiwins;
	int deathiwins;
	int deatmlose;
	int dmikills;
	int dmideathi;
	int tenniwini;
	int golfiwini;

	void LogScript::Tick()
	{
		static bool overlaytogglebool = true;
		if (overlaytogglebool)
		{
			Overlay(&overlaytogglebool);
		}



		if(StatusEditor)
		{
			if (!ImGui::Begin("Stats Editor", &StatusEditor))
			{
				ImGui::End();
				return;
			}





			ImGui::InputInt("Job Earned Money", &JobEarned); ImGui::SameLine(); if (ImGui::Button("Set")){	g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_TOTAL_EVC"), JobEarned, 1);});	}

			ImGui::InputInt("Earned Money", &earned); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_TOTAL_EVC"), earned, 1); }); }


			ImGui::InputInt("Kills", &killstat); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_KILLS_PLAYERS"), killstat, 1); }); }

			ImGui::InputInt("Deaths", &deathstat); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_DEATHS_PLAYER"), deathstat, 1); }); }

			ImGui::InputInt("Report Strength", &reportstrength); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_REPORT_STRENGTH"), reportstrength, 1); }); }

			ImGui::InputInt("Commend Strength", &commendstrength); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_COMMEND_STRENGTH"), commendstrength, 1); }); }


			ImGui::InputInt("Friendly Stuff", &friendlyy); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_FRIENDLY"), friendlyy, 1); }); }


			ImGui::InputInt("Helpfull Stuff", &helpfull); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_HELPFUL"), helpfull, 1); }); }




			ImGui::InputInt("Griefing Stuff", &grify); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_GRIEFING"), grify, 1); }); }


			ImGui::InputInt("VC Hate", &vchatee); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_VC_HATE"), vchatee, 1); }); }



			ImGui::InputInt("Gameplay Exploits", &gameplayex); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_GAME_EXPLOITS"), gameplayex, 1); }); }


			ImGui::InputInt("Won Races", &raciswon); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {	STATS::STAT_SET_INT($("AWD_RACES_WON"), raciswon, 1);   	STATS::STAT_SET_INT($("AWD_FM_GTA_RACES_WON"), raciswon, 1); }); }


			ImGui::InputInt("Armwrestling Wins", &armiwins); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("AWD_NO_ARMWRESTLING_WINS"), armiwins, 1); }); }



			ImGui::InputInt("Deathmatch Wins", &deathiwins); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("AWD_FM_DM_WINS"), deathiwins, 1);STATS::STAT_SET_INT($("AWD_FM_DM_WINS"), deathiwins, 1);STATS::STAT_SET_INT($("AWD_FM_TDM_WINS"), deathiwins, 1); }); }


			ImGui::InputInt("Deathmatch Loses", &deatmlose); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_TOTAL_DEATHMATCH_LOST"), deatmlose, 1); }); }

			ImGui::InputInt("Deathmatch Kills", &dmikills); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("AWD_FM_DM_TOTALKILLS"), dmikills, 1); }); }

			ImGui::InputInt("Deathmatch Deaths", &dmideathi); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("MPPLY_DM_TOTAL_DEATHS"), dmideathi, 1); }); }


			ImGui::InputInt("Golf Wins", &golfiwini); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {STATS::STAT_SET_INT($("AWD_FM_GOLF_WON"), golfiwini, 1); }); }


			ImGui::InputInt("Tennis Wins", &tenniwini); ImGui::SameLine(); if (ImGui::Button("Set")) { g_FiberScript->addTask([] {	STATS::STAT_SET_INT($("AWD_FM_TENNIS_WON"), tenniwini, 1); STATS::STAT_SET_INT($("MPPLY_TENNIS_MATCHES_WON"), tenniwini, 1); }); }




			ImGui::End();

			} 


		if (ModelChanger)
		{
			auto asdasdasdasd = skCrypt("Model Changer");
			if (!ImGui::Begin(asdasdasdasd, &ModelChanger))
			{
				ImGui::End();
				return;
			}
			asdasdasdasd.clear();
			if (ImGui::Button("Randomize Outfit"))
			{
				randomoutfit = true;
			}

			if (ImGui::InputInt("Face", &testa))
			{
			g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, testa, 0, 0);
			});
			}

			if (ImGui::InputInt("Head", &testb))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, testb, 0, 0);
				});
			}


			if (ImGui::InputInt("Hair", &testc))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, testc, 0, 0);
				});
			}


			if (ImGui::InputInt("Torso", &testd))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, testd, 0, 0);
				});
			}

			if (ImGui::InputInt("Legs", &teste))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, teste, 0, 0);
				});
			}

			if (ImGui::InputInt("Hands", &testf))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, testf, 0, 0);
				});
			}
			if (ImGui::InputInt("Feet", &testg))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, testg, 0, 0);
				});
			}
			if (ImGui::InputInt("Eyes", &testh))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, testh, 0, 0);
				});
			}
			if (ImGui::InputInt("Accessories", &testi))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, testi, 0, 0);
				});
			}
			if (ImGui::InputInt("Tasks", &testj))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, testj, 0, 0);
				});
			}
			if (ImGui::InputInt("Textures", &testk))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, testk, 0, 0);
				});
			}
			if (ImGui::InputInt("Torso2", &testl))
			{
				g_FiberScript->addTask([] {
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, testl, 0, 0);
				});
			}

			ImGui::End();

		}


		if (g_Settings.m_LogWindow)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("Console", &g_Settings.m_LogWindow))
			{
				std::lock_guard lock(g_Logger->GetMutex());
				auto msgs = g_Logger->GetMessages();

				for (std::size_t i = 0; i < msgs.second; ++i)
				{
					ImGui::TextUnformatted(msgs.first[i].get());
				}

				if (s_LastLogCount != msgs.second)
				{
					s_LastLogCount = msgs.second;
					ImGui::SetScrollHereY(1.f);
				}
			}  ImGui::End();
		}

		static int switchTabs = 8;
		if (g_UiManager->ImGUIMode)
		{
			if (!ImGui::Begin(encryptedstring().c_str()))
			{

				ImGui::End();
				return;
			}

			ImGui::SetWindowSize({ 1400, 0 }, ImGuiCond_Always);
			ImGui::SetNextWindowSize({ 1400, 0 });



			// tabs


			int colorbuttonid = 4;

			ImGui::PushID(colorbuttonid);
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(colorbuttonid / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(colorbuttonid / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(colorbuttonid / 7.0f, 0.8f, 0.8f));




			if (switchTabs == 8)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				if (ImGui::Button("Home", ImVec2(100.0f, 0.0f)))
					switchTabs = 8;

				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else
			{

				if (ImGui::Button("Home", ImVec2(100.0f, 0.0f)))
					switchTabs = 8;
			}

			ImGui::SameLine(0.0, 25.0f);


			if (switchTabs == 0)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				if (ImGui::Button("Self", ImVec2(100.0f, 0.0f)))
					switchTabs = 0;


				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else
			{
				if (ImGui::Button("Self", ImVec2(100.0f, 0.0f)))
					switchTabs = 0;
			}





			ImGui::SameLine(0.0, 2.0f);

			if (switchTabs == 1)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				if (ImGui::Button("Weapon", ImVec2(100.0f, 0.0f)))
					switchTabs = 1;

				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else
			{
				if (ImGui::Button("Weapon", ImVec2(100.0f, 0.0f)))
					switchTabs = 1;
			}


			ImGui::SameLine(0.0, 2.0f);

			if (switchTabs == 2)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				if (ImGui::Button("Veh Spawner", ImVec2(100.0f, 0.0f)))
					switchTabs = 2;

				ImGui::PopStyleColor(3);
				ImGui::PopID();

			}

			else {
				if (ImGui::Button("Veh Spawner", ImVec2(100.0f, 0.0f)))
					switchTabs = 2;
			}


			ImGui::SameLine(0.0, 2.0f);



			if (switchTabs == 3)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				if (ImGui::Button("Vehicle", ImVec2(100.0f, 0.0f)))
					switchTabs = 3;

				ImGui::PopStyleColor(3);
				ImGui::PopID();

			}
			else
			{
				if (ImGui::Button("Vehicle", ImVec2(100.0f, 0.0f)))
					switchTabs = 3;
			}


			ImGui::SameLine(0.0, 2.0f);



			if (switchTabs == 4)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				if (ImGui::Button("Teleport", ImVec2(100.0f, 0.0f)))
					switchTabs = 4;


				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else
			{
				if (ImGui::Button("Teleport", ImVec2(100.0f, 0.0f)))
					switchTabs = 4;
			}


			ImGui::SameLine(0.0, 2.0f);


			if (switchTabs == 10)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				if (ImGui::Button("Online", ImVec2(100.0f, 0.0f)))
					switchTabs = 10;

				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else
			{
				if (ImGui::Button("Online", ImVec2(100.0f, 0.0f)))
					switchTabs = 10;
			}




			ImGui::SameLine(0.0, 2.0f);


			if (switchTabs == 12)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				if (ImGui::Button("All Player", ImVec2(100.0f, 0.0f)))
					switchTabs = 12;

				ImGui::PopStyleColor(3);
				ImGui::PopID();

			}
			else
			{
				if (ImGui::Button("All Player", ImVec2(100.0f, 0.0f)))
					switchTabs = 12;
			}


			ImGui::SameLine(0.0, 2.0f);


			if (switchTabs == 5)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));

				if (ImGui::Button("Recovery", ImVec2(100.0f, 0.0f)))
					switchTabs = 5;

				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else
			{
				if (ImGui::Button("Recovery", ImVec2(100.0f, 0.0f)))
					switchTabs = 5;
			}



			ImGui::SameLine(0.0, 2.0f);


			if (switchTabs == 6)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				if (ImGui::Button("Misc", ImVec2(100.0f, 0.0f)))
					switchTabs = 6;


				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else
			{
				if (ImGui::Button("Misc", ImVec2(100.0f, 0.0f)))
					switchTabs = 6;
			}

			ImGui::SameLine(0.0, 2.0f);



			if (switchTabs == 11)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));


				if (ImGui::Button("World", ImVec2(100.0f, 0.0f)))
					switchTabs = 11;

				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else
			{
				if (ImGui::Button("World", ImVec2(100.0f, 0.0f)))
					switchTabs = 11;
			}


			ImGui::SameLine(0.0, 2.0f);

			if (switchTabs == 7)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));

				if (ImGui::Button("Protection", ImVec2(100.0f, 0.0f)))
					switchTabs = 7;

				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else {
				if (ImGui::Button("Protection", ImVec2(100.0f, 0.0f)))
					switchTabs = 7;
			}


			ImGui::SameLine(0.0, 2.0f);


			if (switchTabs == 9)
			{
				ImGui::PushID(3);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));

				if (ImGui::Button("Settings", ImVec2(100.0f, 0.0f)))
					switchTabs = 9;

				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
			else
			{
				if (ImGui::Button("Settings", ImVec2(100.0f, 0.0f)))
					switchTabs = 9;
			}
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::PopStyleColor(3);
			ImGui::PopID();

			switch (switchTabs)
			{





			case 11:

			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("baiscoptttxdia", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Basic Options"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}
				if (ImGui::Checkbox("FPS Booster", &Features::AsteroidShowerBool))
				{
					GRAPHICS::_SET_BLACKOUT(Features::AsteroidShowerBool);
	
				}
				ImGui::Checkbox("Disable Gravity", &Features::GravityBool);
				ImGui::Checkbox("Car Caos", &Features::ChaosModeBool);
				if (ImGui::SliderInt("Wave Intensity", &Features::WaveIntensityValue, 0, 5000))
				{
					Features::SetWaveIntensity();
				}








				ImGui::EndChild();
				ImGui::PopStyleVar();
			}

			ImGui::SameLine(0.0f, 380.0f);

			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("Ddgfhhdfghghfghfghfsghfgjhhkhfghfghfghfgh", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Weather and Time Options"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}
				ImGui::Checkbox("Random Time", &Features::TimeSpamBool);
				if (ImGui::SliderInt("Lobby Time", &Features::TimeHour, 0, 23))
				{
					Features::SetLobbyTime(Features::TimeHour, 0, 0);
				}

				if (ImGui::ListBox("Lobby Weather", &Lists::lobbywet, lobbywetter, IM_ARRAYSIZE(lobbywetter), 6))
				{
					Features::SetWeather(Lists::lobbywet);
				}

				if (ImGui::ListBox("Local Weather", &Lists::localweather, wetter, IM_ARRAYSIZE(wetter), 6))
				{
					GAMEPLAY::SET_OVERRIDE_WEATHER((char*)wetter[Lists::localweather]);
				}








				ImGui::EndChild();
				ImGui::PopStyleVar();
			}



			ImGui::NewLine();
			ImGui::SameLine(0.0, 420.0f);

			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("Ddgfhhdfsddfdfsdfghghfghfghfsghfgjhhkhfghfghfghfgh", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Custom Map Mods"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}


				if (ImGui::Button("Maze-Bank Small Ramp")) {
					g_FiberScript->addTask([] {
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -74.94243f, -818.63446f, 326.174347f, 1, 0, 0, 1);

						Features::PlaceObjectByHash(2475986526, -80.9087, -830.357, 325.097, -14.4264, -8.53774, 152.209, -1, 0);
						Features::PlaceObjectByHash(2475986526, -79.2316, -831.297, 325.108, -14.4054, 4.26887, 164.271, -1, 0);
						Features::PlaceObjectByHash(2475986526, -76.7563, -831.549, 325.123, -14.4263, -0, 171.818, -1, 0);
						Features::PlaceObjectByHash(2475986526, -74.2595, -831.691, 325.09, -14.2059, -1.06722, -176.517, -1, 0);
						Features::PlaceObjectByHash(2475986526, -71.9478, -831.257, 325.113, -14.4264, 2.13443, -166.006, -1, 0);
						Features::PlaceObjectByHash(2475986526, -69.5981, -830.542, 325.066, -14.5918, -4.26887, -155.474, -1, 0);
						Features::PlaceObjectByHash(2475986526, -67.4174, -829.035, 325.097, -14.4263, -4.26887, -140.651, -1, 0);
						Features::PlaceObjectByHash(2475986526, -65.7121, -827.409, 325.068, -14.3048, -1.70755, -130.667, -1, 0);
						Features::PlaceObjectByHash(2475986526, -64.2717, -825.422, 325.112, -14.4263, -0, -121.256, -1, 0);
						Features::PlaceObjectByHash(2475986526, -63.2876, -823.434, 325.114, -14.5345, -0, -111.446, -1, 0);
						Features::PlaceObjectByHash(2475986526, -62.4924, -821.128, 325.082, -14.5467, 2.13443, -102.385, -1, 0);
						Features::PlaceObjectByHash(2475986526, -62.233, -818.528, 325.065, -14.6184, -8.00413, -88.1861, -1, 0);
						Features::PlaceObjectByHash(2475986526, -62.8694, -815.926, 325.118, -14.4265, -6.4033, -76.5979, -1, 0);
						Features::PlaceObjectByHash(2475986526, -63.6142, -813.68, 325.112, -14.3655, 8.53774, -66.7885, -1, 0);
						Features::PlaceObjectByHash(2475986526, -64.9883, -811.449, 325.107, -14.4263, 1.28066, -52.8494, -1, 0);
						Features::PlaceObjectByHash(2475986526, -66.5913, -808.328, 325.238, -12.4517, -0, -40.3246, -1, 0);
						Features::PlaceObjectByHash(2475986526, -68.2603, -807.899, 325.336, -13.8689, -0, -33.062, -1, 0);
						Features::PlaceObjectByHash(2475986526, -71.1526, -807.598, 325.153, -12.0416, 4.26887, -28.0523, -1, 0);
						Features::PlaceObjectByHash(2475986526, -73.2853, -806.628, 325.151, -11.7962, -0, -19.1717, -1, 0);
						Features::PlaceObjectByHash(2475986526, -75.2243, -806.286, 325.164, -12.0419, -0, 1.55726, -1, 0);
						Features::PlaceObjectByHash(2475986526, -77.5757, -806.312, 325.088, -14.1843, -0, 12.6263, -1, 0);
						Features::PlaceObjectByHash(2475986526, -79.8704, -807.22, 325.143, -14.049, -4.26887, 21.4769, -1, 0);
						Features::PlaceObjectByHash(2475986526, -82.0222, -807.83, 325.036, -14.1422, -4.26887, 32.7605, -1, 0);
						Features::PlaceObjectByHash(2475986526, -83.8934, -809.424, 325.073, -14.5264, -8.53774, 46.5132, -1, 0);
						Features::PlaceObjectByHash(2475986526, -85.2523, -810.983, 325.043, -14.859, -0, 53.5324, -1, 0);
						Features::PlaceObjectByHash(2475986526, -86.5177, -813.202, 325.089, -14.5267, 4.26887, 64.6634, -1, 0);
						Features::PlaceObjectByHash(2475986526, -87.6645, -815.707, 325.059, -14.8589, 4.26887, 73.157, -1, 0);
						Features::PlaceObjectByHash(2475986526, -87.7973, -817.987, 325.119, -14.8468, -1.33402, 89.3982, -1, 0);
						Features::PlaceObjectByHash(2475986526, -87.5801, -821.034, 325.059, -14.8593, -0, 95.4435, -1, 0);
						Features::PlaceObjectByHash(2475986526, -87.2815, -822.239, 325.126, -15.6308, -4.26887, 100.311, -1, 0);
						Features::PlaceObjectByHash(2475986526, -86.7602, -824.03, 325.044, -15.9224, -0, 116.957, -1, 0);
						Features::PlaceObjectByHash(2475986526, -85.3743, -826.099, 325.136, -15.7025, 2.56132, 124.307, -1, 0);
						Features::PlaceObjectByHash(2475986526, -83.4737, -828.611, 325.076, -15.0688, -0, 132.538, -1, 0);
						Features::PlaceObjectByHash(2475986526, -87.9554, -832.877, 325.894, -14.1563, 4.26887, 132.995, -1, 0);
						Features::PlaceObjectByHash(2475986526, -89.3865, -831.322, 325.887, -14.1562, -0, 126.154, -1, 0);
						Features::PlaceObjectByHash(2475986526, -86.4247, -834.407, 325.915, -14.2701, 4.26887, 143.277, -1, 0);
						Features::PlaceObjectByHash(2475986526, -85.1736, -833.789, 325.653, -14.4072, -4.26887, 145.777, -1, 0);
						Features::PlaceObjectByHash(2475986526, -83.8118, -835.765, 326.063, -12.243, 4.26887, 151.527, -1, 0);
						Features::PlaceObjectByHash(2475986526, -80.7015, -837.145, 326.059, -12.3172, 2.13443, 162.332, -1, 0);
						Features::PlaceObjectByHash(2475986526, -77.6428, -837.649, 326.163, -10.8391, 3.20165, 171.297, -1, 0);
						Features::PlaceObjectByHash(2475986526, -75.479, -837.909, 326.025, -12.3172, -1.06722, 174.574, -1, 0);
						Features::PlaceObjectByHash(2475986526, -73.861, -837.826, 326.061, -12.3173, 5.33609, -176.632, -1, 0);
						Features::PlaceObjectByHash(2475986526, -70.4799, -837.265, 326.09, -12.3173, -0, -166.182, -1, 0);
						Features::PlaceObjectByHash(2475986526, -67.0415, -836.185, 326.018, -12.3171, -0, -156.039, -1, 0);
						Features::PlaceObjectByHash(2475986526, -64.8504, -834.996, 325.951, -11.5263, -0, -145.834, -1, 0);
						Features::PlaceObjectByHash(2475986526, -63.5702, -833.725, 326.1, -11.2947, -0, -140.961, -1, 0);
						Features::PlaceObjectByHash(2475986526, -60.9992, -831.419, 326.075, -11.5262, -4.26887, -130.963, -1, 0);
						Features::PlaceObjectByHash(2475986526, -58.9923, -828.729, 326.116, -11.5262, 4.26887, -121.973, -1, 0);
						Features::PlaceObjectByHash(2475986526, -57.5045, -825.626, 326.114, -11.5263, -0, -110.959, -1, 0);
						Features::PlaceObjectByHash(2475986526, -56.5533, -822.397, 326.08, -11.1311, -6.4033, -102, -1, 0);
						Features::PlaceObjectByHash(2475986526, -56.0911, -820.05, 326.049, -11.0325, 2.13443, -100.794, -1, 0);
						Features::PlaceObjectByHash(2475986526, -56.0681, -818.32, 326.087, -11.1312, -2.66804, -87.9469, -1, 0);
						Features::PlaceObjectByHash(2475986526, -56.2989, -816.237, 326.048, -11.0324, 2.13443, -83.2139, -1, 0);
						Features::PlaceObjectByHash(2475986526, -56.8952, -814.518, 326.142, -11.0324, -2.13443, -76.5476, -1, 0);
						Features::PlaceObjectByHash(2475986526, -58.1209, -811.23, 326.116, -10.9697, -0, -66.7674, -1, 0);
						Features::PlaceObjectByHash(2475986526, -59.0622, -809.17, 326.095, -11.0574, 4.26887, -62.782, -1, 0);
						Features::PlaceObjectByHash(2475986526, -60.096, -807.639, 326.119, -11.5544, -0, -52.7596, -1, 0);
						Features::PlaceObjectByHash(2475986526, -62.081, -805.317, 326.116, -11.1035, -0, -40.7682, -1, 0);
						Features::PlaceObjectByHash(2475986526, -64.1466, -804.55, 326.283, -11.1035, -0, -30.477, -1, 0);
						Features::PlaceObjectByHash(2475986526, -67.9795, -798.8, 326.717, -10.1561, -0, -29.3495, -1, 0);
						Features::PlaceObjectByHash(2475986526, -67.5734, -802.52, 326.262, -10.471, -8.53774, -31.2185, -1, 0);
						Features::PlaceObjectByHash(2475986526, -70.9341, -800.541, 326.198, -10.5317, -0, -20.0064, -1, 0);
						Features::PlaceObjectByHash(2475986526, -75.3309, -801.285, 325.849, -10.2407, -0, 1.58401, -1, 0);
						Features::PlaceObjectByHash(2475986526, -74.0222, -799.865, 326.177, -10.7327, -0, -5.98314, -1, 0);
						Features::PlaceObjectByHash(2475986526, -76.5167, -797.998, 326.32, -12.4969, -2.66804, 1.58883, -1, 0);
						Features::PlaceObjectByHash(2475986526, -79.2787, -800.531, 326.011, -12.9433, 4.26887, 13.0054, -1, 0);
						Features::PlaceObjectByHash(2475986526, -81.6721, -801.017, 325.9, -12.4601, 2.13443, 17.3792, -1, 0);
						Features::PlaceObjectByHash(2475986526, -83.6027, -801.744, 325.971, -12.9433, -0, 26.3052, -1, 0);
						Features::PlaceObjectByHash(2475986526, -85.6586, -802.789, 325.95, -12.8791, 1.28066, 32.5856, -1, 0);
						Features::PlaceObjectByHash(2475986526, -87.5086, -804.25, 325.978, -12.9432, 4.26887, 42.3279, -1, 0);
						Features::PlaceObjectByHash(2475986526, -88.9923, -805.73, 325.89, -11.9333, -4.26887, 46.0613, -1, 0);
						Features::PlaceObjectByHash(2475986526, -90.167, -807.318, 325.946, -13.0244, -0, 53.178, -1, 0);
						Features::PlaceObjectByHash(2475986526, -93.5987, -807.353, 326.343, -11.5713, 4.26887, 60.8753, -1, 0);
						Features::PlaceObjectByHash(2475986526, -93.5166, -813.963, 325.942, -13.4341, -4.26887, 73.0256, -1, 0);
						Features::PlaceObjectByHash(2475986526, -92.121, -810.584, 325.996, -13.4339, -4.26887, 64.9353, -1, 0);
						Features::PlaceObjectByHash(2475986526, -93.9931, -815.866, 325.924, -13.0519, -0, 79.5966, -1, 0);
						Features::PlaceObjectByHash(2475986526, -93.8716, -817.904, 325.988, -13.4339, -0, 88.8361, -1, 0);
						Features::PlaceObjectByHash(2475986526, -93.7912, -821.777, 325.946, -13.6946, -2.66804, 91.1427, -1, 0);
						Features::PlaceObjectByHash(2475986526, -93.2951, -823.554, 325.966, -13.157, -0, 101.424, -1, 0);
						Features::PlaceObjectByHash(2475986526, -92.5757, -827.033, 325.87, -13.5323, -0, 104.668, -1, 0);
						Features::PlaceObjectByHash(2475986526, -91.53, -828.342, 325.842, -14.1563, 4.26887, 120.328, -1, 0);
						Features::PlaceObjectByHash(2475986526, -90.5203, -829.611, 325.936, -14.1563, -0, 124.573, -1, 0);
						Features::PlaceObjectByHash(2475986526, -95.5355, -833.068, 327.049, -9.63525, 1.70755, 124.512, -1, 0);
						Features::PlaceObjectByHash(2475986526, -94.2445, -835.1, 326.976, -9.27617, -1.28066, 128.396, -1, 0);
						Features::PlaceObjectByHash(2475986526, -92.513, -837.087, 327.008, -9.63523, -4.26887, 132.871, -1, 0);
						Features::PlaceObjectByHash(2475986526, -90.07, -839.341, 327.025, -9.63574, 4.26887, 143.545, -1, 0);
						Features::PlaceObjectByHash(2475986526, -86.7336, -841.135, 327.284, -9.63566, -0, 150.983, -1, 0);
						Features::PlaceObjectByHash(2475986526, -84.8343, -842.167, 327.254, -9.36742, -4.26887, 152.377, -1, 0);
						Features::PlaceObjectByHash(2475986526, -90.0883, -842.661, 327.589, -7.98782, -8.53774, 146.409, -1, 0);
						Features::PlaceObjectByHash(2475986526, -82.595, -843.001, 327.277, -9.6352, -0, 161.654, -1, 0);
						Features::PlaceObjectByHash(2475986526, -80.8027, -843.618, 327.263, -9.36755, -2.13443, 165.215, -1, 0);
						Features::PlaceObjectByHash(2475986526, -78.5619, -843.703, 327.458, -9.63545, -2.13443, 171.015, -1, 0);
						Features::PlaceObjectByHash(2475986526, -76.2479, -844.026, 327.261, -9.36765, 1.06722, 175.986, -1, 0);
						Features::PlaceObjectByHash(2475986526, -73.5382, -843.999, 327.285, -9.6355, -0, -177.212, -1, 0);
						Features::PlaceObjectByHash(2475986526, -71.2047, -843.988, 327.3, -9.36764, -1.06722, -172.013, -1, 0);
						Features::PlaceObjectByHash(2475986526, -69.036, -843.266, 327.309, -9.63525, 4.26887, -166.686, -1, 0);
						Features::PlaceObjectByHash(2475986526, -67.2981, -840.996, 326.756, -9.37509, -2.13443, -159.014, -1, 0);
						Features::PlaceObjectByHash(2475986526, -66.7067, -842.714, 327.222, -9.37501, 2.13443, -159.27, -1, 0);
						Features::PlaceObjectByHash(2475986526, -64.5693, -841.792, 327.24, -9.63515, 4.26887, -156.16, -1, 0);
						Features::PlaceObjectByHash(2475986526, -61.8874, -840.436, 327.231, -9.37483, 4.26887, -146.534, -1, 0);
						Features::PlaceObjectByHash(2475986526, -59.7118, -838.501, 327.384, -9.63533, -0, -141.372, -1, 0);
						Features::PlaceObjectByHash(2475986526, -57.9491, -837.16, 327.309, -9.37471, 4.26887, -135.839, -1, 0);
						Features::PlaceObjectByHash(2475986526, -56.3494, -835.471, 327.34, -9.63578, 4.26887, -131.675, -1, 0);
						Features::PlaceObjectByHash(2475986526, -54.9387, -833.93, 327.334, -9.37482, -0, -127.887, -1, 0);
						Features::PlaceObjectByHash(2475986526, -53.727, -832.032, 327.367, -9.63521, -4.26887, -122.142, -1, 0);
						Features::PlaceObjectByHash(2475986526, -52.5928, -830.077, 327.332, -9.37496, -0, -116.843, -1, 0);
						Features::PlaceObjectByHash(2475986526, -51.7552, -827.819, 327.385, -9.63569, 6.4033, -111.077, -1, 0);
						Features::PlaceObjectByHash(2475986526, -51.0061, -825.839, 327.369, -9.37494, 4.26887, -107.054, -1, 0);
						Features::PlaceObjectByHash(2475986526, -50.5468, -823.622, 327.378, -9.63572, 4.26887, -101.598, -1, 0);
						Features::PlaceObjectByHash(2475986526, -50.0992, -820.896, 327.345, -9.47333, -1.06722, -95.7976, -1, 0);
						Features::PlaceObjectByHash(2475986526, -49.9295, -818.102, 327.381, -9.63531, -8.00413, -88.2146, -1, 0);
						Features::PlaceObjectByHash(2475986526, -50.1895, -815.816, 327.358, -9.4734, -0, -82.8649, -1, 0);
						Features::PlaceObjectByHash(2475986526, -50.9164, -813.132, 327.442, -9.63524, 2.13443, -76.865, -1, 0);
						Features::PlaceObjectByHash(2475986526, -51.1585, -811.568, 327.373, -9.58574, -0, -69.3402, -1, 0);
						Features::PlaceObjectByHash(2475986526, -52.0622, -809.533, 327.354, -9.63541, 2.13443, -65.7624, -1, 0);
						Features::PlaceObjectByHash(2475986526, -53.4048, -806.624, 327.376, -9.63526, 2.13443, -65.3971, -1, 0);
						Features::PlaceObjectByHash(2475986526, -55.2978, -803.815, 327.389, -9.63524, 4.26887, -52.2107, -1, 0);
						Features::PlaceObjectByHash(2475986526, -56.5179, -802.266, 327.366, -9.51013, 4.26887, -50.6537, -1, 0);
						Features::PlaceObjectByHash(2475986526, -57.9995, -800.68, 327.42, -9.6353, 1.28066, -41.7027, -1, 0);
						Features::PlaceObjectByHash(2475986526, -61.0278, -799.404, 327.549, -9.63516, 8.53774, -31.016, -1, 0);
						Features::PlaceObjectByHash(2475986526, -64.37, -797.284, 327.603, -9.6351, -0, -31.6732, -1, 0);
						Features::PlaceObjectByHash(2475986526, -66.3998, -795.965, 327.526, -9.42422, 8.53773, -29.018, -1, 0);
						Features::PlaceObjectByHash(2475986526, -68.8079, -794.744, 327.535, -9.63558, -2.13443, -20.0341, -1, 0);
						Features::PlaceObjectByHash(2475986526, -72.1225, -793.825, 327.497, -9.57894, -2.13443, -12.2336, -1, 0);
						Features::PlaceObjectByHash(2475986526, -75.6415, -795.169, 327.2, -9.63555, -1.60083, 2.8097, -1, 0);
						Features::PlaceObjectByHash(2475986526, -77.9613, -794.235, 327.223, -8.9769, -5.33608, 4.53814, -1, 0);
						Features::PlaceObjectByHash(2475986526, -75.3695, -789.507, 328.306, -8.84722, -8.33763, -0.0879073, -1, 0);
						Features::PlaceObjectByHash(2475986526, -80.6908, -794.505, 327.217, -9.63537, 4.26887, 13.0745, -1, 0);
						Features::PlaceObjectByHash(2475986526, -83.5673, -795.148, 327.101, -9.92985, 2.13443, 17.5819, -1, 0);
						Features::PlaceObjectByHash(2475986526, -86.3087, -796.203, 327.177, -9.63542, -4.26887, 25.9296, -1, 0);
						Features::PlaceObjectByHash(2475986526, -88.9655, -797.634, 327.118, -9.92994, -4.26887, 33.0571, -1, 0);
						Features::PlaceObjectByHash(2475986526, -91.6251, -799.702, 327.176, -9.63539, -0, 42.2513, -1, 0);
						Features::PlaceObjectByHash(2475986526, -93.414, -801.299, 327.124, -9.92995, -0, 48.7085, -1, 0);
						Features::PlaceObjectByHash(2475986526, -95.1453, -803.637, 327.147, -9.63537, -8.53774, 53.6544, -1, 0);
						Features::PlaceObjectByHash(2475986526, -96.5885, -805.701, 327.144, -9.8947, -0, 60.5096, -1, 0);
						Features::PlaceObjectByHash(2475986526, -97.6945, -807.971, 327.174, -9.63569, 4.26887, 64.7568, -1, 0);
						Features::PlaceObjectByHash(2475986526, -98.7075, -809.885, 327.026, -8.13758, -0, 67.8881, -1, 0);
						Features::PlaceObjectByHash(2475986526, -99.394, -812.176, 327.105, -9.63525, -4.26887, 73.0223, -1, 0);
						Features::PlaceObjectByHash(2475986526, -100.025, -814.868, 327.097, -9.97277, 2.13443, 83.1537, -1, 0);
						Features::PlaceObjectByHash(2475986526, -100.012, -817.789, 327.15, -9.63535, -1.33402, 88.8234, -1, 0);
						Features::PlaceObjectByHash(2475986526, -100.069, -819.76, 327.099, -9.95297, -1.33402, 90.8729, -1, 0);
						Features::PlaceObjectByHash(2475986526, -99.969, -821.91, 327.11, -9.63541, -2.66804, 91.5501, -1, 0);
						Features::PlaceObjectByHash(2475986526, -99.3358, -824.801, 327.138, -9.63539, 2.13443, 101.678, -1, 0);
						Features::PlaceObjectByHash(2475986526, -98.5443, -828.598, 327.033, -9.63553, -0, 104.64, -1, 0);
						Features::PlaceObjectByHash(2475986526, -97.0896, -831.054, 326.937, -10.0741, 4.26887, 118.72, -1, 0);
						Features::PlaceObjectByHash(2475986526, -102.435, -833.952, 328.506, -5.26399, -0, 118.502, -1, 0);
						Features::PlaceObjectByHash(2475986526, -103.536, -831.932, 328.513, -5.42142, 4.26887, 111.099, -1, 0);
						Features::PlaceObjectByHash(2475986526, -100.644, -836.571, 328.636, -5.26398, -0, 124.006, -1, 0);
						Features::PlaceObjectByHash(2475986526, -99.0448, -838.912, 328.589, -5.26395, -2.13443, 128.175, -1, 0);
						Features::PlaceObjectByHash(2475986526, -96.9401, -841.184, 328.589, -5.26384, -2.13443, 132.615, -1, 0);
						Features::PlaceObjectByHash(2475986526, -95.4409, -842.718, 328.551, -5.01006, -2.13443, 136.57, -1, 0);
						Features::PlaceObjectByHash(2475986526, -93.6584, -844.231, 328.606, -5.26388, -0, 143.429, -1, 0);
						Features::PlaceObjectByHash(2475986526, -92.1044, -845.82, 328.655, -5.01307, -2.13443, 147.428, -1, 0);
						Features::PlaceObjectByHash(2475986526, -89.6061, -846.328, 328.851, -5.26389, -0, 150.62, -1, 0);
						Features::PlaceObjectByHash(2475986526, -87.5884, -847.552, 328.829, -5.6777, -0, 153.36, -1, 0);
						Features::PlaceObjectByHash(2475986526, -84.5215, -848.802, 328.867, -5.26405, 5.33608, 161.164, -1, 0);
						Features::PlaceObjectByHash(2475986526, -81.9779, -849.605, 328.821, -5.67769, 1.06722, 166.961, -1, 0);
						Features::PlaceObjectByHash(2475986526, -79.5282, -849.717, 329.046, -5.26392, 1.06722, 170.517, -1, 0);
						Features::PlaceObjectByHash(2475986526, -76.7555, -850.113, 328.885, -4.93224, 2.66804, 175.995, -1, 0);
						Features::PlaceObjectByHash(2475986526, -73.2336, -850.06, 328.883, -5.26397, -0, -177.431, -1, 0);
						Features::PlaceObjectByHash(2475986526, -70.4067, -849.836, 328.854, -4.82287, -5.33608, -172.2, -1, 0);
						Features::PlaceObjectByHash(2475986526, -67.6252, -849.166, 328.911, -5.26394, -0, -166.741, -1, 0);
						Features::PlaceObjectByHash(2475986526, -64.6525, -848.331, 328.792, -4.82267, -2.13443, -160.74, -1, 0);
						Features::PlaceObjectByHash(2475986526, -62.1086, -847.355, 328.837, -5.26389, 2.13443, -156.346, -1, 0);
						Features::PlaceObjectByHash(2475986526, -60.2755, -846.895, 328.808, -5.97307, -2.13443, -151.031, -1, 0);
						Features::PlaceObjectByHash(2475986526, -58.5152, -845.543, 328.833, -5.26392, 1.06722, -147.129, -1, 0);
						Features::PlaceObjectByHash(2475986526, -55.9339, -843.258, 328.987, -5.26394, 2.13443, -141.8, -1, 0);
						Features::PlaceObjectByHash(2475986526, -53.6636, -841.564, 328.905, -5.18348, -0, -136.192, -1, 0);
						Features::PlaceObjectByHash(2475986526, -51.8013, -839.526, 328.926, -5.26393, -2.13443, -131.788, -1, 0);
						Features::PlaceObjectByHash(2475986526, -49.9112, -837.51, 328.916, -5.18352, -8.53774, -125.894, -1, 0);
						Features::PlaceObjectByHash(2475986526, -48.5833, -835.261, 328.968, -5.26388, 2.13443, -122.598, -1, 0);
						Features::PlaceObjectByHash(2475986526, -47.1369, -832.806, 328.936, -5.18352, -0, -117.146, -1, 0);
						Features::PlaceObjectByHash(2475986526, -46.1092, -830.019, 328.985, -5.26389, -0, -111.097, -1, 0);
						Features::PlaceObjectByHash(2475986526, -45.2549, -827.659, 328.957, -5.18353, -1.06722, -105.915, -1, 0);
						Features::PlaceObjectByHash(2475986526, -44.5598, -824.856, 328.973, -5.26387, -0, -101.582, -1, 0);
						Features::PlaceObjectByHash(2475986526, -44.0346, -821.522, 328.953, -5.26387, 5.33608, -95.978, -1, 0);
						Features::PlaceObjectByHash(2475986526, -43.8673, -817.92, 328.98, -5.26387, -4.00206, -88.1556, -1, 0);
						Features::PlaceObjectByHash(2475986526, -44.1983, -815.072, 328.956, -5.26387, -0, -82.8806, -1, 0);
						Features::PlaceObjectByHash(2475986526, -45.0463, -811.788, 329.021, -5.26392, -0, -77.2513, -1, 0);
						Features::PlaceObjectByHash(2475986526, -45.6154, -809.566, 328.95, -5.25705, -2.13443, -72.2094, -1, 0);
						Features::PlaceObjectByHash(2475986526, -46.5685, -807.149, 328.929, -5.26395, -2.13443, -66.9958, -1, 0);
						Features::PlaceObjectByHash(2475986526, -47.9752, -804.122, 328.959, -5.26398, -0, -65.1505, -1, 0);
						Features::PlaceObjectByHash(2475986526, -49.0785, -802.078, 328.914, -5.31539, 4.26887, -57.7224, -1, 0);
						Features::PlaceObjectByHash(2475986526, -50.5092, -800.141, 328.99, -5.26406, -0, -52.4683, -1, 0);
						Features::PlaceObjectByHash(2475986526, -52.041, -798.134, 329.001, -5.31536, -2.13443, -49.2493, -1, 0);
						Features::PlaceObjectByHash(2475986526, -53.8808, -796.134, 329.041, -5.26389, -0, -42.3308, -1, 0);
						Features::PlaceObjectByHash(2475986526, -55.4375, -794.682, 329.045, -5.32055, 2.13443, -37.3601, -1, 0);
						Features::PlaceObjectByHash(2475986526, -57.7537, -794.2, 329.16, -5.26393, 2.13443, -32.2267, -1, 0);
						Features::PlaceObjectByHash(2475986526, -61.0299, -792.042, 329.172, -5.26389, -2.13443, -32.1174, -1, 0);
						Features::PlaceObjectByHash(2475986526, -63.5163, -790.736, 329.085, -5.04535, -4.26887, -29.2933, -1, 0);
						Features::PlaceObjectByHash(2475986526, -64.7324, -789.882, 329.081, -4.987, -2.13443, -27.7917, -1, 0);
						Features::PlaceObjectByHash(2475986526, -66.7775, -788.94, 329.155, -5.04558, 1.06722, -19.5666, -1, 0);
						Features::PlaceObjectByHash(2475986526, -68.6555, -788.272, 329.103, -5.30654, 3.20165, -16.9146, -1, 0);
						Features::PlaceObjectByHash(2475986526, -70.8259, -787.837, 329.128, -5.04546, 1.06722, -12.2941, -1, 0);
						Features::PlaceObjectByHash(2475986526, -74.5572, -787.022, 329.08, -4.61724, 1.06722, -10.7316, -1, 0);
						Features::PlaceObjectByHash(2475986526, -75.8754, -788.646, 328.671, -6.78921, -0, 2.98721, -1, 0);
						Features::PlaceObjectByHash(2475986526, -78.4, -788.132, 328.83, -5.91899, 2.66804, 3.75875, -1, 0);
						Features::PlaceObjectByHash(2475986526, -80.5351, -788.179, 328.782, -5.80051, -0, 7.26539, -1, 0);
						Features::PlaceObjectByHash(2475986526, -82.1189, -788.558, 328.793, -5.9192, 1.06722, 12.7168, -1, 0);
						Features::PlaceObjectByHash(2475986526, -85.4054, -789.317, 328.666, -5.79433, -0, 17.1877, -1, 0);
						Features::PlaceObjectByHash(2475986526, -87.4651, -789.98, 328.647, -5.63204, -0, 20.2315, -1, 0);
						Features::PlaceObjectByHash(2475986526, -88.9795, -790.697, 328.76, -5.79416, -0, 25.9501, -1, 0);
						Features::PlaceObjectByHash(2475986526, -90.9922, -791.487, 328.684, -6.26149, -0, 27.0819, -1, 0);
						Features::PlaceObjectByHash(2475986526, -92.3298, -792.474, 328.677, -5.79412, -0, 33.3113, -1, 0);
						Features::PlaceObjectByHash(2475986526, -94.2322, -793.73, 328.669, -5.58479, -2.13443, 37.4974, -1, 0);
						Features::PlaceObjectByHash(2475986526, -95.7282, -795.2, 328.764, -5.79431, -0, 41.8672, -1, 0);
						Features::PlaceObjectByHash(2475986526, -97.9782, -797.316, 328.695, -5.58488, -0, 48.9171, -1, 0);
						Features::PlaceObjectByHash(2475986526, -100.042, -800.063, 328.731, -5.79425, 2.13443, 53.7039, -1, 0);
						Features::PlaceObjectByHash(2475986526, -101.884, -802.718, 328.706, -5.5848, 2.13443, 60.3613, -1, 0);
						Features::PlaceObjectByHash(2475986526, -103.09, -805.421, 328.718, -5.79425, -0, 64.506, -1, 0);
						Features::PlaceObjectByHash(2475986526, -104.284, -807.711, 328.691, -5.58488, -2.13443, 65.966, -1, 0);
						Features::PlaceObjectByHash(2475986526, -105.262, -810.369, 328.729, -5.26384, 1.06722, 73.2414, -1, 0);
						Features::PlaceObjectByHash(2475986526, -105.769, -812.146, 328.645, -5.25205, -1.06722, 75.8091, -1, 0);
						Features::PlaceObjectByHash(2475986526, -106.155, -814.128, 328.687, -5.26388, -1.06722, 82.8157, -1, 0);
						Features::PlaceObjectByHash(2475986526, -106.062, -817.685, 328.758, -5.26388, 2.66804, 88.7458, -1, 0);
						Features::PlaceObjectByHash(2475986526, -106.154, -819.723, 328.716, -5.25204, -0, 90.1628, -1, 0);
						Features::PlaceObjectByHash(2475986526, -106.082, -822.072, 328.729, -5.26387, -1.33402, 91.2972, -1, 0);
						Features::PlaceObjectByHash(2475986526, -105.911, -823.815, 328.7, -5.52135, 5.33608, 99.4393, -1, 0);
						Features::PlaceObjectByHash(2475986526, -105.28, -826.029, 328.734, -5.26391, 1.06722, 101.615, -1, 0);
						Features::PlaceObjectByHash(2475986526, -105.06, -827.904, 328.644, -5.29978, 1.06722, 102.515, -1, 0);
						Features::PlaceObjectByHash(2475986526, -104.327, -830.112, 328.614, -5.26391, -2.13443, 104.719, -1, 0);
						Features::PlaceObjectByHash(3291218330, -108.551, -853.416, 327.387, 2.94456, 89.1111, -166.155, -1, 0);
						Features::PlaceObjectByHash(3291218330, -80.2509, -866.418, 327.301, 3.7405, 89.3, 146.641, -1, 0);
						Features::PlaceObjectByHash(3291218330, -55.8513, -863.921, 327.333, 6.87468, 89.6184, 149.776, -1, 0);
						Features::PlaceObjectByHash(3291218330, -37.3907, -848.122, 327.717, 2.33633, 88.8797, -16.2595, -1, 0);
						Features::PlaceObjectByHash(3291218330, -26.1908, -818.332, 328.76, 0.490556, 84.6598, -18.107, -1, 0);
						Features::PlaceObjectByHash(3291218330, -37.891, -789.138, 328.134, 1.11673, 87.6571, 42.7186, -1, 0);
						Features::PlaceObjectByHash(3291218330, -63.492, -772.044, 327.866, 3.09962, 89.1556, 44.702, -1, 0);
						Features::PlaceObjectByHash(3291218330, -93.4916, -774.848, 327.398, 2.73771, 89.0443, 122.539, -1, 0);
						Features::PlaceObjectByHash(3291218330, -115.991, -795.259, 327.27, 3.28432, 89.2033, 123.086, -1, 0);
						Features::PlaceObjectByHash(3291218330, -122.551, -825.074, 327.213, 173.37, 89.6048, 4.27077, -1, 0);
						Features::PlaceObjectByHash(118627012, -74.8438, -819.617, 323.685, 0, 0, -3.37511, -1, 0);
						Features::PlaceObjectByHash(2475986526, -67.6253, -820.244, 323.793, -14.4263, -8.53774, -100.02, -1, 0);

					});
				}

				if (ImGui::Button("Maze-Bank Big Ramp"))
				{
					g_FiberScript->addTask([] {
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -74.94243f, -818.63446f, 326.174347f, 1, 0, 0, 1);

						Features::PlaceObjectByHash(1600026313, -78.4864, -807.943, 323.202, 109.364, -89.9209, 0, -1, 1);
						Features::PlaceObjectByHash(1600026313, -79.2766, -805.701, 323.204, 109.364, -89.9209, 0, -1, 1);
						Features::PlaceObjectByHash(1600026313, -79.8373, -803.709, 323.205, 109.364, -89.9209, 0, -1, 1);
						Features::PlaceObjectByHash(1600026313, -80.4295, -801.947, 323.207, 109.364, -89.9209, 0, -1, 1);
						Features::PlaceObjectByHash(4143853297, -97.4731, -778.557, 308.877, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(1087520462, -84.2429, -793.182, 321.08, -63.5625, -0, -160.249, -1, 1);
						Features::PlaceObjectByHash(1087520462, -83.5429, -795.106, 322.073, -63.5625, -0, -160.249, -1, 1);
						Features::PlaceObjectByHash(1087520462, -84.9429, -791.108, 319.956, -62.6673, 8.53774e-007, -160.249, -1, 1);
						Features::PlaceObjectByHash(1087520462, -85.8122, -788.585, 318.638, -63.5625, -0, -160.249, -1, 1);
						Features::PlaceObjectByHash(1087520462, -89.1589, -779.487, 313.336, -59.5389, 0.0405551, -160.567, -1, 1);
						Features::PlaceObjectByHash(1087520462, -90.7065, -774.863, 310.09, -57.4959, 0.322988, -160.758, -1, 1);
						Features::PlaceObjectByHash(1087520462, -91.4887, -772.564, 308.403, -55.1692, 0.383369, -161.049, -1, 1);
						Features::PlaceObjectByHash(1087520462, -91.7565, -771.74, 307.844, -56.4466, 0.0442451, -160.565, -1, 1);
						Features::PlaceObjectByHash(1087520462, -93.6941, -766.245, 302.736, -45.9996, 0.0556114, -160.556, -1, 1);
						Features::PlaceObjectByHash(1087520462, -94.2969, -764.648, 301.067, -44.7623, -1.70755e-006, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -94.2969, -764.648, 301.067, -44.7623, -1.70755e-006, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -94.886, -762.996, 298.741, -36.7051, -0, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -95.4855, -761.334, 296.406, -36.7051, -0, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -95.4855, -761.334, 296.406, -36.7051, -0, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -96.1606, -759.499, 294.259, -42.0766, -0, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -96.0707, -759.689, 293.709, -36.7051, -0, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -96.0707, -759.689, 293.709, -36.7051, -0, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -96.0707, -759.689, 293.46, -36.7051, -0, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -96.8807, -757.391, 292.506, -51.0291, -8.53774e-007, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -96.8807, -757.391, 292.506, -51.0291, -8.53774e-007, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -97.3203, -756.159, 291.688, -57.2958, -0, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -97.9597, -754.358, 290.78, -62.6673, 8.53774e-007, -160.249, -1, 1);
						Features::PlaceObjectByHash(1087520462, -97.9597, -754.358, 290.78, -62.6673, 8.53774e-007, -160.249, -1, 1);
						Features::PlaceObjectByHash(1087520462, -98.7192, -752.356, 290.042, -69.9278, 3.20165e-005, -160.249, -1, 1);
						Features::PlaceObjectByHash(1087520462, -99.0244, -751.684, 290.499, -90, -8.46346e-007, -160.249, -1, 1);
						Features::PlaceObjectByHash(1087520462, -99.3223, -750.534, 290.479, -90, -8.46346e-007, -160.249, -1, 1);
						Features::PlaceObjectByHash(1087520462, -100.348, -747.881, 290.452, -89.5256, -1.33402e-008, -159.354, -1, 1);
						Features::PlaceObjectByHash(1087520462, -100.26, -748.154, 290.462, -76.096, 4.26887e-007, 19.6954, -1, 1);
						Features::PlaceObjectByHash(1087520462, -100.687, -747.053, 290.731, -62.6673, -8.53774e-007, 20.5907, -1, 1);
						Features::PlaceObjectByHash(1087520462, -101.346, -745.387, 291.611, -58.191, 1.70755e-006, 19.6954, -1, 1);
						Features::PlaceObjectByHash(1087520462, -102.234, -743.119, 293.091, -52.2249, 0.00051141, 21.3426, -1, 1);
						Features::PlaceObjectByHash(2475986526, -102.154, -739.285, 294.83, 9.80014, 0.295618, 18.7802, -1, 1);
						Features::PlaceObjectByHash(2475986526, -105.054, -740.282, 294.827, 9.80014, 0.295618, 18.7802, -1, 1);
						Features::PlaceObjectByHash(1087520462, -103.071, -741.047, 294.832, -48.0666, 0.000519094, 21.3419, -1, 1);
						Features::PlaceObjectByHash(1087520462, -103.75, -739.405, 296.413, -45.1472, 0.000547269, 21.3416, -1, 1);
						Features::PlaceObjectByHash(4143853297, -90.3515, -798.112, 319.893, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -93.2293, -790.348, 317.189, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -95.3479, -784.483, 313.696, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -100.01, -771.31, 304.367, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -101.829, -766.277, 299.666, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -103.318, -762.175, 293.966, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -104.948, -757.681, 288.866, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -108.146, -748.798, 288.866, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -108.146, -748.798, 295.608, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -108.225, -748.694, 302.608, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(3167053133, -103.451, -740.541, 307.317, -0.900199, -1.19985, 20.9076, -1, 1);
						Features::PlaceObjectByHash(2375650849, -102.454, -742.6, 309.309, 0, 0, 20.9393, -1, 1);
						Features::PlaceObjectByHash(4143853297, -101.483, -746.044, 305.602, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -94.7458, -743.402, 295.608, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -94.7566, -743.406, 288.866, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -94.7426, -743.595, 302.651, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(1157292806, -99.7732, -750.516, 309.575, 0, 0, 24.1761, -1, 1);
						Features::PlaceObjectByHash(4143853297, -89.9785, -756.476, 293.966, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -91.5378, -752.285, 288.866, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -87.9094, -762.07, 299.666, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -86.2094, -766.939, 304.367, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -84.0215, -772.971, 309.575, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -81.6733, -779.348, 313.696, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -79.5187, -785.083, 317.189, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(4143853297, -76.5616, -793.191, 319.493, 0, -0, -159.831, -1, 1);
						Features::PlaceObjectByHash(1998517203, -81.0993, -790.139, 326.57, 0, 0, -82.6177, -1, 1);
						Features::PlaceObjectByHash(1998517203, -88.8988, -792.911, 326.95, 0, 0, -82.6177, -1, 1);
						Features::PlaceObjectByHash(803874239, -88.3376, -794.173, 327.042, 0, 0, 31.5501, -1, 1);
						Features::PlaceObjectByHash(803874239, -90.0376, -795.174, 327.262, 0, 0, 31.5501, -1, 1);
						Features::PlaceObjectByHash(803874239, -91.6375, -796.175, 327.482, 0, 0, 31.5501, -1, 1);
						Features::PlaceObjectByHash(803874239, -79.0283, -791.31, 326.763, 0, -0, 100.953, -1, 1);
						Features::PlaceObjectByHash(803874239, -76.8377, -790.87, 326.823, 0, -0, 100.953, -1, 1);
						Features::PlaceObjectByHash(803874239, -81.0088, -791.22, 326.713, 0, -0, 100.953, -1, 1);
					});
				}
				if (ImGui::Button("Beach Ramp"))
				{
					g_FiberScript->addTask([] {
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1513.0f, -1192.0f, 1.0f, 1, 0, 0, 1);
						Features::PlaceObjectByHash(1952396163, -1497.76, -1113.84, -3.08, -90, 6.14715e-007, 165.792, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1461.92, -1216.88, 2.5836, -2.3048, -0, -154.878, -1, 2);
						Features::PlaceObjectByHash(3291218330, -1465.62, -1217.64, 18, 166.516, -5.12264e-006, 24.1717, -1, 2);
						Features::PlaceObjectByHash(3291218330, -1458.89, -1214.4, 18, -38.4956, 8.53774e-007, -153.982, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1460.32, -1219.97, 4.3801, 12.6953, -0, -154.878, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1457, -1226.67, 11.8772, 31.7229, -0, -154.382, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1458.4, -1223.77, 7.9937, 23.6001, -0.0916355, -154.918, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1456.4, -1228.27, 14.9608, 48.674, -0, -153.982, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1456, -1229.07, 19.7441, 68.6628, -0, -153.982, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1456.2, -1228.47, 24.8276, 82.6252, 3.80938, -152.828, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1456.9, -1226.47, 28.9111, 108.498, -8.51368, -157.244, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1458.59, -1223.37, 31.5945, 130.616, -4.72983, -155.087, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1460.59, -1218.38, 33.5779, 143.744, -3.95611, -152.581, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1462.79, -1214.28, 34.161, 163.63, -2.68302, -155.763, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1465.3, -1209.78, 32.5228, -172.187, 4.69576e-006, -152.192, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1465.3, -1209.78, 32.5228, -172.187, 4.69576e-006, -152.192, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1466.9, -1205.68, 29.0062, -155.178, 9.47689e-005, -153.087, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1468.3, -1202.98, 24.1897, -131.11, 6.74481e-005, -153.088, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1468.59, -1202.68, 19.3732, -107.429, 3.07358e-005, -153.087, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1467.99, -1203.88, 13.5732, -89.6528, -0.153235, -155.853, -1, 2);
						Features::PlaceObjectByHash(2475986526, -1467.11, -1205.68, 10.7072, -63.5491, 8.53774e-007, -156.504, -1, 2);
						Features::PlaceObjectByHash(4109455646, -1465.05, -1210.03, 7.9503, 9.53319, 1.38057, 24.2606, -1, 2);
						Features::PlaceObjectByHash(2975320548, -1460.95, -1218.79, 7.66, -29.9323, -0.173323, 24.7221, -1, 2);
						Features::PlaceObjectByHash(2975320548, -1463.05, -1214.19, 6.7879, -6.50192, 1.391, 24.2651, -1, 2);
					});
				}
				if (ImGui::Button("Mount Chilliard Ramp"))
				{
					g_FiberScript->addTask([] {


						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 500, 5593, 795, 1, 0, 0, 1);
						Features::PlaceObjectByHash(1952396163, -1497.76, -1113.84, -3.08, -90, -0, 165.792, 90, 3);
						Features::PlaceObjectByHash(2475986526, -1461.92, -1216.88, 2.5836, -2.3048, 0, -154.878, 205.14, 3);
						Features::PlaceObjectByHash(3291218330, -1458.89, -1214.4, 18, -38.4956, 0, -153.982, 211.95, 3);
						Features::PlaceObjectByHash(2475986526, -1460.32, -1219.97, 4.3801, 12.6953, 0, -154.878, 205.672, 3);
						Features::PlaceObjectByHash(2975320548, -1463.05, -1214.19, 6.7879, -6.5, -1.391, 24.2651, 24.4244, 3);
						Features::PlaceObjectByHash(3291218330, -1465.62, -1217.64, 18, 166.516, 180, 24.1717, 155.224, 3);
						Features::PlaceObjectByHash(4109455646, -1465.05, -1210.03, 7.9503, 9.5304, -1.3806, 24.2606, 24.5148, 3);
						Features::PlaceObjectByHash(2975320548, -1460.95, -1218.79, 7.66, -29.9322, 0.1733, 24.7221, 27.9617, 3);
						Features::PlaceObjectByHash(2475986526, -1458.4, -1223.77, 7.9937, 23.6001, 0.0916, -154.918, 207.065, 3);
						Features::PlaceObjectByHash(2475986526, -1467.11, -1205.68, 10.7072, -63.5491, 0, -156.505, 224.303, 3);
						Features::PlaceObjectByHash(2475986526, -1457, -1226.67, 11.8772, 31.7229, 0, -154.382, 209.411, 3);
						Features::PlaceObjectByHash(2475986526, -1456.4, -1228.27, 14.9608, 48.674, 0, -153.982, 216.471, 3);
						Features::PlaceObjectByHash(2475986526, -1456, -1229.07, 19.7441, 68.6628, 0, -153.982, 233.298, 3);
						Features::PlaceObjectByHash(2475986526, -1456.2, -1228.47, 24.8276, 81.7043, -3.8094, -152.828, 252.429, 3);
						Features::PlaceObjectByHash(2475986526, -1456.9, -1226.47, 28.9111, 110.301, 171.486, -157.244, 312.201, 3);
						Features::PlaceObjectByHash(2475986526, -1458.59, -1223.37, 31.5945, 130.843, 175.27, -155.087, 325.759, 3);
						Features::PlaceObjectByHash(2475986526, -1460.59, -1218.38, 33.5779, 143.844, 176.044, -152.581, 327.979, 3);
						Features::PlaceObjectByHash(2475986526, -1462.79, -1214.28, 34.161, 163.648, 177.317, -155.763, 335.024, 3);
						Features::PlaceObjectByHash(2475986526, -1465.3, -1209.78, 32.5228, -172.187, -180, -152.192, 331.971, 3);
						Features::PlaceObjectByHash(2475986526, -1466.9, -1205.68, 29.0062, -155.178, -180, -153.087, 330.783, 3);
						Features::PlaceObjectByHash(2475986526, -1468.3, -1202.98, 24.1897, -131.11, -180, -153.088, 322.332, 3);
						Features::PlaceObjectByHash(2475986526, -1468.59, -1202.68, 19.3732, -107.429, -180, -153.087, 300.544, 3);
						Features::PlaceObjectByHash(2475986526, -1467.99, -1203.88, 13.5732, -89.6205, 0.1532, -155.853, 269.072, 3);
						Features::PlaceObjectByHash(3966705493, 509.842, 5589.24, 791.066, 0.141, 0, 65.3998, 65.3999, 3);
						Features::PlaceObjectByHash(3966705493, 520.5, 5584.38, 790.503, 5.441, 0, 65.3998, 65.4976, 3);
						Features::PlaceObjectByHash(3966705493, 531.057, 5579.54, 788.691, 12.441, 0, 65.3998, 65.9111, 3);
						Features::PlaceObjectByHash(3966705493, 568.672, 5562.32, 767.428, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 576.972, 5558.53, 759.566, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 560.174, 5566.2, 774.698, 35.0403, 0, 65.3998, 69.4512, 3);
						Features::PlaceObjectByHash(3966705493, 541.325, 5574.84, 785.49, 19.4409, 0, 65.3998, 66.6484, 3);
						Features::PlaceObjectByHash(3966705493, 551.066, 5570.37, 780.799, 27.5407, 0, 65.3998, 67.9049, 3);
						Features::PlaceObjectByHash(3966705493, 585.249, 5554.75, 751.745, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 618.334, 5539.62, 720.386, 40.7936, 0, 65.3998, 70.8829, 3);
						Features::PlaceObjectByHash(3966705493, 626.602, 5535.85, 712.547, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 610.065, 5543.4, 728.217, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 601.777, 5547.19, 736.076, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 593.507, 5550.97, 743.917, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 634.862, 5532.07, 704.725, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 643.121, 5528.29, 696.894, 40.7936, 0, 65.3998, 70.8829, 3);
						Features::PlaceObjectByHash(3966705493, 651.391, 5524.51, 689.053, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 659.651, 5520.73, 681.221, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 667.911, 5516.94, 673.389, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 676.171, 5513.17, 665.558, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 684.431, 5509.38, 657.727, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 692.691, 5505.61, 649.905, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 700.95, 5501.83, 642.074, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 709.22, 5498.05, 634.243, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 717.46, 5494.28, 626.431, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 725.72, 5490.5, 618.6, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 733.98, 5486.72, 610.778, 40.7396, 0, 65.3998, 70.8685, 3);
						Features::PlaceObjectByHash(3966705493, 742.6, 5482.78, 603.167, 36.9395, 0, 65.3998, 69.9005, 3);
						Features::PlaceObjectByHash(3966705493, 751.83, 5478.55, 596.335, 31.0392, 0, 65.3998, 68.5807, 3);
						Features::PlaceObjectByHash(3966705493, 761.71, 5474.02, 590.613, 24.5989, 0, 65.3998, 67.3986, 3);
						Features::PlaceObjectByHash(3966705493, 772.07, 5469.28, 586.08, 18.9288, 0, 65.3998, 66.5835, 3);
						Features::PlaceObjectByHash(3966705493, 782.84, 5464.34, 582.86, 11.5788, 0, 65.3998, 65.8427, 3);
						Features::PlaceObjectByHash(3966705493, 793.89, 5459.28, 581.117, 5.0787, 0, 65.3998, 65.485, 3);
						Features::PlaceObjectByHash(3966705493, 805.1, 5454.15, 580.876, -2.5212, 0, 65.3998, 65.4208, 3);
						Features::PlaceObjectByHash(3966705493, 816.17, 5449.08, 581.975, -7.6213, 0, 65.3998, 65.5917, 3);
						Features::PlaceObjectByHash(3966705493, 827.191, 5444.04, 584.582, -16.6212, 0, 65.3998, 66.3125, 3);
						Features::PlaceObjectByHash(3966705493, 837.681, 5439.24, 588.899, -24.421, 0, 65.3998, 67.3698, 3);
						Features::PlaceObjectByHash(2580877897, 522.61, 5584.49, 779.214, 79.7153, -9.2252, 55.7018, 77.7612, 3);
						Features::PlaceObjectByHash(3862788492, 522.445, 5583.69, 779.551, -0.9197, -69.229, -167.468, 184.555, 3);

					});
				}

				if (ImGui::Button("Airport Ramp"))
				{
					g_FiberScript->addTask([] {

						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1208, -2950, 13, 1, 0, 0, 1);
						Features::PlaceObjectByHash(2475986526, -1242.08, -2931.15, 12.9924, -0.1046, -3.33505e-009, 61.0607, -1, 4);
						Features::PlaceObjectByHash(2475986526, -1247.11, -2928.46, 15.013, -0.1046, -3.33505e-009, 61.0607, -1, 4);
						Features::PlaceObjectByHash(2475986526, -1251.58, -2926.05, 16.7865, -0.1046, -3.33505e-009, 61.0607, -1, 4);
						Features::PlaceObjectByHash(2475986526, -1254.69, -2924.35, 18.25, -0.1046, -3.33505e-009, 61.0607, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1276.69, -2912.99, 23.0019, 0, 0.05, 60.9705, -1, 4);
						Features::PlaceObjectByHash(2475986526, -1258.35, -2922.28, 20.2135, -0.1046, -3.33505e-009, 61.0607, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1270.89, -2916.22, 23.0123, 0, 0, 60.8909, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1270.25, -2914.99, 23.0137, 0, 0, 60.8909, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1274.87, -2909.4, 23.0049, 0, 0.05, 60.9705, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1269.01, -2912.64, 22.9993, 0, 0.05, 60.9705, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1267.87, -2915.44, 28.3632, 0, -0, 147.299, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1272.13, -2918.33, 28.4791, 0, 0.05, 60.9705, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1272.11, -2918.35, 25.6708, -0.48, 0.0499982, 60.9701, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1277.93, -2915.14, 25.604, 0, 0.05, 60.9705, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1279.69, -2909.85, 25.6358, 0, -0, -151.239, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1279.69, -2909.85, 28.4844, 0, -0, -151.239, -1, 4);
						Features::PlaceObjectByHash(2475986526, -1261.82, -2920.38, 21.767, -0.1046, -3.33505e-009, 61.0607, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1273.65, -2907.11, 22.9763, 0, 0.05, 60.9705, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1267.77, -2910.37, 22.9978, 0, 0.05, 60.9705, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1266.49, -2908.08, 22.9987, 0, -0, -119.462, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1265.15, -2905.8, 23.0042, 0, -0, -119.462, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1266.44, -2905.21, 25.6255, 0, -0, -118.761, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1265.66, -2911.99, 25.6968, 0, 0, -30.9603, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1264.88, -2910.66, 25.6982, 0, 0, -30.9603, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1264.84, -2905.14, 25.624, 0, -0, -118.761, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1272.37, -2900.96, 25.6199, 0, -0, -118.761, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1276.35, -2903.91, 25.6214, 0, -0, -151.239, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1276.35, -2903.91, 28.4329, 0, -0, -151.239, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1272.37, -2900.96, 28.4385, 0, -0, -118.761, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1266.44, -2905.21, 28.437, 0, -0, -118.761, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1265.17, -2905.14, 28.3426, 0, -0, -118.861, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1271.09, -2902.58, 23.0057, 0, -0, -119.462, -1, 4);
						Features::PlaceObjectByHash(3966705493, -1272.37, -2904.83, 22.9972, 0, -0, -119.462, -1, 4);

					});
				}


				if (ImGui::Button("Airport Ramp 2"))
				{
					g_FiberScript->addTask([] {


						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1046, -2538, 20, 1, 0, 0, 1);
						Features::PlaceObjectByHash(2475986526, -1098.36, -2631.17, 19, 0, -0, 152.671, -1, 5);
						Features::PlaceObjectByHash(2475986526, -1100.26, -2634.64, 21.1976, 16.2002, 0.192059, 150.427, -1, 5);
						Features::PlaceObjectByHash(2475986526, -1102.26, -2638.02, 25.01, 26.7003, 0.178675, 149.261, -1, 5);
						Features::PlaceObjectByHash(2475986526, -1103.96, -2640.91, 29.04, 28.3717, -0, 146.82, -1, 5);
						Features::PlaceObjectByHash(1952396163, -1119.61, -2670.96, -5.125, 0, -0, 150.514, -1, 5);
						Features::PlaceObjectByHash(1952396163, -1119.61, -2670.96, -5.125, 0, -0, 150.401, -1, 5);
						Features::PlaceObjectByHash(3137065507, -1044.69, -2530.08, 20.4011, 94.8962, 4.26887e-007, 147.716, -1, 5);

					});
				}


				if (ImGui::Button("Ufo Tower"))
				{
					g_FiberScript->addTask([] {

						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 70, -674, 680, 1, 0, 0, 1);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 654.365, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 646.186, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 638.008, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 629.829, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 621.65, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 613.471, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 605.292, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 597.114, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 588.935, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 580.756, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 572.577, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 564.399, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 556.22, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 662.544, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 548.041, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 539.862, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 531.683, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 523.505, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 515.326, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 507.147, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 498.968, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 490.79, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 482.611, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 474.432, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 466.253, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 458.074, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 449.896, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 441.717, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 433.538, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 425.359, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 417.18, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 409.001, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 400.823, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 392.644, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 384.465, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 376.286, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 368.107, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 359.929, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 351.75, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 343.571, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 335.392, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 327.213, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 319.035, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 310.856, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 302.677, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 294.498, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 286.319, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 278.141, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 269.962, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 261.783, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 253.604, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 245.425, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 237.247, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 229.068, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 220.889, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 212.71, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 204.531, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 196.353, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 188.174, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 179.995, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 171.816, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 163.637, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 155.459, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 147.28, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 139.101, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 130.922, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 122.743, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 114.565, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 106.386, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 98.207, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 90.0282, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 81.8494, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 73.6706, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 65.4918, 0.660085, -0.919939, -109.32, -1, 6);
						Features::PlaceObjectByHash(3026699584, 70.2592, -674.044, 57.313, 0.660085, -0.919939, -109.32, -1, 6);

					});
				}





				if (ImGui::Button("Halfpipe"))
				{
					g_FiberScript->addTask([] {
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1003, -2916, 14, 1, 0, 0, 1);
						Features::PlaceObjectByHash(3681122061, -1018.78, -2937.26, 12.9646, 0, 0, -30.3132, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1023.38, -2945.17, 12.9646, 0, 0, -30.3132, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1028.02, -2953.13, 12.9646, 0, 0, -30.3132, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1032.66, -2961.06, 12.9646, 0, 0, -30.3132, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1037.32, -2969.04, 12.9646, 0, 0, -30.3132, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1041.95, -2976.96, 12.9646, 0, 0, -30.3132, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1046.18, -2984.19, 12.9646, 0, 0, -30.3132, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1050.78, -2992.12, 12.9646, 0, 0, -29.8732, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1053.22, -2998.13, 12.9646, 0, 0, -14.2534, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1054.14, -3005.28, 12.9646, 0, 0, -0.613478, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1053.45, -3012.85, 12.9646, 0, 0, 11.4866, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1051.19, -3020.08, 12.9646, 0, 0, 23.3667, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1047.43, -3026.73, 12.9646, 0, 0, 35.2469, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1042.42, -3032.37, 12.9646, 0, 0, 47.7871, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1037.1, -3038.16, 12.9646, 0, 0, 37.2273, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1033.11, -3044.75, 12.9646, 0, 0, 25.5675, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1030.43, -3052.11, 12.9646, 0, 0, 14.5676, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1029.18, -3059.85, 12.9646, 0, 0, 4.00757, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1029.37, -3067.7, 12.9646, 0, 0, -6.55247, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1031, -3075.33, 12.9646, 0, 0, -17.5525, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1034.09, -3082.35, 12.9646, 0, 0, -29.6525, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1038.6, -3088.77, 12.9646, 0, 0, -40.2127, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1044.19, -3094.15, 12.9646, 0, 0, -51.653, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1050.65, -3098.2, 12.9646, 0, 0, -63.7531, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1057.89, -3100.91, 12.9646, 0, 0, -75.1935, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1065.18, -3101.87, 12.9646, 0, 0, -89.7139, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1073.03, -3101.2, 12.9646, 0, -0, -100.054, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1080.63, -3099.11, 12.9646, 0, -0, -110.615, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1087.92, -3095.65, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1095.95, -3091.03, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1104.01, -3086.4, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1112.04, -3081.79, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1120.04, -3077.19, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1128.1, -3072.56, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1136.15, -3067.93, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1144.2, -3063.31, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1152.22, -3058.7, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1160.24, -3054.09, 12.9646, 0, -0, -119.855, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1168.22, -3049.48, 12.9646, 0, -0, -120.295, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1176.21, -3044.8, 12.9646, 0, -0, -120.295, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1183.28, -3040.14, 12.9646, 0, -0, -126.455, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1189.23, -3034.89, 12.9646, 0, -0, -136.356, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1193.86, -3028.84, 12.9646, 0, -0, -148.677, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1197.2, -3021.86, 12.9646, 0, -0, -159.898, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1198.78, -3014.77, 12.9646, 0, -0, -174.639, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1198.72, -3007.04, 12.9646, 0, -0, 173.701, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1197, -2999.97, 12.9646, 0, -0, 158.962, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1193.5, -2993.3, 12.9646, 0, -0, 145.982, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1188.51, -2987.1, 12.9646, 0, -0, 136.083, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1182.5, -2981.85, 12.9646, 0, -0, 126.183, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1175.98, -2978.23, 12.9646, 0, -0, 112.104, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1168.67, -2976.15, 12.9646, 0, -0, 99.7843, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1160.82, -2975.53, 12.9646, 0, 0, 89.4449, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1152.93, -2976.29, 12.9646, 0, 0, 79.5455, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1145.21, -2978.39, 12.9646, 0, 0, 70.0859, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1138.14, -2981.75, 12.9646, 0, 0, 59.0863, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1130.27, -2986.43, 12.9646, 0, 0, 59.0863, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1122.46, -2991.09, 12.9646, 0, 0, 59.0863, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1115.12, -2994.75, 12.9646, 0, 0, 67.1435, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1107.63, -2997.13, 12.9646, 0, 0, 76.9913, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1099.8, -2998.14, 12.9646, 0, 0, 86.8389, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1091.94, -2997.76, 12.9646, 0, -0, 97.5819, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1084.47, -2995.95, 12.9646, 0, -0, 108.325, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1077.64, -2992.78, 12.9646, 0, -0, 119.963, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1077.64, -2992.78, 12.9646, 0, -0, 119.963, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1071.68, -2988.3, 12.9646, 0, -0, 132.496, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1066.33, -2982.53, 12.9646, 0, -0, 141.449, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1053.01, -2960.01, 12.9646, 0, 0, -28.5532, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1048.58, -2951.88, 12.9646, 0, 0, -28.5532, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1044.16, -2943.76, 12.9646, 0, 0, -28.5532, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1039.74, -2935.64, 12.9646, 0, 0, -28.5532, -1, 9);
						Features::PlaceObjectByHash(3681122061, -1035.5, -2927.86, 12.9646, 0, 0, -28.5532, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1063.23, -2993.67, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1067.37, -2998.06, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1063.7, -2994.67, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1064.21, -2995.73, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1064.71, -2996.8, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1065.21, -2997.84, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1067.1, -2999.45, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1065.43, -3000.24, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1068.29, -3000.06, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1065.92, -3001.18, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1066.44, -3002.28, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1065.35, -3002.77, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1065.6, -3003.96, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1066.11, -3005.04, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1064.21, -2999.56, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1069.53, -3000.82, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1070.75, -3001.52, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1068.76, -3002.46, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1069.29, -3003.54, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1068.44, -3005.23, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1071.58, -3003.74, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(2475986526, -1072.98, -3006.81, 16.0846, 0, 0, -26.0348, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1072.44, -3002.05, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1073.73, -3002.72, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(2475986526, -1076.54, -3005.07, 16.0846, 0, 0, -26.0348, -1, 9);
						Features::PlaceObjectByHash(2475986526, -1078.92, -3009.92, 13.7046, 0, 0, -26.0348, -1, 9);
						Features::PlaceObjectByHash(2475986526, -1075.31, -3011.69, 13.7046, 0, 0, -26.0348, -1, 9);
						Features::PlaceObjectByHash(2475986526, -1069.34, -3008.59, 16.0846, 0, 0, -26.0348, -1, 9);
						Features::PlaceObjectByHash(2475986526, -1071.71, -3013.45, 13.7046, 0, 0, -26.0348, -1, 9);
						Features::PlaceObjectByHash(2475986526, -1068.14, -3015.2, 13.7046, 0, 0, -26.0348, -1, 9);
						Features::PlaceObjectByHash(3608473212, -1065.36, -3006.66, 15.3449, 0, 0, -25.1145, -1, 9);
						Features::PlaceObjectByHash(2475986526, -1065.75, -3010.35, 16.0846, 0, 0, -26.0348, -1, 9);



					});
				}


				if (ImGui::Button("Airport Loop Ramp"))
				{
					g_FiberScript->addTask([] {
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1074, -3201, 13, 1, 0, 0, 1);
						Features::PlaceObjectByHash(3966705493, -1041.89, -3219.51, 10.1797, -2.43331, 5.32208, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1037.79, -3221.47, 10.3641, -2.43331, 5.32208, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1034.16, -3223.3, 10.5366, -2.43331, 5.32208, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1036.76, -3219.45, 10.1526, -2.43331, 5.32208, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1033.12, -3221.28, 10.3251, -2.43331, 5.32208, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1029.37, -3225.6, 11.1956, -11.6033, 5.32207, 62.9335, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1028.33, -3223.58, 10.9842, -11.6033, 5.32207, 62.9335, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1024.27, -3225.54, 12.1104, -18.1533, 5.32205, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1025.44, -3227.83, 12.3497, -18.1533, 5.32205, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1020.36, -3230.06, 15.7972, -40.4234, 5.32214, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1019.22, -3227.83, 15.5634, -40.4234, 5.32214, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1014.85, -3229.56, 20.4393, -50.9034, 5.3221, 62.9337, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1016.07, -3231.95, 20.6898, -50.9034, 5.3221, 62.9337, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1012.88, -3232.96, 26.0664, -64.0034, 5.32209, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1011.63, -3230.51, 25.8104, -64.0034, 5.32209, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1009.27, -3231.06, 32.0819, -73.1735, 5.32204, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1010.52, -3233.51, 32.3379, -73.1735, 5.32214, 62.9337, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1009.36, -3233.48, 38.2311, -83.6535, 5.32208, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1008.09, -3230.98, 37.9695, -83.6535, 5.32208, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1007.71, -3230.43, 44.185, -92.8235, 6.63212, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1009.05, -3228.93, 49.9682, -119.024, 6.63217, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1008.93, -3232.81, 44.4969, -92.8235, 6.63212, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1010.27, -3231.31, 50.2801, -119.024, 6.63217, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1011.96, -3226.91, 54.0691, -142.604, 6.6321, 62.9337, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1013.1, -3229.14, 54.3602, -142.604, 6.6321, 62.9337, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1017.49, -3226.51, 57.2125, -159.634, 6.63211, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1022.14, -3223.91, 58.9186, -168.804, 6.63213, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1035.97, -3216.05, 58.7162, 155.826, 1.39214, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1031.37, -3218.71, 60.1775, 176.786, 6.63213, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1026.33, -3221.63, 59.8766, -168.804, 6.63212, 60.3136, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1020.98, -3221.63, 58.6206, -168.804, 6.63213, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1024.97, -3219.25, 59.5578, -168.804, 6.63212, 60.3136, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1016.33, -3224.24, 56.9145, -159.634, 6.63211, 62.9336, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1029.99, -3216.28, 59.8517, 176.786, 6.63213, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1029.99, -3216.28, 59.8517, 176.786, 6.63213, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1034.73, -3213.86, 58.655, 155.826, 1.39214, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1039.18, -3211.42, 55.2255, 138.796, 1.39206, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1039.18, -3211.42, 55.2255, 138.796, 1.39206, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1040.42, -3213.61, 55.2867, 138.796, 1.39206, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1044.34, -3211.51, 50.6082, 128.316, 1.39213, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1043.09, -3209.33, 50.547, 128.316, 1.39213, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1046.16, -3207.74, 45.1535, 117.837, 1.39215, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1048.17, -3206.74, 39.6252, 104.737, 1.39214, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1048.92, -3206.44, 33.1586, 87.6005, 0.0914728, 60.6227, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1048.18, -3206.88, 26.5446, 77.3408, 0.0913896, 60.6229, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1049.44, -3209.13, 26.5487, 77.3407, 0.0913427, 60.6228, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1047.3, -3210.37, 21.3947, 56.6411, 0.0914017, 58.823, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1047.3, -3210.37, 21.3947, 56.6411, 0.0914017, 58.823, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1045.93, -3208.12, 21.3905, 56.6411, 0.0914017, 58.823, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1042.61, -3210.12, 16.8766, 42.1517, 0.0913785, 58.8231, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1038.64, -3212.63, 13.6141, 28.2018, 0.0914187, 58.8231, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1039.97, -3214.83, 13.6182, 28.2018, 0.0914187, 58.8231, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1034.82, -3217.71, 11.1985, 16.4116, 0.0913871, 69.303, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1033.53, -3215.55, 11.1081, 16.4117, 0.0913619, 66.683, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1043.97, -3212.37, 16.8808, 42.1517, 0.0913785, 58.8231, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1050.19, -3208.69, 33.1627, 87.6005, 0.0914728, 60.6227, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1049.45, -3208.98, 39.6879, 104.737, 1.39214, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1047.44, -3209.98, 45.2161, 117.837, 1.39215, 60.3137, -1, 10);
						Features::PlaceObjectByHash(3966705493, -1047.44, -3209.98, 45.2161, 117.837, 1.39215, 60.3137, -1, 10);




					});
				}


				if (ImGui::Button("Airport Ramp"))
				{
					g_FiberScript->addTask([] {
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -74.94243f, -818.63446f, 326.174347f, 1, 0, 0, 1);
						Features::PlaceObjectByHash(3681122061, -82.9657, -818.944, 325.175, 0, -0, 91.03, -1, 11);
						Features::PlaceObjectByHash(3681122061, -91.0941, -819.089, 322.355, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -98.36, -819.224, 316.632, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -105.626, -819.358, 310.91, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -112.892, -819.492, 305.187, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -120.158, -819.626, 299.464, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -127.424, -819.761, 293.741, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -134.69, -819.895, 288.018, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -141.956, -820.029, 282.296, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -149.222, -820.163, 276.573, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -156.487, -820.298, 270.85, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -163.753, -820.432, 265.127, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -171.019, -820.566, 259.404, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -178.285, -820.701, 253.682, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -185.551, -820.835, 247.959, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -192.817, -820.969, 242.236, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -200.083, -821.103, 236.513, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -207.349, -821.238, 230.79, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -214.615, -821.372, 225.068, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -221.881, -821.506, 219.345, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -229.147, -821.641, 213.622, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -236.413, -821.775, 207.899, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -243.679, -821.909, 202.176, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -250.945, -822.043, 196.453, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -258.21, -822.178, 190.731, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -265.476, -822.312, 185.008, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -287.274, -822.715, 167.839, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -280.008, -822.58, 173.562, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -272.742, -822.446, 179.285, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -294.54, -822.849, 162.117, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -301.806, -822.983, 156.394, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -309.072, -823.118, 150.671, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -316.338, -823.252, 144.948, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -323.604, -823.386, 139.225, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -330.87, -823.52, 133.503, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -338.136, -823.655, 127.78, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -345.402, -823.789, 122.057, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -352.668, -823.923, 116.334, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -359.934, -824.057, 110.611, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -367.199, -824.192, 104.889, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -374.465, -824.326, 99.1657, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -381.731, -824.46, 93.4429, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -388.997, -824.595, 87.7201, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -396.263, -824.729, 81.9973, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -403.529, -824.863, 76.2745, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -411.479, -825.022, 68.7971, -19.78, -3.43377e-005, 91.1094, -1, 11);
						Features::PlaceObjectByHash(3681122061, -410.795, -824.997, 70.5517, -38.2199, 0.00787841, 91.0529, -1, 11);
						Features::PlaceObjectByHash(3681122061, -411.96, -825.029, 69.097, -27.6, 1.15259e-005, 91.1095, -1, 11);
						Features::PlaceObjectByHash(3681122061, -412.719, -825.046, 67.8516, -10.58, -2.92151e-006, 91.1095, -1, 11);
						Features::PlaceObjectByHash(3681122061, -413.903, -825.068, 67.2075, -3.21999, 5.66959e-007, 91.1095, -1, 11);
						Features::PlaceObjectByHash(3681122061, -415.378, -825.099, 66.7734, 3.68002, -4.58236e-006, 91.1095, -1, 11);
						Features::PlaceObjectByHash(3681122061, -416.883, -825.126, 66.57, 9.66002, -8.44435e-006, 91.1096, -1, 11);
						Features::PlaceObjectByHash(3681122061, -418.526, -825.157, 66.5571, 15.64, -1.80093e-005, 91.1095, -1, 11);
						Features::PlaceObjectByHash(3681122061, -419.945, -825.184, 66.6727, 20.7001, 8.69782e-006, 91.1094, -1, 11);
						Features::PlaceObjectByHash(3681122061, -421.727, -825.218, 67.0936, 25.7601, -2.09975e-005, 91.1095, -1, 11);
						Features::PlaceObjectByHash(3681122061, -422.006, -825.234, 66.966, 30.8199, 0.114757, 90.6829, -1, 11);
						Features::PlaceObjectByHash(3681122061, -429.913, -825.328, 71.6856, 30.8199, 0.114757, 90.6829, -1, 11);



					});
				}






				ImGui::EndChild();
				ImGui::PopStyleVar();
			}

			break;





			case 12:

			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("basicall", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Basic Options"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}

				if (ImGui::TreeNode("Remote Teleport"))
				{


					if (ImGui::Button("Cayo Perico"))
					{
						g_FiberScript->addTask([] {
							for (int i = 0; i < 32; i++)
							{


								uint64_t args[3] = { CayoPericoTeleport , i, 1300962917 };

								Hooks::TriggerScriptEvent(1, args, 3, 1 << i);
							}
						});
					}

					if (ImGui::Button("Eclipse Tower"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport1(true);
						});

					}

					if (ImGui::Button("West Vinewood"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport2(true);
						});
					}

					if (ImGui::Button("Las Lagunas"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport3(true);
						});
					}


					if (ImGui::Button("Spanish Ave"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport4(true);
						});
					}

					if (ImGui::Button("Power St"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport5(true);
						});
					}
					if (ImGui::Button("Del Perro"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport6(true);
						});
					}
					if (ImGui::Button("Milton Rd"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport7(true);
						});
					}

					if (ImGui::Button("The Royale"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport8(true);
						});
					}
					if (ImGui::Button("La Puerta"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport9(true);
						});
					}
					if (ImGui::Button("Rockford Dr"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport10(true);
						});
					}

					if (ImGui::Button("Dream Tower"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport11(true);
						});
					}
					if (ImGui::Button("San Vitas"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport12(true);
						});
					}
					if (ImGui::Button("Vespucci Blvd"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport13(true);
						});
					}
					if (ImGui::Button("Cougar Ave"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport14(true);
						});
					}
					if (ImGui::Button("Prosperity St"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport15(true);
						});
					}

					if (ImGui::Button("Weazel Plaza"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport16(true);
						});
					}
					if (ImGui::Button("Del Perro Office"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport17(true);
						});
					}
					if (ImGui::Button("Maze Bank West Office"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport18(true);
						});
					}
					if (ImGui::Button("Arcadius Office"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport19(true);
						});
					}

					if (ImGui::Button("Maze Bank Office"))
					{
						g_FiberScript->addTask([] {
							Features::Teleport19(true);
						});
					}



					ImGui::TreePop();
				}

				ImGui::Checkbox("Line ESP", &Features::espbool);
				ImGui::Checkbox("Nametag ESP", &Features::Nametag);


				ImGui::Checkbox("Water Loop All Player", &Features::WaterAll);
				ImGui::Checkbox("Fire Loop All Player", &Features::FireAll);
				ImGui::Checkbox("Freeze All Player", &Features::FreezeAll);




				ImGui::Checkbox("Crash Lobby", &Features::CrashLobbyBool);
				ImGui::Checkbox("Show all Player on Radar", &Features::ShowAllPlayerRadarBool);






				if (ImGui::Button("Cage All Player"))
				{
					cageallplayer = true;
				}






				ImGui::EndChild();
				ImGui::PopStyleVar();
			}
			ImGui::SameLine(0.0f, 380.0f);

			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("Drop Options", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Drop Options"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}

				ImGui::Checkbox("Enable All Player Money Drop", &Features::ALLMoneyDropBool);
				ImGui::SliderInt("Money Drop Amount", &Features::DropAmount, 0, 2500);
				ImGui::SliderInt("Money Drop Delay", &Features::BagDelay, 0, 5000);





				ImGui::EndChild();
				ImGui::PopStyleVar();
			}






				break;



			case 10:






				if (ImGui::ListBoxHeader("##empty", ImVec2(210, 200))) {
					try
					{
						for (int i = 0; i < 32; ++i) {
								if (ImGui::Selectable(PLAYER::GET_PLAYER_NAME(i)))
									g_SelectedPlayer = i;

							//if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))

						}
						ImGui::ListBoxFooter();
					}
					catch (...)
					{
						g_Logger->Info("Error on Playerlist!");
					}
				}
				





					ImGui::SameLine(0.0, 120.0f);




					{
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
						ImGui::BeginChild("playerlistinfo", ImVec2(700, 200), true, ImGuiWindowFlags_MenuBar);
						if (ImGui::BeginMenuBar())
						{
							if (ImGui::BeginMenu("Player Information"))
							{
								ImGui::EndMenu();
							}
							ImGui::EndMenuBar();
						}
						ImGui::Columns(3);






						ImGui::Text("Name: "); ImGui::SameLine(); ImGui::Text(Features::Name);

						ImGui::Text("IP: "); ImGui::SameLine(); ImGui::Text(PlayerIP.c_str());
						ImGui::Text("Port: "); ImGui::SameLine(); ImGui::Text(port_str.c_str());

						ImGui::Text("RID: "); ImGui::SameLine(); ImGui::Text(Features::RID);

						ImGui::Text("Godmode: "); ImGui::SameLine(); ImGui::Text(Features::GodeModeInfo);

						ImGui::Text("Wanted Level: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}", Features::Wanted).c_str());

						ImGui::Text("Street: "); ImGui::SameLine(); ImGui::Text(Features::Street);
						ImGui::Text("Zone: "); ImGui::SameLine(); ImGui::Text(Features::Zone);

						ImGui::Text("Vehicle: "); ImGui::SameLine(); ImGui::Text(Features::Veh);

						ImGui::NextColumn();
						
						ImGui::Text("Armor: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}%", armorper).c_str());

						ImGui::Text("Money: "); ImGui::SameLine(); ImGui::Text(fmt::format("${0}", money).c_str());

						ImGui::Text("Bank: "); ImGui::SameLine(); ImGui::Text(fmt::format("${0}", bank).c_str());

						ImGui::Text("RP: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}", rp).c_str());
						ImGui::Text("Rank: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}", rank).c_str());
						ImGui::Text("Kills: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}", kills2).c_str());
						ImGui::Text("Deaths: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}", deaths2).c_str());
						ImGui::Text("Races-Won: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}", raceswon).c_str());
						ImGui::NextColumn();
						ImGui::Text("Races-Lost: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}", raceslost).c_str());
						ImGui::Text("Earnings: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}", earnings).c_str());
						ImGui::Text("KD: "); ImGui::SameLine(); ImGui::Text(fmt::format("{0}", kd).c_str());
						ImGui::EndChild();
						ImGui::PopStyleVar();


					}
					ImGui::NewLine();
					ImGui::SameLine(0.0, 335.0f);



					if (ImGui::Button("Reload Playerstats"))
					{
						Features::UpdateInfo = true;
					}


				{
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("basicpmenu", ImVec2(500, 150), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
						{
							if (ImGui::BeginMenu("Basic Options"))
								{
									ImGui::EndMenu();
								}
							ImGui::EndMenuBar();
							}

					if (ImGui::TreeNode("Teleport Options"))
					{
						if (ImGui::Button("TP to Player"))
						{
							tptoplayer = true;

						}
						if (ImGui::Button("TP into Vehicle"))
						{
							tpintoveh = true;
						}

						if (ImGui::Button("TP Player to you (Vehicle needed)"))
						{

							Features::TPToMeBool = true;
						}

						ImGui::TreePop();

					}


							ImGui::Checkbox("Spectate Player", &Features::SpectateList);
							ImGui::Checkbox("Water Loop", &Features::WaterList[g_SelectedPlayer]);
							ImGui::Checkbox("Fire Loop", &Features::FireList[g_SelectedPlayer]);


							ImGui::Checkbox("Freeze", &Features::FreezeList[g_SelectedPlayer]);
							ImGui::Checkbox("Explode Loop", &Features::ExplodeList[g_SelectedPlayer]);
							ImGui::Checkbox("Fuck his cam", &Features::FuckCamBool);

							if (ImGui::Button("Airstrike"))
							{
								airstrike = true;
							}
							if (ImGui::Button("Ram Player"))
							{
								ramplayer = true;
							}
							if (ImGui::Button("Kick out of car"))
							{
								kickoutcar = true;
							}

							if (ImGui::Button("Give Godmode"))
							{
								g_FiberScript->addTask([] {
									Hash oball = GAMEPLAY::GET_HASH_KEY("prop_juicestand");
									STREAMING::REQUEST_MODEL(oball);

									Object orangeball;
									orangeball = OBJECT::CREATE_OBJECT(oball, 0, 0, 0, true, 1, -1, &orangeball, true, false, false);

									RequestControlOfEnt(orangeball);
									ENTITY::SET_ENTITY_VISIBLE(orangeball, 0, 0);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(orangeball, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
								});
							}


							if (ImGui::TreeNode("Remote Teleport"))
							{


								if (ImGui::Button("Cayo Perico"))
								{
									//0x4d8b1e65
									g_FiberScript->addTask([] {
										uint64_t args[3] = { CayoPericoTeleport , g_SelectedPlayer, 1300962917 };

										Hooks::TriggerScriptEvent(1, args, 3, 1 << g_SelectedPlayer);
									});
								}

								if (ImGui::Button("Eclipse Tower"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport1(false);
									});
								}

								if (ImGui::Button("West Vinewood"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport2(false);
									});
								}

								if (ImGui::Button("Las Lagunas"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport3(false);
									});
								}


								if (ImGui::Button("Spanish Ave"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport4(false);
									});
								}

								if (ImGui::Button("Power St"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport5(false);
									});
								}
								if (ImGui::Button("Del Perro"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport6(false);
									});
								}
								if (ImGui::Button("Milton Rd"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport7(false);
									});
								}

								if (ImGui::Button("The Royale"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport8(false);
									});
								}
								if (ImGui::Button("La Puerta"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport9(false);
									});
								}
								if (ImGui::Button("Rockford Dr"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport10(false);
									});
								}

								if (ImGui::Button("Dream Tower"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport11(false);
									});
								}
								if (ImGui::Button("San Vitas"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport12(false);
									});
								}
								if (ImGui::Button("Vespucci Blvd"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport13(false);
									});
								}
								if (ImGui::Button("Cougar Ave"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport14(false);
									});
								}
								if (ImGui::Button("Prosperity St"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport15(false);
									});
								}

								if (ImGui::Button("Weazel Plaza"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport16(false);
									});
								}
								if (ImGui::Button("Del Perro Office"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport17(false);
									});
								}
								if (ImGui::Button("Maze Bank West Office"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport18(false);
									});
								}
								if (ImGui::Button("Arcadius Office"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport19(false);
									});
								}
		
								if (ImGui::Button("Maze Bank Office"))
								{
									g_FiberScript->addTask([] {
										Features::Teleport19(false);
									});
								}



								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Object Attachments"))
							{
								if (ImGui::Button("Remove All Attachments"))
								{
									removeattach = true;
								}

								ImGui::NewLine();

								for (auto objects1 : objects)
								{
									if (ImGui::Button(objects1))
									{
										g_FiberScript->addTask([objects1] {
										Features::AttachObjects((char*)objects1);
										});
									}
								}

								ImGui::TreePop();

							}


							if (ImGui::Button("Cage Player"))
							{
								cageplayer = true;
							}


							if (ImGui::TreeNode("Kill Methods"))
							{
								if (ImGui::Button("Normal Kill"))
								{
									normalkill = true;
								}
								if (ImGui::Button("Shoot Kill"))
								{
									shootkill = true;
								}



								ImGui::TreePop();

							}


							if (ImGui::Button("Clone Player"))
							{
								cloneped = true;
							}


							if (ImGui::Button("Give All Weapons"))
							{
								uint Weapons[] = { 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, // Melee
0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, // Handguns
0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, // Submachine Guns
0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, // Shotguns
0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, // Assault Rifles
0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, // Light Machine Guns
0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, // Sniper Rifles
0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, // Heavy Weapons
0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, // Throwables
0x34A67B97, 0xFBAB5776, 0x060EC506, 0xAF3696A1, 0x476BF155, 0xB62D1F67,
0x2B5EF5EC, 0xBA536372, 0x917F6C8C,
								};
								for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
									g_FiberScript->addTask([Weapons, i] {
									WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), Weapons[i], 9999, true);
									});
								}
							}


							if (ImGui::Button("Remove All Weapons"))
							{
								g_FiberScript->addTask([] {
								WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true);
								});
							}

							if (ImGui::Button("Slingshot his car"))
							{
								g_FiberScript->addTask([] {
								Player penis = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);

								if (PED::IS_PED_IN_ANY_VEHICLE(penis, 1))
								{
									NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true));
									if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true)));
									{
										ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
									}
	
								}
								});
							}

							if (ImGui::Button("Show Player Profile"))
							{
								g_FiberScript->addTask([] {
			
									int handle[76];
									NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
									NETWORK::NETWORK_SHOW_PROFILE_UI(&handle[0]);
								});
							}

			





							ImGui::EndChild();
							ImGui::PopStyleVar();

				}


				ImGui::SameLine(0.0f, 380.0f);
				{

				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("advancedopt", ImVec2(500, 150), true, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Advanced Options"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}

				if (ImGui::Button("Copy RID to Clipboard"))
				{
					int netHandle[13];


					NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, netHandle, 13);
					char* UserID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);

					ImGui::LogToClipboard();
					ImGui::LogText(UserID);
					ImGui::LogFinish();

				}




				ImGui::Checkbox("Vehicle Spam Crash", &Features::VehSpamCrashBool);
				
				if (ImGui::Button("Crash1"))
				{
					g_FiberScript->addTask([] {
					Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
					STREAMING::REQUEST_MODEL(0x2D7030F3);
					while (!STREAMING::HAS_MODEL_LOADED(0x2D7030F3)) g_FiberScript->Wait(0);
					Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
					STREAMING::REQUEST_MENU_PED_MODEL(0x2D7030F3);
					PED::CREATE_PED(1, 0x2D7030F3, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
					});
				}
				if (ImGui::Button("Crash2"))
				{
					g_FiberScript->addTask([] {
					Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
					STREAMING::REQUEST_MODEL(0x856cfb02);
					while (!STREAMING::HAS_MODEL_LOADED(0x856cfb02)) g_FiberScript->Wait(0);
					Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
					STREAMING::REQUEST_MENU_PED_MODEL(0x856cfb02);
					PED::CREATE_PED(1, 0x856cfb02, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
					});

				}
				if (ImGui::Button("Crash3"))
				{
					g_FiberScript->addTask([] {
					Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
					STREAMING::REQUEST_MODEL(0x3F039CBA);
					while (!STREAMING::HAS_MODEL_LOADED(0x3F039CBA)) g_FiberScript->Wait(0);
					Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
					STREAMING::REQUEST_MENU_PED_MODEL(0x3F039CBA);
					PED::CREATE_PED(1, 0x3F039CBA, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
					});

				}
				if (ImGui::Button("Crash4"))
				{
					g_FiberScript->addTask([] {
					Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
					STREAMING::REQUEST_MODEL(0xE0CBBA54);
					while (!STREAMING::HAS_MODEL_LOADED(0xE0CBBA54)) g_FiberScript->Wait(0);
					Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
					STREAMING::REQUEST_MENU_PED_MODEL(0xE0CBBA54);
					PED::CREATE_PED(1, 0xE0CBBA54, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);
					});
				}




				if (ImGui::Button("Copy Vehicle"))
				{
					g_FiberScript->addTask([] {
					Features::CloneVehicle(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
					});

				}



				if (ImGui::Button("Gift Vehicle"))
				{
					g_FiberScript->addTask([] {
						DECORATOR::DECOR_SET_INT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1), (char*)"Player_Vehicle", NETWORK::_NETWORK_HASH_FROM_PLAYER_HANDLE(g_SelectedPlayer));
						DECORATOR::DECOR_SET_INT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0), (char*)"Player_Vehicle", NETWORK::_NETWORK_HASH_FROM_PLAYER_HANDLE(g_SelectedPlayer));
					});

				}ImGui::SameLine();
				ShowHelpMarker("1: Spawn Vehicle\n2:You 2nd seat, friend main seat\n3:Friend need full garage\n4:Drive into full garage\n5:Hit replace\n6:Done");

				if (ImGui::Button("Attach to Player"))
				{
					g_FiberScript->addTask([] {
					ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, true, true, false, true, 2, true);
					});
				}
				if (ImGui::Button("Detach from Player"))
				{
					g_FiberScript->addTask([] {
						ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);
					});
				}

				ImGui::EndChild();
				ImGui::PopStyleVar();

				}

				{

					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("scripteventselected", ImVec2(500, 150), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Script Events"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();
					}





					//ImGui::Checkbox("Kick Player (XForce Bypass)", &Features::KickPlayerBool);
					if (ImGui::Button("Kick Player (XForce Bypass)"))
					{
						kickplayerxd = true;
					}

					ImGui::Checkbox("Kick (Invalid Drop)", &Features::KickDropBool); ImGui::SameLine();
					ShowHelpMarker("You need to be near the player.");

					ImGui::Checkbox("Transaction Error Spam", &Features::TransActionSpamBool);


					ImGui::Checkbox("BlackScreen", &Features::BlackScreenBool);




					ImGui::Checkbox("Sound Spam", &Features::Spam[g_SelectedPlayer]);

					ImGui::Checkbox("Spin Cammera", &Features::CameraSpam[g_SelectedPlayer]);


					ImGui::Checkbox("Kick out of CEO", &Features::CEOKickBool);



					ImGui::Checkbox("Sent Player to Mission", &Features::SendToJobBool);


					ImGui::Checkbox("Show Banner", &Features::BannerSpam);




					ImGui::EndChild();
					ImGui::PopStyleVar();

				}



				ImGui::SameLine(0.0f, 380.0f);
				{

					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("blamecustom", ImVec2(500, 150), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Custom Blame (Fake Kill)"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();
					}



					ImGui::SliderInt("Bullet", &BBulletType, 0, 30);
					ImGui::SliderFloat("BulletDamage", &BBulletDamage, 0, 100);
					ImGui::SliderFloat("Shake Value", &BBulletCameraShake, 0, 100);
					ImGui::Checkbox("Explosion Audible", &BBulletAudible);
					ImGui::Checkbox("Explosion Invisible", &BBulletInvisible);



					ImGui::Checkbox("Blame Player", &Features::BlamePlayerBool);





					ImGui::EndChild();
					ImGui::PopStyleVar();

				}

				ImGui::NewLine();
				ImGui::SameLine(0.0f, 420.0f);
				{

					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("dropplayer", ImVec2(500, 150), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Drop Options"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();
					}



					ImGui::Checkbox("Enable Money Drop", &Features::MoneyDropBool);
					ImGui::SliderInt("Money Drop Amount", &Features::DropAmount, 0, 2500);
					ImGui::SliderInt("Money Drop Delay", &Features::BagDelay, 0, 5000);
					ImGui::NewLine();
					ImGui::Checkbox("Enable RP Drop", &Features::RPDropBool);
					ImGui::SliderInt("RP Drop Delay", &Features::RPDROPDELAY, 0, 5000);

					if (ImGui::Button("Drop Armor"))
					{
						g_FiberScript->addTask([] {
							Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
							if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
							Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);


							OBJECT::CREATE_AMBIENT_PICKUPP(1274757841, pos, 0, 0, 1, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
						});

					}

					if (ImGui::Button("Drop Parachute"))
					{
						g_FiberScript->addTask([] {
							Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
							if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
							Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);


							OBJECT::CREATE_AMBIENT_PICKUPP(1735599485, pos, 0, 0, 1, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
						});

					}

					if (ImGui::Button("Drop Snack")) 
					{
						g_FiberScript->addTask([] {
							Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
							if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
							Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);


							OBJECT::CREATE_AMBIENT_PICKUPP(483577702, pos, 0, 0, 1, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
						});

					}






					ImGui::EndChild();
					ImGui::PopStyleVar();

				}






				break;









			case 9:


				ImGui::ShowStyleEditor();
				

				ImGui::Checkbox("Enable Log Window", &g_Settings.m_LogWindow);
				ImGui::Checkbox("Disable Control Lock", &Features::EnableControlBypass);
				ImGui::Checkbox("Overlay", &overlaytogglebool);
				ImGui::Checkbox("Force Show Money Drop Stats", &Features::ForceShowMoneyStat);




				if (ImGui::Button("Unload Menu"))
				{
					g_Running = false;
				}
				if (ImGui::Button("Shutdown Discord RPC"))
				{
					Discord_Shutdown();
				}
				if (ImGui::Button("Reset Droped Money Stat"))
				{
					Features::TotalDropedMoney = 0;
				}
				if (ImGui::Button("Reset Blocked Event Stat"))
				{
					Features::TotalDropedMoney = 0;
				}
				if (ImGui::Button("Reset Money Bag Stat"))
				{
					Features::TotalMoneyBags = 0;
				}
				break;

			case 8:
				ImGui::PushItemWidth(400);
				ImGui::Text(fmt::format("Welcome to {0}!", encryptedstring()).c_str());
				ImGui::Text("Version: 1.7");
				ImGui::Text("Status: Safe");



				//auto dcser = skCrypt("Official M0n0pol Discord Server");
				//if (ImGui::Button(dcser))
				//{
				//	auto runn = skCrypt("explorer https://discord.gg/c96D5rtWfZ");
				//	system(runn);
				//	runn.clear();
				//}
				//dcser.clear();


				//ImGui::SameLine();

				//auto ddffaa = skCrypt("CheatSquad");
				//if (ImGui::Button(ddffaa))
				//{
				//	auto ddsdfsdfsdfffaa = skCrypt("explorer https://cheatsquad.gg/");
				//	system(ddsdfsdfsdfffaa);
				//	ddsdfsdfsdfffaa.clear();
				//}
				//ddffaa.clear();



				ImGui::NewLine();


				break;


			case 0:


	
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("Basic", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Basic Options"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}


				ImGui::Checkbox("Godmode", &Features::GodModeBool);



				ImGui::Checkbox("Super Jump", &Features::superjumpbool);
				ImGui::Checkbox("Never Wanted", &Features::neverwantbool);
				ImGui::Checkbox("Slow Motion", &Features::SlowMoBool);

				if (ImGui::Checkbox("Invisible", &Features::InvisibilityBool))
				{
					ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), Features::InvisibilityBool, 0);
				}


				ImGui::Checkbox("Tiny Player", &Features::TinyPlayerBool);


				ImGui::Checkbox("Off Radar", &Features::OffRadarBool);
				ImGui::Checkbox("No Clip", &Features::freecambool);



				ImGui::Checkbox("Superman", &Features::superman);
				ImGui::Checkbox("No Ragdoll", &Features::RagdollBool);
				ImGui::Checkbox("Walking Carpet", &Features::MagicCarpetBool);
				
				if (ImGui::Button("Start Outfit Changer"))
				{
					ModelChanger = true;
				}
				if (ImGui::Button("Suicide"))
				{
					g_FiberScript->addTask([] {
						Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_ENTITY_HEALTH }, 0);
					});
				}
				if (ImGui::Button("Clean Player"))
				{
					g_FiberScript->addTask([] {
						int Ped = PLAYER::PLAYER_PED_ID(); PED::CLEAR_PED_BLOOD_DAMAGE(Ped); PED::RESET_PED_VISIBLE_DAMAGE(Ped);
					});
				}
				ImGui::EndChild();
				ImGui::PopStyleVar();
			}


			ImGui::SameLine();

			ImGui::SameLine(0.0, 380.0);

			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("Advanced", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Advanced Options"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}

				ImGui::Checkbox("Ultra Jump", &Features::UltraJumpBool);
				ImGui::Checkbox("Forcefield", &Features::Forcefield);
				ImGui::Checkbox("Disable Phone", &Features::DisableCell);
				ImGui::Checkbox("Firebreath", &Features::FireBreathBool);
				ImGui::Checkbox("SlideRun", &Features::SlideRunBool);



				int old = loc_wantedLevel;
				ImGui::SliderInt("Custom Wanted", &loc_wantedLevel, 0, 5);
				if (old != loc_wantedLevel)
				{
					std::vector< DWORD > Wanted_Level = { 0x08, 0x10C8, 0x868 };
					Memory::set_value< int >(Wanted_Level, loc_wantedLevel);
				}
				ImGui::SliderFloat("Fast Run", &Features::RunSpeed, 0, 255);
				ImGui::SameLine();
				if (ImGui::Button("Reset Speed"))
				{
					Features::RunSpeed = 1.0f;
				}

				ImGui::SliderInt("Alpha", &Features::alpha, 0, 255);
				ImGui::SameLine();
				if (ImGui::Button("Set Alpha"))
				{
					setalpha = true;
				}



				ImGui::EndChild();
				ImGui::PopStyleVar();
			}

			ImGui::NewLine();
			ImGui::SameLine(0.0, 420.0f);

			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("PTFX", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Effects"))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();

					if (ImGui::TreeNode("PTFX Effects"))
					{
						ImGui::Checkbox("Lightning", &Features::PTFXLightningBool);
						ImGui::Checkbox("Clown", &Features::ClownEffectBool);
						ImGui::Checkbox("Firework", &Features::FireWorkBool);
						ImGui::Checkbox("Alien 1", &Features::AlienOneBool);
						ImGui::Checkbox("Alien 2", &Features::AlienTwoBool);
						ImGui::Checkbox("Electric 1", &Features::ElectricBool);
						ImGui::Checkbox("Electric 2", &Features::ElectricBooshBool);
						ImGui::Checkbox("Water", &Features::WaterSplashBool);
						ImGui::Checkbox("Smoke", &Features::SmokeBool);
						ImGui::Checkbox("Ghost", &Features::GhostRiderBool);


						ImGui::TreePop();

					}

					if (ImGui::TreeNode("Animations"))
					{
			
						if (ImGui::Button("Stop current animation"))
						{
							g_FiberScript->addTask([] {
							AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
							});
						}

						if (ImGui::Button("Pole Dance"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"mini@strip_club@pole_dance@pole_dance1", (char*)"pd_dance_01");
								});
						}

						if (ImGui::Button("Push Ups"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"amb@world_human_push_ups@male@base", (char*)"base");
							});
						}

						if (ImGui::Button("Sit Ups"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"amb@world_human_sit_ups@male@base", (char*)"base");
							});

						}
						if (ImGui::Button("Meditation"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"rcmcollect_paperleadinout@", (char*)"meditiate_idle"); 
							});

						}
						if (ImGui::Button("On Fire"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"random@arrests", (char*)"kneeling_arrest_idle");
							});
						}

						if (ImGui::Button("Celebrate"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"rcmfanatic1celebrate", (char*)"celebrate");
							});
						}
						if (ImGui::Button("Electroshock"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"ragdoll@human", (char*)"electrocute");
							});
						}

						if (ImGui::Button("Suicide"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"mp_suicide", (char*)"pistol");
							});
						}	
						if (ImGui::Button("Shower"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"mp_safehouseshower@male@", (char*)"male_shower_idle_b");
							});
						}
						if (ImGui::Button("S*x Reciever"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"rcmpaparazzo_2", (char*)"shag_loop_poppy");
							});
						}
						if (ImGui::Button("S*x Giver"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"rcmpaparazzo_2", (char*)"shag_loop_a");
							});
						}
						if (ImGui::Button("Stripper"))
						{
							g_FiberScript->addTask([] {
							machanimation((char*)"mini@strip_club@private_dance@part1", (char*)"priv_dance_p1");
							});
						}



						ImGui::TreePop();
					}


				}






				ImGui::EndChild();
				ImGui::PopStyleVar();
			}
			





			//ImGui::Checkbox("Hulk Mode", &Features::HulkBool);

			//	ImGui::Checkbox("Pilot Mode", &Features::pilotmanbool);
			//	ImGui::SameLine();
	



				//ImGui::SameLine();

				//if (!Features::neverwantbool)
				//{
				//	int old = loc_wantedLevel;
				//	ImGui::SliderInt("", &loc_wantedLevel, 0, 5);
				//	if (old != loc_wantedLevel)
				//	{
				//		std::vector< DWORD > Wanted_Level = { 0x08, 0x10C8, 0x868 };
				//		Memory::set_value< int >(Wanted_Level, loc_wantedLevel);
				//	}

				//}


				//ImGui::Checkbox("Edit Ped Size", &Features::PedSizeBool);
				//if (Features::PedSizeBool == true)
				//{
				//	ImGui::SliderFloat("Ped Hight", &Features::pedsizee, 0, 20);

				//	ImGui::SliderFloat("Ped With", &Features::pedwithh, 0, 20);
				//}


				//ImGui::Checkbox("Speed Run", &Features::RunningBool);
				//if (Features::RunningBool)
				//{
				//	ImGui::SliderFloat("", &Features::RunSpeed, 0, 255);
				//	ImGui::NewLine();
				//}

				//ImGui::Checkbox("Speed Swin", &Features::BackstrokePro);
				//if (Features::BackstrokePro)
				//{
				//	ImGui::SliderFloat("", &Features::RunSpeed, 0, 255);
				//	ImGui::NewLine();
				//}


				//ImGui::SameLine();
				//if (ImGui::Button("Set Alpha"))
				//{
				//	ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), Features::alpha, false);
				//}



				//ImGui::SameLine();
				//ImGui::Checkbox("SlideRun", &Features::SlideRunBool);
				//ImGui::SameLine();
				//ImGui::Checkbox("0 Health", &Features::fakezerohealthbool);
				//ImGui::SameLine();
				//ImGui::SameLine();
				//ImGui::Checkbox("Mobile Radio", &Features::mobileRadio);
				//ImGui::Checkbox("Flying Car", &Features::FlyingCarBool);







				break;
				case 1:


					{
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
						ImGui::BeginChild("GiveGive", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
						if (ImGui::BeginMenuBar())
						{
							if (ImGui::BeginMenu("Weapon Adding"))
							{
								ImGui::EndMenu();
							}

							ImGui::EndMenuBar();



							if (ImGui::Button("Add All Weapons"))
							{
								Features::AddWeaponsBool = true;
							}
							if (ImGui::Button("Remove All Weapons"))
							{
								uint Weapons[] = { 0x1b06d571, 0x5ef9fec4, 0x22d8fe39, 0x99aeeb3b, 0xd205520e, 0xdc4db296,
									0xc1b3c3d1, 0xbfd21232, 0x83839c4, 0x3656c8c1, 0x47757124,
									0x13532244, 0x2be6766b, 0xefe7e2df, 0x9d07f764, 0x7fd62962, 0xa3d4d34,
									0x61012683, 0xdb1aa450, 0xbd248b55, 0x5307A4EC,
									0xbfefff6d, 0x83bf0278, 0xaf113f99, 0xc0a3098d, 0x7f229f94,
									0x624fe830, 0x97EA20B8, 0xCB96392F, 0x88374054, 0x969C3D67, 0x84D6FAFD, 0x555AF99A, 0x6A6C02E0,
									0x1d073a89, 0x7846a318, 0xe284c527, 0x9d61e50f,
									0x3aabbbaa, 0x12e82d3d, 0xef951fbb, 0xa89cb99e,
									0x5fc3c11, 0xc472fe2, 0xc734385a,
									0xa284510b, 0xb1ca77b1, 0x63ab0442, 0x42bf8a85,
									0x6d544c99, 0x7f7497e5, 0x781fe4a,
									0x93e220bd, 0x2c3731d9, 0xab564b93, 0xfdbc8a50, 0xa0973d5e,
									0x24b17070, 0x60ec506, 0x34a67b97, 0xba45e8b8,
									0x99b507ea, 0x678b81b1, 0x4e875f73, 0x958a4a8f, 0x440e4788, 0x84bd7bfd,
									0x94117305, 0x19044ee0, 0x8bb05fd7, 0xdfe37640, 0xcd274149, 0xf9e6aa4b,
									0x92a27487, 0xf9dcbf2d, 0xdd5df8d9, 0x787f0bb, 0xd8df3c3c,
									0xfbab5776, 0xBFE256D4, 0x78A97CD0, 0x394F415C, 0xFAD1F1C9, 0xDBBD7280, 0xA914799,
									0xAF3696A1, 0x476BF155, 0xB62D1F67
								};

								g_FiberScript->addTask([Weapons] {
								for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
									WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), Weapons[i]);
								}
								});

							}

							if (ImGui::Button("Add All MK2 Weapons"))
							{
								g_FiberScript->addTask([] {
								for (Hash hash : MK2Weapons)
									WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
								});
							}

						}

	



						ImGui::EndChild();
						ImGui::PopStyleVar();
					}

					ImGui::SameLine(0.0, 380.0f);



						{
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
							ImGui::BeginChild("helllppp", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
							if (ImGui::BeginMenuBar())
							{
								if (ImGui::BeginMenu("PvP Help"))
								{
									ImGui::EndMenu();
								}
								ImGui::EndMenuBar();
							}

							if (ImGui::Button("Use recommended PvP Config"))
							{
								Features::InfiniteAmmoBool = true;
								Features::DamageBool = true;
								Features::AimbotBool = true;
								Features::ExplosiveAmmoBool = true;
								Features::GodModeBool = true;
								Features::OffRadarBool = true;



							}

							ImGui::Checkbox("Unlimited Ammo", &Features::InfiniteAmmoBool);
							ImGui::Checkbox("Aimbot", &Features::AimbotBool);
							if (ImGui::TreeNode("Aimbot Settings"))
							{
								ImGui::Checkbox("Auto ESP Target", &Features::AimbotESPTarget);

								ImGui::Checkbox("Auto Shoot on Target", &Features::AimbotAutoShoot);


								ImGui::TreePop();

							}
							ImGui::Checkbox("Instant Kill", &Features::DamageBool);
							ImGui::Checkbox("No Recoil", &Features::Recoil);
							ImGui::Checkbox("Rapid Fire", &Features::RapidFireBool);



							ImGui::EndChild();
							ImGui::PopStyleVar();
						}


						{
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
							ImGui::BeginChild("Kohle", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
							if (ImGui::BeginMenuBar())
							{
								if (ImGui::BeginMenu("Cash Guns"))
								{
									ImGui::EndMenu();
								}
								ImGui::EndMenuBar();
							}

							ImGui::Checkbox("Shoot Money", &Features::MoneyGunBool);
							ImGui::SameLine();
							ImGui::Checkbox("Shoot RP", &Features::RPGunBool);
							ImGui::SliderInt("Money Amount", &Features::ShootCash, 1, 2500);



							ImGui::EndChild();
							ImGui::PopStyleVar();
						}
						ImGui::SameLine(0.0, 380.0f);

						{
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
							ImGui::BeginChild("amoad", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
							if (ImGui::BeginMenuBar())
							{
								if (ImGui::BeginMenu("Modded Ammo"))
								{
									ImGui::EndMenu();
								}
								ImGui::EndMenuBar();
							}



							ImGui::Checkbox("Valkyrie Ammo", &Features::VALKYIREROCKET);


							ImGui::Checkbox("Airstrike Ammo", &Features::AirStrike);

							ImGui::Checkbox("Fire Ammo", &Features::FireShoot);
							ImGui::Checkbox("Water Ammo", &Features::WaterShoot);


							ImGui::Checkbox("Explosive Melee", &Features::ExplosiveAmmoFlag);
							ImGui::Checkbox("Explosive Ammo", &Features::ExplosiveAmmoBool);
							ImGui::Checkbox("Explode Ammo", &Features::ExplodeAmmoBool);

							ImGui::EndChild();
							ImGui::PopStyleVar();
						}
				
						ImGui::NewLine();
						ImGui::SameLine(0.0, 420.0f);

						{
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
							ImGui::BeginChild("oterxd", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
							if (ImGui::BeginMenuBar())
							{
								if (ImGui::BeginMenu("Other Options"))
								{
									ImGui::EndMenu();
								}
								ImGui::EndMenuBar();
							}


							ImGui::Checkbox("Minecraft Gun", &Features::HashGunBool);
							ImGui::Checkbox("Teleport Gun", &Features::teleportbool);


							ImGui::Checkbox("Delete Gun", &Features::AimBool);
							ImGui::Checkbox("Drive it Gun", &Features::DriveItBool);
							ImGui::Checkbox("Random Object Gun", &Features::ObjectGunBool);
							ImGui::Checkbox("Gravity Gun", &Features::GravityGun);



							ImGui::EndChild();
							ImGui::PopStyleVar();
						}


	
						break;
					case 2:

						ImGui::SameLine(0.0, 420.0f);
					{
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
						ImGui::BeginChild("spawnset", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
						if (ImGui::BeginMenuBar())
						{
							if (ImGui::BeginMenu("Spawn Settings"))
							{
								ImGui::EndMenu();
							}
							ImGui::EndMenuBar();

							ImGui::Checkbox("Spawn in Vehicle", &Features::SpawnInCar);
							ImGui::Checkbox("Spawn Maxed", &Features::SpawnMaxed);
							ImGui::Checkbox("Spawn Effect", &Features::SpawnEffect);
						}





						ImGui::EndChild();
						ImGui::PopStyleVar();
					}





						{
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
							ImGui::BeginChild("vehlist", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
							if (ImGui::BeginMenuBar())
							{
								if (ImGui::BeginMenu("DLC Vehicle List"))
								{
									ImGui::EndMenu();
								}
								ImGui::EndMenuBar();
							}

							if (ImGui::TreeNode("Cayo Perico - DLC"))
							{

								if (ImGui::ListBox("", &Lists::cayopericointfdsfsdfsdf, CayoPerico, IM_ARRAYSIZE(CayoPerico), 6))
								{
									spawn_vehicle(CayoPerico[Lists::cayopericointfdsfsdfsdf]);
								}
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Summer Special - DLC"))
							{

								if (ImGui::ListBox("", &Lists::summerlistbox, SummerDLC, IM_ARRAYSIZE(SummerDLC), 6))
								{
									spawn_vehicle(SummerDLC[Lists::summerlistbox]);
								}
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Casino Heist - DLC"))
							{

								if (ImGui::ListBox("", &Lists::casinoheistlistbox, CasinoHeist, IM_ARRAYSIZE(CasinoHeist), 6))
								{
									spawn_vehicle(CasinoHeist[Lists::casinoheistlistbox]);
								}
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Casino - DLC"))
							{


								if (ImGui::ListBox("", &Lists::casino, Casino, IM_ARRAYSIZE(Casino), 6))
								{
									spawn_vehicle(Casino[Lists::casino]);
								}
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Arena - DLC"))
							{


								if (ImGui::ListBox("", &Lists::arenawar, ARENAWAR, IM_ARRAYSIZE(ARENAWAR), 6))
								{
									spawn_vehicle(ARENAWAR[Lists::arenawar]);
								}
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Afterhours - DLC"))
							{


								if (ImGui::ListBox("", &Lists::afterh, AFTERHOURS, IM_ARRAYSIZE(AFTERHOURS), 6))
								{
									spawn_vehicle(AFTERHOURS[Lists::afterh]);
								}
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Doomsday - DLC"))
							{


								if (ImGui::ListBox("", &Lists::dommsd, DOOMSDAY, IM_ARRAYSIZE(DOOMSDAY), 6))
								{
									spawn_vehicle(DOOMSDAY[Lists::dommsd]);
								}
								ImGui::TreePop();
							}


							if (ImGui::TreeNode("GunRunning - DLC"))
							{


								if (ImGui::ListBox("", &Lists::gunr, GUNRUNNING, IM_ARRAYSIZE(GUNRUNNING), 6))
								{
									spawn_vehicle(GUNRUNNING[Lists::gunr]);
								}
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Cunning Stunt - DLC"))
							{


								if (ImGui::ListBox("", &Lists::cunning, CUNNINGSTUNT, IM_ARRAYSIZE(CUNNINGSTUNT), 6))
								{
									spawn_vehicle(CUNNINGSTUNT[Lists::cunning]);
								}
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Import Export - DLC"))
							{


								if (ImGui::ListBox("", &Lists::importexport, IMPORTEXPORT, IM_ARRAYSIZE(IMPORTEXPORT), 6))
								{
									spawn_vehicle(IMPORTEXPORT[Lists::importexport]);
								}
								ImGui::TreePop();
							}

							ImGui::EndChild();
							ImGui::PopStyleVar();
						}



						ImGui::SameLine(0.0, 380.0f);


						{
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
							ImGui::BeginChild("vehnorm", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
							if (ImGui::BeginMenuBar())
							{
								if (ImGui::BeginMenu("Normal Vehicle List"))
								{
									ImGui::EndMenu();
								}

								ImGui::EndMenuBar();
								if (ImGui::TreeNode("Super"))
								{
									if (ImGui::ListBox("", &Lists::superveh, Super1, IM_ARRAYSIZE(Super1), 6))
									{
										spawn_vehicle(Super1[Lists::superveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Sport"))
								{
									if (ImGui::ListBox("", &Lists::sportveh, Sports1, IM_ARRAYSIZE(Sports1), 6))
									{
										spawn_vehicle(Sports1[Lists::sportveh]);
									}
									ImGui::TreePop();
								}

								if (ImGui::TreeNode("Sport-Classic"))
								{
									if (ImGui::ListBox("", &Lists::sportclassicveh, SportsClassics1, IM_ARRAYSIZE(SportsClassics1), 6))
									{
										spawn_vehicle(SportsClassics1[Lists::sportclassicveh]);
									}
									ImGui::TreePop();
								}

								if (ImGui::TreeNode("Offroad"))
								{
									if (ImGui::ListBox("", &Lists::offroadveh, OffRoad1, IM_ARRAYSIZE(OffRoad1), 6))
									{
										spawn_vehicle(OffRoad1[Lists::offroadveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Muscle"))
								{
									if (ImGui::ListBox("", &Lists::muscleveh, Muscle1, IM_ARRAYSIZE(Muscle1), 6))
									{
										spawn_vehicle(Muscle1[Lists::muscleveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Boats"))
								{
									if (ImGui::ListBox("", &Lists::boatsveh, Boats1, IM_ARRAYSIZE(Boats1), 6))
									{
										spawn_vehicle(Boats1[Lists::boatsveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Commercial"))
								{
									if (ImGui::ListBox("", &Lists::commercialveh, Commercial1, IM_ARRAYSIZE(Commercial1), 6))
									{
										spawn_vehicle(Commercial1[Lists::commercialveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Compacts"))
								{
									if (ImGui::ListBox("", &Lists::compactsveh, Compacts1, IM_ARRAYSIZE(Compacts1), 6))
									{
										spawn_vehicle(Compacts1[Lists::compactsveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Cycles"))
								{
									if (ImGui::ListBox("", &Lists::Cyclesveh, Cycles1, IM_ARRAYSIZE(Cycles1), 6))
									{
										spawn_vehicle(Cycles1[Lists::Cyclesveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Emergency"))
								{
									if (ImGui::ListBox("", &Lists::emergencyveh, Emergency1, IM_ARRAYSIZE(Emergency1), 6))
									{
										spawn_vehicle(Emergency1[Lists::emergencyveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Helicopters"))
								{
									if (ImGui::ListBox("", &Lists::helicopterveh, Helicopters1, IM_ARRAYSIZE(Helicopters1), 6))
									{
										spawn_vehicle(Helicopters1[Lists::helicopterveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Industrial"))
								{
									if (ImGui::ListBox("", &Lists::industveh, Industrial1, IM_ARRAYSIZE(Industrial1), 6))
									{
										spawn_vehicle(Industrial1[Lists::industveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Military"))
								{
									if (ImGui::ListBox("", &Lists::milliveh, Military1, IM_ARRAYSIZE(Military1), 6))
									{
										spawn_vehicle(Military1[Lists::milliveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Motorcycles"))
								{
									if (ImGui::ListBox("", &Lists::motorcyveh, Motorcycles1, IM_ARRAYSIZE(Motorcycles1), 6))
									{
										spawn_vehicle(Motorcycles1[Lists::motorcyveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Planes"))
								{
									if (ImGui::ListBox("", &Lists::planeveh, Planes1, IM_ARRAYSIZE(Planes1), 6))
									{
										spawn_vehicle(Planes1[Lists::planeveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Service"))
								{
									if (ImGui::ListBox("", &Lists::serviceveh, Service1, IM_ARRAYSIZE(Service1), 6))
									{
										spawn_vehicle(Service1[Lists::serviceveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("SUV"))
								{
									if (ImGui::ListBox("", &Lists::suvveh, SUVs1, IM_ARRAYSIZE(SUVs1), 6))
									{
										spawn_vehicle(SUVs1[Lists::suvveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Trailer"))
								{
									if (ImGui::ListBox("", &Lists::trailerveh, Trailer1, IM_ARRAYSIZE(Trailer1), 6))
									{
										spawn_vehicle(Trailer1[Lists::trailerveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Trains"))
								{
									if (ImGui::ListBox("", &Lists::trainsveh, Trains1, IM_ARRAYSIZE(Trains1), 6))
									{
										spawn_vehicle(Trains1[Lists::trainsveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Utility"))
								{
									if (ImGui::ListBox("", &Lists::utiliveh, Utility1, IM_ARRAYSIZE(Utility1), 6))
									{
										spawn_vehicle(Utility1[Lists::utiliveh]);
									}
									ImGui::TreePop();
								}
								if (ImGui::TreeNode("Vans"))
								{
									if (ImGui::ListBox("", &Lists::vansveh, Vans1, IM_ARRAYSIZE(Vans1), 6))
									{
										spawn_vehicle(Vans1[Lists::vansveh]);
									}
									ImGui::TreePop();
								}

							}


							ImGui::EndChild();
							ImGui::PopStyleVar();
						}

						ImGui::NewLine();
						ImGui::SameLine(0.0, 420.0f);
						{
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
							ImGui::BeginChild("vehbyname", ImVec2(500, 130), true, ImGuiWindowFlags_MenuBar);
							if (ImGui::BeginMenuBar())
							{
								if (ImGui::BeginMenu("Spawn Vehicle by Name"))
								{
									ImGui::EndMenu();
								}
								ImGui::EndMenuBar();
							}




							ImGui::Text("Enter Vehicle Name: ");
							ImGui::InputText("", SpawnByName, sizeof(SpawnByName));
							if (ImGui::Button("Spawn Vehicle")) {
								g_FiberScript->addTask([] {
								spawn_vehicle(SpawnByName);
							});
							}







							ImGui::EndChild();
							ImGui::PopStyleVar();
						}




						ImGui::NewLine();
						ImGui::SameLine(0.0, 420.0f);
						{
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
							ImGui::BeginChild("moddi", ImVec2(500, 130), true, ImGuiWindowFlags_MenuBar);
							if (ImGui::BeginMenuBar())
							{
								if (ImGui::BeginMenu("Modded Vehicles"))
								{
									ImGui::EndMenu();
								}
								ImGui::EndMenuBar();
							}




							if (ImGui::Button("Penis Truck"))
							{
								g_FiberScript->addTask([] {



									//FLATBED Hash

									int karre = $("FLATBED");

									FLOAT heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									STREAMING::REQUEST_MODEL(karre);
									int playerVeh = VEHICLE::CREATE_VEHICLE(karre, MyCoords, heading, *g_GameVariables->is_session_started, 0);
									PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), playerVeh, -1);
									VEHICLE::SET_VEHICLE_COLOURS(playerVeh, 64, 40);

									auto numberpaltetext = skCrypt("BIG PENIS");
									VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, numberpaltetext);
									numberpaltetext.clear();

									VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, 1);
									STREAMING::REQUEST_MODEL(0x8DA1C0E);
									STREAMING::REQUEST_MODEL(0xB32ADCA8);
									Object spawnedOrange;
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, 0, -0.690002, 2.089998, 0, 0, 90, false, false, true, false, 0, true); //1
									ENTITY::SET_ENTITY_COLLISION(spawnedOrange, TRUE, TRUE);
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, 0, -6, 2.08998, 0, -22, 90, false, false, true, false, 0, true); //2
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, 0, -3.35, 2.500000, 0, -11, 90, false, false, true, false, 0, true); //3
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -0.5, -3.35, 3, 0, -11, 90, false, false, true, false, 0, true); //4
									 OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -1, -3.35, 3.5, 0, -11, 90, false, false, true, false, 0, true); //5
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -1.5, -3.35, 4.25, 43, -11, 90, false, false, true, false, 0, true); //6
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -2, -3.35, 5, 23.25, -11, 90, false, false, true, false, 0, true); //7
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -2.5, -3.35, 5.75, 31.25, -11, 90, false, false, true, false, 0, true); //8
									 OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -3, -3.35, 6.25, 18.5, -11, 90, false, false, true, false, 0, true); //9
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -3.5, -3.35, 6.5, 18.5, -11, 90, false, false, true, false, 0, true); //11
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -4.5, -3.35, 7, 18.5, -11, 90, false, false, true, false, 0, true); //12
									OBJECT::CREATE_OBJECT(0x8DA1C0E, 0, 0, 0, true, 1, -1, &spawnedOrange, true, false, false);
									ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -6.25, -3.35, 7.5, 9.25, -11, 90, false, false, true, false, 0, true); //13
								});


							}




							if (ImGui::Button("6x6 War RC"))
							{
								g_FiberScript->addTask([] {
									int Handle = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("dune2");
									int hash2 = GAMEPLAY::GET_HASH_KEY("t20");
									int hash3 = GAMEPLAY::GET_HASH_KEY("dune2");
									int hash4 = GAMEPLAY::GET_HASH_KEY("dune2");
									int hash5 = GAMEPLAY::GET_HASH_KEY("monster");
									int hash6 = GAMEPLAY::GET_HASH_KEY("monster");


									STREAMING::REQUEST_MODEL(hash);


									STREAMING::REQUEST_MODEL(hash2);

									STREAMING::REQUEST_MODEL(hash3);

									STREAMING::REQUEST_MODEL(hash4);

									STREAMING::REQUEST_MODEL(hash5);

									STREAMING::REQUEST_MODEL(hash6);




									int Object1 = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);


									int Object2 = VEHICLE::CREATE_VEHICLE(hash3, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);


									int Object3 = VEHICLE::CREATE_VEHICLE(hash4, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);


									int Object4 = VEHICLE::CREATE_VEHICLE(hash5, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);

									int Object5 = VEHICLE::CREATE_VEHICLE(hash6, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);










									if (ENTITY::DOES_ENTITY_EXIST(Object1) && ENTITY::DOES_ENTITY_EXIST(Object2) && ENTITY::DOES_ENTITY_EXIST(Object3) && ENTITY::DOES_ENTITY_EXIST(Object4) && ENTITY::DOES_ENTITY_EXIST(Object5))
									{
										FLOAT heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords, heading, *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
										{
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);

											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, Vehicle, 0, a.x - 0.1f, a.y, a.z, b.x, b.y + 41.1f, b.z, 0, 1, 0, 0, 2, 1);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object3, Vehicle, 0, a.x + 0.1f, a.y, a.z, b.x, b.y - 41.4f, b.z, 0, 1, 0, 0, 2, 1);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object4, Vehicle, 0, a.x + 1.41f, a.y, a.z - 0.2f, b.x - 179.99f, b.y, b.z, 0, 1, 0, 0, 2, 1);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object5, Vehicle, 0, a.x - 1.41f, a.y, a.z - 0.2f, b.x - 179.99f, b.y, b.z, 0, 1, 0, 0, 2, 1);

											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 255, 255, 255);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 255, 255, 255);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object1, 255, 255, 255);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object1, 255, 255, 255);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object4, 255, 255, 255);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object4, 255, 255, 255);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object5, 255, 255, 255);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object5, 255, 255, 255);
										}

									}
									else
									{
										g_Logger->Info("Not Exist");
									}
								});
							}

							if (ImGui::Button("Speeder Prototype"))
							{
								g_FiberScript->addTask([] {
									int Handle = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("seashark");
									int hash1 = GAMEPLAY::GET_HASH_KEY("seashark");
									int hash2 = GAMEPLAY::GET_HASH_KEY("turismor");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash1);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash1) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Object = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object1 = VEHICLE::CREATE_VEHICLE(hash1, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Object))
										{
											int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
											if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
											{
												VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 255, 0, 0);
												VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 255, 0, 0);
												VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 255, 0, 0);
												VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 255, 0, 0);
												VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object1, 255, 0, 0);
												VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object1, 255, 0, 0);
												PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y + 1.37f, a.z + 0.59f, b.x - 14.33f, b.y + 541.20f, b.z - 1.42f, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a.x, a.y - 0.79f, a.z + 0.83f, b.x + 9.72f, b.y + 539.03f, b.z - 0.16f, 0, 1, 0, 0, 2, 1);
											}
										}
									}
								});
							}


							if (ImGui::Button("Scooter"))
							{
								g_FiberScript->addTask([] {
									int Handle = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("seashark");
									int hash2 = GAMEPLAY::GET_HASH_KEY("sanchez");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Object = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Object))
										{
											int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
											if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
											{
												VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 255, 0, 0);
												VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 255, 0, 0);
												VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 255, 0, 0);
												VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 255, 0, 0);
												PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);

												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x - 0.02f, a.y - 0.08f, a.z - 0.36f, b.x - 0.21f, b.y + 1.83f, b.z - 0.21f, 0, 1, 0, 0, 2, 1);

											}
										}
									}
								});

							}

							if (ImGui::Button("Ufo"))
							{
								g_FiberScript->addTask([] {
									int Handle = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = -0.27, a.y = -0.24, a.z = 0.13f;
									Vector3 b; b.x = 0, b.y = 0, b.z = 180;
									int hash = GAMEPLAY::GET_HASH_KEY("skylift");
									int hash2 = GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Object;
										OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, true, 1, -1, &Object, true, false, false);
										if (ENTITY::DOES_ENTITY_EXIST(Object))
										{
											int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
											if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
											{
												PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);

												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);

												VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 2, 153, 57);
												VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 2, 153, 57);
												VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 2, 153, 57);
												VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 2, 153, 57);

											}
										}
									}
								});
							}

							if (ImGui::Button("Flightsquad"))
							{
								g_FiberScript->addTask([] {

									int Handle = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("hydra");
									int hash1 = GAMEPLAY::GET_HASH_KEY("hydra");
									int hash2 = GAMEPLAY::GET_HASH_KEY("hydra");
									int hash3 = GAMEPLAY::GET_HASH_KEY("hydra");
									int hash4 = GAMEPLAY::GET_HASH_KEY("hydra");
									int hash5 = GAMEPLAY::GET_HASH_KEY("hydra");
									int hash6 = GAMEPLAY::GET_HASH_KEY("hydra");
									int hash7 = GAMEPLAY::GET_HASH_KEY("hydra");
									int hash8 = GAMEPLAY::GET_HASH_KEY("hydra");

									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									STREAMING::REQUEST_MODEL(hash1);
									STREAMING::REQUEST_MODEL(hash3);
									STREAMING::REQUEST_MODEL(hash4);
									STREAMING::REQUEST_MODEL(hash5);
									STREAMING::REQUEST_MODEL(hash6);
									STREAMING::REQUEST_MODEL(hash7);
									STREAMING::REQUEST_MODEL(hash8);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash1) && STREAMING::HAS_MODEL_LOADED(hash3) && STREAMING::HAS_MODEL_LOADED(hash4) && STREAMING::HAS_MODEL_LOADED(hash5) && STREAMING::HAS_MODEL_LOADED(hash6) && STREAMING::HAS_MODEL_LOADED(hash7) && STREAMING::HAS_MODEL_LOADED(hash8))
									{
										int Object = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object1 = VEHICLE::CREATE_VEHICLE(hash1, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object2 = VEHICLE::CREATE_VEHICLE(hash3, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object3 = VEHICLE::CREATE_VEHICLE(hash4, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object4 = VEHICLE::CREATE_VEHICLE(hash5, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object5 = VEHICLE::CREATE_VEHICLE(hash6, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object6 = VEHICLE::CREATE_VEHICLE(hash7, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object7 = VEHICLE::CREATE_VEHICLE(hash8, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Object))
										{
											int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
											if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
											{

												PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);


												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y + 15.541162f, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a.x, a.y + 30.541162f, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, Vehicle, 0, a.x - 15.0f, a.y + 15.541162f, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object3, Vehicle, 0, a.x + 15.0f, a.y + 15.541162f, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object4, Vehicle, 0, a.x + 15.0f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object5, Vehicle, 0, a.x + 30.0f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object6, Vehicle, 0, a.x - 15.0f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object7, Vehicle, 0, a.x - 30.0f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);

											}
										}
									}
								});
							}

							if (ImGui::Button("Bike Robot"))
							{
								g_FiberScript->addTask([] {
									int Handle = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0.03f;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("bati");
									int hash1 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash2 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash3 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash4 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash5 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash6 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash7 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash8 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash9 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash10 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash11 = GAMEPLAY::GET_HASH_KEY("bati");
									int hash12 = GAMEPLAY::GET_HASH_KEY("bati");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash1);
									STREAMING::REQUEST_MODEL(hash2);
									STREAMING::REQUEST_MODEL(hash2);
									STREAMING::REQUEST_MODEL(hash3);
									STREAMING::REQUEST_MODEL(hash4);
									STREAMING::REQUEST_MODEL(hash5);
									STREAMING::REQUEST_MODEL(hash6);
									STREAMING::REQUEST_MODEL(hash7);
									STREAMING::REQUEST_MODEL(hash8);
									STREAMING::REQUEST_MODEL(hash9);
									STREAMING::REQUEST_MODEL(hash10);
									STREAMING::REQUEST_MODEL(hash11);
									STREAMING::REQUEST_MODEL(hash12);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash1) && STREAMING::HAS_MODEL_LOADED(hash3) && STREAMING::HAS_MODEL_LOADED(hash4) && STREAMING::HAS_MODEL_LOADED(hash5) && STREAMING::HAS_MODEL_LOADED(hash6) && STREAMING::HAS_MODEL_LOADED(hash7) && STREAMING::HAS_MODEL_LOADED(hash8) && STREAMING::HAS_MODEL_LOADED(hash9) && STREAMING::HAS_MODEL_LOADED(hash10) && STREAMING::HAS_MODEL_LOADED(hash11))
									{
										int Object = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object1 = VEHICLE::CREATE_VEHICLE(hash1, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object2 = VEHICLE::CREATE_VEHICLE(hash3, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object3 = VEHICLE::CREATE_VEHICLE(hash4, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object4 = VEHICLE::CREATE_VEHICLE(hash5, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object5 = VEHICLE::CREATE_VEHICLE(hash6, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object6 = VEHICLE::CREATE_VEHICLE(hash7, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object7 = VEHICLE::CREATE_VEHICLE(hash8, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object8 = VEHICLE::CREATE_VEHICLE(hash9, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object9 = VEHICLE::CREATE_VEHICLE(hash10, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object10 = VEHICLE::CREATE_VEHICLE(hash11, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object11 = VEHICLE::CREATE_VEHICLE(hash12, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Object))
										{
											int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
											if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
											{
												PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);

												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z + 1.16f, b.x + 62.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a.x + 2.5f, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object3, Vehicle, 0, a.x + 2.5f, a.y, a.z + 1.16f, b.x + 62.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object4, Vehicle, 0, a.x + 0.5f, a.y + 0.5f, a.z + 2.27f, b.x + 50.0f, b.y - 70.0f, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object5, Vehicle, 0, a.x + 1.95f, a.y + 0.5f, a.z + 2.27f, b.x + 50.0f, b.y + 70.0f, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object6, Vehicle, 0, a.x + 1.24f, a.y + 0.8f, a.z + 5.0f, b.x + 90.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object7, Vehicle, 0, a.x + 1.24f, a.y + 0.8f, a.z + 3.5f, b.x + 90.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object8, Vehicle, 0, a.x + 1.24f, a.y + 0.8f, a.z + 6.0f, b.x - 15.0f, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object9, Vehicle, 0, a.x + 2.0f, a.y + 0.8f, a.z + 4.43f, b.x - 30.0f, b.y - 50.0f, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object10, Vehicle, 0, a.x + 0.6f, a.y + 0.8f, a.z + 4.43f, b.x - 30.0f, b.y + 50.0f, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, Vehicle, 0, a.x, a.y + 2.1f, a.z + 3.7f, b.x - 10.0f, b.y + 12.8f, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object11, Vehicle, 0, a.x + 2.8f, a.y + 1.9f, a.z + 3.7f, b.x - 10.0f, b.y - 13.6f, b.z, 0, 1, 0, 0, 2, 1);
											}
										}
									}
								});

							}

							if (ImGui::Button("Buggy"))
							{
								g_FiberScript->addTask([] {
									uint Handle = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = -0.34, a.y = 0.32, a.z = -0.25;
									Vector3 b; b.x = 0, b.y = 0, b.z = 180;
									Vector3 Tire; Tire.x = 0.0, Tire.y = 0.0; Tire.z = 0.0;//Right Front(inner tire)
									Vector3 TireA; TireA.x = 0.40, TireA.y = 1.0, TireA.z = -0.51;//X Coord - Y Coord - Z Coord
									Vector3 TireB; TireB.x = 0.0, TireB.y = 0.0, TireB.z = 88.0;//Pitch - Roll - Yaw
									Vector3 Tire01; Tire01.x = 0.0, Tire01.y = 0.0; Tire01.z = 0;//Right Front(outter tire)
									Vector3 TireC; TireC.x = 0.59, TireC.y = 1.0, TireC.z = -0.51;//X Coord - Y Coord - Z Coord
									Vector3 TireD; TireD.x = 0.0, TireD.y = 0.0, TireD.z = -90.0;//Pitch - Roll - Yaw
									Vector3 Tire02; Tire02.x = 0.0, Tire02.y = 0.0; Tire02.z = 0.0;//Left Front(inner tire)
									Vector3 TireE; TireE.x = -1.09, TireE.y = 1.0, TireE.z = -0.50;//X Coord - Y Coord - Z Coord
									Vector3 TireF; TireF.x = 0.0, TireF.y = 0.0, TireF.z = -88.0;//Pitch - Roll - Yaw
									Vector3 Tire03; Tire03.x = 0.0, Tire03.y = 0.0; Tire03.z = 0.0;//Left Front(outter tire)
									Vector3 TireG; TireG.x = -1.264, TireG.y = 1.0, TireG.z = -0.50;//X Coord - Y Coord - Z Coord
									Vector3 TireH; TireH.x = 0.0, TireH.y = 0.0, TireH.z = 92.0;//Pitch - Roll - Yaw
									Vector3 Engine1; Engine1.x = 0.0, Engine1.y = 0.0; Engine1.z = 0.0;//Engine
									Vector3 EngineA; EngineA.x = -0.39, EngineA.y = -1.60, EngineA.z = -0.70;//X Coord - Y Coord - Z Coord
									Vector3 EngineB; EngineB.x = 0.0, EngineB.y = 0.0, EngineB.z = 0.0;//Pitch - Roll - Yaw
									Vector3 Tire04; Tire04.x = 0.0, Tire04.y = 0.0; Tire04.z = 0.0;//Right Rear(inner tire)
									Vector3 TireI; TireI.x = 0.22, TireI.y = -1.40, TireI.z = -0.50;//X Coord - Y Coord - Z Coord
									Vector3 TireJ; TireJ.x = 0.0, TireJ.y = 0.0, TireJ.z = -88.0;//Pitch - Roll - Yaw
									Vector3 Tire05; Tire05.x = 0.0, Tire05.y = 0.0; Tire05.z = 0.0;//Right Rear(middle tire)
									Vector3 TireK; TireK.x = 0.42, TireK.y = -1.40, TireK.z = -0.50;//X Coord - Y Coord - Z Coord
									Vector3 TireL; TireL.x = 0.0, TireL.y = 0.0, TireL.z = 90.0;//Pitch - Roll - Yaw
									Vector3 Tire06; Tire06.x = 0.0, Tire06.y = 0.0; Tire06.z = 0.0;//Right Rear(outter tire)
									Vector3 TireM; TireM.x = 0.593, TireM.y = -1.40, TireM.z = -0.50;//X Coord - Y Coord - Z Coord
									Vector3 TireN; TireN.x = 0.0, TireN.y = 0.0, TireN.z = -89.0;//Pitch - Roll - Yaw
									Vector3 Tire07; Tire07.x = 0.0, Tire07.y = 0.0; Tire07.z = 0.0;//Left Rear(inner tire)
									Vector3 TireO; TireO.x = -0.81, TireO.y = -1.40, TireO.z = -0.50;//X Coord - Y Coord - Z Coord
									Vector3 TireP; TireP.x = 0.0, TireP.y = 0.0, TireP.z = 88.0;//Pitch - Roll - Yaw
									Vector3 Tire08; Tire08.x = 0.0, Tire08.y = 0.0; Tire08.z = 0.0;//Left Rear(middle tire)
									Vector3 TireQ; TireQ.x = -1.01, TireQ.y = -1.40, TireQ.z = -0.50;//X Coord - Y Coord - Z Coord
									Vector3 TireR; TireR.x = 0.0, TireR.y = 0.0, TireR.z = -91.0;//Pitch - Roll - Yaw
									Vector3 Tire09; Tire09.x = 0.0, Tire09.y = 0.0; Tire09.z = 0.0;//Left Rear(outter tire)
									Vector3 TireSs; TireSs.x = -1.184, TireSs.y = -1.40, TireSs.z = -0.50;//X Coord - Y Coord - Z Coord
									Vector3 TireT; TireT.x = 0.0, TireT.y = 0.0, TireT.z = 88.0;//Pitch - Roll - Yaw
									Vector3 Hood1; Hood1.x = 0, Hood1.y = 0; Hood1.z = 0;//Hood
									Vector3 HoodA; HoodA.x = -0.34, HoodA.y = 1.2, HoodA.z = -0.40;//X Coord - Y Coord - Z Coord
									Vector3 HoodB; HoodB.x = -24.0, HoodB.y = 0.0, HoodB.z = 0.0;//Pitch - Roll - Yaw
									Vector3 Battery1; Battery1.x = 0.0, Battery1.y = 0.0; Battery1.z = 0.0;//Battery
									Vector3 BatteryA; BatteryA.x = -0.34, BatteryA.y = 1.06, BatteryA.z = -0.06;//X Coord - Y Coord - Z Coord
									Vector3 BatteryB; BatteryB.x = -24.0, BatteryB.y = 0.0, BatteryB.z = 0.0;//Pitch - Roll - Yaw
									int hash = GAMEPLAY::GET_HASH_KEY("blista");
									int hash2 = GAMEPLAY::GET_HASH_KEY("prop_bumper_car_01");
									int Tires = GAMEPLAY::GET_HASH_KEY("prop_wheel_01");
									int Engine = GAMEPLAY::GET_HASH_KEY("prop_car_engine_01");
									int Hood = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
									int Battery = GAMEPLAY::GET_HASH_KEY("prop_power_cell");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									STREAMING::REQUEST_MODEL(Tires);
									STREAMING::REQUEST_MODEL(Engine);
									STREAMING::REQUEST_MODEL(Hood);
									STREAMING::REQUEST_MODEL(Battery);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(Tires) && STREAMING::HAS_MODEL_LOADED(Engine) && STREAMING::HAS_MODEL_LOADED(Hood) && STREAMING::HAS_MODEL_LOADED(Battery))
									{
										int Object;
										OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, true, 1, -1, &Object, true, false, false);

										int Tire1;
										OBJECT::CREATE_OBJECT(Tires, Tire.x, Tire.y, Tire.z, true, 1, -1, &Tire1, true, false, false);

										int Tire2;
										OBJECT::CREATE_OBJECT(Tires, Tire01.x, Tire01.y, Tire01.z, true, 1, -1, &Tire2, true, false, false);

										int Tire3;
										OBJECT::CREATE_OBJECT(Tires, Tire02.x, Tire02.y, Tire02.z, true, 1, -1, &Tire3, true, false, false);

										int Tire4;
										OBJECT::CREATE_OBJECT(Tires, Tire03.x, Tire03.y, Tire03.z, true, 1, -1, &Tire4, true, false, false);

										int Engine01;
										OBJECT::CREATE_OBJECT(Tires, Engine1.x, Engine1.y, Engine1.z, true, 1, -1, &Engine01, true, false, false);



										int Tire5;
										OBJECT::CREATE_OBJECT(Tires, Tire04.x, Tire04.y, Tire04.z, true, 1, -1, &Tire5, true, false, false);


										int Tire6;
										OBJECT::CREATE_OBJECT(Tires, Tire05.x, Tire05.y, Tire05.z, true, 1, -1, &Tire6, true, false, false);



										int Tire7;
										OBJECT::CREATE_OBJECT(Tires, Tire06.x, Tire06.y, Tire06.z, true, 1, -1, &Tire7, true, false, false);

										int Tire8;
										OBJECT::CREATE_OBJECT(Tires, Tire07.x, Tire07.y, Tire07.z, true, 1, -1, &Tire8, true, false, false);

										int Tire9;
										OBJECT::CREATE_OBJECT(Tires, Tire08.x, Tire08.y, Tire08.z, true, 1, -1, &Tire9, true, false, false);


										int Tire10;
										OBJECT::CREATE_OBJECT(Tires, Tire09.x, Tire09.y, Tire09.z, true, 1, -1, &Tire10, true, false, false);


										int Hood01;
										OBJECT::CREATE_OBJECT(Hood, Tire09.x, Tire09.y, Tire09.z, true, 1, -1, &Hood01, true, false, false);

										int Battery01;
										OBJECT::CREATE_OBJECT(Battery, Battery1.x, Battery1.y, Battery1.z, true, 1, -1, &Battery01, true, false, false);


										if (ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::DOES_ENTITY_EXIST(Tire1) && ENTITY::DOES_ENTITY_EXIST(Tire2) && ENTITY::DOES_ENTITY_EXIST(Tire3) && ENTITY::DOES_ENTITY_EXIST(Tire4) && ENTITY::DOES_ENTITY_EXIST(Engine01) && ENTITY::DOES_ENTITY_EXIST(Tire5) && ENTITY::DOES_ENTITY_EXIST(Tire6) && ENTITY::DOES_ENTITY_EXIST(Tire7) && ENTITY::DOES_ENTITY_EXIST(Tire8) && ENTITY::DOES_ENTITY_EXIST(Tire9) && ENTITY::DOES_ENTITY_EXIST(Tire10) && ENTITY::DOES_ENTITY_EXIST(Hood01) && ENTITY::DOES_ENTITY_EXIST(Battery01))
										{
											int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
											if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
											{
												PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
												STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
												ENTITY::SET_ENTITY_VISIBLE(Vehicle, false, true);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire1, Vehicle, 0, TireA.x, TireA.y, TireA.z, TireB.x, TireB.y, TireB.z, 0, 1, 0, 0, 2, 1);//Right Front(inner tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire2, Vehicle, 0, TireC.x, TireC.y, TireC.z, TireD.x, TireD.y, TireD.z, 0, 1, 0, 0, 2, 1);//right Front(outter tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire3, Vehicle, 0, TireE.x, TireE.y, TireE.z, TireF.x, TireF.y, TireF.z, 0, 1, 0, 0, 2, 1);//Left Front(inner tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire4, Vehicle, 0, TireG.x, TireG.y, TireG.z, TireH.x, TireH.y, TireH.z, 0, 1, 0, 0, 2, 1);//Left Front(outter tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Engine01, Vehicle, 0, EngineA.x, EngineA.y, EngineA.z, EngineB.x, EngineB.y, EngineB.z, 0, 1, 0, 0, 2, 1);//Engine
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire5, Vehicle, 0, TireI.x, TireI.y, TireI.z, TireJ.x, TireJ.y, TireJ.z, 0, 1, 0, 0, 2, 1);//Right Rear(inner tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire6, Vehicle, 0, TireK.x, TireK.y, TireK.z, TireL.x, TireL.y, TireL.z, 0, 1, 0, 0, 2, 1);//Right Rear(middle tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire7, Vehicle, 0, TireM.x, TireM.y, TireM.z, TireN.x, TireN.y, TireN.z, 0, 1, 0, 0, 2, 1);//Right Rear(outter tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire8, Vehicle, 0, TireO.x, TireO.y, TireO.z, TireP.x, TireP.y, TireP.z, 0, 1, 0, 0, 2, 1);//Left Rear(inner tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire9, Vehicle, 0, TireQ.x, TireQ.y, TireQ.z, TireR.x, TireR.y, TireR.z, 0, 1, 0, 0, 2, 1);//Left Rear(middle tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Tire10, Vehicle, 0, TireSs.x, TireSs.y, TireSs.z, TireT.x, TireT.y, TireT.z, 0, 1, 0, 0, 2, 1);//Left Rear(outter tire)
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Hood01, Vehicle, 0, HoodA.x, HoodA.y, HoodA.z, HoodB.x, HoodB.y, HoodB.z, 0, 1, 0, 0, 2, 1);//Hood
												ENTITY::ATTACH_ENTITY_TO_ENTITY(Battery01, Vehicle, 0, BatteryA.x, BatteryA.y, BatteryA.z, BatteryB.x, BatteryB.y, BatteryB.z, 0, 1, 0, 0, 2, 1);//Battery
												ENTITY::SET_ENTITY_VISIBLE(Handle, true, true);

											}

										}

									}
								});
							}

							if (ImGui::Button("Modded T20"))
							{
								g_FiberScript->addTask([] {
									uint Handle = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									//hash2_EMP
									Vector3 null; null.x = 0.0, null.y = 0.0; null.z = 0.0;
									Vector3 a; a.x = 0.0, a.y = 1.61, a.z = -0.12;//X Coord - Y Coord - Z Coord
									Vector3 b; b.x = -12.0, b.y = 0.0, b.z = 0.0;//Pitch - Roll - Yaw
																				 //hash3_MiniGun
									Vector3 null1; null1.x = 0.0, null1.y = 0.0; null1.z = 0.0;
									Vector3 a1; a1.x = -0.60, a1.y = 1.60, a1.z = 0.20;
									Vector3 b1; b1.x = 0.0, b1.y = 0.0, b1.z = 88.0;
									//hash3_MiniGun2
									Vector3 null0; null0.x = 0.0, null0.y = 0.0; null0.z = 0.0;
									Vector3 a0; a0.x = 0.60, a0.y = 1.60, a0.z = 0.20;
									Vector3 b0; b0.x = 0.0, b0.y = 0.0, b0.z = 88.0;
									//hash4_FLWheel1
									Vector3 null2; null2.x = 0.0, null2.y = 0.0; null2.z = 0.0;
									Vector3 a2; a2.x = -0.94, a2.y = 1.32, a2.z = -0.25;
									Vector3 b2; b2.x = 9.0, b2.y = -28.0, b2.z = 87.0;
									//hash4_RLWheel1
									Vector3 null3; null3.x = 0.0, null3.y = 0.0; null3.z = 0.0;
									Vector3 a3; a3.x = -0.95, a3.y = -1.34, a3.z = -0.25f;
									Vector3 b3; b3.x = 9.0, b3.y = 38.0, b3.z = 87.0;
									//hash4_RFWheel1
									Vector3 null4; null4.x = 0.0, null4.y = 0.0; null4.z = 0.0;
									Vector3 a4; a4.x = 0.95, a4.y = 1.33, a4.z = -0.23;
									Vector3 b4; b4.x = 11.0, b4.y = 26.0, b4.z = -89.0;
									//hash4_RRWheel1
									Vector3 null5; null5.x = 0.0, null5.y = 0.0; null5.z = 0.0;
									Vector3 a5; a5.x = 0.96, a5.y = -1.31, a5.z = -0.23;
									Vector3 b5; b5.x = 10.0, b5.y = 20.0, b5.z = -92.0;

									int hash_T20 = GAMEPLAY::GET_HASH_KEY("t20");
									int hash2_EMP = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
									int hash3_MiniGun = GAMEPLAY::GET_HASH_KEY("prop_minigun_01");
									int hash4_Wheel = GAMEPLAY::GET_HASH_KEY("prop_wheel_01");

									STREAMING::REQUEST_MODEL(hash_T20);
									STREAMING::REQUEST_MODEL(hash2_EMP);
									STREAMING::REQUEST_MODEL(hash3_MiniGun);
									STREAMING::REQUEST_MODEL(hash4_Wheel);

									if (STREAMING::HAS_MODEL_LOADED(hash_T20) && STREAMING::HAS_MODEL_LOADED(hash2_EMP) && STREAMING::HAS_MODEL_LOADED(hash3_MiniGun) && STREAMING::HAS_MODEL_LOADED(hash4_Wheel))
									{
										int EMP;
										OBJECT::CREATE_OBJECT(hash2_EMP, null.x, null.y, null.z, true, 1, -1, &EMP, true, false, false);

										int MiniGun;
										OBJECT::CREATE_OBJECT(hash3_MiniGun, null1.x, null1.y, null1.z, true, 1, -1, &MiniGun, true, false, false);

										int MiniGun2;
										OBJECT::CREATE_OBJECT(hash3_MiniGun, null0.x, null0.y, null0.z, true, 1, -1, &MiniGun2, true, false, false);

										int FLWheel1;
										OBJECT::CREATE_OBJECT(hash4_Wheel, null2.x, null2.y, null2.z, true, 1, -1, &FLWheel1, true, false, false);

										int RLWheel1;
										OBJECT::CREATE_OBJECT(hash4_Wheel, null3.x, null3.y, null3.z, true, 1, -1, &RLWheel1, true, false, false);


										int RFWheel1;
										OBJECT::CREATE_OBJECT(hash4_Wheel, null4.x, null4.y, null4.z, true, 1, -1, &RFWheel1, true, false, false);

										int RRWheel1;
										OBJECT::CREATE_OBJECT(hash4_Wheel, null5.x, null5.y, null5.z, true, 1, -1, &RRWheel1, true, false, false);


										if (ENTITY::DOES_ENTITY_EXIST(EMP) && ENTITY::DOES_ENTITY_EXIST(MiniGun) && ENTITY::DOES_ENTITY_EXIST(MiniGun2) && ENTITY::DOES_ENTITY_EXIST(FLWheel1) && ENTITY::DOES_ENTITY_EXIST(RLWheel1) && ENTITY::DOES_ENTITY_EXIST(RFWheel1) && ENTITY::DOES_ENTITY_EXIST(RRWheel1))
										{

											int Vehicle = VEHICLE::CREATE_VEHICLE(hash_T20, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
											if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
											{
												PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
												STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_T20);
												ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
												ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, true);

												ENTITY::ATTACH_ENTITY_TO_ENTITY(EMP, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun2, Vehicle, 0, a0.x, a0.y, a0.z, b0.x, b0.y, b0.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(FLWheel1, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(RLWheel1, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(RFWheel1, Vehicle, 0, a4.x, a4.y, a4.z, b4.x, b4.y, b4.z, 0, 1, 0, 0, 2, 1);
												ENTITY::ATTACH_ENTITY_TO_ENTITY(RRWheel1, Vehicle, 0, a5.x, a5.y, a5.z, b5.x, b5.y, b5.z, 0, 1, 0, 0, 2, 1);

											}

										}

									}
								});
							}

							if (ImGui::Button("Boat - Trailer"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = -0.61, a.z = 0.28;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("boattrailer");
									int hash2 = GAMEPLAY::GET_HASH_KEY("suntrap");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
											ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);

										}

									}
								});
							}


							if (ImGui::Button("Flatbed - T20"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = -2.0, a.z = 1.1;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									Vector3 null1; null1.x = 0, null1.y = 0; null1.z = 0;
									Vector3 a1; a1.x = -1.06, a1.y = -0.1, a1.z = 0.46;
									Vector3 b1; b1.x = 91.0, b1.y = 0, b1.z = 0;
									Vector3 null2; null2.x = 0, null2.y = 0; null2.z = 0;
									Vector3 a2; a2.x = -0.9, a2.y = 0.61, a2.z = 0.62;
									Vector3 b2; b2.x = 0.0, b2.y = 100.0, b2.z = 0;
									Vector3 null3; null3.x = 0, null3.y = 0; null3.z = 0;
									Vector3 a3; a3.x = 0.9, a3.y = 0.8, a3.z = 0.41;
									Vector3 b3; b3.x = -25.0, b3.y = 0, b3.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("flatbed");
									int hash2 = GAMEPLAY::GET_HASH_KEY("t20");
									int hash3 = GAMEPLAY::GET_HASH_KEY("prop_tool_broom");
									int hash4 = GAMEPLAY::GET_HASH_KEY("prop_roadcone01a");
									int hash5 = GAMEPLAY::GET_HASH_KEY("prop_tool_box_02");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									STREAMING::REQUEST_MODEL(hash3);
									STREAMING::REQUEST_MODEL(hash4);
									STREAMING::REQUEST_MODEL(hash5);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash3) && STREAMING::HAS_MODEL_LOADED(hash4) && STREAMING::HAS_MODEL_LOADED(hash5))
									{



										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);

										int Broom;
										OBJECT::CREATE_OBJECT(hash3, null1.x, null1.y, null1.z, true, 1, -1, &Broom, true, false, false);

										int Cone;
										OBJECT::CREATE_OBJECT(hash4, null2.x, null2.y, null2.z, true, 1, -1, &Cone, true, false, false);

										int Tool;
										OBJECT::CREATE_OBJECT(hash5, null3.x, null3.y, null3.z, true, 1, -1, &Tool, true, false, false);






										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::DOES_ENTITY_EXIST(Broom) && ENTITY::DOES_ENTITY_EXIST(Cone) && ENTITY::DOES_ENTITY_EXIST(Tool))
										{
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, (char*)"Solitary");
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Broom, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, false, 0, 0, 2, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Cone, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, false, 0, 0, 2, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Tool, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, false, 0, 0, 2, true);
											ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);

										}

									}
								});
							}

							if (ImGui::Button("Jetsky - Trailer"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0.;
									Vector3 a; a.x = -0.625, a.y = -1.9, a.z = -0.09;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									Vector3 a1; a1.x = 0.625, a1.y = -1.9, a1.z = -0.09;
									Vector3 b1; b1.x = 0, b1.y = 0, b1.z = 0;

									Vector3 a2; a2.x = 0.0, a2.y = 0.9, a2.z = -0.45;
									Vector3 b2; b2.x = 0, b2.y = 0, b2.z = 180.0;

									int hash = GAMEPLAY::GET_HASH_KEY("boattrailer");
									int hash2 = GAMEPLAY::GET_HASH_KEY("seashark");
									int hash3 = GAMEPLAY::GET_HASH_KEY("prop_tool_box_05");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									STREAMING::REQUEST_MODEL(hash3);

									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash3))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object1 = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);

										int Object2;
										OBJECT::CREATE_OBJECT(hash3, null.x, null.y, null.z, true, 1, -1, &Object2, true, false, false);

										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::DOES_ENTITY_EXIST(Object1) && ENTITY::DOES_ENTITY_EXIST(Object2))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object1, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, false, 0, 0, 2, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object2, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, false, 0, 0, 2, true);
											ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
											ENTITY::SET_ENTITY_COLLISION(Object1, 1, 0);

										}

									}
								});
							}


							if (ImGui::Button("Ramp Truck"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 10.0, a.z = -0.3;
									Vector3 b; b.x = 0, b.y = -147.0, b.z = 90.0;
									int hash = GAMEPLAY::GET_HASH_KEY("phantom");
									int hash2 = GAMEPLAY::GET_HASH_KEY("prop_lev_des_barge_01");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);

										int Object;
										OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, true, 1, -1, &Object, true, false, false);

										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
											ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);

										}

									}
								});
							}

							if (ImGui::Button("Monster Swat"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("monster");
									int hash2 = GAMEPLAY::GET_HASH_KEY("riot");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}

									}
								});
							}

							if (ImGui::Button("Buffulo Police"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("police2");
									int hash2 = GAMEPLAY::GET_HASH_KEY("buffalo2");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Vehicle, 5);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Object, 0, 0);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}

									}
								});
							}

							if (ImGui::Button("Insurget V2"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("insurgent");
									int hash2 = GAMEPLAY::GET_HASH_KEY("insurgent2");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}

									}
								});

							}


							if (ImGui::Button("Super - 1"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = -0.25;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("t20");
									int hash2 = GAMEPLAY::GET_HASH_KEY("cheetah");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}

									}
								});
							}


							if (ImGui::Button("Super - 2"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("feltzer2");
									int hash2 = GAMEPLAY::GET_HASH_KEY("rapidgt");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}

									}
								});

							}


							if (ImGui::Button("Muscle - 1"))
							{
								g_FiberScript->addTask([] {

									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = -0.2;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("hotknife");
									int hash2 = GAMEPLAY::GET_HASH_KEY("jb700");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}

									}
								});
							}

							if (ImGui::Button("Muscle - 2"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 2.0;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("coquette2");
									int hash2 = GAMEPLAY::GET_HASH_KEY("hotknife");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}

									}
								});
							}


							if (ImGui::Button("Zentorno - Kuruma"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("zentorno");
									int hash2 = GAMEPLAY::GET_HASH_KEY("kuruma2");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, (char*)"Solitary");
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}

									}
								});
							}


							if (ImGui::Button("Special Helicopter"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 1, a.z = 0.8;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("buzzard");
									int hash2 = GAMEPLAY::GET_HASH_KEY("submersible");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 255, 149, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}

									}
								});
							}



							if (ImGui::Button("SlamVan"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = -2.0, a.z = 1.1;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									Vector3 null1; null1.x = 0, null1.y = 0; null1.z = 0;
									Vector3 a1; a1.x = -1.06, a1.y = -0.1, a1.z = 0.46;
									Vector3 b1; b1.x = 91.0, b1.y = 0, b1.z = 0;
									Vector3 null2; null2.x = 0, null2.y = 0; null2.z = 0;
									Vector3 a2; a2.x = -0.9, a2.y = 0.61, a2.z = 0.62;
									Vector3 b2; b2.x = 0.0, b2.y = 100.0, b2.z = 0;
									Vector3 null3; null3.x = 0, null3.y = 0; null3.z = 0;
									Vector3 a3; a3.x = 0.9, a3.y = 0.8, a3.z = 0.41;
									Vector3 b3; b3.x = -25.0, b3.y = 0, b3.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("flatbed");
									int hash2 = GAMEPLAY::GET_HASH_KEY("slamvan2");
									int hash3 = GAMEPLAY::GET_HASH_KEY("prop_tool_broom");
									int hash4 = GAMEPLAY::GET_HASH_KEY("prop_roadcone01a");
									int hash5 = GAMEPLAY::GET_HASH_KEY("prop_tool_box_02");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									STREAMING::REQUEST_MODEL(hash3);
									STREAMING::REQUEST_MODEL(hash4);
									STREAMING::REQUEST_MODEL(hash5);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash3) && STREAMING::HAS_MODEL_LOADED(hash4) && STREAMING::HAS_MODEL_LOADED(hash5))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Broom;
										OBJECT::CREATE_OBJECT(hash3, null1.x, null1.y, null1.z, true, 1, -1, &Broom, true, false, false);

										int Cone;
										OBJECT::CREATE_OBJECT(hash4, null2.x, null2.y, null2.z, true, 1, -1, &Cone, true, false, false);

										int Tool;
										OBJECT::CREATE_OBJECT(hash5, null3.x, null3.y, null3.z, true, 1, -1, &Tool, true, false, false);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::DOES_ENTITY_EXIST(Broom) && ENTITY::DOES_ENTITY_EXIST(Cone) && ENTITY::DOES_ENTITY_EXIST(Tool))
										{
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 8, 17, 30);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 30, 1);
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Object, 92, 0);
											VEHICLE::SET_VEHICLE_COLOURS(Object, 12, 53);
											VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, (char*)"Solitary");
											VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Object, 1);
											VEHICLE::TOGGLE_VEHICLE_MOD(Object, 18, 1);
											VEHICLE::TOGGLE_VEHICLE_MOD(Object, 22, 1);
											VEHICLE::SET_VEHICLE_MOD(Object, 11, 3, 0);
											VEHICLE::SET_VEHICLE_MOD(Object, 14, 14, 0);
											VEHICLE::SET_VEHICLE_MOD(Object, 15, 3, 0);
											VEHICLE::SET_VEHICLE_MOD(Object, 13, 2, 0);
											VEHICLE::SET_VEHICLE_WHEEL_TYPE(Object, 6);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_MOD(Object, 23, 18, 1);
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Broom, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, false, 0, 0, 2, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Cone, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, false, 0, 0, 2, true);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Tool, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, false, 0, 0, 2, true);

										}

									}
								});
							}


							if (ImGui::Button("Driving Train"))
							{
								g_FiberScript->addTask([] {
									uint Me = PLAYER::PLAYER_PED_ID();
									Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
									Vector3 null; null.x = 0, null.y = 0; null.z = 0;
									Vector3 a; a.x = 0, a.y = 0, a.z = 0;
									Vector3 b; b.x = 0, b.y = 0, b.z = 0;
									int hash = GAMEPLAY::GET_HASH_KEY("zentorno");
									int hash2 = GAMEPLAY::GET_HASH_KEY("freight");
									STREAMING::REQUEST_MODEL(hash);
									STREAMING::REQUEST_MODEL(hash2);
									if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
									{
										int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
										if (ENTITY::DOES_ENTITY_EXIST(Vehicle) && ENTITY::DOES_ENTITY_EXIST(Object))
										{
											STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
											PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
											ENTITY::SET_ENTITY_VISIBLE(Object, true, true);
											VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
											VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
											VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, (char*)"sm");
											VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
											VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
											ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

										}
									}
								});
							}


							ImGui::EndChild();
							ImGui::PopStyleVar();
						}

						break;
						case 3:


							{
								ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
								ImGui::BeginChild("basicvehopt", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
								if (ImGui::BeginMenuBar())
								{
									if (ImGui::BeginMenu("Basic Options"))
									{
										ImGui::EndMenu();
									}
									ImGui::EndMenuBar();
								}

								if(ImGui::Checkbox("Godmode", &Features::cargodmodebool))
								{
									g_FiberScript->addTask([] {
										Memory::set_value<int>({ 0x08, 0xD30, 0x189 }, Features::cargodmodebool);
									});
								}
								ImGui::Checkbox("Invisible", &Features::InvisibleCarBool);
								ImGui::Checkbox("Flying Car", &Features::FlyingCarBool);

								ImGui::Checkbox("Hornboost", &Features::hornboostbool);
								ImGui::Checkbox("Seatbelt", &Features::seatbeltbool);
								ImGui::Checkbox("Hacker Plate", &Features::MatrixPlates);
								ImGui::Checkbox("Drift Mode", &Features::DriftModeBool);
								ImGui::Checkbox("Fix Vehicle Loop", &Features::FixLoop);
								if (ImGui::Button("One time Fix"))
								{
									g_FiberScript->addTask([] {
										Features::FixCar();
									});
								}


								if (ImGui::Button("Add Ramp"))
								{
									g_FiberScript->addTask([] {
										if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
										{
											Vector3 Him = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
											Him.z = Him.z;
											int VehicleID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
											int hash2 = $("prop_lev_des_barge_01");
											STREAMING::REQUEST_MODEL(hash2);
											if (STREAMING::HAS_MODEL_LOADED(hash2))
											{
												Entity My_Objects;
												OBJECT::CREATE_OBJECT(hash2, Him.x, Him.y, Him.z, true, 1, -1, &My_Objects, true, false, false);

												if (ENTITY::DOES_ENTITY_EXIST(My_Objects))
												{
													ENTITY::SET_ENTITY_COLLISION(My_Objects, true, true);
													ENTITY::SET_ENTITY_ALPHA(My_Objects, 120, false);
													uint Me = PLAYER::PLAYER_PED_ID();
													Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
													Vector3 null; null.x = 0, null.y = 0; null.z = 0;
													Vector3 a; a.x = 0, a.y = 10.0, a.z = -0.3;
													Vector3 b; b.x = 0, b.y = -147.0, b.z = 90.0;
													ENTITY::ATTACH_ENTITY_TO_ENTITY(My_Objects, VehicleID, 0, a.x, 6.3, a.z, b.x, b.y, b.z, 0, false, true, 0, 2, true);
												}
											}
										}
									});
								}

								if (ImGui::Button("Remove Ramp"))
								{
									g_FiberScript->addTask([] {
										if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
										{
											Vector3 Him = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
											Him.z = Him.z;
											GAMEPLAY::CLEAR_AREA_OF_OBJECTS(Him.x, Him.y, Him.z, 2, 0);

											Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Him.x, Him.y, Him.z, 4.0, $("prop_lev_des_barge_01"), 0, 0, 1);
											if (ENTITY::DOES_ENTITY_EXIST(obj))
											{

												ENTITY::SET_ENTITY_COLLISION(obj, true, true);
												ENTITY::SET_ENTITY_ALPHA(obj, 0, false);
												ENTITY::DELETE_ENTITY(&obj);

												ENTITY::DETACH_ENTITY(obj, 0, 0);
											}

										}
									});
								}




								if (ImGui::Button("Start Autopilot"))
								{
									startautopilot = true;
								}

								if (ImGui::Button("Stop Autopilot"))
								{
									stopautopilot = true;
								}



								if (ImGui::Button("Upgrade Vehicle"))
								{
									Features::maxvehicle();
								}

								ImGui::Text("Numberplate Text: ");
								ImGui::InputText("", numberplatetxt, sizeof(numberplatetxt));
								if (ImGui::Button("Set Text")) {
									SetNumberPlateTXT = true;
								}


								ImGui::EndChild();
								ImGui::PopStyleVar();
							}


							ImGui::SameLine(0.0, 380.0f);



							{
								ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
								ImGui::BeginChild("advancedvehopt", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
								if (ImGui::BeginMenuBar())
								{
									if (ImGui::BeginMenu("Advanced Options"))
									{
										ImGui::EndMenu();
									}
									ImGui::EndMenuBar();
								}

							ImGui::SliderInt("Hornboost Speed", &Features::hornboostspeed, 5, 4000);
							if (ImGui::Checkbox("Disable Gravity", &Features::vehiclegravitybool))
							{
								if (Features::vehiclegravitybool)
									GAMEPLAY::SET_GRAVITY_LEVEL(3);
								else
									GAMEPLAY::SET_GRAVITY_LEVEL(0);
							}
							ImGui::Checkbox("Better Vehicle Fly", &Features::BetterFlyingCarBool);
							ImGui::Checkbox("Stick Vehicle", &Features::StickyBool);
							if (ImGui::Button("Open All Doors"))
							{
								g_FiberScript->addTask([] {
									Features::OpenDoors();
								});

							}
							if (ImGui::Button("Close All Doors"))
							{
								g_FiberScript->addTask([] {
								VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
								});
							}
							if (ImGui::Button("Wash Car"))
							{
								g_FiberScript->addTask([] {
								VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
								});

							}

							if (ImGui::Button("Delete current Vehicle"))
							{
								deleteveh = true;
							}




								ImGui::EndChild();
								ImGui::PopStyleVar();
							}


							ImGui::NewLine();
							ImGui::SameLine(0.0, 420.0f);

							{
								ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
								ImGui::BeginChild("vehcolor", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
								if (ImGui::BeginMenuBar())
								{
									if (ImGui::BeginMenu("Custom Color Selector"))
									{
										ImGui::EndMenu();
									}
									ImGui::EndMenuBar();


									if (ImGui::ColorEdit3("Vehicle Color (Click)", color, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions))
									{


										VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), (int)(color[0] * 255), (int)(color[1] * 255), (int)(color[2] * 255));

										VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), (int)(color[0] * 255), (int)(color[1] * 255), (int)(color[2] * 255));

									}

									ImGui::Checkbox("Rainbow Color", &Features::rainbowbool);
									ImGui::Checkbox("Random Color", &Features::RainbowPaintLoop);


									
									if (ImGui::ListBox("Headlight Color", &Lists::headlightcolor, HeadlightColor, IM_ARRAYSIZE(HeadlightColor), 8))
									{
										VEHICLE::_SET_HEADLIGHT_COLOR(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), Lists::headlightcolor);
									}
						



									ImGui::Text("For Custom Headlightcolor you need Xenon lights!");


								}

	



								ImGui::EndChild();
								ImGui::PopStyleVar();
							}



							{
								ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
								ImGui::BeginChild("movementveh", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
								if (ImGui::BeginMenuBar())
								{
									if (ImGui::BeginMenu("Nice Moves"))
									{
										ImGui::EndMenu();
									}
									ImGui::EndMenuBar();


								if (ImGui::Button("KickFlip"))
									{
									g_FiberScript->addTask([] {
										uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
										NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Vehicle);
										if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
											ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 10.71, 5.0, 0.0, 0.0, 1, false, true, true, true, true);
									});
									}


									if (ImGui::Button("Small Kickflip"))
									{
										g_FiberScript->addTask([] {
											uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
											NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Vehicle);
											if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
												ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 5.0, 5.0, 0.0, 0.0, 1, false, true, true, true, true);
										});
									}

									if (ImGui::Button("Big Kickflip"))
									{
										g_FiberScript->addTask([] {
										uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
										NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Vehicle);
										if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
											ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 23.4, 7.09, 0.0, 0.0, 1, false, true, true, true, true);
										});
									}

									if (ImGui::Button("Double Kickflip"))
									{
										g_FiberScript->addTask([] {
										uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
										NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Vehicle);
										if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
											ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 21.43, 20.0, 0.0, 0.0, 1, false, true, true, true, true);
										});
									}

									if (ImGui::Button("Frontflip"))
									{
										g_FiberScript->addTask([] {
										uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
										NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Vehicle);
										if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
											ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 10.71, 0.0, -0.4, 0.0, 1, false, true, true, true, true);
										});
									}
										if (ImGui::Button("Backflip"))
										{
											g_FiberScript->addTask([] {
											uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
											NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Vehicle);
											if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
												ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 10.71, 0.0, 0.4, 0.0, 1, false, true, true, true, true);
											});
										}




								}




								ImGui::EndChild();
								ImGui::PopStyleVar();
							}


							ImGui::SameLine(0.0, 380.0f);

								{
									ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
									ImGui::BeginChild("vehstyleptfx", ImVec2(500, 200), true, ImGuiWindowFlags_MenuBar);
									if (ImGui::BeginMenuBar())
									{
										if (ImGui::BeginMenu("Vehicle Effects"))
										{
											ImGui::EndMenu();
										}
										ImGui::EndMenuBar();
									}


									ImGui::Checkbox("Lighting", &Features::CarLightning);

									ImGui::Checkbox("Clown Effect", &Features::CarClownLoop);

									ImGui::Checkbox("Firework", &Features::Carfireworkloop);

									ImGui::Checkbox("Alien 1", &Features::Caralien1);

									ImGui::Checkbox("Alien 2", &Features::Caralien2);

									ImGui::Checkbox("Electric", &Features::Carelectric);

									ImGui::Checkbox("Burial Dirt", &Features::moneyeffect15);

									ImGui::Checkbox("Ghost Rider", &Features::ghooosoot);

									ImGui::EndChild();
									ImGui::PopStyleVar();
								}




								break;
							case 4:




								ImGui::SameLine(0.0, 420.0f);

							{
								ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
								ImGui::BeginChild("tptowaypo", ImVec2(500, 70), true, ImGuiWindowFlags_MenuBar);
								if (ImGui::BeginMenuBar())
								{
									if (ImGui::BeginMenu("Teleport to Waypoint"))
									{
										ImGui::EndMenu();
									}
									ImGui::EndMenuBar();


									if (ImGui::Button("Teleport to Waypoint"))
									{
										g_FiberScript->addTask([] {
										int WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);
										if (UI::DOES_BLIP_EXIST(WaypointHandle)) {
											Vector3 coords = UI::GET_BLIP_COORDS(WaypointHandle);
											Entity e = PLAYER::PLAYER_PED_ID();
											if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
											{
												e = PED::GET_VEHICLE_PED_IS_USING(e);
											}

											bool groundFound = false;
											static float groundCheckHeight[] =
											{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
											for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
											{
												ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
												Sleep(100);
												if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
												{
													groundFound = true;
													coords.z += 3.0;
													break;
												}
											}
											if (!groundFound)
											{
												coords.z = 100.0f;
												WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
											}
											teleport_to_coords(e, coords);

										}
										});
									}
								}


	
								ImGui::EndChild();
								ImGui::PopStyleVar();
							}





							{
								ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
								ImGui::BeginChild("normalloctp", ImVec2(500, 400), true, ImGuiWindowFlags_MenuBar);
								if (ImGui::BeginMenuBar())
								{
									if (ImGui::BeginMenu("Normal Locations"))
									{
										ImGui::EndMenu();
									}
									ImGui::EndMenuBar();
								}
									if (ImGui::Button("Strip Club"))
									{
										Vector3 Coords;
										Coords.x = 126.135f; Coords.y = -1278.583f; Coords.z = 29.270f; TPPPP(Coords);
									}
									if (ImGui::Button("Police Station"))
									{
										Vector3 Coords;
										Coords.x = 436.491f; Coords.y = -982.172f; Coords.z = 30.699f; TPPPP(Coords);
									}
									if (ImGui::Button("Burnt FIB"))
									{
										Vector3 Coords; Coords.x = 160.868f; Coords.y = -745.831f; Coords.z = 250.063f; TPPPP(Coords);
									}
									if (ImGui::Button("Pacific Standard Vault"))
									{
										Vector3 Coords; Coords.x = 255.851f; Coords.y = 217.030f; Coords.z = 101.683f; TPPPP(Coords);
									}
									if (ImGui::Button("Lester's House"))
									{
										Vector3 Coords; Coords.x = 1273.898f; Coords.y = -1719.304f; Coords.z = 54.771f; TPPPP(Coords);
									}
									if (ImGui::Button("IAA Office"))
									{
										Vector3 Coords; Coords.x = 117.220f; Coords.y = -620.938f; Coords.z = 206.047f; TPPPP(Coords);
									}
									if (ImGui::Button("Torture Room"))
									{
										Vector3 Coords; Coords.x = 147.170f; Coords.y = -2201.804f; Coords.z = 4.688f; TPPPP(Coords);
									}



									if (ImGui::Button("Hippy Camp"))
									{
										Vector3 Coords; Coords.x = 2476.712f; Coords.y = 3789.645f; Coords.z = 41.226f; TPPPP(Coords);
									}
									if (ImGui::Button("Weed Farm"))
									{
										Vector3 Coords; Coords.x = 2208.777f; Coords.y = 5578.235f; Coords.z = 53.735f; TPPPP(Coords);
									}

									if (ImGui::Button("Casino"))
									{
										Vector3 Coords; Coords.x = 925.329f; Coords.y = 46.152f; Coords.z = 80.908f; TPPPP(Coords);
									}
									if (ImGui::Button("Prison"))
									{
										Vector3 Coords; Coords.x = 1679.049f; Coords.y = 2513.711f; Coords.z = 45.565f; TPPPP(Coords);
									}

									if (ImGui::Button("Mount Chiliad"))
									{
										Vector3 Coords; Coords.x = 496.75f; Coords.y = 5591.17f; Coords.z = 795.03f; TPPPP(Coords);
									}
									if (ImGui::Button("Maze Bank")) { Vector3 Coords; Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f; TPPPP(Coords); };

									if (ImGui::Button("Military Base")) { Vector3 Coords; Coords.x = -2012.8470f; Coords.y = 2956.5270f; Coords.z = 32.8101f; TPPPP(Coords); }

									if (ImGui::Button("Zancudo Tower")) { Vector3 Coords; Coords.x = -2356.0940; Coords.y = 3248.645; Coords.z = 101.4505; TPPPP(Coords); }
									if (ImGui::Button("Mask Shop")) { Vector3 Coords; Coords.x = -1338.16; Coords.y = -1278.11; Coords.z = 4.87; TPPPP(Coords); }
									if (ImGui::Button("LS Customs")) { Vector3 Coords; Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31; TPPPP(Coords); }
									if (ImGui::Button("Ammunation")) { Vector3 Coords; Coords.x = 247.3652; Coords.y = -45.8777; Coords.z = 69.9411; TPPPP(Coords); }
									if (ImGui::Button("Airport")) { Vector3 Coords; Coords.x = -1102.2910f; Coords.y = -2894.5160f; Coords.z = 13.9467f; TPPPP(Coords); }
									if (ImGui::Button("Clothes Store")) { Vector3 Coords; Coords.x = -718.91; Coords.y = -158.16; Coords.z = 37.00; TPPPP(Coords); }
									if (ImGui::Button("Waterfall")) { Vector3 Coords; Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f; TPPPP(Coords); }
									if (ImGui::Button("FIB")) { Vector3 Coords; Coords.x = 135.5220f; Coords.y = -749.0003f; Coords.z = 260.0000f; TPPPP(Coords); }
									if (ImGui::Button("Humane Labs")) { Vector3 Coords; Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f; TPPPP(Coords); }
									if (ImGui::Button("MMI")) { Vector3 Coords; Coords.x = -222.1977; Coords.y = -1185.8500; Coords.z = 23.0294; TPPPP(Coords); }
									if (ImGui::Button("Sandy Shores Airfield")) { Vector3 Coords; Coords.x = 1741.4960f; Coords.y = 3269.2570f; Coords.z = 41.6014f; TPPPP(Coords); }
			


								ImGui::EndChild();
								ImGui::PopStyleVar();
							}

							ImGui::SameLine(0.0, 380.0f);
							{
								ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
								ImGui::BeginChild("tpiplloc", ImVec2(500, 400), true, ImGuiWindowFlags_MenuBar);
								if (ImGui::BeginMenuBar())
								{
									if (ImGui::BeginMenu("IPL Locations"))
									{
										ImGui::EndMenu();
									}
									ImGui::EndMenuBar();
								}

								if (ImGui::Button("Cayo Perico"))
								{
									g_FiberScript->addTask([] {
										static const char* ipls[] = { "h4_islandx_terrain_01_lod",  "h4_islandx_terrain_01_slod",  "h4_islandx_terrain_02",  "h4_islandx_terrain_02_lod",  "h4_islandx_terrain_02_slod",  "h4_islandx_terrain_03",  "h4_islandx_terrain_03_lod",  "h4_islandx_terrain_04",  "h4_islandx_terrain_04_lod",  "h4_islandx_terrain_04_slod",  "h4_islandx_terrain_05",  "h4_islandx_terrain_05_lod",  "h4_islandx_terrain_05_slod",  "h4_islandx_terrain_06",  "h4_mph4_terrain_01_grass_0",  "h4_mph4_terrain_01_grass_1",  "h4_mph4_terrain_02_grass_0",  "h4_mph4_terrain_02_grass_1",  "h4_mph4_terrain_02_grass_2",  "h4_mph4_terrain_02_grass_3",  "h4_mph4_terrain_04_grass_0",  "h4_mph4_terrain_04_grass_1",  "h4_mph4_terrain_05_grass_0",  "h4_mph4_terrain_06_grass_0", "h4_islandx_terrain_06_lod",  "h4_islandx_terrain_06_slod",  "h4_islandx_terrain_props_05_a",  "h4_islandx_terrain_props_05_a_lod",  "h4_islandx_terrain_props_05_b",  "h4_islandx_terrain_props_05_b_lod",  "h4_islandx_terrain_props_05_c",  "h4_islandx_terrain_props_05_c_lod",  "h4_islandx_terrain_props_05_d",  "h4_islandx_terrain_props_05_d_lod",  "h4_islandx_terrain_props_05_d_slod",  "h4_islandx_terrain_props_05_e",  "h4_islandx_terrain_props_05_e_lod",  "h4_islandx_terrain_props_05_e_slod",  "h4_islandx_terrain_props_05_f",  "h4_islandx_terrain_props_05_f_lod",  "h4_islandx_terrain_props_05_f_slod",  "h4_islandx_terrain_props_06_a",  "h4_islandx_terrain_props_06_a_lod",  "h4_islandx_terrain_props_06_a_slod",  "h4_islandx_terrain_props_06_b",  "h4_islandx_terrain_props_06_b_lod",  "h4_islandx_terrain_props_06_b_slod",  "h4_islandx_terrain_props_06_c",  "h4_islandx_terrain_props_06_c_lod",  "h4_islandx_terrain_props_06_c_slod",  "h4_mph4_terrain_01",  "h4_mph4_terrain_01_long_0",  "h4_mph4_terrain_02",  "h4_mph4_terrain_03",  "h4_mph4_terrain_04",  "h4_mph4_terrain_05",  "h4_mph4_terrain_06",  "h4_mph4_terrain_06_strm_0",  "h4_mph4_terrain_lod",  "h4_mph4_terrain_occ_00",  "h4_mph4_terrain_occ_01",  "h4_mph4_terrain_occ_02",  "h4_mph4_terrain_occ_03",  "h4_mph4_terrain_occ_04",  "h4_mph4_terrain_occ_05",  "h4_mph4_terrain_occ_06",  "h4_mph4_terrain_occ_07",  "h4_mph4_terrain_occ_08",  "h4_mph4_terrain_occ_09",  "h4_boatblockers",  "h4_islandx",  "h4_islandx_disc_strandedshark",  "h4_islandx_disc_strandedshark_lod",  "h4_islandx_disc_strandedwhale",  "h4_islandx_disc_strandedwhale_lod",  "h4_islandx_props",  "h4_islandx_props_lod",  "h4_islandx_sea_mines",  "h4_mph4_island",  "h4_mph4_island_long_0",  "h4_mph4_island_strm_0",  "h4_aa_guns",  "h4_aa_guns_lod",  "h4_beach",  "h4_beach_bar_props",  "h4_beach_lod",  "h4_beach_party",  "h4_beach_party_lod",  "h4_beach_props",  "h4_beach_props_lod",  "h4_beach_props_party",  "h4_beach_props_slod",  "h4_beach_slod",  "h4_islandairstrip",  "h4_islandairstrip_doorsclosed",  "h4_islandairstrip_doorsclosed_lod",  "h4_islandairstrip_doorsopen",  "h4_islandairstrip_doorsopen_lod",  "h4_islandairstrip_hangar_props",  "h4_islandairstrip_hangar_props_lod",  "h4_islandairstrip_hangar_props_slod",  "h4_islandairstrip_lod",  "h4_islandairstrip_props",  "h4_islandairstrip_propsb",  "h4_islandairstrip_propsb_lod",  "h4_islandairstrip_propsb_slod",  "h4_islandairstrip_props_lod",  "h4_islandairstrip_props_slod",  "h4_islandairstrip_slod",  "h4_islandxcanal_props",  "h4_islandxcanal_props_lod",  "h4_islandxcanal_props_slod",  "h4_islandxdock",  "h4_islandxdock_lod",  "h4_islandxdock_props",  "h4_islandxdock_props_2",  "h4_islandxdock_props_2_lod",  "h4_islandxdock_props_2_slod",  "h4_islandxdock_props_lod",  "h4_islandxdock_props_slod",  "h4_islandxdock_slod",  "h4_islandxdock_water_hatch",  "h4_islandxtower",  "h4_islandxtower_lod",  "h4_islandxtower_slod",  "h4_islandxtower_veg",  "h4_islandxtower_veg_lod",  "h4_islandxtower_veg_slod",  "h4_islandx_barrack_hatch",  "h4_islandx_barrack_props",  "h4_islandx_barrack_props_lod",  "h4_islandx_barrack_props_slod",  "h4_islandx_checkpoint",  "h4_islandx_checkpoint_lod",  "h4_islandx_checkpoint_props",  "h4_islandx_checkpoint_props_lod",  "h4_islandx_checkpoint_props_slod",  "h4_islandx_maindock",  "h4_islandx_maindock_lod",  "h4_islandx_maindock_props",  "h4_islandx_maindock_props_2",  "h4_islandx_maindock_props_2_lod",  "h4_islandx_maindock_props_2_slod",  "h4_islandx_maindock_props_lod",  "h4_islandx_maindock_props_slod",  "h4_islandx_maindock_slod",  "h4_islandx_mansion",  "h4_islandx_mansion_b",  "h4_islandx_mansion_b_lod",  "h4_islandx_mansion_b_side_fence",  "h4_islandx_mansion_b_slod",  "h4_islandx_mansion_entrance_fence",  "h4_islandx_mansion_guardfence",  "h4_islandx_mansion_lights",  "h4_islandx_mansion_lockup_01",  "h4_islandx_mansion_lockup_01_lod",  "h4_islandx_mansion_lockup_02",  "h4_islandx_mansion_lockup_02_lod",  "h4_islandx_mansion_lockup_03",  "h4_islandx_mansion_lockup_03_lod",  "h4_islandx_mansion_lod",  "h4_islandx_mansion_office",  "h4_islandx_mansion_office_lod",  "h4_islandx_mansion_props",  "h4_islandx_mansion_props_lod",  "h4_islandx_mansion_props_slod",  "h4_islandx_mansion_slod",  "h4_islandx_mansion_vault",  "h4_islandx_mansion_vault_lod",  "h4_island_padlock_props",  "h4_mansion_gate_broken",  "h4_mansion_gate_closed",  "h4_mansion_remains_cage",  "h4_mph4_airstrip",  "h4_mph4_airstrip_interior_0_airstrip_hanger",  "h4_mph4_beach",  "h4_mph4_dock",  "h4_mph4_island_lod",  "h4_mph4_island_ne_placement",  "h4_mph4_island_nw_placement",  "h4_mph4_island_se_placement",  "h4_mph4_island_sw_placement",  "h4_mph4_mansion",  "h4_mph4_mansion_b",  "h4_mph4_mansion_b_strm_0",  "h4_mph4_mansion_strm_0",  "h4_mph4_wtowers",  "h4_ne_ipl_00",  "h4_ne_ipl_00_lod",  "h4_ne_ipl_00_slod",  "h4_ne_ipl_01",  "h4_ne_ipl_01_lod",  "h4_ne_ipl_01_slod",  "h4_ne_ipl_02",  "h4_ne_ipl_02_lod",  "h4_ne_ipl_02_slod",  "h4_ne_ipl_03",  "h4_ne_ipl_03_lod",  "h4_ne_ipl_03_slod",  "h4_ne_ipl_04",  "h4_ne_ipl_04_lod",  "h4_ne_ipl_04_slod",  "h4_ne_ipl_05",  "h4_ne_ipl_05_lod",  "h4_ne_ipl_05_slod",  "h4_ne_ipl_06",  "h4_ne_ipl_06_lod",  "h4_ne_ipl_06_slod",  "h4_ne_ipl_07",  "h4_ne_ipl_07_lod",  "h4_ne_ipl_07_slod",  "h4_ne_ipl_08",  "h4_ne_ipl_08_lod",  "h4_ne_ipl_08_slod",  "h4_ne_ipl_09",  "h4_ne_ipl_09_lod",  "h4_ne_ipl_09_slod",  "h4_nw_ipl_00",  "h4_nw_ipl_00_lod",  "h4_nw_ipl_00_slod",  "h4_nw_ipl_01",  "h4_nw_ipl_01_lod",  "h4_nw_ipl_01_slod",  "h4_nw_ipl_02",  "h4_nw_ipl_02_lod",  "h4_nw_ipl_02_slod",  "h4_nw_ipl_03",  "h4_nw_ipl_03_lod",  "h4_nw_ipl_03_slod",  "h4_nw_ipl_04",  "h4_nw_ipl_04_lod",  "h4_nw_ipl_04_slod",  "h4_nw_ipl_05",  "h4_nw_ipl_05_lod",  "h4_nw_ipl_05_slod",  "h4_nw_ipl_06",  "h4_nw_ipl_06_lod",  "h4_nw_ipl_06_slod",  "h4_nw_ipl_07",  "h4_nw_ipl_07_lod",  "h4_nw_ipl_07_slod",  "h4_nw_ipl_08",  "h4_nw_ipl_08_lod",  "h4_nw_ipl_08_slod",  "h4_nw_ipl_09",  "h4_nw_ipl_09_lod",  "h4_nw_ipl_09_slod",  "h4_se_ipl_00",  "h4_se_ipl_00_lod",  "h4_se_ipl_00_slod",  "h4_se_ipl_01",  "h4_se_ipl_01_lod",  "h4_se_ipl_01_slod",  "h4_se_ipl_02",  "h4_se_ipl_02_lod",  "h4_se_ipl_02_slod",  "h4_se_ipl_03",  "h4_se_ipl_03_lod",  "h4_se_ipl_03_slod",  "h4_se_ipl_04",  "h4_se_ipl_04_lod",  "h4_se_ipl_04_slod",  "h4_se_ipl_05",  "h4_se_ipl_05_lod",  "h4_se_ipl_05_slod",  "h4_se_ipl_06",  "h4_se_ipl_06_lod",  "h4_se_ipl_06_slod",  "h4_se_ipl_07",  "h4_se_ipl_07_lod",  "h4_se_ipl_07_slod",  "h4_se_ipl_08",  "h4_se_ipl_08_lod",  "h4_se_ipl_08_slod",  "h4_se_ipl_09",  "h4_se_ipl_09_lod",  "h4_se_ipl_09_slod",  "h4_sw_ipl_00",  "h4_sw_ipl_00_lod",  "h4_sw_ipl_00_slod",  "h4_sw_ipl_01",  "h4_sw_ipl_01_lod",  "h4_sw_ipl_01_slod",  "h4_sw_ipl_02",  "h4_sw_ipl_02_lod",  "h4_sw_ipl_02_slod",  "h4_sw_ipl_03",  "h4_sw_ipl_03_lod",  "h4_sw_ipl_03_slod",  "h4_sw_ipl_04",  "h4_sw_ipl_04_lod",  "h4_sw_ipl_04_slod",  "h4_sw_ipl_05",  "h4_sw_ipl_05_lod",  "h4_sw_ipl_05_slod",  "h4_sw_ipl_06",  "h4_sw_ipl_06_lod",  "h4_sw_ipl_06_slod",  "h4_sw_ipl_07",  "h4_sw_ipl_07_lod",  "h4_sw_ipl_07_slod",  "h4_sw_ipl_08",  "h4_sw_ipl_08_lod",  "h4_sw_ipl_08_slod",  "h4_sw_ipl_09",  "h4_sw_ipl_09_lod",  "h4_sw_ipl_09_slod",  "h4_underwater_gate_closed",  "h4_islandx_placement_01",  "h4_islandx_placement_02",  "h4_islandx_placement_03",  "h4_islandx_placement_04",  "h4_islandx_placement_05",  "h4_islandx_placement_06",  "h4_islandx_placement_07",  "h4_islandx_placement_08",  "h4_islandx_placement_09",  "h4_islandx_placement_10",  "h4_mph4_island_placement" };

										for (auto ipl : ipls)
										{
											STREAMING::REQUEST_IPL((char*)ipl);
										}

										Entity entity = PLAYER::PLAYER_PED_ID();

										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, 4892.064, -4923.567, 3.500, 0, 0, 1);



										Vector3 Coords; Coords.x = 4892.064; Coords.y = -4923.567; Coords.z = 3.500; tpdich(Coords);
									});
								}


								if (ImGui::Button("North Yankton"))
								{
									g_FiberScript->addTask([] {
										Features::Yankton();
									});
								}
								if (ImGui::Button("Yacht"))
								{
									g_FiberScript->addTask([] {
										Features::Yacht();
									});
								}
								if (ImGui::Button("Aircraft Carrier"))
								{
									g_FiberScript->addTask([] {
										Features::Carrier();
									});
								}
								if (ImGui::Button("Sunken Cargo"))
								{
									g_FiberScript->addTask([] {
										Features::Carrier();
									});
								}
								if (ImGui::Button("Hospital"))
								{
									g_FiberScript->addTask([] {
										Features::Hospital();
									});
								}
								if (ImGui::Button("Farm"))
								{
									g_FiberScript->addTask([] {
										Features::Farm();
									});
								}
								if (ImGui::Button("Life Invader"))
								{
									g_FiberScript->addTask([] {
										Features::Invader();
									});
								}
								if (ImGui::Button("Jewelry Store"))
								{
									g_FiberScript->addTask([] {
										Features::Jewelry();
									});
								}
								if (ImGui::Button("Morgue"))
								{
									g_FiberScript->addTask([] {
										Features::Morgue();
									});
								}
		

								ImGui::EndChild();
								ImGui::PopStyleVar();
							}





								break;

								case 5:
								{
									ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
									ImGui::BeginChild("recoverstealth", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
									if (ImGui::BeginMenuBar())
									{
										if (ImGui::BeginMenu("Stealth Loop"))
										{
											ImGui::EndMenu();
										}
										ImGui::EndMenuBar();
									}

									ImGui::Text("Status: REMOVED");
									//ImGui::Checkbox("Enable Cash Adding", &Features::StealthBool);
									//if (ImGui::SliderInt("Cash Amount", &Features::StealthAmount, 1, 10000000))
									//{
									//	if (Features::StealthAmount == 10000001)
									//	{
									//		Features::StealthAmount = 10000000;
									//	}
									//}

			
									ImGui::EndChild();
									ImGui::PopStyleVar();
								}


								ImGui::SameLine(0.0, 380.0f);

								{
									ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
									ImGui::BeginChild("recoveryvehstealth", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
									if (ImGui::BeginMenuBar())
									{
										if (ImGui::BeginMenu("Vehicle Stealth"))
										{
											ImGui::EndMenu();
										}
										ImGui::EndMenuBar();

									}
									ImGui::Text("Status: REMOVED");
									//ImGui::Checkbox("Enable Vehicle Stealth", &Features::VehStealthBool);

									//if(ImGui::Button("Spawn Vehicle + TP to LSC"))
									//{
									//		Vector3 Coords;
									//		Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31;

									//		int Handle = PLAYER::PLAYER_PED_ID();
									//		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
									//		{
									//			ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
									//		}
									//		else
									//		{
									//			ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
									//		}

									//spawn_vehicle("WASHINGTON");
									//}

									//static int e = 0;
									//if (ImGui::RadioButton("61 Million", &e, 0))
									//{
									//	Features::KohleMoney = 61000000;
									//}ImGui::SameLine();

									//if (ImGui::RadioButton("2.1 Billion (restart needed)", &e, 1))
									//{
									//	Features::KohleMoney = 2100000000;
									//}

	


									ImGui::EndChild();
									ImGui::PopStyleVar();
								}

								ImGui::NewLine();
								ImGui::SameLine(0.0, 420.0f);

								{
									ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
									ImGui::BeginChild("recoveryrp", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
									if (ImGui::BeginMenuBar())
									{
										if (ImGui::BeginMenu("RP/Level Recovery"))
										{
											ImGui::EndMenu();
										}
										ImGui::EndMenuBar();
										ImGui::InputInt("", &instant);
										if (ImGui::Button("Apply Level instant (may crash)"))
										{
											setlevelinstant = true;
										}
										ImGui::SameLine();
										if (ImGui::Button("Apply Level (new session needed)"))
										{
											correctlevel = true;
										}
									}
									ImGui::EndChild();
									ImGui::PopStyleVar();
								}

								ImGui::NewLine();
								ImGui::SameLine(0.0, 420.0f);

								{
									ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
									ImGui::BeginChild("recoveryunlock", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
									if (ImGui::BeginMenuBar())
									{
										if (ImGui::BeginMenu("Account Unlocks"))
										{
											ImGui::EndMenu();
										}
										ImGui::EndMenuBar();



										if (ImGui::Button("Start Stats Editor"))
										{
											StatusEditor = true;
										}

										ImGui::Checkbox("Bunker Research", &Features::BunkerBool);

										if (ImGui::Button("Unlock All"))
										{
											unlockall = true;
										}


										if (ImGui::Button("Max Arena Skill"))
										{
											globalHandle(262145).At(1735).As<int>() = 1;
										}

								

										if (ImGui::Button("2 Billion Snacks"))
										{

											STATS::STAT_SET_INT($("MP0_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_CIGARETTES_BOUGHT"), 2000000000, 1);


										}

										if (ImGui::Button("2 Billion Armor"))
										{
											STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
										}

										if (ImGui::Button("2 Billion Firework"))
										{
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_1_RED"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_2_RED"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_3_RED"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_4_RED"), 2000000000, 1);
											STATS::STAT_SET_INT($("MP0_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
										}
									}
									ImGui::EndChild();
									ImGui::PopStyleVar();
								}



								{
									ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
									ImGui::BeginChild("recoveryother", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
									if (ImGui::BeginMenuBar())
									{
										if (ImGui::BeginMenu("Other Money Methods"))
										{
											ImGui::EndMenu();
										}
										ImGui::EndMenuBar();

										ImGui::Checkbox("Fake Money", &Features::FakeLoopBool);


										if (ImGui::Button("Singleplayer Cash"))
										{
											for (int i = 0; i < 3; i++)
											{
												char statNameFull[32];
												sprintf_s(statNameFull, "SP%d_TOTAL_CASH", i);
												Hash hash = GAMEPLAY::GET_HASH_KEY(statNameFull);
												int val;
												STATS::STAT_GET_INT(hash, &val, -1);
												val += 200000000;
												STATS::STAT_SET_INT(hash, val, 1);
											}
										}


									}
									ImGui::EndChild();
									ImGui::PopStyleVar();
								}

								ImGui::SameLine(0.0, 380.0f);


								{
									ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
									ImGui::BeginChild("recoverytrans", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
									if (ImGui::BeginMenuBar())
									{
										if (ImGui::BeginMenu("Money Transfering"))
										{
											ImGui::EndMenu();
										}
										ImGui::EndMenuBar();


										ImGui::InputInt("", &kohle);

										if (ImGui::Button("Transfer to Wallet"))
										{
											g_FiberScript->addTask([] {
												int iVar0;
												STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_MP_CHAR"), &iVar0, 1);
												UNK3::_NETWORK_TRANSFER_BANK_TO_WALLET(iVar0, kohle);
												UNK3::_NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED();
											});
										}
										ImGui::SameLine();
										if (ImGui::Button("Transfer to Bank"))
										{
											g_FiberScript->addTask([] {
												int iVar0;
												STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_MP_CHAR"), &iVar0, 1);
												UNK3::_NETWORK_TRANSFER_BANK_TO_WALLET(iVar0, kohle);
												UNK3::_NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED();
											});
										}




									}
									ImGui::EndChild();
									ImGui::PopStyleVar();
								}











				break;

				case 6:




				{
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("vehpedopt", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Vehicle + Ped Options"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();


						ImGui::Checkbox("Explode all Peds in your area", &Features::ExplodePedBool);
						ImGui::Checkbox("Explode all Vehicle in your area", &Features::ExplodeVehicleBool);
						ImGui::Checkbox("Delete all Vehicle in your area", &Features::DeleteVehicleBool);
					}
					ImGui::EndChild();
					ImGui::PopStyleVar();
				}
				ImGui::SameLine(0.0, 380.0f);
				{
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("networkreque", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Network Request"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();

						if (ImGui::Button("Skip Cutszene"))
						{
							skipcut = true;
						}

						if (ImGui::Button("Give Bullshark"))
						{
							globalHandle(2440049).At(4006).As<int>() = 3;
						}

						if (ImGui::Button("Give Signal Bomb Airstrike"))
						{
							globalHandle(2540384).At(4451).As<int>() = 4390;
						}

						if (ImGui::Button("Spawn Ammunation Supply"))
						{
							globalHandle(2540384).At(871).As<int>() = 833;
						}

						if (ImGui::Button("Evacuate of Ship"))
						{
							globalHandle(2540384).At(872).As<int>() = 834;
						}


						if (ImGui::Button("Spawn Helicopter Support"))
						{
							globalHandle(2540384).At(4450).As<int>() = 4389;
						}




					}
					ImGui::EndChild();
					ImGui::PopStyleVar();
				}

				ImGui::NewLine();
				ImGui::SameLine(0.0, 420.0f);




				{
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("othermisc", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Other Network Options"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();

						if (ImGui::Button("Stop Cutscene"))
						{
							g_FiberScript->addTask([] {
								CUTSCENE::STOP_CUTSCENE;
								CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
							});
						}
						ImGui::Checkbox("Log Network Script Events", &Features::LogEvent);
						ImGui::Checkbox("Disable Minimap", &Features::DisableHUDBool);
						ImGui::Checkbox("Unlimited Orbital Cannon", &Features::OrbitalCooldownBool);

					}
					ImGui::EndChild();
					ImGui::PopStyleVar();
				}




		
						//ImGui::Checkbox("Max Heist Payout", &Features::MaxHeistPayoutBool);




						break;
				case 7:
					



					ImGui::SameLine(0.0, 420.0f);
				{
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("protacde", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Protection Setting"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();

						ImGui::Checkbox("Protection-Notify", &Features::EventNotif);

						if (ImGui::Button("Enable All Protections"))
						{
							Features::AFKNo = true;
							protex1 = true;

							Features::AntiMoneyDrop = true;
							Features::NetworKIDCrashBool = true;
							Features::ModelCrashBool = true; 
							Features::AttachmentBool = true;
							Features::CloneProtectionBool = true;
							protex6 = true;

							CayoPericoProt = true;
							protex11 = true;
							protex7 = true;
							protex8 = true;
							Features::GAME_CLOCK_EVENT = true;
							Features::FIRE_EVENT = true;
							Features::NETWORK_CLEAR_PED_TASKS_EVENT = true;
							protex12 = true;
							Features::REMOVE_WEAPON_EVENT = true;
							Features::EXPLOSION_EVENT = true;
							Features::GAME_WEATHER_EVENT = true;

							protex17 = true;
							protex2 = true;
							protex3 = true;
							protex4 = true;
							protex9 = true;
						}

						if (ImGui::Button("Disable All Protections"))
						{
							Features::AFKNo = false;
							protex1 = false;


							CayoPericoProt = false;
							Features::AntiMoneyDrop = false;
							Features::NetworKIDCrashBool = false;
							Features::ModelCrashBool = false;
							Features::AttachmentBool = false;
							Features::CloneProtectionBool = false;
							protex6 = false;
							protex11 = false;
							protex7 = false;
							protex8 = false;
							Features::GAME_CLOCK_EVENT = false;
							Features::FIRE_EVENT = false;
							Features::NETWORK_CLEAR_PED_TASKS_EVENT = false;
							protex12 = false;
							Features::REMOVE_WEAPON_EVENT = false;
							Features::EXPLOSION_EVENT = false;
							Features::GAME_WEATHER_EVENT = false;

							protex17 = false;
							protex2 = false;
							protex3 = false;
							protex4 = false;
							protex9 = false;
						}



					}
					ImGui::EndChild();
					ImGui::PopStyleVar();
				}







				{
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("prot1", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Script Event Protection"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();


						ImGui::Checkbox("Kick", &protex1);
						ImGui::Checkbox("CEO Ban", &protex3);
						ImGui::Checkbox("CEO Kick", &protex2);
						ImGui::Checkbox("Camera", &protex17);
						ImGui::Checkbox("Cops", &protex11);
						ImGui::Checkbox("Sound", &protex8);
						ImGui::Checkbox("Cayo Perico TP", &CayoPericoProt);
						ImGui::Checkbox("AP-Teleport", &protex7);
						ImGui::Checkbox("Remote Mission", &protex6);
					}
					ImGui::EndChild();
					ImGui::PopStyleVar();
				}
				ImGui::SameLine(0.0, 380.0f);
				{
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("prot2", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Game Event Protection"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();




						ImGui::Checkbox("Fire", &Features::FIRE_EVENT);
						ImGui::Checkbox("Weather", &Features::GAME_WEATHER_EVENT);
						ImGui::Checkbox("Weapon Remove", &Features::REMOVE_WEAPON_EVENT);
						ImGui::Checkbox("Time", &Features::GAME_CLOCK_EVENT);
						ImGui::Checkbox("Explosion", &Features::EXPLOSION_EVENT);
						ImGui::Checkbox("Freeze", &Features::NETWORK_CLEAR_PED_TASKS_EVENT);
					}
					ImGui::EndChild();
					ImGui::PopStyleVar();
				}

				{
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("prot3", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Crash Protection"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();




	


						ImGui::Checkbox("Network Desync", &Features::NetworKIDCrashBool);
						ImGui::Checkbox("Model Spam", &Features::ModelCrashBool);
					}
					ImGui::EndChild();
					ImGui::PopStyleVar();
				}
				ImGui::SameLine(0.0, 380.0f);
				{
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
					ImGui::BeginChild("prot4", ImVec2(500, 140), true, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar())
					{
						if (ImGui::BeginMenu("Other Protection"))
						{
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();
						
						ImGui::Checkbox("Anti-AFK", &Features::AFKNo);
						ImGui::Checkbox("Pickup (Money Bags)", &Features::AntiMoneyDrop);
						ImGui::Checkbox("Attachment", &Features::AttachmentBool);
						ImGui::Checkbox("Object Attachment (Big FPS Drops)", &Features::ClearPropProtectionBool);

						ImGui::Checkbox("Clone", &Features::CloneProtectionBool);
					}
					ImGui::EndChild();
					ImGui::PopStyleVar();
				}






	









					break;

							
			}









			




		





			ImGui::End();

		}
	}
}
