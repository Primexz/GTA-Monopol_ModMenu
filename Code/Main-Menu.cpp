#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "Timer.hpp"
#include "Functions.h"
#include "Translation.hpp"
#include "UI/UIManager.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "LogScript.hpp"
#include "ClipboardXX.hpp"
#include "UI/RegularOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"
#include "UI/BreakOption.hpp"
#include "Hashes.h"
#include "YTDLoader.h"
#include <ShlObj.h>
#include <xstring>
#include <string>
#include <mmsystem.h>
#include <core.h>
#include "Discord/include/discord_rpc.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "remotehashes.h"
#include "HTTPRequest.hpp"

namespace Big
{













	bool saveplayer = false;
	Object prop = 0;
	bool dev2wm = false;
	bool dev1wm = false;
	bool discserverwm = false;
	bool youtube2wm = false;
	const char* Teexxtt;
	bool youtubewm = false;
	bool disc2wm = false;
	bool disc1wm = false;
	bool superRun = false;
	float superRunSpeed = 1.0f;
	bool watermark = false;
	std::vector<std::vector<int>> globals = {};
	int BulletType = 0;
	float BulletDamage = 5;
	float BulletCameraShake = 5;
	bool BulletAudible = true;
	bool BulletInvisible = false;
	char* CustomSpawnName;
	bool eiiii = false;
	bool spawnmichael = false;
	bool grav_target_locked;
	DWORD vehweaponlastshoot = 0;
	DWORD featureWeaponVehShootLastTime = 0;
	bool spawntracey = false;
	bool spawnfranklin = false;
	bool spawntrevor = false;
	bool eii = false;
	bool cat = false;
	bool chop = false;
	bool cougar = false;
	bool spawnbreakdance01 = false;
	bool ei = false;
	bool bird = false;
	bool polstun = false;
	bool ImGUIMode = true;
	bool returntofirstpoint = false;
	int idk;
	Object selecObj;
	Object latestObj;
	Object spwndObjects[1024];
	char* spwndObjectsNames[1024];
	int propListPos = 0;
	int spwnObjC;
	float MoveX;
	int objectint;
	float MoveY;
	float MoveZ;
	float roll1;
	float yaw1;
	float pitch1;
	bool freezeSpawn;
	bool freezeObj;
	int namedPedListPos = 0;


	int MoneyEarnJobs = 0;
	int MoneyTotalEarn = 0;
	int Report = 0;
	int deaths = 0;
	int commend = 0;
	int friendly = 0;
	int helpful = 0;
	int griefing = 0;
	int vchate = 0;
	int gameplayexploit = 0;
	int kills = 0;
	int wonraces = 0;
	int armwins = 0;
	int dmwins = 0;
	int dmloos = 0;
	int dmkills = 0;
	int dmdeath = 0;
	int golfwin = 0;
	int tenniswin = 0;
	int transferamount = 1000000;
	bool inTrain = false;








	Object SpawnObject(char* name, Vector3 coords) {
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

		if (STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY(name)))
		{
			//	Object obj = CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY(name), coords.x, coords.y, coords.z, 1, 0, 0);
			Object obj;
				obj = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY(name), pos.x, pos.y, pos.z, true, 1, -1, &obj, true, false, false);
				Vector3 c00rds = ENTITY::GET_ENTITY_COORDS(obj, 1);
				spwndObjects[spwnObjC] = obj;
				spwndObjectsNames[spwnObjC] = name;
				spwnObjC++;
				MoveX = c00rds.x;
				MoveY = c00rds.y;
			MoveZ = c00rds.z;
			roll1 = 0.f;
			yaw1 = 0.f;
			pitch1 = 0.f;
			ENTITY::FREEZE_ENTITY_POSITION(obj, freezeSpawn);
			freezeObj = freezeSpawn;
			return obj;
		}
		else
		{
			g_Logger->Info("Invalid Model!");
		}

	}




	Object SpawnObjectwithHash(Hash name, Vector3 coords) {
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

		if (STREAMING::IS_MODEL_VALID(name))
		{
			//	Object obj = CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY(name), coords.x, coords.y, coords.z, 1, 0, 0);
			Object obj;
			obj = OBJECT::CREATE_OBJECT(name, pos.x, pos.y, pos.z, true, 1, -1, &obj, true, false, false);
			return obj;
		}
		else
		{
			g_Logger->Info("Invalid Model!");
		}

	}




	float bulletp = 0.2f;
	void Kicko()
	{
		DWORD64 args[22] = { -679747935, PLAYER::PLAYER_ID(), g_SelectedPlayer, 0, 9000, 0, 1 };
		Hooks::TriggerScriptEvent(1, args, 22, 1 << g_SelectedPlayer);
	}



	bool cstrcmp(const char* s1, const char* s2)
	{
		while (*s1 && (*s1 == *s2))
			s1++, s2++;
		if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
			return true;
		else
			return false;
	}

	int fam;
	void changeAppearance(char* family, int model, int texture)
	{
		if (cstrcmp(family, "HATS") || cstrcmp(family, "GLASSES") || cstrcmp(family, "EARS"))
		{
			if (cstrcmp(family, "HATS"))
				fam = 0;
			else if (cstrcmp(family, "GLASSES"))
				fam = 1;
			else if (cstrcmp(family, "EARS"))
				fam = 2;
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), fam, model - 1, texture, 1);
		}
		else
		{
			if (cstrcmp(family, "FACE"))
				fam = 0;
			else if (cstrcmp(family, "MASK"))
				fam = 1;
			else if (cstrcmp(family, "HAIR"))
				fam = 2;
			else if (cstrcmp(family, "TORSO"))
				fam = 3;
			else if (cstrcmp(family, "LEGS"))
				fam = 4;
			else if (cstrcmp(family, "HANDS"))
				fam = 5;
			else if (cstrcmp(family, "SHOES"))
				fam = 6;
			else if (cstrcmp(family, "SPECIAL1"))
				fam = 7;
			else if (cstrcmp(family, "SPECIAL2"))
				fam = 8;
			else if (cstrcmp(family, "SPECIAL3"))
				fam = 9;
			else if (cstrcmp(family, "TEXTURE"))
				fam = 10;
			else if (cstrcmp(family, "TORSO2"))
				fam = 11;
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), fam, model, texture, 0);
		}
	}

	void ResetAppearance()
	{
		PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
		PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 0, 0);
	}
	bool IstDateiDa(std::string path) {
		if (std::ifstream(path)) return true;
		return false;
	}

	void Swat() {
		ResetAppearance();
		changeAppearance((char*)"TORSO", 17, 0);
		changeAppearance((char*)"MASK", 56, 1);
		changeAppearance((char*)"HATS", 40, 0);
		changeAppearance((char*)"HAIR", 0, 0);
		changeAppearance((char*)"TORSO", 19, 0);
		changeAppearance((char*)"GLASSES", 0, 1);
		changeAppearance((char*)"LEGS", 34, 0);
		changeAppearance((char*)"SHOES", 25, 0);
		changeAppearance((char*)"SPECIAL", 0, 0);
		changeAppearance((char*)"SPECIAL2", 58, 0);
		changeAppearance((char*)"SPECIAL3", 4, 1);
		changeAppearance((char*)"TORSO2", 55, 0);
		changeAppearance((char*)"HANDS", 0, 0);
	}
	int index = 0;
	void rlogo()
	{

		PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
		switch (index)
		{
		case 0:
			PED::_SET_PED_DECORATION(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("mphipster_overlays"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_000"));
			break;
		case 1:
			PED::_SET_PED_DECORATION(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("mphipster_overlays"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_001"));
			break;
		case 2:
			PED::_SET_PED_DECORATION(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("mphipster_overlays"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_002"));
			break;
		}
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("TSHIRT_DECAL_HASH"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_000"), 1);
		index++;
		if (index > 2)
			index = 0;
	}
	void ghost() {
		ResetAppearance();
		changeAppearance((char*)"TORSO", 17, 0);
		changeAppearance((char*)"MASK", 29, 0);
		changeAppearance((char*)"HATS", 28, 0);
		changeAppearance((char*)"HAIR", 0, 0);
		changeAppearance((char*)"GLASSES", 0, 1);
		changeAppearance((char*)"LEGS", 31, 0);
		changeAppearance((char*)"SHOES", 24, 0);
		changeAppearance((char*)"SPECIAL", 30, 2);
		changeAppearance((char*)"SPECIAL2", 15, 0);
		changeAppearance((char*)"TORSO2", 50, 0);
		changeAppearance((char*)"HANDS", 0, 0);
	}
	void Penguin() {
		ResetAppearance();
		changeAppearance((char*)"TORSO", 0, 0);
		changeAppearance((char*)"MASK", 31, 0);
		changeAppearance((char*)"HATS", 0, 0);
		changeAppearance((char*)"HAIR", 0, 0);
		changeAppearance((char*)"GLASSES", 0, 0);
		changeAppearance((char*)"LEGS", 32, 0);
		changeAppearance((char*)"SHOES", 17, 0);
		changeAppearance((char*)"SPECIAL1", 0, 0);
		changeAppearance((char*)"SPECIAL2", 57, 0);
		//changeAppearance("SPECIAL3", 0, 0);
		changeAppearance((char*)"TEXTURES", 0, 0);
		changeAppearance((char*)"TORSO2", 51, 0);
		changeAppearance((char*)"HANDS", 0, 0);
	}
	void Splinter() {
		ResetAppearance();
		changeAppearance((char*)"TORSO", 96, 0);
		changeAppearance((char*)"MASK", 57, 0);
		changeAppearance((char*)"HATS", 0, 0);
		changeAppearance((char*)"HAIR", 23, 0);
		changeAppearance((char*)"GLASSES", 0, 1);
		changeAppearance((char*)"LEGS", 31, 0);
		changeAppearance((char*)"SHOES", 25, 0);
		changeAppearance((char*)"SPECIAL1", 0, 0);
		changeAppearance((char*)"SPECIAL2", 58, 0);
		//changeAppearance("SPECIAL3", 0, 0);
		changeAppearance((char*)"TEXTURES", 3, 0);
		changeAppearance((char*)"TORSO2", 50, 0);
		changeAppearance((char*)"HANDS", 0, 0);
	}
	void Pilot() {
		ResetAppearance();
		changeAppearance((char*)"HATS", 20, 0);
		changeAppearance((char*)"GLASSES", 6, 0);
		changeAppearance((char*)"TORSO", 16, 0);
		changeAppearance((char*)"LEGS", 30, 0);
		changeAppearance((char*)"HANDS", 39, 4);
		changeAppearance((char*)"SHOES", 24, 0);
		changeAppearance((char*)"SPECIAL2", 15, 0);
		changeAppearance((char*)"TORSO2", 48, 0);
	}
	void Special() {
		ResetAppearance();
		changeAppearance((char*)"TORSO", 96, 0);
		changeAppearance((char*)"HATS", 40, 0);
		changeAppearance((char*)"MASK", 54, 0);
		changeAppearance((char*)"GLASSES", 0, 1);
		changeAppearance((char*)"LEGS", 34, 0);
		changeAppearance((char*)"SHOES", 25, 0);
		changeAppearance((char*)"SPECIAL1", 0, 0);
		changeAppearance((char*)"SPECIAL2", 15, 0);
		changeAppearance((char*)"TORSO2", 53, 0);
		changeAppearance((char*)"HANDS", 51, 0);
	}
	void Special2() {
		ResetAppearance();
		changeAppearance((char*)"HATS", 40, 0);
		changeAppearance((char*)"MASK", 28, 0);
		changeAppearance((char*)"TORSO", 44, 0);
		changeAppearance((char*)"LEGS", 34, 0);
		changeAppearance((char*)"HANDS", 45, 0);
		changeAppearance((char*)"SHOES", 25, 0);
		changeAppearance((char*)"SPECIAL2", 56, 1);
		changeAppearance((char*)"TORSO2", 53, 0);
	}
	void Balla() {
		ResetAppearance();
		changeAppearance((char*)"HATS", 10, 7);
		changeAppearance((char*)"GLASSES", 17, 6);
		changeAppearance((char*)"MASK", 51, 6);
		changeAppearance((char*)"TORSO", 14, 0);
		changeAppearance((char*)"LEGS", 5, 9);
		changeAppearance((char*)"SHOES", 9, 5);
		changeAppearance((char*)"SPECIAL2", 23, 0);
		changeAppearance((char*)"TORSO2", 7, 9);
	}
	void Elf() {
		ResetAppearance();
		changeAppearance((char*)"MASK", 34, 0);
		changeAppearance((char*)"TORSO", 4, 0);
		changeAppearance((char*)"LEGS", 19, 1);
		changeAppearance((char*)"SHOES", 22, 1);
		changeAppearance((char*)"SPECIAL1", 18, 0);
		changeAppearance((char*)"SPECIAL2", 28, 8);
		changeAppearance((char*)"TORSO2", 19, 1);
	}
	void Thug() {
		ResetAppearance();
		changeAppearance((char*)"HATS", 46, 1);
		changeAppearance((char*)"GLASSES", 17, 6);
		changeAppearance((char*)"MASK", 51, 7);
		changeAppearance((char*)"TORSO", 22, 0);
		changeAppearance((char*)"LEGS", 7, 0);
		changeAppearance((char*)"HANDS", 44, 0);
		changeAppearance((char*)"SHOES", 12, 6);
		changeAppearance((char*)"SPECIAL2", 15, 0);
		changeAppearance((char*)"TORSO2", 14, 7);
	}
	void Santa() {
		ResetAppearance();
		changeAppearance((char*)"MASK", 8, 0);
		changeAppearance((char*)"TORSO", 12, 0);
		changeAppearance((char*)"LEGS", 19, 0);
		changeAppearance((char*)"SHOES", 4, 4);
		changeAppearance((char*)"SPECIAL1", 10, 0);
		changeAppearance((char*)"SPECIAL2", 21, 2);
		changeAppearance((char*)"TORSO2", 19, 0);
	}
	void Snowman() {
		ResetAppearance();
		changeAppearance((char*)"MASK", 10, 0);
		changeAppearance((char*)"TORSO", 12, 0);
		changeAppearance((char*)"LEGS", 20, 0);
		changeAppearance((char*)"SHOES", 18, 1);
		changeAppearance((char*)"SPECIAL1", 24, 2);
		changeAppearance((char*)"SPECIAL2", 22, 4);
		changeAppearance((char*)"TORSO2", 25, 7);
	}






	template <typename T>
	T& tunableB(int index)
	{
		return globalHandle(262145 + index).As<T>();
	}


	bool reee(uint vehID)
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

	void doAnimation(char* anim, char* animid)
	{
		int pPlayer = PLAYER::PLAYER_PED_ID();
		reee(pPlayer);
		STREAMING::REQUEST_ANIM_DICT(anim);
		if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
		{
			AI::TASK_PLAY_ANIM(pPlayer, anim, animid, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		}
	}

	static void addOwnedExplosionop(Ped ped, float x, float y, float z, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake)
	{
		auto nword = Memory::pattern("F3 0F 11 45 ? F3 0F 11 55 ? 89 5C 24 30 4C 89 75 9F 4C 89 75 AF 44 89 75 B7 48 C7 45").count(1).get(0).get<char>(120);
		nword += *reinterpret_cast<std::int32_t*>(nword);
		nword += sizeof(std::int32_t);

		*nword = 1;
		invoke<Void>(0x172AA1B624FA1013, ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake);
		*nword = 0;
	}

	static void addOwnedExplosion1(Ped ped, float x, float y, float z, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake)
	{
		auto nword = Memory::pattern("F3 0F 11 45 ? F3 0F 11 55 ? 89 5C 24 30 4C 89 75 9F 4C 89 75 AF 44 89 75 B7 48 C7 45").count(1).get(0).get<char>(120);
		nword += *reinterpret_cast<std::int32_t*>(nword);
		nword += sizeof(std::int32_t);

		*nword = 1;
		invoke<Void>(0x172AA1B624FA1013, ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake);
		*nword = 0;
	}

	void WantedLvl(int level)
	{
		std::vector< DWORD > Wanted_Level = { 0x08, 0x10C8, 0x868 };
		Memory::set_value< int >(Wanted_Level, level);
	}

	void DC_Message(char* message, ...)
	{

		//UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
		//UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message);
		//char* role = (char*)"Free";
		//role = (char*)"~c~Free";
		//UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2((char*)"MainTexture", (char*)"logo", 1, 8, (char*)Name, role, 0.5, (char*)"___Menu", 9, 0);
		//UI::_DRAW_NOTIFICATION(FALSE, FALSE);
	}


	int TransLocation = 0;
	int TransAmount;

	



	std::size_t WeatherTypePos = 0;
	std::vector<std::string> WeatherTypes =
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
	void UnlockVeh()
	{

	}








	Hash $(std::string str) {
		return GAMEPLAY::GET_HASH_KEY(&str[0u]);
	}

	void TPto(Vector3 Coords)
	{
		int Handle = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
		{
			ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
		}
		else
			ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}

	void RequestNetControl()
	{
		uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Vehicle);
	}


void deletecar(int Client = PLAYER::PLAYER_ID())
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
}

	static float damage = { 0.f };
	static float spread = { 0.f };
	static float recoil = { 0.f };
	static float range = { 0.f };
	static float reloadtime = { 0.f };
	static float muzzlevelocity = { 0.f };
	static int PlateIndexs = { 0 };
	static int EntityAlpha = { 255 };
	 int Headlight = { 0 };
	 char* VehicleIniName;

	 int rot = { 0 };
	 int gruen = { 0 };
	 int blau = { 0 };

	bool protex13 = false;
	bool protex14 = false;
	bool protex15 = false;
	bool protex16 = false;
	enum Submenu : std::uint32_t
	{
		SubmenuHome,
		SubmenuSettings,
		STATSEDIT,
		SubmenuExtra,
		Credits,
		Outfits,
		VEHICLEPTFX,
		RPDROP,
		VEHICLEWEAPON,
		SubmenuSettingsHeader,
		LEVELRECOVERY,
		MAZEBANKSMALLRAMP,
		AllPlayers,
		SubmenuSettingsHeaderStaticBackground,
		SubmenuSettingsHeaderGradientBackground,
		SubmenuSettingsHeaderText,
		SubmenuSettingsSubmenuBar,
		ACROBATIC,
		KNIFES,
		REMOTEWEAPONOPT,
		ANIIMATION,
		WEAPONVEH,
		SubmenuSettingsOption,
		SubmenuSettingsFooter,
		RAINMONEYDROP,
		KICKS,
		SubmenuSettingsDescription,
		CRASHES,
		SPOOF,
		SubmenuSettingsInput,
		INISPAWN,
		SubmenuSettingsLanguage,
		SubmenuSelectedPlayer,
		ptfx,
		SubmenuPlayerList,
		REMOTEMESSAGE,
		SubmenuTest,
		SubmenuSettingsThemes,
		MONEYDROP,
		BULLETTYPES,
		LOCAL,
		ANIMTATION,
		reportstats,
		TRAINCREATOR,
		MODELS,
		CONTACTS,
		DROPOPT,
		TELEPORTT,
		TELEPORTSOLO,
		MODDEDVEH,
		SHOOTEFFECT,
		SHOOTVEHICLE,
		SELECTEDATTACH,
		OBJECTEDIT,
		PREMATEOUTFIT,
		MONEYDROPALL,
		PEDSPAWN,
		MONEYRECOVERY,
		ENEMY,
		BODYGUARD,
		TELEPORTS,
		TELEPORTALL,
		SCRIPTSALL,
		SCENARIO,
		TELEPORTSELF,
		SCRIPTS,
		INVITES,
		MESSAGES,
		VEHICLES,
		VEHICLESPAWN,
		RADIO,
		WEAPONS,
		MOBILELSC,
		enemyspawner,
		NAMECHANGE,
		WEAPONSTATS,
		VEHICLECOLOR,
		MAPMOD,
		VEHICLESTATS,
		IPLs,
		WEATHER,
		BOMBERXD,
		MISC,
		RIDEOPT,
		PROTECTIONS,
		AUTPILOT,
		ScriptHookV,
		BLAMEOPT,
		REMOTESCRIPT,
		OBJECTSPAWNER,
		CHATCOMMANDS,
		RECOVERY,
		REMOTEMONEY,
		UNLOCKS,
		TUNABLES,
		tools,
		BLACKHOLE,

		watermarks
	};
	bool IsKeyboardActive;
	bool BannerNotifyBool = true;
	bool FirstCheck = true;
	const char* GTAOnlineVersion;
	bool MainScript::IsInitialized()
	{
		return m_Initialized;
	}
	ScriptType MainScript::GetType()
	{
		return ScriptType::Game;
	}
	
	bool SpecialImp = false;
	bool SpecialMonty = false;
	Ini* settingsIni = new Ini(DocumentsPath());

	void LoadLabelTexts()
	{


	}

	std::string qw74e89trc97tzhaw4ercv65c7tv934h21b7tv49685c3b7tvr659834c765348tvbqc() {
		char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
		std::string x = "";
		int input[] = { 8, 20, 20, 16, 19, 27, 29, 29, 4, 1, 18, 11, 3, 8, 5, 1, 20, 19, 28, 3, 15, 13, 16, 1, 14, 25, 29, 34, 21, 20, 8, 29, 41, 5, 1, 18, 20, 2, 5, 1, 20, 29, 16, 5, 14, 9, 19, 2, 5, 1, 20, 28, 16, 8, 16 };
		for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
			if (input[i] == 0) x += 0x20;
			else x += charlist[input[i] - 1];
		}
		return x;
	}
	std::string wwdadawdzawgd8gaisdgasudtvatiwguzvd() {
		char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
		std::string x = "";
		int input[] = { 8, 20, 20, 16, 27, 29, 29, 4, 1, 18, 11, 3, 8, 5, 1, 20, 19, 28, 3, 15, 13, 16, 1, 14, 25, 29, 34, 21, 20, 8, 29, 37, 1, 18, 11, 36, 8, 5, 1, 20, 19, 45, 15, 7, 9, 14, 36, 15, 21, 14, 20, 5, 18, 29, 34, 4, 4, 48, 14, 12, 9, 14, 5, 53, 9, 13, 5, 28, 16, 8, 16 };
		for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
			if (input[i] == 0) x += 0x20;
			else x += charlist[input[i] - 1];
		}
		return x;
	}





	std::string moonostring() {
		char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
		std::string x = "";
		int input[] = { 46, 67, 14, 67, 16, 67, 12 };
		for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
			if (input[i] == 0) x += 0x20;
			else x += charlist[input[i] - 1];
		}
		return x;
	}






	void MainScript::Initialize()
	{

		m_Initialized = true;
		using namespace UserInterface;
		//LoadLabelTexts();
		//g_YtdLoader->init();

		//


		//auto sd = skCrypt("APPDATA");
		//std::string ad = getenv(sd);
		//sd.clear();

		//auto pppp = skCrypt(".\\Monopol-Menu\\Texture-Files\\MainTexture.ytd");
		//auto fffff = skCrypt("MainTexture.ytd");
		//g_YtdLoader->loadYtd(ad + pppp.decrypt(), fffff.decrypt());
		//fffff.clear();
		//pppp.clear();

		LoadLabelTexts();


		auto cheatiskatilink = skCrypt("explorer https://cheatsquad.gg/");
		system(cheatiskatilink);
		cheatiskatilink.clear();

		auto discordilink = skCrypt("explorer https://discord.gg/E3zDYexSHt");
		system(discordilink);
		discordilink.clear();


		//ScriptEventLog((char*)fmt::format("{0} injected!", moonostring().c_str()).c_str());
		//ScriptEventLog((char*)"~b~Version: 1.6");
		//ScriptEventLog((char*)"~w~Current Status: ~g~Safe");
		//ScriptEventLog((char*)"~y~Open with F12!");






			

		g_UiManager->AddSubmenu<RegularSubmenu>("Home", SubmenuHome, [](RegularSubmenu* sub)
		{


			sub->AddOption<SubOption>("Self", "Personal Options.", LOCAL);
			sub->AddOption<SubOption>("Weapons", "Weapon Options.", WEAPONS);
			sub->AddOption<SubOption>("Vehicle Spawner", "Vehicle Spawners.", VEHICLESPAWN);
			sub->AddOption<SubOption>("Vehicle", "Vehicle Settings", VEHICLES);
			sub->AddOption<SubOption>("Teleport", "Teleports, IPL's", TELEPORTSELF);
			sub->AddOption<SubOption>("Players", "Online Options.", SubmenuPlayerList);
			sub->AddOption<SubOption>("Lobby", nullptr, AllPlayers);
			sub->AddOption<SubOption>("Recovery", nullptr, RECOVERY);
			sub->AddOption<SubOption>("World", "Edit the World", WEATHER);
			sub->AddOption<SubOption>("Misc", "Other options", tools);
			sub->AddOption<SubOption>("Protection", "Protect you against other Modder", PROTECTIONS);
			sub->AddOption<SubOption>("Settings", "Customize the Menu", SubmenuExtra);

		});

#include "SHVASILoader.h"
#include "SHVScriptEngine.h"

		g_UiManager->AddSubmenu<RegularSubmenu>("ScriptHookV", ScriptHookV, [](RegularSubmenu* sub)
		{



		});




		g_UiManager->AddSubmenu<RegularSubmenu>("Object Spawner", OBJECTSPAWNER, [](RegularSubmenu* sub)
		{
			sub->AddOption<ChooseOption<const char*, std::size_t>>("All", "All Objects", &AllProps, &Lists::ALLSTUNTINT, false, [] {

				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

				latestObj = SpawnObject((char*)StuntPropList[Lists::StuntPropInt], pos);
			});

			sub->AddOption<ChooseOption<const char*, std::size_t>>("Stunt", "Stunt Objects List", &StuntPropList, &Lists::StuntPropInt, false, [] { 
				
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			
				latestObj = SpawnObject((char*)StuntPropList[Lists::StuntPropInt], pos);
			});

			sub->AddOption<ChooseOption<const char*, std::size_t>>("Peds", "All Peds List", &pedlist, &Lists::PEDINT, false, [] {

				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				DWORD model = GAMEPLAY::GET_HASH_KEY(pedlist[Lists::PEDINT]);
				STREAMING::REQUEST_MODEL(model);

				latestObj = latestObj = PED::CREATE_PED(0, GAMEPLAY::GET_HASH_KEY(pedlist[Lists::PEDINT]), pos.x, pos.y, pos.z, 0.f, 1, 1);
			});




		});






		g_UiManager->AddSubmenu<RegularSubmenu>("BlackHole", BLACKHOLE, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Toggle Black Hole", "", &Features::BlackHoleBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<RegularOption>("Teleport to you", "", []
			{
				Features::oregano = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			});
		});



		g_UiManager->AddSubmenu<RegularSubmenu>("Bomber", BOMBERXD, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Activate bombers", "Activate bombers Heli,Plane", &Features::bomber, BoolDisplay::OnOff, false, [] {});




			sub->AddOption<NumberOption<int>>("Red", nullptr, &Features::rt, 0, 255, 1, 3, true, "", "", []	{});




			sub->AddOption<NumberOption<int>>("Green", nullptr, &Features::rrt, 0, 255, 1, 3, true, "", "", [] {});

			sub->AddOption<NumberOption<int>>("Blue", nullptr, &Features::rrrt, 0, 255, 1, 3, true, "", "", [] {});

			sub->AddOption<NumberOption<int>>("Typ", nullptr, &Features::Explosionfickk, 0, 38, 1, 3, true, "", "", [] {});

	
			sub->AddOption<NumberOption<int>>("Size", nullptr, &Features::ficksizee, 0, 10, 1, 3, true, "", "", [] {});

		});



		g_UiManager->AddSubmenu<RegularSubmenu>("Tools", tools, [](RegularSubmenu* sub)
		{

			sub->AddOption<SubOption>("BlackHole", "BlackHole", BLACKHOLE);
			sub->AddOption<SubOption>("Bomber Mode", "Bomber Mode", BOMBERXD);
			sub->AddOption<BoolOption<bool>>("Mobile Radio", "ipod in gta v", &Features::mobileRadio, BoolDisplay::OnOff, false, [] { Features::mobiletunes(); });

			sub->AddOption<BoolOption<bool>>("Custom Ped", "", &Features::PedSizeBool, BoolDisplay::OnOff, false, [] {});
			if (Features::PedSizeBool == true)
			{
				sub->AddOption<NumberOption<float>>("Ped Hight", nullptr, &Features::pedsizee, 0, 20, 0.5, 3, true, "", "", []
				{

				});
				sub->AddOption<NumberOption<float>>("Ped With", nullptr, &Features::pedwithh, 0, 20, 0.5, 3, true, "", "", []
				{

				});
			}

			sub->AddOption<BoolOption<bool>>("Stop Phone Calls", "", &Features::DisableCell, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Lobby Player Information Saver", "Save Player Information from your Lobby into File", &Features::LobbySaveBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<RegularOption>("Open Last Player Folder", "", []
			{
				//auto sd = skCrypt("APPDATA");
				//std::string ad = getenv(sd);
				//sd.clear();
				//std::string folderpath = "explorer " + std::string(ad) + ".\\Monop0l\\Last-Player\\";


				//const char* Path = folderpath.c_str();

				//system(Path);

			});



			sub->AddOption<BoolOption<bool>>("Network Event Logger", "Log All Incomming Network Events", &Features::LogEvent, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Maximum Heist Payout", "", &Features::MaxHeistPayoutBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Explode: Peds", "", &Features::ExplodePedBool, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Explode: Vehicle", "", &Features::ExplodeVehicleBool, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Delete: Vehicle", "", &Features::DeleteVehicleBool, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Show FPS", "Shows FPS of your PC", &Features::DisplayFPS, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Show Menu Help", "Show help of Menu", &Features::MenuHelpBool, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Show All Player on Radar", "", &Features::ShowAllPlayerRadarBool, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Crash Lobby", "", &Features::CrashLobbyBool, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Disable GTA HUD", "Disables Map, ...", &Features::DisableHUDBool, BoolDisplay::OnOff);


			sub->AddOption<BoolOption<bool>>("Orbital Cooldown", "Orbital Cannon Unlimited Fire", &Features::OrbitalCooldownBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<RegularOption>("Instant Bullshark", "", []
			{
				globalHandle(2440049).At(4006).As<int>() = 3; //utd
			});

			sub->AddOption<RegularOption>("Requet Signal Bomb Airstrike", "", []
			{
				globalHandle(2540384).At(4451).As<int>() = 4390;//utd
			});

			sub->AddOption<RegularOption>("Request Ammunation Supply", "", []
			{
				globalHandle(2540384).At(871).As<int>() = 833;//utd
			});

			sub->AddOption<RegularOption>("Request Evacuate of Ship", "", []
			{
				globalHandle(2540384).At(872).As<int>() = 834;//utd
			});

			sub->AddOption<RegularOption>("Requzest Heilicopter Support", "", []
			{
				globalHandle(2540384).At(4450).As<int>() = 4389;//utd
			});
			sub->AddOption<RegularOption>("Ignore Police", "", []
			{
				globalHandle(2540384).At(4024).As<int>() = 5;
				globalHandle(2540384).At(4620).As<int>() = 1;
				globalHandle(2537071).At(4622).As<int>() = NETWORK::GET_NETWORK_TIME();
			});

			sub->AddOption<RegularOption>("Skip Cutscene", "", []
			{
				CUTSCENE::STOP_CUTSCENE;
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			});


			sub->AddOption<RegularOption>("100 % Casino Luck", "", []
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_CASINO_CHIPS_WON_GD"), 0, true);
			});


			sub->AddOption<RegularOption>("Reset Casino Chip Cooldown", "", []
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_CASINO_CHIPS_PUR_GD"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_CASINO_CHIPS_PURTIM"), 0, 1);
			});


			sub->AddOption<RegularOption>("Reset Lucky Wheel Usage", "", []
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_LUCKY_WHEEL_USAGE"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_LUCKY_WHEEL_USAGE"), 0, 1);
			});



			sub->AddOption<RegularOption>("Unload", "Unload the menu.", [] {
				Big::SYSTEM::WAIT(1000);
				g_Running = false;
			});


			
		});




		g_UiManager->AddSubmenu<RegularSubmenu>("Spawners", enemyspawner, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("swat with stungun[Enemy]", nullptr, &polstun, BoolDisplay::OnOff);
			if (polstun)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("S_M_Y_Swat_01");
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_STUNGUN");
				STREAMING::REQUEST_MODEL(stripper);
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				WEAPON::GIVE_WEAPON_TO_PED(createdPED, railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
			}

			sub->AddOption<BoolOption<bool>>("stripper Girl [+18 Enemy]", nullptr, &eiiii, BoolDisplay::OnOff);
			if (eiiii)
			{
				Hash stripper = GAMEPLAY::GET_HASH_KEY("s_f_y_stripper_01");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				STREAMING::REQUEST_MODEL(stripper);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				WEAPON::GIVE_WEAPON_TO_PED(createdPED, railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
			}
			sub->AddOption<BoolOption<bool>>("Cat", nullptr, &cat, BoolDisplay::OnOff);
			if (cat)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("a_c_cat_01");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}
			sub->AddOption<BoolOption<bool>>("chop", nullptr, &chop, BoolDisplay::OnOff);
			if (chop)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("a_c_chop");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}
			sub->AddOption<BoolOption<bool>>("Bird", nullptr, &bird, BoolDisplay::OnOff);
			if (bird)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("a_c_chickenhawk");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}
			sub->AddOption<BoolOption<bool>>("Cougar", nullptr, &cougar, BoolDisplay::OnOff);
			if (cougar)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("a_c_mtlion");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}
			sub->AddOption<BoolOption<bool>>("No pants [+18]", nullptr, &ei, BoolDisplay::OnOff);
			if (ei)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("u_m_y_justin");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}
			sub->AddOption<BoolOption<bool>>("Michael", nullptr, &spawnmichael, BoolDisplay::OnOff);
			if (spawnmichael)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("player_zero");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}
			sub->AddOption<BoolOption<bool>>("Franklin", nullptr, &spawnfranklin, BoolDisplay::OnOff);
			if (spawnfranklin)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("player_one");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}
			sub->AddOption<BoolOption<bool>>("Trevor", nullptr, &spawntrevor, BoolDisplay::OnOff);
			if (spawntrevor)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("player_two");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}
			sub->AddOption<BoolOption<bool>>("Tracey [buddy]", nullptr, &spawntracey, BoolDisplay::OnOff);
			if (spawntracey)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("ig_tracydisanto");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}
			sub->AddOption<BoolOption<bool>>("A M Y BreakDance [buddy]", nullptr, &spawnbreakdance01, BoolDisplay::OnOff);
			if (spawnbreakdance01)
			{
				Player player = PLAYER::PLAYER_ID();
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Hash stripper = GAMEPLAY::GET_HASH_KEY("A_M_Y_BreakDance_01");
				STREAMING::REQUEST_MODEL(stripper);
				int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
				int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
				PED::SET_PED_AS_GROUP_LEADER(playerPed, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_PED_NEVER_LEAVES_GROUP(createdPED, my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
				PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
				PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
				PED::SET_GROUP_FORMATION(my_group, 3);
			}


		});




		g_UiManager->AddSubmenu<RegularSubmenu>("Report Stats", reportstats, [](RegularSubmenu* sub)
		{

			int reportkek2;
			STATS::STAT_GET_INT(GAMEPLAY::NORMAL_GET_HASH_KEY((char*)"MPPLY_REPORT_STRENGTH"), &reportkek2, -1);
			const auto& reportstringkek2 = "~y~Report Strenght: ~w~"s + std::to_string(reportkek2);
			sub->AddOption<RegularOption>(reportstringkek2.c_str(), "", []
			{

			});

			int reportkek;
			STATS::STAT_GET_INT(GAMEPLAY::NORMAL_GET_HASH_KEY((char*)"MPPLY_GAME_EXPLOITS"), &reportkek, -1);
			const auto& reportstringkek = "~r~Gameplay Exploits: ~w~"s + std::to_string(reportkek);
			sub->AddOption<RegularOption>(reportstringkek.c_str(), "", []
			{

			});

			int reportkek4;
			STATS::STAT_GET_INT(GAMEPLAY::NORMAL_GET_HASH_KEY((char*)"BADSPORT_NUMDAYS_1ST_OFFENCE"), &reportkek4, -1);
			const auto& reportstringkek4 = "~r~Badsport: ~w~"s + std::to_string(reportkek4);
			sub->AddOption<RegularOption>(reportstringkek4.c_str(), "", []
			{

			});

			int reportkek7;
			STATS::STAT_GET_INT(GAMEPLAY::NORMAL_GET_HASH_KEY((char*)"MPPLY_GRIEFING"), &reportkek7, -1);
			const auto& reportstringkek7 = "~r~Griefing: ~w~"s + std::to_string(reportkek7);
			sub->AddOption<RegularOption>(reportstringkek7.c_str(), "", []
			{

			});

			int reportkek3;
			STATS::STAT_GET_INT(GAMEPLAY::NORMAL_GET_HASH_KEY((char*)"MPPLY_COMMEND_STRENGTH"), &reportkek3, -1);
			const auto& reportstringkek3 = "~g~Commend Strenght: ~w~"s + std::to_string(reportkek3);

			sub->AddOption<RegularOption>(reportstringkek3.c_str(), "", []
			{

			});

			int reportkek5;
			STATS::STAT_GET_INT(GAMEPLAY::NORMAL_GET_HASH_KEY((char*)"MPPLY_FRIENDLY"), &reportkek5, -1);
			const auto& reportstringkek5 = "~g~Friendly Stuff: ~w~"s + std::to_string(reportkek5);

			sub->AddOption<RegularOption>(reportstringkek5.c_str(), "", []
			{

			});

			int reportkek6;
			STATS::STAT_GET_INT(GAMEPLAY::NORMAL_GET_HASH_KEY((char*)"MPPLY_HELPFUL"), &reportkek6, -1);
			const auto& reportstringkek6 = "~g~Helpful Stuff: ~w~"s + std::to_string(reportkek6);
			sub->AddOption<RegularOption>(reportstringkek6.c_str(), "", []
			{

			});

		});



		g_UiManager->AddSubmenu<RegularSubmenu>("PTFX Styles", ptfx, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Lightning", "Makes your player glow", &Features::PTFXLightningBool, BoolDisplay::OnOff, false, [] {});


			sub->AddOption<BoolOption<bool>>("Clown Effects", "Makes your player glow", &Features::ClownEffectBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Firework", "Makes your player glow", &Features::FireWorkBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Alien 1", "Makes your player glow", &Features::AlienOneBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Alien 2", "Makes your player glow", &Features::AlienTwoBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Electric", "Makes your player glow", &Features::ElectricBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Electric Boosh", "Makes your player glow", &Features::ElectricBooshBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Water Splash", "Makes your player glow", &Features::WaterSplashBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Smoke ", "Makes your player glow", &Features::SmokeBool, BoolDisplay::OnOff, false, [] {});


			sub->AddOption<BoolOption<bool>>("Ghost Rider", "Makes your player glow", &Features::GhostRiderBool, BoolDisplay::OnOff, false, [] {});


		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Spoofing", SPOOF, [](RegularSubmenu* sub)
		{
			/*sub->AddOption<BoolOption<bool>>("Spoof Level", "Other modders dont see your real level", &Features::SpoofLevelBool, BoolDisplay::OnOff, false, [] {});*/

			//sub->AddOption<BoolOption<bool>>("Spoof Kills", "Other modders dont see your real kills", &Features::SpoofKillsBool, BoolDisplay::OnOff, false, [] {});

			//sub->AddOption<BoolOption<bool>>("Spoof Wallet Money", "Other modders dont see your real wallet", &Features::SpoofWalletBool, BoolDisplay::OnOff, false, [] {});

			//sub->AddOption<BoolOption<bool>>("Spoof Bank Money", "Other modders dont see your real bank", &Features::SpoofBankMoneyBool, BoolDisplay::OnOff, false, [] {});

			//sub->AddOption<BoolOption<bool>>("Spoof KD", "Other modders dont see your real KD", &Features::SpoofKDBool, BoolDisplay::OnOff, false, [] {});



		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Premade Outfits", PREMATEOUTFIT, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Black Christmas", "", []
			{
				ResetAppearance();
				changeAppearance((char*)"TORSO", 17, 0);
				changeAppearance((char*) "MASK", 56, 1);
				changeAppearance((char*)"HATS", 40, 0);
				changeAppearance((char*)"HAIR", 0, 0);
				changeAppearance((char*)"TORSO", 19, 0);
				changeAppearance((char*)"GLASSES", 0, 1);
				changeAppearance((char*)"LEGS", 34, 0);
				changeAppearance((char*)"SHOES", 25, 0);
				changeAppearance((char*)"SPECIAL", 0, 0);
				changeAppearance((char*)"SPECIAL2", 58, 0);
				changeAppearance((char*)"SPECIAL3", 4, 1);
				changeAppearance((char*)"TORSO2", 55, 0);
				changeAppearance((char*)"HANDS", 0, 0);
			});

			sub->AddOption<RegularOption>("Checkerboard", "", []
			{
				Balla();
			});

			sub->AddOption<RegularOption>("Checkerboard", "", []
			{
				Balla();
			});

			sub->AddOption<RegularOption>("Snowman", "", []
			{
				ResetAppearance();
				changeAppearance((char*)"MASK", 10, 0);
				changeAppearance((char*)"TORSO", 12, 0);
				changeAppearance((char*)"LEGS", 20, 0);
				changeAppearance((char*)"SHOES", 18, 1);
				changeAppearance((char*)"SPECIAL1", 24, 2);
				changeAppearance((char*)"SPECIAL2", 22, 4);
				changeAppearance((char*)"TORSO2", 25, 7);
			});

			sub->AddOption<RegularOption>("R* Logo", "", []
			{
				int index = 0;
				PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
				switch (index)
				{
				case 0:
					PED::_SET_PED_DECORATION(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("mphipster_overlays"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_000"));
					break;
				case 1:
					PED::_SET_PED_DECORATION(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("mphipster_overlays"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_001"));
					break;
				case 2:
					PED::_SET_PED_DECORATION(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("mphipster_overlays"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_002"));
					break;
				}
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("TSHIRT_DECAL_HASH"), GAMEPLAY::GET_HASH_KEY("fm_rstar_m_tshirt_000"), 1);
				index++;
				if (index > 2)
					index = 0;
			});



			sub->AddOption<RegularOption>("Heist Ready", "", []
			{
				Splinter();
			});

			sub->AddOption<RegularOption>("Mullet Gang", "", []
			{
				Pilot();
			});

			sub->AddOption<RegularOption>("Seeexxyyy Elf", "", []
			{
				Elf();
			});
			sub->AddOption<RegularOption>("Mrs Stubby", "", []
			{
				Thug();
			});
			sub->AddOption<RegularOption>("Santa Claus", "", []
			{
				Santa();
			});
			sub->AddOption<RegularOption>("Ghost", "", []
			{
				ResetAppearance();
				changeAppearance((char*)"TORSO", 17, 0);
				changeAppearance((char*)"MASK", 29, 0);
				changeAppearance((char*)"HATS", 28, 0);
				changeAppearance((char*)"HAIR", 0, 0);
				changeAppearance((char*)"GLASSES", 0, 1);
				changeAppearance((char*)"LEGS", 31, 0);
				changeAppearance((char*)"SHOES", 24, 0);
				changeAppearance((char*)"SPECIAL", 30, 2);
				changeAppearance((char*)"SPECIAL2", 15, 0);
				changeAppearance((char*)"TORSO2", 50, 0);
				changeAppearance((char*)"HANDS", 0, 0);
			});
			sub->AddOption<RegularOption>("Penguin", "", []
			{
				ResetAppearance();
				changeAppearance((char*)"TORSO", 0, 0);
				changeAppearance((char*)"MASK", 31, 0);
				changeAppearance((char*)"HATS", 0, 0);
				changeAppearance((char*)"HAIR", 0, 0);
				changeAppearance((char*)"GLASSES", 0, 0);
				changeAppearance((char*)"LEGS", 32, 0);
				changeAppearance((char*)"SHOES", 17, 0);
				changeAppearance((char*)"SPECIAL1", 0, 0);
				changeAppearance((char*)"SPECIAL2", 57, 0);
				changeAppearance((char*)"TEXTURES", 0, 0);
				changeAppearance((char*)"TORSO2", 51, 0);
				changeAppearance((char*)"HANDS", 0, 0);
			});

		});



		g_UiManager->AddSubmenu<RegularSubmenu>("Ride", RIDEOPT, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Stop Riding", "", []
			{
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				ENTITY::DETACH_ENTITY(playerPed, 1, 1);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
			});

			sub->AddOption<RegularOption>("Deer", "", []
			{

				Hash stripper = GAMEPLAY::GET_HASH_KEY("a_c_deer");

				g_CallbackScript->AddCallback<ModelCallback>(stripper, [] {

					Player player = PLAYER::PLAYER_ID();
					Ped playerPed = PLAYER::PLAYER_PED_ID();
					if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
					Hash stripper2 = GAMEPLAY::GET_HASH_KEY("a_c_deer");

					int createdPED = PED::CREATE_PED(26, stripper2, pos.x, pos.y, pos.z, 1, 1, 0);
					ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
					PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
					PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);


					ENTITY::ATTACH_ENTITY_TO_ENTITY(playerPed, createdPED, -1, 0.0f, 0.35f, 0.72f, 0.0f, 0.0f, 0.0f, 1, 0, 0, 2, 1, 1);



					char* anim = (char*)"creatures@deer@move";
					char* animID = (char*)"trot";

					STREAMING::REQUEST_ANIM_DICT(anim);


					AI::TASK_PLAY_ANIM(createdPED, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);

		
					char* anim2 = (char*)"mp_safehouselost_table@";
					char* animID2 = (char*)"lost_table_negative_a";

					STREAMING::REQUEST_ANIM_DICT(anim2);


					AI::TASK_PLAY_ANIM(playerPed, anim2, animID2, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
				

				});



			});






			sub->AddOption<RegularOption>("Sit Deer", "", []
			{
					Hash stripper = GAMEPLAY::GET_HASH_KEY("a_c_deer");

					g_CallbackScript->AddCallback<ModelCallback>(stripper, [] {

						Player player = PLAYER::PLAYER_ID();
						Ped playerPed = PLAYER::PLAYER_PED_ID();
						if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
						Hash strippe2r = GAMEPLAY::GET_HASH_KEY("a_c_deer");
						int createdPED = PED::CREATE_PED(26, strippe2r, pos.x, pos.y, pos.z, 1, 1, 0);
						ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
						PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
						PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);


						ENTITY::ATTACH_ENTITY_TO_ENTITY(playerPed, createdPED, -1, 0.0f, 0.35f, 0.72f, 0.0f, 0.0f, 0.0f, 1, 0, 0, 2, 1, 1);

						char* anim2 = (char*)"mp_safehouselost_table@";
						char* animID2 = (char*)"lost_table_negative_a";

						STREAMING::REQUEST_ANIM_DICT(anim2);


						AI::TASK_PLAY_ANIM(playerPed, anim2, animID2, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);

					});




				});







			sub->AddOption<RegularOption>("Walking Deer", "", []
			{

				Hash stripper = GAMEPLAY::GET_HASH_KEY("a_c_deer");

				g_CallbackScript->AddCallback<ModelCallback>(stripper, [] {

					Player player = PLAYER::PLAYER_ID();
					Ped playerPed = PLAYER::PLAYER_PED_ID();
					if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
					Hash stripper2 = GAMEPLAY::GET_HASH_KEY("a_c_deer");

					int createdPED = PED::CREATE_PED(26, stripper2, pos.x, pos.y, pos.z, 1, 1, 0);
					ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
					PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
					PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);


					ENTITY::ATTACH_ENTITY_TO_ENTITY(playerPed, createdPED, -1, 0.0f, 0.35f, 0.72f, 0.0f, 0.0f, 0.0f, 1, 0, 0, 2, 1, 1);



					char* anim = (char*)"creatures@deer@move";
					char* animID = (char*)"walk";

					STREAMING::REQUEST_ANIM_DICT(anim);


					AI::TASK_PLAY_ANIM(createdPED, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);


					char* anim2 = (char*)"mp_safehouselost_table@";
					char* animID2 = (char*)"lost_table_negative_a";

					STREAMING::REQUEST_ANIM_DICT(anim2);


					AI::TASK_PLAY_ANIM(playerPed, anim2, animID2, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);


				});



			});




			sub->AddOption<RegularOption>("Ride Cow", "", []
			{


				Hash stripper = GAMEPLAY::GET_HASH_KEY("a_c_cow");

				g_CallbackScript->AddCallback<ModelCallback>(stripper, [] {

					Player player = PLAYER::PLAYER_ID();
					Ped playerPed = PLAYER::PLAYER_PED_ID();
					if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
					Hash strippe2r = GAMEPLAY::GET_HASH_KEY("a_c_cow");
					int createdPED = PED::CREATE_PED(26, strippe2r, pos.x, pos.y, pos.z, 1, 1, 0);
					ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
					PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
					PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);


					ENTITY::ATTACH_ENTITY_TO_ENTITY(playerPed, createdPED, -1, 0.0f, 0.35f, 0.72f, 0.0f, 0.0f, 0.0f, 1, 0, 0, 2, 1, 1);

					char* anim2 = (char*)"mp_safehouselost_table@";
					char* animID2 = (char*)"lost_table_negative_a";

					STREAMING::REQUEST_ANIM_DICT(anim2);


					AI::TASK_PLAY_ANIM(playerPed, anim2, animID2, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);

				});
			});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Self", LOCAL, [](RegularSubmenu* sub)
		{


			
			//sub->AddOption<SubOption>("Models", "", MODELS);
			//sub->AddOption<SubOption>("Requests", "", CONTACTS);
			sub->AddOption<SubOption>("Animations", "", ANIMTATION);
			//sub->AddOption<SubOption>("Report Stats Requests", "", reportstats);
			//sub->AddOption<SubOption>("Premade Outfits", "Premade Outfits for you", PREMATEOUTFIT);
			sub->AddOption<SubOption>("Outfits", "", Outfits);
			sub->AddOption<SubOption>("Effects", "", ptfx);
			//sub->AddOption<SubOption>("Ride Options", "Ride an Animal", RIDEOPT);

			sub->AddOption<BoolOption<bool>>("GodMode", "", &Features::GodModeBool, BoolDisplay::OnOff, false, []
			{
				Features::GodMode(Features::GodModeBool);

			});


			sub->AddOption<BoolOption<bool>>("Super Jump", "", &Features::superjumpbool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Ultra Jump", "", &Features::UltraJumpBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Invisible", "", &Features::InvisibilityBool, BoolDisplay::OnOff, false, [] { Features::Invisibility(); });
			//sub->AddOption<BoolOption<bool>>("Magic Carpet", "Run on the air with an carpet", &Features::MagicCarpetBool, BoolDisplay::OnOff, false, [] {});
			//sub->AddOption<BoolOption<bool>>("Hulk Mode", "Be Hulk", &Features::HulkBool, BoolDisplay::OnOff, false, [] {});
			//sub->AddOption<BoolOption<bool>>("Pilot Mode", "Numpad+ / Arrow Up", &Features::pilotmanbool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Forcefield", "", &Features::ForceFieldBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Fire Breath", "", &Features::FireBreathBool, BoolDisplay::OnOff, false, [] {});

			if (Features::WantedLevel == 0)
			{
				sub->AddOption<BoolOption<bool>>("Never Wanted", "", &Features::neverwantbool, BoolDisplay::OnOff, false, [] {});
			}

			if (Features::neverwantbool == false)
			{
				sub->AddOption<NumberOption<int>>("Wanted Level", nullptr, &Features::WantedLevel, 0, 5, 1, 3, true, "", "", []
				{
					WantedLvl(Features::WantedLevel);
				});
			}


			sub->AddOption<BoolOption<bool>>("Slow Motion", "Slows Down Time", &Features::SlowMoBool, BoolDisplay::OnOff, false, []
			{
				Features::SlowMo();

			});
			sub->AddOption<BoolOption<bool>>("No Clip", "No Clip", &Features::freecambool, BoolDisplay::OnOff, false, []{});

			sub->AddOption<BoolOption<bool>>("Superman", "", &Features::superman, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<NumberOption<float>>("Run Speed", nullptr, &Features::RunSpeed, 0, 255, 1, 3, true, "", "", [] 	{});

		

			sub->AddOption<NumberOption<int>>("Alpha", nullptr, &Features::alpha, 0, 255, 5, 3, true, "", "", []{
			
				if (Features::alpha != 255)
				{
					ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), Features::alpha, false);
				}

			});

			sub->AddOption<BoolOption<bool>>("SlideRun", "", &Features::SlideRunBool, BoolDisplay::OnOff, false, [] { Features::BackstrokeSpeed(); });
			sub->AddOption<BoolOption<bool>>("No Ragdoll", "", &Features::RagdollBool, BoolDisplay::OnOff, false, [] { Features::NoRagdoll(); });
			sub->AddOption<BoolOption<bool>>("Off Radar", "", &Features::OffRadarBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Tiny Player", "", &Features::TinyPlayerBool, BoolDisplay::OnOff, false, [] { Features::TinyPlayer(); });
			sub->AddOption<BoolOption<bool>>("Forcefield", nullptr, &Features::Forcefield, BoolDisplay::OnOff, false, [] { });

			sub->AddOption<RegularOption>("Fix Health", "", [] { Features::HealPlayer(); });
			sub->AddOption<RegularOption>("Random Outfit", "", [] { PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true); });
			sub->AddOption<RegularOption>("Wash your body", "", [] {  int Ped = PLAYER::PLAYER_PED_ID(); PED::CLEAR_PED_BLOOD_DAMAGE(Ped); PED::RESET_PED_VISIBLE_DAMAGE(Ped); });
			sub->AddOption<RegularOption>("Suicide", "", [] { Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_ENTITY_HEALTH }, 0); });



			});



		g_UiManager->AddSubmenu<RegularSubmenu>("Name changer", NAMECHANGE, [](RegularSubmenu* sub)
		{
			//sub->AddOption<RegularOption>("Change Name", "", [] { 

			//				return 0;
			//			Features::SetName("TestDarkMo");

			//
			//});




			sub->AddOption<RegularOption>("~r~Red Name", "", [] { Features::SetName("~r~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~b~Blue Name", "", [] { Features::SetName("~b~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~g~Green Name", "", [] { Features::SetName("~g~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~y~Yellow Name", "", [] { Features::SetName("~y~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~p~Purple Name", "", [] { Features::SetName("~p~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~o~Orange Name", "", [] { Features::SetName("~o~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~c~Grey Name", "", [] { Features::SetName("~c~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~m~Dark Grey Name", "", [] { Features::SetName("~m~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~u~Black Name", "", [] { Features::SetName("~u~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~s~White Name", "", [] { Features::SetName("~s~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~d~Dark Blue Name", "", [] { Features::SetName("~d~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~f~Light Blue Name", "", [] { Features::SetName("~f~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~bold~Bold Name", "", [] { Features::SetName("~bold~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			sub->AddOption<RegularOption>("~italic~Italic Name", "", [] { Features::SetName("~italic~" + (string)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())); });
			
		});


		int Value;
		g_UiManager->AddSubmenu<RegularSubmenu>("Models", MODELS, [](RegularSubmenu* sub)
		{
			//for (auto model : pedModels)
			//{
			//	sub->AddOption<RegularOption>(model, "", [model] {
			//		
			//		
			//		
			//		DWORD model = GAMEPLAY::GET_HASH_KEY(pedModels[i]);
			//		STREAMING::REQUEST_MODEL(model);
			//		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
			//		PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
			//		PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
			//		WAIT(10);
			//		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			//		WAIT(10);
	
			//	
			//	});
			//}

			//for (int i = 0; i < ARRAYSIZE(pedModels); i++)
			//{
			//	Value = i;
			//	sub->AddOption<RegularOption>(pedModels[i], pedModels[i], []
			//	{
			//		DWORD model = GAMEPLAY::GET_HASH_KEY(pedModels[Value]);
			//		STREAMING::REQUEST_MODEL(model);
			//		while (!STREAMING::HAS_MODEL_LOADED(model)) Big::SYSTEM::WAIT(0);
			//		PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
			//		PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
			//		Big::SYSTEM::WAIT(10);
			//		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			//		Big::SYSTEM::WAIT(10);
			//	});
			//}


		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Chat Commands", CHATCOMMANDS, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Enable", nullptr, &Features::ChatCommands, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("/vehicle", nullptr, &Features::SlashVehicle, BoolDisplay::OnOff, false, [] { });
			//sub->AddOption<BoolOption<bool>>("/cash", nullptr, &Features::SlashCash, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("/otr", nullptr, &Features::SlashOtr, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("/day", nullptr, &Features::SlashDay, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("/night", nullptr, &Features::SlashNight, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("/snow", nullptr, &Features::SlashSnow, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("/clear", nullptr, &Features::SlashClear, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("/weapons", nullptr, &Features::SlashWeapons, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("/neverwanted", nullptr, &Features::SlashNeverWanted, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("/clone", nullptr, &Features::SlashClone, BoolDisplay::OnOff, false, [] { });
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Contact Requests", CONTACTS, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Helicopter Backup", "", [] { globalHandle(2528542).At(4380).As<int>() = 1; });
			sub->AddOption<RegularOption>("Helicopter Pickup", "", [] { globalHandle(2528542).At(826).As<int>() = 1; });
			sub->AddOption<RegularOption>("Boat Pickup", "", [] { globalHandle(2528542).At(825).As<int>() = 1; });
			sub->AddOption<RegularOption>("Ammo Drop", "", [] { globalHandle(2528542).At(824).As<int>() = 1; });
			sub->AddOption<RegularOption>("Crate Drop", "", [] { globalHandle(2528542).At(834).As<int>() = 1; });
			sub->AddOption<RegularOption>("Airstrike", "", [] { globalHandle(2528542).At(4381).As<int>() = 1; });



		});



		//g_UiManager->AddSubmenu<RegularSubmenu>("Telport Options", TELEPORTT, [](RegularSubmenu* sub)
		//{

		//	sub->AddOption<RegularOption>("Teleport to him", "Teleport you to the player", [&]
		//	{
		//		Entity handle;
		//		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
		//		PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
		//		ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);

		//		DC_Message((char*)"Teleported!");

		//	});

		//	sub->AddOption<RegularOption>("Teleport into Vehicle", "Teleport you into his Vehicle", [&]
		//	{
		//		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
		//		for (int i = -1; i < 32; i++)
		//		{
		//			if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i))
		//			{
		//				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, i);
		//			}
		//		}
		//		DC_Message((char*)"Teleported in Vehicle!");
		//	});


		//});

		g_UiManager->AddSubmenu<RegularSubmenu>("Remote Money Notifys", REMOTEMONEY, [](RegularSubmenu* sub)
		{

			sub->AddOption<NumberOption<int>>("Money Amount", nullptr, &Features::MoneyNotifyAmount, 0, 99999, 100, 3, true, "", "", [] {
			});


				sub->AddOption<RegularOption>("Disbursed Money Message", nullptr, [&]
				{

					Player player = g_SelectedPlayer;

					DWORD64 args[14] = { NOTIFICATION, player, 1018143336, Features::MoneyNotifyAmount };
					Hooks::TriggerScriptEvent(1, args, 14, 1 << player);
				});

				sub->AddOption<RegularOption>("Deposited Money Message", nullptr, [&]
				{

					Player  player = g_SelectedPlayer;

					DWORD64 penis[15] = { NOTIFICATION, player, -141590900, Features::MoneyNotifyAmount };
					Hooks::TriggerScriptEvent(1, penis, 15, 1 << player);
				});

				sub->AddOption<RegularOption>("Stolen Money Message", nullptr, [&]
				{

					Player  player = g_SelectedPlayer;

					DWORD64 penis[15] = { NOTIFICATION, player, 309201771, Features::MoneyNotifyAmount };
					Hooks::TriggerScriptEvent(1, penis, 15, 1 << player);
				});

				sub->AddOption<RegularOption>("APP - Activated Message", nullptr, [&]
				{

					Player  player = g_SelectedPlayer;

					DWORD64 penis[15] = { APP_NOTIFY, player, 246714254, Features::MoneyNotifyAmount };
					Hooks::TriggerScriptEvent(1, penis, 15, 1 << player);
				});

				sub->AddOption<RegularOption>("APP - Disabled Message", nullptr, [&]
				{

					Player  player = g_SelectedPlayer;

					DWORD64 penis[15] = { APP_NOTIFY, player, -858848965, Features::MoneyNotifyAmount };
					Hooks::TriggerScriptEvent(1, penis, 15, 1 << player);
				});

				sub->AddOption<RegularOption>("Cell-Positions all Player Message", nullptr, [&]
				{

					Player player = g_SelectedPlayer;



					uint64_t args[4] = { NOTIFICATION, player, 1192107944, Features::MoneyNotifyAmount };
					Hooks::TriggerScriptEvent(1, args, 4, 1 << player);
				});

				sub->AddOption<RegularOption>("Marker = Hidden - Notify", nullptr, [&]
				{

					Player player = g_SelectedPlayer;



					uint64_t args[4] = { NOTIFICATION, player, 2029894551, Features::MoneyNotifyAmount };
					Hooks::TriggerScriptEvent(1, args, 4, 1 << player);
				});



				sub->AddOption<RegularOption>("Marker = Hidden - Notify", nullptr, [&]
				{

					Player player = g_SelectedPlayer;



					uint64_t args[4] = { NOTIFICATION, player, -871580373, Features::MoneyNotifyAmount };
					Hooks::TriggerScriptEvent(1, args, 4, 1 << player);
				});



		});



		g_UiManager->AddSubmenu<RegularSubmenu>("Remote Messages", REMOTEMESSAGE, [](RegularSubmenu* sub)
		{

			sub->AddOption<SubOption>("Remote Money Messages", "More nice Remote Messages", REMOTEMONEY);



			sub->AddOption<RegularOption>("Sent Error Message", "Sent your player an Error Message", [&]
			{
				Player player = g_SelectedPlayer; //upd
				uint64_t args[3] = { SEND_ERROR_MSG, player, 0 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			});

			sub->AddOption<RegularOption>("Sent Spectating Message", nullptr, [&]
			{
				Player player = g_SelectedPlayer; //upd
				uint64_t args[3] = { SPECTATE_MESSAGE, player, 0 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			});

			sub->AddOption<RegularOption>("Sent Spectating Message 2", nullptr, [&]
			{
				DWORD64 args[14] = { SPECTATE_MESSAGE, g_SelectedPlayer, -2129516738 };
				Hooks::TriggerScriptEvent(1, args, 14, 1 << g_SelectedPlayer);
			});

			sub->AddOption<RegularOption>("Sent Stop-Spectating Message", nullptr, [&]
			{
				Player player = g_SelectedPlayer; //upd
				uint64_t args[3] = { STOPP_SPECT_MSG, player, 0 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			});

			sub->AddOption<RegularOption>("Sent Insurance Message", nullptr, [&]
			{
				Player player = g_SelectedPlayer;

				DWORD64 args[2] = { INSURANCE_MESSAGE, player };
				Hooks::TriggerScriptEvent(1, args, 2, 1 << player);
			});

			sub->AddOption<RegularOption>("Sent Blame Kill Notify", nullptr, [&]
			{
				Player player = g_SelectedPlayer;



				uint64_t args[3] = { NOTIFICATION, player, 692650692 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			});

			sub->AddOption<RegularOption>("Sent Blame Delivery Money Notify", nullptr, [&]
			{
				Player player = g_SelectedPlayer;



				uint64_t args[3] = { NOTIFICATION, player, 692650692 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			});


			sub->AddOption<RegularOption>("Sent Level Missed Notify", nullptr, [&]
			{
				Player player = g_SelectedPlayer;



				uint64_t args[3] = { NOTIFICATION, player, -2141984028 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			});

			sub->AddOption<RegularOption>("Sent Easiest Way Notify", nullptr, [&]
			{
				Player player = g_SelectedPlayer;



				uint64_t args[3] = { NOTIFICATION, player, 1576922578 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			});

			sub->AddOption<RegularOption>("Sent Smuggler Vehicle Down", nullptr, [&]
			{
				Player player = g_SelectedPlayer;



				uint64_t args[3] = { NOTIFICATION, player, 1393757853 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			});

			sub->AddOption<RegularOption>("Sent attached Transporter Notify", nullptr, [&]
			{
				Player player = g_SelectedPlayer;



				uint64_t args[3] = { NOTIFICATION, player, 1393757853 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			});


		});





		g_UiManager->AddSubmenu<RegularSubmenu>("Remote Scripts Events", REMOTESCRIPT, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Remote Messages", nullptr, REMOTEMESSAGE);
			sub->AddOption<BoolOption<bool>>("Remote Spam Transaction Error", nullptr, &Features::TransActionSpamBool, BoolDisplay::OnOff);





			//sub->AddOption<RegularOption>("Remote Rotate Cam", nullptr, [&]
			//{
			//	Player player = g_SelectedPlayer;
			//	uint64_t args[3] = { ROT_CAM, player, -1859848501 };
			//	Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
			//});


			//sub->AddOption<RegularOption>("Remote Black Screen", nullptr, [&]
			//{
			//	DWORD64 args[9] = { BLACK_SCREEN, g_SelectedPlayer, 0, 0, 0, -1, 1, 1, 0 };
			//	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
			//});

			//sub->AddOption<RegularOption>("Remote Infinity Black Screen", nullptr, [&]
			//{
			//	DWORD64 args[9] = { BLACK_SCREEN, g_SelectedPlayer, 0, 0, 0, -1, 1, 1, 0 };
			//	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
			//});



			//sub->AddOption<RegularOption>("Remote Give Wanted", nullptr, [&]
			//{
			//	Ped playa = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			//	const int maxPeds = 10;
			//	Ped ClonedPed[maxPeds];
			//	Ped playerPed = PLAYER::PLAYER_PED_ID();
			//	Vector3 coords = coordsOf(playa);

			//	for (int i = 0; i < maxPeds; i++)
			//	{
			//		ClonedPed[i] = PED::CLONE_PED(playa, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 1);
			//		ENTITY::SET_ENTITY_COORDS(ClonedPed[i], coords.x, coords.y, coords.z + 25, 0, 0, 0, 1);
			//		PED::SET_PED_AS_COP(ClonedPed[i], true);
			//		Vector3 cloneCoord = ENTITY::GET_ENTITY_COORDS(ClonedPed[i], 0);
			//		ENTITY::SET_ENTITY_VISIBLE(ClonedPed[i], false, false);
			//		//FIRE::ADD_OWNED_EXPLOSION(playa, cloneCoord.x, cloneCoord.y, cloneCoord.z, 9, 5.0f, 0, 1, 0.0f);
			//		addOwnedExplosionop(playa, cloneCoord.x, cloneCoord.y, cloneCoord.z, 9, 5.0f, 0, 1, 0.0f);
			//		PED::DELETE_PED(&ClonedPed[i]);
			//	}
			//});

			//sub->AddOption<RegularOption>("Remote Remote Wanted", nullptr, [&]
			//{
			//	int handle = globalHandle(1624079).At(g_SelectedPlayer, 558).At(491).As<int>();
			//	DWORD64 args[3] = { REMOVE_WANTED_LEVEL, g_SelectedPlayer, handle };
			//	Hooks::TriggerScriptEvent(1, args, 3, 1 << g_SelectedPlayer);
			//});




			//sub->AddOption<RegularOption>("Remote Sent to Mission", nullptr, [&]
			//{
			//	DWORD64 args[2] = { SEND_TO_MISSION, g_SelectedPlayer };
			//	Hooks::TriggerScriptEvent(1, args, 2, 1 << g_SelectedPlayer);
			//});

			//sub->AddOption<RegularOption>("Remote Banner 1", nullptr, [&]
			//{
			//	DWORD64 args[4] = { SHOW_BANNER1, g_SelectedPlayer, 0, 0 };
			//	Hooks::TriggerScriptEvent(1, args, 4, 1 << g_SelectedPlayer);
			//});

			//sub->AddOption<RegularOption>("Remote Banner 2", nullptr, [&]
			//{
			//	uint64_t args[3] = { SHOW_BANNER1, g_SelectedPlayer, SHOW_BANNER2 };
			//	Hooks::TriggerScriptEvent(1, args, 3, 1 << g_SelectedPlayer);
			//});

			//sub->AddOption<RegularOption>("Remote Mission Suggestion", nullptr, [&]
			//{
			//	DWORD64 args[4] = { FORCE_MISSION, g_SelectedPlayer, 0, 0 };
			//	Hooks::TriggerScriptEvent(1, args, 4, 1 << g_SelectedPlayer);
			//});

			//sub->AddOption<RegularOption>("Remote CEO Kick", nullptr, [&]
			//{
			//	DWORD64 args[4] = { CEO_KICK, g_SelectedPlayer, 0, 0 };
			//	Hooks::TriggerScriptEvent(1, args, 4, 1 << g_SelectedPlayer);
			//});

		});






		g_UiManager->AddSubmenu<RegularSubmenu>("Remote Weapons", REMOTEWEAPONOPT, [](RegularSubmenu* sub)
		{



			sub->AddOption<RegularOption>("Give All Weapons", nullptr, [&]
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
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), Weapons[i], 9999, true);
					}
			});

			sub->AddOption<RegularOption>("Delete All Weapons", nullptr, [&]
			{
				WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true);
			});

		});






		g_UiManager->AddSubmenu<RegularSubmenu>("Blame Options", BLAMEOPT, [](RegularSubmenu* sub)
		{

			sub->AddOption<NumberOption<int>>("Bullet Type", "Select Bullet for Blame", &BulletType, 0, 30, 1, 3, false, "", "", [] {});
			sub->AddOption<NumberOption<float>>("Bullet Damage", "Select Bullet Dmage", &BulletDamage, 0, 100, 1, 3, false, "", "", [] {});
			sub->AddOption<NumberOption<float>>("Camera Shake", "Select Camera Shake", &BulletCameraShake, 0, 100, 1, 3, false, "", "", [] {});
			sub->AddOption<BoolOption<bool>>("Bullet Audible", "Player can/can't hear Bullet", &BulletAudible, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("Bullet Invisible", "Player can/can't see Bullet", &BulletInvisible, BoolDisplay::OnOff, false, [] {});



			sub->AddOption<RegularOption>("Spawn Blame", nullptr, [&]
			{


				Player player = g_SelectedPlayer;
				Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
				Player local = PLAYER::PLAYER_ID();

				for (int i = 0; i < 32; i++)
				{
					if (i != local && i != player)
					{
						auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), true);
						addOwnedExplosionop(ped, pos.x, pos.y, pos.z, BulletType, BulletDamage, BulletAudible, BulletInvisible, BulletCameraShake);
					}
				}

			});


		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Drop Options", DROPOPT, [](RegularSubmenu* sub)
		{



			sub->AddOption<SubOption>("Money Drop", "Drop Money", MONEYDROP);
			sub->AddOption<SubOption>("Rain Money Drop", "Drop Money", RAINMONEYDROP);
			sub->AddOption<SubOption>("RP Drop (RP, Crew Lvl)", "Drop Money", RPDROP);


		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Rain Money Drop", RAINMONEYDROP, [](RegularSubmenu* sub)
		{


			sub->AddOption<BoolOption<bool>>("Enable Rain Cash Drop", "Start droping Money", &Features::moneyrain2k, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<int>>("Drop Amount", "Select Bullet for Blame", &Features::DropAmount, 0, 2500, 10, 3, false, "", "", [] {});
			sub->AddOption<NumberOption<int>>("Drop Delay", "Select Bullet for Blame", &Features::BagDelay, 0, 5000, 50, 3, false, "", "", [] {});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("RP Drop", RPDROP, [](RegularSubmenu* sub)
		{




			sub->AddOption<BoolOption<bool>>("Enable RP Drop", "Start droping Money", &Features::RPDropBool, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<int>>("Drop Delay", "Select Bullet for Blame", &Features::RPDROPDELAY, 0, 5000, 50, 3, false, "", "", [] {});




		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Money Drop", MONEYDROP, [](RegularSubmenu* sub)
		{

			sub->AddOption<BoolOption<bool>>("Enable Cash Drop", "Start droping Money", &Features::MoneyDropBool, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<int>>("Drop Amount", "Select Bullet for Blame", &Features::DropAmount, 0, 2500, 10, 3, false, "", "", [] {});
			sub->AddOption<NumberOption<int>>("Drop Delay", "Select Bullet for Blame", &Features::BagDelay, 0, 5000, 50, 3, false, "", "", [] {});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Kicks", KICKS, [](RegularSubmenu* sub)
		{
			//sub->AddOption<RegularOption>("EXTREME Dark Kick", "Super Dark Kick", [] {

			//	DWORD64 args1[4] = { KICK_1, g_SelectedPlayer };
			//	Hooks::TriggerScriptEvent(1, args1, 4, 1 << g_SelectedPlayer);


			//	DWORD64 args2[3] = { KICK_2, g_SelectedPlayer };
			//	Hooks::TriggerScriptEvent(1, args2, 3, 1 << g_SelectedPlayer);


			//	DWORD64 args3[4] = { KICK_3, g_SelectedPlayer };
			//	Hooks::TriggerScriptEvent(1, args3, 4, 1 << g_SelectedPlayer);


			//	DWORD64 args4[5] = { KICK_4, g_SelectedPlayer, 0, 111 };
			//	Hooks::TriggerScriptEvent(1, args4, 5, 1 << g_SelectedPlayer);

			//	DWORD64 args5[3] = { KICK_5, g_SelectedPlayer };
			//	Hooks::TriggerScriptEvent(1, args5, 3, 1 << g_SelectedPlayer);


			//	DWORD64 args6[4] = { KICK_6, g_SelectedPlayer, 50 };
			//	Hooks::TriggerScriptEvent(1, args6, 4, 1 << g_SelectedPlayer);


			//	DWORD64 args7[4] = { KICK_7, g_SelectedPlayer, 20, 1 };
			//	Hooks::TriggerScriptEvent(1, args7, 4, 1 << g_SelectedPlayer);


			//	DWORD64 args8[4] = { KICK_8, g_SelectedPlayer, 20 };
			//	Hooks::TriggerScriptEvent(1, args8, 4, 1 << g_SelectedPlayer);


			//	DWORD64 args9[4] = { KICK_9, g_SelectedPlayer, 20, 1 };
			//	Hooks::TriggerScriptEvent(1, args9, 4, 1 << g_SelectedPlayer);


			//	DWORD64 args10[4] = { KICK_10, g_SelectedPlayer, 20 };
			//	Hooks::TriggerScriptEvent(1, args10, 4, 1 << g_SelectedPlayer);


			//	DWORD64 args11[4] = { KICK_11, g_SelectedPlayer, 20 };
			//	Hooks::TriggerScriptEvent(1, args11, 4, 1 << g_SelectedPlayer);


			//	DWORD64 args12[6] = { KICK_12, g_SelectedPlayer, 0, 0, 0, 36 };
			//	Hooks::TriggerScriptEvent(1, args12, 6, 1 << g_SelectedPlayer);


			//	DWORD64 args13[3] = { KICK_13, g_SelectedPlayer, 36 };
			//	Hooks::TriggerScriptEvent(1, args13, 3, 1 << g_SelectedPlayer);


			//	DWORD64 asd[3] = { KICK_14, g_SelectedPlayer, -4294967260/*36*/ };
			//	Hooks::TriggerScriptEvent(1, asd, 3, 1 << g_SelectedPlayer);

			//	DWORD64 adasdasd[4] = { KICK_15, g_SelectedPlayer, 32 };
			//	Hooks::TriggerScriptEvent(1, adasdasd, 4, 1 << g_SelectedPlayer);


			//	DWORD64 sadfas[5] = { KICK_16, g_SelectedPlayer, 0, 0, 32 };
			//	Hooks::TriggerScriptEvent(1, sadfas, 5, 1 << g_SelectedPlayer);


			//	DWORD64 asasdads[5] = { KICK_17, g_SelectedPlayer, 0, 0, 32 };
			//	Hooks::TriggerScriptEvent(1, asasdads, 5, 1 << g_SelectedPlayer);


			//	DWORD64 dffgdfgd[5] = { KICK_18, g_SelectedPlayer, 4 };
			//	Hooks::TriggerScriptEvent(1, dffgdfgd, 5, 1 << g_SelectedPlayer);


			//	DWORD64 fdfgdhfgh[5] = { KICK_19, g_SelectedPlayer, 7 };
			//	Hooks::TriggerScriptEvent(1, fdfgdhfgh, 5, 1 << g_SelectedPlayer);


			//	DWORD64 fddfgfdg[6] = { KICK_20, g_SelectedPlayer, 0, 59 };
			//	Hooks::TriggerScriptEvent(1, fddfgfdg, 6, 1 << g_SelectedPlayer);

			//	DWORD64 arfghhfgffgs[5] = { KICK_21, g_SelectedPlayer, 0, 59 };
			//	Hooks::TriggerScriptEvent(1, arfghhfgffgs, 5, 1 << g_SelectedPlayer);

			//	DWORD64 asdasdasd[4] = { KICK_22, g_SelectedPlayer, 0, 59 };
			//	Hooks::TriggerScriptEvent(1, asdasdasd, 4, 1 << g_SelectedPlayer);


			//	DWORD64 tzhjtzhhjtgghjgjh[4] = { KICK_23, g_SelectedPlayer, 62 };
			//	Hooks::TriggerScriptEvent(1, tzhjtzhhjtgghjgjh, 4, 1 << g_SelectedPlayer);


			//	DWORD64 qwqweqweqwe[4] = { KICK_24, g_SelectedPlayer, 0, 26 };
			//	Hooks::TriggerScriptEvent(1, qwqweqweqwe, 4, 1 << g_SelectedPlayer);


			//	DWORD64 sijhdgfbsduhfsbvdhgfsdf[5] = { KICK_25, g_SelectedPlayer, 0, 26 };
			//	Hooks::TriggerScriptEvent(1, sijhdgfbsduhfsbvdhgfsdf, 5, 1 << g_SelectedPlayer);


			//	DWORD64 hjgkhjkhjk[4] = { KICK_26, g_SelectedPlayer, 0, 26 };
			//	Hooks::TriggerScriptEvent(1, hjgkhjkhjk, 4, 1 << g_SelectedPlayer);


			//	DWORD64 jkljkljkl[3] = { KICK_27, g_SelectedPlayer, 3 };
			//	Hooks::TriggerScriptEvent(1, jkljkljkl, 3, 1 << g_SelectedPlayer);


			//	DWORD64 qwqwweqqwe[24] = { KICK_28, g_SelectedPlayer, 180 };
			//	Hooks::TriggerScriptEvent(1, qwqwweqqwe, 24, 1 << g_SelectedPlayer);


			//	DWORD64 zuizuizuizu[5] = { KICK_29, g_SelectedPlayer, 64 };
			//	Hooks::TriggerScriptEvent(1, zuizuizuizu, 5, 1 << g_SelectedPlayer);


			//	DWORD64 qweqweqwe[3] = { KICK_30, g_SelectedPlayer, 32 };
			//	Hooks::TriggerScriptEvent(1, qweqweqwe, 3, 1 << g_SelectedPlayer);


			//	DWORD64 uhijewhizuwerhb[4] = { KICK_31, g_SelectedPlayer, 62 };
			//	Hooks::TriggerScriptEvent(1, uhijewhizuwerhb, 4, 1 << g_SelectedPlayer);


			//	DWORD64 asdasdasdasdasd[18] = { KICK_32, g_SelectedPlayer };
			//	Hooks::TriggerScriptEvent(1, asdasdasdasdasd, 18, 1 << g_SelectedPlayer);

			//	DWORD64 asdasdasdasf[3] = { KICK_33, g_SelectedPlayer };
			//	Hooks::TriggerScriptEvent(1, asdasdasdasf, 3, 1 << g_SelectedPlayer);


			//	DWORD64 djkfgndejgnkd[13] = { KICK_34, g_SelectedPlayer, 123 }; //fix
			//	Hooks::TriggerScriptEvent(1, djkfgndejgnkd, 13, 1 << g_SelectedPlayer);


			//	DWORD64 asdasdfgddfgdfg[4] = { KICK_35, g_SelectedPlayer };
			//	Hooks::TriggerScriptEvent(1, asdasdfgddfgdfg, 4, 1 << g_SelectedPlayer);


			//	DWORD64 dfgdfgdfg[21];
			//	*dfgdfgdfg = KICK_36;
			//	dfgdfgdfg[1] = g_SelectedPlayer;
			//	dfgdfgdfg[19] = 125;
			//	Hooks::TriggerScriptEvent(1, dfgdfgdfg, 21, 1 << g_SelectedPlayer);

			//	DWORD64 sdfsdfsdfsdf[4] = { KICK_37, g_SelectedPlayer, 1, 124 };//need check false alarm
			//	Hooks::TriggerScriptEvent(1, sdfsdfsdfsdf, 4, 1 << g_SelectedPlayer);


			//	DWORD64 hjzhjkzhjkzhjkhjkhjk[10] = { KICK_38, g_SelectedPlayer, 1, 10000, 32/*n0*/, 0, 1, 46, 1, 40 };
			//	Hooks::TriggerScriptEvent(1, hjzhjkzhjkzhjkhjkhjk, 10, 1 << g_SelectedPlayer);


			//	DWORD64 ghfgfhfghfghfgh[10] = { KICK_39, g_SelectedPlayer, 1, 10000, 32, 0, 1, 36, 1, 40 };
			//	Hooks::TriggerScriptEvent(1, ghfgfhfghfghfgh, 10, 1 << g_SelectedPlayer);


			//	DWORD64 dfghfgfghhfghfg[25];
			//	*dfghfgfghhfghfg = KICK_40, dfghfgfghhfghfg[1] = g_SelectedPlayer, dfghfgfghhfghfg[2] = 180;
			//	Hooks::TriggerScriptEvent(1, dfghfgfghhfghfg, 25, 1 << g_SelectedPlayer);


			//});

		});




		g_UiManager->AddSubmenu<RegularSubmenu>("Crashes", CRASHES, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Crash 1", "", [] {
				Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				STREAMING::REQUEST_MODEL(0x2D7030F3);
				while (!STREAMING::HAS_MODEL_LOADED(0x856cfb02)) SYSTEM::WAIT(0);
				Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
				PED::CREATE_PED(1, 0x856cfb02, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);

			});

			sub->AddOption<RegularOption>("Crash 2", "", [] {
				Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				STREAMING::REQUEST_MODEL(0x2D7030F3);
				while (!STREAMING::HAS_MODEL_LOADED(0x2D7030F3)) SYSTEM::WAIT(0);
				Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
				PED::CREATE_PED(1, 0x2D7030F3, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);

			});

			sub->AddOption<RegularOption>("Crash 3", "", [] {
				Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				STREAMING::REQUEST_MODEL(0x3F039CBA);
				while (!STREAMING::HAS_MODEL_LOADED(0x3F039CBA)) SYSTEM::WAIT(0);
				Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
				PED::CREATE_PED(1, 0x3F039CBA, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);

			});

			sub->AddOption<RegularOption>("Crash 4", "", [] {
				Player nigga = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				STREAMING::REQUEST_MODEL(0xE0CBBA54);
				while (!STREAMING::HAS_MODEL_LOADED(0xE0CBBA54)) SYSTEM::WAIT(0);
				Vector3 fposition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(nigga, 0.0, 5.0, 0.0);
				PED::CREATE_PED(1, 0x3F039CBA, fposition.x, fposition.y, fposition.z, ENTITY::GET_ENTITY_HEADING(nigga), TRUE, TRUE);

			});



		});

		g_UiManager->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
		{
			Features::LoadPlayerInfo(g_SelectedPlayer);

			sub->AddOption<SubOption>("Teleport Options", "Teleport Settings", TELEPORTT);
			sub->AddOption<SubOption>("Remote Script Events", "Remote Scripts Events", REMOTESCRIPT);
			sub->AddOption<SubOption>("Kick Events", nullptr, KICKS);
			sub->AddOption<SubOption>("Crashes", nullptr, CRASHES);
			sub->AddOption<SubOption>("Ped Spawns", nullptr, PEDSPAWN);
			sub->AddOption<SubOption>("Money Options", nullptr, DROPOPT);
			sub->AddOption<SubOption>("Object Attachment Options", "Attach Objects to player", SELECTEDATTACH);

			sub->AddOption<SubOption>("Blame Options", "", BLAMEOPT);
			sub->AddOption<SubOption>("Remote Teleports", nullptr, TELEPORTSOLO);
			sub->AddOption<SubOption>("Remote Weapon Options", "Weapon Options", REMOTEWEAPONOPT);



			/*sub->AddOption<BoolOption<bool>>("Spectate", nullptr, &Features::SpectateList[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::Spectate(Features::SpectateList[g_SelectedPlayer]); });*/
			sub->AddOption<BoolOption<bool>>("Fuck Their Cam", nullptr, &Features::FuckCamBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Explode", nullptr, &Features::ExplodeList[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::ExplodeLoopPlayer(Features::ExplodeList[g_SelectedPlayer]); });
			sub->AddOption<BoolOption<bool>>("Water Loop", nullptr, &Features::WaterList[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::WaterLoop(Features::WaterList[g_SelectedPlayer]); });
			sub->AddOption<BoolOption<bool>>("Fire Loop", nullptr, &Features::FireList[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::FireLoop(Features::FireList[g_SelectedPlayer]); });
			sub->AddOption<BoolOption<bool>>("Freeze", nullptr, &Features::FreezeList[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::Freeze(Features::FreezeList[g_SelectedPlayer]); });
			sub->AddOption<BoolOption<bool>>("Force Fly", nullptr, &Features::remoteContainerFlybool, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Fuck Handeling", nullptr, &Features::fuckedhandling, BoolDisplay::OnOff);





			sub->AddOption<RegularOption>("Airstrike Player", "", [] { Features::AirStrikeKill(); });
			sub->AddOption<RegularOption>("Clone Vehicle", "", [] { Features::CloneVehicle(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer)); });
			sub->AddOption<RegularOption>("Ram Player", "", [] { Features::RamPlayer(); });
			sub->AddOption<RegularOption>("Clone Player", "", [] { 
				PED::CLONE_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1, 1, 1);
			
			});

			sub->AddOption<RegularOption>("Save RID", "", [] {
				int netHandle[13];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, netHandle, 13);
				char* UserID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);


				Features::SaveRID(PLAYER::GET_PLAYER_NAME(g_SelectedPlayer), UserID);
			});


			sub->AddOption<RegularOption>("Attach Me to Him", "", [] {
				ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, true, true, false, true, 2, true);
			});
			sub->AddOption<RegularOption>("Detach Me from Him", "", [] {
				ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);

			});


		sub->AddOption<RegularOption>("Kick him out of car", "", [] {
			Player penis = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);

			if (PED::IS_PED_IN_ANY_VEHICLE(penis, 1))
			{
				RequestControlOfEnt(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true));
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true)));
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
				}

			}

			else {

			}


		});


			Ped SelectedCoords = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			Vector3 SelectCoords = ENTITY::GET_ENTITY_COORDS(SelectedCoords, true);
			GRAPHICS::DRAW_MARKER(2, SelectCoords.x, SelectCoords.y, SelectCoords.z + 1.25, 0, 0, 0, 0, 180, 0, 0.25, 0.25, 0.25, 200, 94, 100, 255, 1, 1, 1, 0, 0, 0, 0);


			//sub->AddOption<RegularOption>("Give GodMode", "He protected against shoots", []
			//{
			//	Hash oball = GAMEPLAY::GET_HASH_KEY("prop_juicestand");
			//	STREAMING::REQUEST_MODEL(oball);
			//	while (!STREAMING::HAS_MODEL_LOADED(oball))
			//	{

			//	}
			//	Object orangeball;
			//	orangeball = OBJECT::CREATE_OBJECT(oball, 0, 0, 0, true, 1, -1, &orangeball, true, false, false);

			//	RequestControlOfEnt(orangeball);
			//	ENTITY::SET_ENTITY_VISIBLE(orangeball, 0, 0);
			//	ENTITY::ATTACH_ENTITY_TO_ENTITY(orangeball, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);

			//});



			sub->AddOption<RegularOption>("Copy Outfit", "Copy Outfit of the Player", []
			{
				for (int i = 0; i < 12; i++)
				{
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), i), PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), i), PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), i));
					for (int i = 0; i < 2; i++) {
						g_FiberScript->Wait(0);
					}
				}

			});



			sub->AddOption<RegularOption>("Force Host", "", []
				{
					globalHandle(2417897 + 816).As<int>() = 0;
					globalHandle(2462883).As<const char*>() = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
					globalHandle(1628237).At(PLAYER::PLAYER_ID(), 615).At(10).As<int>() = 1;

				});

			sub->AddOption<RegularOption>("Cage Him", "Put your Player into the Cage", []
			{
				Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
				Object obj;
				OBJECT::CREATE_OBJECT($("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1, true, 1, -1, &obj, true, false, false);

			});

			sub->AddOption<RegularOption>("Kill", "Kill Player", []
			{
				Ped selectdenfick = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectdenfick, 1);
				addOwnedExplosion1(selectdenfick, pos.x, pos.y, pos.z, 29, 999.f, false, false, 0.f);

			});

			sub->AddOption<RegularOption>("Stealth Kill", "kill em", [&]
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

			});



			sub->AddOption<RegularOption>("Gift Vehicle", "Gift him Vehicle", []
			{
				DECORATOR::DECOR_SET_INT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1), (char*)"Player_Vehicle", NETWORK::_NETWORK_HASH_FROM_PLAYER_HANDLE(g_SelectedPlayer));
				DECORATOR::DECOR_SET_INT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0), (char*)"Player_Vehicle", NETWORK::_NETWORK_HASH_FROM_PLAYER_HANDLE(g_SelectedPlayer));

			});

			sub->AddOption<RegularOption>("Show Profile", nullptr, []
			{
				int handle[76];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
				NETWORK::NETWORK_SHOW_PROFILE_UI(&handle[0]);
			});

			sub->AddOption<RegularOption>("Add as friend", nullptr, []
			{
				int handle[76];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
				NETWORK::NETWORK_SHOW_PROFILE_UI(&handle[0]);
			});


			sub->AddOption<RegularOption>("Slingshot Car", "Slingshot his car", []
			{
				Player penis = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);

				if (PED::IS_PED_IN_ANY_VEHICLE(penis, 1))
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true));
					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true)));
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
					}
					DC_Message((char*)"Slingshotted!");
				}

				else {
					DC_Message((char*)"Player isnt in a Vehicle!");
				}

			});

		});
		





		g_UiManager->AddSubmenu<RegularSubmenu>("Ped Manager", PEDSPAWN, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Spawn Enemy", nullptr, ENEMY);
			sub->AddOption<SubOption>("Spawn Bodyguard", nullptr, BODYGUARD);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Spawn Enemy", ENEMY, [](RegularSubmenu* sub)
		{
			for (auto enemies : pedModels)
			{
				sub->AddOption<RegularOption>(enemies, "", [enemies] { Features::Enemy((char*)enemies); });
			}
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Spawn Bodyguard", BODYGUARD, [](RegularSubmenu* sub)
		{
			for (auto bodyguard : pedModels)
			{
				sub->AddOption<RegularOption>(bodyguard, "", [bodyguard] { Features::Bodyguard((char*)bodyguard); });
			}
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Attach Objects", SELECTEDATTACH, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Detach Objects", "", [] { Features::ClearProps(); });
			for (auto objects1 : objects)
			{
				sub->AddOption<RegularOption>(objects1, "", [objects1] { Features::AttachObjects((char*)objects1); });
			}
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Teleports", TELEPORTS, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Eclipse Towers", "", [] { Features::Teleport1(); });
			sub->AddOption<RegularOption>("West Vinewood", "", [] { Features::Teleport2(); });
			sub->AddOption<RegularOption>("Las Lagunas", "", [] { Features::Teleport3(); });
			sub->AddOption<RegularOption>("Spanish Ave", "", [] { Features::Teleport4(); });
			sub->AddOption<RegularOption>("Power St", "", [] { Features::Teleport5(); });
			sub->AddOption<RegularOption>("Del Perro", "", [] { Features::Teleport6(); });
			sub->AddOption<RegularOption>("Milton Rd", "", [] { Features::Teleport7(); });
			sub->AddOption<RegularOption>("The Royale", "", [] { Features::Teleport8(); });
			sub->AddOption<RegularOption>("La Puerta", "", [] { Features::Teleport9(); });
			sub->AddOption<RegularOption>("Rockford Dr", "", [] { Features::Teleport10(); });
			sub->AddOption<RegularOption>("Dream Tower", "", [] { Features::Teleport11(); });
			sub->AddOption<RegularOption>("San Vitas", "", [] { Features::Teleport12(); });
			sub->AddOption<RegularOption>("Vespucci Blvd", "", [] { Features::Teleport13(); });
			sub->AddOption<RegularOption>("Cougar Ave", "", [] { Features::Teleport14(); });
			sub->AddOption<RegularOption>("Prosperity St", "", [] { Features::Teleport15(); });
			sub->AddOption<RegularOption>("Weazel Plaza", "", [] { Features::Teleport16(); });
			sub->AddOption<RegularOption>("Del Perro Office", "", [] { Features::Teleport17(); });
			sub->AddOption<RegularOption>("Maze Bank West Office", "", [] { Features::Teleport18(); });
			sub->AddOption<RegularOption>("Arcadius Office", "", [] { Features::Teleport19(); });
			sub->AddOption<RegularOption>("Maze Bank Office", "", [] { Features::Teleport20(); });
			sub->AddOption<NumberOption<std::int32_t>>("Custom Location", nullptr, &Features::WantedLevel, 1, 115, 1, 3, true, "", "", [] {
				Features::TeleportCustom(Features::WantedLevel);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::WantedLevel = getInputs();
						if (Features::WantedLevel > 5)
							Features::WantedLevel = 5;
						if (Features::WantedLevel < 0)
							Features::WantedLevel = 0;
						Features::TeleportCustom(Features::WantedLevel);
					});
				}
			
			});
		});
		static const char* actions[] = {
			"GBSAL_DRAW", "GBSAL_COLL", "GBFK_TEXP", "GR_VISTKR_SELL"
		};
		g_UiManager->AddSubmenu<RegularSubmenu>("Script Events", SCRIPTS, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Invites", nullptr, INVITES);
			sub->AddOption<SubOption>("Messages", nullptr, MESSAGES);
			sub->AddOption<BoolOption<bool>>("Sound Spam", nullptr, &Features::Spam[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::DoSoundSpam(Features::Spam[g_SelectedPlayer]); });
			sub->AddOption<BoolOption<bool>>("Remote OTR", nullptr, &Features::RemoteOTRBool[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::RemoteOTR(Features::RemoteOTRBool[g_SelectedPlayer]); });
			sub->AddOption<BoolOption<bool>>("Cops Blind Eye", nullptr, &Features::BlindEyeBool[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::BlindEye(Features::BlindEyeBool[g_SelectedPlayer]); });
			sub->AddOption<BoolOption<bool>>("Camera Spam", nullptr, &Features::CameraSpam[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::sendFaceCameraForward(Features::CameraSpam[g_SelectedPlayer]); });
			sub->AddOption<BoolOption<bool>>("Never Wanted", nullptr, &Features::RemoteNeverWanted[g_SelectedPlayer], BoolDisplay::OnOff, false, [] { Features::RemoveWanted(Features::RemoteNeverWanted[g_SelectedPlayer]); });

			sub->AddOption<RegularOption>("Show GTA-V Banner I", "", [] {

				DWORD64 args[4] = { SHOW_BANNER1, g_SelectedPlayer, 0, 0 };
				Hooks::TriggerScriptEvent(1, args, 4, 1 << g_SelectedPlayer);

			});

			sub->AddOption<RegularOption>("Show GTA-V Banner II", "", [] {
				DWORD64 args[3] = { SHOW_BANNER1, g_SelectedPlayer, SHOW_BANNER1 };
				Hooks::TriggerScriptEvent(1, args, 3, 1 << g_SelectedPlayer);
			});


			sub->AddOption<RegularOption>("Force Disappear", "", [] { Features::ForceDisappear(); });
			sub->AddOption<RegularOption>("Remove Wanted", "", [] { Features::RemoveWanted(g_SelectedPlayer); });
			sub->AddOption<RegularOption>("Send To Job", "", [] { Features::SendToJob(); });
			sub->AddOption<RegularOption>("CEO Kick", "", [] { Features::CEOKick(); });
			sub->AddOption<RegularOption>("CEO Ban", "", [] { Features::CEOBan(); });
			sub->AddOption<RegularOption>("Transaction Error", "", [] { Features::TransactionError(g_SelectedPlayer); });
			sub->AddOption<RegularOption>("Infinite Loading Screen", "", [] { Features::InfiniteLoading(); });
			sub->AddOption<RegularOption>("Remove From Vehicle", "", [] { Features::GentleKick(); });

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Invites", INVITES, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Yacht", "", [] { Features::Invite2Place(g_SelectedPlayer, 1); });
			sub->AddOption<RegularOption>("Office", "", [] { Features::Invite2Place(g_SelectedPlayer, 2); });
			sub->AddOption<RegularOption>("Clubhouse", "", [] { Features::Invite2Place(g_SelectedPlayer, 3); });
			sub->AddOption<RegularOption>("Office Garage", "", [] { Features::Invite2Place(g_SelectedPlayer, 6); });
			sub->AddOption<RegularOption>("Apartment", "", [] { Features::Invite2Place(g_SelectedPlayer, 70); });
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Messages", MESSAGES, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("1.5bill Banked", nullptr, &Features::AddSpam, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("1.5bill Removed", nullptr, &Features::RemoveSpam, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<RegularOption>("Troll Insurance Message", "", [] { Features::TrollMessage(); });
			sub->AddOption<RegularOption>("Spectating", "", [] { Features::MessageSpam(g_SelectedPlayer, RemoteMessageSpectating); });
			sub->AddOption<RegularOption>("Idle Kick", "", [] { Features::MessageSpam(g_SelectedPlayer, RemoteMessageIdleKick); });
			sub->AddOption<RegularOption>("Psycho", "", [] { Features::MessageSpam(g_SelectedPlayer, RemoteMessagePsycho); });
			sub->AddOption<RegularOption>("Goon Remove", "", [] { Features::MessageSpam(g_SelectedPlayer, RemoteMessageGoonRemove); });
			sub->AddOption<RegularOption>("Goon Leave", "", [] { Features::MessageSpam(g_SelectedPlayer, RemoteMessageGoonLeave); });
			sub->AddOption<RegularOption>("Goon Join", "", [] { Features::MessageSpam(g_SelectedPlayer, RemoteMessageGoonJoin); });
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Auto Pilot", AUTPILOT, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Start Autopilot", "Start Autopilot driving to your Waypoint", [] {
				int WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);
				int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

				if (UI::DOES_BLIP_EXIST(WaypointHandle)) {
					Vector3 WaypointPos = UI::GET_BLIP_COORDS(WaypointHandle);
					AI::TASK_VEHICLE_DRIVE_TO_COORD(PLAYER::PLAYER_PED_ID(), VehID, WaypointPos.x, WaypointPos.y, WaypointPos.z, 18.f, 0, VehID, DrivingStyleNormal, 1.f, true);
					DC_Message((char*)"Starting Autopilot!");
				}
				else
					DC_Message((char*)"No Waypoint found!");
			});

			sub->AddOption<RegularOption>("Stop Autopilot", "Stop the Autopilo", [] {
			
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
				DC_Message((char*)"Stoped Autopilot");
			});
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Animations", ANIMTATION, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Animations", "Animations for you", ANIIMATION);
			sub->AddOption<SubOption>("Scenarios", "Scenarios for you", SCENARIO);


		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Animations", ANIIMATION, [](RegularSubmenu* sub)


		{
			sub->AddOption<RegularOption>("~r~Reset Animation", "Stop your current Animation", [] {AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); });

			sub->AddOption<RegularOption>("Pole Dance", "Pole Dance Animation", [] { doAnimation((char*)"mini@strip_club@pole_dance@pole_dance1", (char*)"pd_dance_01"); });

			sub->AddOption<RegularOption>("Push Ups", "Push Ups Animation", [] { doAnimation((char*)"amb@world_human_push_ups@male@base", (char*)"base"); });



			sub->AddOption<RegularOption>("Sit Ups", "Sit Ups Animation", [] { doAnimation((char*)"amb@world_human_sit_ups@male@base", (char*)"base"); });
			sub->AddOption<RegularOption>("Meditation", "Mediation Animation", [] { doAnimation((char*)"rcmcollect_paperleadinout@", (char*)"meditiate_idle"); });



			sub->AddOption<RegularOption>("On Fire", "On Fire Animation", [] { doAnimation((char*)"random@arrests", (char*)"kneeling_arrest_idle"); });

			sub->AddOption<RegularOption>("Celebrate", "Celebrate Animation", [] { doAnimation((char*)"rcmfanatic1celebrate", (char*)"celebrate"); });

			sub->AddOption<RegularOption>("Electrocution", "Electrocution Animation", [] { doAnimation((char*)"ragdoll@human", (char*)"electrocute"); });

			sub->AddOption<RegularOption>("Suicide", "Suicide Animation", [] { doAnimation((char*)"mp_suicide", (char*)"pistol"); });

			sub->AddOption<RegularOption>("Showering", "Showering Animation", [] { doAnimation((char*)"mp_safehouseshower@male@", (char*)"male_shower_idle_b"); });

			sub->AddOption<RegularOption>("Fuck Receiver", "Fuck Reciever Animation", [] { doAnimation((char*)"rcmpaparazzo_2", (char*)"shag_loop_poppy"); });

			sub->AddOption<RegularOption>("Fuck Giver", "Fuck Giver Animation", [] { doAnimation((char*)"rcmpaparazzo_2", (char*)"shag_loop_a"); });

			sub->AddOption<RegularOption>("Stripper Dance", "Stripper Dance Animation", [] { doAnimation((char*)"mini@strip_club@private_dance@part1", (char*)"priv_dance_p1"); });


			
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Animations", SCENARIO, [](RegularSubmenu* sub)
		{


			sub->AddOption<RegularOption>("~r~Reset Scenarios", "Reset Scenarios", [] {AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); });

			sub->AddOption<RegularOption>("Paparizzi", "Paparizzi Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_PAPARAZZI", 0, true); });

			sub->AddOption<RegularOption>("Drug Dealer", "Drug Dealer Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_DRUG_DEALER_HARD", 0, true); });

			sub->AddOption<RegularOption>("Drinking Coffee", "Drinking Coffee Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_AA_COFFEE", 0, true); });

			sub->AddOption<RegularOption>("Playing Instruments", "Playing Instruments Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_MUSICIAN", 0, true); });

			sub->AddOption<RegularOption>("Flexing", "Flexing Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_MUSCLE_FLEX", 0, true); });

			sub->AddOption<RegularOption>("Jogging", "Jogging Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_JOG_STANDING", 0, true); });

			sub->AddOption<RegularOption>("Binoculars", "Binoculars Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_BINOCULARS", 0, true); });

			sub->AddOption<RegularOption>("Clipboard", "Clipboard Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_CLIPBOARD", 0, true); });

			sub->AddOption<RegularOption>("Bench", "Bench Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, true); });

			sub->AddOption<RegularOption>("Chin Ups", "Chin Ups Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"PROP_HUMAN_MUSCLE_CHIN_UPS", 0, true); });

			sub->AddOption<RegularOption>("BBQ", "BBQ Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"PROP_HUMAN_BBQ", 0, true); });

			sub->AddOption<RegularOption>("Superhero", "Superhero Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_SUPERHERO", 0, true); });

			sub->AddOption<RegularOption>("Fishing", "Fishing Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_STAND_FISHING", 0, true); });

			sub->AddOption<RegularOption>("Security", "Security Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, true); });

			sub->AddOption<RegularOption>("Leaf Blower", "Leaf Blower Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, true); });

			sub->AddOption<RegularOption>("Film Shocking", "Film Shocking Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true); });

			sub->AddOption<RegularOption>("Idle Cop", "Idle Cop Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_COP_IDLES", 0, true); });

			sub->AddOption<RegularOption>("Drinking", "Drinking Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_DRINKING", 0, true); });

			sub->AddOption<RegularOption>("Golf Player", "Golf Player Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_GOLF_PLAYER", 0, true); });

			sub->AddOption<RegularOption>("Welding", "Welding Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_WELDING", 0, true); });

			sub->AddOption<RegularOption>("Smoking Pot", "Smoking Pot Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_SMOKING_POT", 0, true); });

			sub->AddOption<RegularOption>("Hammering", "Hammering Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_HAMMERING", 0, true); });

			sub->AddOption<RegularOption>("Tennis", "Tennis Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_TENNIS_PLAYER", 0, true); });

			sub->AddOption<RegularOption>("Drilling", "Drilling Scenario", [] {AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), (char*)"WORLD_HUMAN_CONST_DRILL", 0, true); });



		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Acrobatic", ACROBATIC, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Kickflip", "Kickflip Acrobatic", [] {
				uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
				RequestNetControl();
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
					ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 10.71, 5.0, 0.0, 0.0, 1, false, true, true, true, true);
			});

			sub->AddOption<RegularOption>("Small Kickflip", "Small Kickflip Acrobatic", [] {
				uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
				RequestNetControl();
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
					ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 5.0, 5.0, 0.0, 0.0, 1, false, true, true, true, true);
			});

			sub->AddOption<RegularOption>("Big Kickflip", "Big Kickflip Acrobatic", [] {
				uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
				RequestNetControl();
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
					ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 23.4, 7.09, 0.0, 0.0, 1, false, true, true, true, true);
			});

			sub->AddOption<RegularOption>("Double Kickflip", "Double Kickflip Acrobatic", [] {
				uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
				RequestNetControl();
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
					ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 21.43, 20.0, 0.0, 0.0, 1, false, true, true, true, true);
			});

			sub->AddOption<RegularOption>("Frontflip", "Frontflip Acrobatic", [] {
				uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
				RequestNetControl();
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
					ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 10.71, 0.0, -0.4, 0.0, 1, false, true, true, true, true);
			});

			sub->AddOption<RegularOption>("Backflip", "Backflip Acrobatic", [] {
				uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
				RequestNetControl();
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
					ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, 0.0, 0.0, 10.71, 0.0, 0.4, 0.0, 1, false, true, true, true, true);
			});
		});


		static const char* PlateRegions[] = {
			"Blue/White", "Yellow/Black","Yellow/Blue", "Blue/White2", "Blue/White3", "Yankton"
		};



		g_UiManager->AddSubmenu<RegularSubmenu>("INI Options", INISPAWN, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Save Vehicle Ini", "Save Vehicle", [] {



				g_FiberScript->addTask([] {
					GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
					while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
					{
						IsKeyboardActive = true;
						g_UiManager->ResetInput();
						g_FiberScript->Wait(0);
					}
					IsKeyboardActive = false;
					if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
						return 0;

					char* Name = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
					Features::WriteVehicle(Name, PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
				});



			});




			//sub->AddOption<RegularOption>("", "", [] { });

			//namespace fs = std::filesystem;

			//auto sd = skCrypt("APPDATA");
			//std::string ad = getenv(sd);
			//sd.clear();
			//auto pppp = skCrypt(".\\Monop0l\\vehicles\\");
			//fs::directory_iterator dirIt{ ad + pppp.decrypt() };
			//pppp.clear();
			//for (auto&& dirEntry : dirIt)
			//{

			//	auto path = dirEntry.path();

			//	if (path.extension() == ".ini")
			//	{
			//		sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
			//		{
			//			Features::LoadVehicle(path.stem().u8string().c_str());
			//		});


			//	}
			//}

		});



		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle PTFX", VEHICLEPTFX, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Lightning", "", &Features::CarLightning, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Clown Effect", "", &Features::CarClownLoop, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Firework", "", &Features::Carfireworkloop, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Alien 1", "", &Features::Caralien1, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Alien 2", "", &Features::Caralien2, BoolDisplay::OnOff, false, [] {});




			sub->AddOption<BoolOption<bool>>("Electric", "", &Features::Carelectric, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Burial Dirt", "", &Features::moneyeffect15, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Ghost Rider", "", &Features::ghooosoot, BoolDisplay::OnOff, false, [] {});





		});




		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle", VEHICLES, [](RegularSubmenu* sub)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
			{



				sub->AddOption<SubOption>("Color Selector", "Select your Vehicle Color", VEHICLECOLOR);
				sub->AddOption<SubOption>("Vehicle Stats", "Edit your Vehicle Stats", VEHICLESTATS);
				sub->AddOption<SubOption>("Auto Pilot", "Options for the autopilot", AUTPILOT);
				sub->AddOption<SubOption>("Mobile LSC", "Tune your Vehicle", MOBILELSC);
				sub->AddOption<SubOption>("Modded Weapons", "Modded Weapons for your Vehicle", VEHICLEWEAPON);
				sub->AddOption<SubOption>("Vehicle PTFX", "Modded Weapons for your Vehicle", VEHICLEPTFX);
				sub->AddOption<SubOption>("Acrobatics", "Nice Movement Acrobatics", ACROBATIC);
				sub->AddOption<SubOption>("INI Saver/Spawner", "Save your vehicle into an ini file", INISPAWN);
				sub->AddOption<NumberOption<std::int32_t>>("Vehicle Alpha", nullptr, &EntityAlpha, 0, 255, 5, 3, true, "", "", [] {
					ENTITY::SET_ENTITY_ALPHA(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), EntityAlpha, true);
					if (IsKeyPressed(VK_NUMPAD5))
					{
						g_FiberScript->addTask([] {

							EntityAlpha = getInputs();
							if (EntityAlpha > 255)
								EntityAlpha = 255;
							if (EntityAlpha < 0)
								EntityAlpha = 0;
							ENTITY::SET_ENTITY_ALPHA(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), EntityAlpha, true);
						});
					}

				});
				//sub->AddOption<BoolOption<bool>>("Boost Charge", "Hold shift to Speed Horn Boost", &Features::RocketBoost, BoolDisplay::OnOff, false, [] {});
				sub->AddOption<NumberOption<std::int32_t>>("Boost Level", "shift for boost / S for super brake", &Features::boostlevel, 0, 1000, 10, 3, true, "", "", [] { ScriptEventLog("Press shift for forward boost"); ScriptEventLog("Press S for instant brake");
				if (IsKeyPressed(VK_NUMPAD5) || IsKeyPressed(VK_RETURN))
				{
					g_FiberScript->addTask([] {

						Features::boostlevel = getInputs();
						if (Features::boostlevel > 1000)
							Features::boostlevel = 1000;
						if (Features::boostlevel < 0)
							Features::boostlevel = 0;
					});
				}
				});


				sub->AddOption<BoolOption<bool>>("Vehicle Godmode", nullptr, &Features::cargodmodebool, BoolDisplay::OnOff, false, [] {});
				sub->AddOption<BoolOption<bool>>("Instant Stop", "No more Movement of your Vehicle", &Features::zerospeedbool, BoolDisplay::OnOff, false, [] {});
				sub->AddOption<BoolOption<bool>>("Drift Mode", "100% Drift for your Vehicle", &Features::DriftModeBool, BoolDisplay::OnOff, false, [] {});
				sub->AddOption<BoolOption<bool>>("Invisibility", "Makes your car Invisible", &Features::InvisibleCarBool, BoolDisplay::OnOff, false, [] { Features::InvisibleCar(); });
				sub->AddOption<BoolOption<bool>>("Sonic Vehicle", "Your Car = Sonic :=)", &Features::sonicvehicle, BoolDisplay::OnOff, false, [] {});
				sub->AddOption<BoolOption<bool>>("No Gravity", "No Gravity for your Vehicle", &Features::vehiclegravitybool, BoolDisplay::OnOff, false, [] { Features::vehiclegravity(); });
				sub->AddOption<BoolOption<bool>>("Hornboost", "", &Features::hornboostbool, BoolDisplay::OnOff, false, [] {});
				if (Features::hornboostbool == true)
				{
					sub->AddOption<NumberOption<int>>("Hornboost Speed", nullptr, &Features::hornboostspeed, 0, 500, 5, 3, true, "", "", [] {});
				}

				sub->AddOption<ChooseOption<const char*, std::size_t>>("Plate Region Selector", nullptr, &PlateRegions, &Lists::DemoListPos26, false, [] { Vehicle vehicle; vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false); VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, Lists::DemoListPos26); });




				sub->AddOption<BoolOption<bool>>("No more seat falling", "No falling from vehicles again", &Features::seatbeltbool, BoolDisplay::OnOff);

				sub->AddOption<BoolOption<bool>>("Drive on Water", "Drive with your Vehicle on the ocean", &Features::dowbool, BoolDisplay::OnOff, false, [] {});

				/*sub->AddOption<BoolOption<bool>>("Vehicle Rockets", "Weapons For Car", &Features::WeaponRockets, BoolDisplay::OnOff, false, [] { ScriptEventLog("Press NUMPAD+ to shoot rockets"); });*/
				sub->AddOption<BoolOption<bool>>("SpeedoMeter", "Show speed of your Vehicle", &Features::SpeedoBool, BoolDisplay::OnOff, false, [] {});
				sub->AddOption<BoolOption<bool>>("Matrix Plates", "Random generated Matrix Plate", &Features::MatrixPlates, BoolDisplay::OnOff, false, [] {});
				sub->AddOption<BoolOption<bool>>("Stick Vehicle on Ground", "Stick Vehicle to Ground", &Features::StickyBool, BoolDisplay::OnOff, false, [] {});

				sub->AddOption<BoolOption<bool>>("Flying Vehicle", "Fly with your Vehicle!", &Features::FlyingCarBool, BoolDisplay::OnOff, false, [] {});
				sub->AddOption<BoolOption<bool>>("Flying Vehicle 2", "Fly with your Vehicle!", &Features::BetterFlyingCarBool, BoolDisplay::OnOff, false, [] {});
				sub->AddOption<RegularOption>("Fix Vehicle", "Fix's Car", [] { Features::FixCar(); });

				sub->AddOption<BoolOption<bool>>("Fix Loop", "Fix Loop", &Features::FixLoop, BoolDisplay::OnOff, false, [] {});

				sub->AddOption<BoolOption<bool>>("Fix Loop", "Fix Loop", &Features::FixLoop, BoolDisplay::OnOff, false, [] {});


				sub->AddOption<RegularOption>("Max Vehicle", "Upgrades your car to max", [] { Features::maxvehicle(); });
				sub->AddOption<RegularOption>("Open Doors", "Open's All Doors", [] { Features::OpenDoors(); }); \
					sub->AddOption<RegularOption>("Close Doors", "Close All Doors", [] { VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true); });
				sub->AddOption<RegularOption>("Clean Vehicle", "Wash your Vehicle / Clean it", [] {
					GRAPHICS::WASH_DECALS_FROM_VEHICLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 100.0f);
				});
				sub->AddOption<RegularOption>("Delete Vehicle", "Delete your current vehicle", [] {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					deletecar(veh);
				});
				sub->AddOption<RegularOption>("Reset Placement", "Resets Car Placement", [] { Features::flip(); });

				sub->AddOption<RegularOption>("Add Big Ramp", "Add Big Ramp to your Vehicle", [] {

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

				sub->AddOption<RegularOption>("Remove Big Ramp", "Remove Big Ramp to your Vehicle", [] {

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
			else
			{
			sub->AddOption<BreakOption>("Enter an Vehicle to Unlock Vehicle Options!", "Enter an Vehicle to Unlock Vehicle Options!", [] {});
			}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Weapons", VEHICLEWEAPON, [](RegularSubmenu* sub)
		{

			sub->AddOption<BoolOption<bool>>("Vehicle Rockets", "Press + on your Keyboard", &Features::ShootR, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Vehicle Tank Rounds", "Press + on your Keyboard", &Features::ShootTankR, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Vehicle Mini", "Press + on your Keyboard", &Features::ShootMini, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Vehicle RPG", "Press + on your Keyboard", &Features::carRPG, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Vehicle RED Laser", "Press + on your Keyboard", &Features::llcar, BoolDisplay::OnOff, false, [] {});
	
			sub->AddOption<BoolOption<bool>>("Vehicle Green Laser", "Press + on your Keyboard", &Features::ggcar, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Vehicle Plane Rocket", "Press + on your Keyboard", &Features::wwcar, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Vehicle Blazer Cannon", "Press + on your Keyboard", &Features::cccar, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Vehicle Turret Boxville", "Press + on your Keyboard", &Features::ttcar, BoolDisplay::OnOff, false, [] {});


			sub->AddOption<BoolOption<bool>>("Vehicle Flaregun", "Press + on your Keyboard", &Features::ttcarflare, BoolDisplay::OnOff, false, [] {});


			sub->AddOption<BoolOption<bool>>("Vehicle Ruiner Bullet", "Press + on your Keyboard", &Features::qqcar, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Vehicle Molotow Gun", "Press + on your Keyboard", &Features::qqcarxdsa, BoolDisplay::OnOff, false, [] {});

		});
	
		static float Acceleration = { 0.f };
		static float Brake = { 0.f };
		static float Traction = { 0.f };
		static float Deform = { 0.f };
		static float Suspensions = { 0.f };
		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Stats", VEHICLESTATS, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Acceleration", "Makes Car Go Faster", &Acceleration, 0.f, 1000.f, 0.1f, 1, true, "", "", [] { 
				Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0x4C }, Acceleration);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Acceleration = (float)getInputs();
						if (Acceleration > 1000.f)
							Acceleration = 1000.f;
						if (Acceleration < 0.f)
							Acceleration = 0.f;
						Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0x4C }, Acceleration);
					});
				}
			
			
			});
			sub->AddOption<NumberOption<float>>("Brake", "Brake Speed of car", &Brake, 0.f, 1000.f, 0.1f, 1, true, "", "", [] {
				Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0x6C }, Brake);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Brake = (float)getInputs();
						if (Brake > 1000.f)
							Brake = 1000.f;
						if (Brake < 0.f)
							Brake = 0.f;
						Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0x6C }, Brake);
					});
				}
			
			});
			sub->AddOption<NumberOption<float>>("Traction", "Grip To Ground", &Traction, 0.f, 1000.f, 0.1f, 1, true, "", "", [] {
				Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0x90 }, Traction);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Traction = (float)getInputs();
						if (Traction > 1000.f)
							Traction = 1000.f;
						if (Traction < 0.f)
							Traction = 0.f;
						Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0x90 }, Traction);
					});
				}
			
			});
			sub->AddOption<NumberOption<float>>("Deform", "How Deforded You Want Car To Be", &Deform, 0.f, 1000.f, 0.1f, 1, true, "", "", [] {
				Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0xF8 }, Deform); 
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Deform = (float)getInputs();
						if (Deform > 1000.f)
							Deform = 1000.f;
						if (Deform < 0.f)
							Deform = 0.f;
						Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0xF8 }, Deform);
					});
				}
			
			});
			sub->AddOption<NumberOption<float>>("Suspension", "Lowering Highering Car", &Suspensions, 0.f, 1000.f, 0.1f, 1, true, "", "", [] { 
				Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0xBC }, Suspension); 
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Suspensions = (float)getInputs();
						if (Suspensions > 1000.f)
							Suspensions = 1000.f;
						if (Suspensions < 0.f)
							Suspensions = 0.f;
						Memory::set_value<float>({ 0x8, 0xD28, 0x918, 0xBC }, Suspension);
					});
				}
			
			
			});
		});
		
		g_UiManager->AddSubmenu<RegularSubmenu>("Mobile LSC [Beta]", MOBILELSC, [](RegularSubmenu* sub)
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Spoiler:", nullptr, &Spoiler, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPOILER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SPOILER, Spoiler, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Front Bumper:", nullptr, &FBumper, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTBUMPER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTBUMPER, FBumper, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Rear Bumper:", nullptr, &RBumper, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_REARBUMPER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_REARBUMPER, RBumper, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Side Skirt:", nullptr, &SSkirt, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SIDESKIRT), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SIDESKIRT, SSkirt, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Exhaust:", nullptr, &Exhaust, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_EXHAUST), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_EXHAUST, Exhaust, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Grille:", nullptr, &Grille, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_GRILLE), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_GRILLE, Grille, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Chassis:", nullptr, &Chasis, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_CHASSIS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_CHASSIS, Chasis, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Hood:", nullptr, &Hood, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HOOD), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_HOOD, Hood, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Fender:", nullptr, &Fender, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FENDER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_FENDER, Fender, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Right Fender:", nullptr, &RFender, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_RIGHTFENDER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_RIGHTFENDER, RFender, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Roof:", nullptr, &Roof, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ROOF), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ROOF, Roof, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Engine:", nullptr, &Engine, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE, Engine, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Brakes:", nullptr, &Brakes, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_BRAKES), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_BRAKES, Brakes, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Transmission:", nullptr, &Transmission, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRANSMISSION), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRANSMISSION, Transmission, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Horns:", nullptr, &Horns, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HORNS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_HORNS, Horns, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Suspension:", nullptr, &Suspension, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SUSPENSION), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SUSPENSION, Suspension, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Armor:", nullptr, &Armor, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARMOR, Armor, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Turbo:", nullptr, &Turbo, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TURBO), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TURBO, Turbo, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Tire Smoke:", nullptr, &TSmoke, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TIRESMOKE), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TIRESMOKE, TSmoke, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Xenon:", nullptr, &Xenon, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_XENONLIGHTS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_XENONLIGHTS, Xenon, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Wheels:", nullptr, &Wheels, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTWHEELS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTWHEELS, Wheels, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Windows:", nullptr, &Windows, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_WINDOWS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_WINDOWS, Windows, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Plate Holder:", nullptr, &Plateholder, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_PLATEHOLDER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_PLATEHOLDER, Plateholder, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Vanity Plates:", nullptr, &Vanity, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_VANITY_PLATES), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_VANITY_PLATES, Vanity, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Trim:", nullptr, &Trims, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRIM), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRIM, Trims, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Ornaments:", nullptr, &Ornaments, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ORNAMENTS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ORNAMENTS, Ornaments, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Dashboard:", nullptr, &Dashboard, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_DASHBOARD), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_DASHBOARD, Dashboard, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Dial:", nullptr, &Dial, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_DIAL), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_DIAL, Dial, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Door Speaker:", nullptr, &DoorSpeaker, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_DOOR_SPEAKER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_DOOR_SPEAKER, DoorSpeaker, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Seats:", nullptr, &Seats, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SEATS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SEATS, Seats, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Steering Wheel:", nullptr, &SteeringWheel, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_STEERINGWHEEL), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_STEERINGWHEEL, SteeringWheel, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Shifting Levers:", nullptr, &Shifter, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SHIFTER_LEAVERS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SHIFTER_LEAVERS, Shifter, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Plaques:", nullptr, &Plaques, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_PLAQUES), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_PLAQUES, Plaques, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Speakers:", nullptr, &Speakers, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPEAKERS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SPEAKERS, Speakers, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Trunk:", nullptr, &Trunk, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRUNK), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRUNK, Trunk, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Hydraulics:", nullptr, &Hydraulics, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HYDRULICS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_HYDRULICS, Hydraulics, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Engine Block:", nullptr, &EngineBlock, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE_BLOCK), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE_BLOCK, EngineBlock, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Air Filter:", nullptr, &Filter, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_AIR_FILTER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_AIR_FILTER, Filter, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Struts:", nullptr, &Struts, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_STRUTS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_STRUTS, Struts, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Arch Cover:", nullptr, &Arch, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARCH_COVER), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARCH_COVER, Arch, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Aerials:", nullptr, &Aerials, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_AERIALS), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_AERIALS, Aerials, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Trim 2:", nullptr, &TrimTwo, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRIM_2), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRIM_2, TrimTwo, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Tank:", nullptr, &Tank, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TANK), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TANK, Tank, false); });
			sub->AddOption<NumberOption<std::int32_t>>("Livery:", nullptr, &Livery, 0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_LIVERY), 1, 3, true, "", "", [veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_LIVERY, Livery, false); });
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Color", VEHICLECOLOR, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Smooth Rainbow", "Sexy smoothi Rainbow for your Vehicle", &Features::rainbowbool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<NumberOption<int>>("Headlight", "Xenon Light needed!", &Headlight, 0, 12, 1, 3, true, "", "", [] {
				VEHICLE::_SET_HEADLIGHT_COLOR(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), Headlight);
			});

			sub->AddOption<BoolOption<bool>>("Neon Rainbow", nullptr, &Features::NeonBool, BoolDisplay::OnOff, false, [] {});



			sub->AddOption<BoolOption<bool>>("Spammer Rainbow", "This wil kill your Eyes", &Features::RainbowPaintLoop, BoolDisplay::OnOff, false, [] {});
		
			sub->AddOption<RegularOption>("Random Color", "Generates an Random Color one time", [] {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);



				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
			});


			sub->AddOption<NumberOption<std::int32_t>>("Primary R:", nullptr, &Features::primarycolorintr, 0, 255, 1, 3, true, "", "", [] { 
				Features::PrimaryColor();
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::primarycolorintr = getInputs();
						if (Features::primarycolorintr > 255)
							Features::primarycolorintr = 255;
						if (Features::primarycolorintr < 0)
							Features::primarycolorintr = 0;
						Features::PrimaryColor();
					});
				}
			
			});



			sub->AddOption<NumberOption<std::int32_t>>("Primary G:", "Primary Green", &Features::primarycolorintg, 0, 255, 1, 3, true, "", "", [] {
				Features::PrimaryColor();
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::primarycolorintg = getInputs();
						if (Features::primarycolorintg > 255)
							Features::primarycolorintg = 255;
						if (Features::primarycolorintg < 0)
							Features::primarycolorintg = 0;
						Features::PrimaryColor();
					});
				}
			
			});
			sub->AddOption<NumberOption<std::int32_t>>("Primary B:", "Primary Blue", &Features::primarycolorintb, 0, 255, 1, 3, true, "", "", [] { 
				Features::PrimaryColor(); 
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::primarycolorintb = getInputs();
						if (Features::primarycolorintb > 255)
							Features::primarycolorintb = 255;
						if (Features::primarycolorintb < 0)
							Features::primarycolorintb = 0;
						Features::PrimaryColor();
					});
				}
			});
			sub->AddOption<NumberOption<std::int32_t>>("Secondary R:", "Primary Red", &Features::secondarycolorintr, 0, 255, 1, 3, true, "", "", [] { 
				Features::SecondaryColor1(); 
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::secondarycolorintr = getInputs();
						if (Features::secondarycolorintr > 255)
							Features::secondarycolorintr = 255;
						if (Features::secondarycolorintr < 0)
							Features::secondarycolorintr = 0;
						Features::SecondaryColor1();
					});
				}
			
			});
			sub->AddOption<NumberOption<std::int32_t>>("Secondary G:", "Secondary Green", &Features::secondarycolorintg, 0, 255, 1, 3, true, "", "", [] { 
				Features::SecondaryColor1(); 
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::secondarycolorintg = getInputs();
						if (Features::secondarycolorintg > 255)
							Features::secondarycolorintg = 255;
						if (Features::secondarycolorintg < 0)
							Features::secondarycolorintg = 0;
						Features::SecondaryColor1();
					});
				}
			});
			sub->AddOption<NumberOption<std::int32_t>>("Secondary B:", "Secondary Blue", &Features::secondarycolorintb, 0, 255, 1, 3, true, "", "", [] { 
				Features::SecondaryColor1(); 
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::secondarycolorintb = getInputs();
						if (Features::secondarycolorintb > 255)
							Features::secondarycolorintb = 255;
						if (Features::secondarycolorintb < 0)
							Features::secondarycolorintb = 0;
						Features::SecondaryColor1();
					});
				}
			});
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Modded Vehicles", MODDEDVEH, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("6x6 War RC", "", [] {
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


			sub->AddOption<RegularOption>("Speeder Prototype", "", [] {
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


			sub->AddOption<RegularOption>("Scooter", "", [] {
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

			sub->AddOption<RegularOption>("UFO", "", [] {
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

			sub->AddOption<RegularOption>("Flightsquad", "", [] {
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

			sub->AddOption<RegularOption>("Bike Robot", "", [] {
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

			sub->AddOption<RegularOption>("Buggy", "", [] {

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

			sub->AddOption<RegularOption>("Modded T20", "", [] {
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

			sub->AddOption<RegularOption>("Boat - Trailer", "", [] {
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

			sub->AddOption<RegularOption>("Flatbed - T20", "", [] {
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





			sub->AddOption<RegularOption>("Jetsky - Trailer", "", [] {
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




			sub->AddOption<RegularOption>("Ramp Truck", "", [] {
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



			sub->AddOption<RegularOption>("Monster Swat", "", [] {

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

			sub->AddOption<RegularOption>("Buffulo Police", "", [] {

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

			sub->AddOption<RegularOption>("Insurget V2", "", [] {
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



			sub->AddOption<RegularOption>("Super - 1", "", [] {

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



			sub->AddOption<RegularOption>("Super - 2", "", [] {

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

			sub->AddOption<RegularOption>("Muscle - 1", "", [] {

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


			sub->AddOption<RegularOption>("Muscle - 2", "", [] {

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

			sub->AddOption<RegularOption>("Zentorno - Kuruma", "", [] {
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


			sub->AddOption<RegularOption>("Special Helicopter", "", [] {
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

			sub->AddOption<RegularOption>("SlamVan", "", [] {
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

			sub->AddOption<RegularOption>("Flying 5 Seater", "", [] {
				uint Me = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0.;

				Vector3 a; a.x = 0.0, a.y = 0.0, a.z = 0.6;		// seashark 1 - 0.7 worked just hard to get on .. infront and behind wings only way to get on the sharks ...
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;

				Vector3 a1; a1.x = 0.0, a1.y = -4.0, a1.z = 0.6;  // seashark 2
				Vector3 b1; b1.x = 0, b1.y = 0, b1.z = 0;


				Vector3 a2; a2.x = 0.0, a2.y = 0.9, a2.z = -0.45;
				Vector3 b2; b2.x = 0, b2.y = 0, b2.z = 180.0;

				int hash = GAMEPLAY::GET_HASH_KEY("hydra");
				int hash2 = GAMEPLAY::GET_HASH_KEY("seashark");
				int hash3 = GAMEPLAY::GET_HASH_KEY("prop_tool_box_05"); // turn this into something usefull maybe another sea shark ...
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hash3);

				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash3))
				{
					int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);
					int Object = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);


					int Object1;
					OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, true, 1, -1, &Object1, true, false, false);

					int Object2;
					OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, true, 1, -1, &Object2, true, false, false);


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


			sub->AddOption<RegularOption>("Weapon Panto", "", [] {
				uint Handle = PLAYER::PLAYER_PED_ID();
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				//hash2_PANTO
				Vector3 null; null.x = 0.0, null.y = 0.0; null.z = 0.0;
				Vector3 a; a.x = 0.0, a.y = 0.0, a.z = -0.2;//X Coord - Y Coord - Z Coord
				Vector3 b; b.x = 0.0, b.y = 0.0, b.z = 0.0;//Pitch - Roll - Yaw
														   //hash3_MiniGun
				Vector3 null1; null1.x = 0.0, null1.y = 0.0; null1.z = 0.0;
				Vector3 a1; a1.x = -0.60, a1.y = 1.60, a1.z = 0.20;
				Vector3 b1; b1.x = 0.0, b1.y = 0.0, b1.z = 88.0;
				//hash3_MiniGun2
				Vector3 null0; null0.x = 0.0, null0.y = 0.0; null0.z = 0.0;
				Vector3 a0; a0.x = 0.60, a0.y = 1.60, a0.z = 0.20;
				Vector3 b0; b0.x = 0.0, b0.y = 0.0, b0.z = 88.0;
				//hash4_WindScreen _ VANISHED NEEDS FIXING
				Vector3 null2; null2.x = 0.0, null2.y = 0.0; null2.z = 0.0;
				Vector3 a2; a2.x = 0.3, a2.y = 0.41, a2.z = 0.50;
				Vector3 b2; b2.x = -45.3, b2.y = 0.0, b2.z = -179.0;//87
																	//hash4_RLWheel1
				Vector3 null3; null3.x = 0.0, null3.y = 0.0; null3.z = 0.0;
				Vector3 a3; a3.x = -0.90, a3.y = -1.2, a3.z = 0.0; // -0.23
				Vector3 b3; b3.x = 0.0, b3.y = 0.0, b3.z = 86.0;
				//hash4_RFWindScreen 
				Vector3 null4; null4.x = 0.0, null4.y = 0.0; null4.z = 0.0;
				Vector3 a4; a4.x = -0.3, a4.y = 0.41, a4.z = 0.5;
				Vector3 b4; b4.x = -45.3, b4.y = 0.0, b4.z = -179.0;
				//hash4_RRWheel1
				Vector3 null5; null5.x = 0.0, null5.y = 0.0; null5.z = 0.0;
				Vector3 a5; a5.x = 0.92, a5.y = -1.2, a5.z = 0.01;
				Vector3 b5; b5.x = 0.0, b5.y = 0.0, b5.z = -92.0;
				//PUNTO -- FUCK UP NEEDS FIXING 
				Vector3 null6; null6.x = 0, null6.y = 0; null6.z = 0;
				Vector3 a6; a6.x = 0.0, a6.y = 0.0, a6.z = -0.2;
				Vector3 b6; b6.x = 0.0, b6.y = 0.0, b6.z = 0.0;
				//SIDES LEFT
				Vector3 null7; null7.x = 0, null7.y = 0; null7.z = 0;
				Vector3 a7; a7.x = -0.75, a7.y = 0.7, a7.z = -0.3;
				Vector3 b7; b7.x = 90.0, b7.y = 0.0, b7.z = 0.0;
				//SIDES RIGHT
				Vector3 null8; null8.x = 0, null8.y = 0; null8.z = 0;
				Vector3 a8; a8.x = 0.75, a8.y = 0.7, a8.z = -0.3;
				Vector3 b8; b8.x = 90.0, b8.y = 0.0, b8.z = 0.0;

				int hash = GAMEPLAY::GET_HASH_KEY("hotknife");
				int hash2_EMP = GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp");
				int hash3_MiniGun = GAMEPLAY::GET_HASH_KEY("prop_minigun_01");
				int hash4_Wheel = GAMEPLAY::GET_HASH_KEY("prop_wheel_01");
				int hash2 = GAMEPLAY::GET_HASH_KEY("panto");
				int hashWindow = GAMEPLAY::GET_HASH_KEY("prop_ballistic_shield");
				int hashSides = GAMEPLAY::GET_HASH_KEY("prop_cons_plank");




				STREAMING::REQUEST_MODEL(hashWindow);// WINDOW
				STREAMING::REQUEST_MODEL(hash2_EMP); // PANTO
				STREAMING::REQUEST_MODEL(hash3_MiniGun); // GUNS
				STREAMING::REQUEST_MODEL(hash4_Wheel); // back wheels
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(hash2);
				STREAMING::REQUEST_MODEL(hashSides); // SIDE SKIRTS

				if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hashSides) && STREAMING::HAS_MODEL_LOADED(hashWindow) && STREAMING::HAS_MODEL_LOADED(hash2_EMP) && STREAMING::HAS_MODEL_LOADED(hash3_MiniGun) && STREAMING::HAS_MODEL_LOADED(hash2) && STREAMING::HAS_MODEL_LOADED(hash4_Wheel))
				{


					int EMP;
					OBJECT::CREATE_OBJECT(hash2_EMP, null.x, null.y, null.z, true, 1, -1, &EMP, true, false, false);

					int MiniGun;
					OBJECT::CREATE_OBJECT(hash3_MiniGun, null1.x, null1.y, null1.z, true, 1, -1, &MiniGun, true, false, false);

					int MiniGun2;
					OBJECT::CREATE_OBJECT(hash3_MiniGun, null0.x, null0.y, null0.z, true, 1, -1, &MiniGun2, true, false, false);



					int RLWheel1;
					OBJECT::CREATE_OBJECT(hash4_Wheel, null3.x, null3.y, null3.z, true, 1, -1, &RLWheel1, true, false, false);


					int RRWheel1;
					OBJECT::CREATE_OBJECT(hash4_Wheel, null5.x, null5.y, null5.z, true, 1, -1, &RRWheel1, true, false, false);




					int WINDOW_1;
					OBJECT::CREATE_OBJECT(hashWindow, null2.x, null2.y, null2.z, true, 1, -1, &WINDOW_1, true, false, false);


					int WINDOW_2;
					OBJECT::CREATE_OBJECT(hashWindow, null4.x, null4.y, null4.z, true, 1, -1, &WINDOW_2, true, false, false);


					int LeftSide;
					OBJECT::CREATE_OBJECT(hashSides, null7.x, null7.y, null7.z, true, 1, -1, &LeftSide, true, false, false);


					int RightSide;
					OBJECT::CREATE_OBJECT(hashSides, null8.x, null8.y, null8.z, true, 1, -1, &RightSide, true, false, false);


					int Object;
					OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, true, 1, -1, &Object, true, false, false);







					int Vehicle = VEHICLE::CREATE_VEHICLE(hash2, null, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);

					if (ENTITY::DOES_ENTITY_EXIST(EMP) && ENTITY::DOES_ENTITY_EXIST(LeftSide) && ENTITY::DOES_ENTITY_EXIST(RightSide) && ENTITY::DOES_ENTITY_EXIST(MiniGun) && ENTITY::DOES_ENTITY_EXIST(MiniGun2) && ENTITY::DOES_ENTITY_EXIST(WINDOW_1) && ENTITY::DOES_ENTITY_EXIST(RLWheel1) && ENTITY::DOES_ENTITY_EXIST(WINDOW_2) && ENTITY::DOES_ENTITY_EXIST(RRWheel1))
					{
						int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), *g_GameVariables->is_session_started, 0);

						if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
						{
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
							ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, true);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
							ENTITY::SET_ENTITY_VISIBLE(Vehicle, true, true);
							VEHICLE::SET_VEHICLE_MOD_KIT(Object, 0);
							VEHICLE::SET_VEHICLE_WINDOW_TINT(Object, 5);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Object, 0, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Object, 0, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
							VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle, (char*)"sm");
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, (char*)"sm");
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle, 1);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Object, 1);

							ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(EMP, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun, Vehicle, 0, a1.x, a1.y, a1.z, b1.x, b1.y, b1.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(MiniGun2, Vehicle, 0, a0.x, a0.y, a0.z, b0.x, b0.y, b0.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(WINDOW_1, Vehicle, 0, a2.x, a2.y, a2.z, b2.x, b2.y, b2.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RLWheel1, Vehicle, 0, a3.x, a3.y, a3.z, b3.x, b3.y, b3.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(WINDOW_2, Vehicle, 0, a4.x, a4.y, a4.z, b4.x, b4.y, b4.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RRWheel1, Vehicle, 0, a5.x, a5.y, a5.z, b5.x, b5.y, b5.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(LeftSide, Vehicle, 0, a7.x, a7.y, a7.z, b7.x, b7.y, b7.z, 0, 1, 0, 0, 2, 1);
							ENTITY::ATTACH_ENTITY_TO_ENTITY(RightSide, Vehicle, 0, a8.x, a8.y, a8.z, b8.x, b8.y, b8.z, 0, 1, 0, 0, 2, 1);


						}

					}

				}
			});











			sub->AddOption<RegularOption>("Driving Train", "", [] {
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



			sub->AddOption<RegularOption>("Old Car - Mix", "", [] {
				Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				Vector3 null; null.x = 0, null.y = 0; null.z = 0;
				Vector3 a; a.x = 0, a.y = 0, a.z = 0;
				Vector3 b; b.x = 0, b.y = 0, b.z = 0;
				int hash = GAMEPLAY::GET_HASH_KEY("ztype");
				int hash2 = GAMEPLAY::GET_HASH_KEY("btype");
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
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle, (char*)"Solitary");
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Object, (char*)"Solitary");
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle, 0, 0, 0);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle, 0, 0, 0);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, false, 0, 0, 2, true);

					}

				}


			});


		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Spawner", VEHICLESPAWN, [](RegularSubmenu* sub)
		{
			Features::listPresets();


			sub->AddOption<BoolOption<bool>>("Spawn In Vehicle", "Teleport into Vehicle after Teleport", &Features::SpawnInCar, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("Spawn Maxed", "Spawn Vehicle with maxed Tunings", &Features::SpawnMaxed, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<SubOption>("Modded Vehicles", "Select your Vehicle Color", MODDEDVEH);
			
			sub->AddOption<RegularOption>("", "", [] {	});



			sub->AddOption<ChooseOption<const char*, std::size_t>>("Cayo Perico Heist", CayoPerico[Lists::cayopericoint], &CayoPerico, &Lists::cayopericoint, false, [] { spawn_vehicle((char*)CayoPerico[Lists::cayopericoint]); });

			sub->AddOption<ChooseOption<const char*, std::size_t>>("Summer Special DLC", SummerDLC[Lists::SummerSpecialInt], &SummerDLC, &Lists::SummerSpecialInt, false, [] { spawn_vehicle((char*)SummerDLC[Lists::SummerSpecialInt]); });
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Casino Heist DLC", CasinoHeist[Lists::CASINOHEISTINTT], &CasinoHeist, &Lists::CASINOHEISTINTT, false, [] { spawn_vehicle((char*)CasinoHeist[Lists::CASINOHEISTINTT]); });


			sub->AddOption<ChooseOption<const char*, std::size_t>>("Casino DLC", Casino[Lists::CasinoINT], &Casino, &Lists::CasinoINT, false, [] { spawn_vehicle((char*)Casino[Lists::CasinoINT]); });


			sub->AddOption<ChooseOption<const char*, std::size_t>>("ArenaWar DLC", ARENAWAR[Lists::ARENAWARINT], &ARENAWAR, &Lists::ARENAWARINT, false, [] { spawn_vehicle((char*)ARENAWAR[Lists::ARENAWARINT]); });


			sub->AddOption<ChooseOption<const char*, std::size_t>>("AfterHours DLC", AFTERHOURS[Lists::AFTERHOURSINT], &AFTERHOURS, &Lists::AFTERHOURSINT, false, [] { spawn_vehicle((char*)AFTERHOURS[Lists::AFTERHOURSINT]); });


			sub->AddOption<ChooseOption<const char*, std::size_t>>("Doomsday DLC", DOOMSDAY[Lists::DOOMSDAYINT], &DOOMSDAY, &Lists::DOOMSDAYINT, false, [] { spawn_vehicle((char*)DOOMSDAY[Lists::DOOMSDAYINT]); });
			sub->AddOption<ChooseOption<const char*, std::size_t>>("GunRunning DLC", GUNRUNNING[Lists::GunRunningInt], &GUNRUNNING, &Lists::GunRunningInt, false, [] { spawn_vehicle((char*)GUNRUNNING[Lists::GunRunningInt]); });
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Cunning Stunt DLC", CUNNINGSTUNT[Lists::CunningStuntInt], &CUNNINGSTUNT, &Lists::CunningStuntInt, false, [] { spawn_vehicle((char*)CUNNINGSTUNT[Lists::CunningStuntInt]); });
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Import-Export DLC", IMPORTEXPORT[Lists::ImportExportInt], &IMPORTEXPORT, &Lists::ImportExportInt, false, []{ spawn_vehicle((char*)IMPORTEXPORT[Lists::ImportExportInt]); });
			sub->AddOption<RegularOption>("", "", [] {});



			sub->AddOption<ChooseOption<const char*, std::size_t>>("Super", Super1[Lists::DemoListPos1], &Super1, &Lists::DemoListPos1, false, [] { spawn_vehicle((char*)Super1[Lists::DemoListPos1]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Sports", Sports1[Lists::DemoListPos2], &Sports1, &Lists::DemoListPos2, false, [] { spawn_vehicle((char*)Sports1[Lists::DemoListPos2]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Sport Classic", SportsClassics1[Lists::DemoListPos3], &SportsClassics1, &Lists::DemoListPos3, false, [] { spawn_vehicle((char*)SportsClassics1[Lists::DemoListPos3]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Offroad", OffRoad1[Lists::DemoListPos4], &OffRoad1, &Lists::DemoListPos4, false, [] { spawn_vehicle((char*)OffRoad1[Lists::DemoListPos4]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Sedans", Sedans1[Lists::DemoListPos5], &Sedans1, &Lists::DemoListPos5, false, [] { spawn_vehicle((char*)Sedans1[Lists::DemoListPos5]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Coupes", Coupes1[Lists::DemoListPos6], &Coupes1, &Lists::DemoListPos6, false, [] { spawn_vehicle((char*)Coupes1[Lists::DemoListPos6]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Muscle", Muscle1[Lists::DemoListPos7], &Muscle1, &Lists::DemoListPos7, false, [] { spawn_vehicle((char*)Muscle1[Lists::DemoListPos7]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Boats", Boats1[Lists::DemoListPos8], &Boats1, &Lists::DemoListPos8, false, [] { spawn_vehicle((char*)Boats1[Lists::DemoListPos8]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Commercial", Commercial1[Lists::DemoListPos9], &Commercial1, &Lists::DemoListPos9, false, [] { spawn_vehicle((char*)Commercial1[Lists::DemoListPos9]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Compacts", Compacts1[Lists::DemoListPos10], &Compacts1, &Lists::DemoListPos10, false, [] { spawn_vehicle((char*)Compacts1[Lists::DemoListPos10]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Cycles", Cycles1[Lists::DemoListPos11], &Cycles1, &Lists::DemoListPos11, false, [] { spawn_vehicle((char*)Cycles1[Lists::DemoListPos11]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Emergency", Emergency1[Lists::DemoListPos12], &Emergency1, &Lists::DemoListPos12, false, [] { spawn_vehicle((char*)Emergency1[Lists::DemoListPos12]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Helicopters", Helicopters1[Lists::DemoListPos14], &Helicopters1, &Lists::DemoListPos14, false, [] { spawn_vehicle((char*)Helicopters1[Lists::DemoListPos14]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Industrial", Industrial1[Lists::DemoListPos15], &Industrial1, &Lists::DemoListPos15, false, [] { spawn_vehicle((char*)Industrial1[Lists::DemoListPos15]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Military", Military1[Lists::DemoListPos16], &Military1, &Lists::DemoListPos16, false, [] { spawn_vehicle((char*)Military1[Lists::DemoListPos16]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Motorcycles", Motorcycles1[Lists::DemoListPos17], &Motorcycles1, &Lists::DemoListPos17, false, [] { spawn_vehicle((char*)Motorcycles1[Lists::DemoListPos17]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Planes", Planes1[Lists::DemoListPos18], &Planes1, &Lists::DemoListPos18, false, [] { spawn_vehicle((char*)Planes1[Lists::DemoListPos18]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Service", Service1[Lists::DemoListPos19], &Service1, &Lists::DemoListPos19, false, [] { spawn_vehicle((char*)Service1[Lists::DemoListPos19]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("SUV", "Vans For Family ", &SUVs1, &Lists::DemoListPos20, false, [] { spawn_vehicle((char*)SUVs1[Lists::DemoListPos20]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Trailer", SUVs1[Lists::DemoListPos20], &Trailer1, &Lists::DemoListPos21, false, [] { spawn_vehicle((char*)Trailer1[Lists::DemoListPos21]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Trains", Trains1[Lists::DemoListPos22], &Trains1, &Lists::DemoListPos22, false, [] { spawn_vehicle((char*)Trains1[Lists::DemoListPos22]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Utility", Utility1[Lists::DemoListPos23], &Utility1, &Lists::DemoListPos23, false, [] { spawn_vehicle((char*)Utility1[Lists::DemoListPos23]);	});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Vans", Vans1[Lists::DemoListPos24], &Vans1, &Lists::DemoListPos24, false, [] { spawn_vehicle((char*)Vans1[Lists::DemoListPos24]);	});
			sub->AddOption<RegularOption>("Delete Vehicle", "Deletes Current Spawned Car", [] { Features::DeleteVeh(); });
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Bullet Types", SHOOTEFFECT, [](RegularSubmenu* sub)
		{

			sub->AddOption<BoolOption<bool>>("Molotov Gun", "", &Features::MOLOTOV, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("RPG", "", &Features::RPG, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Granade Gun", "", &Features::Grenade, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("FlameThrower Gun", "", &Features::Flare, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Red Laser Gun", "", &Features::leagun, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Cartoon Gun", "", &Features::CLOWNGUN, BoolDisplay::OnOff);






			sub->AddOption<BoolOption<bool>>("Clown Effect", "Clown Effect for your Weapon", &Features::ClownWeaponEffectBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Firework 1 Effect", "Firework Effect 1 for your Weapon", &Features::FireWorkWeaponBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Firework 2 Effect", "Firework Effect 2 for your Weapon", &Features::FireWorkWeaponTwoBool, BoolDisplay::OnOff);



			sub->AddOption<BoolOption<bool>>("Bank Note Effect", "Bank Note Effect for your Weapon", &Features::BankNoteEffectBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Truck Crash Effect", "Truck Crash Effect for your Weapon", &Features::TruckCrashEffectBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Electric Effect", "Electric Effect for your Weapon", &Features::ElectricWeaponEffectBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Alien Effect", "Alien Effect for your Weapon", &Features::AlienWeaponEffectBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Electric Box Effect", "Electric Box Effect for your Weapon", &Features::particel8bool, BoolDisplay::OnOff);




			sub->AddOption<BoolOption<bool>>("Water Splash Effect", "Water Splash Effect for your Weapon", &Features::particel9bool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Blood Effect Effect", "Blood Effect Effect for your Weapon", &Features::particel10bool, BoolDisplay::OnOff);



			sub->AddOption<BoolOption<bool>>("Sniper Effect", "Blood Effect for your Weapon", &Features::particel11bool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Dirt Effect", "Dirt Effect for your Weapon", &Features::particel12bool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Blood 2 Effect", "Blood 2 Effect for your Weapon", &Features::particel13bool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Ped Effect", "Ped Effect for your Weapon", &Features::particel14bool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Camera Effect", "Camera Effect for your Weapon", &Features::particel15bool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Meth Effect", "Meth Effect for your Weapon", &Features::particel16bool, BoolDisplay::OnOff);


		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Knifes", KNIFES, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Dildo Knife", "Spawn Dildo Knife Object in your hand", [] {

				Hash KnifeModel = $("prop_cs_dildo_01");

				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), $("WEAPON_KNIFE"), 1, TRUE);
				WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), $("WEAPON_KNIFE"), 1);
				STREAMING::REQUEST_MODEL(KnifeModel);
				auto knife = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
				auto c = ENTITY::GET_ENTITY_COORDS(knife, 1);
				c.z = c.z;
				//auto dildo = OBJECT::CREATE_OBJECT($("prop_cs_dildo_01"), c.x, c.y, c.z, 1, 1);

				Object object;
				OBJECT::CREATE_OBJECT(KnifeModel, c.x, c.y, c.z, true, 1, -1, &object, true, false, false);
				ENTITY::SET_ENTITY_ALPHA(knife, 0, 0);
				Vector3 v0, v1;
				GAMEPLAY::GET_MODEL_DIMENSIONS(KnifeModel, &v0, &v1);

				ENTITY::ATTACH_ENTITY_TO_ENTITY(object, knife, v1.z, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
			});



			sub->AddOption<RegularOption>("Gun Case Knife", "Spawn Gun Case Knife Object in your hand", [] {

				Hash KnifeModel = $("prop_gun_case_01");

				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), $("WEAPON_KNIFE"), 1, TRUE);
				WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), $("WEAPON_KNIFE"), 1);
				STREAMING::REQUEST_MODEL(KnifeModel);
				auto knife = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
				auto c = ENTITY::GET_ENTITY_COORDS(knife, 1);
				c.z = c.z;
				//auto dildo = OBJECT::CREATE_OBJECT($("prop_cs_dildo_01"), c.x, c.y, c.z, 1, 1);

				float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
				Object object;
				OBJECT::CREATE_OBJECT(KnifeModel, c.x, c.y, c.z, true, 1, -1, &object, true, false, false);
				ENTITY::SET_ENTITY_ALPHA(knife, 0, 0);
				Vector3 v0, v1;
				GAMEPLAY::GET_MODEL_DIMENSIONS(KnifeModel, &v0, &v1);

				ENTITY::ATTACH_ENTITY_TO_ENTITY(object, knife, v1.z, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
			});


		

			sub->AddOption<RegularOption>("Guitar Knife", "Spawn Guitar Object in your hand", [] {

				Hash KnifeModel = $("prop_acc_guitar_01");

				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), $("WEAPON_KNIFE"), 1, TRUE);
				WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), $("WEAPON_KNIFE"), 1);
				STREAMING::REQUEST_MODEL(KnifeModel);
				auto knife = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
				auto c = ENTITY::GET_ENTITY_COORDS(knife, 1);
				c.z = c.z;
				//auto dildo = OBJECT::CREATE_OBJECT($("prop_cs_dildo_01"), c.x, c.y, c.z, 1, 1);

				float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
				Object object;
				OBJECT::CREATE_OBJECT(KnifeModel, c.x, c.y, c.z, true, 1, -1, &object, true, false, false);
				ENTITY::SET_ENTITY_ALPHA(knife, 0, 0);
				Vector3 v0, v1;
				GAMEPLAY::GET_MODEL_DIMENSIONS(KnifeModel, &v0, &v1);

				ENTITY::ATTACH_ENTITY_TO_ENTITY(object, knife, v1.z, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
			});





		});



		g_UiManager->AddSubmenu<RegularSubmenu>("Shoot Vehicle", SHOOTVEHICLE, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Enable Vehicle Shooting", "", &Features::ShootVehicleBool, BoolDisplay::OnOff);


			sub->AddOption<ChooseOption<const char*, std::size_t>>("Summer Special DLC", SummerDLC[Lists::SummerSpecialInt], &SummerDLC, &Lists::SummerSpecialInt, true, [] {
				Features::selectShootVeh = (char*)SummerDLC[Lists::SummerSpecialInt];
			});
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Casino Heist DLC", CasinoHeist[Lists::CASINOHEISTINTT], &CasinoHeist, &Lists::CASINOHEISTINTT, true, [] { Features::selectShootVeh = (char*)CasinoHeist[Lists::CASINOHEISTINTT]; });

			sub->AddOption<ChooseOption<const char*, std::size_t>>("Casino DLC", Casino[Lists::CasinoINT], &Casino, &Lists::CasinoINT, true, [] { Features::selectShootVeh = (char*)Casino[Lists::CasinoINT]; });


			sub->AddOption<ChooseOption<const char*, std::size_t>>("ArenaWar DLC", ARENAWAR[Lists::ARENAWARINT], &ARENAWAR, &Lists::ARENAWARINT, true, [] { Features::selectShootVeh = (char*)ARENAWAR[Lists::ARENAWARINT]; });


			sub->AddOption<ChooseOption<const char*, std::size_t>>("AfterHours DLC", AFTERHOURS[Lists::AFTERHOURSINT], &AFTERHOURS, &Lists::AFTERHOURSINT, true, [] {Features::selectShootVeh = (char*)AFTERHOURS[Lists::AFTERHOURSINT]; });


			sub->AddOption<ChooseOption<const char*, std::size_t>>("Doomsday DLC", DOOMSDAY[Lists::DOOMSDAYINT], &DOOMSDAY, &Lists::DOOMSDAYINT, true, [] {Features::selectShootVeh = (char*)DOOMSDAY[Lists::DOOMSDAYINT]; });
			sub->AddOption<ChooseOption<const char*, std::size_t>>("GunRunning DLC", GUNRUNNING[Lists::GunRunningInt], &GUNRUNNING, &Lists::GunRunningInt, true, [] { Features::selectShootVeh = (char*)GUNRUNNING[Lists::GunRunningInt]; });
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Cunning Stunt DLC", CUNNINGSTUNT[Lists::CunningStuntInt], &CUNNINGSTUNT, &Lists::CunningStuntInt, true, [] { Features::selectShootVeh = (char*)CUNNINGSTUNT[Lists::CunningStuntInt]; });
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Import-Export DLC", IMPORTEXPORT[Lists::ImportExportInt], &IMPORTEXPORT, &Lists::ImportExportInt, true, [] { Features::selectShootVeh = (char*)IMPORTEXPORT[Lists::ImportExportInt]; });

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Weapons", WEAPONS, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Give All Weapons", "Gives ALL WEAPONS", [] {
				for (Hash hash : Weaponss)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
			});
			sub->AddOption<RegularOption>("Give MK1 Weapons", "", [] {
				for (Hash hash : MK1Weapons)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
			});
			sub->AddOption<RegularOption>("Give MK2 Weapons", "", [] {
				for (Hash hash : MK2Weapons)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
			});
			sub->AddOption<RegularOption>("Give All Weapon Addons", "", [] { Hash hash; WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &hash, 1);  Features::BruteForceWeaponAddons(PLAYER::PLAYER_PED_ID(), hash); });



			sub->AddOption<RegularOption>("Remove all Weapons", "", [] {
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

				for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
					WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), Weapons[i]);
				}
			});



			sub->AddOption<SubOption>("Bullet Types", "Many shoots effects for your weapon", SHOOTEFFECT);

			sub->AddOption<SubOption>("Knfies", "Knfies", KNIFES);

			sub->AddOption<SubOption>("Shoot Vehicle", "Shoot Vehicles", SHOOTVEHICLE);
			//sub->AddOption<SubOption>("Weapon Stats", "Weapons Damage ETC", WEAPONSTATS);
			sub->AddOption<BoolOption<bool>>("Infinity Ammo", "NO RUNOUT", &Features::InfiniteAmmoBool, BoolDisplay::OnOff);


			sub->AddOption<BoolOption<bool>>("Drive it Gun", "Shoot to an Vehicle and drive the Vehicle", &Features::DriveItBool, BoolDisplay::OnOff);



			sub->AddOption<BoolOption<bool>>("AirStrike Ammo", "Spawn an Airstrike", &Features::AirStrike, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Firework Ammo", "Shoot Fireworks", &Features::FireworkBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Valkyrie Rocket", "Camera Rocket Launcher", &Features::VALKYIREROCKET, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Shoot Asteroids", "Shoot very big asteroid", &Features::ShootAsteroidBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Money Gun", "Shoot Money", &Features::MoneyGunBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("RP Gun", "Shoot RP", &Features::RPGunBool, BoolDisplay::OnOff);



			sub->AddOption<BoolOption<bool>>("Fire Ammo", "Marvolvo Ammo", &Features::FireShoot, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Water Ammo", "Fire Hidrant Ammo", &Features::WaterShoot, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Explosive Melee", "Granade Ammo", &Features::ExplosiveAmmoFlag, BoolDisplay::OnOff);


			sub->AddOption<BoolOption<bool>>("Explode Ammo", "Granade Ammo", &Features::ExplodeAmmoBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("Explosive Ammo", "Granade Ammo", &Features::ExplosiveAmmoBool, BoolDisplay::OnOff);




			sub->AddOption<BoolOption<bool>>("Rainbow Weapon", "Rainbow your Weapon", &Features::RainbowWeaponsBool, BoolDisplay::OnOff);


			sub->AddOption<BoolOption<bool>>("Delete Gun", "Deletes every Entity you are shooting on", &Features::AimBool, BoolDisplay::OnOff, false, [] {});


			sub->AddOption<BoolOption<bool>>("Teleport Gun", "Teleport Gun", &Features::teleportbool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Object Gun", "Shoot Objects", &Features::ObjectGunBool, BoolDisplay::OnOff, false, [] {});



			sub->AddOption<BoolOption<bool>>("Gravity Gun", "Shoot any Vehicles from the street like you want", &Features::GravityGun, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Aimbot", "Amazing Aim Bot", &Features::AimbotBool, BoolDisplay::OnOff);

			sub->AddOption<BoolOption<bool>>("1 Shoot Kill", "Kill everything with 1 shoot", &Features::DamageBool, BoolDisplay::OnOff, false, [] {	Features::DamageMod();	});

			sub->AddOption<BoolOption<bool>>("No Recoil", "No Weapon Knockback ", &Features::Recoil, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<BoolOption<bool>>("Rapid Fire", "Ammo For Life", &Features::RapidFireBool, BoolDisplay::OnOff, false, [] {});



		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Weapon Stats", WEAPONSTATS, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Damage", "Weapon Damage", &damage, 0.f, 1000.f, 0.1f, 1, true,"","/1000.f", [] { 
				Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_BULLET_DMG }, damage);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						damage = (float)getInputs();
						if (damage > 1000)
							damage = 1000;
						if (damage < 0)
							damage = 0;
						Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_BULLET_DMG }, damage);
					});
				}


				else if (IsKeyPressed(VK_RETURN))
				{
					g_FiberScript->addTask([] {

						damage = (float)getInputs();
						if (damage > 1000)
							damage = 1000;
						if (damage < 0)
							damage = 0;
						Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_BULLET_DMG }, damage);
						});
				}
			});
			sub->AddOption<NumberOption<float>>("Spread", "Spreed Of Bullets", &spread, 0.f, 1000.f, 0.1f, 1, true, "", "", [] { 
				Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_SPREAD }, spread);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						spread = (float)getInputs();
						if (spread > 1000)
							spread = 1000;
						if (spread < 0)
							spread = 0;
						Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_SPREAD }, spread);
					});
				}
			});
			sub->AddOption<NumberOption<float>>("Recoil", "Recoil Time", &recoil, 0.f, 1000.f, 0.1f, 1, true, "", "", [] { 
				Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RECOIL }, recoil);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						recoil = (float)getInputs();
						if (recoil > 1000)
							recoil = 1000;
						if (recoil < 0)
							recoil = 0;
						Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RECOIL }, recoil);
					});
				}
			});
			sub->AddOption<NumberOption<float>>("Range", "Range Of Weapons", &range, 0.f, 1000.f, 0.1f, 1, true, "", "", [] { 
				Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RANGE }, range);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						range = (float)getInputs();
						if (range > 1000)
							range = 1000;
						if (range < 0)
							range = 0;
						Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RANGE }, range);
					});
				}
			});
			sub->AddOption<NumberOption<float>>("Reload", "Realoding Time", &reloadtime, 0.f, 1000.f, 0.1f, 1, true, "", "", [] { 
				Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RELOAD_MULTIPLIER }, reloadtime);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						reloadtime = (float)getInputs();
						if (reloadtime > 1000)
							reloadtime = 1000;
						if (reloadtime < 0)
							reloadtime = 0;
						Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RELOAD_MULTIPLIER }, reloadtime);
					});
				}
			});
			sub->AddOption<NumberOption<float>>("Muzzle Velocity", "Muzzle Size", &muzzlevelocity, 0.f, 1000.f, 0.1f, 1, true, "", "", [] {
				Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_MUZZLE_VELOCITY }, muzzlevelocity); 
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						muzzlevelocity = (float)getInputs();
						if (muzzlevelocity > 1000)
							muzzlevelocity = 1000;
						if (muzzlevelocity < 0)
							muzzlevelocity = 0;
						Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_MUZZLE_VELOCITY }, muzzlevelocity);
					});
				}
			});
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Teleports", TELEPORTSELF, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("IPLs", "Teleportation's EVERYWHERE", IPLs);

			sub->AddOption<RegularOption>("Teleport To Waypoint", "", [] { teleport_to_marker(); });
			sub->AddOption<RegularOption>("Strip Club", "", [] { Vector3 Coords; Coords.x = 126.135f; Coords.y = -1278.583f; Coords.z = 29.270f; TPto(Coords); });
			sub->AddOption<RegularOption>("Police Station", "", [] { Vector3 Coords; Coords.x = 436.491f; Coords.y = -982.172f; Coords.z = 30.699f; TPto(Coords); });
			sub->AddOption<RegularOption>("Burnt FIB", "", [] { Vector3 Coords; Coords.x = 160.868f; Coords.y = -745.831f; Coords.z = 250.063f; TPto(Coords); });
			sub->AddOption<RegularOption>("Pacific Standard Vault", "", [] { Vector3 Coords; Coords.x = 255.851f; Coords.y = 217.030f; Coords.z = 101.683f; TPto(Coords); });
			sub->AddOption<RegularOption>("Lester's House", "", [] { Vector3 Coords; Coords.x = 1273.898f; Coords.y = -1719.304f; Coords.z = 54.771f; TPto(Coords); });
			sub->AddOption<RegularOption>("IAA Office", "", [] { Vector3 Coords; Coords.x = 117.220f; Coords.y = -620.938f; Coords.z = 206.047f; TPto(Coords); });
			sub->AddOption<RegularOption>("Torture Room", "", [] { Vector3 Coords; Coords.x = 147.170f; Coords.y = -2201.804f; Coords.z = 4.688f; TPto(Coords); });


			sub->AddOption<RegularOption>("Hippy Camp", "", [] { Vector3 Coords; Coords.x = 2476.712f; Coords.y = 3789.645f; Coords.z = 41.226f; TPto(Coords); });
			sub->AddOption<RegularOption>("Weed Farm", "", [] { Vector3 Coords; Coords.x = 2208.777f; Coords.y = 5578.235f; Coords.z = 53.735f; TPto(Coords); });
			sub->AddOption<RegularOption>("Casino", "", [] { Vector3 Coords; Coords.x = 925.329f; Coords.y = 46.152f; Coords.z = 80.908f; TPto(Coords); });
			sub->AddOption<RegularOption>("Prison", "", [] { Vector3 Coords; Coords.x = 1679.049f; Coords.y = 2513.711f; Coords.z = 45.565f; TPto(Coords); });
			sub->AddOption<RegularOption>("Mount Chiliad", "", [] { Vector3 Coords; Coords.x = 496.75f; Coords.y = 5591.17f; Coords.z = 795.03f; TPto(Coords); });
			sub->AddOption<RegularOption>("Maze Bank", "", [] { Vector3 Coords; Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f; TPto(Coords); });


			sub->AddOption<RegularOption>("Military Base", "", [] { Vector3 Coords; Coords.x = -2012.8470f; Coords.y = 2956.5270f; Coords.z = 32.8101f; TPto(Coords); });
			sub->AddOption<RegularOption>("Zancudo Tower", "", [] { Vector3 Coords; Coords.x = -2356.0940; Coords.y = 3248.645; Coords.z = 101.4505; TPto(Coords); });
			sub->AddOption<RegularOption>("Mask Shop", "", [] { Vector3 Coords; Coords.x = -1338.16; Coords.y = -1278.11; Coords.z = 4.87; TPto(Coords); });
			sub->AddOption<RegularOption>("LS Customs", "", [] { Vector3 Coords; Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31; TPto(Coords); });
			sub->AddOption<RegularOption>("Ammunation", "", [] { Vector3 Coords; Coords.x = 247.3652; Coords.y = -45.8777; Coords.z = 69.9411; TPto(Coords); });
			sub->AddOption<RegularOption>("Airport", "", [] { Vector3 Coords; Coords.x = -1102.2910f; Coords.y = -2894.5160f; Coords.z = 13.9467f; TPto(Coords); });
			sub->AddOption<RegularOption>("Clothes Store", "", [] { Vector3 Coords; Coords.x = -718.91; Coords.y = -158.16; Coords.z = 37.00; TPto(Coords); });
			sub->AddOption<RegularOption>("Waterfall", "", [] { Vector3 Coords; Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f; TPto(Coords); });
			sub->AddOption<RegularOption>("FIB", "", [] { Vector3 Coords; Coords.x = 135.5220f; Coords.y = -749.0003f; Coords.z = 260.0000f; TPto(Coords); });
			sub->AddOption<RegularOption>("Humane Labs", "", [] { Vector3 Coords; Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f; TPto(Coords); });
			sub->AddOption<RegularOption>("MMI", "", [] { Vector3 Coords; Coords.x = -222.1977; Coords.y = -1185.8500; Coords.z = 23.0294; TPto(Coords); });
			sub->AddOption<RegularOption>("Sandy Shores Airfield", "", [] { Vector3 Coords; Coords.x = 1741.4960f; Coords.y = 3269.2570f; Coords.z = 41.6014f; TPto(Coords); });
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("IPLs", IPLs, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Cayo Perico", "", [] {


				static const char* ipls[] = { "h4_islandx_terrain_01_lod",  "h4_islandx_terrain_01_slod",  "h4_islandx_terrain_02",  "h4_islandx_terrain_02_lod",  "h4_islandx_terrain_02_slod",  "h4_islandx_terrain_03",  "h4_islandx_terrain_03_lod",  "h4_islandx_terrain_04",  "h4_islandx_terrain_04_lod",  "h4_islandx_terrain_04_slod",  "h4_islandx_terrain_05",  "h4_islandx_terrain_05_lod",  "h4_islandx_terrain_05_slod",  "h4_islandx_terrain_06",  "h4_mph4_terrain_01_grass_0",  "h4_mph4_terrain_01_grass_1",  "h4_mph4_terrain_02_grass_0",  "h4_mph4_terrain_02_grass_1",  "h4_mph4_terrain_02_grass_2",  "h4_mph4_terrain_02_grass_3",  "h4_mph4_terrain_04_grass_0",  "h4_mph4_terrain_04_grass_1",  "h4_mph4_terrain_05_grass_0",  "h4_mph4_terrain_06_grass_0", "h4_islandx_terrain_06_lod",  "h4_islandx_terrain_06_slod",  "h4_islandx_terrain_props_05_a",  "h4_islandx_terrain_props_05_a_lod",  "h4_islandx_terrain_props_05_b",  "h4_islandx_terrain_props_05_b_lod",  "h4_islandx_terrain_props_05_c",  "h4_islandx_terrain_props_05_c_lod",  "h4_islandx_terrain_props_05_d",  "h4_islandx_terrain_props_05_d_lod",  "h4_islandx_terrain_props_05_d_slod",  "h4_islandx_terrain_props_05_e",  "h4_islandx_terrain_props_05_e_lod",  "h4_islandx_terrain_props_05_e_slod",  "h4_islandx_terrain_props_05_f",  "h4_islandx_terrain_props_05_f_lod",  "h4_islandx_terrain_props_05_f_slod",  "h4_islandx_terrain_props_06_a",  "h4_islandx_terrain_props_06_a_lod",  "h4_islandx_terrain_props_06_a_slod",  "h4_islandx_terrain_props_06_b",  "h4_islandx_terrain_props_06_b_lod",  "h4_islandx_terrain_props_06_b_slod",  "h4_islandx_terrain_props_06_c",  "h4_islandx_terrain_props_06_c_lod",  "h4_islandx_terrain_props_06_c_slod",  "h4_mph4_terrain_01",  "h4_mph4_terrain_01_long_0",  "h4_mph4_terrain_02",  "h4_mph4_terrain_03",  "h4_mph4_terrain_04",  "h4_mph4_terrain_05",  "h4_mph4_terrain_06",  "h4_mph4_terrain_06_strm_0",  "h4_mph4_terrain_lod",  "h4_mph4_terrain_occ_00",  "h4_mph4_terrain_occ_01",  "h4_mph4_terrain_occ_02",  "h4_mph4_terrain_occ_03",  "h4_mph4_terrain_occ_04",  "h4_mph4_terrain_occ_05",  "h4_mph4_terrain_occ_06",  "h4_mph4_terrain_occ_07",  "h4_mph4_terrain_occ_08",  "h4_mph4_terrain_occ_09",  "h4_boatblockers",  "h4_islandx",  "h4_islandx_disc_strandedshark",  "h4_islandx_disc_strandedshark_lod",  "h4_islandx_disc_strandedwhale",  "h4_islandx_disc_strandedwhale_lod",  "h4_islandx_props",  "h4_islandx_props_lod",  "h4_islandx_sea_mines",  "h4_mph4_island",  "h4_mph4_island_long_0",  "h4_mph4_island_strm_0",  "h4_aa_guns",  "h4_aa_guns_lod",  "h4_beach",  "h4_beach_bar_props",  "h4_beach_lod",  "h4_beach_party",  "h4_beach_party_lod",  "h4_beach_props",  "h4_beach_props_lod",  "h4_beach_props_party",  "h4_beach_props_slod",  "h4_beach_slod",  "h4_islandairstrip",  "h4_islandairstrip_doorsclosed",  "h4_islandairstrip_doorsclosed_lod",  "h4_islandairstrip_doorsopen",  "h4_islandairstrip_doorsopen_lod",  "h4_islandairstrip_hangar_props",  "h4_islandairstrip_hangar_props_lod",  "h4_islandairstrip_hangar_props_slod",  "h4_islandairstrip_lod",  "h4_islandairstrip_props",  "h4_islandairstrip_propsb",  "h4_islandairstrip_propsb_lod",  "h4_islandairstrip_propsb_slod",  "h4_islandairstrip_props_lod",  "h4_islandairstrip_props_slod",  "h4_islandairstrip_slod",  "h4_islandxcanal_props",  "h4_islandxcanal_props_lod",  "h4_islandxcanal_props_slod",  "h4_islandxdock",  "h4_islandxdock_lod",  "h4_islandxdock_props",  "h4_islandxdock_props_2",  "h4_islandxdock_props_2_lod",  "h4_islandxdock_props_2_slod",  "h4_islandxdock_props_lod",  "h4_islandxdock_props_slod",  "h4_islandxdock_slod",  "h4_islandxdock_water_hatch",  "h4_islandxtower",  "h4_islandxtower_lod",  "h4_islandxtower_slod",  "h4_islandxtower_veg",  "h4_islandxtower_veg_lod",  "h4_islandxtower_veg_slod",  "h4_islandx_barrack_hatch",  "h4_islandx_barrack_props",  "h4_islandx_barrack_props_lod",  "h4_islandx_barrack_props_slod",  "h4_islandx_checkpoint",  "h4_islandx_checkpoint_lod",  "h4_islandx_checkpoint_props",  "h4_islandx_checkpoint_props_lod",  "h4_islandx_checkpoint_props_slod",  "h4_islandx_maindock",  "h4_islandx_maindock_lod",  "h4_islandx_maindock_props",  "h4_islandx_maindock_props_2",  "h4_islandx_maindock_props_2_lod",  "h4_islandx_maindock_props_2_slod",  "h4_islandx_maindock_props_lod",  "h4_islandx_maindock_props_slod",  "h4_islandx_maindock_slod",  "h4_islandx_mansion",  "h4_islandx_mansion_b",  "h4_islandx_mansion_b_lod",  "h4_islandx_mansion_b_side_fence",  "h4_islandx_mansion_b_slod",  "h4_islandx_mansion_entrance_fence",  "h4_islandx_mansion_guardfence",  "h4_islandx_mansion_lights",  "h4_islandx_mansion_lockup_01",  "h4_islandx_mansion_lockup_01_lod",  "h4_islandx_mansion_lockup_02",  "h4_islandx_mansion_lockup_02_lod",  "h4_islandx_mansion_lockup_03",  "h4_islandx_mansion_lockup_03_lod",  "h4_islandx_mansion_lod",  "h4_islandx_mansion_office",  "h4_islandx_mansion_office_lod",  "h4_islandx_mansion_props",  "h4_islandx_mansion_props_lod",  "h4_islandx_mansion_props_slod",  "h4_islandx_mansion_slod",  "h4_islandx_mansion_vault",  "h4_islandx_mansion_vault_lod",  "h4_island_padlock_props",  "h4_mansion_gate_broken",  "h4_mansion_gate_closed",  "h4_mansion_remains_cage",  "h4_mph4_airstrip",  "h4_mph4_airstrip_interior_0_airstrip_hanger",  "h4_mph4_beach",  "h4_mph4_dock",  "h4_mph4_island_lod",  "h4_mph4_island_ne_placement",  "h4_mph4_island_nw_placement",  "h4_mph4_island_se_placement",  "h4_mph4_island_sw_placement",  "h4_mph4_mansion",  "h4_mph4_mansion_b",  "h4_mph4_mansion_b_strm_0",  "h4_mph4_mansion_strm_0",  "h4_mph4_wtowers",  "h4_ne_ipl_00",  "h4_ne_ipl_00_lod",  "h4_ne_ipl_00_slod",  "h4_ne_ipl_01",  "h4_ne_ipl_01_lod",  "h4_ne_ipl_01_slod",  "h4_ne_ipl_02",  "h4_ne_ipl_02_lod",  "h4_ne_ipl_02_slod",  "h4_ne_ipl_03",  "h4_ne_ipl_03_lod",  "h4_ne_ipl_03_slod",  "h4_ne_ipl_04",  "h4_ne_ipl_04_lod",  "h4_ne_ipl_04_slod",  "h4_ne_ipl_05",  "h4_ne_ipl_05_lod",  "h4_ne_ipl_05_slod",  "h4_ne_ipl_06",  "h4_ne_ipl_06_lod",  "h4_ne_ipl_06_slod",  "h4_ne_ipl_07",  "h4_ne_ipl_07_lod",  "h4_ne_ipl_07_slod",  "h4_ne_ipl_08",  "h4_ne_ipl_08_lod",  "h4_ne_ipl_08_slod",  "h4_ne_ipl_09",  "h4_ne_ipl_09_lod",  "h4_ne_ipl_09_slod",  "h4_nw_ipl_00",  "h4_nw_ipl_00_lod",  "h4_nw_ipl_00_slod",  "h4_nw_ipl_01",  "h4_nw_ipl_01_lod",  "h4_nw_ipl_01_slod",  "h4_nw_ipl_02",  "h4_nw_ipl_02_lod",  "h4_nw_ipl_02_slod",  "h4_nw_ipl_03",  "h4_nw_ipl_03_lod",  "h4_nw_ipl_03_slod",  "h4_nw_ipl_04",  "h4_nw_ipl_04_lod",  "h4_nw_ipl_04_slod",  "h4_nw_ipl_05",  "h4_nw_ipl_05_lod",  "h4_nw_ipl_05_slod",  "h4_nw_ipl_06",  "h4_nw_ipl_06_lod",  "h4_nw_ipl_06_slod",  "h4_nw_ipl_07",  "h4_nw_ipl_07_lod",  "h4_nw_ipl_07_slod",  "h4_nw_ipl_08",  "h4_nw_ipl_08_lod",  "h4_nw_ipl_08_slod",  "h4_nw_ipl_09",  "h4_nw_ipl_09_lod",  "h4_nw_ipl_09_slod",  "h4_se_ipl_00",  "h4_se_ipl_00_lod",  "h4_se_ipl_00_slod",  "h4_se_ipl_01",  "h4_se_ipl_01_lod",  "h4_se_ipl_01_slod",  "h4_se_ipl_02",  "h4_se_ipl_02_lod",  "h4_se_ipl_02_slod",  "h4_se_ipl_03",  "h4_se_ipl_03_lod",  "h4_se_ipl_03_slod",  "h4_se_ipl_04",  "h4_se_ipl_04_lod",  "h4_se_ipl_04_slod",  "h4_se_ipl_05",  "h4_se_ipl_05_lod",  "h4_se_ipl_05_slod",  "h4_se_ipl_06",  "h4_se_ipl_06_lod",  "h4_se_ipl_06_slod",  "h4_se_ipl_07",  "h4_se_ipl_07_lod",  "h4_se_ipl_07_slod",  "h4_se_ipl_08",  "h4_se_ipl_08_lod",  "h4_se_ipl_08_slod",  "h4_se_ipl_09",  "h4_se_ipl_09_lod",  "h4_se_ipl_09_slod",  "h4_sw_ipl_00",  "h4_sw_ipl_00_lod",  "h4_sw_ipl_00_slod",  "h4_sw_ipl_01",  "h4_sw_ipl_01_lod",  "h4_sw_ipl_01_slod",  "h4_sw_ipl_02",  "h4_sw_ipl_02_lod",  "h4_sw_ipl_02_slod",  "h4_sw_ipl_03",  "h4_sw_ipl_03_lod",  "h4_sw_ipl_03_slod",  "h4_sw_ipl_04",  "h4_sw_ipl_04_lod",  "h4_sw_ipl_04_slod",  "h4_sw_ipl_05",  "h4_sw_ipl_05_lod",  "h4_sw_ipl_05_slod",  "h4_sw_ipl_06",  "h4_sw_ipl_06_lod",  "h4_sw_ipl_06_slod",  "h4_sw_ipl_07",  "h4_sw_ipl_07_lod",  "h4_sw_ipl_07_slod",  "h4_sw_ipl_08",  "h4_sw_ipl_08_lod",  "h4_sw_ipl_08_slod",  "h4_sw_ipl_09",  "h4_sw_ipl_09_lod",  "h4_sw_ipl_09_slod",  "h4_underwater_gate_closed",  "h4_islandx_placement_01",  "h4_islandx_placement_02",  "h4_islandx_placement_03",  "h4_islandx_placement_04",  "h4_islandx_placement_05",  "h4_islandx_placement_06",  "h4_islandx_placement_07",  "h4_islandx_placement_08",  "h4_islandx_placement_09",  "h4_islandx_placement_10",  "h4_mph4_island_placement" };

				for (auto ipl : ipls)
				{
					STREAMING::REQUEST_IPL((char*)ipl);
				}

				Entity entity = PLAYER::PLAYER_PED_ID();

				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, 4892.064, -4923.567, 3.500, 0, 0, 1);



						Vector3 Coords; Coords.x = 4892.064; Coords.y = -4923.567; Coords.z = 3.500; TPto(Coords);

			});

			sub->AddOption<RegularOption>("North Yankton", "", [] { Features::Yankton(); });
			sub->AddOption<RegularOption>("Yacht", "", [] { Features::Yacht(); });
			sub->AddOption<RegularOption>("Aircraft Carrier", "", [] { Features::Carrier(); });
			sub->AddOption<RegularOption>("Sunken Cargo Ship", "", [] { Features::SunkenShip(); });
			sub->AddOption<RegularOption>("Destroyed Hospital", "", [] { Features::Hospital(); });
			sub->AddOption<RegularOption>("ONeil Farm", "", [] { Features::Farm(); });
			sub->AddOption<RegularOption>("Life Invader", "", [] { Features::Invader(); });
			sub->AddOption<RegularOption>("Jewelry Store", "", [] { Features::Jewelry(); });
			sub->AddOption<RegularOption>("Morgue", "", [] { Features::Morgue(); });
		});
		static const char* Weathers[] = {
	"Clear", "Clearing","Snowlight", "Thunder", "Blizzard", "Overcast", "Foggy", "Smog", "Clouds"
		};
		g_UiManager->AddSubmenu<RegularSubmenu>("Map Mods", MAPMOD, [](RegularSubmenu* sub)
		{


			sub->AddOption<RegularOption>("Maze Bank Small Ramp", "", [] {

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



				DC_Message((char*)"Spawned Maze Bank Small Ramp!");


			});

			sub->AddOption<RegularOption>("Maze Bank Roof Ramp", "", [] {
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


				DC_Message((char*)"Spawned Maze Bank Roof Ramp!");


			});

			sub->AddOption<RegularOption>("Beach Ramp", "", [] {
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



				DC_Message((char*)"Spawned Beach Ramp!");


			});

			sub->AddOption<RegularOption>("Mount Chilliad Ramp", "", [] {
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


				DC_Message((char*)"Spawned Mound Chilliad Ramp!");


			});

			sub->AddOption<RegularOption>("Airport Mini Ramp", "", [] {
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


				DC_Message((char*)"Spawned Airport Mini Ramp!");


			});

			sub->AddOption<RegularOption>("Airport Gate Ramp", "", [] {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1046, -2538, 20, 1, 0, 0, 1);
				Features::PlaceObjectByHash(2475986526, -1098.36, -2631.17, 19, 0, -0, 152.671, -1, 5);
				Features::PlaceObjectByHash(2475986526, -1100.26, -2634.64, 21.1976, 16.2002, 0.192059, 150.427, -1, 5);
				Features::PlaceObjectByHash(2475986526, -1102.26, -2638.02, 25.01, 26.7003, 0.178675, 149.261, -1, 5);
				Features::PlaceObjectByHash(2475986526, -1103.96, -2640.91, 29.04, 28.3717, -0, 146.82, -1, 5);
				Features::PlaceObjectByHash(1952396163, -1119.61, -2670.96, -5.125, 0, -0, 150.514, -1, 5);
				Features::PlaceObjectByHash(1952396163, -1119.61, -2670.96, -5.125, 0, -0, 150.401, -1, 5);
				Features::PlaceObjectByHash(3137065507, -1044.69, -2530.08, 20.4011, 94.8962, 4.26887e-007, 147.716, -1, 5);



				DC_Message((char*)"Spawned Airport Gate Ramp!");


			});

			sub->AddOption<RegularOption>("MazeBank - Ufo Tower", "", [] {
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

				DC_Message((char*)"Spawned MazeBank - Ufo Tower!");


			});

			//sub->AddOption<RegularOption>("Exploit Quad Ramp", "", [] {
			//	ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -74.94243f, -818.63446f, 326.174347f, 1, 0, 0, 1);

			//	Features::PlaceObjectByHash(3522933110, -81.3886, -814.648, 325.169, 0, -0, 180, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -81.7456, -809.064, 324.799, 0.500021, 2.66804, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -86.1333, -802.279, 321.92, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -89.7406, -796.701, 316.539, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -93.601, -790.725, 310.777, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -97.4741, -784.73, 304.997, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -101.373, -778.696, 299.179, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -105.233, -772.72, 293.417, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -109.106, -766.725, 287.637, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -112.954, -760.769, 281.894, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -116.827, -754.773, 276.113, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -120.687, -748.798, 270.352, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -124.518, -742.868, 264.636, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -128.358, -736.925, 258.909, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -132.22, -730.949, 253.151, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -136.081, -724.974, 247.394, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -139.943, -718.998, 241.636, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -143.826, -712.99, 235.846, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -147.667, -707.047, 230.12, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -151.508, -701.104, 224.394, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -155.369, -695.128, 218.636, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -159.252, -689.12, 212.846, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -163.072, -683.209, 207.152, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -166.976, -677.168, 201.331, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -170.838, -671.193, 195.573, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -174.7, -665.217, 189.815, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -178.583, -659.209, 184.026, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -182.444, -653.233, 178.268, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -186.327, -647.225, 172.479, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -190.189, -641.249, 166.721, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -194.03, -635.306, 160.994, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -197.871, -629.363, 155.268, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -201.711, -623.42, 149.542, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -205.552, -617.477, 143.815, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -209.393, -611.534, 138.089, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -213.255, -605.559, 132.331, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -217.095, -599.616, 126.605, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -220.957, -593.64, 120.847, -38.9999, -1.45141, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -222.245, -591.648, 118.928, -33.8999, 1.02453, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -223.349, -589.94, 117.561, -29.31, 1.79292, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -224.58, -588.036, 116.288, -26.25, 5.12264, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -225.869, -586.04, 115.116, -24.7199, -1.10991, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -227.127, -584.095, 114.05, -21.6599, 1.8783, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -228.615, -581.794, 112.961, -19.6199, 1.02453, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -230.201, -579.341, 111.92, -17.0699, -0, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -232.121, -576.369, 110.833, -12.9899, 4.26887, 32.8808, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -234.105, -573.302, 109.991, -9.9299, -2.98821, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -236.628, -569.396, 109.329, -7.3799, -4.26887, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -239.81, -564.475, 108.721, -4.3199, 1.28066, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -241.76, -561.459, 108.549, -0.7499, -1.12058, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -244.04, -557.932, 108.494, 2.82011, -2.77476, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -246.372, -554.326, 108.705, 5.8801, -2.77476, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -248.668, -550.777, 109.14, 10.4701, 8.96462, 32.8806, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -251.664, -546.138, 110.313, 13.5301, 1.15259, 32.8806, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -254.537, -541.694, 111.791, 16.5901, 4.26887, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -256.28, -538.999, 112.748, 19.6501, -1.19528, 32.8807, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -65.9078, -814.752, 326.106, 19.89, 4.26887, -53.8105, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -58.6541, -809.444, 327.336, -4.08004, -2.13443, -53.8103, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -52.4476, -804.909, 323.715, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -47.2332, -801.09, 317.168, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -42.0187, -797.272, 310.621, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -36.8326, -793.474, 304.109, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -31.5898, -789.635, 297.526, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -26.4037, -785.838, 291.014, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -21.1893, -782.019, 284.467, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -15.9748, -778.201, 277.919, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -10.7604, -774.383, 271.372, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -5.57426, -770.585, 264.86, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -0.359839, -766.767, 258.313, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 4.82623, -762.969, 251.799, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 10.0123, -759.171, 245.285, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 15.2268, -755.353, 238.735, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 20.4412, -751.535, 232.184, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 25.6273, -747.737, 225.67, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 30.8135, -743.939, 219.155, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 36.0279, -740.121, 212.605, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 41.214, -736.323, 206.091, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 46.4285, -732.505, 199.54, -45.3899, 2.56132, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 48.4122, -731.052, 197.049, -41.8198, 1.62217, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 49.5549, -730.218, 195.782, -38.2499, 3.24434, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 51.171, -729.035, 194.203, -36.2098, 2.39057, -53.81, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 52.8966, -727.773, 192.637, -33.1499, -6.83019, -53.8101, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 54.586, -726.537, 191.27, -30.0898, 8.70849, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 56.5413, -725.105, 189.866, -25.4998, 7.59859, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 58.8359, -723.425, 188.509, -22.4398, 4.26887, -53.81, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 60.738, -722.033, 187.536, -18.3599, 1.10991, -53.81, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 63.1509, -720.268, 186.544, -15.8098, 5.03727, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 65.131, -718.821, 185.849, -12.7498, 5.07995, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 67.1384, -717.352, 185.286, -9.17981, 4.78113, -53.81, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 69.2894, -715.776, 184.855, -4.5898, 4.18349, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 71.7831, -713.952, 184.607, 0.000193536, 4.16213, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 74.0832, -712.268, 184.607, 3.06019, 3.7566, -53.81, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 76.0175, -710.853, 184.736, 8.1602, 4.35424, -53.81, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 77.7752, -709.567, 185.048, 13.2602, 5.50684, -53.81, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 79.6997, -708.158, 185.61, 17.3402, 3.7566, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 81.3947, -706.918, 186.266, 21.9302, 4.26887, -53.81, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 83.3036, -705.52, 187.219, 26.0102, 9.39151, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 85.6244, -703.821, 188.622, 29.0702, 1.96368, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 87.3526, -702.556, 189.812, 33.1501, 2.90283, -53.8098, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 89.2107, -701.196, 191.316, 37.2301, 4.86651, -53.8098, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 90.8492, -699.998, 192.859, 41.82, -2.56132, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 92.6236, -698.701, 194.826, 46.41, 8.2816, -53.8099, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 94.2096, -697.539, 196.89, 52.0199, 6.57406, -53.8098, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 95.6251, -696.503, 199.137, 56.61, 9.22075, -53.8097, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 96.9799, -695.512, 201.683, 61.7098, 8.53774, -53.8097, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 98.1658, -694.646, 204.413, 65.7899, 5.03726, -53.8096, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -69.0186, -829.452, 324.775, 0, -0, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -65.276, -836.288, 321.491, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -62.2554, -842.061, 315, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -59.2515, -847.802, 308.544, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -56.2313, -853.574, 302.053, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -53.1945, -859.378, 295.526, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -50.2071, -865.088, 289.106, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -47.2032, -870.829, 282.65, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -44.1829, -876.602, 276.159, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -41.1626, -882.374, 269.667, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -38.1751, -888.084, 263.247, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -35.1713, -893.825, 256.791, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -32.1674, -899.566, 250.335, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -29.1635, -905.307, 243.879, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -26.1432, -911.079, 237.388, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -23.1393, -916.821, 230.932, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -20.119, -922.593, 224.44, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -17.1152, -928.334, 217.985, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -14.1112, -934.075, 211.529, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -11.1235, -939.785, 205.108, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -8.13589, -945.495, 198.687, -44.8796, 3.24434, -152.398, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -5.28891, -951.101, 192.102, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -2.35757, -956.552, 185.364, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 0.589775, -962.033, 178.59, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 3.5211, -967.483, 171.852, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 9.3998, -978.414, 158.339, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 6.46847, -972.964, 165.077, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 12.3311, -983.865, 151.601, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 15.2944, -989.375, 144.789, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 21.1569, -1000.28, 131.313, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 18.2417, -994.856, 138.014, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 24.0722, -1005.7, 124.612, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 27.0355, -1011.21, 117.801, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 29.9828, -1016.69, 111.026, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 35.8294, -1027.56, 97.5867, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 37.2241, -1030.15, 94.4555, -44.3698, -1.70754, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 38.7475, -1032.99, 91.3086, -39.7798, -4.26887, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 39.7483, -1034.85, 89.5491, -36.7197, 3.4151, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 40.9818, -1037.14, 87.6062, -33.6597, -2.21981, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 42.1248, -1039.27, 85.999, -30.0898, -1.96368, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 32.9141, -1022.14, 104.288, -47.4298, -1.79292, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 43.3132, -1041.47, 84.5449, -26.5197, -1.79293, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 44.7115, -1044.08, 83.0715, -23.4597, -2.39056, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 45.9496, -1046.38, 81.937, -20.3997, -2.47594, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 47.0815, -1048.48, 81.0483, -17.3397, -2.09174, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 48.302, -1050.75, 80.2436, -14.7897, -8.96462, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 50.0647, -1054.03, 79.2608, -13.2597, -2.77476, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 52.0238, -1057.67, 78.2861, -11.7297, -1.45141, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 53.7395, -1060.86, 77.5341, -9.17973, -1.1099, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 55.7265, -1064.56, 76.8558, -6.11973, -6.61674, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 57.3746, -1067.62, 76.4825, -3.56972, -9.60496, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 59.3125, -1071.23, 76.2272, 0.000276446, -9.05818, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 61.112, -1074.58, 76.2272, 4.08028, -8.00412, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 62.529, -1077.21, 76.4405, 7.65027, -7.04364, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 64.0779, -1080.1, 76.8796, 10.7103, -1.28066, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 65.9388, -1083.55, 77.623, 14.2802, -1.70755, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 67.4076, -1086.29, 78.4126, 17.3403, -1.57948, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, 68.7639, -1088.81, 79.3066, 21.4202, 1.36604, -151.734, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -86.0915, -825.576, 324.775, 0, -0, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -99.1939, -833.684, 315.911, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -105.248, -837.511, 310.056, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -93.1729, -829.876, 321.734, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -111.268, -841.319, 304.233, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -123.245, -848.891, 292.651, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -147.333, -864.12, 269.359, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -141.278, -860.292, 275.213, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -135.256, -856.485, 281.036, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -129.266, -852.699, 286.828, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -117.224, -845.084, 298.474, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -165.367, -875.521, 251.921, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -213.415, -905.895, 205.464, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -207.426, -902.108, 211.255, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -201.403, -898.301, 217.078, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -195.414, -894.515, 222.87, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -183.434, -886.942, 234.452, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -177.445, -883.156, 240.244, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -171.422, -879.348, 246.067, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -159.378, -871.734, 257.713, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -153.355, -867.927, 263.536, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -189.424, -890.728, 228.661, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -231.449, -917.296, 188.027, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -225.46, -913.509, 193.818, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -219.47, -909.723, 199.609, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -237.439, -921.082, 182.235, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -284.806, -951.016, 167.673, 28.5601, -7.5132, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -289.048, -953.697, 170.578, 34.1701, -3.41509, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -290.727, -954.757, 171.926, 37.23, 3.41509, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -286.998, -952.399, 169.084, 31.62, -1.36604, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -282.375, -949.481, 166.27, 26.0101, 3.50047, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -280.014, -947.991, 165.174, 21.4201, -6.83019, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -277.4, -946.336, 164.178, 17.8501, -3.15896, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -270.266, -941.827, 162.896, 4.59013, -1.79292, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -266.683, -939.562, 163.103, -6.11989, -1.38738, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -259.328, -934.913, 165.339, -17.8499, -4.69576, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -253.478, -931.22, 168.474, -26.01, -4.18349, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -248.103, -927.823, 172.247, -33.66, -5.97642, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -243.429, -924.868, 176.444, -39.27, -2.30519, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -256.593, -933.187, 166.676, -22.4399, -5.97641, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -262.183, -936.72, 164.252, -14.2799, -3.20165, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -268.321, -940.597, 162.896, 0.000125527, -1.95033, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -272.668, -943.344, 163.123, 8.67012, -2.86014, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -275.091, -944.877, 163.561, 12.7501, -5.1226, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -249.757, -928.867, 170.944, -31.11, -6.0617, 122.286, -1, 7);
			//	Features::PlaceObjectByHash(3681122061, -251.566, -930.012, 169.653, -27.54, -3.58585, 122.286, -1, 7);


			//	DC_Message((char*)"Spawned Exploit Quad Ramp!");


			//});

			sub->AddOption<RegularOption>("Exploit Fort", "", [] {
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -2731, 3259, 32, 1, 0, 0, 1);
				Features::PlaceObjectByHash(3213433054, -2661.22, 3209.43, 32.7118, 0, -0, -120.437, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2657.86, 3207.56, 32.7118, 0, 0, 59.6808, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2659.52, 3212.33, 32.7118, 0, -0, -120.437, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2656.2, 3210.41, 32.7118, 0, 0, 59.6808, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2654.54, 3213.26, 32.7118, 0, 0, 59.6808, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2657.84, 3215.18, 32.7118, 0, -0, -120.437, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2615.14, 3183, 32.8118, 0, -0, -120.45, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2611.82, 3181.02, 32.8118, 0, 0, 58.529, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2613.47, 3185.85, 32.8118, 0, -0, -120.45, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2610.11, 3183.91, 32.8118, 0, 0, 59.589, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2611.79, 3188.7, 32.8118, 0, -0, -120.45, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2608.46, 3186.71, 32.8118, 0, 0, 58.529, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2550.83, 3162.65, 32.7702, 0, -0, -117.989, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2547.01, 3160.66, 34.9496, 11.66, -2.56132e-006, -118.95, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2476.76, 3120.72, 32.7718, 0, -0, -119.612, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2473.51, 3118.83, 34.5672, 8.47412, -0.0223369, -120.965, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2442.43, 3105.7, 35.6224, -7.42001, -5.12265e-006, 150.074, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2443.67, 3101.83, 35.8732, -11.66, 3.84198e-006, 59.738, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2438.8, 3099, 36.0155, -11.66, -6.40331e-006, 59.7379, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2434.05, 3096.22, 36.6871, -22.26, -1.45141e-005, 59.7379, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2446.85, 3098.2, 35.6088, -7.42, 3.20165e-006, -31.8463, -1, 8);
				Features::PlaceObjectByHash(2402097066, -2448.77, 3097.65, 35.4732, 0, -0, -120.616, -1, 8);
				Features::PlaceObjectByHash(2402097066, -2442.95, 3108.08, 35.4832, 0, -0, -117.436, -1, 8);
				Features::PlaceObjectByHash(2402097066, -2442.95, 3108.08, 35.4832, 0, -0, -117.436, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2389.55, 3069.11, 36.5952, 179.801, -3.76861e-006, -117.806, -1, 8);
				Features::PlaceObjectByHash(1982829832, -2363.33, 3056.01, 31.8257, 0, -0, -119.219, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2389.55, 3069.11, 36.5952, 179.801, -3.76861e-006, -117.806, -1, 8);
				Features::PlaceObjectByHash(2609922146, -2358.79, 3060.59, 31.8217, 0, -0, -119.371, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2325.93, 3034.99, 33.3214, 19.8, 3.41509e-006, -120.09, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2321.78, 3032.58, 36.3899, 25.7399, -8.62311e-005, -120.09, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2317.79, 3030.29, 39.6222, 25.0799, -6.23256e-005, -120.09, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2313.74, 3027.94, 42.9228, 25.7399, -8.62311e-005, -120.09, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2309.83, 3025.69, 46.2289, 27.06, -8.2816e-005, -120.09, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2306.07, 3023.49, 49.5919, 29.0399, -0.000116113, -120.09, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2283.14, 3009.97, 44.7284, 14.12, -2.04906e-005, 60.0397, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2287.5, 3012.47, 46.9591, 13.6, 0.680011, 60.0397, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2302.26, 3021.28, 53.174, 29.6999, -0.000100745, -120.09, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2292.06, 3015.11, 49.2546, 13.6, 1.53679e-005, 60.0397, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2298.56, 3019.12, 56.7472, 30.36, -8.79386e-005, -120.09, -1, 8);
				Features::PlaceObjectByHash(2052512905, -2294.52, 3015.08, 58.6366, 82.6616, 0.00430302, -31.2919, -1, 8);
				Features::PlaceObjectByHash(2052512905, -2293.13, 3017.4, 58.6822, 80.9428, 0.00560716, 149.187, -1, 8);
				Features::PlaceObjectByHash(2787492567, -2293.66, 3016.58, 31.8318, -90, 0.0833042, 109.919, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2202.78, 2963.39, 32.8003, 0, -0, -120.04, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2199.53, 2961.53, 34.17, -40.5599, -2.56132e-006, 59.8803, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2137.1, 2904.97, 32.8327, 16.8, -1.10991e-005, -141.061, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2132.27, 2897.94, 34.4465, 16.8, -14, -141.061, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2127.12, 2890.88, 36.4432, 17.92, -29.68, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2119.98, 2885.33, 38.8379, 17.92, -29.68, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2113.02, 2880, 41.2705, 17.92, -29.68, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2085.18, 2857.71, 49.9177, 19.04, -43.12, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2078.1, 2852.44, 51.662, 19.0399, -50.4001, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2092.05, 2863.54, 48.2285, 17.92, -34.16, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2098.91, 2869.18, 46.2053, 17.92, -29.68, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2105.97, 2874.59, 43.7379, 17.92, -29.68, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2070.42, 2847.69, 53.5814, 19.0399, -50.4001, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2062.85, 2843.01, 55.4739, 19.0399, -50.4001, -136.581, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2055.32, 2838.69, 56.5097, 17.7868, -43.8868, -131.905, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2047.61, 2834.88, 58.9097, 26.1867, -43.8868, -131.905, -1, 8);
				Features::PlaceObjectByHash(3681122061, -2039.74, 2832.2, 62.2769, 38.5067, -45.5668, -131.905, -1, 8);
				Features::PlaceObjectByHash(3681122061, -1996.98, 2830.2, 48.384, 0.202822, -14.4337, -105.503, -1, 8);
				Features::PlaceObjectByHash(3681122061, -1996.42, 2832.89, 59.0601, -179.433, 12.3451, 76.9258, -1, 8);
				Features::PlaceObjectByHash(3213433054, -1951.86, 2849.63, 34.5146, -47.5199, -7.59859e-005, 59.6261, -1, 8);
				Features::PlaceObjectByHash(3213433054, -1950.16, 2852.52, 34.5146, -47.5199, -7.59859e-005, 59.6261, -1, 8);
				Features::PlaceObjectByHash(3213433054, -1953.57, 2854.49, 32.8004, 0, -0, -120.091, -1, 8);
				Features::PlaceObjectByHash(3213433054, -1955.25, 2851.59, 32.8004, 0, -0, -120.091, -1, 8);
				Features::PlaceObjectByHash(4111834409, -1960.72, 2857.38, 31.7305, 0, -0, -118.505, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2144, 2967.21, 36.0606, 9.35852, -0.00134085, 59.8371, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2139.63, 2964.67, 33.9985, 5.84852, -0.0013321, 59.8371, -1, 8);
				Features::PlaceObjectByHash(4109455646, -2135.45, 2962.3, 32.4604, 0, 0, 60.4792, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2193.23, 2995.21, 35.0684, 11.6996, -0.00262322, -119.238, -1, 8);
				Features::PlaceObjectByHash(2975320548, -2197.74, 2997.74, 32.8074, 15.2099, 2.04906e-005, -119.328, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2246.82, 3026.19, 33.0318, 0.0331696, 0.0056356, 58.6423, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2256.38, 3032.02, 35.4343, 6.5707, 0.0279573, 58.7685, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2265.19, 3037.37, 38.408, 10.1262, 0.0254109, 58.7585, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2273.45, 3042.38, 40.214, 8.95404, -0.00182451, 58.7729, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2281.36, 3047.19, 42.7382, 8.89319, 0.151422, 58.8279, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2289.41, 3052.05, 46.2871, 13.2, 0.000150264, 58.7642, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2397.86, 3114.2, 32.8449, 0, 0, 60.2049, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2402.38, 3116.77, 34.7648, 0, 0, 60.2049, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2394.65, 3118.07, 32.5452, 0, 0, 56.6241, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2397.73, 3120.09, 34.1452, 2.04, -1.38738e-006, 56.6241, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2401.78, 3122.77, 36.6227, 8.16, 1.28066e-006, 56.6239, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2405.48, 3125.2, 39.5571, 14.28, 1.02453e-005, 56.6239, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2409.12, 3127.6, 43.2064, 20.4, -2.39057e-005, 56.6239, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2412.29, 3129.71, 46.9494, 24.4781, -1.44125, 56.2632, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2415.18, 3131.49, 51.529, 38.3931, -3.70399, 55.299, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2416.96, 3132.28, 56.2986, 54.0331, -3.70398, 53.2589, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2417.37, 3132.16, 61.6124, 73.753, -3.70394, 53.2588, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2416.48, 3131.04, 66.996, 90.9129, -3.70395, 53.2587, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2414.88, 3129.5, 70.998, 104.113, -3.70383, 50.6186, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2412.46, 3127.2, 74.61, 116.653, -3.70392, 50.6185, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2409.58, 3124.71, 77.6119, 121.273, -3.70395, 50.6185, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2406.75, 3122.18, 80.0586, 127.213, -3.70391, 50.6184, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2403.38, 3119.23, 82.2502, 135.793, -3.70396, 50.6185, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2369.71, 3092.81, 68.2807, -146.327, -3.7039, 50.6183, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2367.45, 3091.4, 63.3347, -134.447, -3.70392, 50.6182, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2366, 3090.66, 58.0814, -123.887, -3.7039, 50.6182, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2365.38, 3090.57, 53.1623, -112.007, -3.70391, 50.6182, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2365.62, 3091.18, 48.0172, -99.4666, -3.70393, 50.6181, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2366.77, 3092.54, 43.04, -86.2661, -3.70399, 50.6181, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2368.73, 3094.52, 38.5669, -74.386, -3.70392, 50.6181, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2371.25, 3096.8, 35.0692, -59.206, -3.70384, 55.2379, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2375.18, 3099.61, 32.3997, -42.0459, -3.70387, 57.2179, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2395.69, 3112.77, 84.6355, 152.292, -3.70389, 50.6184, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2391.54, 3109.37, 84.6603, 162.192, -3.70393, 50.6184, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2387.13, 3105.84, 83.6595, 172.752, -3.70391, 50.6184, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2382.97, 3102.56, 81.8101, -179.988, -3.70391, 50.6184, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2372.52, 3094.76, 72.6855, -154.907, -3.70391, 50.6183, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2379.11, 3099.59, 79.371, -172.728, -3.70391, 50.6183, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2375.46, 3096.85, 76.1692, -162.168, -3.70388, 50.6182, -1, 8);
				Features::PlaceObjectByHash(2475986526, -2399.8, 3116.19, 83.7512, 143.712, -3.70387, 50.6184, -1, 8);
				Features::PlaceObjectByHash(3213433054, -2510.73, 3180.4, 32.8111, 0, 0, 59.4291, -1, 8);
				Features::PlaceObjectByHash(209943352, -2302.92, 3059.95, 50.2208, 76.8397, -0.679965, -120.716, -1, 8);
				Features::PlaceObjectByHash(209943352, -2298.84, 3057.5, 48.7042, 71.3997, -0.679954, -120.716, -1, 8);
				Features::PlaceObjectByHash(209943352, -2290.6, 3052.58, 47.3498, 84.3198, -0.679946, -120.716, -1, 8);
				Features::PlaceObjectByHash(209943352, -2290.6, 3052.58, 47.3498, 84.3198, -0.679946, -120.716, -1, 8);
				Features::PlaceObjectByHash(209943352, -2294.73, 3055.05, 47.6692, 76.8398, -0.680059, -120.716, -1, 8);
				Features::PlaceObjectByHash(209943352, -2533.2, 3193.91, 37.3948, 0, -0, -120.716, -1, 8);
				Features::PlaceObjectByHash(209943352, -2533.2, 3193.91, 37.3948, 0, -0, -120.716, -1, 8);
				Features::PlaceObjectByHash(209943352, -2425.58, 3091.36, 36.493, 0, -0, -120.716, -1, 8);
				Features::PlaceObjectByHash(209943352, -2425.58, 3091.36, 36.493, 0, -0, -120.716, -1, 8);
				Features::PlaceObjectByHash(209943352, -2293.7, 3012.65, 55.3685, -89.7587, -0.659716, -30.2946, -1, 8);
				Features::PlaceObjectByHash(209943352, -2293.7, 3012.65, 55.3685, -89.7587, -0.659716, -30.2946, -1, 8);



				DC_Message((char*)"Spawned Exploit Fort!");


			});


			sub->AddOption<RegularOption>("Halfpipe", "", [] {
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

				DC_Message((char*)"Spawned Half Pipe");


			});

			sub->AddOption<RegularOption>("Airport Loop Ramp", "", [] {
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


				DC_Message((char*)"Spawned Airport Loop Ramp");


			});

			sub->AddOption<RegularOption>("Airport Ramp", "", [] {
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



				DC_Message((char*)"Spawned Mega Ramp");


			});





			});




			g_UiManager->AddSubmenu<RegularSubmenu>("Weather", WEATHER, [](RegularSubmenu* sub)
			{


				//sub->AddOption<SubOption>("Modded Map Addons", "Modded Objects", MAPMOD);
				sub->AddOption<BoolOption<bool>>("Zero Gravity Mode", "No more gravity", &Features::GravityBool, BoolDisplay::OnOff, false, [] {	Features::Gravity();	});
				sub->AddOption<BoolOption<bool>>("Lobby Time Spammer", "Spawm the time in lobby", &Features::TimeSpamBool, BoolDisplay::OnOff, false, [] {});



				sub->AddOption<BoolOption<bool>>("Disable all lights", "Blackout Mode (no light)", &Features::AsteroidShowerBool, BoolDisplay::OnOff, true, [] {});


				//sub->AddOption<NumberOption<std::int32_t>>("Lobby Time:", nullptr, &Features::TimeHour, 0, 23, 1, 1, true, "", "", [] { Features::SetLobbyTime(Features::TimeHour, 0, 0); });
				//sub->AddOption<RegularOption>("Sync Time with System Time", "Your system time = GTA time", [] { Features::IrlTime(); });
		


				sub->AddOption<ChooseOption<const char*, std::size_t>>("Local Weather", "Changes your local weather", &Weathers, &Lists::DemoListPos27, false, [] { GAMEPLAY::SET_OVERRIDE_WEATHER((char*)Weathers[Lists::DemoListPos27]); });
				sub->AddOption<ChooseOption<std::string, std::size_t>>("Lobby Weather", "Changes Weather for all players", &WeatherTypes, &WeatherTypePos, false, [] { Features::SetWeather(WeatherTypePos); });





			sub->AddOption<BoolOption<bool>>("Crazy Chaos Mode", "Complete Chaos in the session", &Features::ChaosModeBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<NumberOption<std::int32_t>>("Wave Intensity:", "Changes intensity of all waves", &Features::WaveIntensityValue, 0, 5000, 10, 3, true, "", "", [] { 
				Features::SetWaveIntensity(); 
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::WaveIntensityValue = getInputs();
						if (Features::WaveIntensityValue > 5000)
							Features::WaveIntensityValue = 5000;
						if (Features::WaveIntensityValue < 0)
							Features::WaveIntensityValue = 0;
						Features::SetWaveIntensity();
					});
				}
			});
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Protections", PROTECTIONS, [](RegularSubmenu* sub)
		{



			sub->AddOption<BoolOption<bool>>("Anti AFK Kick", "", &Features::AFKNo, BoolDisplay::OnOff, false, []	{});
			sub->AddOption<BoolOption<bool>>("Money Drop Protection", "", &Features::AntiMoneyDrop, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Secure Account Information", "Fake Level, Money, BankMoney, KD, ...", &Features::SpoofLevelBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Extrem Kick Protections", "", &protex1, BoolDisplay::OnOff, false, [] {		});
			sub->AddOption<BoolOption<bool>>("Notify On Block", nullptr, &Features::EventNotif, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Crash 1 Protection", nullptr, &Features::NetworKIDCrashBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Crash 2 Protection", nullptr, &Features::ModelCrashBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Attachment Protection", nullptr, &Features::AttachmentBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Clone Protection", "", &Features::CloneProtectionBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Send To Mission Protection", "", &protex6, BoolDisplay::OnOff, false, [] {	 });
			sub->AddOption<BoolOption<bool>>("Bounty Protection", "", &protex11, BoolDisplay::OnOff, false, [] { });
			sub->AddOption<BoolOption<bool>>("Teleport Protection", "", &protex7, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Sound Spam Protection", "", &protex8, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Time Protection", "", &Features::GAME_CLOCK_EVENT, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Fire Protection", "", &Features::FIRE_EVENT, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Freeze Protection", "", &Features::NETWORK_CLEAR_PED_TASKS_EVENT, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Wanted Remove Protection", "", &protex12, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Camera Spin Protection", "", &protex17, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Weapon Remove Protection", "", &Features::REMOVE_WEAPON_EVENT, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("CEO Protection", "", &protex2, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("CEO Ban Protection", "", &protex3, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Remote OTR Protection", "", &protex4, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Transaction Error Protection", "", &protex9, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Explosion Protection", "", &Features::EXPLOSION_EVENT, BoolDisplay::OnOff, false, [] { 	 });
			sub->AddOption<BoolOption<bool>>("Weather Protection", "", &Features::GAME_WEATHER_EVENT, BoolDisplay::OnOff, false, [] {});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Money", MONEYRECOVERY, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Vehicle Stealth Tutorial", "View this Tut, to see how it works", [] {
				system("explorer https://youtu.be/2qMHrmIe4tk");
			});


			sub->AddOption<RegularOption>("Spawn Vehicle", "Spawn Vehicle for selling", [] {

				Vector3 Coords;
				Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31;

				int Handle = PLAYER::PLAYER_PED_ID();
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
				{
					ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
				}
				else
				{
					ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
				}

			spawn_vehicle("WASHINGTON");

			});

			sub->AddOption<BoolOption<bool>>("Enable Vehicle Stealth", "Start Vehicle Stealth Function", &Features::VehStealthBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<RegularOption>("", "", [] {});


			sub->AddOption<BoolOption<bool>>("Enable Stealth Loop", "Add Money to your Account", &Features::StealthBool, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<NumberOption<std::int32_t>>("Money Amount", "´Set amount of Money", &Features::StealthAmount, 1, 15000000, 10000, 3, true, "", "", [] {});

			sub->AddOption<RegularOption>("", "", [] {});


			sub->AddOption<BoolOption<bool>>("2 Billion Fake Loop", "Add MOUCH Temp Money to your Account", &Features::FakeLoopBool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<RegularOption>("", "", [] {});

			sub->AddOption<RegularOption>("Add Singleplayer Money", "", [] {
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
			});

		});




		g_UiManager->AddSubmenu<RegularSubmenu>("Level", LEVELRECOVERY, [](RegularSubmenu* sub)
		{

			sub->AddOption<NumberOption<std::int32_t>>("RP Correction", "Set Level with RP Correction", &Features::levelrp, 0, 8000, 1, 3, false, "", "", [] {
				Features::SetRank(Features::levelrp); ScriptEventLog("Join a new session!");
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::levelrp = getInputs();
						if (Features::levelrp > 8000)
							Features::levelrp = 8000;
						if (Features::levelrp < 0)
							Features::levelrp = 0;
						Features::SetRank(Features::levelrp);
					});
				}
			});

			sub->AddOption<NumberOption<std::int32_t>>("Instant Level", "Set Level with Instant Level", &Features::levelrp, 0, 8000, 1, 3, false, "", "", [] {
				STATS::STAT_SET_INT($("MP0_CHAR_XP_FM"), Features::Levels[(Features::levelrp - 1)], 1);
				STATS::STAT_SET_INT($("MP1_CHAR_XP_FM"), Features::Levels[(Features::levelrp - 1)], 1);
				STATS::STAT_SET_INT($("MP2_CHAR_XP_FM"), Features::Levels[(Features::levelrp - 1)], 1);
				if (IsKeyPressed(VK_NUMPAD5))
				{
					g_FiberScript->addTask([] {

						Features::levelrp = getInputs();
						if (Features::levelrp > 8000)
							Features::levelrp = 8000;
						if (Features::levelrp < 0)
							Features::levelrp = 0;
						STATS::STAT_SET_INT($("MP0_CHAR_XP_FM"), Features::Levels[(Features::levelrp - 1)], 1);
						STATS::STAT_SET_INT($("MP1_CHAR_XP_FM"), Features::Levels[(Features::levelrp - 1)], 1);
						STATS::STAT_SET_INT($("MP2_CHAR_XP_FM"), Features::Levels[(Features::levelrp - 1)], 1);
					});
				}
			});

			sub->AddOption<RegularOption>("", "", [] {});



			sub->AddOption<RegularOption>("RP Loop Location", "Start looping of stars", []
			{
				Vector3 Coords;
				Coords.x = 869.664978f; Coords.y = 5657.907715f; Coords.z = 677.523743f;
				teleport_to_coords(PLAYER::PLAYER_PED_ID(), Coords);
				GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY((char*)"scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
			});
			sub->AddOption<RegularOption>("Start RP Loop", "Start looping of stars", []
			{
				Features::RPLooperBool = true;
			});
			sub->AddOption<RegularOption>("Stop RP Loop", "Stop looping of stars", []
			{
				Features::RPLooperBool = false;
				Features::RPLooperBool = false;
				Memory::set_value<int>({ 0x08, 0x10C8, 0x868 }, 0);
			});


		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Recovery", RECOVERY, [](RegularSubmenu* sub)
		{

			sub->AddOption<SubOption>("Money Options", "Options to add Money", MONEYRECOVERY);
			sub->AddOption<SubOption>("RP Options", "Options to imrpove your Level", LEVELRECOVERY);
			sub->AddOption<SubOption>("Unlocks", "UNLOCK STUFF", UNLOCKS);
			sub->AddOption<SubOption>("Stats Editor", "Tune Stuff", STATSEDIT);
			sub->AddOption<SubOption>("Money Transfer", "Tune Stuff", TUNABLES);
			sub->AddOption<SubOption>("Chat Commands", "Chat Commands for Player", CHATCOMMANDS);

			

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Stats", STATSEDIT, [](RegularSubmenu* sub)
		{

			sub->AddOption<NumberOption<int>>("Total Job Earned Money", "Set Value of Money you have earned in jobs", &MoneyEarnJobs, 0, 99999, 100, 3, false, "", "", [] {
				
				STATS::STAT_SET_INT($("MPPLY_TOTAL_EVC"), MoneyEarnJobs, 1);
			});



			sub->AddOption<NumberOption<int>>("Total Earned Money", "Set Value of Money you have earn", &MoneyTotalEarn, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_TOTAL_EVC"), MoneyTotalEarn, 1);
			});




			sub->AddOption<NumberOption<int>>("Report Strength", "Set Value of Report Strength", &Report, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_REPORT_STRENGTH"), Report, 1);
			});


			sub->AddOption<NumberOption<int>>("Kills", "Set Value of Kills", &kills, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_KILLS_PLAYERS"), kills, 1);
			});

			sub->AddOption<NumberOption<int>>("Deaths", "Set Value of Deaths", &deaths, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_DEATHS_PLAYER"), deaths, 1);
			});


			sub->AddOption<NumberOption<int>>("Commend Strength", "Set Value of Commend Strength", &commend, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_COMMEND_STRENGTH"), commend, 1);
			});



			sub->AddOption<NumberOption<int>>("Friendly Stuff", "Set Value of Friendly Stuff", &friendly, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_FRIENDLY"), friendly, 1);
			});



			sub->AddOption<NumberOption<int>>("Helpfull Stuff", "Set Value of Helpfull Stuff", &helpful, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_HELPFUL"), helpful, 1);
			});


			sub->AddOption<NumberOption<int>>("Griefing Stuff", "Set Value of Griefing Stuff", &griefing, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_GRIEFING"), griefing, 1);
			});


			sub->AddOption<NumberOption<int>>("VC Hate", "Set Value of VC Hate", &vchate, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_VC_HATE"), vchate, 1);
			});

			sub->AddOption<NumberOption<int>>("Gameplay Exploits", "Set Value of Gameplay Exploits", &gameplayexploit, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_GAME_EXPLOITS"), gameplayexploit, 1);
			});


			sub->AddOption<NumberOption<int>>("Won Races", "Set Value of Won Races", &wonraces, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("AWD_RACES_WON"), wonraces, 1);
				STATS::STAT_SET_INT($("AWD_FM_GTA_RACES_WON"), wonraces, 1);
			});


			sub->AddOption<NumberOption<int>>("Armwrestling Wins", "Set Value of Armwrestling Wins", &armwins, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("AWD_NO_ARMWRESTLING_WINS"), armwins, 1);
			});

			sub->AddOption<NumberOption<int>>("Deathmatch Wins", "Set Value of Deathmatch Wins", &dmwins, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("AWD_FM_DM_WINS"), dmwins, 1);
				STATS::STAT_SET_INT($("AWD_FM_DM_WINS"), dmwins, 1);
				STATS::STAT_SET_INT($("AWD_FM_TDM_WINS"), dmwins, 1);
			});

			sub->AddOption<NumberOption<int>>("Deathmatch Losses", "Set Value of Deathmatch Losses", &dmloos, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_TOTAL_DEATHMATCH_LOST"), dmloos, 1);
			});

			sub->AddOption<NumberOption<int>>("Deathmatch Kills", "Set Value of Deathmatch Kills", &dmkills, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("AWD_FM_DM_TOTALKILLS"), dmkills, 1);
			});

			sub->AddOption<NumberOption<int>>("Deathmatch Deaths", "Set Value of Deathmatch Deaths", &dmdeath, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("MPPLY_DM_TOTAL_DEATHS"), dmdeath, 1);
			});

			sub->AddOption<NumberOption<int>>("Golf Wins", "Set Value of Golf Wins", &golfwin, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("AWD_FM_GOLF_WON"), golfwin, 1);
			});
			sub->AddOption<NumberOption<int>>("Tennis Wins", "Set Value of Tennis Wins", &tenniswin, 0, 99999, 100, 3, false, "", "", [] {

				STATS::STAT_SET_INT($("AWD_FM_TENNIS_WON"), tenniswin, 1);
				STATS::STAT_SET_INT($("MPPLY_TENNIS_MATCHES_WON"), tenniswin, 1);
			});


		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Transfer", TUNABLES, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<int>>("Amount of Transfer", "Set Amount for Changing", &transferamount, 0, 99999999, 10000, 3, false, "", "", [] {});

			sub->AddOption<RegularOption>("Bank -> Wallet", "Transfer Money from Bank to Wallet", []
			{
				int iVar0;
				STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_MP_CHAR"), &iVar0, 1);
				UNK3::_NETWORK_TRANSFER_BANK_TO_WALLET(iVar0, transferamount);
				UNK3::_NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED();
			});

			sub->AddOption<RegularOption>("Wallet -> Bank", "Transfer Money from Bank to Wallet", []
			{
				int32_t character;
				STATS::STAT_GET_INT($("MPPLY_LAST_MP_CHAR"), &character, 1);

				UNK3::_NETWORK_TRANSFER_WALLET_TO_BANK(character, transferamount);
				UNK3::_NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED();
			});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Unlocks", UNLOCKS, [](RegularSubmenu* sub)
		{			
			sub->AddOption<RegularOption>("~g~Unlock All", "", [] { Features::UnlockAll(); });
			sub->AddOption<RegularOption>("", "", [] {});

			sub->AddOption<RegularOption>("Unlock Tattoos", "", [] { Features::UnlockTattoos(); });
			sub->AddOption<RegularOption>("Unlock Rims", "", [] { Features::UnlockRims(); });
			sub->AddOption<RegularOption>("Unlock Vehicles", "", [] { Features::UnlockVehicles(); });
			sub->AddOption<RegularOption>("Unlock Achievements", "", [] { Features::UnlockAchievements(); });


			sub->AddOption<RegularOption>("Unlock Hairstyles", "", [] { Features::UnlockHairstyles(); });
			sub->AddOption<RegularOption>("Unlock Weapons", "", [] { Features::UnlockWeapons(); });
			sub->AddOption<RegularOption>("Unlock Clothes", "", [] { Features::UnlockClothes(); });
			sub->AddOption<RegularOption>("SecuroServ Office Cash", "", [] { Features::OfficeMoney(); });
			sub->AddOption<RegularOption>("SecuroServ Office Statue", "", [] { Features::OfficeStatue(); });
			sub->AddOption<RegularOption>("Max Snacks", "", [] { Features::UnlockSnacks(); });



			sub->AddOption<RegularOption>("Unlock Exlusive-Thirts", "", [] {

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




			});
			sub->AddOption<RegularOption>("Unlock Hairstyles", "", [] {

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



			});



			sub->AddOption<RegularOption>("Max Arena Skill", "", []
			{
				globalHandle(2540384).At(1795).As<int>() = 1;
			});

			sub->AddOption<RegularOption>("Max LSC-Mods", "", []
			{

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


			});

			sub->AddOption<RegularOption>("Unlock Heists", "", [] {

				STATS::STAT_SET_INT($("MP0_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
				STATS::STAT_SET_INT($("MP0_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);
				STATS::STAT_SET_INT($("MP1_CHAR_FM_VEHICLE_1_UNLCK"), -1, 1);
				STATS::STAT_SET_INT($("MP1_CHAR_FM_VEHICLE_2_UNLCK"), -1, 1);

			});


			sub->AddOption<RegularOption>("Clear Badsport", "", [] {


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


			});

			sub->AddOption<RegularOption>("Max Snacks", "", []
			{

				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 99999999, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 99999999, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 99999999, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 99999999, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 99999999, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_BOURGE_BOUGHT"), 99999999, 0);


			});

			sub->AddOption<RegularOption>("Biker Club Cutter", "", []
			{
				STATS::STAT_SET_INT($("LIFETIME_BIKER_BUY_COMPLET"), 1200, 1);
				STATS::STAT_SET_INT($("LIFETIME_BIKER_BUY_COMPLET"), 1200, 1);
				STATS::STAT_SET_INT($("LIFETIME_BIKER_BUY_UNDERTA"), 1200, 1);
				STATS::STAT_SET_INT($("LIFETIME_BIKER_SELL_COMPLET"), 1200, 1);
				STATS::STAT_SET_INT($("LIFETIME_BIKER_SELL_UNDERTA"), 1200, 1);
				STATS::STAT_SET_INT($("LIFETIME_BKR_SELL_EARNINGS0"), 1200, 1);

			});


			sub->AddOption<RegularOption>("Unlock Office Money", "", []
			{

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
			});



				sub->AddOption<RegularOption>("2 Billion Snacks", "", []
			{

				STATS::STAT_SET_INT($("MP0_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
				STATS::STAT_SET_INT($("MP0_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
				STATS::STAT_SET_INT($("MP0_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
				STATS::STAT_SET_INT($("MP0_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
				STATS::STAT_SET_INT($("MP0_CIGARETTES_BOUGHT"), 2000000000, 1);

			});
				sub->AddOption<RegularOption>("2 Billion Armor", "", []
				{
				STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
				STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
				STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
				STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
				STATS::STAT_SET_INT($("MP0_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);


			});
				sub->AddOption<RegularOption>("2 Billion Fireworks", "", []
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


			});



				sub->AddOption<RegularOption>("Set Max Skill", "", []
				{

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



				});
			
				sub->AddOption<RegularOption>("Weapon Skins", "", []
				{

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

				});
		

				sub->AddOption<RegularOption>("Unlock LSC", "", []
				{

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



				});
	

				sub->AddOption<RegularOption>("All Camosand Parachutes", "", []
				{


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


		
				}); 

				sub->AddOption<RegularOption>("Unlock All Chrome Skins", "", []
				{

					STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_CAPTURES"), 25, 1);
					STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_DROPOFF_CAP_PACKAGES"), 100, 1);
					STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_KILL_CARRIER_CAPTURE"), 100, 1);
					STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEISTS"), 50, 1);
					STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FINISH_HEIST_SETUP_JOB"), 50, 1);
					STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_NIGHTVISION_KILLS, 100"), 1, 1);
					STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_WIN_LAST_TEAM_STANDINGS"), 50, 1);
					STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, 1);


				});
			
				sub->AddOption<RegularOption>("Unlock Vehicle Mods(LSC)", "", []
				{

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

				});

				
				sub->AddOption<RegularOption>("Unlock All Heist' Trophies", "", []
				{

					STATS::STAT_SET_INT($("MPPLY_HEIST_ACH_TRACKER"), -1, 1);
					STATS::STAT_SET_INT($("MPPLY_HEIST_ACH_TRACKER"), -1, 1);

	

				});
				
					sub->AddOption<RegularOption>("Enable Roosevelt in Phone", "", []
				{

					STATS::STAT_SET_INT($("MPPLY_VEHICLE_ID_ADMIN_WEB"), 117401876, 1);
				
				});

					sub->AddOption<RegularOption>("Purchase All Weapons", "", []
					{

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

			
			});

		});



		g_UiManager->AddSubmenu<RegularSubmenu>("Demo_sub", SubmenuTest, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("RegularOption_demo", "A regular option.", []
			{
				g_Logger->Info("You pressed the test option");
			});

			static bool testBool1{};
			sub->AddOption<BoolOption<bool>>("BoolOnOff_demo", nullptr, &testBool1, BoolDisplay::OnOff);
			static bool testBool2{};
			sub->AddOption<BoolOption<bool>>("BoolYesNo_demo", nullptr, &testBool2, BoolDisplay::YesNo);

			static std::int32_t int32Test{ 69 };
			sub->AddOption<NumberOption<std::int32_t>>("Int32", nullptr, &int32Test, 0, 100);

			static std::int64_t int64Test{ 420 };
			sub->AddOption<NumberOption<std::int64_t>>("Int64", nullptr, &int64Test, 0, 1000, 10);

			static float floatTest{ 6.9f };
			sub->AddOption<NumberOption<float>>("Float", nullptr, &floatTest, 0.f, 10.f, 0.1f, 1);

			static std::vector<std::uint64_t> vector{ 1, 2, 3 };
			static std::size_t vectorPos{};

			sub->AddOption<ChooseOption<const char*, std::size_t>>("Array", nullptr, &Lists::DemoList, &Lists::DemoListPos);
			sub->AddOption<ChooseOption<std::uint64_t, std::size_t>>("Vector", nullptr, &vector, &vectorPos);
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Settings", SubmenuExtra, [](RegularSubmenu* sub)
		{

			/*sub->AddOption<ChooseOption<const char*, std::size_t>>(Trans[Lists::DemoListPos1], nullptr, &Trans, &Lists::DemoListPos1, false, [] { 	});
			sub->AddOption<NumberOption<std::int32_t>>("Amount", nullptr, &TransAmount, 0, 10000000, 100000, 3, true, "", "", [] { });
		sub->AddOption<RegularOption>("[RISKY] Custom Stealth Hashes", "", [] { TestStealth(TransAmount, atoi(Trans[Lists::DemoListPos1])); });
			sub->AddOption<RegularOption>("[Experimental] R* ID Joiner", "", [] {
				g_FiberScript->addTask([] {
					GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
					while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
					{
						IsKeyboardActive = true;
						g_UiManager->ResetInput();
						g_FiberScript->Wait(0);
					}
					IsKeyboardActive = false;
					if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
						return 0;
					Join = atoi(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
					Joiner = true;
				});

			});*/
			sub->AddOption<SubOption>("UI Settings", "customize your UI", SubmenuSettings);
			sub->AddOption<BoolOption<bool>>("Notify if Modder Detected", "", &Features::MenuNotifyBool, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Enable Controller Support", "Enable Controller Support", &m_Controller, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Unsensor Chat", "Secure your GTA Chat", &Features::ChatSensor, BoolDisplay::OnOff);

			//sub->AddOption<RegularOption>("Terminate Discord RPC", "", [] { Discord_Shutdown(); });
			sub->AddOption<RegularOption>("Close Game", "", [] { exit(0); });

		});


		

		g_UiManager->AddSubmenu<RegularSubmenu>("Outfits", Outfits, [](RegularSubmenu* sub)
		{

			sub->AddOption<RegularOption>("Random outfit", "change your clothes quickly", [] { Features::randomoutfit(); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Face:", nullptr, &testa, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 0), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, testa, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Head:", nullptr, &testb, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 1), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, testb, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Hair:", nullptr, &testc, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 2), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, testc, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Torso:", nullptr, &testd, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 3), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, testd, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Legs:", nullptr, &teste, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 4), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, teste, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Hands:", nullptr, &testf, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 5), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, testf, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Feet:", nullptr, &testg, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 6), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, testg, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Eyes:", nullptr, &testh, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 7), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, testh, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Accessories:", nullptr, &testi, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 8), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, testi, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Tasks:", nullptr, &testj, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 9), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, testj, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Textures:", nullptr, &testk, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 10), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, testk, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Torso2:", nullptr, &testl, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), 11), 1, 3, true, "", "", [] { PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, testl, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Head Props:", nullptr, &testm, 0, 255, 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, testm, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Eye Props:", nullptr, &testn, 0, 255, 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, testn, 0, 0); });
			sub->AddOption<NumberOption<std::int32_t>>("Item -> Ear Props:", nullptr, &testo, 0, 255, 1, 3, true, "", "", [] { PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 3, testo, 0, 0); });

		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Settings", SubmenuSettings, [](RegularSubmenu* sub)
		{
			Features::LoadPlayerInfo(g_SelectedPlayer);
			//sub->AddOption<BoolOption<std::atomic_bool>>("Enable/Disable Log Window", "Enable or Disable the Log Window", &g_Settings.m_LogWindow, BoolDisplay::OnOff);
			sub->AddOption<SubOption>("Infobar", "The bar just below the header saying 'SETTINGS'.", SubmenuSettingsSubmenuBar);
			sub->AddOption<SubOption>("Options", "Background, Scroller, Text, etc.", SubmenuSettingsOption);
			sub->AddOption<SubOption>("Footer", "Where the 'S' logo is at the bottom.", SubmenuSettingsFooter);
			sub->AddOption<SubOption>("Description", "The description is this thing here.", SubmenuSettingsDescription);
			sub->AddOption<SubOption>("Input", "Input delays", SubmenuSettingsInput);
			sub->AddOption<NumberOption<float>>("Change Horizontal Position", "Changes the X Postion", &g_UiManager->m_PosX, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Change Vertical Position", "Changes the Y Postion", &g_UiManager->m_PosY, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Change the Width", "Change The Width of the menu", &g_UiManager->m_Width, 0.01f, 1.f, 0.01f, 2);
			if (g_UiManager->m_PosX > 0.482f) {
				sub->AddOption<NumberOption<float>>("Player Info Position (On the left)", "Change position of the box on the right.", &g_UiManager->m_PosB, 0.f, 1.f, 0.01f, 2);
			}
			else if (g_UiManager->m_PosX < 0.482f) {
				sub->AddOption<NumberOption<float>>("Player Info Position (On the right)", "Change position of the box on the left.", &g_UiManager->m_PosA, 0.f, 1.f, 0.01f, 2);
			}
			if (sub->GetSelectedOption() == 10) { Features::LoadPlayerInfo(g_SelectedPlayer); }
		});
#include "SHVASILoader.h"
		g_UiManager->AddSubmenu<RegularSubmenu>("Language", SubmenuSettingsLanguage, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ GetModulePath(GetModuleHandleA(NULL)) };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						if (path.extension() == ".asi")
						{
						sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
						{
							//ASILoader::LoadPlugins(path.stem().u8string().c_str());
						});
						}

					}
				}
			}

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Infobar", SubmenuSettingsSubmenuBar, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_SubmenuBarHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_SubmenuBarTextSize, 0.01f, 1.f, 0.01f, 2);

			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text R", nullptr, &g_UiManager->m_SubmenuBarTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text G", nullptr, &g_UiManager->m_SubmenuBarTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text B", nullptr, &g_UiManager->m_SubmenuBarTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text A", nullptr, &g_UiManager->m_SubmenuBarTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Options", SubmenuSettingsOption, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Option Height", nullptr, &g_UiManager->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<std::uint8_t>>("Scroller R", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Scroller G", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Scroller B", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Scroller A", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text R", nullptr, &g_UiManager->m_OptionSelectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text G", nullptr, &g_UiManager->m_OptionSelectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text B", nullptr, &g_UiManager->m_OptionSelectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text A", nullptr, &g_UiManager->m_OptionSelectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text R", nullptr, &g_UiManager->m_OptionUnselectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text G", nullptr, &g_UiManager->m_OptionUnselectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text B", nullptr, &g_UiManager->m_OptionUnselectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text A", nullptr, &g_UiManager->m_OptionUnselectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Footer", SubmenuSettingsFooter, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Sprite Size", nullptr, &g_UiManager->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);

			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_FooterBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_FooterBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_FooterBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_FooterBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite R", nullptr, &g_UiManager->m_FooterSpriteColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite G", nullptr, &g_UiManager->m_FooterSpriteColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite B", nullptr, &g_UiManager->m_FooterSpriteColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite A", nullptr, &g_UiManager->m_FooterSpriteColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header", SubmenuSettingsHeader, [](RegularSubmenu* sub)
		{
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &Lists::HeaderTypesFrontend, &Lists::HeaderTypesPosition, true, []
			{
				g_UiManager->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
			});

			switch (g_UiManager->m_HeaderType)
			{
			case HeaderType::YTD:
				break;
			case HeaderType::YTD3:
				break;
			case HeaderType::YTD4:
				break;
			case HeaderType::YTD2:
				break;
			case HeaderType::YTD5:
				break;
			case HeaderType::YTD6:
				break;
			}

			sub->AddOption<SubOption>("Text", nullptr, SubmenuSettingsHeaderText);
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("YTD Images", SubmenuSettingsHeaderGradientBackground, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Alternate Header Image", nullptr, &Features::HeaderImage, BoolDisplay::OnOff);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Text", SubmenuSettingsHeaderText, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Enable", nullptr, &g_UiManager->m_HeaderText, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<float>>("Size", nullptr, &g_UiManager->m_HeaderTextSize, 0.1f, 2.f, 0.01f, 2);
			sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_UiManager->m_HeaderTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_UiManager->m_HeaderTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_UiManager->m_HeaderTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_UiManager->m_HeaderTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Description", SubmenuSettingsDescription, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Padding", "Padding before the description rect.", &g_UiManager->m_DescriptionHeightPadding, 0.0001f, 10.f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Height", "Size of the description rect.", &g_UiManager->m_DescriptionHeight, 0.01f, 10.f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", "Size of the description text.", &g_UiManager->m_DescriptionTextSize, 0.1f, 20.f, 0.01f, 2);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Input", SubmenuSettingsInput, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::int32_t>>("Open Delay", nullptr, &g_UiManager->m_OpenDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Back Delay", nullptr, &g_UiManager->m_BackDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Enter Delay", nullptr, &g_UiManager->m_EnterDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Vertical Delay", nullptr, &g_UiManager->m_VerticalDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Horizontal Delay", nullptr, &g_UiManager->m_HorizontalDelay, 10, 1000, 10, 0);
		});
		g_UiManager->AddSubmenu<RegularSubmenu>("Network", SubmenuPlayerList, [](RegularSubmenu* sub)
		{
				

			for (std::uint32_t i = 0; i < 32; ++i)
			{
				if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
				{
					sub->AddOption<SubOption>(PLAYER::GET_PLAYER_NAME(i), nullptr, SubmenuSelectedPlayer, [=]
					{
						g_SelectedPlayer = i;

					});
				}
			}
		});



		g_UiManager->AddSubmenu<RegularSubmenu>("Money Drop - All", MONEYDROPALL, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Enable Cash Drop", "Start droping Money", &Features::ALLMoneyDropBool, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<int>>("Drop Amount", "Select Bullet for Blame", &Features::DropAmount, 0, 2500, 10, 3, false, "", "", [] {});
			sub->AddOption<NumberOption<int>>("Drop Delay", "Select Bullet for Blame", &Features::BagDelay, 0, 5000, 50, 3, false, "", "", [] {});

		});



		g_UiManager->AddSubmenu<RegularSubmenu>("All Players", AllPlayers, [](RegularSubmenu* sub)
		{
				


			sub->AddOption<SubOption>("Remote Teleport", nullptr, TELEPORTALL);

			sub->AddOption<SubOption>("Money Drop All Player", nullptr, MONEYDROPALL);
			sub->AddOption<SubOption>("RP Drop All Player", nullptr, RPDROP);




			sub->AddOption<BoolOption<bool>>("Water Loop", nullptr, &Features::WaterAll, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Fire Loop", nullptr, &Features::FireAll, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Freeze", nullptr, &Features::FreezeAll, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Nametag ESP", "Show Names of all people on your screen", &Features::Nametag, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("ESP", "Show all people on your screen", &Features::espbool, BoolDisplay::OnOff, false, [] {});

			sub->AddOption<RegularOption>("Cage All Player", "Put your Player into the Cage", []
			{
				for (int i123 = 0; i123 <= 32; i123++) {
					if (PLAYER::PLAYER_ID() != i123) {

						Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i123), 0);
						Object obj;
						OBJECT::CREATE_OBJECT($("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1, true, 1, -1, &obj, true, false, false);
					}
				}

			});
	//		sub->AddOption<RegularOption>("Kill All Player", "Kill all Players in Lobby", []
	//		{
	//			for (int pimmel = 0; pimmel < 32; pimmel++)
	//			{
	//				int excludemypimmel = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(pimmel);

	//				if (excludemypimmel != PLAYER::PLAYER_PED_ID())
	//				{

	//					Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(pimmel);

	//					Vector3 pos = ENTITY::GET_ENTITY_COORDS(iPed, 1);
	//					addOwnedExplosion1(iPed, pos.x, pos.y, pos.z, 29, 999.f, false, false, 0.f);
	//				}
	//			}

	//		});

	//		sub->AddOption<RegularOption>("Clone All Player", "Cone all Playerss", []
	//		{
	//			for (int i = 0; i < 32; i++)
	//			{
	//				int excludeMe = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
	//				if (excludeMe > 0 && excludeMe != PLAYER::PLAYER_PED_ID())
	//				{

	//					PED::CLONE_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1, 1, 1);

	//				}
	//			}

	//		});


	//		sub->AddOption<RegularOption>("Solo Session", "10sec Game Wait", [] {
	//			Sleep(10000);
	//			Big::SYSTEM::WAIT(250);
	//		});


	//		sub->AddOption<RegularOption>("Give Weapons", nullptr, [&]
	//		{
	//			for (int i = 0; i <= 32; i++)
	//			{
	//				uint Weapons[] = { 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, // Melee
	//				0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, // Handguns
	//				0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, // Submachine Guns
	//				0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, // Shotguns
	//				0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, // Assault Rifles
	//				0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, // Light Machine Guns
	//				0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, // Sniper Rifles
	//				0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, // Heavy Weapons
	//				0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, // Throwables
	//				0x34A67B97, 0xFBAB5776, 0x060EC506, 0xAF3696A1, 0x476BF155, 0xB62D1F67,
	//				0x2B5EF5EC, 0xBA536372, 0x917F6C8C,
	//				};
	//				for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
	//					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), Weapons[i], 9999, true);
	//				}
	//			}
	//		});

	//		sub->AddOption<RegularOption>("Kick All Players", nullptr, [&]
	//		{
	//			for (int z = 0; z < 32; z++)
	//			{

	//				int excludeMe = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(z);
	//				if (excludeMe != PLAYER::PLAYER_PED_ID())
	//				{
	//DWORD64 args1[4] = { KICK_1, z };
	//			Hooks::TriggerScriptEvent(1, args1, 4, 1 << z);


	//			DWORD64 args2[3] = { KICK_2, z };
	//			Hooks::TriggerScriptEvent(1, args2, 3, 1 << z);


	//			DWORD64 args3[4] = { KICK_3, z };
	//			Hooks::TriggerScriptEvent(1, args3, 4, 1 << z);


	//			DWORD64 args4[5] = { KICK_4, z, 0, 111 };
	//			Hooks::TriggerScriptEvent(1, args4, 5, 1 << z);

	//			DWORD64 args5[3] = { KICK_5, z };
	//			Hooks::TriggerScriptEvent(1, args5, 3, 1 << z);


	//			DWORD64 args6[4] = { KICK_6, z, 50 };
	//			Hooks::TriggerScriptEvent(1, args6, 4, 1 << z);


	//			DWORD64 args7[4] = { KICK_7, z, 20, 1 };
	//			Hooks::TriggerScriptEvent(1, args7, 4, 1 << z);


	//			DWORD64 args8[4] = { KICK_8, z, 20 };
	//			Hooks::TriggerScriptEvent(1, args8, 4, 1 << z);


	//			DWORD64 args9[4] = { KICK_9, z, 20, 1 };
	//			Hooks::TriggerScriptEvent(1, args9, 4, 1 << z);


	//			DWORD64 args10[4] = { KICK_10, z, 20 };
	//			Hooks::TriggerScriptEvent(1, args10, 4, 1 << z);


	//			DWORD64 args11[4] = { KICK_11, z, 20 };
	//			Hooks::TriggerScriptEvent(1, args11, 4, 1 << z);


	//			DWORD64 args12[6] = { KICK_12, z, 0, 0, 0, 36 };
	//			Hooks::TriggerScriptEvent(1, args12, 6, 1 << z);


	//			DWORD64 args13[3] = { KICK_13, z, 36 };
	//			Hooks::TriggerScriptEvent(1, args13, 3, 1 << z);


	//			DWORD64 asd[3] = { KICK_14, z, -4294967260/*36*/ };
	//			Hooks::TriggerScriptEvent(1, asd, 3, 1 << z);

	//			DWORD64 adasdasd[4] = { KICK_15, z, 32 };
	//			Hooks::TriggerScriptEvent(1, adasdasd, 4, 1 << z);


	//			DWORD64 sadfas[5] = { KICK_16, z, 0, 0, 32 };
	//			Hooks::TriggerScriptEvent(1, sadfas, 5, 1 << z);


	//			DWORD64 asasdads[5] = { KICK_17, z, 0, 0, 32 };
	//			Hooks::TriggerScriptEvent(1, asasdads, 5, 1 << z);


	//			DWORD64 dffgdfgd[5] = { KICK_18, z, 4 };
	//			Hooks::TriggerScriptEvent(1, dffgdfgd, 5, 1 << z);


	//			DWORD64 fdfgdhfgh[5] = { KICK_19, z, 7 };
	//			Hooks::TriggerScriptEvent(1, fdfgdhfgh, 5, 1 << z);


	//			DWORD64 fddfgfdg[6] = { KICK_20, z, 0, 59 };
	//			Hooks::TriggerScriptEvent(1, fddfgfdg, 6, 1 << z);

	//			DWORD64 arfghhfgffgs[5] = { KICK_21, z, 0, 59 };
	//			Hooks::TriggerScriptEvent(1, arfghhfgffgs, 5, 1 << z);

	//			DWORD64 asdasdasd[4] = { KICK_22, z, 0, 59 };
	//			Hooks::TriggerScriptEvent(1, asdasdasd, 4, 1 << z);


	//			DWORD64 tzhjtzhhjtgghjgjh[4] = { KICK_23, z, 62 };
	//			Hooks::TriggerScriptEvent(1, tzhjtzhhjtgghjgjh, 4, 1 << z);


	//			DWORD64 qwqweqweqwe[4] = { KICK_24, z, 0, 26 };
	//			Hooks::TriggerScriptEvent(1, qwqweqweqwe, 4, 1 << z);


	//			DWORD64 sijhdgfbsduhfsbvdhgfsdf[5] = { KICK_25, z, 0, 26 };
	//			Hooks::TriggerScriptEvent(1, sijhdgfbsduhfsbvdhgfsdf, 5, 1 << z);


	//			DWORD64 hjgkhjkhjk[4] = { KICK_26, z, 0, 26 };
	//			Hooks::TriggerScriptEvent(1, hjgkhjkhjk, 4, 1 << z);


	//			DWORD64 jkljkljkl[3] = { KICK_27, z, 3 };
	//			Hooks::TriggerScriptEvent(1, jkljkljkl, 3, 1 << z);


	//			DWORD64 qwqwweqqwe[24] = { KICK_28, z, 180 };
	//			Hooks::TriggerScriptEvent(1, qwqwweqqwe, 24, 1 << z);


	//			DWORD64 zuizuizuizu[5] = { KICK_29, z, 64 };
	//			Hooks::TriggerScriptEvent(1, zuizuizuizu, 5, 1 << z);


	//			DWORD64 qweqweqwe[3] = { KICK_30, z, 32 };
	//			Hooks::TriggerScriptEvent(1, qweqweqwe, 3, 1 << z);


	//			DWORD64 uhijewhizuwerhb[4] = { KICK_31, z, 62 };
	//			Hooks::TriggerScriptEvent(1, uhijewhizuwerhb, 4, 1 << z);


	//			DWORD64 asdasdasdasdasd[18] = { KICK_32, z };
	//			Hooks::TriggerScriptEvent(1, asdasdasdasdasd, 18, 1 << z);

	//			DWORD64 asdasdasdasf[3] = { KICK_33, z };
	//			Hooks::TriggerScriptEvent(1, asdasdasdasf, 3, 1 << z);


	//			DWORD64 djkfgndejgnkd[13] = { KICK_34, z, 123 }; //fix
	//			Hooks::TriggerScriptEvent(1, djkfgndejgnkd, 13, 1 << z);


	//			DWORD64 asdasdfgddfgdfg[4] = { KICK_35, z };
	//			Hooks::TriggerScriptEvent(1, asdasdfgddfgdfg, 4, 1 << z);


	//			DWORD64 dfgdfgdfg[21];
	//			*dfgdfgdfg = KICK_36;
	//			dfgdfgdfg[1] = z;
	//			dfgdfgdfg[19] = 125;
	//			Hooks::TriggerScriptEvent(1, dfgdfgdfg, 21, 1 << z);

	//			DWORD64 sdfsdfsdfsdf[4] = { KICK_37, z, 1, 124 };//need check false alarm
	//			Hooks::TriggerScriptEvent(1, sdfsdfsdfsdf, 4, 1 << z);


	//			DWORD64 hjzhjkzhjkzhjkhjkhjk[10] = { KICK_38, z, 1, 10000, 32/*n0*/, 0, 1, 46, 1, 40 };
	//			Hooks::TriggerScriptEvent(1, hjzhjkzhjkzhjkhjkhjk, 10, 1 << z);


	//			DWORD64 ghfgfhfghfghfgh[10] = { KICK_39, z, 1, 10000, 32, 0, 1, 36, 1, 40 };
	//			Hooks::TriggerScriptEvent(1, ghfgfhfghfghfgh, 10, 1 << z);


	//			DWORD64 dfghfgfghhfghfg[25];
	//			*dfghfgfghhfghfg = KICK_40, dfghfgfghhfghfg[1] = z, dfghfgfghhfghfg[2] = 180;
	//			Hooks::TriggerScriptEvent(1, dfghfgfghhfghfg, 25, 1 << z);

	//				}
	//			}
	//		});

		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Script Events", SCRIPTSALL, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Sound Spam", nullptr, &Features::SoundSpamAll, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Remote OTR", nullptr, &Features::RemoteOTRAll, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Cops Blind Eye", nullptr, &Features::BlindEyeAll, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Camera Spam", nullptr, &Features::CameraSpamAll, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<BoolOption<bool>>("Never Wanted", nullptr, &Features::NeverWantedAll, BoolDisplay::OnOff, false, [] {});
			sub->AddOption<RegularOption>("Send To Job", "", [] { Features::SendToJob(); });
			sub->AddOption<RegularOption>("CEO Kick", "", [] { Features::CEOKick(); });
			sub->AddOption<RegularOption>("CEO Ban", "", [] { Features::CEOBan(true); });

			sub->AddOption<RegularOption>("Remove From Vehicle", "", [] { Features::GentleKick(true); });
		});


		g_UiManager->AddSubmenu<RegularSubmenu>("Remote Teleports", TELEPORTALL, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Eclipse Towers", "", [] { Features::Teleport1(true); });
			sub->AddOption<RegularOption>("West Vinewood", "", [] { Features::Teleport2(true); });
			sub->AddOption<RegularOption>("Las Lagunas", "", [] { Features::Teleport3(true); });
			sub->AddOption<RegularOption>("Spanish Ave", "", [] { Features::Teleport4(true); });
			sub->AddOption<RegularOption>("Power St", "", [] { Features::Teleport5(true); });
			sub->AddOption<RegularOption>("Del Perro", "", [] { Features::Teleport6(true); });
			sub->AddOption<RegularOption>("Milton Rd", "", [] { Features::Teleport7(true); });
			sub->AddOption<RegularOption>("The Royale", "", [] { Features::Teleport8(true); });
			sub->AddOption<RegularOption>("La Puerta", "", [] { Features::Teleport9(true); });
			sub->AddOption<RegularOption>("Rockford Dr", "", [] { Features::Teleport10(true); });
			sub->AddOption<RegularOption>("Dream Tower", "", [] { Features::Teleport11(true); });
			sub->AddOption<RegularOption>("San Vitas", "", [] { Features::Teleport12(true); });
			sub->AddOption<RegularOption>("Vespucci Blvd", "", [] { Features::Teleport13(true); });
			sub->AddOption<RegularOption>("Cougar Ave", "", [] { Features::Teleport14(true); });
			sub->AddOption<RegularOption>("Prosperity St", "", [] { Features::Teleport15(true); });
			sub->AddOption<RegularOption>("Weazel Plaza", "", [] { Features::Teleport16(true); });
			sub->AddOption<RegularOption>("Del Perro Office", "", [] { Features::Teleport17(true); });
			sub->AddOption<RegularOption>("Maze Bank West Office", "", [] { Features::Teleport18(true); });
			sub->AddOption<RegularOption>("Arcadius Office", "", [] { Features::Teleport19(true); });
			sub->AddOption<RegularOption>("Maze Bank Office", "", [] { Features::Teleport20(true); });
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Remote Teleports", TELEPORTSOLO, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Eclipse Towers", "", [] { Features::Teleport1(false); });
			sub->AddOption<RegularOption>("West Vinewood", "", [] { Features::Teleport2(false); });
			sub->AddOption<RegularOption>("Las Lagunas", "", [] { Features::Teleport3(false); });
			sub->AddOption<RegularOption>("Spanish Ave", "", [] { Features::Teleport4(false); });
			sub->AddOption<RegularOption>("Power St", "", [] { Features::Teleport5(false); });
			sub->AddOption<RegularOption>("Del Perro", "", [] { Features::Teleport6(false); });
			sub->AddOption<RegularOption>("Milton Rd", "", [] { Features::Teleport7(false); });
			sub->AddOption<RegularOption>("The Royale", "", [] { Features::Teleport8(false); });
			sub->AddOption<RegularOption>("La Puerta", "", [] { Features::Teleport9(false); });
			sub->AddOption<RegularOption>("Rockford Dr", "", [] { Features::Teleport10(false); });
			sub->AddOption<RegularOption>("Dream Tower", "", [] { Features::Teleport11(false); });
			sub->AddOption<RegularOption>("San Vitas", "", [] { Features::Teleport12(false); });
			sub->AddOption<RegularOption>("Vespucci Blvd", "", [] { Features::Teleport13(false); });
			sub->AddOption<RegularOption>("Cougar Ave", "", [] { Features::Teleport14(false); });
			sub->AddOption<RegularOption>("Prosperity St", "", [] { Features::Teleport15(false); });
			sub->AddOption<RegularOption>("Weazel Plaza", "", [] { Features::Teleport16(false); });
			sub->AddOption<RegularOption>("Del Perro Office", "", [] { Features::Teleport17(false); });
			sub->AddOption<RegularOption>("Maze Bank West Office", "", [] { Features::Teleport18(false); });
			sub->AddOption<RegularOption>("Arcadius Office", "", [] { Features::Teleport19(false); });
			sub->AddOption<RegularOption>("Maze Bank Office", "", [] { Features::Teleport20(false); });
		});

		g_UiManager->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
		{
			sub;
		});
	
	}
	void MainScript::Destroy()
	{
		g_UiManager.reset();

	}
	void Text(const char* text, int red, int green, int blue, int alpha, float x, float y, float width, float height, bool center)
	{
		UI::SET_TEXT_CENTRE(center);
		UI::SET_TEXT_COLOUR(red, green, blue, alpha);
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(width, height);
		UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
		UI::SET_TEXT_OUTLINE();
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT2("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT2(x, y, 0);
	}
	void MainScript::Tick()
	{


		//WelcomeBannerLoop();
		g_UiManager->OnTick();

	}
}
