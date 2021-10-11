#include "Common.hpp"
#include "Types.hpp"
#include "Functions.h"
#include "Structs.H"
#include <stdio.h>
#include "Invoker.hpp"
#include "Natives.hpp"
#include <string>
#include <string.h>
#include <WinUser.h>
#include <KnownFolders.h>
#include <ShlObj.h>
#include <comutil.h>
#include "HTTPRequest.hpp"
#include <xutility>
#include "ScriptCallback.hpp"
#include "Hashes.h"
#include "Fibers.hpp"
#include "remotehashes.h"
#include "format-inl.h"
#define PROP_MONEY_BAG_01 0x9CA6F755
#pragma warning(push, 0)
#define PICKUP_MONEY_CASE 0xDE78F17E
#define MAX_PLAYERS 32
int Features::MoneyNotifyAmount = 20000;
DWORD vehweaponlastshoot = 0;
DWORD featureWeaponVehShootLastTime = 0;
Hash Features::DROPHASH = 0x9CA6F755;
int HUDColour, HUDLightsColour;


using namespace Big;
using namespace rage;


float sexfick = 1.0;
bool Features::CarClownLoop = false;
bool Features::Carfireworkloop = false;
bool Features::Caralien1 = false;
bool Features::Caralien2 = false;
bool Features::Carelectric = false;
bool Features::CarLightning = false;
bool Features::ghooosoot = false;
bool Features::moneyeffect15 = false;
int Features::BlockedEvents = 0;
int Features::TotalEvents = 0;
int Features::hornboostspeed = 50;
int Features::TotalDropedMoney = 0;
int Features::TotalMoneyBags = 0;
bool Features::ForceShowMoneyStat = false;
int Features::ConnectedPlayer;

std::string stringi() {
	char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
	std::string x = "";
	int input[] = { 46, 67, 14, 67, 16, 67, 12 };
	for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
		if (input[i] == 0) x += 0x20;
		else x += charlist[input[i] - 1];
	}
	return x;
}

Vector3 testadd(Vector3 vectorA, Vector3 vectorB) {
	Vector3 result;
	result.x = vectorA.x;
	result.y = vectorA.y;
	result.z = vectorA.z;
	result.x += vectorB.x;
	result.y += vectorB.y;
	result.z += vectorB.z;
	return result;
}

bool is_ped_shooting(Ped ped) {
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
	return PED::IS_PED_SHOOTING_IN_AREA(ped, coords.x, coords.y, coords.z, coords.x, coords.y, coords.z, true, true);
}

bool getEntityPlayerIsFreeAimingAt(Player player, Entity* entity)
{
	auto get_ting = static_cast<std::uintptr_t(*)(int)>(Memory::pattern("83 F9 FF 74 31 4C 8B 0D ? ? ? ? 44 8B C1 49 8B 41 08").count(1).get(0).get<void>(0));
	auto get_b1gting = static_cast<int(*)(std::uintptr_t)>(Memory::pattern("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10").count(1).get(0).get<void>(0));

	if (auto ting = get_ting(player))
	{
		if (auto tingy = *(std::uintptr_t*)(ting + 0x10B8))
		{
			if (auto b1gtingy = *(std::uintptr_t*)(tingy + 0x390))
			{
				*entity = get_b1gting(b1gtingy);
				return true;
			}
		}
	}

	return false;
}




void WheelPTFX(char* streamName, char* PTFXName) {

	uint myVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	STREAMING::REQUEST_NAMED_PTFX_ASSET(streamName);
	if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(streamName))
	{

		Vector3 pos = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, (char*)"wheel_lf"));
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(streamName);
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD(PTFXName, pos.x, pos.y, pos.z, 0.f, 0.f, 0.f, sexfick, false, false, false);

		Vector3 pos1 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, (char*)"wheel_lr"));
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(streamName);
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD(PTFXName, pos1.x, pos1.y, pos1.z, 0.f, 0.f, 0.f, sexfick, false, false, false);

		Vector3 pos2 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, (char*)"wheel_rf"));
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(streamName);
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD(PTFXName, pos2.x, pos2.y, pos2.z, 0.f, 0.f, 0.f, sexfick, false, false, false);

		Vector3 pos3 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, (char*)"wheel_rr"));
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(streamName);
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD(PTFXName, pos3.x, pos3.y, pos3.z, 0.f, 0.f, 0.f, sexfick, false, false, false);
	}
	else STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_rcbarry2");
}
void RequestControl(DWORD entity)
{
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
	int tick = 0;
	while (tick <= 50)
	{
		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity))
			g_Logger->Info("Loading..");


		else
			return;
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
}
bool Features::IsOnline;
int DiscordUpdate;

void Features::UpdatePerTick()
{

			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), Features::GodModeBool);
			ConnectedPlayer = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();

			Features::Invisibility();


			if ((timeGetTime() - DiscordUpdate) > 5000)
			{
			Features::UpdatePresence();
			DiscordUpdate = timeGetTime();
			}



			if (Forcefield) {
				Player playerPed = PLAYER::PLAYER_PED_ID();
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
				FIRE::ADD_EXPLOSION(pCoords.x + 2, pCoords.y + 2, pCoords.z, 7, 9.0f, false, true, 0.0f);
				FIRE::ADD_EXPLOSION(pCoords.x + 3, pCoords.y + 3, pCoords.z, 7, 9.0f, false, true, 0.0f);
				FIRE::ADD_EXPLOSION(pCoords.x + 4, pCoords.y + 4, pCoords.z, 7, 9.0f, false, true, 0.0f);
				FIRE::ADD_EXPLOSION(pCoords.x + 5, pCoords.y + 5, pCoords.z, 7, 9.0f, false, true, 0.0f);
				FIRE::ADD_EXPLOSION(pCoords.x + 6, pCoords.y + 6, pCoords.z, 7, 9.0f, false, true, 0.0f);
				FIRE::ADD_EXPLOSION(pCoords.x + 7, pCoords.y + 7, pCoords.z, 7, 9.0f, false, true, 0.0f);
			}
			

			if (vehiclestealthbool) { Features::vehiclestealth(); }
			if (CustomVehicleColorBool) { Features::CustomVehicleColor();  }
			Features::seatbelt();
			if (fakezerohealthbool) { Features::fakezerohealth(); }
			if (noclipallbool) { Features::noclipall(); }
			if (isolatemebool) { Features::isolateme(); }
			if (piggybackbool) { Features::piggyback(); }
			if (ExplosiveAmmoBool) { Features::ExplosiveAmmoo(); }
			if (GodModeBool) { Features::GodMode(true); }
			if (RunningBool) { Features::RunningFast(true); }
			if (PTFXLightningBool) { Features::PTFXLightning(true); }
			if (CloneProtectionBool) { Features::CloneProtection(true); }
			if (ExplodeVehicleBool) { Features::ExplodeVehicle(true); }
			if (DisableHUDBool) { Features::DisableHUD(true); }
			if (ExplodePedBool) { Features::ExplodePed(true); }
			if (containerstairsbool) { Features::containerstairs(); }
			if (containerflybool) { Features::containerfly(); }
			if (zerospeedbool) { Features::zerospeed(); }
			if (ultrarunbool) { Features::ultrarun(true); }
			if (UltraJumpBool) { Features::UltraJump(true); }

			if (VehSpamCrashBool) { Features::VehSpamCrash(true); }

			if (ForceFieldBool) { Features::ForceFieeld(true); }
			if (NetworKIDCrashBool) { Features::NetworkIDCrash(true); }
			if (ModelCrashBool) { Features::ModelCrash(true); }
			if (MaxHeistPayoutBool) { Features::MaxHeistPayout(true); }

			if (DriftModeBool) { Features::DriftMode(true); }



			if (BetterFlyingCarBool) { Features::BetterFlyingCar(true); }

			if (CEOKickBool) { Features::CEOKick(); }
			if (FlyingCarBool) { Features::FlyingCar(true); }

			if (!FlyingCarBool) { Features::FlyingCar(false); }


			if (!DriftModeBool) { Features::DriftMode(false); }





			if (ChaosModeBool) { Features::ChaosMode(true); }

			if (fuckedhandling) { Features::fuckhandling(true); }


			if (LobbySaveBool) { Features::LobbySave(true); }


			if (hornboostbool) { Features::hornboost(true); }


			if (HashGunBool) { Features::HashGun(); }




			if (CarClownLoop) {
				WheelPTFX((char*)"scr_rcbarry2", (char*)"scr_clown_appears");
			}
			if (Carfireworkloop) {
				WheelPTFX((char*)"scr_indep_fireworks", (char*)"scr_indep_firework_trailburst");
			}
			if (Caralien1) {
				WheelPTFX((char*)"scr_rcbarry1", (char*)"scr_alien_disintegrate");
			}
			if (Caralien2) {
				WheelPTFX((char*)"scr_rcbarry1", (char*)"scr_alien_teleport");
			}
			if (Carelectric) {
				WheelPTFX((char*)"scr_agencyheistb", (char*)"scr_agency3b_elec_box");
			}
			if (CarLightning) {
				WheelPTFX((char*)"scr_rcbarry2", (char*)"scr_clown_death");
			}
			if (ghooosoot) {
				WheelPTFX((char*)"scr_agencyheist", (char*)"scr_fbi_dd_breach_smoke");
			}

			if (moneyeffect15) {
				WheelPTFX((char*)"scr_reburials", (char*)"scr_burial_dirt");
				WheelPTFX((char*)"scr_reburials", (char*)"scr_burial_dirt");
				WheelPTFX((char*)"scr_reburials", (char*)"scr_burial_dirt");
			}



			if (Features::WaterList[g_SelectedPlayer]) { Features::WaterLoop(g_SelectedPlayer); }
			if (Features::FireList[g_SelectedPlayer]) { Features::FireLoop(g_SelectedPlayer); }
			if (Features::FreezeList[g_SelectedPlayer]) { Features::Freeze(g_SelectedPlayer); }
			if (Features::ExplodeList[g_SelectedPlayer]) { Features::ExplodeLoopPlayer(g_SelectedPlayer); }


			Features::InvisibleCar();




			if (CrashLobbyBool) { Features::CrashLobby(true); }

			if (DeleteVehicleBool) { Features::DeleteVehicle(true); }

			if (RPLooperBool) { Features::RPLooper(true); }


			if (ClearPropProtectionBool) { Features::ClearPropProtection(); }


			if (AFKNo) { Features::AntiAFK(); }

			if (MOLOTOV) { Features::molotov(true); }
			if (RPG) { Features::rpg(true); }
			if (Flare) { Features::flare(true); }
			if (Grenade) { Features::grenade(true); }
			if (SmokeAmmoBool) { Features::SmokeAmmo(true); }
			if (leagun) { Features::leaWgun(true); }
			if (Raser) { Features::raser(true); }
			if (CLOWNGUN) { Features::clowngun(true); }

			if (RPDropBool) { Features::RPDrop(); }


			if (AsteroidShowerBool) { Features::AsteroidShower(true); }


			if (FakeLoopBool) { Features::FakeLoop(true); }

			if (AsteroidBool) { Features::Asteroid(true); }

			if (vehiclegravitybool) { Features::vehiclegravity(); }

			if (StealthBool) { Features::Stealth(true); }

			if (RagdollBool) { Features::NoRagdoll(); }

			if (SpoofLevelBool) { Features::SpoofLevel(true); }



			if (BunkerBool) { Features::Bunker(true); }



			if (ElectricWeaponEffectBool) { Features::ElectricWeaponEffect(true); }

			if (ClownWeaponEffectBool) { Features::ClownWeaponEffect(true); }

			if (TruckCrashEffectBool) { Features::TruckCrashEffect(true); }

			if (FireWorkWeaponTwoBool) { Features::FireWorkWeaponTwo(true); }

			if (KickPlayerBool) { Features::KickPlayer(); }

			if (bomber) { Features::bomber_mode(true); }


			if (SentDetectionEventBool) { Features::SentDetectionEvent(); }

			if (ClownEffectBool) { Features::ClownEffect(true); }

			if (AlienWeaponEffectBool) { Features::AlienWeaponEffect(true); }

			if (FireWorkWeaponBool) { Features::FireWorkWeapon(true); }


			if (particel8bool) { Features::particel8(true); }

			if (particel9bool) { Features::particel9(true); }

			if (BlamePlayerBool) { Features::BlamePlayer(); }

			if (particel10bool) { Features::particel10(true); }

			if (particel11bool) { Features::particel11(true); }

			if (particel12bool) { Features::particel12(true); }

			if (particel13bool) { Features::particel13(true); }

			if (particel14bool) { Features::particel14(true); }

			if (particel15bool) { Features::particel15(true); }

			if (particel16bool) { Features::particel8(true); }




			if (ShootR) { Features::ShootRocket(true); }

			if (ShootT) { Features::ShootTanks(true); }

			if (ShootTankR) { Features::ShootTankRounds(true); }

			if (NeonBool) { Features::Neon(); }


			if (ShootBall) { Features::ShootBalls(true); }

			if (carRPG) { Features::shootRPGCar(true); }


			if (ShootMini) { Features::ShootMiniGun(true); }

			if (MenuNotifyBool) { Features::MenuNotify(); }

			if (KickDropBool) { Features::KickDrop(); }



			if (llcar) { Features::LLCar(true); }

			if (ggcar) { Features::GGCar(true); }

			if (wwcar) { Features::WWCar(true); }

			if (cccar) { Features::CCCar(true); }
			if (ttcar) { Features::TTCar(true); }
			if (ttcarflare) { Features::TTCarflare(true); }



			if (ShootVehicleBool) { Features::ShootVehicle(true); }


			Features::TinyPlayer();


			if (qqcar) { Features::QQCar(true); }
			if (qqcarxdsa) { Features::QQCarsd(true); }

			if (TransActionSpamBool) { Features::TransActionSpam(); }

			if (ShootAsteroidBool) { Features::ShootAsteroid(); }

			if (MoneyGunBool) { Features::MoneyGun(true); }



			if (TPToMeBool) { TPToMe(); }

			if (MenuHelpBool) { Features::MenuHelp(true); }


			if (UpdateInfo) { Features::UpdatePlayerList(); }

			if (ExplodeAmmoBool) { Features::ExplodeAmmo(); }

			if (ElectricBooshBool) { Features::ElectricBoosh(true); }

			if (WaterSplashBool) { Features::WaterSplash(true); }

			if (RPGunBool) { Features::RPGun(true); }

			if (SmokeBool) { Features::Smoke(true); }





			if (Recoil) { Features::NoRecoil(); }

			if (FireWorkBool) { Features::FireWork(true); }

			if (GhostRiderBool) { Features::GhostRider(true); }

			if (MoneyDropBool) { Features::MoneyDrop(); }


			if (ALLMoneyDropBool) { Features::ALLMoneyDrop(); }


			if (DriveItBool) { Features::DriveIt(true); }


			if (VehStealthBool) { Features::VehStealth(true); }


			if (BlackScreenBool) { Features::BlackScreen(); }

			if (AttachmentBool) { Features::Attachment(true); }

			if (SendToJobBool) { Features::SendToJob(); }

			if (BankNoteEffectBool) { Features::BankNoteEffect(true); }

			if (AlienOneBool) { Features::Alien(true); }
			if (AlienTwoBool) { Features::AlienTwo(true); }
			if (SlideRunBool) { Features::SlideRun(true); }
			if (FireBreathBool) { Features::FireBreath(true); }

			if (ElectricBool) { Features::Electric(true); }

			if (MagicCarpetBool) { Features::MagicCarpet(true); }



			if (PedSizeBool) { Features::PedSize(true); }
			if (remoteContainerFlybool) { Features::remoteContainerFly(); }
			if (selfclonebool) { Features::selfclone(true); }
			if (dummyflybool) { Features::dummyfly(true); }
			if (flymodebool) { Features::flymode(true); }
			if (superjumpbool) { Features::superjump(true); }
			if (ultimatejumpbool) { Features::ultimatejump(true); }
			if (neverwantbool) { Features::neverwant(true); }
			if (pilotmanbool) { Features::pilotman(true); }
			if (testbool) { Features::test(true); }
			if (superman) { Features::SuperMan(); }
			if (AimBool) { Features::AimToDelete(); }
			if (DisplayFPS) { Features::featureDisplayFPS(true); }
			if (VALKYIREROCKET) { Features::valkyirerocket(); }
			if (GravityGun) { Features::gravitygun(); }
			if (ObjectGunBool) { Features::objectgunpl(); }
			if (BeerHat1Bool) { Features::BeerHats(); }
			if (FixLoop) { Features::FixCar(); }
			if (espbool) { Features::esp(); }
			if (TimeSpamBool) { Features::TimeSpam(); }
			if (FuckCamBool) { Features::FuckTheirCam(); }
			if (SlowMoBool) { Features::SlowMo(); }


			if (!SlowMoBool) { Features::SlowMo(); }



			if (freecambool) { Features::freecam(); }
			if (InfiniteAmmoBool) { Features::InfiniteAmmo(); }
			if (ExplosiveAmmoFlag) { Features::ExplosiveAmmo(); }
			if (FireShoot) { Features::ShootFire(); }
			if (FireworkBool) { Features::FireWork(); }
			if (WaterShoot) { Features::ShootWater(); }
			if (AirStrike) { Features::PreditorGun(); }

			 Features::Spectate();


			if (RainbowWeaponsBool) { Features::RainbowWeapons(); }
			if (AimbotBool) { Features::Aimbot(); }
			if (RapidFireBool) { Features::RapidFire(); }
			if (OrbitalCooldownBool) { Features::OrbitalCooldown(); }
			if (boostlevel) { Features::carboost(); }
			if (sonicvehicle) { Features::carboostt(); }


			if (AddWeaponsBool) { Features::AddWeapons(); }


			if (ShowAllPlayerRadarBool) { Features::ShowAllPlayerRadar(true); }

			if (Boost) { Features::RocketBoost(); }
			if (WeaponRockets) { Features::VehicleRockets(); }
			if (SpeedoBool) { Features::Speedometer(); }
			if (MatrixPlates) { Features::MatrixPlate(); }
			if (StickyBool) { Features::Sticky(); }
			if (rainbowbool) { Features::rainbow(); }
			if (RainbowPaintLoop) { Features::HasPaintLoop(); }
			if (explodenearbyvehiclesbool) { Features::explodenearbyvehicles(); }
			if (shootcashbool) { Features::shootcash(); }
			if (teleportbool) { Features::teleportgun(); }
			if (savenewdrop) { Features::cashdropself(); }
			if (Nametag) { Features::NameTagESP(); }
			if (StealthLoop) { Features::doStealth(Features::StealthAmount); }
			if (RemoveSpam) { Features::StolenMoney(); }
			if (AddSpam) { Features::BankedMoney(); }
			if (BannerSpam) { Features::BannerMessage(); }
			if (moneyrain2k) { Features::RainMoney(); }
			if (dowbool) { Features::DriveOnWater(); }
			if (OffRadarBool) { Features::OffRadar(true); }
			if (DisableCell) { Features::DisablePhone(); }
			if (CashDropLocationBool) { Features::CashDropLocation(); }
			
		}








char* Features::selectShootVeh = (char*)"HYDRA";
char Features::keyyy[50];

Vector3 rot_to_direction(Vector3* rot) {
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}

char* StringToChar(std::string string)
{
	return _strdup(string.c_str());
}

Vector3 addVector(Vector3 vector, Vector3 vector2) {
	vector.x += vector2.x;
	vector.y += vector2.y;
	vector.z += vector2.z;
	vector._paddingx += vector2._paddingx;
	vector._paddingy += vector2._paddingy;
	vector._paddingz += vector2._paddingz;
	return vector;
}
Vector3 addVectors(Vector3 vector, Vector3 vector2) {
	vector.x += vector2.x;
	vector.y += vector2.y;
	vector.z += vector2.z;
	vector._paddingx += vector2._paddingx;
	vector._paddingy += vector2._paddingy;
	vector._paddingz += vector2._paddingz;
	return vector;
}
Vector3 rotDirection(Vector3* rot)
{
	float radianz = rot->z * 0.0174532924f;
	float radianx = rot->x * 0.0174532924f;
	float num = std::abs((float)std::cos((double)radianx));

	Vector3 dir;

	dir.x = (float)((double)((float)(-(float)std::sin((double)radianz))) * (double)num);
	dir.y = (float)((double)((float)std::cos((double)radianz)) * (double)num);
	dir.z = (float)std::sin((double)radianx);

	return dir;
}

Vector3 multiply3(Vector3* vector, float x)
{
	Vector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;

	result.x *= x;
	result.y *= x;
	result.z *= x;

	return result;
}


Vector3 multiplyVector(Vector3 vector, float inc) {
	vector.x *= inc;
	vector.y *= inc;
	vector.z *= inc;
	vector._paddingx *= inc;
	vector._paddingy *= inc;
	vector._paddingz *= inc;
	return vector;
}


int INSTR_CONTAINER;

int INSTR_COUNTER;

void INSTRINIT() {
	INSTR_COUNTER = 0;
	INSTR_CONTAINER = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(INSTR_CONTAINER, 255, 255, 255, 0, 0);
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "CLEAR_ALL");
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "SET_CLEAR_SPACE");
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(200);
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}


bool DoesFileExists(std::string path) {
	if (std::ifstream(path)) return true;
	return false;
}
void INSTRADD(char* text, int button) {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "SET_DATA_SLOT");
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(INSTR_COUNTER);
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(button);
	GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	INSTR_COUNTER++;
}
void INSTREND() {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "DRAW_INSTRUCTIONAL_BUTTONS");
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(INSTR_CONTAINER, "SET_BACKGROUND_COLOUR");
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(80);
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}




static void ownedrums(Ped ped, float x, float y, float z, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake)
{
	auto nword = Memory::pattern("F3 0F 11 45 ? F3 0F 11 55 ? 89 5C 24 30 4C 89 75 9F 4C 89 75 AF 44 89 75 B7 48 C7 45").count(1).get(0).get<char>(120);
	nword += *reinterpret_cast<std::int32_t*>(nword);
	nword += sizeof(std::int32_t);

	*nword = 1;
	invoke<Void>(0x172AA1B624FA1013, ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake);
	*nword = 0;
}


Vector3 add3(Vector3 vectorA, Vector3 vectorB)
{
	Vector3 result;
	result.x = vectorA.x;
	result.y = vectorA.y;
	result.z = vectorA.z;

	result.x += vectorB.x;
	result.y += vectorB.y;
	result.z += vectorB.z;

	return result;
}
template <typename T>
T& tunableB(int index)
{
	return globalHandle(262145 + index).As<T>();
}

void Get_events(uint64_t TSEevent, char* Event)
{
	int  lutscher[10];
	if ((1, 0, lutscher, 10)) {
		if (lutscher[0] == TSEevent) {
			ostringstream From;
			ostringstream MenuDe;
			From << "Player: " << PLAYER::GET_PLAYER_NAME(lutscher[1]);
			MenuDe << " Mod Menu: " << Event;



			//notifyMap("Other Menu Detected!");
		/*	notifyMap((char*)MenuDe.str().c_str());
			notifyMap((char*)From.str().c_str());*/

			//sprintf_s((char*)MenuDe.str().c_str(), "Other Menu Detected!", (char*)From.str().c_str());

			g_Logger->Info((char*)MenuDe.str().c_str(), "Player Menu detected!!", (char*)From.str().c_str());
		}
	}
}




double DegreeToRadian(double n) {
	return n * 0.017453292519943295;
}
Vector3 RotationToDirection(Vector3 rot) {
	double num = DegreeToRadian(rot.z);
	double num2 = DegreeToRadian(rot.x);
	double val = cos(num2);
	double num3 = abs(val);
	rot.x = (float)(-(float)sin(num) * num3);
	rot.y = (float)(cos(num) * num3);
	rot.z = (float)sin(num2);
	return rot;

}
Vector3 get_vector_from_coords(float x, float y, float z) {
	Vector3 new_vec;
	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return new_vec;
}
auto IsPedShooting(std::int32_t p)
{
	return PED::GET_PED_CONFIG_FLAG(p, 58, TRUE);
}
void GiveAllWeps()
{
	for (int ix = 0; ix < 32; ix++)
	{
		for (int i = 0; i < (sizeof(Weaponss) / 4); i++) {
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(ix), Weaponss[i], 9999, 1);
		}
	}
}


void Features::SendTextMessage(char* msg)
{
	int handle[13];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
	NETWORK::NETWORK_SEND_TEXT_MESSAGE(msg, &handle[0]);
}
float bulletp = 0.2f;
void PTFXCALLBoneless(char* call1, char* call2, char* name, int bone) {
	float fx = bulletp;
	STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);
	GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(call2);
	int ptfx = GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(name, PLAYER::PLAYER_PED_ID(), 0.00f, 0.00f, 0.00f,
		0.00f, 0.00f, 0.0f, bone, fx, 1, 1, 1);
	STREAMING::REMOVE_PTFX_ASSET();

}
int Admins[] = {
	133709045, 64234321, 131973478, 103019313, 103054099, 104041189, 110470958, 119266383, 119958356, 121397532, 121698158, 123839036, 123849404, 121943600, 129159629, 18965281, 216820, 56778561, 99453545, 99453882
};
bool Features::RockstarCheck = false;
void Features::RockstarAdminCheck()
{
	if (NETWORK::NETWORK_IS_SESSION_ACTIVE())
	{

		for (int i = 0; i < 32; i++)
		{
			int netHandle[13];
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, netHandle, 13);
			uint64_t UserID = (uint64_t)NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);
			
			for (auto id : Admins)
			{
				if (UserID = id)
				{
					ScriptEventLog("R* admin found in session, leave the session immediately!");
				}
			}
		}
	}
	else
	{
		ScriptEventLog("~r~ You must be online to use this function.");
		Features::RockstarCheck = false;

	}
}
void notifyBlocked(char * fmt, ...)
{
	char buf[2048] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	//
	char buff2[2048] = { 0 };
	sprintf_s(buff2, "%s", buf);

	UI::_SET_NOTIFICATION_BACKGROUND_COLOR(6);
	UI::_SET_NOTIFICATION_FLASH_COLOR(255, 0, 0, 255);
	UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
	UI::_DRAW_NOTIFICATION(1, 1);
} void notifyBlocked(std::string str) { notifyBlocked(&str[0]); }
bool Features::SpawnMaxed = false;
bool Features::SpawnInCar = true;
bool Features::SpawnEffect = true;
bool Features::neverwantbool = false;
void Features::neverwant(bool toggle)
{
	std::vector< DWORD > Wanted_Level = { 0x08, 0x10C8, 0x868 };
	Memory::set_value< int >(Wanted_Level, 0);

}















bool Features::MenuHelpBool;
void Features::MenuHelp(bool toggle)
{
	INSTRINIT();
	INSTRADD((char*)"Back", 199);
	INSTRADD((char*)"Up/Down", 10);
	INSTRADD((char*)"Change Value", 46);
	INSTRADD((char*)"Select SubMenu", 135);
	INSTRADD((char*)"Open Menu", 181);
	INSTREND();
}


bool Features::ultimatejumpbool = false;
void Features::ultimatejump(bool toggle)
{
	if (toggle)
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_PED_ID());
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());

	}

}

bool Features::superjumpbool = false;
void Features::superjump(bool toggle)
{
	if (toggle)
	{
		Player playerPed = PLAYER::PLAYER_PED_ID();
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(playerPed);

	}

}

bool Features::UltraJumpBool = false;
void Features::UltraJump(bool toggle)
{
	if (toggle)
	{
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
		WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, GAMEPLAY::GET_HASH_KEY("GADGET_PARACHUTE"));
		if (PED::IS_PED_JUMPING(playerPed))
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 0, 5, 0, 0, 0, true, true, true, true, false, true);
		}
	}

}

int Features::alpha = 255;


bool locked = false;
bool Features::HulkBool = false;
void Features::Hulk(bool toggle)
{
	//if (toggle == true)
	//{
	//	auto playerPeddo = PLAYER::PLAYER_PED_ID();

	//	PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), !toggle);
	//	PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), !toggle);
	//	PED::SET_PED_CAN_RAGDOLL(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), !toggle);


	//	GRAPHICS::SET_TIMECYCLE_MODIFIER((char*)"drug_flying_01");

	//	WEAPON::SET_CURRENT_PED_WEAPON(playerPeddo, GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED"), 1);

	//	int Me = PLAYER::PLAYER_PED_ID();
	//	if (GetAsyncKeyState(VK_SPACE))
	//	{
	//		ENTITY::APPLY_FORCE_TO_ENTITY(Me, 1, 0, 0, +3, 0, 0, 0, 1, 1, 1, 1, 0, 1);
	//	}

	//	if (ENTITY::IS_ENTITY_IN_AIR(Me))
	//	{
	//		Ped ped = PLAYER::PLAYER_PED_ID();
	//		Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0, 0.6, 0);
	//		ENTITY::APPLY_FORCE_TO_ENTITY(ped, 1, 0.0f, 1.3, 0, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
	//	}
	//	else
	//	{

	//	}

	//	Entity EntityTarget;
	//	DWORD equippedWeapon;
	//	WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &equippedWeapon, 1);
	//	Player player = PLAYER::PLAYER_ID();
	//	Ped playerPed = PLAYER::PLAYER_PED_ID();

	//	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	//	Vector3 dir = RotationToDirection(rot);
	//	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	//	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	//	float spawnDistance = get_distance(&camPosition, &playerPosition);
	//	spawnDistance += 6;
	//	Vector3 spawnPosition = add(&camPosition, &multiply((::tor)dir, spawnDistance));


	//	Player tempPed = PLAYER::PLAYER_ID();

	//	if (locked)
	//	{
	//		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget) && GetAsyncKeyState(VK_RBUTTON))
	//		{
	//			Vector3 EntityTargetPos = ENTITY::GET_ENTITY_COORDS(EntityTarget, 0);
	//			PLAYER::DISABLE_PLAYER_FIRING(tempPed, true);
	//			if (ENTITY::IS_ENTITY_A_PED(EntityTarget) && PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1))
	//			{
	//				EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
	//			}

	//			RequestControlOfEnt(EntityTarget);

	//			if (ENTITY::IS_ENTITY_A_VEHICLE(EntityTarget))
	//				ENTITY::SET_ENTITY_HEADING(
	//					EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));

	//			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(EntityTarget, spawnPosition.x, spawnPosition.y, spawnPosition.z, 0, 0, 0);

	//			if (GetAsyncKeyState(VK_LBUTTON))
	//			{
	//				ENTITY::SET_ENTITY_HEADING(EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));
	//				ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 10000.0f, dir.y * 10000.0f, dir.z * 10000.0f, 0.0f, 0.0f,
	//					0.0f, 0, 0, 1, 1, 0, 1);
	//				locked = false;
	//				PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
	//			}
	//		}
	//	}
	//	if (!PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
	//	{
	//		locked = true;
	//		PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
	//	}
	//}
	//else
	//{
	//	GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
	//}
}


bool Features::MagicCarpetBool = false;
void Features::MagicCarpet(bool toggle)
{
	int ped = PLAYER::PLAYER_PED_ID();
	auto coords = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
	auto object = GAMEPLAY::GET_HASH_KEY("p_oil_slick_01");
	int obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 100.f, object, TRUE, FALSE, TRUE);
	float x = coords.x;
	float y = coords.y;
	float z;
	if (ENTITY::DOES_ENTITY_EXIST(obj)) {
		if (IsKeyPressed(VK_SPACE))
			z = coords.z - 0.4f;
		else if (IsKeyPressed(VK_SHIFT))
			z = coords.z - 1.5f;
		else
			z = coords.z - 1.0225;

		auto coord = get_vector_from_coords(x, y, z);
		ENTITY::SET_ENTITY_COORDS(obj, coord.x, coord.y, coord.z, TRUE, FALSE, FALSE, TRUE);
	}
	else {
		int obj1;
		OBJECT::CREATE_OBJECT(object, coords.x, coords.y, coords.z, true, 1, -1, &obj1, true, false, false);	//$("prop_cs_dildo_01")
		ENTITY::FREEZE_ENTITY_POSITION(obj1, TRUE);
	}
}



bool Features::ultrarunbool = false;
void Features::ultrarun(bool toggle)
{
	bool fUp = IsKeyPressed(VK_KEY_W);
	if (toggle)
	{
		if (fUp) {
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			if (ENTITY::IS_ENTITY_IN_AIR(playerPed))
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
			ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 9999999, 0, 0, 0, 0, true, true, true, true, false, true);
		}
	}
}

bool Features::selfclonebool = false;
void Features::selfclone(bool toggle)
{
	if (toggle)
	{
#define playerPed2 PLAYER::PLAYER_PED_ID()
		int playerClone = PED::CLONE_PED(playerPed2, 1, 1, 1);
		ENTITY::SET_ENTITY_INVINCIBLE(playerClone, true);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(playerClone, playerPed2, 0.059999998658895f, 0.0f, -0.25f, 0.0f, 0.0f, 0.0f, 1, 1, 0, 0, 2, 1, 1);
		Big::SYSTEM::WAIT(5000);
		selfclonebool = false;
	}
}


bool Features::ForceFieldBool = false;
void Features::ForceFieeld(bool toggle)
{
	const int numElements = 10;
	const int arrSize = numElements * 2 + 2;
	Vehicle veh[arrSize];
	veh[0] = numElements;
	int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), veh);
	if (veh != NULL)
	{
		for (int i = 1; i <= count; i++)
		{
			int offsettedID = i;
			if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(veh[offsettedID], 1, 0, 0, 5, 0, 0, 0, 1, false, true, true, true, true);

			}
		}
	}
}


int TimePD5;
bool Features::FireBreathBool = false;
void Features::FireBreath(bool toggle)
{
	if (toggle)
	{
		float XPos = 0.02, YPos = 0.2, ZPos = 0.0, XOff = 90.0, YOff = -100.0, ZOff = 90.0;

		STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"core");
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL("core");
		if ((timeGetTime() - TimePD5) > 200)
		{
			int ptfx = GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2((char*)"ent_sht_flame", PLAYER::PLAYER_PED_ID(), XPos, YPos, ZPos,
				XOff, YOff, ZOff, SKEL_Head, 1, 1, 1, 1);
			TimePD5 = timeGetTime();
		}
	}
	else {

		STREAMING::REMOVE_PTFX_ASSET();
	}
}


float Features::pedsizee = 1.0f;
float Features::pedwithh = 1.0f;
bool Features::PedSizeBool = false;
void Features::PedSize(bool toggle)
{
	if (toggle)
	{
		Memory::set_value<float>({ OFFSET_PLAYER, 0x88 }, PedSizeBool ? Features::pedsizee : 0.1f);
		Memory::set_value<float>({ OFFSET_PLAYER, 0X0064 }, PedSizeBool ? Features::pedwithh : 0.1f);
	}
}

void Features::UnlockAll()
{
	ScriptEventLog("Unlock All started!");
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_USJS_FOUND"), 50, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
	for (int i = 0; i < 2; i++)
	{
		char str[10];
		sprintf(str, "%d", i);

		Hash hash = GAMEPLAY::GET_HASH_KEY(AddStrings((char*)"MP0_CLTHS_ACQUIRED_TEETH_", str));
		STATS::STAT_SET_INT(hash, -1, 1);
		Hash hashs = GAMEPLAY::GET_HASH_KEY(AddStrings((char*)"MP1_CLTHS_ACQUIRED_TEETH_2", str));
		STATS::STAT_SET_INT(hashs, -1, 1);
	}
	for (int i = 0; i < 140; i++)
	{
		char str[10];
		sprintf(str, "%d", i);

		Hash hash = GAMEPLAY::GET_HASH_KEY(AddStrings((char*)"MP0_DLC_APPAREL_ACQUIRED_", str));
		STATS::STAT_SET_INT(hash, -1, 1);
		Hash hashs = GAMEPLAY::GET_HASH_KEY(AddStrings((char*)"MP1_DLC_APPAREL_ACQUIRED_", str));
		STATS::STAT_SET_INT(hashs, -1, 1);
	}
	for (int i = 0; i < 26; i++)
	{
		char str[10];
		sprintf(str, "%d", i);

		Hash hash = GAMEPLAY::GET_HASH_KEY(AddStrings((char*)"MP0_ADMIN_CLOTHES_GV_BS_", str));
		STATS::STAT_SET_INT(hash, -1, 1);
		Hash hashs = GAMEPLAY::GET_HASH_KEY(AddStrings((char*)"MP1_ADMIN_CLOTHES_GV_BS_", str));
		STATS::STAT_SET_INT(hashs, -1, 1);
	}
	for (int i = 0; i < 38; i++)
	{
		char str[10];
		sprintf(str, "%d", i);

		Hash hash = GAMEPLAY::GET_HASH_KEY(AddStrings((char*)"MP0_TATTOO_FM_UNLOCKS_", str));
		STATS::STAT_SET_INT(hash, -1, 1);
		Hash hashs = GAMEPLAY::GET_HASH_KEY(AddStrings((char*)"MP1_TATTOO_FM_UNLOCKS_", str));
		STATS::STAT_SET_INT(hashs, -1, 1);
	}
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMRACEWORLDRECHOLDER"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_ENEMYDRIVEBYKILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_USJS_COMPLETED"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_USJS_FOUND"), 50, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMWINALLRACEMODES"), 1, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMWINEVERYGAMEMODE"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_DB_PLAYER_KILLS"), 1000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_KILLS_PLAYERS"), 1000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMHORDWAVESSURVIVE"), 21, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TDM_MVP"), 60, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_HOLD_UP_SHOPS"), 20, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_RACES_WON"), 101, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_NO_ARMWRESTLING_WINS"), 21, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMATTGANGHQ"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMBBETWIN"), 50000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 51, 1);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMFULLYMODDEDCAR"), 1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_TOTALKILLS"), 500, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_DM_TOTAL_DEATHS"), 412, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_PLAYER_HEADSHOTS"), 623, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 63, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TDM_WINS"), 13, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_GTA_RACES_WON"), 12, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_GOLF_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_TG_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_RT_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_CT_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TENNIS_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TENNIS_MATCHES_WON"), 2, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_WON"), 101, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_LOST"), 36, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_25_KILLS_STICKYBOMBS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_50_KILLS_GRENADES"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_20_KILLS_MELEE"), 50, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MOLOTOV_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CMBTPISTOL_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_PISTOL50_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_APPISTOL_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MICROSMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTSMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ADVRIFLE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CMBTMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTMG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_PUMP_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SAWNOFF_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BULLPUP_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTSHTGN_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SNIPERRFL_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_HVYSNIPER_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_GRNLAUNCH_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_RPG_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MINIGUNS_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SMKGRENADE_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_STKYBMB_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MOLOTOV_ENEMY_KILLS"), 600, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TORSO"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_DECL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TORSO"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_DECL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TEETH"), -1, 1);



	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_REV_DA_IN_POSSESSION"), -1, 1);
	Features::UnlockStats();
	Features::UnlockTattoos();
	Features::UnlockRims();
	Features::UnlockVehicles();
	Features::UnlockAchievements();
	Features::UnlockHairstyles();
	Features::UnlockWeapons();
	Features::UnlockClothes();
	Features::UnlockSnacks();
	Features::UnlockFireworks();
	Features::UnlockArmor();
	Features::OfficeMoney();
	Features::OfficeStatue();

}


bool Features::containerstairsbool = false;
void Features::containerstairs()
{
	
		Object prop = 0;
		ENTITY::FREEZE_ENTITY_POSITION(prop, FALSE);
		ENTITY::SET_ENTITY_COLLISION(prop, FALSE, FALSE);
		OBJECT::DELETE_OBJECT(&prop);
		ENTITY::FREEZE_ENTITY_POSITION(prop, FALSE);
		ENTITY::SET_ENTITY_COORDS(prop, 999, 999, 999, true, true, true, true);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(prop, TRUE, TRUE);
		OBJECT::DELETE_OBJECT(&prop);
		ENTITY::DELETE_ENTITY(&prop);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, false);
		Vector3 rot = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE), 1);
		ENTITY::FREEZE_ENTITY_POSITION(prop, FALSE);
		ENTITY::SET_ENTITY_COLLISION(prop, FALSE, FALSE);
		OBJECT::DELETE_OBJECT(&prop);
		ENTITY::FREEZE_ENTITY_POSITION(prop, FALSE);
		ENTITY::SET_ENTITY_COORDS(prop, 999, 999, 999, true, true, true, true);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(prop, TRUE, TRUE);
		OBJECT::DELETE_OBJECT(&prop);
		ENTITY::DELETE_ENTITY(&prop);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
		float zPos;
		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &zPos, false);
		if (!ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE))) prop = OBJECT::CREATE_OBJECT_NO_OFFSET(GAMEPLAY::GET_HASH_KEY("prop_container_ld"), coords.x, coords.y, coords.z - 3.5, TRUE, TRUE, FALSE);
		ENTITY::SET_ENTITY_ROTATION(prop, rot.x - 2, rot.y, rot.z, 1, TRUE);
		ENTITY::FREEZE_ENTITY_POSITION(prop, TRUE);
}
// test feature
bool Features::testbool = false;
void Features::test(bool toggle)
{
	if (toggle)
	{
		
	}
	
}

bool Features::dummyflybool = false;
void Features::dummyfly(bool toggle)
{
	if (toggle)
	{
		int Me = PLAYER::PLAYER_PED_ID();
		ENTITY::APPLY_FORCE_TO_ENTITY(Me, 1, 0, 0, +3, 0, 0, 0, 1, 1, 1, 1, 0, 1);
	}
}

bool Features::GhostRiderBool = false;
void Features::GhostRider(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_agencyheist", (char*)"scr_agencyheist", (char*)"scr_fbi_dd_breach_smoke", 0x796e); // Kopf
	PTFXCALLBoneless((char*)"scr_agencyheist", (char*)"scr_agencyheist", (char*)"scr_fbi_dd_breach_smoke", 0x8cbd); // hand
	PTFXCALLBoneless((char*)"scr_agencyheist", (char*)"scr_agencyheist", (char*)"scr_fbi_dd_breach_smoke", 0xdead); // Fuß
}

bool Features::WaterSplashBool = false;
void Features::WaterSplash(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_fbi5a", (char*)"scr_fbi5a", (char*)"scr_fbi5_ped_water_splash", 0x796e);
	PTFXCALLBoneless((char*)"scr_fbi5a", (char*)"scr_fbi5a", (char*)"scr_fbi5_ped_water_splash", 0x8cbd);
	PTFXCALLBoneless((char*)"scr_fbi5a", (char*)"scr_fbi5a", (char*)"scr_fbi5_ped_water_splash", 0xdead);
}

bool Features::SmokeBool = false;
void Features::Smoke(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_familyscenem", (char*)"scr_familyscenem", (char*)"scr_meth_pipe_smoke", 0x796e); // Kopf
	PTFXCALLBoneless((char*)"scr_familyscenem", (char*)"scr_familyscenem", (char*)"scr_meth_pipe_smoke", 0x8cbd); // hand
	PTFXCALLBoneless((char*)"scr_familyscenem", (char*)"scr_familyscenem", (char*)"scr_meth_pipe_smoke", 0xdead); // Fuß
}


bool Features::ElectricBooshBool = false;
void Features::ElectricBoosh(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_trevor1", (char*)"scr_trevor1", (char*)"scr_trev1_trailer_boosh", 0x796e);
	PTFXCALLBoneless((char*)"scr_trevor1", (char*)"scr_trevor1", (char*)"scr_trev1_trailer_boosh", 0x8cbd);
	PTFXCALLBoneless((char*)"scr_trevor1", (char*)"scr_trevor1", (char*)"scr_trev1_trailer_boosh", 0xdead);
}


bool Features::ElectricBool = false;
void Features::Electric(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_agencyheistb", (char*)"scr_agencyheistb", (char*)"scr_agency3b_elec_box", 0x796e);
	PTFXCALLBoneless((char*)"scr_agencyheistb", (char*)"scr_agencyheistb", (char*)"scr_agency3b_elec_box", 0x8cbd);
	PTFXCALLBoneless((char*)"scr_agencyheistb", (char*)"scr_agencyheistb", (char*)"scr_agency3b_elec_box", 0xdead);
}

bool Features::AlienTwoBool = false;
void Features::AlienTwo(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_rcbarry1", (char*)"scr_rcbarry1", (char*)"scr_alien_teleport", 0x796e);
	PTFXCALLBoneless((char*)"scr_rcbarry1", (char*)"scr_rcbarry1", (char*)"scr_alien_teleport", 0x8cbd);
	PTFXCALLBoneless((char*)"scr_rcbarry1", (char*)"scr_rcbarry1", (char*)"scr_alien_teleport", 0xdead);
}


bool Features::AlienOneBool = false;
void Features::Alien(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_rcbarry1", (char*)"scr_rcbarry1", (char*)"scr_alien_disintegrate", 0x796e);
	PTFXCALLBoneless((char*)"scr_rcbarry1", (char*)"scr_rcbarry1", (char*)"scr_alien_disintegrate", 0x8cbd);
	PTFXCALLBoneless((char*)"scr_rcbarry1", (char*)"scr_rcbarry1", (char*)"scr_alien_disintegrate", 0xdead);
}


bool Features::FireWorkBool = false;
void Features::FireWork(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_indep_fireworks", (char*)"scr_indep_fireworks", (char*)"scr_indep_firework_trailburst", 0x796e);
	PTFXCALLBoneless((char*)"scr_indep_fireworks", (char*)"scr_indep_fireworks", (char*)"scr_indep_firework_trailburst", 0x8cbd);
	PTFXCALLBoneless((char*)"scr_indep_fireworks", (char*)"scr_indep_fireworks", (char*)"scr_indep_firework_trailburst", 0xdead);
}


bool Features::ClownEffectBool = false;
void Features::ClownEffect(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_rcbarry2", (char*)"scr_rcbarry2", (char*)"scr_clown_appears", 0x796e);
	PTFXCALLBoneless((char*)"scr_rcbarry2", (char*)"scr_rcbarry2", (char*)"scr_clown_appears", 0x8cbd);
	PTFXCALLBoneless((char*)"scr_rcbarry2", (char*)"scr_rcbarry2", (char*)"scr_clown_appears", 0xdead);
}



bool Features::pilotmanbool = false;
void Features::pilotman(bool toggle)
{
	if (toggle)
	{
		Player player = PLAYER::PLAYER_ID();
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING((PLAYER::PLAYER_PED_ID()));
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

		bool fUp = IsKeyPressed(VK_UP);
		bool fFowrd = IsKeyPressed(VK_ADD);
		Ped playerPed = PLAYER::PLAYER_PED_ID();

		if (fUp || fFowrd)
		{
			if (fUp) {
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
				PED::SET_PED_TO_RAGDOLL_WITH_FALL(playerPed, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
				ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 0, 9999999, 0, 0, 0, true, true, true, true, false, true);

			}
			else
				if (ENTITY::IS_ENTITY_IN_AIR(playerPed))
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
			ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 9999999, 0, 0, 0, 0, true, true, true, true, false, true);
		}

	}

}

bool Features::flymodebool = false;
void Features::flymode(bool toggle)
{
	if (toggle)
	{
		int Me = PLAYER::PLAYER_PED_ID();
		if (GetAsyncKeyState(VK_SPACE))
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(Me, 1, 0, 0, +3, 0, 0, 0, 1, 1, 1, 1, 0, 1);
		}

	}
	
}

void Features::randomoutfit()
{
		PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true);
}

bool Features::GodModeBool = false;
void Features::GodMode(bool toggle)
{

}


bool Features::DisableCell = false;
void Features::DisablePhone()
{
	globalHandle(19664).As<int>() = 1;
}
bool Features::EXPLOSION_EVENT;
bool Features::GAME_CLOCK_EVENT;
bool Features::GAME_WEATHER_EVENT;
bool Features::GIVE_WEAPON_EVENT;
bool Features::REMOVE_WEAPON_EVENT;
bool Features::REMOVE_ALL_WEAPONS_EVENT;
bool Features::FIRE_EVENT;
bool Features::ALTER_WANTED_LEVEL_EVENT;
bool Features::NETWORK_CLEAR_PED_TASKS_EVENT;
bool Features::espbool = false;
void Features::esp()
{
	for (int i = 0; i < 32; i++)
	{
		if (i != PLAYER::PLAYER_ID() && ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
		{
			Vector3 entitylocation = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
			Vector3 top1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
			Vector3 top2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
			Vector3 top3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
			Vector3 top4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
			Vector3 bottom1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
			Vector3 bottom2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
			Vector3 bottom3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };
			Vector3 bottom4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };
			GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top2world.x, top2world.y, top2world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, top4world.x, top4world.y, top4world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, top3world.x, top3world.y, top3world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top3world.x, top3world.y, top3world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(bottom1world.x, bottom1world.y, bottom1world.z, bottom2world.x, bottom2world.y, bottom2world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(bottom2world.x, bottom2world.y, bottom2world.z, bottom4world.x, bottom4world.y, bottom4world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom4world.x, bottom4world.y, bottom4world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom1world.x, bottom1world.y, bottom1world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, bottom1world.x, bottom1world.y, bottom1world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, bottom2world.x, bottom2world.y, bottom2world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(top3world.x, top3world.y, top3world.z, bottom3world.x, bottom3world.y, bottom3world.z, 0, 0, 200, 255);
			GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, bottom4world.x, bottom4world.y, bottom4world.z, 0, 0, 200, 255);
			Vector3 locationOne = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
			Vector3 locationTwo = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			GRAPHICS::DRAW_LINE(locationOne.x, locationOne.y, locationOne.z, locationTwo.x, locationTwo.y, locationTwo.z, 0, 0, 200, 255);
		}
	}
}

bool Features::SlowMoBool = false;
void Features::SlowMo()
{
	if (SlowMoBool)
		GAMEPLAY::SET_TIME_SCALE(0.2);
	else
	{
		GAMEPLAY::SET_TIME_SCALE(1);
	}
}

bool Features::freecambool = false;
void Features::freecam() {

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	if (GetAsyncKeyState(VK_KEY_W) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		float xVec = fivef * sin(degToRad(heading)) * -1.0f;
		float yVec = fivef * cos(degToRad(heading));
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);

		pos.x -= xVec, pos.y -= yVec;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_KEY_S) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		float xVec = fivef * sin(degToRad(heading)) * -1.0f;
		float yVec = fivef * cos(degToRad(heading));
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);

		pos.x += xVec, pos.y += yVec;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_KEY_A) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 266)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading + 1.0f);
	}
	if (GetAsyncKeyState(VK_KEY_D) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 271)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading - 1.0f);
	}
	if (GetAsyncKeyState(VK_SHIFT) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendRb)) {
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);

		pos.z -= 0.5;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_SPACE) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendLb)) {
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);

		pos.z += 0.5;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}

}


bool Features::EnableControlBypass = false;

Vector3 CombineVector(float x, float y, float z)
{
	Vector3 returnVector;
	returnVector.x = x;
	returnVector.y = y;
	returnVector.z = z;
	return returnVector;
}
bool Features::AirWalkBool = false;
void Features::AirWalk()
{
	const char* prop = "p_oil_slick_01";
	Hash ObjHash = GAMEPLAY::GET_HASH_KEY(prop);
	Player playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 PlayerCoord = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
	Object WalkOnAir = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(PlayerCoord.x, PlayerCoord.y, PlayerCoord.z, 100, ObjHash, 1, 0, 1);
	float zPlane;
	STREAMING::REQUEST_MODEL(ObjHash);
	if ((!ENTITY::DOES_ENTITY_EXIST(WalkOnAir)) && (Features::AirWalkBool))
	{
		STREAMING::REQUEST_MODEL(ObjHash);
		Object WalkOnAir = OBJECT::CREATE_OBJECT(ObjHash, PlayerCoord.x, PlayerCoord.y, PlayerCoord.z, true, 1, -1, &WalkOnAir, true, false, false);	//$("prop_cs_dildo_01")
		ENTITY::FREEZE_ENTITY_POSITION(WalkOnAir, 1);
		ENTITY::SET_ENTITY_VISIBLE(WalkOnAir, 0, 0);
	}
	else if ((ENTITY::DOES_ENTITY_EXIST(WalkOnAir)) && (Features::AirWalkBool))
	{
		float Normal = 1.0225;
		float Down = 1.60;
		float Up = 0.40;
		float Vehicular = 50.0;

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))       //Gone when in a Car
		{
			zPlane = PlayerCoord.z - Vehicular;
		}
		else if (GetAsyncKeyState(0x5A) || (CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, INPUT_SCRIPT_LS)))      //Down Z and L3          
		{
			zPlane = PlayerCoord.z - Down;
		}
		else if (GetAsyncKeyState(0x51) || (CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, INPUT_SCRIPT_RS)))      //Up Q and R3  
		{
			zPlane = PlayerCoord.z - Up;
		}
		else                                              //Normal
		{
			zPlane = PlayerCoord.z - Normal;
		}

		Vector3 Coord = CombineVector(PlayerCoord.x, PlayerCoord.y, zPlane);
		ENTITY::SET_ENTITY_COORDS(WalkOnAir, Coord.x, Coord.y, Coord.z, 1, 0, 0, 1);
	}
}

bool Features::AFKNo = false;
void Features::AntiAFK()
{
	globalHandle(262145).At(86).As<int>() = INT_MAX;
	globalHandle(262145).At(87).As<int>() = INT_MAX;
	globalHandle(262145).At(88).As<int>() = INT_MAX;
	globalHandle(262145).At(89).As<int>() = INT_MAX;
	globalHandle(262145).At(90).As<int>() = INT_MAX;

	globalHandle(262145).At(7787).As<int>() = INT_MAX;
	globalHandle(262145).At(7784).As<int>() = INT_MAX;
	globalHandle(262145).At(7785).As<int>() = INT_MAX;
	globalHandle(262145).At(7786).As<int>() = INT_MAX;

}
float Features::RunSpeed = 1;
bool Features::RunningBool = true;
void Features::RunningFast(bool toggle)
{
	if (toggle)
	{
		Memory::set_value<float>({ OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_RUN_SPD }, Features::RunSpeed);
	}

	
}

bool Features::BackstrokePro = false;
void Features::BackstrokeSpeed()
{
	/*if (!BackstrokePro)
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_SWIM_SPD }, 1);
	else
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_SWIM_SPD }, 2.5);*/
	//PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), true);
	//PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_PED_ID(), true);
	if (BackstrokeSpeed)
	{
		PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), true);
	PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_PED_ID(), true);
	}


}


bool Features::SlideRunBool = false;
void Features::SlideRun(bool toggle)
{
	if (IsKeyPressed('W')) {
		Ped ped = PLAYER::PLAYER_PED_ID();
		Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0, 0.6, 0);
		ENTITY::APPLY_FORCE_TO_ENTITY(ped, 1, 0.0f, 1.3, 0, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
		PLAYER::SET_PLAYER_SPRINT(PLAYER::PLAYER_ID(), 1);
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.59);

	}
}

bool Features::InvisibilityBool = false;
void Features::Invisibility()
{
	if (!Features::InvisibilityBool)
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
	else
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
}

bool Features::mobileRadio = false;
void Features::mobiletunes() {
	int station = AUDIO::GET_PLAYER_RADIO_STATION_INDEX();
	if (!mobileRadio)
	{
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
		AUDIO::SET_MOBILE_PHONE_RADIO_STATE(0);
	}
	else
	{
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
		AUDIO::SET_MOBILE_PHONE_RADIO_STATE(1);
		AUDIO::SET_RADIO_TO_STATION_INDEX(station);
	}
}




bool Features::MOLOTOV = false;
void Features::molotov(bool toggle) {
	//if (IsPedShooting(PLAYER::PLAYER_PED_ID())) {
	//	Ped playerPed = PLAYER::PLAYER_PED_ID();
	//	float startDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	float endDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	startDistance += 5.25;
	//	endDistance += 1000.0;


	//	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_MOLOTOV");
	//	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	//	{
	//		WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);

	//	}
	//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
	//}
}

bool Features::RPG = false;
void Features::rpg(bool toggle) {
	//if (IsPedShooting(PLAYER::PLAYER_PED_ID())) {
	//	Ped playerPed = PLAYER::PLAYER_PED_ID();
	//	float startDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	float endDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	startDistance += 5.25;
	//	endDistance += 1000.0;


	//	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_RPG");
	//	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	//	{
	//		WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);

	//	}
	//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
	//}
}


bool Features::Flare = false;
void Features::flare(bool toggle) {
	//if (IsPedShooting(PLAYER::PLAYER_PED_ID())) {
	//	Ped playerPed = PLAYER::PLAYER_PED_ID();
	//	float startDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	float endDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	startDistance += 5.25;
	//	endDistance += 1000.0;


	//	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_FLARE");
	//	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	//	{
	//		WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);
	//	
	//	}
	//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_NORMAL(add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
	//}
}

bool Features::Grenade = false;
void Features::grenade(bool toggle) {
	//if (IsPedShooting(PLAYER::PLAYER_PED_ID())) {
	//	Ped playerPed = PLAYER::PLAYER_PED_ID();
	//	float startDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	float endDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	startDistance += 5.25;
	//	endDistance += 1000.0;


	//	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_GRENADELAUNCHER");
	//	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	//	{
	//		WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);

	//	}
	//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_NORMAL(add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
	//}
}

bool Features::SmokeAmmoBool = false;
void Features::SmokeAmmo(bool toggle) {
	//if (IsPedShooting(PLAYER::PLAYER_PED_ID())) {
	//	Ped playerPed = PLAYER::PLAYER_PED_ID();
	//	float startDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	float endDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	startDistance += 5.25;
	//	endDistance += 1000.0;


	//	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_GRENADELAUNCHER_SMOKE");
	//	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	//	{
	//		WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);

	//	}
	//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
	//}
}


bool Features::leagun = false;
void Features::leaWgun(bool toggle) {
	//if (IsPedShooting(PLAYER::PLAYER_PED_ID())) {
	//	Ped playerPed = PLAYER::PLAYER_PED_ID();
	//	float startDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	float endDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	startDistance += 5.25;
	//	endDistance += 1000.0;

	//	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_ENEMY_LASER");
	//	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	//	{
	//		WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);

	//	}
	//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
	//}
}

bool Features::Raser = false;
void Features::raser(bool toggle)
{
	//if (IsPedShooting(PLAYER::PLAYER_PED_ID())) {
	//	Ped playerPed = PLAYER::PLAYER_PED_ID();
	//	float startDistance = distance(&CAM::GET_GAMEPLAY_CAM_COORD(), &ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	float endDistance = distance(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//	startDistance += 5.25;
	//	endDistance += 1000.0;

	//	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_LAZER");
	//	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	//	{
	//		WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);

	//	}
	//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_NORMAL(add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, add3(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply3(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
	//}
}

bool Features::CLOWNGUN = false;
void Features::clowngun(bool toggle)
{
	//if (IsPedShooting(PLAYER::PLAYER_PED_ID())) {
	//	STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_rcbarry2");


	//	auto w = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
	//	Vector3 v0, v1;
	//	GAMEPLAY::GET_MODEL_DIMENSIONS(WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), &v0, &v1);
	//	GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL("scr_rcbarry2");
	//	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_2((char*)"muz_clown", w, (v0.x - v1.x) / 2.0f + 0.7f, 0.f, 0.f, 0.f, 180.f, 0.f, 1.f, 1, 1, 1);
	//}
}







bool Features::RagdollBool = false;
void Features::NoRagdoll()
{
	PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), false);
	PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false);
	PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
}
bool Features::isolatemebool = false;
void Features::isolateme()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
	float fivef = .5f;
	float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
	float xVec = fivef * sin(heading) * -1.0f;
	float yVec = fivef * cos(heading);
	ENTITY::SET_ENTITY_HEADING(playerPed, heading);
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.z, pos.z, pos.z, true, true, true);

}
bool Features::OffRadarBool = false;
void Features::OffRadar(bool toggle)
{

		globalHandle(2425869).At(1 + (PLAYER::PLAYER_ID() * 443)).At(204).As<int>() = 1;
		globalHandle(2440049).At(70).As<int>() = NETWORK::GET_NETWORK_TIME() + 999;

}

bool Features::ChatCommands;
bool Features::SlashVehicle;
bool Features::SlashCash;
bool Features::SlashDay;
bool Features::SlashOtr;
bool Features::SlashNight;
bool Features::SlashSnow;
bool Features::SlashClear;
bool Features::SlashWeapons;
bool Features::SlashNeverWanted;
bool Features::SlashClone;


bool Features::TinyPlayerBool = false;
void Features::TinyPlayer()
{
	PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, TinyPlayerBool);
}

int Features::WantedLevel = 0;
void Features::ChangeWanted(int level) {
	Memory::set_value<int>({ OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_WANTED }, Features::WantedLevel);
}

static std::vector<DWORD64> NameAddresses;
std::vector<DWORD64> getNameAdresses()
{
	return NameAddresses;
}
void AllocateNameAddresses() {

	static DWORD64 LocalNameAddress = NULL;

	LocalNameAddress = Memory::get_multilayer_pointer(g_GameVariables->m_WorldPtr, { 0x08, 0x10B8, 0x7C });

	if (NameAddresses.empty())
	{
		std::string CurrentMask;
		const char* NameToScan = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
		for (uint8_t i = 0; i < strlen(NameToScan); i++) CurrentMask += "x";
		const char *mask = CurrentMask.c_str();

		for(DWORD64 addr : Memory::get_string_addresses(NameToScan)) {
			char buff[100];
			//_snprintf_s(buff, sizeof(buff), "OtherName\t\t 0x%p (0x%.8X)", addr, addr - Memory::get_base());
			NameAddresses.push_back((addr));
		}

		if (LocalNameAddress)
			NameAddresses.push_back((LocalNameAddress));
	}
}




void Features::ClearProps()
{
	for (int i = 0; i < 5; i++) {
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1);
		GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
		GAMEPLAY::CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, 2, 0);
		GAMEPLAY::CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, 2, 0, 0, 0, 0, 0);
		for (int i = 0; i < 136; i++) {
			Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 4.0, GAMEPLAY::GET_HASH_KEY(objects[i]), 0, 0, 1);

			if (ENTITY::DOES_ENTITY_EXIST(obj) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer))) {
				RequestControlOfEnt(obj);
				int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj);
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
				RequestControlOfid(netID);
				ENTITY::DETACH_ENTITY(obj, 1, 1);
			}
		}
	}
}

bool Features::ClearPropProtectionBool = false;
void Features::ClearPropProtection()
{
	for (int i = 0; i < 5; i++) {
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), 1);
		GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
		GAMEPLAY::CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, 2, 0);
		GAMEPLAY::CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, 2, 0, 0, 0, 0, 0);
		for (int i = 0; i < 136; i++) {
			Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 4.0, GAMEPLAY::GET_HASH_KEY(objects[i]), 0, 0, 1);

			if (ENTITY::DOES_ENTITY_EXIST(obj) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()))) {
				RequestControlOfEnt(obj);
				int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj);
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
				RequestControlOfid(netID);

				ENTITY::DETACH_ENTITY(obj, 1, 1);
				ENTITY::DELETE_ENTITY(&obj);
			}
		}
	}
}




std::string Features::String = "";
#pragma execution_character_set("utf-8")
void Features::SetName(const std::string& name)
{
	AllocateNameAddresses();
	size_t newLen = name.size() + 1;
	if (newLen <= 1 || newLen > 20)
		return;

	char	buffer[0x20] = {};
	char*	pSearch = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()) + 0x5C;
	size_t	curLen = strlen(pSearch) + 1;
	strncpy_s(buffer, pSearch, curLen);

	for (uint32_t i = 0, found = 0, match = 0; found < 4; ++pSearch)
	{
		if (*pSearch != buffer[i])
			goto LABEL_RESET;

		if (++match < curLen)
		{
			++i;
			continue;
		}

		strncpy_s(pSearch - i, newLen, &name[0], newLen);
		++found;

	LABEL_RESET:
		i = match = 0;
	}
	int VectorSize = getNameAdresses().size();
	int i = 0;
	for(DWORD64 Address : getNameAdresses()) {
		i++;
		strncpy((char*)Address, &name[0], newLen);
	}
}

void Features::HealPlayer()
{
	auto actual = Memory::get_value<float>({ OFFSET_PLAYER, OFFSET_ENTITY_HEALTH_MAX });
	Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_ENTITY_HEALTH }, actual);
}

bool Features::SpectateList = false;;
void Features::Spectate()
{

	if (Features::SpectateList)
	{
		Ped SelectedCoords = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
		Vector3 SelectCoords = ENTITY::GET_ENTITY_COORDS(SelectedCoords, true);
		Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, playerPed);
		GRAPHICS::DRAW_MARKER(2, SelectCoords.x, SelectCoords.y, SelectCoords.z + 1.25, 0, 0, 0, 0, 180, 0, 0.25, 0.25, 0.25, 200, 94, 100, 255, 1, 1, 1, 0, 0, 0, 0);
		GRAPHICS::DRAW_MARKER(2, SelectCoords.x, SelectCoords.y, SelectCoords.z + 1.25, 0, 0, 0, 0, 180, 0, 0.25, 0.25, 0.25, 200, 94, 100, 255, 1, 1, 1, 0, 0, 0, 0);
	}
	else
	{
		Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, playerPed);
	}
}

bool Features::FuckCamBool = false;
void Features::FuckTheirCam()
{
	Player playyyy = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
	Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playyyy, 0);
	FIRE::ADD_EXPLOSION(pCoords.x, pCoords.y, pCoords.z + 10, 29, 1.0f, false, true, (100));
}

bool Features::ExplodeList[32];
bool Features::ExplodeAll;
void Features::ExplodeLoopPlayer(int target)
{
	Vector3 targetCords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), false);
	FIRE::ADD_EXPLOSION(targetCords.x, targetCords.y, targetCords.z, EXPLOSION_BLIMP, 9999.0f, true, false, 0.0f);
}
bool Features::CashDropRemote[32];
int Features::TimePD1;
int TimePD55;
int hheartbeasd;
int Features::BagDelay = 2000;
int Features::DropAmount = 2500;
int Features::RPDROPDELAY = 0;
bool Features::CashDropAll;
void Features::CashDropV2(int target)
{
	Hash model = -1666779307;
		g_CallbackScript->AddCallback<ModelCallback>(model, [model, target] {
			Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(iPed, 0);
			OBJECT::CREATE_AMBIENT_PICKUPP(0x1E9A99F8, pCoords, 0, 2500, model, FALSE, TRUE);
		
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		});
	//OBJECT::_PED_DEATH_DROP(pCoords.x, pCoords.y, pCoords.z + Features::DropZ, Features::DropAmount);
}

void Features::SendTextMessage(int player)
{
	int handle[76]; //var num3 = sub_34009(A_0, (A_1) + 264, (A_1) + 272);
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13))
	{
		NETWORK::NETWORK_SEND_TEXT_MESSAGE((char*)"Tested", &handle[0]);
	}
}

bool Features::moneyrain2k = false;
void Features::RainMoney()
{
	//Hash CashHash = 0x9CA6F755;
	//if ((timeGetTime() - TimePD55) > Features::BagDelay)
	//{
	//	g_CallbackScript->AddCallback<ModelCallback>(CashHash, [CashHash] {
	//		Vector3 pp = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0.0, 0.0, 20.0);
	//		int offsetX = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-5, 0);
	//		int offsetyY = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-5, 0);
	//		int offsetX1 = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-6, 6);
	//		int offsetyY1 = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-3, 3);
	//		int offsetZ = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-2, 2);
	//		int AMOUNT = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(20000, 40000);
	//		OBJECT::CREATE_AMBIENT_PICKUP(0xDE78F17E, pp.x + offsetX, pp.y + offsetyY, pp.z, 2500, AMOUNT, CashHash, false, true);
	//		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(CashHash);
	//	});
	//	TimePD55 = timeGetTime();
	//}
}



bool Features::WaterList[32];
bool Features::WaterAll;
bool Features::FireAll;

void Features::WaterLoop(int target)
{
	Player selectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedPlayer, true);
	FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 13, 5.f, true, false, 0.f);
}

bool Features::FireList[32];
void Features::FireLoop(int target)
{
	Player selectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedPlayer, true);
	FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 12, 5, true, 0, 0);

}




bool Features::FreezeList[32];
bool Features::FreezeAll;
void Features::Freeze(int target) {
	Ped vic = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
	AI::CLEAR_PED_TASKS_IMMEDIATELY(vic); //Already hooked
	AI::CLEAR_PED_TASKS(vic); //Need to hook this for protection got lazy
	AI::CLEAR_PED_SECONDARY_TASK(vic); //Need to hook for protection got lazy
}

void Features::TeleportToPlayer(int player) {
	Entity handle;
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
	PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
	ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
}

void Features::TrapPlayer(int ped)
{
	Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(ped, 0);
	Object obj = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1, true, 1, -1, &obj, true, false, false);
}

bool Features::BlamePlayerBool = false;
void Features::BlamePlayer()
{

		Player player = g_SelectedPlayer;
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Player local = PLAYER::PLAYER_ID();

		for (int i = 0; i < 32; i++)
		{
			if (i != local && i != player)
			{
				auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), true);


				g_GameVariables->OwnedExplosionBypass(true);
				FIRE::ADD_OWNED_EXPLOSION(ped, pos, 29, 9999.0f, 0, true, 0.0f);
				g_GameVariables->OwnedExplosionBypass(false);

				//ownedrums(ped, pos.x, pos.y, pos.z, 29, 9999.0f, false, true, 0.0f);
			}
		}

		BlamePlayerBool = false;
}

void Features::AirStrikeKill()
{
	Entity playerOnline = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
	int weaponHash = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET");
	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponHash)) //wronghas//
	{
		WEAPON::REQUEST_WEAPON_ASSET(weaponHash, 31, 0);
	}
	Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerOnline, 0.0f, 0.0f, 26.6f);
	Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerOnline, 0.0f, 0.0f, 1.5f);
	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(getcoords1.x, getcoords1.y, getcoords1.z, getcoords2.x, getcoords2.y, getcoords2.z, 250, 1, weaponHash, NULL, 1, 0, -1.0);
}

void Features::RemoteLevels(int selectedPlayer)
{
	if (ENTITY::DOES_ENTITY_EXIST(selectedPlayer))
	{
		const int maxPeds = 40;
		Ped ClonedPed[maxPeds];
		auto playerPed = PLAYER::PLAYER_PED_ID();
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(selectedPlayer, 0);
		for (int i = 0; i < maxPeds; i++)
		{
			ClonedPed[i] = PED::CLONE_PED(selectedPlayer, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 1);
			ENTITY::SET_ENTITY_COORDS(ClonedPed[i], coords.x, coords.y, coords.z + 25, 0, 0, 0, 1);
			PED::SET_PED_AS_COP(ClonedPed[i], true);
			Vector3 cloneCoord = ENTITY::GET_ENTITY_COORDS(ClonedPed[i], 0);
			ENTITY::SET_ENTITY_VISIBLE(ClonedPed[i], false, 0);
			g_GameVariables->OwnedExplosionBypass(true);
			FIRE::ADD_OWNED_EXPLOSION(selectedPlayer, cloneCoord, 9, 5.0f, 0, 1, 0.0f);
			g_GameVariables->OwnedExplosionBypass(false);
		}
	}
}
void Features::DeleteVeh()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle pedVeh = PED::GET_VEHICLE_PED_IS_IN(playerPed, FALSE);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(pedVeh, true, true);
	VEHICLE::DELETE_VEHICLE(&pedVeh);
}
void Features::CloneVehicle(int ped)
{
	Vehicle pedVeh = NULL;
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE))
	{
		pedVeh = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
		if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
		{
			Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);
			g_CallbackScript->AddCallback<ModelCallback>(vehicleModelHash, [vehicleModelHash, playerPed, pedVeh] {
				Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
				Vehicle playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition, ENTITY::GET_ENTITY_HEADING(playerPed), *g_GameVariables->is_session_started, false);
				PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, -1);
				int primaryColor, secondaryColor;
				VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
				if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(pedVeh))
				{
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(pedVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, r, g, b);
				}
				if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(pedVeh))
				{
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(pedVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, r, g, b);
				}
				if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModelHash))
				{
					VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
					VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
					for (int i = 0; i <= 24; i++)
					{
						if (i > 16 && i < 23)
							VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
						else
							VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
					}
					int tireSmokeColor[3], pearlescentColor, wheelColor;
					VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
					if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
					{
						int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
						if (convertableState == 0 || convertableState == 3 || convertableState == 5)
							VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
						else
							VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
					}
					for (int i = 0; i <= 3; i++)
					{
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(pedVeh, i));
					}
					for (int i = 0; i <= 11; i++)
					{
						if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
							VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
					}
					if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
					{
						VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
					}
					int neonColor[3];
					VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
					VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
				}
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);

			});
		}
	}
	else
	{
		notifyBlocked((char*)"Player must be vehicle before it can be duplicated.");
	}
}

void Features::TeleportInVehicle(int player)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), FALSE))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
		for (int i = -1; i < 16; i++)
		{
			if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, i);
				return;
			}
		}
	}
	else
	{
		notifyBlocked((char*)"Player is not in a vehicle!");
	}
}

void Features::KickFromVehicle(int player)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), FALSE))
	{
		RequestControlOfEnt(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
		AI::CLEAR_PED_TASKS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
		AI::CLEAR_PED_SECONDARY_TASK(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
	}
	else
	{
		notifyBlocked((char*)"Player is not in a vehicle!");
	}
}








bool Features::noclipallbool = false;
void Features::noclipall()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);

	if (GetAsyncKeyState(VK_KEY_S) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		float xVec = fivef * sin(degToRad(heading)) * -1.0f;
		float yVec = fivef * cos(degToRad(heading));
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);
		pos.x -= xVec, pos.y -= yVec;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_KEY_W) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		float xVec = fivef * sin(degToRad(heading)) * -1.0f;
		float yVec = fivef * cos(degToRad(heading));
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);
		pos.x += xVec, pos.y += yVec;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_KEY_A) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 266)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		float xVec = fivef * sin(degToRad(heading)) * -1.0f;
		float yVec = fivef * cos(degToRad(heading));
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);
		pos.z += xVec, pos.y += yVec;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_KEY_D) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 271)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		float xVec = fivef * sin(degToRad(heading)) * -1.0f;
		float yVec = fivef * cos(degToRad(heading));
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);
		pos.z -= xVec, pos.y -= yVec;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_SHIFT) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendRb)) {
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);
		pos.z -= 0.5;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_SPACE) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendLb)) {
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);
		pos.z += 0.5;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}

}
void Features::RamPlayer()
{
	Hash model = GAMEPLAY::GET_HASH_KEY("INSURGENT");

	g_CallbackScript->AddCallback<ModelCallback>(model, [model] {
		float offset;
		STREAMING::REQUEST_MODEL(model);
		Vector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0.0, -10.0, 0.0);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
		{
			Vector3 dim1, dim2;
			GAMEPLAY::GET_MODEL_DIMENSIONS(model, &dim1, &dim2);

			offset = dim2.y * 1.6;

			Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
			float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0)).z;
			pCoords.x + (dir.x * offset);
			pCoords.y + (dir.y * offset);
			Vehicle veh = VEHICLE::CREATE_VEHICLE(model, pCoords, rot, *g_GameVariables->is_session_started, false);

			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 1000.0);
		}
	});

}



Vector3 get_coords_infront_player(float dist)
{
	//Credits to Sub1To and Mike Rohsoft
	Vector3 r = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	float	heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	r.x += dist * sin(DegreeToRadian(heading)) * -1,
		r.y += dist * cos(DegreeToRadian(heading));
	return r;
}
void Features::AttachObjects(char* object)
{
	Entity t = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
	int bone = -1;
	Vector3 pos = { 0.f, -.26f, .1f };
	Vector3 rot = { 0.f, 0.f, 0.f };
	Hash hash = GAMEPLAY::GET_HASH_KEY(object);
	if (bone != -1 && pos.y == -.26f)
		pos.y = 0.f;
	bone == -1 ? bone = 0 : bone = PED::GET_PED_BONE_INDEX(t, bone);
	Vector3		pos2 = get_coords_infront_player(6.f);
	Object	obj;
	Vector3 empty = { 0 };
	OBJECT::CREATE_OBJECT(hash, pos2.x, pos2.y, pos2.z, true, 1, -1, &obj, true, false, false);	//$("prop_cs_dildo_01")
	ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, t, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
	return;
}

void Features::Teleport1(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 1, 0,0,0 }; //Eclipse
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 1, 0,0,0 }; //Eclipse
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport2(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 6, 0,0,0 }; //West Vinewood
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 6, 0,0,0 }; //West Vinewood
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport3(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 10, 0,0,0 }; //Las Lagunas
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 10, 0,0,0 }; //Las Lagunas
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport4(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 9, 0,0,0 }; //Spanish Ave
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 9, 0,0,0 }; //Spanish Ave
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport5(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 8, 0,0,0 }; //Power St.
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 8, 0,0,0 }; //Power St.
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}


}
void Features::Teleport6(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 7, 0,0,0 }; //Del Perro
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 7, 0,0,0 }; //Del Perro
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport7(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 11, 0,0,0 }; //Milton Rd.
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 11, 0,0,0 }; //Milton Rd.
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport8(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 12, 0,0,0 }; //The Royale
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 12, 0,0,0 }; //The Royale
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport9(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 14, 0,0,0 }; //La Puerta
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 14, 0,0,0 }; //La Puerta
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport10(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 15, 0,0,0 }; //Rockford
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 15, 0,0,0 }; //Rockford
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport11(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 16, 0,0,0 }; //DreamTower
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 16, 0,0,0 }; //DreamTower
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport12(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 18, 0,0,0 }; //San Vitas
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 18, 0,0,0 }; //San Vitas
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}


bool Features::HashGunBool = false;
void Features::HashGun()
{
	float Tmp[6];
	WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), (Vector3*)Tmp);
	if (Tmp[0] != 0 || Tmp[2] != 0 || Tmp[4] != 0) {

		Object ObjAsteroid;
		ENTITY::FREEZE_ENTITY_POSITION(OBJECT::CREATE_OBJECT(4146332269, Tmp[0], Tmp[2], Tmp[4], 1, 1, 0, &ObjAsteroid, true, false, 0) ,1);
	}
}


bool Features::TPToMeBool = false;
void Features::TPToMe()
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true))
	{
		int CurrentPlayersVehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
		Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		if (CurrentPlayersVehicle)
		{
			RequestControlOfEnt(CurrentPlayersVehicle);
			ENTITY::SET_ENTITY_COORDS(CurrentPlayersVehicle, MyCoords.x, MyCoords.y, MyCoords.z + 1.0f, false, false, false, false);

		}
	}
	else
	{
		ScriptEventLog("~r~Player is in no Vehicle!");
	}
	TPToMeBool = false;
}



void Features::Teleport13(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 20, 0,0,0 }; //Vespucci Blvd
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	else
	{
		DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 20, 0,0,0 }; //Vespucci Blvd
		Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
	}

}
void Features::Teleport14(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 21, 0,0,0 }; //Cougar Ave
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 21, 0,0,0 }; //Cougar Ave
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
}
void Features::Teleport15(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 22, 0,0,0 }; //Prosperity St.
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 22, 0,0,0 }; //Prosperity St.
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
}
void Features::Teleport16(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 35, 0,0,0 }; //Weazel Plaza
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 35, 0,0,0 }; //Weazel Plaza
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
}






const char* Features::Name = "NULL";
const char* Features::RID = "NULL";
const char* Features::GodeModeInfo = "NULL";
int Features::Wanted = 0;
const char* Features::Street = "NULL";
const char* Features::Zone = "NULL";
const char* Features::Veh = "NULL";
const char* Features::Speeed = "NULL";
float Features::armorper;
bool Features::UpdateInfo = false;
int timeforupdate;

void Features::UpdatePlayerList()
{
	
}









bool  Features::piggybackbool = false;
void Features::piggyback()
{
#define playerPed2 PLAYER::PLAYER_PED_ID()
	const char* anim = "mini@prostitutes@sexnorm_veh";
	const char* animID = "bj_loop_male";
	int playerClone = PED::CLONE_PED(playerPed2, 1, 1, 1);
	ENTITY::SET_ENTITY_INVINCIBLE(playerClone, true);
	STREAMING::REQUEST_ANIM_DICT2(anim);
	AI::TASK_PLAY_ANIM2(playerClone, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	ENTITY::ATTACH_ENTITY_TO_ENTITY(playerClone, playerPed2, 0.059999998658895f, 0.0f, -0.25f, 0.0f, 0.0f, 0.0f, 1, 1, 0, 0, 2, 1, 1);
	Big::SYSTEM::WAIT(5000);
	piggybackbool = false;
}
void Features::Teleport17(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 87, 0,0,0 }; //Del Perro Office
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 87, 0,0,0 }; //Del Perro Office
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
}
void Features::Teleport18(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 88, 0,0,0 }; //Maze Bank West
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 88, 0,0,0 }; //Maze Bank West
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
}
void Features::Teleport19(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 89, 0,0,0 }; //Arcadius Office
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 89, 0,0,0 }; //Arcadius Office
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
}
void Features::Teleport20(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[9] = { TELEPORT_AP, i, 1, -1, 1, 90, 0,0,0 }; //Arcadius Office
			Hooks::TriggerScriptEvent(1, args, 9, 1 << i);
		}
		return;
	}
	DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, 90, 0,0,0 }; //Arcadius Office
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
}

void Features::TeleportCustom(int place)
{
	DWORD64 args[9] = { TELEPORT_AP, g_SelectedPlayer, 1, -1, 1, place, 0,0,0 }; //Custom
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
}
bool Features::Spam[32];
bool Features::SoundSpamAll;
void Features::DoSoundSpam(int player, bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[3] = { SOUND_SPAM, i, 7 };
			Hooks::TriggerScriptEvent(1, args, 3, 1 << i);
		}
		return;
	}
	DWORD64 args[3] = { SOUND_SPAM, player, 7 };
	Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
}
bool Features::Forcefield = false;
bool Features::RemoteOTRBool[32];
bool Features::RemoteOTRAll;
void Features::RemoteOTR(int target)
{
	int unk1 = NETWORK::GET_NETWORK_TIME();
	int unk2 = NETWORK::GET_NETWORK_TIME() + (60000 * 59);
	int unk6 = globalHandle(1626536).At(target, 603).At(529).As<int>();
	DWORD64 args[7] = { 1848739240, target, unk2, unk1, 1, 1, unk6 };
	Hooks::TriggerScriptEvent(1, args, 7, 1 << target);
	if (!Features::RemoteOTRBool)
	{
		int unk1 = NETWORK::GET_NETWORK_TIME();
		unk2 = NETWORK::GET_NETWORK_TIME() + 0;
	    int unk6 = globalHandle(1626536).At(target, 603).At(529).As<int>();
		DWORD64 args[7] = { 1848739240, target, unk2, unk1, 1, 1, unk6 };
		Hooks::TriggerScriptEvent(1, args, 7, 1 << target);
	}
}

void Features::SaveRID(std::string name, char* rockstarid)
{
	//auto sd = skCrypt("APPDATA");
	//std::string ad = getenv(sd);
	//sd.clear();

	//std::string folderpath = std::string(ad) + ".\\Monop0l\\RIDs\\";

	//Ini* settingsIni = new Ini(std::string(ad) + ".\\Monop0l\\RIDs\\" + name + ".ini");

	//if (!std::filesystem::exists(folderpath.c_str()))
	//{
	//	std::filesystem::create_directory(folderpath.c_str());
	//}
	//// Title Rect //
	//settingsIni->WriteString(rockstarid, "Saved RID", name + std::string("'s Rockstar ID"));

	//delete settingsIni;

}


bool Features::VehSpamCrashBool = false;
void Features::VehSpamCrash(bool toggle)
{
		int excludeMe = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
		if (excludeMe > 0 && excludeMe != PLAYER::PLAYER_PED_ID())
		{
			int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
			Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("CARGOPLANE"));
			Vehicle zentorno = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("CARGOPLANE"), Ocoords, 0, *g_GameVariables->is_session_started, 0);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(zentorno);
			VEHICLE::SET_VEHICLE_IS_STOLEN(zentorno, 0);
			ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			DECORATOR::DECOR_SET_INT(zentorno, (char*)"MPBitset", 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(zentorno);


			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("kosatka"));
			Vehicle ddd = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("kosatka"), Ocoords, 0, *g_GameVariables->is_session_started, 0);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(ddd);
			VEHICLE::SET_VEHICLE_IS_STOLEN(ddd, 0);
			ENTITY::SET_ENTITY_INVINCIBLE(ddd, 0);
			DECORATOR::DECOR_SET_INT(ddd, (char*)"MPBitset", 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ddd);

	}
}


void Features::ForceDisappear()
{
	int iVar2 = globalHandle(2448723).At(4279).At(353).As<int>();
	int param4 = globalHandle(1573351).At(228).At(iVar2, 4).As<int>();
	int param3 = globalHandle(1573351).At(228).At(iVar2, 4).At(1).As<int>();
	int param6 = globalHandle(1573351).At(228).At(iVar2, 4).At(2).As<int>();
	DWORD64 args[6] = { -77616667, g_SelectedPlayer, param3, param4, 1, param6 };
	Hooks::TriggerScriptEvent(1, args, 6, 1 << g_SelectedPlayer);//2007171053
}

void Features::BruteForceWeaponAddons(Ped ped, Hash weaponHash)
{
	const char* weaponAddons[] = { "COMPONENT_AT_SCOPE_MACRO" ,"COMPONENT_AT_SCOPE_MACRO_02" ,"COMPONENT_AT_SCOPE_SMALL" ,"COMPONENT_AT_SCOPE_SMALL_02" ,"COMPONENT_AT_SCOPE_MEDIUM" ,"COMPONENT_AT_SCOPE_LARGE" ,"COMPONENT_AT_SCOPE_MAX" ,"COMPONENT_AT_RAILCOVER_01" ,"COMPONENT_AT_AR_AFGRIP" ,"COMPONENT_AT_PI_FLSH" ,"COMPONENT_AT_AR_FLSH" ,"COMPONENT_PISTOL_CLIP_02" ,"COMPONENT_COMBATPISTOL_CLIP_02" ,"COMPONENT_APPISTOL_CLIP_02" ,"COMPONENT_MICROSMG_CLIP_02" ,"COMPONENT_SMG_CLIP_02" ,"COMPONENT_ASSAULTRIFLE_CLIP_02" ,"COMPONENT_CARBINERIFLE_CLIP_02" ,"COMPONENT_ADVANCEDRIFLE_CLIP_02" ,"COMPONENT_MG_CLIP_02" ,"COMPONENT_COMBATMG_CLIP_02" ,"COMPONENT_ASSAULTSHOTGUN_CLIP_02" ,"COMPONENT_PISTOL50_CLIP_02" ,"COMPONENT_ASSAULTSMG_CLIP_02" ,"COMPONENT_SNSPISTOL_CLIP_02" ,"COMPONENT_COMBATPDW_CLIP_02" ,"COMPONENT_HEAVYPISTOL_CLIP_02" ,"COMPONENT_SPECIALCARBINE_CLIP_02" ,"COMPONENT_BULLPUPRIFLE_CLIP_02" ,"COMPONENT_VINTAGEPISTOL_CLIP_02" ,"COMPONENT_MARKSMANRIFLE_CLIP_02" ,"COMPONENT_HEAVYSHOTGUN_CLIP_02" ,"COMPONENT_GUSENBERG_CLIP_02"};
	//const char* weaponAddons[] = { "COMPONENT_KNUCKLE_VARMOD_BAS","COMPONENT_KNUCKLE_VARMOD_PIM","COMPONENT_KNUCKLE_VARMOD_BALLA","COMPONENT_KNUCKLE_VARMOD_DOLLA","COMPONENT_KNUCKLE_VARMOD_DIAMON","COMPONENT_KNUCKLE_VARMOD_HAT","COMPONENT_KNUCKLE_VARMOD_LOV","COMPONENT_KNUCKLE_VARMOD_PLAYE","COMPONENT_KNUCKLE_VARMOD_KIN","COMPONENT_KNUCKLE_VARMOD_VAGO","COMPONENT_SWITCHBLADE_VARMOD_BAS","COMPONENT_SWITCHBLADE_VARMOD_VAR","COMPONENT_SWITCHBLADE_VARMOD_VAR","COMPONENT_PISTOL_CLIP_0","COMPONENT_PISTOL_CLIP_0","COMPONENT_AT_PI_FLS","COMPONENT_AT_PI_SUPP_0","COMPONENT_PISTOL_VARMOD_LUX","COMPONENT_COMBATPISTOL_CLIP_0","COMPONENT_COMBATPISTOL_CLIP_0","COMPONENT_AT_PI_FLS","COMPONENT_AT_PI_SUP","COMPONENT_COMBATPISTOL_VARMOD_LOWRIDE","COMPONENT_APPISTOL_CLIP_0","COMPONENT_APPISTOL_CLIP_0","COMPONENT_AT_PI_FLS","COMPONENT_AT_PI_SUP","COMPONENT_APPISTOL_VARMOD_LUX","COMPONENT_PISTOL50_CLIP_0","COMPONENT_PISTOL50_CLIP_0","COMPONENT_AT_PI_FLS","COMPONENT_AT_AR_SUPP_0","COMPONENT_PISTOL50_VARMOD_LUX","COMPONENT_REVOLVER_VARMOD_BOS","COMPONENT_REVOLVER_VARMOD_GOO","COMPONENT_REVOLVER_CLIP_0","COMPONENT_SNSPISTOL_CLIP_0","COMPONENT_SNSPISTOL_CLIP_0","COMPONENT_SNSPISTOL_VARMOD_LOWRIDE","COMPONENT_HEAVYPISTOL_CLIP_0","COMPONENT_HEAVYPISTOL_CLIP_0","COMPONENT_AT_PI_FLS","COMPONENT_AT_PI_SUP","COMPONENT_HEAVYPISTOL_VARMOD_LUX","COMPONENT_REVOLVER_MK2_CLIP_0","COMPONENT_REVOLVER_MK2_CLIP_TRACE","COMPONENT_REVOLVER_MK2_CLIP_INCENDIAR","COMPONENT_REVOLVER_MK2_CLIP_HOLLOWPOIN","COMPONENT_REVOLVER_MK2_CLIP_FM","COMPONENT_AT_SIGHT","COMPONENT_AT_SCOPE_MACRO_MK","COMPONENT_AT_PI_FLS","COMPONENT_AT_PI_COMP_0","COMPONENT_SNSPISTOL_MK2_CLIP_0","COMPONENT_SNSPISTOL_MK2_CLIP_0","COMPONENT_SNSPISTOL_MK2_CLIP_TRACE","COMPONENT_SNSPISTOL_MK2_CLIP_INCENDIAR","COMPONENT_SNSPISTOL_MK2_CLIP_HOLLOWPOIN","COMPONENT_SNSPISTOL_MK2_CLIP_FM","COMPONENT_AT_PI_FLSH_0","COMPONENT_AT_PI_RAIL_0","COMPONENT_AT_PI_SUPP_0","COMPONENT_AT_PI_COMP_0","COMPONENT_PISTOL_MK2_CLIP_0","COMPONENT_PISTOL_MK2_CLIP_0","COMPONENT_PISTOL_MK2_CLIP_TRACE","COMPONENT_PISTOL_MK2_CLIP_INCENDIAR","COMPONENT_PISTOL_MK2_CLIP_HOLLOWPOIN","COMPONENT_PISTOL_MK2_CLIP_FM","COMPONENT_AT_PI_RAI","COMPONENT_AT_PI_FLSH_0","COMPONENT_AT_PI_SUPP_0","COMPONENT_AT_PI_COM","COMPONENT_VINTAGEPISTOL_CLIP_0","COMPONENT_VINTAGEPISTOL_CLIP_0","COMPONENT_AT_PI_SUP","COMPONENT_RAYPISTOL_VARMOD_XMAS1","COMPONENT_MICROSMG_CLIP_0","COMPONENT_MICROSMG_CLIP_0","COMPONENT_AT_PI_FLS","COMPONENT_AT_SCOPE_MACR","COMPONENT_AT_AR_SUPP_0","COMPONENT_MICROSMG_VARMOD_LUX","COMPONENT_SMG_CLIP_0","COMPONENT_SMG_CLIP_0","COMPONENT_SMG_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_SCOPE_MACRO_0","COMPONENT_AT_PI_SUP","COMPONENT_SMG_VARMOD_LUX","COMPONENT_ASSAULTSMG_CLIP_0","COMPONENT_ASSAULTSMG_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_SCOPE_MACR","COMPONENT_AT_AR_SUPP_0","COMPONENT_ASSAULTSMG_VARMOD_LOWRIDE","COMPONENT_MINISMG_CLIP_0","COMPONENT_MINISMG_CLIP_0","COMPONENT_SMG_MK2_CLIP_0","COMPONENT_SMG_MK2_CLIP_0","COMPONENT_SMG_MK2_CLIP_TRACE","COMPONENT_SMG_MK2_CLIP_INCENDIAR","COMPONENT_SMG_MK2_CLIP_HOLLOWPOIN","COMPONENT_SMG_MK2_CLIP_FM","COMPONENT_AT_AR_FLS","COMPONENT_AT_SIGHTS_SM","COMPONENT_AT_SCOPE_MACRO_02_SMG_MK","COMPONENT_AT_SCOPE_SMALL_SMG_MK","COMPONENT_AT_PI_SUP","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_SB_BARREL_0","COMPONENT_AT_SB_BARREL_0","COMPONENT_MACHINEPISTOL_CLIP_0","COMPONENT_MACHINEPISTOL_CLIP_0","COMPONENT_MACHINEPISTOL_CLIP_0","COMPONENT_AT_PI_SUP","COMPONENT_COMBATPDW_CLIP_0","COMPONENT_COMBATPDW_CLIP_0","COMPONENT_COMBATPDW_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_AR_AFGRI","COMPONENT_AT_SCOPE_SMAL","COMPONENT_AT_AR_FLS","COMPONENT_AT_SR_SUP","COMPONENT_PUMPSHOTGUN_VARMOD_LOWRIDE","COMPONENT_SAWNOFFSHOTGUN_VARMOD_LUX","COMPONENT_ASSAULTSHOTGUN_CLIP_0","COMPONENT_ASSAULTSHOTGUN_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_AR_SUP","COMPONENT_AT_AR_AFGRI","COMPONENT_AT_AR_FLS","COMPONENT_AT_AR_SUPP_0","COMPONENT_AT_AR_AFGRI","COMPONENT_PUMPSHOTGUN_MK2_CLIP_0","COMPONENT_PUMPSHOTGUN_MK2_CLIP_INCENDIAR","COMPONENT_PUMPSHOTGUN_MK2_CLIP_ARMORPIERCIN","COMPONENT_PUMPSHOTGUN_MK2_CLIP_HOLLOWPOIN","COMPONENT_PUMPSHOTGUN_MK2_CLIP_EXPLOSIV","COMPONENT_AT_SIGHT","COMPONENT_AT_SCOPE_MACRO_MK","COMPONENT_AT_SCOPE_SMALL_MK","COMPONENT_AT_AR_FLS","COMPONENT_AT_SR_SUPP_0","COMPONENT_AT_MUZZLE_0","COMPONENT_HEAVYSHOTGUN_CLIP_0","COMPONENT_HEAVYSHOTGUN_CLIP_0","COMPONENT_HEAVYSHOTGUN_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_AR_SUPP_0","COMPONENT_AT_AR_AFGRI","COMPONENT_ASSAULTRIFLE_CLIP_0","COMPONENT_ASSAULTRIFLE_CLIP_0","COMPONENT_ASSAULTRIFLE_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_SCOPE_MACR","COMPONENT_AT_AR_SUPP_0","COMPONENT_AT_AR_AFGRI","COMPONENT_ASSAULTRIFLE_VARMOD_LUX","COMPONENT_CARBINERIFLE_CLIP_0","COMPONENT_CARBINERIFLE_CLIP_0","COMPONENT_CARBINERIFLE_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_SCOPE_MEDIU","COMPONENT_AT_AR_SUP","COMPONENT_AT_AR_AFGRI","COMPONENT_CARBINERIFLE_VARMOD_LUX","COMPONENT_ADVANCEDRIFLE_CLIP_0","COMPONENT_ADVANCEDRIFLE_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_SCOPE_SMAL","COMPONENT_AT_AR_SUP","COMPONENT_ADVANCEDRIFLE_VARMOD_LUX","COMPONENT_SPECIALCARBINE_CLIP_0","COMPONENT_SPECIALCARBINE_CLIP_0","COMPONENT_SPECIALCARBINE_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_SCOPE_MEDIU","COMPONENT_AT_AR_SUPP_0","COMPONENT_AT_AR_AFGRI","COMPONENT_SPECIALCARBINE_VARMOD_LOWRIDE","COMPONENT_BULLPUPRIFLE_CLIP_0","COMPONENT_BULLPUPRIFLE_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_SCOPE_SMAL","COMPONENT_AT_AR_SUP","COMPONENT_AT_AR_AFGRI","COMPONENT_BULLPUPRIFLE_VARMOD_LO","COMPONENT_BULLPUPRIFLE_MK2_CLIP_0","COMPONENT_BULLPUPRIFLE_MK2_CLIP_0","COMPONENT_BULLPUPRIFLE_MK2_CLIP_TRACE","COMPONENT_BULLPUPRIFLE_MK2_CLIP_INCENDIAR","COMPONENT_BULLPUPRIFLE_MK2_CLIP_ARMORPIERCIN","COMPONENT_BULLPUPRIFLE_MK2_CLIP_FM","COMPONENT_AT_AR_FLS","COMPONENT_AT_SIGHT","COMPONENT_AT_SCOPE_MACRO_02_MK","COMPONENT_AT_SCOPE_SMALL_MK","COMPONENT_AT_BP_BARREL_0","COMPONENT_AT_BP_BARREL_0","COMPONENT_AT_AR_SUP","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_AR_AFGRIP_0","COMPONENT_SPECIALCARBINE_MK2_CLIP_0","COMPONENT_SPECIALCARBINE_MK2_CLIP_0","COMPONENT_SPECIALCARBINE_MK2_CLIP_TRACE","COMPONENT_SPECIALCARBINE_MK2_CLIP_INCENDIAR","COMPONENT_SPECIALCARBINE_MK2_CLIP_ARMORPIERCIN","COMPONENT_SPECIALCARBINE_MK2_CLIP_FM","COMPONENT_AT_AR_FLS","COMPONENT_AT_SIGHT","COMPONENT_AT_SCOPE_MACRO_MK","COMPONENT_AT_SCOPE_MEDIUM_MK","COMPONENT_AT_AR_SUPP_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_AR_AFGRIP_0","COMPONENT_AT_SC_BARREL_0","COMPONENT_AT_SC_BARREL_0","COMPONENT_ASSAULTRIFLE_MK2_CLIP_0","COMPONENT_ASSAULTRIFLE_MK2_CLIP_0","COMPONENT_ASSAULTRIFLE_MK2_CLIP_TRACE","COMPONENT_ASSAULTRIFLE_MK2_CLIP_INCENDIAR","COMPONENT_ASSAULTRIFLE_MK2_CLIP_ARMORPIERCIN","COMPONENT_ASSAULTRIFLE_MK2_CLIP_FM","COMPONENT_AT_AR_AFGRIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_SIGHT","COMPONENT_AT_SCOPE_MACRO_MK","COMPONENT_AT_SCOPE_MEDIUM_MK","COMPONENT_AT_AR_SUPP_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_AR_BARREL_0","COMPONENT_AT_AR_BARREL_0","COMPONENT_CARBINERIFLE_MK2_CLIP_0","COMPONENT_CARBINERIFLE_MK2_CLIP_0","COMPONENT_CARBINERIFLE_MK2_CLIP_TRACE","COMPONENT_CARBINERIFLE_MK2_CLIP_INCENDIAR","COMPONENT_CARBINERIFLE_MK2_CLIP_ARMORPIERCIN","COMPONENT_CARBINERIFLE_MK2_CLIP_FM","COMPONENT_AT_AR_AFGRIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_SIGHT","COMPONENT_AT_SCOPE_MACRO_MK","COMPONENT_AT_SCOPE_MEDIUM_MK","COMPONENT_AT_AR_SUP","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_CR_BARREL_0","COMPONENT_AT_CR_BARREL_0","COMPONENT_COMPACTRIFLE_CLIP_0","COMPONENT_COMPACTRIFLE_CLIP_0","COMPONENT_COMPACTRIFLE_CLIP_0","COMPONENT_MG_CLIP_0","COMPONENT_MG_CLIP_0","COMPONENT_AT_SCOPE_SMALL_0","COMPONENT_MG_VARMOD_LOWRIDE","COMPONENT_COMBATMG_CLIP_0","COMPONENT_COMBATMG_CLIP_0","COMPONENT_AT_SCOPE_MEDIU","COMPONENT_AT_AR_AFGRI","COMPONENT_COMBATMG_VARMOD_LOWRIDE","COMPONENT_COMBATMG_MK2_CLIP_0","COMPONENT_COMBATMG_MK2_CLIP_0","COMPONENT_COMBATMG_MK2_CLIP_TRACE","COMPONENT_COMBATMG_MK2_CLIP_INCENDIAR","COMPONENT_COMBATMG_MK2_CLIP_ARMORPIERCIN","COMPONENT_COMBATMG_MK2_CLIP_FM","COMPONENT_AT_AR_AFGRIP_0","COMPONENT_AT_SIGHT","COMPONENT_AT_SCOPE_SMALL_MK","COMPONENT_AT_SCOPE_MEDIUM_MK","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MG_BARREL_0","COMPONENT_AT_MG_BARREL_0","COMPONENT_GUSENBERG_CLIP_0","COMPONENT_GUSENBERG_CLIP_0","COMPONENT_SNIPERRIFLE_CLIP_0","COMPONENT_AT_AR_SUPP_0","COMPONENT_AT_SCOPE_LARG","COMPONENT_AT_SCOPE_MA","COMPONENT_SNIPERRIFLE_VARMOD_LUX","COMPONENT_HEAVYSNIPER_CLIP_0","COMPONENT_AT_SCOPE_LARG","COMPONENT_AT_SCOPE_MA","COMPONENT_MARKSMANRIFLE_MK2_CLIP_0","COMPONENT_MARKSMANRIFLE_MK2_CLIP_0","COMPONENT_MARKSMANRIFLE_MK2_CLIP_TRACE","COMPONENT_MARKSMANRIFLE_MK2_CLIP_INCENDIAR","COMPONENT_MARKSMANRIFLE_MK2_CLIP_ARMORPIERCIN","COMPONENT_MARKSMANRIFLE_MK2_CLIP_FM","COMPONENT_AT_SIGHT","COMPONENT_AT_SCOPE_MEDIUM_MK","COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM_MK","COMPONENT_AT_AR_FLS","COMPONENT_AT_AR_SUP","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MRFL_BARREL_0","COMPONENT_AT_MRFL_BARREL_0","COMPONENT_AT_AR_AFGRIP_0","COMPONENT_HEAVYSNIPER_MK2_CLIP_0","COMPONENT_HEAVYSNIPER_MK2_CLIP_0","COMPONENT_HEAVYSNIPER_MK2_CLIP_INCENDIAR","COMPONENT_HEAVYSNIPER_MK2_CLIP_ARMORPIERCIN","COMPONENT_HEAVYSNIPER_MK2_CLIP_FM","COMPONENT_HEAVYSNIPER_MK2_CLIP_EXPLOSIV","COMPONENT_AT_SCOPE_LARGE_MK","COMPONENT_AT_SCOPE_MA","COMPONENT_AT_SCOPE_N","COMPONENT_AT_SCOPE_THERMA","COMPONENT_AT_SR_SUPP_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_MUZZLE_0","COMPONENT_AT_SR_BARREL_0","COMPONENT_AT_SR_BARREL_0","COMPONENT_MARKSMANRIFLE_CLIP_0","COMPONENT_MARKSMANRIFLE_CLIP_0","COMPONENT_AT_SCOPE_LARGE_FIXED_ZOO","COMPONENT_AT_AR_FLS","COMPONENT_AT_AR_SUP","COMPONENT_AT_AR_AFGRI","COMPONENT_MARKSMANRIFLE_VARMOD_LUX","COMPONENT_GRENADELAUNCHER_CLIP_0","COMPONENT_AT_AR_FLS","COMPONENT_AT_AR_AFGRI","COMPONENT_AT_SCOPE_SMAL" };
	for (const char* addonHash : weaponAddons)
	{
		Hash hash = GAMEPLAY::GET_HASH_KEY(addonHash);
		if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weaponHash, hash))
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, hash);
	}
	const char* silencers[] = { "COMPONENT_AT_PI_SUPP","COMPONENT_AT_PI_SUPP_02","COMPONENT_AT_AR_SUPP","COMPONENT_AT_SR_SUPP","COMPONENT_AT_AR_SUPP_02"};
		for (const char* silencerHash : silencers)
		{
			Hash hash = GAMEPLAY::GET_HASH_KEY(silencerHash);
			if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weaponHash, hash)) {
				if (weaponHash != WeaponAdvancedRifle && WEAPON::GET_WEAPONTYPE_GROUP(weaponHash) != ControlSelectWeaponShotgun)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, hash);
			}
		}
		Hash hashes = GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02");
		if (weaponHash == WeaponSniperRifle || weaponHash == WeaponMicroSMG)
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, hashes);
		std::vector<Hash> pistolMk2{
		1329061674, 2396306288, 1140676955, 1709866683, 568543123, 2467084625
		};
		std::vector<Hash> smgMk2{
			190476639, 2076495324, 2681951826, 3842157419, 1038927834, 1303784126, 2774849419, 966612367
		};
		std::vector<Hash> assltRifleMk2{
			1675665560, 2640679034, 2076495324, 1108334355, 77277509, 3328927042, 2805810788, 1303784126, 1447477866, 3115408816
		};
		std::vector<Hash> carbineRifleMk2{
			1141059345, 2640679034, 2076495324, 1108334355, 77277509, 3328927042, 2205435306, 1303784126, 2335983627, 3663056191
		};
		std::vector<Hash> combatMgMk2{
			1475288264, 2640679034, 1108334355, 1060929921, 3328927042, 1303784126, 3051509595, 3607349581
		};
		std::vector<Hash> heavySniperMk2{
			2313935527, 2193687427, 3159677559, 3061846192, 776198721, 2890063729, 1764221345, 277524638, 1815270123
		};
		std::vector<Hash> WeaponHash{
			0xBFE256D4, 0x78A97CD0, 0xDBBD7280, 0x394F415C, 0xFAD1F1C9, 0xA914799
		};

		for (Hash hash : pistolMk2)
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL_MK2"), hash);

		for (Hash hash : smgMk2)
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_SMG_MK2"), hash);

		for (Hash hash : assltRifleMk2)
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"), hash);

		for (Hash hash : carbineRifleMk2)
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"), hash);

		for (Hash hash : combatMgMk2)
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG_MK2"), hash);

		for (Hash hash : heavySniperMk2)
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"), hash);

		for (Hash hash : WeaponHash)
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
}
void Features::GentleKick(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[2] = { GENTLE_KCIK, 0 };
			Hooks::TriggerScriptEvent(1, args, 2, 1 << i);
		}
		return;
	}

	DWORD64 args[2] = { GENTLE_KCIK, 0 };
	Hooks::TriggerScriptEvent(1, args, 2, 1 << g_SelectedPlayer);
}
bool Features::BlindEyeBool[32];
bool Features::BlindEyeAll;
void Features::BlindEye(int player)
{
	int time = NETWORK::GET_NETWORK_TIME() + (60000 * 59);
	int biggey = globalHandle(1626536).At(player, 603).At(529).As<int>();
	int biggeya = globalHandle(2528542).At(4549).As<int>();
	DWORD64 args[7] = { -1635856102, player, biggeya, 0,time, 0, biggey };
	Hooks::TriggerScriptEvent(1, args, 7, 1 << player);
}
bool Features::RemoteNeverWanted[32];
bool Features::NeverWantedAll;
void Features::RemoveWanted(int player)
{

	uint64_t args[3] = { REMOVE_WANTED_LEVEL, player, globalHandle(1630317).At(player, 595).At(506).As<int>() };
	Hooks::TriggerScriptEvent(1, args, 3, 1 << player);


}

int offradardplrr = 1000;
bool Features::ShowAllPlayerRadarBool;
void Features::ShowAllPlayerRadar(bool toggle)
{
	if (toggle)
	{
		std::uint64_t args[7] = { OTR, g_SelectedPlayer, NETWORK::GET_NETWORK_TIME() + (offradardplrr * 59) + 1, NETWORK::GET_NETWORK_TIME(), 1, 1, globalHandle(1628237 + 1 + g_SelectedPlayer * 615 + 533).As<std::uint64_t>() };
		Hooks::TriggerScriptEvent(1, args, 7, 1 << g_SelectedPlayer);
	}
	else
	{
		std::uint64_t args[7] = { OTR, g_SelectedPlayer, NETWORK::GET_NETWORK_TIME() + (0) + 1, NETWORK::GET_NETWORK_TIME(), 0, 0, globalHandle(1628237 + 1 + g_SelectedPlayer * 615 + 533).As<std::uint64_t>() };
		Hooks::TriggerScriptEvent(1, args, 7, 1 << g_SelectedPlayer);

	}
}

bool Features::CrashLobbyBool;
void Features::CrashLobby(bool toggle)
{
	for (int i = 0; i < 32; i++)
	{
		int excludeMe = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		if (excludeMe > 0 && excludeMe != PLAYER::PLAYER_PED_ID())
		{
			int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
			Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("CARGOPLANE"));
			Vehicle zentorno = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("CARGOPLANE"), Ocoords, 0, *g_GameVariables->is_session_started, 0);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(zentorno);
			VEHICLE::SET_VEHICLE_IS_STOLEN(zentorno, 0);
			ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			DECORATOR::DECOR_SET_INT(zentorno, (char*)"MPBitset", 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(zentorno);


			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("kosatka"));
			Vehicle ddd = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("kosatka"), Ocoords, 0, *g_GameVariables->is_session_started, 0);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(ddd);
			VEHICLE::SET_VEHICLE_IS_STOLEN(ddd, 0);
			ENTITY::SET_ENTITY_INVINCIBLE(ddd, 0);
			DECORATOR::DECOR_SET_INT(ddd, (char*)"MPBitset", 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ddd);



		}

	}
}




int tictac = 0;
int tictac2 = 0;
bool Features::RPLooperBool;
void Features::RPLooper(bool toggle)
{
	if (toggle)
	{
		tictac++;
		if (tictac > 5) {
			Memory::set_value<int>({ 0x08, 0x10C8, 0x868 }, 5);
			tictac2++;
			if (tictac2 > 5) {
				Memory::set_value<int>({ 0x08, 0x10C8, 0x868 }, 0);
				tictac = 0;
				tictac2 = 0;
			}
		}
	}
	else
	{
		Memory::set_value<int>({ 0x08, 0x10C8, 0x868 }, false);
	}
}

bool Features::SendToJobBool = false;
void Features::SendToJob()
{
	DWORD64 args[2] = { SEND_TO_MISSION, g_SelectedPlayer };
	Hooks::TriggerScriptEvent(1, args, 2, 1 << g_SelectedPlayer);

	Features::SendToJobBool == false;
}


bool Features::CEOKickBool;
void Features::CEOKick()
{
	DWORD64 args[4] = { CEO_KICK, g_SelectedPlayer, 0, 0 };
	Hooks::TriggerScriptEvent(1, args, 4, 1 << g_SelectedPlayer);
}

void Features::CEOBan(bool all)
{
	if (all)
	{
		for (int i = 0; i < 32; i++)
		{
			DWORD64 args[3] = { CEO_BAN, i, 1 };
			Hooks::TriggerScriptEvent(1, args, 3, 1 << i);//2007171053
		}
		return;
	}
	DWORD64 args[3] = { CEO_BAN, g_SelectedPlayer, 1 };
	Hooks::TriggerScriptEvent(1, args, 3, 1 << g_SelectedPlayer);//2007171053
}


bool Features::KickPlayerBool = false;
void Features::KickPlayer()
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
	Features::KickPlayerBool = false;
}






void Features::InfiniteLoading()
{
	DWORD64 args[9] = { UNLIMITED_LOADING, g_SelectedPlayer, 0, -1, 1, 0, 0,0,0 }; //Custom
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);
}

void Features::TrollMessage()
{
	DWORD64 args[3] = { MESSAGE_SPAM, g_SelectedPlayer, 1000000000 }; //Eclipse
	Hooks::TriggerScriptEvent(1, args, 3, 1 << g_SelectedPlayer);
}
bool Features::AddSpam = false;
bool Features::ToggledOn = false;
bool Features::ToggledOff = false;
void Features::BankedMoney()
{
	for (int i = 0; i < 32; i++)
	{
		DWORD64 args[14] = { MESSAGE_SPAM, g_SelectedPlayer, -1695772783, 1500000000 };
		Hooks::TriggerScriptEvent(1, args, 14, 1 << g_SelectedPlayer);
	}
}
bool Features::RemoveSpam = false;
void Features::StolenMoney()
{
	for (int i = 0; i < 32; i++)
	{
		DWORD64 args[14] = { MESSAGE_SPAM, g_SelectedPlayer, 1207028646, 1500000000 };
		Hooks::TriggerScriptEvent(1, args, 14, 1 << g_SelectedPlayer);
	}
}
static const char* ssss[] = {
	"TICK_ATTVAN", "R2P_ACCT", "R2P_JOINT", "R2P_LEAVT", "R2P_DISQT", "RCE_EXP_4", "GHO_START", "TICK_CHOPPER",
	"TICK_EYE", "TICK_RAPEL", "TICK_RIVAL", "TICK_TAKEN", "IMPEX_HIPR_WRK", "IMPEX_HIPR_NOL", "FM_GDM_TK1",
	"TICK_TC_BANK", "TICK_TC_STOL", "TICK_TC_REMO", "ACD_TICKS", "ACD_TSC0"
};
bool Features::BannerSpam = false;
void Features::BannerMessage()
{
	uint64_t args[3] = { SHOW_BANNER1, g_SelectedPlayer, SHOW_BANNER2 };
	Hooks::TriggerScriptEvent(1, args, 3, 1 << g_SelectedPlayer);

	uint64_t args3[3] = { SHOW_BANNER1, g_SelectedPlayer, SHOW_BANNER2 };
	Hooks::TriggerScriptEvent(1, args3, 3, 1 << g_SelectedPlayer);

}

void Features::Invite2Place(int player, int place)
{
	DWORD64 args[3] = { TELEPORT_AP, player, place };
	Hooks::TriggerScriptEvent(1, args, 3, 1 << player);
}

void Features::MessageSpam(int player, std::int64_t message)
{
	int RemoteEventShowMessage = MESSAGE_SPAM;
	DWORD64 args[14] = { RemoteEventShowMessage, player, message };
	Hooks::TriggerScriptEvent(1, args, 14, 1 << player);
}

bool Features::InfiniteAmmoBool = false;
void Features::InfiniteAmmo() {
	Hash cur;
	if (WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &cur, 1))
	{
		if (WEAPON::IS_WEAPON_VALID(cur))
		{
			int maxAmmo;
			if (WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), cur, &maxAmmo))
			{
				WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), cur, maxAmmo);

				maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), cur, 1);
				if (maxAmmo > 0)
					WEAPON::SET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), cur, maxAmmo);
			}
		}
	}
}


bool Features::DisableHUDBool = false;
void Features::DisableHUD(bool toggle) {
	UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
}


bool Features::MaxHeistPayoutBool = false;
void Features::MaxHeistPayout(bool toggle) {
	globalHandle(262145).At(8664).As<int>() = true;
	globalHandle(262145).At(8665).As<int>() = true;
	globalHandle(262145).At(8666).As<int>() = true;
	globalHandle(262145).At(8667).As<int>() = true;
	globalHandle(262145).At(8668).As<int>() = true;

	//262145.f_8663 = 115000 // fleeca bank
	//262145.f_8664 = 400000 //Prison Break
	//262145.f_8665 = 540000 //Humane Labs
	//262145.f_8666 = 404000 //Series A
	//262145.f_8667 = 1000000//Pasific Standard
}


bool Features::ExplodePedBool = false;
void Features::ExplodePed(bool toggle) {
	const int ElementAmount = 10;
	const int ArrSize = ElementAmount * 2 + 2;

	Ped* peds = new Ped[ArrSize];
	peds[0] = ElementAmount;

	int PedFound = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);

	for (int i = 0; i < PedFound; i++)
	{
		int OffsetID = i * 2 + 2;
		RequestControlOfEnt(peds[OffsetID]);
		if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && PLAYER::PLAYER_PED_ID() != peds[OffsetID])
		{
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(peds[OffsetID], false);
			FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 0, 1000.f, true, false, 0.f);
		}
	}
}






bool Features::ExplodeVehicleBool = false;
void Features::ExplodeVehicle(bool toggle) {
	const int ElementAmount = 10;
	const int ArrSize = ElementAmount * 2 + 2;

	Vehicle* vehs = new Vehicle[ArrSize];
	vehs[0] = ElementAmount;
	int VehFound = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);

	for (int i = 0; i < VehFound; i++)
	{
		int OffsetID = i * 2 + 2;
		if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))
		{
			RequestControlOfEnt(vehs[OffsetID]);
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(vehs[OffsetID], false);
			FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 1000.f, true, false, 0.f);
		}
	}
	delete vehs;
}

bool Features::DeleteVehicleBool = false;
void Features::DeleteVehicle(bool toggle) {
	const int ElementAmount = 10;
	const int ArrSize = ElementAmount * 2 + 2;

	Vehicle* vehs = new Vehicle[ArrSize];
	vehs[0] = ElementAmount;
	int VehFound = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);

	for (int i = 0; i < VehFound; i++)
	{
		int OffsetID = i * 2 + 2;
		if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))
		{
			RequestControlOfEnt(vehs[OffsetID]);
			ENTITY::SET_ENTITY_COORDS(vehs[OffsetID], 6400.f, 6400.f, 0.f, false, false, false, false);
		}
	}
	delete vehs;
}



bool Features::ClownWeaponEffectBool = false;
void Features::ClownWeaponEffect(bool toggle) {
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_rcbarry2");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_rcbarry2");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_clown_appears", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}

}

bool Features::BankNoteEffectBool = false;
void Features::BankNoteEffect(bool toggle) {

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_martin1");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_martin1");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_sol1_sniper_impact", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}

}


bool Features::TruckCrashEffectBool = false;
void Features::TruckCrashEffect(bool toggle) {

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_ornate_heist");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_ornate_heist");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_heist_ornate_banknotes", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}

}


bool Features::ElectricWeaponEffectBool = false;
void Features::ElectricWeaponEffect(bool toggle) {

Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_finalec2");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_finalec2");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_finale2_blood_entry", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}












bool Features::particel8bool = false;
void Features::particel8(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_rcbarry1");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_rcbarry1");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_alien_teleport", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}


bool Features::particel9bool = false;
void Features::particel9(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_agencyheistb");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_agencyheistb");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_agency3b_elec_box", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}


bool Features::particel10bool = false;
void Features::particel10(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_fbi5a");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_fbi5a");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_fbi5_ped_water_splash", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}


bool Features::particel11bool = false;
void Features::particel11(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_fbi5a");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_fbi5a");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"water_splash_ped_bubbles", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}


bool Features::particel12bool = false;
void Features::particel12(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_finalec2");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_finalec2");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_finale2_blood_entry", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}


bool Features::particel13bool = false;
void Features::particel13(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_martin1");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_martin1");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_sol1_sniper_impact", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}


bool Features::particel14bool = false;
void Features::particel14(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"core_snow");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"core_snow");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"cs_mich1_spade_dirt_throw", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}


bool Features::particel15bool = false;
void Features::particel15(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_michael2");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_michael2");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_mich2_blood_stab", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}


bool Features::particel16bool = false;
void Features::particel16(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_michael2");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_michael2");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_abattoir_ped_sliced", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}















bool Features::AlienWeaponEffectBool = false;
void Features::AlienWeaponEffect(bool toggle) {

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{


			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_rcbarry1");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_rcbarry1");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_alien_disintegrate", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}
}



bool Features::FireWorkWeaponTwoBool = false;
void Features::FireWorkWeaponTwo(bool toggle) {

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{


			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"proj_xmas_firework");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"proj_xmas_firework");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_firework_xmas_burst_rgw", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}

}


void Features::HeartBeat()
{



}



bool Features::FireWorkWeaponBool = false;
void Features::FireWorkWeapon(bool toggle) {

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (IsPedShooting(playerPed)) {
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_indep_fireworks");
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_indep_fireworks");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD((char*)"scr_indep_firework_trailburst", coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 1.f, 0, 0, 0);
		}
	}

}

bool Features::ExplosiveAmmoFlag = false;
void Features::ExplosiveAmmo() {
	Memory::set_value<uint32_t>({ 8, 0x10C8, 0x1F8 }, Memory::get_value<uint32_t>({ 8, 0x10C8, 0x1F8 }) | (1 << 13));
}

bool Features::ExplosiveAmmoBool = false;
void Features::ExplosiveAmmoo() {
	Memory::set_value<uint32_t>({ 8, 0x10C8, 0x1F8 }, Memory::get_value<uint32_t>({ 8, 0x10C8, 0x1F8 }) | (1 << 11));
}

bool Features::ExplodeAmmoBool = false;
void Features::ExplodeAmmo() {
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (IsPedShooting(playerPed))
	{
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 10.0f, false, false, false);
		}

	}
}


bool Features::WaterShoot = false;
void Features::ShootWater()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (is_ped_shooting(playerPed))
	{
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 13, 10.0f, false, false, false);
		}

	}
}

int Features::ShootCash = 2500;
bool Features::MoneyGunBool = false;
void Features::MoneyGun(bool toggle)
{
	if (IsPedShooting(PLAYER::PLAYER_PED_ID()))
	{
		g_CallbackScript->AddCallback<ModelCallback>(Features::DROPHASH, [] {
			Ped PedID = PLAYER::PLAYER_PED_ID();
			Vector3 pos;
			pos.z + .5f;
			WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PedID, &pos);
			OBJECT::CREATE_AMBIENT_PICKUPP(0xDE78F17E, pos, 0, 2500, Features::DROPHASH, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
			//OBJECT::CREATE_AMBIENT_PICKUP(0x1E9A99F8, pos.x, pos.y, pos.z, 0, Features::ShootCash, 0x9CA6F755, FALSE, TRUE);
		});
	}
	}







bool Features::ShootVehicleBool = false;
void Features::ShootVehicle(bool toggle)
{
	/*Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);
	FLOAT heading = ENTITY::GET_ENTITY_HEADING(playerPed);
	DWORD model = GAMEPLAY::GET_HASH_KEY(selectShootVeh);
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = RotationToDirection(rot);
	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	float spawnDistance = get_distance(&camPosition, &playerPosition);
	spawnDistance += 5;
	Vector3 spawnPosition = add(&camPosition, &multiply(&dir, spawnDistance));

	if (bPlayerExists)
	{
		if (PED::IS_PED_SHOOTING(playerPed))
		{
			Vector3 playerOffset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0, 5, 0);
			if (PED::IS_PED_ON_FOOT(playerPed))
			{
				STREAMING::REQUEST_MODEL(model);
				g_CallbackScript->AddCallback<ModelCallback>(model, [model, spawnPosition, heading] {

					Vehicle veh = VEHICLE::CREATE_VEHICLE(model, spawnPosition, heading, *g_GameVariables->is_session_started, 0);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 120.0);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
					ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
				});

			}
		}
	}
	*/
}


bool Features::RPGunBool = false;
void Features::RPGun(bool toggle)
{
	if (IsPedShooting(PLAYER::PLAYER_PED_ID()))
	{
		g_CallbackScript->AddCallback<ModelCallback>(0x4d6514a3, [] {
			Ped PedID = PLAYER::PLAYER_PED_ID();
			Vector3 pos;
			pos.z + .5f;
			WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PedID, &pos);

			OBJECT::CREATE_AMBIENT_PICKUPP(0xC3CD8B31, pos, 0, 0, 0x4d6514a3, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
			//OBJECT::CREATE_AMBIENT_PICKUP(0xC3CD8B31, pos.x, pos.y, pos.z, 0, 0, 0x4d6514a3, FALSE, TRUE);
		});
	}
}


bool Features::DriveItBool = false;
void Features::DriveIt(bool toggle)
{
	Vector3 iCoord;
	if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &iCoord))
	{
		int VehID = VEHICLE::GET_CLOSEST_VEHICLE(iCoord.x, iCoord.y, iCoord.z, 100.0f, 0, 71);
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), VehID, -1);
	}
}


bool Features::FireShoot = false;
void Features::ShootFire()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (is_ped_shooting(playerPed))
	{
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
		{
			FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 12, 10.0f, false, false, false);
		}

	}
}
bool Features::FireworkBool = false;
void Features::FireWork()
{
	//float startDistance = distanceBetween(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//float endDistance = distanceBetween(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//startDistance += 0.25;
	//endDistance += 1000.0;
	//if (PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
	//{
	//	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_FIREWORK"); //WEAPON_FIREWORK
	//	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	//	{
	//		WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);
	//	}
	//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, PLAYER::PLAYER_PED_ID(), 1, 0, -1.0);
	//}

}
bool Features::AmmoEditorBool = false;
void Features::AmmoEditor(std::string weaponType)
{
	//float startDistance = distanceBetween(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//float endDistance = distanceBetween(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
	//startDistance += 0.25;
	//endDistance += 1000.0;
	//if (PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
	//{
	//	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY(weaponType); //Weapon
	//	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	//	{
	//		WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, false);
	//	}
	//	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, add(&CAM::GET_GAMEPLAY_CAM_COORD(), &multiply(&rotDirection(&CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, 250, 1, weaponAssetRocket, PLAYER::PLAYER_PED_ID(), 1, 0, -1.0);
	//}

}
bool Features::AirStrike = false;
void Features::PreditorGun()
{
	Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET");
	if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
	{
		g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

		});
	}
	if (is_ped_shooting(PLAYER::PLAYER_PED_ID()))
	{
		Vector3 Pos;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &Pos))
		{
			auto Start = Pos;
			Start.z += 35;
			auto End = Pos;
			End.z += 2;
			FIRE::ADD_EXPLOSION(Pos.x, Pos.y, Pos.z, 22, 0, 1, 0, 0);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Start.x, Start.y, Start.z, End.x, End.y, End.z, 0, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 100);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Start.x, Start.y, Start.z, End.x, End.y, End.z, 0, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 100);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Start.x, Start.y, Start.z, End.x, End.y, End.z, 0, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 100);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Start.x, Start.y, Start.z, End.x, End.y, End.z, 0, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 100);
		}
	}
}
bool Features::RainbowWeaponsBool = false;
void Features::RainbowWeapons() {
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	static LPCSTR weaponNames[] = {
		"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR",
		"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG",
		"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
		"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
		"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
		"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
		"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN",
		"WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER",
		"WEAPON_PROXMINE", "WEAPON_SNOWBALL", "WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET",
		"WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN", "WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN", "WEAPON_FLAREGUN",
		"WEAPON_KNUCKLE", "GADGET_NIGHTVISION", "GADGET_PARACHUTE", "WEAPON_MARKSMANPISTOL", "", ""
	};
	for (int i = 0; i < sizeof(weaponNames) / sizeof(weaponNames[0]); i++)
	{
		if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, GAMEPLAY::GET_HASH_KEY((char *)weaponNames[i]), 0))
		{
			WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, GAMEPLAY::GET_HASH_KEY((char *)weaponNames[i]), rand() % 8);
		}
	}
}

bool Features::AimbotAutoShoot = false;
bool Features::AimbotESPTarget = false;
bool Features::AimbotBool = false;
void Features::Aimbot()
{
int player = PLAYER::PLAYER_ID();
int playerPed = PLAYER::PLAYER_PED_ID();

for (int i = 0; i < 32; i++)
{
	if (i != player)
	{

			Ped targetPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(targetPed, 1);
			BOOL exists = ENTITY::DOES_ENTITY_EXIST(targetPed);
			BOOL dead = PLAYER::IS_PLAYER_DEAD(targetPed);

			if (exists && !dead)
			{
				float screenX, screenY;
				BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY);
				if (ENTITY::IS_ENTITY_VISIBLE(targetPed) && onScreen)
				{
					if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, targetPed, 17))
					{

						if (i != PLAYER::PLAYER_ID() && ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
						{

						}



						Vector3 targetCoords = PED::GET_PED_BONE_COORDS(targetPed, 31086, 0, 0, 0);



						if (Features::AimbotAutoShoot)
						{
							if (AimbotESPTarget)
							{
								Vector3 entitylocation = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
								Vector3 top1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
								Vector3 top2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
								Vector3 top3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
								Vector3 top4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
								Vector3 bottom1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
								Vector3 bottom2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
								Vector3 bottom3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };
								Vector3 bottom4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };
								GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top2world.x, top2world.y, top2world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, top4world.x, top4world.y, top4world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, top3world.x, top3world.y, top3world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top3world.x, top3world.y, top3world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(bottom1world.x, bottom1world.y, bottom1world.z, bottom2world.x, bottom2world.y, bottom2world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(bottom2world.x, bottom2world.y, bottom2world.z, bottom4world.x, bottom4world.y, bottom4world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom4world.x, bottom4world.y, bottom4world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom1world.x, bottom1world.y, bottom1world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, bottom1world.x, bottom1world.y, bottom1world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, bottom2world.x, bottom2world.y, bottom2world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top3world.x, top3world.y, top3world.z, bottom3world.x, bottom3world.y, bottom3world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, bottom4world.x, bottom4world.y, bottom4world.z, 200, 0, 0, 255);
								Vector3 locationOne = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
								Vector3 locationTwo = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
								GRAPHICS::DRAW_LINE(locationOne.x, locationOne.y, locationOne.z, locationTwo.x, locationTwo.y, locationTwo.z, 200, 0, 0, 255);
							}
							PED::SET_PED_SHOOTS_AT_COORD(playerPed, targetCoords.x, targetCoords.y, targetCoords.z, 1);
						}

						if (IsKeyPressed(VK_RBUTTON) && !Features::AimbotAutoShoot)
						{
							if (AimbotESPTarget)
							{
								Vector3 entitylocation = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
								Vector3 top1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
								Vector3 top2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
								Vector3 top3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
								Vector3 top4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
								Vector3 bottom1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
								Vector3 bottom2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
								Vector3 bottom3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };
								Vector3 bottom4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };
								GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top2world.x, top2world.y, top2world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, top4world.x, top4world.y, top4world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, top3world.x, top3world.y, top3world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top3world.x, top3world.y, top3world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(bottom1world.x, bottom1world.y, bottom1world.z, bottom2world.x, bottom2world.y, bottom2world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(bottom2world.x, bottom2world.y, bottom2world.z, bottom4world.x, bottom4world.y, bottom4world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom4world.x, bottom4world.y, bottom4world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom1world.x, bottom1world.y, bottom1world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, bottom1world.x, bottom1world.y, bottom1world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, bottom2world.x, bottom2world.y, bottom2world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top3world.x, top3world.y, top3world.z, bottom3world.x, bottom3world.y, bottom3world.z, 200, 0, 0, 255);
								GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, bottom4world.x, bottom4world.y, bottom4world.z, 200, 0, 0, 255);
								Vector3 locationOne = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
								Vector3 locationTwo = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
								GRAPHICS::DRAW_LINE(locationOne.x, locationOne.y, locationOne.z, locationTwo.x, locationTwo.y, locationTwo.z, 200, 0, 0, 255);
							}
							PED::SET_PED_SHOOTS_AT_COORD(playerPed, targetCoords.x, targetCoords.y, targetCoords.z, 1);
						}

					}
				}
			}
		}
}
}


bool Features::ShootR = false;
void Features::ShootRocket(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();



	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}

}


bool Features::ShootT = false;
void Features::ShootTanks(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();



	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_FIREWORK");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}

bool Features::ShootTankR = false;
void Features::ShootTankRounds(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();



	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_TANK");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}
		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}


bool Features::ShootBall = false;
void Features::ShootBalls(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();


	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_BALL");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}

bool Features::ShootMini = false;
void Features::ShootMiniGun(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();



	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_BULLET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}

bool Features::carRPG = false;
void Features::shootRPGCar(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}
		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();


	}
}

bool Features::llcar = false;
void Features::LLCar(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_ENEMY_LASER");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();


	}
}


bool Features::ggcar = false;
void Features::GGCar(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_LASER");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();


	}
}

bool Features::wwcar = false;
void Features::WWCar(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLANE_ROCKET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();


	}
}























bool Features::cccar = false;
void Features::CCCar(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_CANNON_BLAZER");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();


	}
}

bool Features::ttcar = false;
void Features::TTCar(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_TURRET_BOXVILLE");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();


	}
}


bool Features::ttcarflare = false;
void Features::TTCarflare(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_FLARE");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}
		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();


	}
}

bool Features::qqcar = false;
void Features::QQCar(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_RUINER_BULLET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}
		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();


	}
}

bool Features::qqcarxdsa = false;
void Features::QQCarsd(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	bool bSelect = GetAsyncKeyState(0x6B); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_MOLOTOV");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 0, weaponAssetRocket, playerPed, 1, 0, -1.0);

		featureWeaponVehShootLastTime = GetTickCount();


	}
}



float yaw, rotation, pitch, roll = 0.0f;
bool Features::FlyingCarBool = false;
bool isBackward;
void Features::FlyingCar(bool toggle)
{
	if (toggle)
	{
		if (PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) != NULL)
		{
			VEHICLE::SET_VEHICLE_GRAVITY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), FALSE); // No more falling.
			pitch = ENTITY::GET_ENTITY_PITCH(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
			float curSpeed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));


			if (IsKeyPressed(0x57)) /* W DOWN - GO FORWARD */
			{
				isBackward = false;
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), pitch, 0.0f, yaw, 2, TRUE);
				RequestControl(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), curSpeed += 3.0f);
			}
			else if (IsKeyPressed(0x53)) /* S DOWN - GO BACKWARD */
			{
				isBackward = true;
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), pitch, 0.0f, yaw, 2, TRUE);
				RequestControl(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), (curSpeed * -1.0f) - 3.0f);
			}
			else {
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), pitch, roll, yaw, 2, TRUE);
				if (curSpeed > 3.0f && isBackward)
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), curSpeed - 3.0f);
				}
				else
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f);
				}
			}

			if (IsKeyPressed(0x41)) /* A DOWN - TURN LEFT */
			{
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), pitch, roll, yaw += 4.5f, 2, TRUE);
			}

			if (IsKeyPressed(0x44)) /* D DOWN - TURN RIGHT */
			{
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), pitch, roll, yaw -= 4.5f, 2, TRUE);
			}

			if (IsKeyPressed(VK_SHIFT)) /* SHIFT DOWN - PITCH UP */
			{
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), pitch -= 4.5f, roll, yaw, 2, TRUE);
			}

			if (IsKeyPressed(VK_CONTROL)) /* CTRL DOWN - PITCH DOWN */
			{
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), pitch += 4.5f, roll, yaw, 2, TRUE);
			}

			if (IsKeyPressed(VK_SPACE)) /* SPACE DOWN - STOP */
			{
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f, roll, yaw, 2, TRUE);
				RequestControl(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0.0f);
			}
		}
	}
	else
	{
		VEHICLE::SET_VEHICLE_GRAVITY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), TRUE);
	}
}



bool Features::DamageBool = false;
void Features::DamageMod()
{
	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))
	{
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999);
	}
}

bool Features::Recoil = false;
void Features::NoRecoil()
{
	if (Features::Recoil)
	{
		Memory::set_value<float>({ 0x08, 0x10D8, 0x20, 0x2F4 }, 0);
	}
	else
	{
		Memory::set_value<float>({ 0x08, 0x10D8, 0x20, 0x2F4 }, 1);
	}
}

bool Features::RapidFireBool = false;
void Features::RapidFire() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		//PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 1);
		Vector3 gameplayCam = CAM::_GET_GAMEPLAY_CAM_COORDS();
		Vector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
		Vector3 gameplayCamDirection = RotationToDirection(gameplayCamRot);
		Vector3 startCoords = addVectors(gameplayCam, (multiplyVector(gameplayCamDirection, 1.0f)));
		Vector3 endCoords = addVectors(startCoords, multiplyVector(gameplayCamDirection, 500.0f));
		Hash weaponhash;
		WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &weaponhash, 1);
		if (CONTROLS::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000)) {
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords.x, startCoords.y, startCoords.z, endCoords.x, endCoords.y, endCoords.z, 50, 1, weaponhash, playerPed, 1, 1, 0xbf800000);
		}
	}
}

bool Features::OrbitalCooldownBool = false;
void Features::OrbitalCooldown()
{
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ORBITAL_CANNON_COOLDOWN"), 0, -1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ORBITAL_CANNON_COOLDOWN"), 0, -1);
}

bool Features::CustomVehicleColorBool = false;
void Features::CustomVehicleColor()
{
	
}

int Features::boostlevel = 0;
void Features::carboost()
{
	int player = PLAYER::PLAYER_PED_ID();

	if (PED::IS_PED_IN_ANY_VEHICLE(player, 0))
	{
		if (IsKeyPressed(VK_SHIFT))
		{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, Features::boostlevel);
			}
		}
		if (IsKeyPressed(VK_KEY_S))
		{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 0);
			}
		}
	}
}
bool Features::sonicvehicle = false;
void Features::carboostt()
{
	int player = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(player, 0))
	{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 1000);
			}
	}
}
bool Features::containerflybool = false;
void Features::containerfly()
{
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
	float zPos;
	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &zPos, false);
	Object prop = OBJECT::CREATE_OBJECT_NO_OFFSET(GAMEPLAY::GET_HASH_KEY("prop_container_ld"), coords.x, coords.y, zPos - 2.75, TRUE, TRUE, FALSE);
	Vector3 rot = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE), 1);
	ENTITY::SET_ENTITY_ROTATION(prop, rot.x, rot.y, rot.z, 1, TRUE);
	ENTITY::FREEZE_ENTITY_POSITION(prop, TRUE);
	ENTITY::SET_OBJECT_AS_NO_LONGER_NEEDED(&prop);
	
}

bool Features::fuckedhandling = { false };
void Features::fuckhandling(bool toggle)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
	RequestControlOfEnt(veh);
	VEHICLE::SET_VEHICLE_STEER_BIAS(veh, 32 ? 1.0f : 0.0f);
}

Object prop = 0;
bool Features::remoteContainerFlybool = false;
void Features::remoteContainerFly()
{
	if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), FALSE)))
	{
		ENTITY::FREEZE_ENTITY_POSITION(prop, FALSE);
		ENTITY::SET_ENTITY_COLLISION(prop, FALSE, FALSE);
		OBJECT::DELETE_OBJECT(&prop);
		ENTITY::FREEZE_ENTITY_POSITION(prop, FALSE);
		ENTITY::SET_ENTITY_COORDS(prop, 999, 999, 999, true, true, true, true);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(prop, TRUE, TRUE);
		OBJECT::DELETE_OBJECT(&prop);
		ENTITY::DELETE_ENTITY(&prop);
	}




	PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1);
	PED::SET_PED_CONFIG_FLAG(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 32, false);
	Vector3 rot = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), FALSE), 1);
	if (prop != 0)
	{
		if (prop > 32)
		{
			ENTITY::FREEZE_ENTITY_POSITION(prop, FALSE);
			ENTITY::SET_ENTITY_COLLISION(prop, FALSE, FALSE);
			OBJECT::DELETE_OBJECT(&prop);
			ENTITY::FREEZE_ENTITY_POSITION(prop, FALSE);
			ENTITY::SET_ENTITY_COORDS(prop, 999, 999, 999, true, true, true, true);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(prop, TRUE, TRUE);
			OBJECT::DELETE_OBJECT(&prop);
			ENTITY::DELETE_ENTITY(&prop);
		}
	}

	if (!ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), FALSE)))
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), TRUE);
		float zPos;
		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &zPos, false);
		if (!ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), FALSE))) prop = OBJECT::CREATE_OBJECT_NO_OFFSET(GAMEPLAY::GET_HASH_KEY("prop_container_ld"), coords.x, coords.y, coords.z - 3.5, TRUE, TRUE, FALSE);

		ENTITY::SET_ENTITY_ROTATION(prop, rot.x - 2, rot.y, rot.z, 1, TRUE);
		ENTITY::FREEZE_ENTITY_POSITION(prop, TRUE);

		if (prop > 32)
		{
			ENTITY::SET_ENTITY_ALPHA(prop, 0, false);
		}


	}

	//ENTITY::SET_OBJECT_AS_NO_LONGER_NEEDED(&prop);
}

bool Features::TransActionSpamBool = false;
void Features::TransActionSpam()
{
	auto unkKek1 = globalHandle(1628237 + 1 + g_SelectedPlayer * 615 + 533).As<std::uint64_t>();
	auto unkKek2 = globalHandle(1650640 + 9).As<std::uint64_t>();
	std::uint64_t args[8] = {
		TRANSACION_ERROR,
		g_SelectedPlayer,
		10000, // amount
		0,
		0,
		unkKek1, unkKek2, unkKek2
	};
	Hooks::TriggerScriptEvent(1, args, 8, 1 << g_SelectedPlayer);
}

bool Features::zerospeedbool = false;
void Features::zerospeed()
{
	int player = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(player, 0))
	{
		Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
		{
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 0);
		}
	}
}
bool Features::AsteroidShowerBool = false;
void Features::AsteroidShower(bool toggle) {


}



bool Features::BetterFlyingCarBool = false;
void Features::BetterFlyingCar(bool toggle)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
	{
		int Vehid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

		if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(Vehid)) || VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(Vehid)))
		{
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, INPUT_VEH_FLY_THROTTLE_UP)) //Forward
			{
				float Speed = ENTITY::GET_ENTITY_SPEED(Vehid) + 0.4;
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Vehid, Speed);
			}

			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, INPUT_VEH_FLY_YAW_LEFT) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Turn Left
			{
				Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(Vehid, 2);
				Rot.z = Rot.z + 1.0;
				ENTITY::SET_ENTITY_ROTATION(Vehid, Rot.x, Rot.y, Rot.z, 2, 1);
			}

			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, INPUT_VEH_FLY_YAW_RIGHT) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Turn Right
			{
				Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(Vehid, 2);
				Rot.z = Rot.z - 1.0;
				ENTITY::SET_ENTITY_ROTATION(Vehid, Rot.x, Rot.y, Rot.z, 2, 1);
			}
		}
	}
}


bool Features::AddWeaponsBool = false;
void Features::AddWeapons()
{
	for (Hash hash : Weaponss)
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
	AddWeaponsBool = false;
}



bool Features::AsteroidBool = false;
void Features::Asteroid(bool toggle) {


	Hash ast = GAMEPLAY::GET_HASH_KEY("prop_asteroid_01");
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)"Thunder");
	Vector3 kek = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	if ((timeGetTime() - TimePD5) > 600) 
	{
		if (STREAMING::IS_MODEL_VALID(ast))
		{
			STREAMING::REQUEST_MODEL(ast);
			while (!STREAMING::HAS_MODEL_LOADED(ast));
			float ang = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 20.0f) * 3.14159265359f;
			float rad = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 20.0f) * 15.0f;
			float x = kek.x + rad * cos(ang);
			float y = kek.y + rad * sin(ang);
			Object ObjAsteroid;
			ObjAsteroid = OBJECT::CREATE_OBJECT(ast, x, y, kek.z, 1, 1, 0, &ObjAsteroid, true, false, 0);
			ENTITY::SET_ENTITY_COLLISION(ObjAsteroid, 1, 1);
			ENTITY::APPLY_FORCE_TO_ENTITY(ObjAsteroid, 1, 150.0f, 180.0f, 200.0f, 20.0f, 20.0f, 50.0f, 0, 0, 1, 1, 0, 1);
			TimePD5 = timeGetTime();
		}
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ast);
	}


}



Object mapMods[250];
int mapModsIndex = 0;
void Features::PlaceObjectByHash(Hash hash, float x, float y, float z, float pitch, float roll, float yaw, float heading, int id)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash)) {
		STREAMING::REQUEST_MODEL(hash);
		//while (!STREAMING::HAS_MODEL_LOADED(hash)) SYSTEM::WAIT(0);


		Object obj;
		OBJECT::CREATE_OBJECT(hash, x, y, z, 1, 1, 0, &obj, true, false, 0);
		//SET_ENTITY_HEADING(obj, heading);
		//SET_ENTITY_ROTATION(obj, pitch, roll, yaw, 2, 1);
		ENTITY::SET_ENTITY_LOD_DIST(obj, 696969);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(obj);
		ENTITY::FREEZE_ENTITY_POSITION(obj, 1);
		ENTITY::SET_ENTITY_ROTATION(obj, pitch, roll, yaw, 0, 1);
		mapMods[mapModsIndex] = obj;
		if (mapModsIndex <= 250) mapModsIndex++;
		//SYSTEM::WAIT(25);
		g_FiberScript->Wait(10);
	}
}


bool Features::ChaosModeBool = false;
void Features::ChaosMode(bool toggle)
{
	const int numElements = 15;
	const int arrSize = numElements * 2 + 2;
	Ped peds[arrSize];
	peds[0] = numElements;
	int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);

	// Nearby Peds
	for (int i = 0; i < count; ++i)
	{
		int offsettedID = i * 2 + 2;
		if (ENTITY::DOES_ENTITY_EXIST(peds[offsettedID]) && peds[offsettedID] != PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX()))
		{
			ENTITY::SET_ENTITY_HAS_GRAVITY(peds[offsettedID], false);
			Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(peds[offsettedID]);
			velocity.z = 2.f;
			if (ENTITY::IS_ENTITY_A_PED(peds[offsettedID]) && !PED::IS_PED_RAGDOLL(peds[offsettedID]))
			{
				PED::SET_PED_TO_RAGDOLL(peds[offsettedID], 2000, 0, 2, false, false, false);
				velocity.z = 5.f;
				ENTITY::APPLY_FORCE_TO_ENTITY(peds[offsettedID], 1, 0, 0, ENTITY::IS_ENTITY_A_PED(peds[offsettedID]) ? 10.f : 5.f, 0, 0, 0, 1, 1, 1, 1, 1, 1);
			}
			ENTITY::SET_ENTITY_VELOCITY(peds[offsettedID], velocity.x, velocity.y, velocity.z);
		}
	}

	// Nearby Vehicles
	const int numElements2 = 15;
	const int arrSize2 = numElements2 * 2 + 2;
	Vehicle veh[arrSize2];
	veh[0] = numElements2;
	int count2 = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), veh);

	if (veh != NULL)
	{
		for (int i = 0; i < count2; i++)
		{
			int offsettedID = i * 2 + 2;
			if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]) && veh[offsettedID] != PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX())))
			{
				ENTITY::SET_ENTITY_HAS_GRAVITY(veh[offsettedID], false);
				Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(veh[offsettedID]);
				velocity.z = 2.f;
				ENTITY::SET_ENTITY_VELOCITY(veh[offsettedID], velocity.x, velocity.y, velocity.z);
				ENTITY::APPLY_FORCE_TO_ENTITY(veh[offsettedID], 1, 0, 0, ENTITY::IS_ENTITY_A_PED(veh[offsettedID]) ? 10.f : 5.f, 0, 0, 0, 1, 1, 1, 1, 1, 1);
			}
		}
	}
}

bool Features::DriftModeBool = false;
void Features::DriftMode(bool toggle)
{
	if (toggle)
	{
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
	}
	else {
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
	}
}

std::vector<int32_t> aquire_dough() {
	const int pineapple = 999;
	int nerby[pineapple * 50 + 50] = { pineapple * 50 + 50 };
	auto count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), (int*)&nerby);
	std::vector<int32_t> rtrn;

	for (int i = 0; i < count; i++) {
		auto v = nerby[i * 2 + 2];
		rtrn.push_back(v);
	}

	return rtrn;
}

std::vector<int32_t> add_tomato_sauce() {
	const int pineapple = 999;
	int nerby[pineapple * 50 + 50] = { pineapple * 50 + 50 };
	auto count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), (int*)&nerby, PLAYER::PLAYER_PED_ID());
	std::vector<int32_t> rtrn;

	for (int i = 0; i < count; i++) {
		auto p = nerby[i * 2 + 2];
		rtrn.push_back(p);
	}

	return rtrn;
}
Vector3 Features::oregano;
float BH_FORCE = 1.f;
bool Features::BlackHoleBool = false;
void Features::BlackHole(bool toggle)
{
	if (Features::BlackHoleBool)
	{
		GRAPHICS::DRAW_MARKER(28, oregano.x, oregano.y, oregano.z, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 15.f, 15.f, 15.f, 0, 0, 0, 255, false, false, 0, false, NULL, NULL, false);
	
		auto ingredient = aquire_dough();
		auto second_ingredient = add_tomato_sauce();
		ingredient.insert(ingredient.end(), second_ingredient.begin(), second_ingredient.end());
		for (auto pizza : ingredient) {
			if (pizza && ENTITY::DOES_ENTITY_EXIST(pizza)) {
				auto pepperoni = ENTITY::GET_ENTITY_COORDS(pizza, 1);
				auto pineapple = oregano;
				pineapple.z += 1.5f;
				Vector3 extra_cheese = { pineapple.x - pepperoni.x, pineapple.y - pepperoni.y, pineapple.z - pepperoni.z };
				if (distanceBetween(pineapple, pepperoni) > 3.f) {
					ENTITY::APPLY_FORCE_TO_ENTITY(pizza, 1, (extra_cheese.x / 13) * BH_FORCE, (extra_cheese.y / 13) * BH_FORCE, extra_cheese.z / 13, 0.f, 0.f, 0.f, 0, false, true, true, 0, 0);
				}
				else {
					ENTITY::SET_ENTITY_VELOCITY(pizza, 0.f, 0.f, 0.f);
					ENTITY::APPLY_FORCE_TO_ENTITY(pizza, 1, 0.f, 0.f, extra_cheese.z / 15, 0.f, 0.f, 0.f, 0, false, true, true, 0, 0);
				}
			}
		}
	}
	else
	{

	}
}

int ddddd(int start, int end) {
	return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(start, end);
}


int Features::StealthTimer;
bool Features::StealthBool = false;
void Features::Stealth(bool toggle)
{

	if ((timeGetTime() - StealthTimer) > 500)
	{
		int val1 = 0x129A5B6E;

		globalHandle(4265412 + 1).As<int>() = ddddd(0, INT_MAX);
		globalHandle(4265412 + 6).As<int>() = 1;
		globalHandle(4265412 + 5).As<int>() = 1;
		globalHandle(4265412 + 3).As<int>() = val1;
		globalHandle(4265412 + 2).As<int>() = StealthAmount;
		globalHandle(4265412).As<int>() = 1;




		StealthTimer = timeGetTime();

	}
}


int Features::KohleMoney = 61000000;
bool Features::VehStealthBool = false;
void Features::VehStealth(bool toggle)
{
	globalHandle(99007).At(970).As<int>() = Features::KohleMoney;
	globalHandle(26269).As<int>() = Features::KohleMoney;

	//Reset Sell Time
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VEHICLE_SELL_TIME"), 0, 1);
}





bool Features::FakeLoopBool = false;
void Features::FakeLoop(bool toggle)
{

	int towallet;
	int tobank;
	int iVar2 = INT_MAX;

	if (globalHandle(2599118).As<int>() == -1) {
		globalHandle(2599118) = NETWORKCASH::NETWORK_GET_VC_BANK_BALANCE();
	}
	if (globalHandle(2599119).As<int>() == -1) {
		globalHandle(2599119) = NETWORKCASH::NETWORK_GET_VC_WALLET_BALANCE(-1);
	}
	towallet = 0;
	tobank = 0;
	if (globalHandle(2599118).Get<int>() > 0) {
		if (globalHandle(2599118).Get<int>() >= &iVar2) {
			tobank = iVar2;
		}
		else {
			tobank = iVar2 - (iVar2 - globalHandle(2599118).As<int>());
		}
		iVar2 -= tobank;
	}
	if (iVar2 > 0) {
		if (globalHandle(2599119).Get<int>() > 0) {
			if (globalHandle(2599119).Get<int>() >= &iVar2) {
				towallet = iVar2;
			}
			else {
				towallet = iVar2 - (iVar2 - globalHandle(2599119).As<int>());
			}
			iVar2 -= towallet;
		}
	}
	invoke<Void>(536737010038877744, towallet, tobank);
	globalHandle(2599118) = towallet;
	globalHandle(2599119) = tobank;
}










int Features::Explosionfickk = 38;
int Features::ficksizee = 10;
int Features::rt = 255;
int Features::rrt = 255;
int Features::rrrt = 255;
int bomber_ting;
Vector3 bomb_coords;
bool bomber_cooldown;
bool bomber_countdown = true;
bool Features::bomber;
void Features::bomber_mode(bool toggle) {
	if (PED::IS_PED_IN_ANY_HELI(PLAYER::PLAYER_PED_ID()) || PED::IS_PED_IN_ANY_PLANE(PLAYER::PLAYER_PED_ID())) {
		Vector3 c = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(c.x, c.y, c.z, &c.z, 0);
		if (!bomber_countdown)
			bomb_coords = c;

		GRAPHICS::DRAW_MARKER(6, bomb_coords.x, bomb_coords.y, bomb_coords.z, 0.f, 0.f, 0.f, 90.f, 0.f, 0.f, 15.f, 15.f, 15.f, rt, rrt, rrrt, 150, 0, 0, 0, 0, NULL, NULL, 0);

		static auto ticker = GetTickCount();
		if (bomber_cooldown) {
			if ((GetTickCount() - ticker) >= 3500) {
				bomber_cooldown = false;
				ticker = GetTickCount();
			}
		}

		static auto ticcker = GetTickCount();
		if (bomber_countdown) {
			if ((GetTickCount() - ticcker) >= 1500) {
				FIRE::ADD_EXPLOSION(bomb_coords.x, bomb_coords.y, bomb_coords.z, Features::Explosionfickk, Features::ficksizee, true, false, 0);
				g_Logger->Info("~g~Completed.");
				bomber_ting = 0;
				bomber_countdown = false;
				ticcker = GetTickCount();
			}
		}

		if (IsKeyPressed(VK_SPACE) && !bomber_cooldown) {
			ticcker = GetTickCount();
			ticker = GetTickCount();
			g_Logger->Info("~s~Wait...");
			bomb_coords = c;
			bomber_countdown = true;
			bomber_cooldown = true;
		}
	}
}


















void Features::PlateEdit(char* plate)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, plate);
	}
	else
	{
		ScriptEventLog("~r~You must be in a vehicle to change the plate text!");
	}
}

bool Features::cargodmodebool = false;
void Features::cargodmode()
{
	Memory::set_value<int>({ 0x08, 0xD30, 0x189 }, Features::cargodmodebool);
}

bool Features::Boost = false;
void Features::RocketBoost()
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	if (VEHICLE::_HAS_VEHICLE_ROCKET_BOOST(veh))
	{
		VEHICLE::_SET_VEHICLE_ROCKET_BOOST_REFILL_TIME(veh, 0);
		VEHICLE::_SET_VEHICLE_ROCKET_BOOST_PERCENTAGE(veh, 100.0f);
	}
}

bool Features::InvisibleCarBool = false;
void Features::InvisibleCar()
{
	Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	if (Features::InvisibleCarBool)
		ENTITY::SET_ENTITY_VISIBLE(Veh, false, 0);
	else
		ENTITY::SET_ENTITY_VISIBLE(Veh, true, 0);
}


bool Features::LobbySaveBool = false;
void Features::LobbySave(bool toggle)
{
	//for (std::uint32_t i = 0; i < 32; ++i)
	//{
	//	if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
	//	{


	//			auto sd = skCrypt("APPDATA");
	//			std::string ad = getenv(sd);
	//			sd.clear();
	//			std::string folderpath = std::string(ad) + ".\\Monop0l\\Last-Player\\";
	//			std::string PlayerName = PLAYER::GET_PLAYER_NAME(i);
	//			if (!DoesFileExists(std::string(ad) + ".\\Monop0l\\Last-Player\\" + PlayerName + ".ini"))
	//			{







	//				int rp = globalHandle(1590682).At(i, 876).At(211).At(5).As<int>();
	//				int money = globalHandle(1590682).At(i, 876).At(211).At(3).As<int>();
	//				int rank = globalHandle(1590682).At(i, 876).At(211).At(6).As<int>();
	//				int kills = globalHandle(1590682).At(i, 876).At(211).At(28).As<int>();
	//				int deaths = globalHandle(1590682).At(i, 876).At(211).At(29).As<int>();
	//				int handle = globalHandle(1590682).At(i, 876).At(211).At(56).As<int>();
	//				int handle2 = globalHandle(1590682).At(i, 876).At(211).At(3).As<int>();
	//				int bank = handle - 10 - handle2 + (5 * 1 + 3 + 2);
	//				int raceswon = globalHandle(1590682).At(i, 421).At(122).At(1).As<int>();
	//				int raceslost = globalHandle(1590682).At(i, 421).At(122).At(1).At(1).As<int>();
	//				int earnings = globalHandle(1590682).At(i, 876).At(211).At(56).As<int>();








	//				int netHandle[13];
	//				NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, netHandle, 13);
	//				char* UserID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);
	//				std::string PlayerIP;
	//				char ipBuf[32] = {};
	//				static auto nigNog = (std::uintptr_t(*)(int))(Memory::pattern("40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C").count(1).get(0).get<void>(0));
	//				auto nigger = nigNog(i);
	//				auto faggot = *(uintptr_t*)(nigger + 0x10C8);
	//				auto ip = (BYTE*)(faggot + 0x44);
	//				std::snprintf(ipBuf, sizeof(ipBuf) - 1, "~r~IP: %u.%u.%u.%u", ip[3], ip[2], ip[1], *ip);
	//				PlayerIP = std::to_string(ip[3]) + "." + std::to_string(ip[2]) + "." + std::to_string(ip[1]) + "." + std::to_string(*ip);
	//				std::string port_str;
	//				auto port = reinterpret_cast<uint16_t*>(faggot + 0x1F4EBA0);
	//				char buffer[5 + 1];
	//				std::snprintf(buffer, sizeof(buffer), "%i", *port);
	//				port_str = buffer;
	//				Ini* settingsIni = new Ini(std::string(ad) + ".\\Monop0l\\Last-Player\\" + PlayerName + ".ini");
	//				if (!std::filesystem::exists(folderpath.c_str()))
	//				{
	//					std::filesystem::create_directory(folderpath.c_str());
	//				}
	//				settingsIni->WriteString(PlayerIP, PlayerName, "IP");
	//				settingsIni->WriteString(port_str, "", "Port");
	//				settingsIni->WriteString(UserID, "", "Rockstar ID");
	//				settingsIni->WriteString(std::to_string(money), "", "Money");
	//				settingsIni->WriteString(std::to_string(bank), "", "Bank");
	//				settingsIni->WriteString(std::to_string(rp), "", "RP");
	//				settingsIni->WriteString(std::to_string(rank), "", "Level");
	//				settingsIni->WriteString(std::to_string(kills), "", "Kills");
	//				settingsIni->WriteString(std::to_string(deaths), "", "Deaths");
	//				settingsIni->WriteString(std::to_string(raceswon), "", "Races-Won");
	//				settingsIni->WriteString(std::to_string(raceslost), "", "Races-Lost");
	//				settingsIni->WriteString(std::to_string(earnings), "", "Earnings");
	//				delete settingsIni;
	//		}
	//	}
	//}
}


bool Features::vehiclegravitybool = false;
void Features::vehiclegravity()
{
	if (vehiclegravitybool)
		GAMEPLAY::SET_GRAVITY_LEVEL(3);
	else
		GAMEPLAY::SET_GRAVITY_LEVEL(0);
}



bool Features::hornboostbool = false;
void Features::hornboost(bool toggle)
{
	if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()))
	{
		GRAPHICS::ANIMPOSTFX_PLAY((char*)"RaceTurbo", 0, 0);
		Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);

		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
		{
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, hornboostspeed);

		}
		GRAPHICS::ANIMPOSTFX_STOP((char*)"RaceTurbo");
	}
}


bool Features::WeaponRockets = false;
DWORD ShootTime = 0;
void Features::VehicleRockets()
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !Features::WeaponRockets) return;

	bool bSelect = IsKeyPressed(0x6B); // num plus
	if (bSelect && ShootTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket)) //wronghas//
		{
			g_CallbackScript->AddCallback<WeaponModelCallback>(weaponAssetRocket, [] {

			});
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);

		ShootTime = GetTickCount();
	}
}

bool Features::SpeedoBool = false;
bool Features::MPH = true;
bool Features::PlateMPH = false;
void Features::Speedometer()
{
	float speed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())) * 3.6f;

	if (Features::MPH)
		speed = speed * .621f;
	char msg[0xFF];
	if (MPH)
	{
		sprintf_s(msg, "%i", (int)speed);
	}
	else
	{
		sprintf_s(msg, "%i", (int)speed);
	}
	drawstring(msg, .50f, .05f);
	if (PlateMPH)
	{
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), msg);
	}
}
std::string plateSymbols[35] = {
	"a", "b", "c", "d", "e", "f",
	"g", "h", "i", "j", "k", "l",
	"m", "n", "o", "p", "q",
	"r", "s", "t", "u", "v",
	"w", "x", "y", "z", "1",
	"2", "3", "4", "5", "6", "7",
	"8", "9",
};
bool Features::MatrixPlates = false;
void Features::MatrixPlate()
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
	{
		std::string textInput = plateSymbols[rand() % 35] + plateSymbols[rand() % 35] + plateSymbols[rand() % 35] + plateSymbols[rand() % 35] + plateSymbols[rand() % 35] + plateSymbols[rand() % 35] + plateSymbols[rand() % 35] + plateSymbols[rand() % 35] + plateSymbols[rand() % 35];
		char* plateText = (strcpy((char*)malloc(textInput.length() + 1), textInput.c_str()));
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), plateText);
	}
}



bool Features::StickyBool = false;
void Features::Sticky()
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
	{
		int myVehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(myVehicle);
	}
}
bool Features::FixLoop;
void Features::FixCar()
{
	uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
	VEHICLE::SET_VEHICLE_FIXED(Vehicle);
	VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle);
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0);
}



bool Features::BlackScreenBool;
void Features::BlackScreen()
{
	DWORD64 args[9] = { BLACK_SCREEN, g_SelectedPlayer, 0, 0, 0, -1, 1, 1, 0 };
	Hooks::TriggerScriptEvent(1, args, 9, 1 << g_SelectedPlayer);

	DWORD64 args2[9] = { BLACK_SCREEN, g_SelectedPlayer, 0, 0, 0, -1, 1, 1, 0 };
	Hooks::TriggerScriptEvent(1, args2, 9, 1 << g_SelectedPlayer);

	Features::BlackScreenBool == false;
}


void Features::maxvehicle()
{
	Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
	for (int i = 0; i < 50; i++)
	{
		VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
	}
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, false);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, (char*)stringi().c_str());
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 5);
}
bool Features::MentalStateBool = false;
void Features::MentalState()
{
	if (Features::MentalStateBool)
	{
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MPPLY_PLAYER_MENTAL_STATE"), 100.0f, 1);
	}
	else
	{
		STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MPPLY_PLAYER_MENTAL_STATE"), 0.00f, 1);

	}
}

void Features::previewCar(const char* carname) {
	static Vehicle Veh;
	static int timer;


	Hash hash = GAMEPLAY::GET_HASH_KEY(carname);
	Ped Player = PLAYER::PLAYER_PED_ID();




	float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	if (STREAMING::IS_MODEL_VALID(hash))
	{
		if (ENTITY::GET_ENTITY_MODEL(Veh) == hash) {
			float heading = ENTITY::GET_ENTITY_HEADING(Veh);

			Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Player, 0, 4.0f, 0.5f);
			ENTITY::SET_ENTITY_COORDS(Veh, Coords.x, Coords.y, Coords.z, false, false, false, false);

			ENTITY::SET_ENTITY_HEADING(Veh, heading >= 360.f ? 0 : heading + 0.5f);
			ENTITY::SET_ENTITY_COLLISION(Veh, false, false);
			// VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(Veh);

			goto skipTick;
		}
		else {
			ENTITY::DELETE_ENTITY(&Veh);
		}


		STREAMING::REQUEST_MODEL(hash);
		if (!STREAMING::HAS_MODEL_LOADED(hash)) goto skipTick;

		Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Player, 0, 4.0f, 0.5f);


		Veh = VEHICLE::CREATE_VEHICLE(hash, Coords, heading, true, true);
		// VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(Veh);
		ENTITY::SET_ENTITY_COLLISION(Veh, false, false);
		ENTITY::SET_ENTITY_ALPHA(Veh, 150, 0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

	}


skipTick:;

}



bool Features::PTFXLightningBool = false;
void Features::PTFXLightning(bool toggle)
{
	PTFXCALLBoneless((char*)"scr_rcbarry2", (char*)"scr_rcbarry2", (char*)"scr_clown_death", 0x796e);
	PTFXCALLBoneless((char*)"scr_rcbarry2", (char*)"scr_rcbarry2", (char*)"scr_clown_death", 0x8cbd);
	PTFXCALLBoneless((char*)"scr_rcbarry2", (char*)"scr_rcbarry2", (char*)"scr_clown_death", 0xdead);
}






bool Features::SpoofLevelBool = false;
void Features::SpoofLevel(bool toggle)
{
	if (toggle) {
		globalHandle(1590682).At(PLAYER::PLAYER_ID(), 876).At(211).At(6).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);

	 globalHandle(1590682).At(PLAYER::PLAYER_ID(), 421).At(122).At(1).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
	 globalHandle(1590682).At(PLAYER::PLAYER_ID(), 421).At(122).At(1).At(1).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
	 globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(26).As<float>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(56).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		 globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(3).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(20).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(21).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
	globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(15).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		globalHandle(1590682).At(PLAYER::PLAYER_ID(), 421).At(208).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(5).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		 globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(3).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(6).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
 globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(28).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(29).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		globalHandle(1590682).At(PLAYER::PLAYER_ID(), 883).At(211).At(56).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
		 globalHandle(1590682).At(PLAYER::PLAYER_ID(), 833).At(211).At(3).As<int>() = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 9999999999999);
	}
}












void Features::OpenDoors()
{
	VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, true, false);
	VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, true, false);
	VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, true, false);
	VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, true, false);
	VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 4, true, false);
	VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 5, true, false);
	VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 6, true, false);
	VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 7, true, false);
}

void Features::flip()
{
	VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
}

int Features::primarycolorintr = { 0 };
int Features::primarycolorintg = { 0 };
int Features::primarycolorintb = { 0 };

void Features::PrimaryColor() {
	int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehID, Features::primarycolorintr, Features::primarycolorintg, Features::primarycolorintb);
}
int Features::secondarycolorintr = { 0 };
int Features::secondarycolorintg = { 0 };
int Features::secondarycolorintb = { 0 };

void Features::SecondaryColor1() {
	int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehID, Features::secondarycolorintr, Features::secondarycolorintg, Features::secondarycolorintb);
}
typedef struct { int R, G, B, A; } RGBA;
RGBA aprimary{ 255, 0, 0 };
RGBA asecondary{ 255, 0, 0 };
bool Features::rainbowbool = false;
void Features::rainbow()
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (aprimary.R > 0 && aprimary.B == 0)
		{
			aprimary.R--;
			aprimary.G++;
		}
		if (aprimary.G > 0 && aprimary.R == 0)
		{
			aprimary.G--;
			aprimary.B++;
		}
		if (aprimary.B > 0 && aprimary.G == 0)
		{
			aprimary.R++;
			aprimary.B--;
		}

		if (asecondary.R > 0 && asecondary.B == 0)
		{
			asecondary.R--;
			asecondary.G++;
		}
		if (asecondary.G > 0 && asecondary.R == 0)
		{
			asecondary.G--;
			asecondary.B++;
		}
		if (asecondary.B > 0 && asecondary.G == 0)
		{
			asecondary.R++;
			asecondary.B--;
		}
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, aprimary.R, aprimary.G, aprimary.B);
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, aprimary.R, aprimary.G, aprimary.B);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, asecondary.R, asecondary.G, asecondary.B);
		VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 4, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 5, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 6, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 7, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, aprimary.R, aprimary.G, aprimary.B);

	}
}

bool Features::NeonBool = false;
void Features::Neon()
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (aprimary.R > 0 && aprimary.B == 0)
		{
			aprimary.R--;
			aprimary.G++;
		}
		if (aprimary.G > 0 && aprimary.R == 0)
		{
			aprimary.G--;
			aprimary.B++;
		}
		if (aprimary.B > 0 && aprimary.G == 0)
		{
			aprimary.R++;
			aprimary.B--;
		}

		if (asecondary.R > 0 && asecondary.B == 0)
		{
			asecondary.R--;
			asecondary.G++;
		}
		if (asecondary.G > 0 && asecondary.R == 0)
		{
			asecondary.G--;
			asecondary.B++;
		}
		if (asecondary.B > 0 && asecondary.G == 0)
		{
			asecondary.R++;
			asecondary.B--;
		}

		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), aprimary.R, aprimary.G, aprimary.B);
	}
}


bool Features::RainbowPaintLoop = false;
void Features::HasPaintLoop()
{
	int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
	VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
	VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
	VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 0, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 1, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 2, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 3, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 4, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 5, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 6, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 7, 1);
	VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
}

std::vector<std::string> listFiles(LPCSTR directory)
{
	std::vector<std::string> tempVector;
	int fileCount = 0;
	std::stringstream tempStringStream;
	/*for (auto & collectedFiles : (directory)) {
		tempStringStream << collectedFiles;
		std::string testing = tempStringStream.str();
		if (testing.substr(testing.find_last_of(".") + 1) == "mp3") {
			unsigned foundAmount = testing.find_last_of("/");
			std::string TempHolder = testing.substr(0, foundAmount);
			std::string TempHolder2 = testing.substr(foundAmount + 1);
			tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
		}
	}*/
	return tempVector;
}
std::string FloatToString(float flt) {
	std::ostringstream ss;
	ss << flt;
	std::string str(ss.str());
	return str;
}
bool Features::dowbool = false;
void Features::DriveOnWater() {
	//g_FiberScript->addTask([]() {
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
		float height = 0;
		WATER::_SET_CURRENT_INTENSITY(height);
		if ((!(VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)))) && WATER::GET_WATER_HEIGHT_NO_WAVES(pos.x, pos.y, pos.z, &height)) {
			Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, GAMEPLAY::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
			if (ENTITY::DOES_ENTITY_EXIST(container) && height > -50.0f) {
				Vector3 pRot = ENTITY::GET_ENTITY_ROTATION(playerPed, 0);
				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) pRot = ENTITY::GET_ENTITY_ROTATION(veh, 0);
				RequestControlOfEnt(container);
				ENTITY::SET_ENTITY_COORDS(container, pos.x, pos.y, height - 1.5f, 0, 0, 0, 1);
				ENTITY::SET_ENTITY_ROTATION(container, 0, 0, pRot.z, 0, 1);
				Vector3 containerCoords = ENTITY::GET_ENTITY_COORDS(container, 1);
				if (pos.z < containerCoords.z) {
					if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
						ENTITY::SET_ENTITY_COORDS(playerPed, pos.x, pos.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
					}
					else {
						RequestControlOfEnt(veh);
						Vector3 vehc = ENTITY::GET_ENTITY_COORDS(veh, 1);
						ENTITY::SET_ENTITY_COORDS(veh, vehc.x, vehc.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
					}
				}
			}
			else {
				Hash model = GAMEPLAY::GET_HASH_KEY("prop_container_ld2");
				STREAMING::REQUEST_MODEL(model);
				g_CallbackScript->AddCallback<ModelCallback>(model, [] {

				});
				container = OBJECT::CREATE_OBJECT(model, pos.x, pos.y, pos.z, 1, 1, 0, &container, true, false, 0);
				RequestControlOfEnt(container);
				ENTITY::FREEZE_ENTITY_POSITION(container, 1);
				ENTITY::SET_ENTITY_ALPHA(container, 0, 1);
				ENTITY::SET_ENTITY_VISIBLE(container, 0, 0);
			}
		}
		else {
			Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, GAMEPLAY::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
			if (ENTITY::DOES_ENTITY_EXIST(container)) {
				RequestControlOfEnt(container);
				ENTITY::SET_ENTITY_COORDS(container, 0, 0, -1000.0f, 0, 0, 0, 1);
				//g_FiberScript->Wait(10);
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&container);
				ENTITY::DELETE_ENTITY(&container);
				WATER::_RESET_CURRENT_INTENSITY();
			}
		}
	//});
}
bool Features::HeaderImage = 0;
bool Features::DisplayFPS = false;
void Features::featureDisplayFPS(bool toggle)
{
	float LastFrameTime = GAMEPLAY::GET_FRAME_TIME();
	int getFPS = (1.0f / LastFrameTime);
	char FPStext[60];
	snprintf(FPStext, sizeof(FPStext), "~g~%d", getFPS);
	setupdraw();
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(0.5f, 0.5f);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_CENTRE(0);
	drawstring(FPStext, 0.020f, 0.010f);

}
float StringToFloat(std::string str) {
	return ::atof(str.c_str());
}
Vehicle SpawnVehicleH(DWORD model, Vector3 coords, bool tpinto = 0, float heading = 0.0f) {
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model)) {
		g_CallbackScript->AddCallback<ModelCallback>(model, [model, coords, heading, tpinto] {

		});
			Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords, heading, *g_GameVariables->is_session_started, false);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			if (tpinto) {
				ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
			}
			VEHICLE::SET_VEHICLE_IS_STOLEN(veh, 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			return veh;
	}

}
std::vector<int> ToggleTypes = { 17, 18, 19, 20, 21, 22 };
std::vector<int> ModTypes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 23, 24, 26, 25, 48, 37, 27, 28, 30, 33, 34, 35, 38, 39, 45 };
std::vector<Object> Spawned;
void printf(std::string f) {
	printf(f.c_str());
}
Object AttachObjectToVehicleByHash(Hash hash, float x, float y, float z, float rotx, float roty, float rotz, Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)) {
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
		ScriptEventLog("~r~You need to be in a vehicle to load a preset !");
		return -1;
	}
	g_CallbackScript->AddCallback<ModelCallback>(hash, [hash] {

	});
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash)) {
		STREAMING::REQUEST_MODEL(hash);
		//while (!STREAMING::HAS_MODEL_LOADED(hash))
		Vector3 co = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		Object obj = OBJECT::CREATE_OBJECT_NO_OFFSET(hash, co.x, co.y, co.z, 1, 0, 0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(obj);
		ENTITY::FREEZE_ENTITY_POSITION(obj, 1);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, veh, 0, x, y, z, rotx, roty, rotz, 1, 0, 1, 0, 2, 1);
		return obj;
	}
	else {
		printf("Not in image");
		return -1;
	}
}

void Features::WriteVehicle(std::string name, Vehicle veh) {

	//auto sd = skCrypt("APPDATA");
	//std::string ad = getenv(sd);
	//sd.clear();

	//std::string iniPath = (std::string)sd + ".\\Monop0l\\vehicles\\" + name + ".ini";
	//for (int i = 0; i < ModTypes.size(); i++) {
	//	WritePrivateProfileStringA("Vehicle", FloatToString(ModTypes[i]).c_str(), FloatToString(VEHICLE::GET_VEHICLE_MOD(veh, ModTypes[i])).c_str(), iniPath.c_str());
	//}
	////VEHICLE::_GET_INTERIOR_DASH_LIGHT_COLOR(veh, &HUDLightsColour);
	////VEHICLE::_GET_INTERIOR_COATING_COLOR(veh, &HUDColour);
	//WritePrivateProfileStringA("Vehicle", "DashColor", FloatToString(HUDColour).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "DashLightColor", FloatToString(HUDLightsColour).c_str(), iniPath.c_str());
	//int PpaintType = 0;
	//int Pcolor = 0;
	//int SpaintType = 0;
	//int Scolor = 0;
	//int Sr, Sg, Sb, Pr, Pg, Pb;
	//int Prnd;
	//int pearlescent, wheelColor;
	//int wheelType = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh);
	//int PlateIndex = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh);
	//char* PlateText = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(veh);
	//bool Bulletproof = !VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(veh);
	//bool CustomTyres = VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23);
	//WritePrivateProfileStringA("Vehicle", "Bulletproof", FloatToString(Bulletproof).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "CustomTyres", FloatToString(CustomTyres).c_str(), iniPath.c_str());
	//int NeonR, NeonG, NeonB, SmokeR, SmokeG, SmokeB;
	//bool NeonEnabled;
	//VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(veh, &NeonR, &NeonG, &NeonB);
	//VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(veh, &SmokeR, &SmokeG, &SmokeB);
	//if (VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 0)) NeonEnabled = 1;
	//for (int i = 0; i < ToggleTypes.size(); i++) {
	//	WritePrivateProfileStringA("Vehicle", std::string("TOGGLE_" + FloatToString(ToggleTypes[i])).c_str(), FloatToString(VEHICLE::IS_TOGGLE_MOD_ON(veh, ToggleTypes[i])).c_str(), iniPath.c_str());
	//}
	//int WindowTintIndex = VEHICLE::GET_VEHICLE_WINDOW_TINT(veh);
	//WritePrivateProfileStringA("Vehicle", "NeonEnabled", FloatToString(NeonEnabled).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "NeonR", FloatToString(NeonR).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "NeonG", FloatToString(NeonG).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "NeonB", FloatToString(NeonB).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "SmokeR", FloatToString(SmokeR).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "SmokeG", FloatToString(SmokeG).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "SmokeB", FloatToString(SmokeB).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "WindowTint", FloatToString(WindowTintIndex).c_str(), iniPath.c_str());
	//VEHICLE::GET_VEHICLE_MOD_COLOR_1(veh, &PpaintType, &Pcolor, &Prnd);
	//VEHICLE::GET_VEHICLE_MOD_COLOR_2(veh, &SpaintType, &Scolor);
	//VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &Pr, &Pg, &Pb);
	//VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &Sr, &Sg, &Sb);
	//VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearlescent, &wheelColor);
	//std::ostringstream os; os << ENTITY::GET_ENTITY_MODEL(veh);
	//WritePrivateProfileStringA("Vehicle", "Model", os.str().c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "PrimaryPaintT", FloatToString(PpaintType).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "SecondaryPaintT", FloatToString(SpaintType).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "PrimaryPaint", FloatToString(Pcolor).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "SecondaryPaint", FloatToString(Scolor).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "Pearlescent", FloatToString(pearlescent).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "PrimaryR", FloatToString(Pr).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "PrimaryG", FloatToString(Pg).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "PrimaryB", FloatToString(Pb).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "SecondaryR", FloatToString(Sr).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "SecondaryG", FloatToString(Sg).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "SecondaryB", FloatToString(Sb).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "WheelsColor", FloatToString(wheelColor).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "WheelsType", FloatToString(wheelType).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "Unknown", FloatToString(Prnd).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "Unknown", FloatToString(PlateIndex).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Vehicle", "PlateText", PlateText, iniPath.c_str());
	//for (int i = 0; i < 10; i++) {
	//	if (VEHICLE::DOES_EXTRA_EXIST(veh, i)) {
	//		WritePrivateProfileStringA("Vehicle", std::string("Extra_" + FloatToString(i)).c_str(), FloatToString(VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(veh, i)).c_str(), iniPath.c_str());
	//	}
	//}
	//ScriptEventLog("~g~Successfully saved vehicle. !");
}

void WritePreset(std::string name, float id, float x, float y, float z, float rotx, float roty, float rotz, Hash model) {

	auto sd = skCrypt("APPDATA");
	std::string ad = getenv(sd);
	sd.clear();

	//std::string iniPath = std::string(ad) + ".\\Monop0l\\vehicles\\" + name + ".ini"; //change path
	//if (!std::ifstream(iniPath)) std::ofstream file(iniPath);
	//if (DoesFileExists(iniPath)) {
	//	return;
	//}
	std::string X = FloatToString(x);
	std::string Y = FloatToString(y);
	std::string Z = FloatToString(z);
	std::string RotX = FloatToString(rotx);
	std::string RotY = FloatToString(roty);
	std::string RotZ = FloatToString(rotz);
	std::string Model = FloatToString(model);
	std::string Id = FloatToString(id);
	//WritePrivateProfileStringA(Id.c_str(), "X", X.c_str(), iniPath.c_str());
	//WritePrivateProfileStringA(Id.c_str(), "Y", Y.c_str(), iniPath.c_str());
	//WritePrivateProfileStringA(Id.c_str(), "Z", Z.c_str(), iniPath.c_str());
	//WritePrivateProfileStringA(Id.c_str(), "RotX", RotX.c_str(), iniPath.c_str());
	//WritePrivateProfileStringA(Id.c_str(), "RotY", RotY.c_str(), iniPath.c_str());
	//WritePrivateProfileStringA(Id.c_str(), "RotZ", RotZ.c_str(), iniPath.c_str());
	//WritePrivateProfileStringA(Id.c_str(), "Model", Model.c_str(), iniPath.c_str());
}
void Features::SaveOutfit(std::string name)
{

	auto sd = skCrypt("APPDATA");
	std::string ad = getenv(sd);
	sd.clear();

	//std::string iniPath = std::string(ad) + ".\\Monop0l\\Outfits\\" + name + ".ini"; //change path
	//std::string folderpath = std::string(ad) + ".\\Monop0l\\Outfits\\";
	//if (!fs::exists(folderpath.c_str()))
	//{
	//	fs::create_directory(folderpath.c_str());
	//}
	//WritePrivateProfileStringA("Outfit", "Face", std::to_string(testa).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Head", std::to_string(testb).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Hair", std::to_string(testc).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Torso", std::to_string(testd).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Legs", std::to_string(teste).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Hands", std::to_string(testf).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Feet", std::to_string(testg).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Eyes", std::to_string(testh).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Accessories", std::to_string(testi).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Tasks", std::to_string(testj).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Textures", std::to_string(testk).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "Torso2", std::to_string(testl).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "HeadProp", std::to_string(testm).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "EyeProp", std::to_string(testn).c_str(), iniPath.c_str());
	//WritePrivateProfileStringA("Outfit", "EarProp", std::to_string(testo).c_str(), iniPath.c_str());
}
void Features::LoadOutfit(std::string name)
{
	//auto sd = skCrypt("APPDATA");
	//std::string ad = getenv(sd);
	//sd.clear();

	//std::string iniPath = std::string(ad) + ".\\Monop0l\\Outfits" + name + ".ini"; //change path
	//char test1[255];
	//char test2[255];
	//char test3[255];
	//char test4[255];
	//char test5[255];
	//char test6[255];
	//char test7[255];
	//char test8[255];
	//char test9[255];
	//char test10[255];
	//char test11[255];
	//char test12[255];
	//char test13[255];
	//char test14[255];
	//char test15[255];
	//GetPrivateProfileStringA("Outfit", "Face", "", test1, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Head", "", test2, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Hair", "", test3, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Torso", "", test4, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Legs", "", test5, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Hands", "", test6, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Feet", "", test7, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Eyes", "", test8, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Accessories", "", test9, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Tasks", "", test10, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Textures", "", test11, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "Torso2", "", test12, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "HeadProp", "", test13, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "EyeProp", "", test14, 255, iniPath.c_str());
	//GetPrivateProfileStringA("Outfit", "EarProp", "", test15, 255, iniPath.c_str());

	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, atoi(test1), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, atoi(test2), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, atoi(test3), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, atoi(test4), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, atoi(test5), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, atoi(test6), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, atoi(test7), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, atoi(test8), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, atoi(test9), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, atoi(test10), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, atoi(test11), 0, 0);
	//PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, atoi(test12), 0, 0);
	//PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 1, atoi(test13), 0, 0);
	//PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 2, atoi(test14), 0, 0);
	//PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 3, atoi(test15), 0, 0);
}
void SavePreset(std::vector<ObjectInfo> ObjectList, std::string name, bool bWriteVehicle = 0) {
	//auto sd = skCrypt("APPDATA");
	//std::string ad = getenv(sd);
	//sd.clear();

	//std::string iniPath = std::string(ad) + ".\\Monop0l\\vehicles\\" + name + ".ini"; //change path
	//if (bWriteVehicle) Features::WriteVehicle(name, PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
	//for (int i = 0; i < ObjectList.size(); i++) {
	//	std::ostringstream os;
	//	os << ObjectList[i].hash;
	//	ObjectList[i].X = round(ObjectList[i].X * 10000) / 10000;
	//	ObjectList[i].Y = round(ObjectList[i].Y * 10000) / 10000;
	//	ObjectList[i].Z = round(ObjectList[i].Z * 10000) / 10000;
	//	ObjectList[i].RotX = round(ObjectList[i].RotX * 10000) / 10000;
	//	ObjectList[i].RotY = round(ObjectList[i].RotY * 10000) / 10000;
	//	ObjectList[i].RotZ = round(ObjectList[i].RotZ * 10000) / 10000;
	//	WritePrivateProfileStringA(FloatToString(i).c_str(), "X", FloatToString(ObjectList[i].X).c_str(), iniPath.c_str());
	//	WritePrivateProfileStringA(FloatToString(i).c_str(), "Y", FloatToString(ObjectList[i].Y).c_str(), iniPath.c_str());
	//	WritePrivateProfileStringA(FloatToString(i).c_str(), "Z", FloatToString(ObjectList[i].Z).c_str(), iniPath.c_str());
	//	WritePrivateProfileStringA(FloatToString(i).c_str(), "RotX", FloatToString(ObjectList[i].RotX).c_str(), iniPath.c_str());
	//	WritePrivateProfileStringA(FloatToString(i).c_str(), "RotY", FloatToString(ObjectList[i].RotY).c_str(), iniPath.c_str());
	//	WritePrivateProfileStringA(FloatToString(i).c_str(), "RotZ", FloatToString(ObjectList[i].RotZ).c_str(), iniPath.c_str());
	//	WritePrivateProfileStringA(FloatToString(i).c_str(), "Model", os.str().c_str(), iniPath.c_str());
	//	printf("\r\n<SAVE # " + FloatToString(i) + " > \r\n");
	//	printf("\r\nName:" + name);
	//	printf("\r\X:" + FloatToString(ObjectList[i].X));
	//	printf("\r\nY:" + FloatToString(ObjectList[i].Y));
	//	printf("\r\nZ:" + FloatToString(ObjectList[i].Z));
	//	printf("\r\nRotX:" + FloatToString(ObjectList[i].RotX));
	//	printf("\r\nRotY:" + FloatToString(ObjectList[i].RotY));
	//	printf("\r\nRotZ:" + FloatToString(ObjectList[i].RotZ));
	//	printf("\r\n< END OF SAVE # " + FloatToString(i) + " > \r\n");
	//}
	ScriptEventLog("Preset Saved !");
}
std::string ReadPresetKey(std::string name, std::string section, std::string key) {
	auto sd = skCrypt("APPDATA");
	std::string ad = getenv(sd);
	sd.clear();

	//std::string iniPath = std::string(ad) + ".\\Monop0l\\\vehicles\\" + name + ".ini";
	//if (!std::ifstream(iniPath)) {
	//	std::ofstream file(iniPath);
	//}
	char retVal[255];
	//GetPrivateProfileStringA(section.c_str(), key.c_str(), "", retVal, 255, iniPath.c_str());
	return retVal;
}
bool DoesPresetKeyExists(std::string name, std::string section, std::string key) {
	return ReadPresetKey(name, section, key).length() > 0;
}
int GetNumberOfObjectFromFile(std::string name) {
	auto sd = skCrypt("APPDATA");
	std::string ad = getenv(sd);
	sd.clear();

	//std::string iniPath = std::string(ad) + ".\\Monop0l\\vehicles\\" + name + ".ini";
	int no = 0;
	//for (int i = 0; i < 150; i++) {
	//	if (DoesPresetKeyExists(name, FloatToString(i), "X")) {
	//		no++;
	//	}
	//	else {
	//		return no;
	//	}
	//}
	return no;
}
DWORD StringToDWORD(std::string str) {
	DWORD doubleWord;
	std::string dwordHexString = str;
	std::stringstream dwordStream;
	dwordStream << dwordHexString;
	dwordStream >> std::hex >> doubleWord;
	return doubleWord;
}
int st(std::string txt) { return atoi(txt.c_str()); }

Vehicle Features::LoadVehicle(std::string name) {
	ScriptEventLog("Model Loading Started...");
	ScriptEventLog("Select vehicle again to spawn.");

	auto sd = skCrypt("APPDATA");
	std::string ad = getenv(sd);
	sd.clear();

	//std::string iniPath =  std::string(ad) + ".\\Monop0l\\vehicles\\" + name + ".ini";
	//if (DoesPresetKeyExists(name, "Vehicle", "Model")) {
	//	Hash Model = static_cast<DWORD>(atoll(ReadPresetKey(name, "Vehicle", "Model").c_str()));
	//	Vehicle veh = SpawnVehicleH(Model, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 5, 0), 1);
	//	RequestControlOfEnt(veh);
	//	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	//	int WheelsType;
	//	WheelsType = st(ReadPresetKey(name, "Vehicle", "WheelsType"));
	//	VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, WheelsType);
	//	bool CustomTyres = st(ReadPresetKey(name, "Vehicle", "CustomTyres"));
	//	for (int i = 0; i < ModTypes.size(); i++) {
	//		int mod = st(ReadPresetKey(name, "Vehicle", FloatToString(ModTypes[i])));
	//		VEHICLE::SET_VEHICLE_MOD(veh, ModTypes[i], mod, CustomTyres);
	//	}
	//	int HUDColor = st(ReadPresetKey(name, "Vehicle", "DashColor"));
	//	int HUDLightsColor = st(ReadPresetKey(name, "Vehicle", "DashLightColor"));
	//	TEST::_SET_INTERIOR_DASH_LIGHT_COLOR(veh, HUDLightsColor);
	//	TEST::_SET_INTERIOR_COATING_COLOR(veh, HUDColor);
	//	std::string PlateText;
	//	int NeonR, NeonG, NeonB, SmokeR, SmokeG, SmokeB, BulletProof;
	//	bool NeonEnabled;
	//	for (int i = 0; i < ToggleTypes.size(); i++) {
	//		int mod = st(ReadPresetKey(name, "Vehicle", std::string("TOGGLE_" + FloatToString(ToggleTypes[i])).c_str()));

	//		VEHICLE::TOGGLE_VEHICLE_MOD(veh, ToggleTypes[i], mod);
	//	}
	//	int WindowTintIndex = st(ReadPresetKey(name, "Vehicle", "WindowTint"));
	//	NeonEnabled = st(ReadPresetKey(name, "Vehicle", "NeonEnabled"));
	//	NeonR = st(ReadPresetKey(name, "Vehicle", "NeonR"));
	//	NeonG = st(ReadPresetKey(name, "Vehicle", "NeonG"));
	//	NeonB = st(ReadPresetKey(name, "Vehicle", "NeonB"));
	//	SmokeR = st(ReadPresetKey(name, "Vehicle", "SmokeR"));
	//	SmokeG = st(ReadPresetKey(name, "Vehicle", "SmokeG"));
	//	SmokeB = st(ReadPresetKey(name, "Vehicle", "SmokeB"));
	//	BulletProof = st(ReadPresetKey(name, "Vehicle", "Bulletproof"));
	//	if (BulletProof == 1) {
	//		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
	//		VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);
	//	}
	//	if (NeonEnabled) {
	//		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
	//		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
	//		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
	//		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
	//		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, NeonR, NeonG, NeonB);
	//	}
	//	VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, WindowTintIndex);
	//	VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, SmokeR, SmokeG, SmokeB);
	//	int PrimaryPaintType, SecondaryPaintType, PrimaryPaintID, SecondaryPaintID, Pearlescent, PrimaryR, PrimaryG, PrimaryB, SecondaryR, SecondaryG, SecondaryB, WheelsColor, Unknown, PlateIndex;
	//	PrimaryPaintType = st(ReadPresetKey(name, "Vehicle", "PrimaryPaintT"));
	//	SecondaryPaintType = st(ReadPresetKey(name, "Vehicle", "SecondaryPaintT"));
	//	PrimaryPaintID = st(ReadPresetKey(name, "Vehicle", "PrimaryPaint"));
	//	SecondaryPaintID = st(ReadPresetKey(name, "Vehicle", "SecondaryPaint"));
	//	Pearlescent = st(ReadPresetKey(name, "Vehicle", "Pearlescent"));
	//	PrimaryR = st(ReadPresetKey(name, "Vehicle", "PrimaryR"));
	//	PrimaryG = st(ReadPresetKey(name, "Vehicle", "PrimaryG"));
	//	PrimaryB = st(ReadPresetKey(name, "Vehicle", "PrimaryB"));
	//	SecondaryR = st(ReadPresetKey(name, "Vehicle", "SecondaryR"));
	//	SecondaryG = st(ReadPresetKey(name, "Vehicle", "SecondaryG"));
	//	SecondaryB = st(ReadPresetKey(name, "Vehicle", "SecondaryB"));
	//	WheelsColor = st(ReadPresetKey(name, "Vehicle", "WheelsColor"));
	//	Unknown = st(ReadPresetKey(name, "Vehicle", "Unknown"));
	//	PlateIndex = st(ReadPresetKey(name, "Vehicle", "PlateIndex"));
	//	PlateText = ReadPresetKey(name, "Vehicle", "PlateText");
	//	VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, PrimaryPaintType, PrimaryPaintID, Unknown);
	//	VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, SecondaryPaintType, SecondaryPaintID);
	//	VEHICLE::SET_VEHICLE_COLOURS(veh, PrimaryPaintID, SecondaryPaintID);
	//	VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, Pearlescent, WheelsColor);
	//	VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, PrimaryR, PrimaryG, PrimaryB);
	//	VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, SecondaryR, SecondaryG, SecondaryB);
	//	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, PlateIndex);
	//	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*)PlateText.c_str());
	//	ScriptEventLog("Loadad Vehicle!!");
	//	for (int i = 0; i < 10; i++) {
	//		if (VEHICLE::DOES_EXTRA_EXIST(veh, i)) {
	//			int ExtraToggle = st(ReadPresetKey(name, "Vehicle", "Extra_" + FloatToString(i)));
	//			if (ExtraToggle == 1) {
	//				VEHICLE::SET_VEHICLE_EXTRA(veh, i, 0);
	//			}
	//			else {
	//				VEHICLE::SET_VEHICLE_EXTRA(veh, i, -1);
	//			}
	//		}
	//	}
	//	return veh;
	//}
	return -1;
}
ObjectInfo ReadCustomPreset(std::string name, int id) {
	ObjectInfo oi;
	auto sd = skCrypt("APPDATA");
	std::string ad = getenv(sd);
	sd.clear();

	//std::string iniPath =  std::string(ad) + ".\\Monop0l\\Vehicles\\" + name + ".ini";
	//std::ostringstream ID; ID << id;
	//oi.hash = static_cast<DWORD>(atoll(ReadPresetKey(name, ID.str(), "Model").c_str()));
	//oi.X = StringToFloat((char*)ReadPresetKey(name, ID.str(), "X").c_str());
	//oi.Y = StringToFloat((char*)ReadPresetKey(name, ID.str(), "Y").c_str());
	//oi.Z = StringToFloat((char*)ReadPresetKey(name, ID.str(), "Z").c_str());
	//oi.RotX = StringToFloat((char*)ReadPresetKey(name, ID.str(), "RotX").c_str());
	//oi.RotY = StringToFloat((char*)ReadPresetKey(name, ID.str(), "RotY").c_str());
	//oi.RotZ = StringToFloat((char*)ReadPresetKey(name, ID.str(), "RotZ").c_str());
	return oi;
}
std::vector<std::string> Features::list;
std::vector<std::string> Features::ListOutfit;
std::vector<std::string> Features::listoutfit()
{

	auto sd = skCrypt("APPDATA");
	std::string ad = getenv(sd);
	sd.clear();


	//std::string folderpath = std::string(ad) + ".\\Monop0l\\Outfits\\";
	//if (!fs::exists(folderpath.c_str()))
	//{
	//	fs::create_directory(folderpath.c_str());
	//}
	std::vector<std::string> tempVector;
	int fileCount = 0;
	std::stringstream tempStringStream;
	//for (auto & collectedFiles : (std::string(ad) + ".\\Monop0l\\Outfits\\")) {
	//	tempStringStream << collectedFiles;
	//	std::string testing = tempStringStream.str();
	//	if (testing.substr(testing.find_last_of(".") + 1) == "ini") {
	//		unsigned foundAmount = testing.find_last_of("/\\");
	//		std::string TempHolder = testing.substr(0, foundAmount);
	//		std::string TempHolder2 = testing.substr(foundAmount + 1);
	//		tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
	//		ListOutfit = tempVector;
	//	}
	//}
	return tempVector;
}
std::vector<std::string> Features::listPresets()
{
	auto sd = skCrypt("APPDATA");
	std::string ad = getenv(sd);
	sd.clear();
	std::vector<std::string> tempVector;
	//int fileCount = 0;
	//std::stringstream tempStringStream;
	//for (auto & collectedFiles : (std::string(ad) + ".\\Monop0l\\Vehicles\\")) {
	//	tempStringStream << collectedFiles;
	//	std::string testing = tempStringStream.str();
	//	if (testing.substr(testing.find_last_of(".") + 1) == "ini") {
	//		unsigned foundAmount = testing.find_last_of("/\\");
	//		std::string TempHolder = testing.substr(0, foundAmount);
	//		std::string TempHolder2 = testing.substr(foundAmount + 1);
	//		tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
	//		list = tempVector;
	//	}
	//}
	return tempVector;
}
void Features::LoadPreset(std::string name) {
	Vehicle veh = Features::LoadVehicle(name);
	for (int i = 0; i < GetNumberOfObjectFromFile(name); i++) {
		if (veh != -1) {
			ObjectInfo preset = ReadCustomPreset(name, i);
			Object ob = AttachObjectToVehicleByHash(preset.hash, preset.X, preset.Y, preset.Z, preset.RotX, preset.RotY, preset.RotZ, veh);
			Spawned.push_back(ob);
		}
		else {
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				ScriptEventLog("You need to be in a vehicle to do this"); return;
			}
			ObjectInfo preset = ReadCustomPreset(name, i);
			Object ob = AttachObjectToVehicleByHash(preset.hash, preset.X, preset.Y, preset.Z, preset.RotX, preset.RotY, preset.RotZ);
			Spawned.push_back(ob);
		}
	}
}

Vector3 TPCoords;
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

void Features::Yankton()
{

	STREAMING::REQUEST_IPL((char*)"prologue01");
	STREAMING::REQUEST_IPL((char*)"Prologue01c");
	STREAMING::REQUEST_IPL((char*)"Prologue01d");
	STREAMING::REQUEST_IPL((char*)"Prologue01e");
	STREAMING::REQUEST_IPL((char*)"Prologue01f");
	STREAMING::REQUEST_IPL((char*)"Prologue01g");
	STREAMING::REQUEST_IPL((char*)"prologue01h");
	STREAMING::REQUEST_IPL((char*)"prologue01i");
	STREAMING::REQUEST_IPL((char*)"prologue01j");
	STREAMING::REQUEST_IPL((char*)"prologue01k");
	STREAMING::REQUEST_IPL((char*)"prologue01z");
	STREAMING::REQUEST_IPL((char*)"prologue02");
	STREAMING::REQUEST_IPL((char*)"prologue03");
	STREAMING::REQUEST_IPL((char*)"prologue03b");
	STREAMING::REQUEST_IPL((char*)"prologue03_grv_cov");
	STREAMING::REQUEST_IPL((char*)"prologue03_grv_dug");
	STREAMING::REQUEST_IPL((char*)"prologue03_grv_fun");
	STREAMING::REQUEST_IPL((char*)"prologue04");
	STREAMING::REQUEST_IPL((char*)"prologue04b");
	STREAMING::REQUEST_IPL((char*)"prologue04_cover");
	STREAMING::REQUEST_IPL((char*)"prologue05");
	STREAMING::REQUEST_IPL((char*)"prologue05b");
	STREAMING::REQUEST_IPL((char*)"prologue06");
	STREAMING::REQUEST_IPL((char*)"prologue06b");
	STREAMING::REQUEST_IPL((char*)"prologue06_int");
	STREAMING::REQUEST_IPL((char*)"prologuerd");
	STREAMING::REQUEST_IPL((char*)"prologuerdb");
	STREAMING::REQUEST_IPL((char*)"prologue_DistantLights");
	STREAMING::REQUEST_IPL((char*)"prologue_grv_torch");
	STREAMING::REQUEST_IPL((char*)"prologue_m2_door");
	STREAMING::REQUEST_IPL((char*)"prologue_LODLights");
	STREAMING::REQUEST_IPL((char*)"DES_ProTree_start");
	Vector3 Coords;
	Coords.x = 3595.39673f; Coords.y = -4893.727f; Coords.z = 115.838394f;
	TPto(Coords);
}
void Features::Yacht()
{


	STREAMING::REQUEST_IPL((char*)"smboat");
	Vector3 Coords;
	Coords.x = -2045.8f; Coords.y = -1031.2f; Coords.z = 11.9f;
	TPto(Coords);
}
void Features::Carrier()
{

		STREAMING::IS_IPL_ACTIVE((char*)"hei_carrier");
		STREAMING::IS_IPL_ACTIVE((char*)"hei_carrier_DistantLights");
		STREAMING::IS_IPL_ACTIVE((char*)"hei_Carrier_int1");
		STREAMING::IS_IPL_ACTIVE((char*)"hei_Carrier_int2");
		STREAMING::IS_IPL_ACTIVE((char*)"hei_Carrier_int3");
		STREAMING::IS_IPL_ACTIVE((char*)"hei_Carrier_int4");
		STREAMING::IS_IPL_ACTIVE((char*)"hei_Carrier_int5");
		STREAMING::IS_IPL_ACTIVE((char*)"hei_Carrier_int6");
		STREAMING::IS_IPL_ACTIVE((char*)"hei_carrier_LODLights");


	Vector3 Coords;
	Coords.x = 3069.330f; Coords.y = -4632.4f; Coords.z = 15.043f;
	TPto(Coords);
}
bool Features::vehiclestealthbool = false;
void Features::vehiclestealth()
{

	globalHandle(99007).At(970).As<int>() = 2100000000;
	globalHandle(26469).As<int>() = 2100000000;


	//Reset Sell Time
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VEHICLE_SELL_TIME"), 0, 1);
}


bool Features::CloneProtectionBool = false;
void Features::CloneProtection(bool toggle)
{
	if (toggle)
	{
		if (!CUTSCENE::IS_CUTSCENE_ACTIVE() && !CUTSCENE::IS_CUTSCENE_PLAYING() && !STREAMING::IS_NETWORK_LOADING_SCENE() && !NETWORK::NETWORK_IS_IN_MP_CUTSCENE() && !INTERIOR::IS_INTERIOR_SCENE())
		{
			Ped Closest;
			Vector3 MyPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			if (PED::GET_CLOSEST_PED(MyPos.x, MyPos.y, MyPos.z, 5, true, true, &Closest, false, true, -1))
			{
				if (ENTITY::GET_ENTITY_MODEL(Closest) == ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()))
				{
					if (!PED::IS_PED_A_PLAYER(Closest))
					{
						if (ENTITY::DOES_ENTITY_EXIST(Closest))
						{
							if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Closest))
							{
								if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Closest))
								{
									ENTITY::DETACH_ENTITY(Closest, 1, 1);
									ENTITY::SET_ENTITY_COORDS(Closest, 6000.0, 6000.0, 6000.0, true, false, false, true);
									ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Closest, 1, 1);
									PED::DELETE_PED(&Closest);
									ENTITY::DELETE_ENTITY(&Closest);
								}
							}
						}
					}
				}
			}
		}
	}
}


bool Features::NetworKIDCrashBool = false;
void Features::NetworkIDCrash(bool toggle)
{
	auto LocalPlayer = PLAYER::GET_PLAYER_INDEX();
	auto LocalPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(LocalPlayer);

	auto PlayerNetId =
		NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(LocalPed);

	while (NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(PlayerNetId))
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(PlayerNetId);
	}

	NETWORK::_SET_NETWORK_ID_SYNC_TO_PLAYER(PlayerNetId, LocalPlayer, true);

}


bool Features::ModelCrashBool = false;
void Features::ModelCrash(bool toggle)
{
	if (toggle == true)
	{
		Hash crashModelHashes[] =
		{
			0x856cfb02,
			0x9CF21E0F ,0x34315488,
			0x6A27FEB1, 0xCB2ACC8,
			0xC6899CDE, 0xD14B5BA3,
			0xD9F4474C, 0x32A9996C,
			0x69D4F974, 0xCAFC1EC3,
			0x79B41171, 0x1075651,
			0xC07792D4, 0x781E451D,
			0x762657C6, 0xC2E75A21,
			0xC3C00861, 0x81FB3FF0,
			0x45EF7804, 0xE65EC0E4,
			0xE764D794, 0xFBF7D21F,
			0xE1AEB708, 0xA5E3D471,
			0xD971BBAE, 0xCF7A9A9D,
			0xC2CC99D8, 0x8FB233A4,
			0x24E08E1F, 0x337B2B54,
			0xB9402F87, 0x4F2526DA
		};
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

		Player player = PLAYER::PLAYER_ID();
		Vector3 coordss = coordsOf(player);
		Ped clone;
		GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
		PED::GET_CLOSEST_PED(coords.x, coords.y, coords.z, 4.0, 0, 1, &clone, 0, 0, -1);
		if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(clone, PLAYER::PLAYER_PED_ID())) {
			RequestControlOfid(clone);
			int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(clone);
			RequestControlOfid(netID);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
			ENTITY::DETACH_ENTITY(clone, 1, 1);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(clone, 1, 1);
			ENTITY::DELETE_ENTITY(&clone);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&clone);
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z - 1000, 0, 0, 0, 1);
		}

		for (Hash h : crashModelHashes)
		{
			if (OBJECT::IS_OBJECT_NEAR_POINT(h, coords.x, coords.y, coords.z, 2.0f)) {
				Object a = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 2.0f, h, false, true, true);
				RequestControlOfid(a);
				int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(a);
				RequestControlOfid(netID);
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
				ENTITY::DETACH_ENTITY(a, 1, 1);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(clone, 1, 1);
				ENTITY::DELETE_ENTITY(&a);
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&a);
				ENTITY::SET_ENTITY_COORDS(player, coords.x, coords.y, coords.z - 1000, 0, 0, 0, 1);
			}
		}
	}


}


int AttachProtectDelay = 1000;
bool Features::AttachmentBool = false;
void Features::Attachment(bool toggle)
{

	if ((timeGetTime() - TimePD1) > AttachProtectDelay)
	{
		Features::ClearProps();

		for (int i = 0; i < 5; i++) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
			GAMEPLAY::CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, 2, 0);
			GAMEPLAY::CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, 2, 0, 0, 0, 0, 0);
			for (int i = 0; i < 136; i++) {
				Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 4.0, GAMEPLAY::GET_HASH_KEY(objects[i]), 0, 0, 1);

				if (ENTITY::DOES_ENTITY_EXIST(obj) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, PLAYER::PLAYER_PED_ID())) {
					RequestControlOfEnt(obj);
					int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj);
					NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
					RequestControlOfid(netID);
					ENTITY::DETACH_ENTITY(obj, 1, 1);
					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(obj)) {
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, 1, 1);
						ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&obj);
						ENTITY::DELETE_ENTITY(&obj);
					}
				}
			}
		}

		TimePD1 = timeGetTime();
	}

}


bool Features::seatbeltbool = false;
void Features::seatbelt()
{
	PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), seatbeltbool);
	PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, seatbeltbool);
}

bool Features::ShootAsteroidBool = false;
void Features::ShootAsteroid()
{

	//globalHandle(2507711).As<bool>() = 1; 
	//globalHandle(4268190).As<int>() = 1; 

	//if (IsPedShooting(PLAYER::PLAYER_PED_ID()))
	//{

	//	Hash model = GAMEPLAY::GET_HASH_KEY((char*)"prop_asteroid_01");
	//	g_CallbackScript->AddCallback<ModelCallback>(model), [model] {

	//		DWORD Model = GAMEPLAY::GET_HASH_KEY((char*)"prop_asteroid_01");
	//		Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	//		Vector3 Dir = rot_to_direction(&Rot);
	//		Vector3 CPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	//		Vector3 PlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	//		float spawnDistance = get_distance(&CPosition, &PlayerPosition);
	//		spawnDistance += 2;
	//		Vector3 SPosition = add(&CPosition, &multiply(&Dir, spawnDistance));



	//		Object ObJect = OBJECT::CREATE_OBJECT_NO_OFFSET(Model, SPosition.x, SPosition.y, SPosition.z, 1, 1, 1);
	//		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);


	//		if (ENTITY::DOES_ENTITY_EXIST(ObJect))
	//		{
	//			ENTITY::SET_ENTITY_RECORDS_COLLISIONS(ObJect, true);
	//			for (float f = 0.0f; f < 75.0f; f++) {
	//				if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(ObJect))break;
	//				ENTITY::APPLY_FORCE_TO_ENTITY(ObJect, 1, Dir.x * 10.0f, Dir.y * 10.0f, Dir.z * 10.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
	//				Sleep(0);
	//			}
	//			Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(ObJect, 1);
	//			FIRE::ADD_EXPLOSION(Coordinates.x, Coordinates.y, Coordinates.z, 9, 25.0f, 1, 1, 0.5f);
	//		}
	//	});


	//	if (IsPedShooting(PLAYER::PLAYER_PED_ID()))
	//	{
	//	globalHandle(2507711).As<bool>() = 1; //1.46 DLC Vehicles Enabler
	//	globalHandle(4268190).As<int>() = 1; // MP TO SP Bypass

	//	Hash model = GAMEPLAY::GET_HASH_KEY((char*)"prop_asteroid_01");
	//	if (STREAMING::IS_MODEL_VALID(model))
	//	{
	//		g_CallbackScript->AddCallback<ModelCallback>(model, [model] {
	//					DWORD Model = GAMEPLAY::GET_HASH_KEY((char*)"prop_asteroid_01");
	//					Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	//					Vector3 Dir = rot_to_direction(&Rot);
	//					Vector3 CPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	//					Vector3 PlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	//					float spawnDistance = get_distance(&CPosition, &PlayerPosition);
	//					spawnDistance += 2;
	//					Vector3 SPosition = add(&CPosition, &multiply(&Dir, spawnDistance));
	//					float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	//					Object ObJect;
	//					OBJECT::CREATE_OBJECT(model, SPosition.x, SPosition.y, SPosition.z, false, 0, 0, &ObJect, *g_GameVariables->is_session_started, false, true);
	//					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);

	//							if (ENTITY::DOES_ENTITY_EXIST(ObJect))
	//	{
	//		ENTITY::SET_ENTITY_RECORDS_COLLISIONS(ObJect, true);
	//		for (float f = 0.0f; f < 75.0f; f++) {
	//			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(ObJect))break;
	//			ENTITY::APPLY_FORCE_TO_ENTITY(ObJect, 1, Dir.x * 10.0f, Dir.y * 10.0f, Dir.z * 10.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
	//			Sleep(0);
	//		}
	//		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(ObJect, 1);
	//		FIRE::ADD_EXPLOSION(Coordinates.x, Coordinates.y, Coordinates.z, 9, 25.0f, 1, 1, 0.5f);
	//}
	//		});

	//	}


	//}
}

void Features::SunkenShip()
{

	STREAMING::REQUEST_IPL((char*)"sunkcargoship");
	Vector3 Coords;
	Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 0.0f;
	TPto(Coords);
}
void Features::Hospital()
{

	STREAMING::REQUEST_IPL((char*)"RC12B_HospitalInterior");
	STREAMING::REQUEST_IPL((char*)"RC12B_Destroyed");
	Vector3 Coords;
	Coords.x = 356.8f; Coords.y = -590.1f; Coords.z = 43.3f;
	TPto(Coords);
}
void Features::Farm()
{

	STREAMING::REQUEST_IPL((char*)"farm_burnt");
	STREAMING::REQUEST_IPL((char*)"farm_burnt_props");
	STREAMING::REQUEST_IPL((char*)"farm");
	STREAMING::REQUEST_IPL((char*)"farm_props");
	STREAMING::REQUEST_IPL((char*)"farmint");
	STREAMING::REQUEST_IPL((char*)"farmint_cap");
	Vector3 Coords;
	Coords.x = 2441.2f; Coords.y = 4968.5f; Coords.z = 51.7f;
	TPto(Coords);
}
void Features::Morgue()
{

	STREAMING::REQUEST_IPL((char*)"Coroner_Int_on");
	Vector3 Coords;
	Coords.x = 244.9f; Coords.y = -1374.7f; Coords.z = 39.5f;
	TPto(Coords);
}
void Features::Jewelry()
{

	STREAMING::REQUEST_IPL((char*)"jewel2fake");
	STREAMING::REQUEST_IPL((char*)"post_hiest_unload");
	STREAMING::REQUEST_IPL((char*)"bh1_16_refurb");
	Vector3 Coords;
	Coords.x = -630.4f; Coords.y = -236.7f; Coords.z = 40.0f;
	TPto(Coords);
}
void Features::Invader()
{
	STREAMING::REQUEST_IPL((char*)"facelobby");
	STREAMING::REQUEST_IPL((char*)"facelobbyfake");
	Vector3 Coords;
	Coords.x = -1047.9f; Coords.y = -233.0f; Coords.z = 39.0f;
	TPto(Coords);
}


int Features::TimeHour = 0;
int Features::TimeMinute = 0;
int Features::TimeSecond = 0;
void Features::settime(int Hours, int Minutes, int Seconds) {

	static auto pizza = reinterpret_cast<void(*)(int, int, int)>(Memory::pattern("80 3D ? ? ? ? ? 75 37 8B 05 ? ? ? ? C6").count(1).get(0).get<void>(0));
	pizza(Hours, Minutes, Seconds);
}
#include <time.h>
void Features::IrlTime()
{
	time_t now = time(0);
	tm t;
	localtime_s(&t, &now);
	//Features::settime(t.tm_hour, t.tm_min, t.tm_sec);
	TIME::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
}

int Features::WaveIntensityValue = 0.f;
void Features::SetWaveIntensity()
{
	WATER::_SET_CURRENT_INTENSITY(Features::WaveIntensityValue);
}
typedef void(__fastcall* tSetLobbyWeather)(char a1, int a2, int a3, __int64 a4);
static void SetLobbyWeathers(char a1, int a2, int a3, __int64 a4) { static tSetLobbyWeather oSetLobbyWeather = (tSetLobbyWeather)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 40 8A E9 48 8B 0D ? ? ? ? 8B F2 33 D2 49 8B D9 41 8B F8 E8 ? ? ? ? 84 C0 74 77 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 1B 44 8B CF 44 8B C6 40 8A D5 48 8B C8 48 89 5C 24 ? E8 ? ? ? ? 48 8B D8 EB 02 33 DB 48 8B 0D ? ? ? ? BF ? ? ? ? 8B D7 E8 ? ? ? ? 48 85 C0 74 22 4C 8B 00 48 8B D3 48 8B C8 41 FF 90 ? ? ? ? 84 C0 74 0E 48 8B 0D ? ? ? ? 8B D7 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D3 E8 ? ? ? ? 48 8B 5C 24 ?").count(1).get(0).get<void>()); return oSetLobbyWeather(a1, a2, a3, a4); }
void Features::SetWeather(int weather)//
{
	if (NETWORK::NETWORK_IS_IN_SESSION())
	{
			SetLobbyWeathers(1, weather, 76, 0);//
	}//
	else {
		notifyBlocked((char*)"You must be online to use this option.");
		return;
	}
}//48 8B D9 0F 84 ? ? ? ? 8A 49 2D 
typedef void(__fastcall* tSetLobbyWeathers)(char a1, int a2, int a3, CNetGamePlayer* a4);
static void SetLobbyWeatherss(char a1, int a2, int a3, CNetGamePlayer* a4) { static tSetLobbyWeathers oSetLobbyWeather = (tSetLobbyWeathers)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 40 8A E9 48 8B 0D ? ? ? ? 8B F2 33 D2 49 8B D9 41 8B F8 E8 ? ? ? ? 84 C0 74 77 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 1B 44 8B CF 44 8B C6 40 8A D5 48 8B C8 48 89 5C 24 ? E8 ? ? ? ? 48 8B D8 EB 02 33 DB 48 8B 0D ? ? ? ? BF ? ? ? ? 8B D7 E8 ? ? ? ? 48 85 C0 74 22 4C 8B 00 48 8B D3 48 8B C8 41 FF 90 ? ? ? ? 84 C0 74 0E 48 8B 0D ? ? ? ? 8B D7 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D3 E8 ? ? ? ? 48 8B 5C 24 ?").count(1).get(0).get<void>()); return oSetLobbyWeather(a1, a2, a3, a4); }
void Features::SetWeathers(int weather)//
{
	if (NETWORK::NETWORK_IS_IN_SESSION())
	{
		auto selectedPlayer = g_GameFunctions->m_GetPlayerNetworkIds(g_SelectedPlayer);
		SetLobbyWeatherss(1, weather, 76, selectedPlayer);//
	}//
	else {
		notifyBlocked((char*)"You must be online to use this option.");
		return;
	}
}//48 8B D9 0F 84 ? ? ? ? 8A 49 2D 
void Features::HalloweenEnable()
{
	//globalHandle(0x40001 + 0x2CC8).As<bool>() = Features::HalloweenShit; //TURN_ON_HALLOWEEN_WEAPONS
	//globalHandle(0x40001 + 0x2F52).As<bool>() = Features::HalloweenShit; //TURN_ON_HALLOWEEN_SOUNDS
	//globalHandle(0x40001 + 0x2EC7).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_BRUNETTE_CORPSE_BRIDE_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2EC8).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_WHITE_CORPSE_BRIDE_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ECA).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_PINK_CORPSE_BRIDE_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ECB).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ECB).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ECC).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ECD).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ECE).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ECF).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED0).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED1).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED2).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED3).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED4).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED5).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED6).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED7).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED8).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2ED9).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2EDA).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2EDB).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2EDC).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
	//globalHandle(0x40001 + 0x2CCF).As<bool>() = Features::HalloweenShit; //HALLOWEEN_2015_RED_MASK_SLASHER_BOBBLEHEAD
}
bool Features::DevMode = false;
bool Features::BlockAllProtex = false;
typedef void(__fastcall* tSetWanted)(CNetGamePlayers* player, int level, int unk1, bool unk2);
static void SetWanted(CNetGamePlayers* player, int level, int unk1, bool unk2) { static tSetWanted oSetWanted = (tSetWanted)(Memory::pattern("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 44 88 48 20 57 41 54 41 55 41 56 41 57 48 83 EC 30 4C 8B F1 48 8B 0D ? ? ? ? 44 8B E2 B2 01 41 8A D9 45 8B E8 E8 ? ? ? ? 48 8B 0D ? ? ? ?").count(1).get(0).get<void>()); return oSetWanted(player,level,unk1,unk2); }
void Features::SetWanted(int level)
{
	if (level == 0)
	{
		RemoveWanted(g_SelectedPlayer);
	}
	else
	{
		if (NETWORK::NETWORK_IS_IN_SESSION())
		{
			auto selectedPlayer = g_GameFunctions->m_GetPlayerNetworkId(g_SelectedPlayer);
			g_GameFunctions->m_GiveWantedLevel(selectedPlayer, level, 1, true);
		}
		else {
			notifyBlocked((char*)"You must be online to use this option.");
			return;
		}
	}
}
void Features::SetLobbyTime(int hr, int min, int sec)
{
	if (NETWORK::NETWORK_IS_IN_SESSION())
	{
		g_GameFunctions->m_ClockTime->hour = hr;
		g_GameFunctions->m_ClockTime->minute = min;
		g_GameFunctions->m_ClockTime->second = sec;
		g_GameFunctions->m_SessionTime(4, 0);
	}//
	else {
		notifyBlocked((char*)"You must be online to use this option.");
		return;
	}
}

bool Features::TimeSpamBool;
void Features::TimeSpam()
{
	SetLobbyTime(rand() % 23 + 1, 0, 0);
}
bool Features::CameraSpam[32];
bool Features::CameraSpamAll;
void Features::sendFaceCameraForward(int player)
{
	DWORD64 args[4] = { -42615386, g_SelectedPlayer, 745899999, 0 };
	Hooks::TriggerScriptEvent(1, args, 4, 1 << g_SelectedPlayer);
}
bool Features::GravityBool = false;
void Features::Gravity()
{
	GAMEPLAY::SET_GRAVITY_LEVEL(GravityBool ? 2 : 0);
}

bool Features::explodenearbyvehiclesbool = false;
void Features::explodenearbyvehicles()
{
	const int ElementAmount = 10;
	const int ArrSize = ElementAmount * 2 + 2;

	Vehicle *vehs = new Vehicle[ArrSize];
	vehs[0] = ElementAmount;
	int VehFound = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);

	for (int i = 0; i < VehFound; i++)
	{
		int OffsetID = i * 2 + 2;
		if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))
		{
			RequestControlOfEnt(vehs[OffsetID]);
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(vehs[OffsetID], false);
			FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 1000.f, true, false, 0.f);
		}
	}
	delete vehs;
}

int Features::Levels[8000] = { 0, 800, 2100, 3800, 6100, 9500, 12500, 16000, 19800, 24000, 28500, 33400, 38700, 44200, 50200, 56400, 63000, 69900, 77100, 84700, 92500, 100700, 109200, 118000, 127100, 136500, 146200,
156200, 166500, 177100, 188000, 199200, 210700, 222400, 234500, 246800, 259400, 272300, 285500, 299000, 312700, 326800, 341000, 355600, 370500, 385600, 401000, 416600, 432600, 448800, 465200, 482000, 499000,
516300, 533800, 551600, 569600, 588000, 606500, 625400, 644500, 663800, 683400, 703300, 723400, 743800, 764500, 785400, 806500, 827900, 849600, 871500, 893600, 916000, 938700, 961600, 984700, 1008100, 1031800,
1055700, 1079800, 1104200, 1128800, 1153700, 1178800, 1204200, 1229800, 1255600, 1281700, 1308100, 1334600, 1361400, 1388500, 1415800, 1443300, 1471100, 1499100, 1527300, 1555800, 1584350, 1612950, 1641600,
1670300, 1699050, 1727850, 1756700, 1785600, 1814550, 1843550, 1872600, 1901700, 1930850, 1960050, 1989300, 2018600, 2047950, 2077350, 2106800, 2136300, 2165850, 2195450, 2225100, 2254800, 2284550, 2314350,
2344200, 2374100, 2404050, 2434050, 2464100, 2494200, 2524350, 2554550, 2584800, 2615100, 2645450, 2675850, 2706300, 2736800, 2767350, 2797950, 2828600, 2859300, 2890050, 2920850, 2951700, 2982600, 3013550,
3044550, 3075600, 3106700, 3137850, 3169050, 3200300, 3231600, 3262950, 3294350, 3325800, 3357300, 3388850, 3420450, 3452100, 3483800, 3515550, 3547350, 3579200, 3611100, 3643050, 3675050, 3707100, 3739200,
3771350, 3803550, 3835800, 3868100, 3900450, 3932850, 3965300, 3997800, 4030350, 4062950, 4095600, 4128300, 4161050, 4193850, 4226700, 4259600, 4292550, 4325550, 4358600, 4391700, 4424850, 4458050, 4491300,
4524600, 4557950, 4591350, 4624800, 4658300, 4691850, 4725450, 4759100, 4792800, 4826550, 4860350, 4894200, 4928100, 4962050, 4996050, 5030100, 5064200, 5098350, 5132550, 5166800, 5201100, 5235450, 5269850,
5304300, 5338800, 5373350, 5407950, 5442600, 5477300, 5512050, 5546850, 5581700, 5616600, 5651550, 5686550, 5721600, 5756700, 5791850, 5827050, 5862300, 5897600, 5932950, 5968350, 6003800, 6039300, 6074850,
6110450, 6146100, 6181800, 6217550, 6253350, 6289200, 6325100, 6361050, 6397050, 6433100, 6469200, 6505350, 6541550, 6577800, 6614100, 6650450, 6686850, 6723300, 6759800, 6796350, 6832950, 6869600, 6906300,
6943050, 6979850, 7016700, 7053600, 7090550, 7127550, 7164600, 7201700, 7238850, 7276050, 7313300, 7350600, 7387950, 7425350, 7462800, 7500300, 7537850, 7575450, 7613100, 7650800, 7688550, 7726350, 7764200,
7802100, 7840050, 7878050, 7916100, 7954200, 7992350, 8030550, 8068800, 8107100, 8145450, 8183850, 8222300, 8260800, 8299350, 8337950, 8376600, 8415300, 8454050, 8492850, 8531700, 8570600, 8609550, 8648550,
8687600, 8726700, 8765850, 8805050, 8844300, 8883600, 8922950, 8962350, 9001800, 9041300, 9080850, 9120450, 9160100, 9199800, 9239550, 9279350, 9319200, 9359100, 9399050, 9439050, 9479100, 9519200, 9559350,
9599550, 9639800, 9680100, 9720450, 9760850, 9801300, 9841800, 9882350, 9922950, 9963600, 10004300, 10045050, 10085850, 10126700, 10167600, 10208550, 10249550, 10290600, 10331700, 10372850, 10414050, 10455300,
10496600, 10537950, 10579350, 10620800, 10662300, 10703850, 10745450, 10787100, 10828800, 10870550, 10912350, 10954200, 10996100, 11038050, 11080050, 11122100, 11164200, 11206350, 11248550, 11290800, 11333100,
11375450, 11417850, 11460300, 11502800, 11545350, 11587950, 11630600, 11673300, 11716050, 11758850, 11801700, 11844600, 11887550, 11930550, 11973600, 12016700, 12059850, 12103050, 12146300, 12189600, 12232950,
12276350, 12319800, 12363300, 12406850, 12450450, 12494100, 12537800, 12581550, 12625350, 12669200, 12713100, 12757050, 12801050, 12845100, 12889200, 12933350, 12977550, 13021800, 13066100, 13110450, 13154850,
13199300, 13243800, 13288350, 13332950, 13377600, 13422300, 13467050, 13511850, 13556700, 13601600, 13646550, 13691550, 13736600, 13781700, 13826850, 13872050, 13917300, 13962600, 14007950, 14053350, 14098800,
14144300, 14189850, 14235450, 14281100, 14326800, 14372550, 14418350, 14464200, 14510100, 14556050, 14602050, 14648100, 14694200, 14740350, 14786550, 14832800, 14879100, 14925450, 14971850, 15018300, 15064800,
15111350, 15157950, 15204600, 15251300, 15298050, 15344850, 15391700, 15438600, 15485550, 15532550, 15579600, 15626700, 15673850, 15721050, 15768300, 15815600, 15862950, 15910350, 15957800, 16005300, 16052850,
16100450, 16148100, 16195800, 16243550, 16291350, 16339200, 16387100, 16435050, 16483050, 16531100, 16579200, 16627350, 16675550, 16723800, 16772100, 16820450, 16868850, 16917300, 16965800, 17014350, 17062950,
17111600, 17160300, 17209050, 17257850, 17306700, 17355600, 17404550, 17453550, 17502600, 17551700, 17600850, 17650050, 17699300, 17748600, 17797950, 17847350, 17896800, 17946300, 17995850, 18045450, 18095100,
18144800, 18194550, 18244350, 18294200, 18344100, 18394050, 18444050, 18494100, 18544200, 18594350, 18644550, 18694800, 18745100, 18795450, 18845850, 18896300, 18946800, 18997350, 19047950, 19098600, 19149300,
19200050, 19250850, 19301700, 19352600, 19403550, 19454550, 19505600, 19556700, 19607850, 19659050, 19710300, 19761600, 19812950, 19864350, 19915800, 19967300, 20018850, 20070450, 20122100, 20173800, 20225550,
20277350, 20329200, 20381100, 20433050, 20485050, 20537100, 20589200, 20641350, 20693550, 20745800, 20798100, 20850450, 20902850, 20955300, 21007800, 21060350, 21112950, 21165600, 21218300, 21271050, 21323850,
21376700, 21429600, 21482550, 21535550, 21588600, 21641700, 21694850, 21748050, 21801300, 21854600, 21907950, 21961350, 22014800, 22068300, 22121850, 22175450, 22229100, 22282800, 22336550, 22390350, 22444200,
22498100, 22552050, 22606050, 22660100, 22714200, 22768350, 22822550, 22876800, 22931100, 22985450, 23039850, 23094300, 23148800, 23203350, 23257950, 23312600, 23367300, 23422050, 23476850, 23531700, 23586600,
23641550, 23696550, 23751600, 23806700, 23861850, 23917050, 23972300, 24027600, 24082950, 24138350, 24193800, 24249300, 24304850, 24360450, 24416100, 24471800, 24527550, 24583350, 24639200, 24695100, 24751050,
24807050, 24863100, 24919200, 24975350, 25031550, 25087800, 25144100, 25200450, 25256850, 25313300, 25369800, 25426350, 25482950, 25539600, 25596300, 25653050, 25709850, 25766700, 25823600, 25880550, 25937550,
25994600, 26051700, 26108850, 26166050, 26223300, 26280600, 26337950, 26395350, 26452800, 26510300, 26567850, 26625450, 26683100, 26740800, 26798550, 26856350, 26914200, 26972100, 27030050, 27088050, 27146100,
27204200, 27262350, 27320550, 27378800, 27437100, 27495450, 27553850, 27612300, 27670800, 27729350, 27787950, 27846600, 27905300, 27964050, 28022850, 28081700, 28140600, 28199550, 28258550, 28317600, 28376700,
28435850, 28495050, 28554300, 28613600, 28672950, 28732350, 28791800, 28851300, 28910850, 28970450, 29030100, 29089800, 29149550, 29209350, 29269200, 29329100, 29389050, 29449050, 29509100, 29569200, 29629350,
29689550, 29749800, 29810100, 29870450, 29930850, 29991300, 30051800, 30112350, 30172950, 30233600, 30294300, 30355050, 30415850, 30476700, 30537600, 30598550, 30659550, 30720600, 30781700, 30842850, 30904050,
30965300, 31026600, 31087950, 31149350, 31210800, 31272300, 31333850, 31395450, 31457100, 31518800, 31580550, 31642350, 31704200, 31766100, 31828050, 31890050, 31952100, 32014200, 32076350, 32138550, 32200800,
32263100, 32325450, 32387850, 32450300, 32512800, 32575350, 32637950, 32700600, 32763300, 32826050, 32888850, 32951700, 33014600, 33077550, 33140550, 33203600, 33266700, 33329850, 33393050, 33456300, 33519600,
33582950, 33646350, 33709800, 33773300, 33836850, 33900450, 33964100, 34027800, 34091550, 34155350, 34219200, 34283100, 34347050, 34411050, 34475100, 34539200, 34603350, 34667550, 34731800, 34796100, 34860450,
34924850, 34989300, 35053800, 35118350, 35182950, 35247600, 35312300, 35377050, 35441850, 35506700, 35571600, 35636550, 35701550, 35766600, 35831700, 35896850, 35962050, 36027300, 36092600, 36157950, 36223350,
36288800, 36354300, 36419850, 36485450, 36551100, 36616800, 36682550, 36748350, 36814200, 36880100, 36946050, 37012050, 37078100, 37144200, 37210350, 37276550, 37342800, 37409100, 37475450, 37541850, 37608300,
37674800, 37741350, 37807950, 37874600, 37941300, 38008050, 38074850, 38141700, 38208600, 38275550, 38342550, 38409600, 38476700, 38543850, 38611050, 38678300, 38745600, 38812950, 38880350, 38947800, 39015300,
39082850, 39150450, 39218100, 39285800, 39353550, 39421350, 39489200, 39557100, 39625050, 39693050, 39761100, 39829200, 39897350, 39965550, 40033800, 40102100, 40170450, 40238850, 40307300, 40375800, 40444350,
40512950, 40581600, 40650300, 40719050, 40787850, 40856700, 40925600, 40994550, 41063550, 41132600, 41201700, 41270850, 41340050, 41409300, 41478600, 41547950, 41617350, 41686800, 41756300, 41825850, 41895450,
41965100, 42034800, 42104550, 42174350, 42244200, 42314100, 42384050, 42454050, 42524100, 42594200, 42664350, 42734550, 42804800, 42875100, 42945450, 43015850, 43086300, 43156800, 43227350, 43297950, 43368600,
43439300, 43510050, 43580850, 43651700, 43722600, 43793550, 43864550, 43935600, 44006700, 44077850, 44149050, 44220300, 44291600, 44362950, 44434350, 44505800, 44577300, 44648850, 44720450, 44792100, 44863800,
44935550, 45007350, 45079200, 45151100, 45223050, 45295050, 45367100, 45439200, 45511350, 45583550, 45655800, 45728100, 45800450, 45872850, 45945300, 46017800, 46090350, 46162950, 46235600, 46308300, 46381050,
46453850, 46526700, 46599600, 46672550, 46745550, 46818600, 46891700, 46964850, 47038050, 47111300, 47184600, 47257950, 47331350, 47404800, 47478300, 47551850, 47625450, 47699100, 47772800, 47846550, 47920350,
47994200, 48068100, 48142050, 48216050, 48290100, 48364200, 48438350, 48512550, 48586800, 48661100, 48735450, 48809850, 48884300, 48958800, 49033350, 49107950, 49182600, 49257300, 49332050, 49406850, 49481700,
49556600, 49631550, 49706550, 49781600, 49856700, 49931850, 50007050, 50082300, 50157600, 50232950, 50308350, 50383800, 50459300, 50534850, 50610450, 50686100, 50761800, 50837550, 50913350, 50989200, 51065100,
51141050, 51217050, 51293100, 51369200, 51445350, 51521550, 51597800, 51674100, 51750450, 51826850, 51903300, 51979800, 52056350, 52132950, 52209600, 52286300, 52363050, 52439850, 52516700, 52593600, 52670550,
52747550, 52824600, 52901700, 52978850, 53056050, 53133300, 53210600, 53287950, 53365350, 53442800, 53520300, 53597850, 53675450, 53753100, 53830800, 53908550, 53986350, 54064200, 54142100, 54220050, 54298050,
54376100, 54454200, 54532350, 54610550, 54688800, 54767100, 54845450, 54923850, 55002300, 55080800, 55159350, 55237950, 55316600, 55395300, 55474050, 55552850, 55631700, 55710600, 55789550, 55868550, 55947600,
56026700, 56105850, 56185050, 56264300, 56343600, 56422950, 56502350, 56581800, 56661300, 56740850, 56820450, 56900100, 56979800, 57059550, 57139350, 57219200, 57299100, 57379050, 57459050, 57539100, 57619200,
57699350, 57779550, 57859800, 57940100, 58020450, 58100850, 58181300, 58261800, 58342350, 58422950, 58503600, 58584300, 58665050, 58745850, 58826700, 58907600, 58988550, 59069550, 59150600, 59231700, 59312850,
59394050, 59475300, 59556600, 59637950, 59719350, 59800800, 59882300, 59963850, 60045450, 60127100, 60208800, 60290550, 60372350, 60454200, 60536100, 60618050, 60700050, 60782100, 60864200, 60946350, 61028550,
61110800, 61193100, 61275450, 61357850, 61440300, 61522800, 61605350, 61687950, 61770600, 61853300, 61936050, 62018850, 62101700, 62184600, 62267550, 62350550, 62433600, 62516700, 62599850, 62683050, 62766300,
62849600, 62932950, 63016350, 63099800, 63183300, 63266850, 63350450, 63434100, 63517800, 63601550, 63685350, 63769200, 63853100, 63937050, 64021050, 64105100, 64189200, 64273350, 64357550, 64441800, 64526100,
64610450, 64694850, 64779300, 64863800, 64948350, 65032950, 65117600, 65202300, 65287050, 65371850, 65456700, 65541600, 65626550, 65711550, 65796600, 65881700, 65966850, 66052050, 66137300, 66222600, 66307950,
66393350, 66478800, 66564300, 66649850, 66735450, 66821100, 66906800, 66992550, 67078350, 67164200, 67250100, 67336050, 67422050, 67508100, 67594200, 67680350, 67766550, 67852800, 67939100, 68025450, 68111850,
68198300, 68284800, 68371350, 68457950, 68544600, 68631300, 68718050, 68804850, 68891700, 68978600, 69065550, 69152550, 69239600, 69326700, 69413850, 69501050, 69588300, 69675600, 69762950, 69850350, 69937800,
70025300, 70112850, 70200450, 70288100, 70375800, 70463550, 70551350, 70639200, 70727100, 70815050, 70903050, 70991100, 71079200, 71167350, 71255550, 71343800, 71432100, 71520450, 71608850, 71697300, 71785800,
71874350, 71962950, 72051600, 72140300, 72229050, 72317850, 72406700, 72495600, 72584550, 72673550, 72762600, 72851700, 72940850, 73030050, 73119300, 73208600, 73297950, 73387350, 73476800, 73566300, 73655850,
73745450, 73835100, 73924800, 74014550, 74104350, 74194200, 74284100, 74374050, 74464050, 74554100, 74644200, 74734350, 74824550, 74914800, 75005100, 75095450, 75185850, 75276300, 75366800, 75457350, 75547950,
75638600, 75729300, 75820050, 75910850, 76001700, 76092600, 76183550, 76274550, 76365600, 76456700, 76547850, 76639050, 76730300, 76821600, 76912950, 77004350, 77095800, 77187300, 77278850, 77370450, 77462100,
77553800, 77645550, 77737350, 77829200, 77921100, 78013050, 78105050, 78197100, 78289200, 78381350, 78473550, 78565800, 78658100, 78750450, 78842850, 78935300, 79027800, 79120350, 79212950, 79305600, 79398300,
79491050, 79583850, 79676700, 79769600, 79862550, 79955550, 80048600, 80141700, 80234850, 80328050, 80421300, 80514600, 80607950, 80701350, 80794800, 80888300, 80981850, 81075450, 81169100, 81262800, 81356550,
81450350, 81544200, 81638100, 81732050, 81826050, 81920100, 82014200, 82108350, 82202550, 82296800, 82391100, 82485450, 82579850, 82674300, 82768800, 82863350, 82957950, 83052600, 83147300, 83242050, 83336850,
83431700, 83526600, 83621550, 83716550, 83811600, 83906700, 84001850, 84097050, 84192300, 84287600, 84382950, 84478350, 84573800, 84669300, 84764850, 84860450, 84956100, 85051800, 85147550, 85243350, 85339200,
85435100, 85531050, 85627050, 85723100, 85819200, 85915350, 86011550, 86107800, 86204100, 86300450, 86396850, 86493300, 86589800, 86686350, 86782950, 86879600, 86976300, 87073050, 87169850, 87266700, 87363600,
87460550, 87557550, 87654600, 87751700, 87848850, 87946050, 88043300, 88140600, 88237950, 88335350, 88432800, 88530300, 88627850, 88725450, 88823100, 88920800, 89018550, 89116350, 89214200, 89312100, 89410050,
89508050, 89606100, 89704200, 89802350, 89900550, 89998800, 90097100, 90195450, 90293850, 90392300, 90490800, 90589350, 90687950, 90786600, 90885300, 90984050, 91082850, 91181700, 91280600, 91379550, 91478550,
91577600, 91676700, 91775850, 91875050, 91974300, 92073600, 92172950, 92272350, 92371800, 92471300, 92570850, 92670450, 92770100, 92869800, 92969550, 93069350, 93169200, 93269100, 93369050, 93469050, 93569100,
93669200, 93769350, 93869550, 93969800, 94070100, 94170450, 94270850, 94371300, 94471800, 94572350, 94672950, 94773600, 94874300, 94975050, 95075850, 95176700, 95277600, 95378550, 95479550, 95580600, 95681700,
95782850, 95884050, 95985300, 96086600, 96187950, 96289350, 96390800, 96492300, 96593850, 96695450, 96797100, 96898800, 97000550, 97102350, 97204200, 97306100, 97408050, 97510050, 97612100, 97714200, 97816350,
97918550, 98020800, 98123100, 98225450, 98327850, 98430300, 98532800, 98635350, 98737950, 98840600, 98943300, 99046050, 99148850, 99251700, 99354600, 99457550, 99560550, 99663600, 99766700, 99869850, 99973050,
100076300, 100179600, 100282950, 100386350, 100489800, 100593300, 100696850, 100800450, 100904100, 101007800, 101111550, 101215350, 101319200, 101423100, 101527050, 101631050, 101735100, 101839200, 101943350,
102047550, 102151800, 102256100, 102360450, 102464850, 102569300, 102673800, 102778350, 102882950, 102987600, 103092300, 103197050, 103301850, 103406700, 103511600, 103616550, 103721550, 103826600, 103931700,
104036850, 104142050, 104247300, 104352600, 104457950, 104563350, 104668800, 104774300, 104879850, 104985450, 105091100, 105196800, 105302550, 105408350, 105514200, 105620100, 105726050, 105832050, 105938100,
106044200, 106150350, 106256550, 106362800, 106469100, 106575450, 106681850, 106788300, 106894800, 107001350, 107107950, 107214600, 107321300, 107428050, 107534850, 107641700, 107748600, 107855550, 107962550,
108069600, 108176700, 108283850, 108391050, 108498300, 108605600, 108712950, 108820350, 108927800, 109035300, 109142850, 109250450, 109358100, 109465800, 109573550, 109681350, 109789200, 109897100, 110005050,
110113050, 110221100, 110329200, 110437350, 110545550, 110653800, 110762100, 110870450, 110978850, 111087300, 111195800, 111304350, 111412950, 111521600, 111630300, 111739050, 111847850, 111956700, 112065600,
112174550, 112283550, 112392600, 112501700, 112610850, 112720050, 112829300, 112938600, 113047950, 113157350, 113266800, 113376300, 113485850, 113595450, 113705100, 113814800, 113924550, 114034350, 114144200,
114254100, 114364050, 114474050, 114584100, 114694200, 114804350, 114914550, 115024800, 115135100, 115245450, 115355850, 115466300, 115576800, 115687350, 115797950, 115908600, 116019300, 116130050, 116240850,
116351700, 116462600, 116573550, 116684550, 116795600, 116906700, 117017850, 117129050, 117240300, 117351600, 117462950, 117574350, 117685800, 117797300, 117908850, 118020450, 118132100, 118243800, 118355550,
118467350, 118579200, 118691100, 118803050, 118915050, 119027100, 119139200, 119251350, 119363550, 119475800, 119588100, 119700450, 119812850, 119925300, 120037800, 120150350, 120262950, 120375600, 120488300,
120601050, 120713850, 120826700, 120939600, 121052550, 121165550, 121278600, 121391700, 121504850, 121618050, 121731300, 121844600, 121957950, 122071350, 122184800, 122298300, 122411850, 122525450, 122639100,
122752800, 122866550, 122980350, 123094200, 123208100, 123322050, 123436050, 123550100, 123664200, 123778350, 123892550, 124006800, 124121100, 124235450, 124349850, 124464300, 124578800, 124693350, 124807950,
124922600, 125037300, 125152050, 125266850, 125381700, 125496600, 125611550, 125726550, 125841600, 125956700, 126071850, 126187050, 126302300, 126417600, 126532950, 126648350, 126763800, 126879300, 126994850,
127110450, 127226100, 127341800, 127457550, 127573350, 127689200, 127805100, 127921050, 128037050, 128153100, 128269200, 128385350, 128501550, 128617800, 128734100, 128850450, 128966850, 129083300, 129199800,
129316350, 129432950, 129549600, 129666300, 129783050, 129899850, 130016700, 130133600, 130250550, 130367550, 130484600, 130601700, 130718850, 130836050, 130953300, 131070600, 131187950, 131305350, 131422800,
131540300, 131657850, 131775450, 131893100, 132010800, 132128550, 132246350, 132364200, 132482100, 132600050, 132718050, 132836100, 132954200, 133072350, 133190550, 133308800, 133427100, 133545450, 133663850,
133782300, 133900800, 134019350, 134137950, 134256600, 134375300, 134494050, 134612850, 134731700, 134850600, 134969550, 135088550, 135207600, 135326700, 135445850, 135565050, 135684300, 135803600, 135922950,
136042350, 136161800, 136281300, 136400850, 136520450, 136640100, 136759800, 136879550, 136999350, 137119200, 137239100, 137359050, 137479050, 137599100, 137719200, 137839350, 137959550, 138079800, 138200100,
138320450, 138440850, 138561300, 138681800, 138802350, 138922950, 139043600, 139164300, 139285050, 139405850, 139526700, 139647600, 139768550, 139889550, 140010600, 140131700, 140252850, 140374050, 140495300,
140616600, 140737950, 140859350, 140980800, 141102300, 141223850, 141345450, 141467100, 141588800, 141710550, 141832350, 141954200, 142076100, 142198050, 142320050, 142442100, 142564200, 142686350, 142808550,
142930800, 143053100, 143175450, 143297850, 143420300, 143542800, 143665350, 143787950, 143910600, 144033300, 144156050, 144278850, 144401700, 144524600, 144647550, 144770550, 144893600, 145016700, 145139850,
145263050, 145386300, 145509600, 145632950, 145756350, 145879800, 146003300, 146126850, 146250450, 146374100, 146497800, 146621550, 146745350, 146869200, 146993100, 147117050, 147241050, 147365100, 147489200,
147613350, 147737550, 147861800, 147986100, 148110450, 148234850, 148359300, 148483800, 148608350, 148732950, 148857600, 148982300, 149107050, 149231850, 149356700, 149481600, 149606550, 149731550, 149856600,
149981700, 150106850, 150232050, 150357300, 150482600, 150607950, 150733350, 150858800, 150984300, 151109850, 151235450, 151361100, 151486800, 151612550, 151738350, 151864200, 151990100, 152116050, 152242050,
152368100, 152494200, 152620350, 152746550, 152872800, 152999100, 153125450, 153251850, 153378300, 153504800, 153631350, 153757950, 153884600, 154011300, 154138050, 154264850, 154391700, 154518600, 154645550,
154772550, 154899600, 155026700, 155153850, 155281050, 155408300, 155535600, 155662950, 155790350, 155917800, 156045300, 156172850, 156300450, 156428100, 156555800, 156683550, 156811350, 156939200, 157067100,
157195050, 157323050, 157451100, 157579200, 157707350, 157835550, 157963800, 158092100, 158220450, 158348850, 158477300, 158605800, 158734350, 158862950, 158991600, 159120300, 159249050, 159377850, 159506700,
159635600, 159764550, 159893550, 160022600, 160151700, 160280850, 160410050, 160539300, 160668600, 160797950, 160927350, 161056800, 161186300, 161315850, 161445450, 161575100, 161704800, 161834550, 161964350,
162094200, 162224100, 162354050, 162484050, 162614100, 162744200, 162874350, 163004550, 163134800, 163265100, 163395450, 163525850, 163656300, 163786800, 163917350, 164047950, 164178600, 164309300, 164440050,
164570850, 164701700, 164832600, 164963550, 165094550, 165225600, 165356700, 165487850, 165619050, 165750300, 165881600, 166012950, 166144350, 166275800, 166407300, 166538850, 166670450, 166802100, 166933800,
167065550, 167197350, 167329200, 167461100, 167593050, 167725050, 167857100, 167989200, 168121350, 168253550, 168385800, 168518100, 168650450, 168782850, 168915300, 169047800, 169180350, 169312950, 169445600,
169578300, 169711050, 169843850, 169976700, 170109600, 170242550, 170375550, 170508600, 170641700, 170774850, 170908050, 171041300, 171174600, 171307950, 171441350, 171574800, 171708300, 171841850, 171975450,
172109100, 172242800, 172376550, 172510350, 172644200, 172778100, 172912050, 173046050, 173180100, 173314200, 173448350, 173582550, 173716800, 173851100, 173985450, 174119850, 174254300, 174388800, 174523350,
174657950, 174792600, 174927300, 175062050, 175196850, 175331700, 175466600, 175601550, 175736550, 175871600, 176006700, 176141850, 176277050, 176412300, 176547600, 176682950, 176818350, 176953800, 177089300,
177224850, 177360450, 177496100, 177631800, 177767550, 177903350, 178039200, 178175100, 178311050, 178447050, 178583100, 178719200, 178855350, 178991550, 179127800, 179264100, 179400450, 179536850, 179673300,
179809800, 179946350, 180082950, 180219600, 180356300, 180493050, 180629850, 180766700, 180903600, 181040550, 181177550, 181314600, 181451700, 181588850, 181726050, 181863300, 182000600, 182137950, 182275350,
182412800, 182550300, 182687850, 182825450, 182963100, 183100800, 183238550, 183376350, 183514200, 183652100, 183790050, 183928050, 184066100, 184204200, 184342350, 184480550, 184618800, 184757100, 184895450,
185033850, 185172300, 185310800, 185449350, 185587950, 185726600, 185865300, 186004050, 186142850, 186281700, 186420600, 186559550, 186698550, 186837600, 186976700, 187115850, 187255050, 187394300, 187533600,
187672950, 187812350, 187951800, 188091300, 188230850, 188370450, 188510100, 188649800, 188789550, 188929350, 189069200, 189209100, 189349050, 189489050, 189629100, 189769200, 189909350, 190049550, 190189800,
190330100, 190470450, 190610850, 190751300, 190891800, 191032350, 191172950, 191313600, 191454300, 191595050, 191735850, 191876700, 192017600, 192158550, 192299550, 192440600, 192581700, 192722850, 192864050,
193005300, 193146600, 193287950, 193429350, 193570800, 193712300, 193853850, 193995450, 194137100, 194278800, 194420550, 194562350, 194704200, 194846100, 194988050, 195130050, 195272100, 195414200, 195556350,
195698550, 195840800, 195983100, 196125450, 196267850, 196410300, 196552800, 196695350, 196837950, 196980600, 197123300, 197266050, 197408850, 197551700, 197694600, 197837550, 197980550, 198123600, 198266700,
198409850, 198553050, 198696300, 198839600, 198982950, 199126350, 199269800, 199413300, 199556850, 199700450, 199844100, 199987800, 200131550, 200275350, 200419200, 200563100, 200707050, 200851050, 200995100,
201139200, 201283350, 201427550, 201571800, 201716100, 201860450, 202004850, 202149300, 202293800, 202438350, 202582950, 202727600, 202872300, 203017050, 203161850, 203306700, 203451600, 203596550, 203741550,
203886600, 204031700, 204176850, 204322050, 204467300, 204612600, 204757950, 204903350, 205048800, 205194300, 205339850, 205485450, 205631100, 205776800, 205922550, 206068350, 206214200, 206360100, 206506050,
206652050, 206798100, 206944200, 207090350, 207236550, 207382800, 207529100, 207675450, 207821850, 207968300, 208114800, 208261350, 208407950, 208554600, 208701300, 208848050, 208994850, 209141700, 209288600,
209435550, 209582550, 209729600, 209876700, 210023850, 210171050, 210318300, 210465600, 210612950, 210760350, 210907800, 211055300, 211202850, 211350450, 211498100, 211645800, 211793550, 211941350, 212089200,
212237100, 212385050, 212533050, 212681100, 212829200, 212977350, 213125550, 213273800, 213422100, 213570450, 213718850, 213867300, 214015800, 214164350, 214312950, 214461600, 214610300, 214759050, 214907850,
215056700, 215205600, 215354550, 215503550, 215652600, 215801700, 215950850, 216100050, 216249300, 216398600, 216547950, 216697350, 216846800, 216996300, 217145850, 217295450, 217445100, 217594800, 217744550,
217894350, 218044200, 218194100, 218344050, 218494050, 218644100, 218794200, 218944350, 219094550, 219244800, 219395100, 219545450, 219695850, 219846300, 219996800, 220147350, 220297950, 220448600, 220599300,
220750050, 220900850, 221051700, 221202600, 221353550, 221504550, 221655600, 221806700, 221957850, 222109050, 222260300, 222411600, 222562950, 222714350, 222865800, 223017300, 223168850, 223320450, 223472100,
223623800, 223775550, 223927350, 224079200, 224231100, 224383050, 224535050, 224687100, 224839200, 224991350, 225143550, 225295800, 225448100, 225600450, 225752850, 225905300, 226057800, 226210350, 226362950,
226515600, 226668300, 226821050, 226973850, 227126700, 227279600, 227432550, 227585550, 227738600, 227891700, 228044850, 228198050, 228351300, 228504600, 228657950, 228811350, 228964800, 229118300, 229271850,
229425450, 229579100, 229732800, 229886550, 230040350, 230194200, 230348100, 230502050, 230656050, 230810100, 230964200, 231118350, 231272550, 231426800, 231581100, 231735450, 231889850, 232044300, 232198800,
232353350, 232507950, 232662600, 232817300, 232972050, 233126850, 233281700, 233436600, 233591550, 233746550, 233901600, 234056700, 234211850, 234367050, 234522300, 234677600, 234832950, 234988350, 235143800,
235299300, 235454850, 235610450, 235766100, 235921800, 236077550, 236233350, 236389200, 236545100, 236701050, 236857050, 237013100, 237169200, 237325350, 237481550, 237637800, 237794100, 237950450, 238106850,
238263300, 238419800, 238576350, 238732950, 238889600, 239046300, 239203050, 239359850, 239516700, 239673600, 239830550, 239987550, 240144600, 240301700, 240458850, 240616050, 240773300, 240930600, 241087950,
241245350, 241402800, 241560300, 241717850, 241875450, 242033100, 242190800, 242348550, 242506350, 242664200, 242822100, 242980050, 243138050, 243296100, 243454200, 243612350, 243770550, 243928800, 244087100,
244245450, 244403850, 244562300, 244720800, 244879350, 245037950, 245196600, 245355300, 245514050, 245672850, 245831700, 245990600, 246149550, 246308550, 246467600, 246626700, 246785850, 246945050, 247104300,
247263600, 247422950, 247582350, 247741800, 247901300, 248060850, 248220450, 248380100, 248539800, 248699550, 248859350, 249019200, 249179100, 249339050, 249499050, 249659100, 249819200, 249979350, 250139550,
250299800, 250460100, 250620450, 250780850, 250941300, 251101800, 251262350, 251422950, 251583600, 251744300, 251905050, 252065850, 252226700, 252387600, 252548550, 252709550, 252870600, 253031700, 253192850,
253354050, 253515300, 253676600, 253837950, 253999350, 254160800, 254322300, 254483850, 254645450, 254807100, 254968800, 255130550, 255292350, 255454200, 255616100, 255778050, 255940050, 256102100, 256264200,
256426350, 256588550, 256750800, 256913100, 257075450, 257237850, 257400300, 257562800, 257725350, 257887950, 258050600, 258213300, 258376050, 258538850, 258701700, 258864600, 259027550, 259190550, 259353600,
259516700, 259679850, 259843050, 260006300, 260169600, 260332950, 260496350, 260659800, 260823300, 260986850, 261150450, 261314100, 261477800, 261641550, 261805350, 261969200, 262133100, 262297050, 262461050,
262625100, 262789200, 262953350, 263117550, 263281800, 263446100, 263610450, 263774850, 263939300, 264103800, 264268350, 264432950, 264597600, 264762300, 264927050, 265091850, 265256700, 265421600, 265586550,
265751550, 265916600, 266081700, 266246850, 266412050, 266577300, 266742600, 266907950, 267073350, 267238800, 267404300, 267569850, 267735450, 267901100, 268066800, 268232550, 268398350, 268564200, 268730100,
268896050, 269062050, 269228100, 269394200, 269560350, 269726550, 269892800, 270059100, 270225450, 270391850, 270558300, 270724800, 270891350, 271057950, 271224600, 271391300, 271558050, 271724850, 271891700,
272058600, 272225550, 272392550, 272559600, 272726700, 272893850, 273061050, 273228300, 273395600, 273562950, 273730350, 273897800, 274065300, 274232850, 274400450, 274568100, 274735800, 274903550, 275071350,
275239200, 275407100, 275575050, 275743050, 275911100, 276079200, 276247350, 276415550, 276583800, 276752100, 276920450, 277088850, 277257300, 277425800, 277594350, 277762950, 277931600, 278100300, 278269050,
278437850, 278606700, 278775600, 278944550, 279113550, 279282600, 279451700, 279620850, 279790050, 279959300, 280128600, 280297950, 280467350, 280636800, 280806300, 280975850, 281145450, 281315100, 281484800,
281654550, 281824350, 281994200, 282164100, 282334050, 282504050, 282674100, 282844200, 283014350, 283184550, 283354800, 283525100, 283695450, 283865850, 284036300, 284206800, 284377350, 284547950, 284718600,
284889300, 285060050, 285230850, 285401700, 285572600, 285743550, 285914550, 286085600, 286256700, 286427850, 286599050, 286770300, 286941600, 287112950, 287284350, 287455800, 287627300, 287798850, 287970450,
288142100, 288313800, 288485550, 288657350, 288829200, 289001100, 289173050, 289345050, 289517100, 289689200, 289861350, 290033550, 290205800, 290378100, 290550450, 290722850, 290895300, 291067800, 291240350,
291412950, 291585600, 291758300, 291931050, 292103850, 292276700, 292449600, 292622550, 292795550, 292968600, 293141700, 293314850, 293488050, 293661300, 293834600, 294007950, 294181350, 294354800, 294528300,
294701850, 294875450, 295049100, 295222800, 295396550, 295570350, 295744200, 295918100, 296092050, 296266050, 296440100, 296614200, 296788350, 296962550, 297136800, 297311100, 297485450, 297659850, 297834300,
298008800, 298183350, 298357950, 298532600, 298707300, 298882050, 299056850, 299231700, 299406600, 299581550, 299756550, 299931600, 300106700, 300281850, 300457050, 300632300, 300807600, 300982950, 301158350,
301333800, 301509300, 301684850, 301860450, 302036100, 302211800, 302387550, 302563350, 302739200, 302915100, 303091050, 303267050, 303443100, 303619200, 303795350, 303971550, 304147800, 304324100, 304500450,
304676850, 304853300, 305029800, 305206350, 305382950, 305559600, 305736300, 305913050, 306089850, 306266700, 306443600, 306620550, 306797550, 306974600, 307151700, 307328850, 307506050, 307683300, 307860600,
308037950, 308215350, 308392800, 308570300, 308747850, 308925450, 309103100, 309280800, 309458550, 309636350, 309814200, 309992100, 310170050, 310348050, 310526100, 310704200, 310882350, 311060550, 311238800,
311417100, 311595450, 311773850, 311952300, 312130800, 312309350, 312487950, 312666600, 312845300, 313024050, 313202850, 313381700, 313560600, 313739550, 313918550, 314097600, 314276700, 314455850, 314635050,
314814300, 314993600, 315172950, 315352350, 315531800, 315711300, 315890850, 316070450, 316250100, 316429800, 316609550, 316789350, 316969200, 317149100, 317329050, 317509050, 317689100, 317869200, 318049350,
318229550, 318409800, 318590100, 318770450, 318950850, 319131300, 319311800, 319492350, 319672950, 319853600, 320034300, 320215050, 320395850, 320576700, 320757600, 320938550, 321119550, 321300600, 321481700,
321662850, 321844050, 322025300, 322206600, 322387950, 322569350, 322750800, 322932300, 323113850, 323295450, 323477100, 323658800, 323840550, 324022350, 324204200, 324386100, 324568050, 324750050, 324932100,
325114200, 325296350, 325478550, 325660800, 325843100, 326025450, 326207850, 326390300, 326572800, 326755350, 326937950, 327120600, 327303300, 327486050, 327668850, 327851700, 328034600, 328217550, 328400550,
328583600, 328766700, 328949850, 329133050, 329316300, 329499600, 329682950, 329866350, 330049800, 330233300, 330416850, 330600450, 330784100, 330967800, 331151550, 331335350, 331519200, 331703100, 331887050,
332071050, 332255100, 332439200, 332623350, 332807550, 332991800, 333176100, 333360450, 333544850, 333729300, 333913800, 334098350, 334282950, 334467600, 334652300, 334837050, 335021850, 335206700, 335391600,
335576550, 335761550, 335946600, 336131700, 336316850, 336502050, 336687300, 336872600, 337057950, 337243350, 337428800, 337614300, 337799850, 337985450, 338171100, 338356800, 338542550, 338728350, 338914200,
339100100, 339286050, 339472050, 339658100, 339844200, 340030350, 340216550, 340402800, 340589100, 340775450, 340961850, 341148300, 341334800, 341521350, 341707950, 341894600, 342081300, 342268050, 342454850,
342641700, 342828600, 343015550, 343202550, 343389600, 343576700, 343763850, 343951050, 344138300, 344325600, 344512950, 344700350, 344887800, 345075300, 345262850, 345450450, 345638100, 345825800, 346013550,
346201350, 346389200, 346577100, 346765050, 346953050, 347141100, 347329200, 347517350, 347705550, 347893800, 348082100, 348270450, 348458850, 348647300, 348835800, 349024350, 349212950, 349401600, 349590300,
349779050, 349967850, 350156700, 350345600, 350534550, 350723550, 350912600, 351101700, 351290850, 351480050, 351669300, 351858600, 352047950, 352237350, 352426800, 352616300, 352805850, 352995450, 353185100,
353374800, 353564550, 353754350, 353944200, 354134100, 354324050, 354514050, 354704100, 354894200, 355084350, 355274550, 355464800, 355655100, 355845450, 356035850, 356226300, 356416800, 356607350, 356797950,
356988600, 357179300, 357370050, 357560850, 357751700, 357942600, 358133550, 358324550, 358515600, 358706700, 358897850, 359089050, 359280300, 359471600, 359662950, 359854350, 360045800, 360237300, 360428850,
360620450, 360812100, 361003800, 361195550, 361387350, 361579200, 361771100, 361963050, 362155050, 362347100, 362539200, 362731350, 362923550, 363115800, 363308100, 363500450, 363692850, 363885300, 364077800,
364270350, 364462950, 364655600, 364848300, 365041050, 365233850, 365426700, 365619600, 365812550, 366005550, 366198600, 366391700, 366584850, 366778050, 366971300, 367164600, 367357950, 367551350, 367744800,
367938300, 368131850, 368325450, 368519100, 368712800, 368906550, 369100350, 369294200, 369488100, 369682050, 369876050, 370070100, 370264200, 370458350, 370652550, 370846800, 371041100, 371235450, 371429850,
371624300, 371818800, 372013350, 372207950, 372402600, 372597300, 372792050, 372986850, 373181700, 373376600, 373571550, 373766550, 373961600, 374156700, 374351850, 374547050, 374742300, 374937600, 375132950,
375328350, 375523800, 375719300, 375914850, 376110450, 376306100, 376501800, 376697550, 376893350, 377089200, 377285100, 377481050, 377677050, 377873100, 378069200, 378265350, 378461550, 378657800, 378854100,
379050450, 379246850, 379443300, 379639800, 379836350, 380032950, 380229600, 380426300, 380623050, 380819850, 381016700, 381213600, 381410550, 381607550, 381804600, 382001700, 382198850, 382396050, 382593300,
382790600, 382987950, 383185350, 383382800, 383580300, 383777850, 383975450, 384173100, 384370800, 384568550, 384766350, 384964200, 385162100, 385360050, 385558050, 385756100, 385954200, 386152350, 386350550,
386548800, 386747100, 386945450, 387143850, 387342300, 387540800, 387739350, 387937950, 388136600, 388335300, 388534050, 388732850, 388931700, 389130600, 389329550, 389528550, 389727600, 389926700, 390125850,
390325050, 390524300, 390723600, 390922950, 391122350, 391321800, 391521300, 391720850, 391920450, 392120100, 392319800, 392519550, 392719350, 392919200, 393119100, 393319050, 393519050, 393719100, 393919200,
394119350, 394319550, 394519800, 394720100, 394920450, 395120850, 395321300, 395521800, 395722350, 395922950, 396123600, 396324300, 396525050, 396725850, 396926700, 397127600, 397328550, 397529550, 397730600,
397931700, 398132850, 398334050, 398535300, 398736600, 398937950, 399139350, 399340800, 399542300, 399743850, 399945450, 400147100, 400348800, 400550550, 400752350, 400954200, 401156100, 401358050, 401560050,
401762100, 401964200, 402166350, 402368550, 402570800, 402773100, 402975450, 403177850, 403380300, 403582800, 403785350, 403987950, 404190600, 404393300, 404596050, 404798850, 405001700, 405204600, 405407550,
405610550, 405813600, 406016700, 406219850, 406423050, 406626300, 406829600, 407032950, 407236350, 407439800, 407643300, 407846850, 408050450, 408254100, 408457800, 408661550, 408865350, 409069200, 409273100,
409477050, 409681050, 409885100, 410089200, 410293350, 410497550, 410701800, 410906100, 411110450, 411314850, 411519300, 411723800, 411928350, 412132950, 412337600, 412542300, 412747050, 412951850, 413156700,
413361600, 413566550, 413771550, 413976600, 414181700, 414386850, 414592050, 414797300, 415002600, 415207950, 415413350, 415618800, 415824300, 416029850, 416235450, 416441100, 416646800, 416852550, 417058350,
417264200, 417470100, 417676050, 417882050, 418088100, 418294200, 418500350, 418706550, 418912800, 419119100, 419325450, 419531850, 419738300, 419944800, 420151350, 420357950, 420564600, 420771300, 420978050,
421184850, 421391700, 421598600, 421805550, 422012550, 422219600, 422426700, 422633850, 422841050, 423048300, 423255600, 423462950, 423670350, 423877800, 424085300, 424292850, 424500450, 424708100, 424915800,
425123550, 425331350, 425539200, 425747100, 425955050, 426163050, 426371100, 426579200, 426787350, 426995550, 427203800, 427412100, 427620450, 427828850, 428037300, 428245800, 428454350, 428662950, 428871600,
429080300, 429289050, 429497850, 429706700, 429915600, 430124550, 430333550, 430542600, 430751700, 430960850, 431170050, 431379300, 431588600, 431797950, 432007350, 432216800, 432426300, 432635850, 432845450,
433055100, 433264800, 433474550, 433684350, 433894200, 434104100, 434314050, 434524050, 434734100, 434944200, 435154350, 435364550, 435574800, 435785100, 435995450, 436205850, 436416300, 436626800, 436837350,
437047950, 437258600, 437469300, 437680050, 437890850, 438101700, 438312600, 438523550, 438734550, 438945600, 439156700, 439367850, 439579050, 439790300, 440001600, 440212950, 440424350, 440635800, 440847300,
441058850, 441270450, 441482100, 441693800, 441905550, 442117350, 442329200, 442541100, 442753050, 442965050, 443177100, 443389200, 443601350, 443813550, 444025800, 444238100, 444450450, 444662850, 444875300,
445087800, 445300350, 445512950, 445725600, 445938300, 446151050, 446363850, 446576700, 446789600, 447002550, 447215550, 447428600, 447641700, 447854850, 448068050, 448281300, 448494600, 448707950, 448921350,
449134800, 449348300, 449561850, 449775450, 449989100, 450202800, 450416550, 450630350, 450844200, 451058100, 451272050, 451486050, 451700100, 451914200, 452128350, 452342550, 452556800, 452771100, 452985450,
453199850, 453414300, 453628800, 453843350, 454057950, 454272600, 454487300, 454702050, 454916850, 455131700, 455346600, 455561550, 455776550, 455991600, 456206700, 456421850, 456637050, 456852300, 457067600,
457282950, 457498350, 457713800, 457929300, 458144850, 458360450, 458576100, 458791800, 459007550, 459223350, 459439200, 459655100, 459871050, 460087050, 460303100, 460519200, 460735350, 460951550, 461167800,
461384100, 461600450, 461816850, 462033300, 462249800, 462466350, 462682950, 462899600, 463116300, 463333050, 463549850, 463766700, 463983600, 464200550, 464417550, 464634600, 464851700, 465068850, 465286050,
465503300, 465720600, 465937950, 466155350, 466372800, 466590300, 466807850, 467025450, 467243100, 467460800, 467678550, 467896350, 468114200, 468332100, 468550050, 468768050, 468986100, 469204200, 469422350,
469640550, 469858800, 470077100, 470295450, 470513850, 470732300, 470950800, 471169350, 471387950, 471606600, 471825300, 472044050, 472262850, 472481700, 472700600, 472919550, 473138550, 473357600, 473576700,
473795850, 474015050, 474234300, 474453600, 474672950, 474892350, 475111800, 475331300, 475550850, 475770450, 475990100, 476209800, 476429550, 476649350, 476869200, 477089100, 477309050, 477529050, 477749100,
477969200, 478189350, 478409550, 478629800, 478850100, 479070450, 479290850, 479511300, 479731800, 479952350, 480172950, 480393600, 480614300, 480835050, 481055850, 481276700, 481497600, 481718550, 481939550, 482160600, 482381700, 482602850, 482824050, 483045300, 483266600, 483487950, 483709350, 483930800, 484152300, 484373850, 484595450, 484817100, 485038800, 485260550, 485482350, 485704200, 485926100, 486148050, 486370050, 486592100, 486814200, 487036350, 487258550, 487480800, 487703100, 487925450, 488147850, 488370300, 488592800, 488815350, 489037950, 489260600, 489483300, 489706050, 489928850, 490151700, 490374600, 490597550, 490820550, 491043600, 491266700, 491489850, 491713050, 491936300, 492159600, 492382950, 492606350, 492829800, 493053300, 493276850, 493500450, 493724100, 493947800, 494171550, 494395350, 494619200, 494843100, 495067050, 495291050, 495515100, 495739200, 495963350, 496187550, 496411800, 496636100, 496860450, 497084850, 497309300, 497533800, 497758350, 497982950, 498207600, 498432300, 498657050, 498881850, 499106700, 499331600, 499556550, 499781550, 500006600, 500231700, 500456850, 500682050, 500907300, 501132600, 501357950, 501583350, 501808800, 502034300, 502259850, 502485450, 502711100, 502936800, 503162550, 503388350, 503614200, 503840100, 504066050, 504292050, 504518100, 504744200, 504970350, 505196550, 505422800, 505649100, 505875450, 506101850, 506328300, 506554800, 506781350, 507007950, 507234600, 507461300, 507688050, 507914850, 508141700, 508368600, 508595550, 508822550, 509049600, 509276700, 509503850, 509731050, 509958300, 510185600, 510412950, 510640350, 510867800, 511095300, 511322850, 511550450, 511778100, 512005800, 512233550, 512461350, 512689200, 512917100, 513145050, 513373050, 513601100, 513829200, 514057350, 514285550, 514513800, 514742100, 514970450, 515198850, 515427300, 515655800, 515884350, 516112950, 516341600, 516570300, 516799050, 517027850, 517256700, 517485600, 517714550, 517943550, 518172600, 518401700, 518630850, 518860050, 519089300, 519318600, 519547950, 519777350, 520006800, 520236300, 520465850, 520695450, 520925100, 521154800, 521384550, 521614350, 521844200, 522074100, 522304050, 522534050, 522764100, 522994200, 523224350, 523454550, 523684800, 523915100, 524145450, 524375850, 524606300, 524836800, 525067350, 525297950, 525528600, 525759300, 525990050, 526220850, 526451700, 526682600, 526913550, 527144550, 527375600, 527606700, 527837850, 528069050, 528300300, 528531600, 528762950, 528994350, 529225800, 529457300, 529688850, 529920450, 530152100, 530383800, 530615550, 530847350, 531079200, 531311100, 531543050, 531775050, 532007100, 532239200, 532471350, 532703550, 532935800, 533168100, 533400450, 533632850, 533865300, 534097800, 534330350, 534562950, 534795600, 535028300, 535261050, 535493850, 535726700, 535959600, 536192550, 536425550, 536658600, 536891700, 537124850, 537358050, 537591300, 537824600, 538057950, 538291350, 538524800, 538758300, 538991850, 539225450, 539459100, 539692800, 539926550, 540160350, 540394200, 540628100, 540862050, 541096050, 541330100, 541564200, 541798350, 542032550, 542266800, 542501100, 542735450, 542969850, 543204300, 543438800, 543673350, 543907950, 544142600, 544377300, 544612050, 544846850, 545081700, 545316600, 545551550, 545786550, 546021600, 546256700, 546491850, 546727050, 546962300, 547197600, 547432950, 547668350, 547903800, 548139300, 548374850, 548610450, 548846100, 549081800, 549317550, 549553350, 549789200, 550025100, 550261050, 550497050, 550733100, 550969200, 551205350, 551441550, 551677800, 551914100, 552150450, 552386850, 552623300, 552859800, 553096350, 553332950, 553569600, 553806300, 554043050, 554279850, 554516700, 554753600, 554990550, 555227550, 555464600, 555701700, 555938850, 556176050, 556413300, 556650600, 556887950, 557125350, 557362800, 557600300, 557837850, 558075450, 558313100, 558550800, 558788550, 559026350, 559264200, 559502100, 559740050, 559978050, 560216100, 560454200, 560692350, 560930550, 561168800, 561407100, 561645450, 561883850, 562122300, 562360800, 562599350, 562837950, 563076600, 563315300, 563554050, 563792850, 564031700, 564270600, 564509550, 564748550, 564987600, 565226700, 565465850, 565705050, 565944300, 566183600, 566422950, 566662350, 566901800, 567141300, 567380850, 567620450, 567860100, 568099800, 568339550, 568579350, 568819200, 569059100, 569299050, 569539050, 569779100, 570019200, 570259350, 570499550, 570739800, 570980100, 571220450, 571460850, 571701300, 571941800, 572182350, 572422950, 572663600, 572904300, 573145050, 573385850, 573626700, 573867600, 574108550, 574349550, 574590600, 574831700, 575072850, 575314050, 575555300, 575796600, 576037950, 576279350, 576520800, 576762300, 577003850, 577245450, 577487100, 577728800, 577970550, 578212350, 578454200, 578696100, 578938050, 579180050, 579422100, 579664200, 579906350, 580148550, 580390800, 580633100, 580875450, 581117850, 581360300, 581602800, 581845350, 582087950, 582330600, 582573300, 582816050, 583058850, 583301700, 583544600, 583787550, 584030550, 584273600, 584516700, 584759850, 585003050, 585246300, 585489600, 585732950, 585976350, 586219800, 586463300, 586706850, 586950450, 587194100, 587437800, 587681550, 587925350, 588169200, 588413100, 588657050, 588901050, 589145100, 589389200, 589633350, 589877550, 590121800, 590366100, 590610450, 590854850, 591099300, 591343800, 591588350, 591832950, 592077600, 592322300, 592567050, 592811850, 593056700, 593301600, 593546550, 593791550, 594036600, 594281700, 594526850, 594772050, 595017300, 595262600, 595507950, 595753350, 595998800, 596244300, 596489850, 596735450, 596981100, 597226800, 597472550, 597718350, 597964200, 598210100, 598456050, 598702050, 598948100, 599194200, 599440350, 599686550, 599932800, 600179100, 600425450, 600671850, 600918300, 601164800, 601411350, 601657950, 601904600, 602151300, 602398050, 602644850, 602891700, 603138600, 603385550, 603632550, 603879600, 604126700, 604373850, 604621050, 604868300, 605115600, 605362950, 605610350, 605857800, 606105300, 606352850, 606600450, 606848100, 607095800, 607343550, 607591350, 607839200, 608087100, 608335050, 608583050, 608831100, 609079200, 609327350, 609575550, 609823800, 610072100, 610320450, 610568850, 610817300, 611065800, 611314350, 611562950, 611811600, 612060300, 612309050, 612557850, 612806700, 613055600, 613304550, 613553550, 613802600, 614051700, 614300850, 614550050, 614799300, 615048600, 615297950, 615547350, 615796800, 616046300, 616295850, 616545450, 616795100, 617044800, 617294550, 617544350, 617794200, 618044100, 618294050, 618544050, 618794100, 619044200, 619294350, 619544550, 619794800, 620045100, 620295450, 620545850, 620796300, 621046800, 621297350, 621547950, 621798600, 622049300, 622300050, 622550850, 622801700, 623052600, 623303550, 623554550, 623805600, 624056700, 624307850, 624559050, 624810300, 625061600, 625312950, 625564350, 625815800, 626067300, 626318850, 626570450, 626822100, 627073800, 627325550, 627577350, 627829200, 628081100, 628333050, 628585050, 628837100, 629089200, 629341350, 629593550, 629845800, 630098100, 630350450, 630602850, 630855300, 631107800, 631360350, 631612950, 631865600, 632118300, 632371050, 632623850, 632876700, 633129600, 633382550, 633635550, 633888600, 634141700, 634394850, 634648050, 634901300, 635154600, 635407950, 635661350, 635914800, 636168300, 636421850, 636675450, 636929100, 637182800, 637436550, 637690350, 637944200, 638198100, 638452050, 638706050, 638960100, 639214200, 639468350, 639722550, 639976800, 640231100, 640485450, 640739850, 640994300, 641248800, 641503350, 641757950, 642012600, 642267300, 642522050, 642776850, 643031700, 643286600, 643541550, 643796550, 644051600, 644306700, 644561850, 644817050, 645072300, 645327600, 645582950, 645838350, 646093800, 646349300, 646604850, 646860450, 647116100, 647371800, 647627550, 647883350, 648139200, 648395100, 648651050, 648907050, 649163100, 649419200, 649675350, 649931550, 650187800, 650444100, 650700450, 650956850, 651213300, 651469800, 651726350, 651982950, 652239600, 652496300, 652753050, 653009850, 653266700, 653523600, 653780550, 654037550, 654294600, 654551700, 654808850, 655066050, 655323300, 655580600, 655837950, 656095350, 656352800, 656610300, 656867850, 657125450, 657383100, 657640800, 657898550, 658156350, 658414200, 658672100, 658930050, 659188050, 659446100, 659704200, 659962350, 660220550, 660478800, 660737100, 660995450, 661253850, 661512300, 661770800, 662029350, 662287950, 662546600, 662805300, 663064050, 663322850, 663581700, 663840600, 664099550, 664358550, 664617600, 664876700, 665135850, 665395050, 665654300, 665913600, 666172950, 666432350, 666691800, 666951300, 667210850, 667470450, 667730100, 667989800, 668249550, 668509350, 668769200, 669029100, 669289050, 669549050, 669809100, 670069200, 670329350, 670589550, 670849800, 671110100, 671370450, 671630850, 671891300, 672151800, 672412350, 672672950, 672933600, 673194300, 673455050, 673715850, 673976700, 674237600, 674498550, 674759550, 675020600, 675281700, 675542850, 675804050, 676065300, 676326600, 676587950, 676849350, 677110800, 677372300, 677633850, 677895450, 678157100, 678418800, 678680550, 678942350, 679204200, 679466100, 679728050, 679990050, 680252100, 680514200, 680776350, 681038550, 681300800, 681563100, 681825450, 682087850, 682350300, 682612800, 682875350, 683137950, 683400600, 683663300, 683926050, 684188850, 684451700, 684714600, 684977550, 685240550, 685503600, 685766700, 686029850, 686293050, 686556300, 686819600, 687082950, 687346350, 687609800, 687873300, 688136850, 688400450, 688664100, 688927800, 689191550, 689455350, 689719200, 689983100, 690247050, 690511050, 690775100, 691039200, 691303350, 691567550, 691831800, 692096100, 692360450, 692624850, 692889300, 693153800, 693418350, 693682950, 693947600, 694212300, 694477050, 694741850, 695006700, 695271600, 695536550, 695801550, 696066600, 696331700, 696596850, 696862050, 697127300, 697392600, 697657950, 697923350, 698188800, 698454300, 698719850, 698985450, 699251100, 699516800, 699782550, 700048350, 700314200, 700580100, 700846050, 701112050, 701378100, 701644200, 701910350, 702176550, 702442800, 702709100, 702975450, 703241850, 703508300, 703774800, 704041350, 704307950, 704574600, 704841300, 705108050, 705374850, 705641700, 705908600, 706175550, 706442550, 706709600, 706976700, 707243850, 707511050, 707778300, 708045600, 708312950, 708580350, 708847800, 709115300, 709382850, 709650450, 709918100, 710185800, 710453550, 710721350, 710989200, 711257100, 711525050, 711793050, 712061100, 712329200, 712597350, 712865550, 713133800, 713402100, 713670450, 713938850, 714207300, 714475800, 714744350, 715012950, 715281600, 715550300, 715819050, 716087850, 716356700, 716625600, 716894550, 717163550, 717432600, 717701700, 717970850, 718240050, 718509300, 718778600, 719047950, 719317350, 719586800, 719856300, 720125850, 720395450, 720665100, 720934800, 721204550, 721474350, 721744200, 722014100, 722284050, 722554050, 722824100, 723094200, 723364350, 723634550, 723904800, 724175100, 724445450, 724715850, 724986300, 725256800, 725527350, 725797950, 726068600, 726339300, 726610050, 726880850, 727151700, 727422600, 727693550, 727964550, 728235600, 728506700, 728777850, 729049050, 729320300, 729591600, 729862950, 730134350, 730405800, 730677300, 730948850, 731220450, 731492100, 731763800, 732035550, 732307350, 732579200, 732851100, 733123050, 733395050, 733667100, 733939200, 734211350, 734483550, 734755800, 735028100, 735300450, 735572850, 735845300, 736117800, 736390350, 736662950, 736935600, 737208300, 737481050, 737753850, 738026700, 738299600, 738572550, 738845550, 739118600, 739391700, 739664850, 739938050, 740211300, 740484600, 740757950, 741031350, 741304800, 741578300, 741851850, 742125450, 742399100, 742672800, 742946550, 743220350, 743494200, 743768100, 744042050, 744316050, 744590100, 744864200, 745138350, 745412550, 745686800, 745961100, 746235450, 746509850, 746784300, 747058800, 747333350, 747607950, 747882600, 748157300, 748432050, 748706850, 748981700, 749256600, 749531550, 749806550, 750081600, 750356700, 750631850, 750907050, 751182300, 751457600, 751732950, 752008350, 752283800, 752559300, 752834850, 753110450, 753386100, 753661800, 753937550, 754213350, 754489200, 754765100, 755041050, 755317050, 755593100, 755869200, 756145350, 756421550, 756697800, 756974100, 757250450, 757526850, 757803300, 758079800, 758356350, 758632950, 758909600, 759186300, 759463050, 759739850, 760016700, 760293600, 760570550, 760847550, 761124600, 761401700, 761678850, 761956050, 762233300, 762510600, 762787950, 763065350, 763342800, 763620300, 763897850, 764175450, 764453100, 764730800, 765008550, 765286350, 765564200, 765842100, 766120050, 766398050, 766676100, 766954200, 767232350, 767510550, 767788800, 768067100, 768345450, 768623850, 768902300, 769180800, 769459350, 769737950, 770016600, 770295300, 770574050, 770852850, 771131700, 771410600, 771689550, 771968550, 772247600, 772526700, 772805850, 773085050, 773364300, 773643600, 773922950, 774202350, 774481800, 774761300, 775040850, 775320450, 775600100, 775879800, 776159550, 776439350, 776719200, 776999100, 777279050, 777559050, 777839100, 778119200, 778399350, 778679550, 778959800, 779240100, 779520450, 779800850, 780081300, 780361800, 780642350, 780922950, 781203600, 781484300, 781765050, 782045850, 782326700, 782607600, 782888550, 783169550, 783450600, 783731700, 784012850, 784294050, 784575300, 784856600, 785137950, 785419350, 785700800, 785982300, 786263850, 786545450, 786827100, 787108800, 787390550, 787672350, 787954200, 788236100, 788518050, 788800050, 789082100, 789364200, 789646350, 789928550, 790210800, 790493100, 790775450, 791057850, 791340300, 791622800, 791905350, 792187950, 792470600, 792753300, 793036050, 793318850, 793601700, 793884600, 794167550, 794450550, 794733600, 795016700, 795299850, 795583050, 795866300, 796149600, 796432950, 796716350, 796999800, 797283300, 797566850, 797850450, 798134100, 798417800, 798701550, 798985350, 799269200, 799553100, 799837050, 800121050, 800405100, 800689200, 800973350, 801257550, 801541800, 801826100, 802110450, 802394850, 802679300, 802963800, 803248350, 803532950, 803817600, 804102300, 804387050, 804671850, 804956700, 805241600, 805526550, 805811550, 806096600, 806381700, 806666850, 806952050, 807237300, 807522600, 807807950, 808093350, 808378800, 808664300, 808949850, 809235450, 809521100, 809806800, 810092550, 810378350, 810664200, 810950100, 811236050, 811522050, 811808100, 812094200, 812380350, 812666550, 812952800, 813239100, 813525450, 813811850, 814098300, 814384800, 814671350, 814957950, 815244600, 815531300, 815818050, 816104850, 816391700, 816678600, 816965550, 817252550, 817539600, 817826700, 818113850, 818401050, 818688300, 818975600, 819262950, 819550350, 819837800, 820125300, 820412850, 820700450, 820988100, 821275800, 821563550, 821851350, 822139200, 822427100, 822715050, 823003050, 823291100, 823579200, 823867350, 824155550, 824443800, 824732100, 825020450, 825308850, 825597300, 825885800, 826174350, 826462950, 826751600, 827040300, 827329050, 827617850, 827906700, 828195600, 828484550, 828773550, 829062600, 829351700, 829640850, 829930050, 830219300, 830508600, 830797950, 831087350, 831376800, 831666300, 831955850, 832245450, 832535100, 832824800, 833114550, 833404350, 833694200, 833984100, 834274050, 834564050, 834854100, 835144200, 835434350, 835724550, 836014800, 836305100, 836595450, 836885850, 837176300, 837466800, 837757350, 838047950, 838338600, 838629300, 838920050, 839210850, 839501700, 839792600, 840083550, 840374550, 840665600, 840956700, 841247850, 841539050, 841830300, 842121600, 842412950, 842704350, 842995800, 843287300, 843578850, 843870450, 844162100, 844453800, 844745550, 845037350, 845329200, 845621100, 845913050, 846205050, 846497100, 846789200, 847081350, 847373550, 847665800, 847958100, 848250450, 848542850, 848835300, 849127800, 849420350, 849712950, 850005600, 850298300, 850591050, 850883850, 851176700, 851469600, 851762550, 852055550, 852348600, 852641700, 852934850, 853228050, 853521300, 853814600, 854107950, 854401350, 854694800, 854988300, 855281850, 855575450, 855869100, 856162800, 856456550, 856750350, 857044200, 857338100, 857632050, 857926050, 858220100, 858514200, 858808350, 859102550, 859396800, 859691100, 859985450, 860279850, 860574300, 860868800, 861163350, 861457950, 861752600, 862047300, 862342050, 862636850, 862931700, 863226600, 863521550, 863816550, 864111600, 864406700, 864701850, 864997050, 865292300, 865587600, 865882950, 866178350, 866473800, 866769300, 867064850, 867360450, 867656100, 867951800, 868247550, 868543350, 868839200, 869135100, 869431050, 869727050, 870023100, 870319200, 870615350, 870911550, 871207800, 871504100, 871800450, 872096850, 872393300, 872689800, 872986350, 873282950, 873579600, 873876300, 874173050, 874469850, 874766700, 875063600, 875360550, 875657550, 875954600, 876251700, 876548850, 876846050, 877143300, 877440600, 877737950, 878035350, 878332800, 878630300, 878927850, 879225450, 879523100, 879820800, 880118550, 880416350, 880714200, 881012100, 881310050, 881608050, 881906100, 882204200, 882502350, 882800550, 883098800, 883397100, 883695450, 883993850, 884292300, 884590800, 884889350, 885187950, 885486600, 885785300, 886084050, 886382850, 886681700, 886980600, 887279550, 887578550, 887877600, 888176700, 888475850, 888775050, 889074300, 889373600, 889672950, 889972350, 890271800, 890571300, 890870850, 891170450, 891470100, 891769800, 892069550, 892369350, 892669200, 892969100, 893269050, 893569050, 893869100, 894169200, 894469350, 894769550, 895069800, 895370100, 895670450, 895970850, 896271300, 896571800, 896872350, 897172950, 897473600, 897774300, 898075050, 898375850, 898676700, 898977600, 899278550, 899579550, 899880600, 900181700, 900482850, 900784050, 901085300, 901386600, 901687950, 901989350, 902290800, 902592300, 902893850, 903195450, 903497100, 903798800, 904100550, 904402350, 904704200, 905006100, 905308050, 905610050, 905912100, 906214200, 906516350, 906818550, 907120800, 907423100, 907725450, 908027850, 908330300, 908632800, 908935350, 909237950, 909540600, 909843300, 910146050, 910448850, 910751700, 911054600, 911357550, 911660550, 911963600, 912266700, 912569850, 912873050, 913176300, 913479600, 913782950, 914086350, 914389800, 914693300, 914996850, 915300450, 915604100, 915907800, 916211550, 916515350, 916819200, 917123100, 917427050, 917731050, 918035100, 918339200, 918643350, 918947550, 919251800, 919556100, 919860450, 920164850, 920469300, 920773800, 921078350, 921382950, 921687600, 921992300, 922297050, 922601850, 922906700, 923211600, 923516550, 923821550, 924126600, 924431700, 924736850, 925042050, 925347300, 925652600, 925957950, 926263350, 926568800, 926874300, 927179850, 927485450, 927791100, 928096800, 928402550, 928708350, 929014200, 929320100, 929626050, 929932050, 930238100, 930544200, 930850350, 931156550, 931462800, 931769100, 932075450, 932381850, 932688300, 932994800, 933301350, 933607950, 933914600, 934221300, 934528050, 934834850, 935141700, 935448600, 935755550, 936062550, 936369600, 936676700, 936983850, 937291050, 937598300, 937905600, 938212950, 938520350, 938827800, 939135300, 939442850, 939750450, 940058100, 940365800, 940673550, 940981350, 941289200, 941597100, 941905050, 942213050, 942521100, 942829200, 943137350, 943445550, 943753800, 944062100, 944370450, 944678850, 944987300, 945295800, 945604350, 945912950, 946221600, 946530300, 946839050, 947147850, 947456700, 947765600, 948074550, 948383550, 948692600, 949001700, 949310850, 949620050, 949929300, 950238600, 950547950, 950857350, 951166800, 951476300, 951785850, 952095450, 952405100, 952714800, 953024550, 953334350, 953644200, 953954100, 954264050, 954574050, 954884100, 955194200, 955504350, 955814550, 956124800, 956435100, 956745450, 957055850, 957366300, 957676800, 957987350, 958297950, 958608600, 958919300, 959230050, 959540850, 959851700, 960162600, 960473550, 960784550, 961095600, 961406700, 961717850, 962029050, 962340300, 962651600, 962962950, 963274350, 963585800, 963897300, 964208850, 964520450, 964832100, 965143800, 965455550, 965767350, 966079200, 966391100, 966703050, 967015050, 967327100, 967639200, 967951350, 968263550, 968575800, 968888100, 969200450, 969512850, 969825300, 970137800, 970450350, 970762950, 971075600, 971388300, 971701050, 972013850, 972326700, 972639600, 972952550, 973265550, 973578600, 973891700, 974204850, 974518050, 974831300, 975144600, 975457950, 975771350, 976084800, 976398300, 976711850, 977025450, 977339100, 977652800, 977966550, 978280350, 978594200, 978908100, 979222050, 979536050, 979850100, 980164200, 980478350, 980792550, 981106800, 981421100, 981735450, 982049850, 982364300, 982678800, 982993350, 983307950, 983622600, 983937300, 984252050, 984566850, 984881700, 985196600, 985511550, 985826550, 986141600, 986456700, 986771850, 987087050, 987402300, 987717600, 988032950, 988348350, 988663800, 988979300, 989294850, 989610450, 989926100, 990241800, 990557550, 990873350, 991189200, 991505100, 991821050, 992137050, 992453100, 992769200, 993085350, 993401550, 993717800, 994034100, 994350450, 994666850, 994983300, 995299800, 995616350, 995932950, 996249600, 996566300, 996883050, 997199850, 997516700, 997833600, 998150550, 998467550, 998784600, 999101700, 999418850, 999736050, 1000053300, 1000370600, 1000687950, 1001005350, 1001322800, 1001640300, 1001957850, 1002275450, 1002593100, 1002910800, 1003228550, 1003546350, 1003864200, 1004182100, 1004500050, 1004818050, 1005136100, 1005454200, 1005772350, 1006090550, 1006408800, 1006727100, 1007045450, 1007363850, 1007682300, 1008000800, 1008319350, 1008637950, 1008956600, 1009275300, 1009594050, 1009912850, 1010231700, 1010550600, 1010869550, 1011188550, 1011507600, 1011826700, 1012145850, 1012465050, 1012784300, 1013103600, 1013422950, 1013742350, 1014061800, 1014381300, 1014700850, 1015020450, 1015340100, 1015659800, 1015979550, 1016299350, 1016619200, 1016939100, 1017259050, 1017579050, 1017899100, 1018219200, 1018539350, 1018859550, 1019179800, 1019500100, 1019820450, 1020140850, 1020461300, 1020781800, 1021102350, 1021422950, 1021743600, 1022064300, 1022385050, 1022705850, 1023026700, 1023347600, 1023668550, 1023989550, 1024310600, 1024631700, 1024952850, 1025274050, 1025595300, 1025916600, 1026237950, 1026559350, 1026880800, 1027202300, 1027523850, 1027845450, 1028167100, 1028488800, 1028810550, 1029132350, 1029454200, 1029776100, 1030098050, 1030420050, 1030742100, 1031064200, 1031386350, 1031708550, 1032030800, 1032353100, 1032675450, 1032997850, 1033320300, 1033642800, 1033965350, 1034287950, 1034610600, 1034933300, 1035256050, 1035578850, 1035901700, 1036224600, 1036547550, 1036870550, 1037193600, 1037516700, 1037839850, 1038163050, 1038486300, 1038809600, 1039132950, 1039456350, 1039779800, 1040103300, 1040426850, 1040750450, 1041074100, 1041397800, 1041721550, 1042045350, 1042369200, 1042693100, 1043017050, 1043341050, 1043665100, 1043989200, 1044313350, 1044637550, 1044961800, 1045286100, 1045610450, 1045934850, 1046259300, 1046583800, 1046908350, 1047232950, 1047557600, 1047882300, 1048207050, 1048531850, 1048856700, 1049181600, 1049506550, 1049831550, 1050156600, 1050481700, 1050806850, 1051132050, 1051457300, 1051782600, 1052107950, 1052433350, 1052758800, 1053084300, 1053409850, 1053735450, 1054061100, 1054386800, 1054712550, 1055038350, 1055364200, 1055690100, 1056016050, 1056342050, 1056668100, 1056994200, 1057320350, 1057646550, 1057972800, 1058299100, 1058625450, 1058951850, 1059278300, 1059604800, 1059931350, 1060257950, 1060584600, 1060911300, 1061238050, 1061564850, 1061891700, 1062218600, 1062545550, 1062872550, 1063199600, 1063526700, 1063853850, 1064181050, 1064508300, 1064835600, 1065162950, 1065490350, 1065817800, 1066145300, 1066472850, 1066800450, 1067128100, 1067455800, 1067783550, 1068111350, 1068439200, 1068767100, 1069095050, 1069423050, 1069751100, 1070079200, 1070407350, 1070735550, 1071063800, 1071392100, 1071720450, 1072048850, 1072377300, 1072705800, 1073034350, 1073362950, 1073691600, 1074020300, 1074349050, 1074677850, 1075006700, 1075335600, 1075664550, 1075993550, 1076322600, 1076651700, 1076980850, 1077310050, 1077639300, 1077968600, 1078297950, 1078627350, 1078956800, 1079286300, 1079615850, 1079945450, 1080275100, 1080604800, 1080934550, 1081264350, 1081594200, 1081924100, 1082254050, 1082584050, 1082914100, 1083244200, 1083574350, 1083904550, 1084234800, 1084565100, 1084895450, 1085225850, 1085556300, 1085886800, 1086217350, 1086547950, 1086878600, 1087209300, 1087540050, 1087870850, 1088201700, 1088532600, 1088863550, 1089194550, 1089525600, 1089856700, 1090187850, 1090519050, 1090850300, 1091181600, 1091512950, 1091844350, 1092175800, 1092507300, 1092838850, 1093170450, 1093502100, 1093833800, 1094165550, 1094497350, 1094829200, 1095161100, 1095493050, 1095825050, 1096157100, 1096489200, 1096821350, 1097153550, 1097485800, 1097818100, 1098150450, 1098482850, 1098815300, 1099147800, 1099480350, 1099812950, 1100145600, 1100478300, 1100811050, 1101143850, 1101476700, 1101809600, 1102142550, 1102475550, 1102808600, 1103141700, 1103474850, 1103808050, 1104141300, 1104474600, 1104807950, 1105141350, 1105474800, 1105808300, 1106141850, 1106475450, 1106809100, 1107142800, 1107476550, 1107810350, 1108144200, 1108478100, 1108812050, 1109146050, 1109480100, 1109814200, 1110148350, 1110482550, 1110816800, 1111151100, 1111485450, 1111819850, 1112154300, 1112488800, 1112823350, 1113157950, 1113492600, 1113827300, 1114162050, 1114496850, 1114831700, 1115166600, 1115501550, 1115836550, 1116171600, 1116506700, 1116841850, 1117177050, 1117512300, 1117847600, 1118182950, 1118518350, 1118853800, 1119189300, 1119524850, 1119860450, 1120196100, 1120531800, 1120867550, 1121203350, 1121539200, 1121875100, 1122211050, 1122547050, 1122883100, 1123219200, 1123555350, 1123891550, 1124227800, 1124564100, 1124900450, 1125236850, 1125573300, 1125909800, 1126246350, 1126582950, 1126919600, 1127256300, 1127593050, 1127929850, 1128266700, 1128603600, 1128940550, 1129277550, 1129614600, 1129951700, 1130288850, 1130626050, 1130963300, 1131300600, 1131637950, 1131975350, 1132312800, 1132650300, 1132987850, 1133325450, 1133663100, 1134000800, 1134338550, 1134676350, 1135014200, 1135352100, 1135690050, 1136028050, 1136366100, 1136704200, 1137042350, 1137380550, 1137718800, 1138057100, 1138395450, 1138733850, 1139072300, 1139410800, 1139749350, 1140087950, 1140426600, 1140765300, 1141104050, 1141442850, 1141781700, 1142120600, 1142459550, 1142798550, 1143137600, 1143476700, 1143815850, 1144155050, 1144494300, 1144833600, 1145172950, 1145512350, 1145851800, 1146191300, 1146530850, 1146870450, 1147210100, 1147549800, 1147889550, 1148229350, 1148569200, 1148909100, 1149249050, 1149589050, 1149929100, 1150269200, 1150609350, 1150949550, 1151289800, 1151630100, 1151970450, 1152310850, 1152651300, 1152991800, 1153332350, 1153672950, 1154013600, 1154354300, 1154695050, 1155035850, 1155376700, 1155717600, 1156058550, 1156399550, 1156740600, 1157081700, 1157422850, 1157764050, 1158105300, 1158446600, 1158787950, 1159129350, 1159470800, 1159812300, 1160153850, 1160495450, 1160837100, 1161178800, 1161520550, 1161862350, 1162204200, 1162546100, 1162888050, 1163230050, 1163572100, 1163914200, 1164256350, 1164598550, 1164940800, 1165283100, 1165625450, 1165967850, 1166310300, 1166652800, 1166995350, 1167337950, 1167680600, 1168023300, 1168366050, 1168708850, 1169051700, 1169394600, 1169737550, 1170080550, 1170423600, 1170766700, 1171109850, 1171453050, 1171796300, 1172139600, 1172482950, 1172826350, 1173169800, 1173513300, 1173856850, 1174200450, 1174544100, 1174887800, 1175231550, 1175575350, 1175919200, 1176263100, 1176607050, 1176951050, 1177295100, 1177639200, 1177983350, 1178327550, 1178671800, 1179016100, 1179360450, 1179704850, 1180049300, 1180393800, 1180738350, 1181082950, 1181427600, 1181772300, 1182117050, 1182461850, 1182806700, 1183151600, 1183496550, 1183841550, 1184186600, 1184531700, 1184876850, 1185222050, 1185567300, 1185912600, 1186257950, 1186603350, 1186948800, 1187294300, 1187639850, 1187985450, 1188331100, 1188676800, 1189022550, 1189368350, 1189714200, 1190060100, 1190406050, 1190752050, 1191098100, 1191444200, 1191790350, 1192136550, 1192482800, 1192829100, 1193175450, 1193521850, 1193868300, 1194214800, 1194561350, 1194907950, 1195254600, 1195601300, 1195948050, 1196294850, 1196641700, 1196988600, 1197335550, 1197682550, 1198029600, 1198376700, 1198723850, 1199071050, 1199418300, 1199765600, 1200112950, 1200460350, 1200807800, 1201155300, 1201502850, 1201850450, 1202198100, 1202545800, 1202893550, 1203241350, 1203589200, 1203937100, 1204285050, 1204633050, 1204981100, 1205329200, 1205677350, 1206025550, 1206373800, 1206722100, 1207070450, 1207418850, 1207767300, 1208115800, 1208464350, 1208812950, 1209161600, 1209510300, 1209859050, 1210207850, 1210556700, 1210905600, 1211254550, 1211603550, 1211952600, 1212301700, 1212650850, 1213000050, 1213349300, 1213698600, 1214047950, 1214397350, 1214746800, 1215096300, 1215445850, 1215795450, 1216145100, 1216494800, 1216844550, 1217194350, 1217544200, 1217894100, 1218244050, 1218594050, 1218944100, 1219294200, 1219644350, 1219994550, 1220344800, 1220695100, 1221045450, 1221395850, 1221746300, 1222096800, 1222447350, 1222797950, 1223148600, 1223499300, 1223850050, 1224200850, 1224551700, 1224902600, 1225253550, 1225604550, 1225955600, 1226306700, 1226657850, 1227009050, 1227360300, 1227711600, 1228062950, 1228414350, 1228765800, 1229117300, 1229468850, 1229820450, 1230172100, 1230523800, 1230875550, 1231227350, 1231579200, 1231931100, 1232283050, 1232635050, 1232987100, 1233339200, 1233691350, 1234043550, 1234395800, 1234748100, 1235100450, 1235452850, 1235805300, 1236157800, 1236510350, 1236862950, 1237215600, 1237568300, 1237921050, 1238273850, 1238626700, 1238979600, 1239332550, 1239685550, 1240038600, 1240391700, 1240744850, 1241098050, 1241451300, 1241804600, 1242157950, 1242511350, 1242864800, 1243218300, 1243571850, 1243925450, 1244279100, 1244632800, 1244986550, 1245340350, 1245694200, 1246048100, 1246402050, 1246756050, 1247110100, 1247464200, 1247818350, 1248172550, 1248526800, 1248881100, 1249235450, 1249589850, 1249944300, 1250298800, 1250653350, 1251007950, 1251362600, 1251717300, 1252072050, 1252426850, 1252781700, 1253136600, 1253491550, 1253846550, 1254201600, 1254556700, 1254911850, 1255267050, 1255622300, 1255977600, 1256332950, 1256688350, 1257043800, 1257399300, 1257754850, 1258110450, 1258466100, 1258821800, 1259177550, 1259533350, 1259889200, 1260245100, 1260601050, 1260957050, 1261313100, 1261669200, 1262025350, 1262381550, 1262737800, 1263094100, 1263450450, 1263806850, 1264163300, 1264519800, 1264876350, 1265232950, 1265589600, 1265946300, 1266303050, 1266659850, 1267016700, 1267373600, 1267730550, 1268087550, 1268444600, 1268801700, 1269158850, 1269516050, 1269873300, 1270230600, 1270587950, 1270945350, 1271302800, 1271660300, 1272017850, 1272375450, 1272733100, 1273090800, 1273448550, 1273806350, 1274164200, 1274522100, 1274880050, 1275238050, 1275596100, 1275954200, 1276312350, 1276670550, 1277028800, 1277387100, 1277745450, 1278103850, 1278462300, 1278820800, 1279179350, 1279537950, 1279896600, 1280255300, 1280614050, 1280972850, 1281331700, 1281690600, 1282049550, 1282408550, 1282767600, 1283126700, 1283485850, 1283845050, 1284204300, 1284563600, 1284922950, 1285282350, 1285641800, 1286001300, 1286360850, 1286720450, 1287080100, 1287439800, 1287799550, 1288159350, 1288519200, 1288879100, 1289239050, 1289599050, 1289959100, 1290319200, 1290679350, 1291039550, 1291399800, 1291760100, 1292120450, 1292480850, 1292841300, 1293201800, 1293562350, 1293922950, 1294283600, 1294644300, 1295005050, 1295365850, 1295726700, 1296087600, 1296448550, 1296809550, 1297170600, 1297531700, 1297892850, 1298254050, 1298615300, 1298976600, 1299337950, 1299699350, 1300060800, 1300422300, 1300783850, 1301145450, 1301507100, 1301868800, 1302230550, 1302592350, 1302954200, 1303316100, 1303678050, 1304040050, 1304402100, 1304764200, 1305126350, 1305488550, 1305850800, 1306213100, 1306575450, 1306937850, 1307300300, 1307662800, 1308025350, 1308387950, 1308750600, 1309113300, 1309476050, 1309838850, 1310201700, 1310564600, 1310927550, 1311290550, 1311653600, 1312016700, 1312379850, 1312743050, 1313106300, 1313469600, 1313832950, 1314196350, 1314559800, 1314923300, 1315286850, 1315650450, 1316014100, 1316377800, 1316741550, 1317105350, 1317469200, 1317833100, 1318197050, 1318561050, 1318925100, 1319289200, 1319653350, 1320017550, 1320381800, 1320746100, 1321110450, 1321474850, 1321839300, 1322203800, 1322568350, 1322932950, 1323297600, 1323662300, 1324027050, 1324391850, 1324756700, 1325121600, 1325486550, 1325851550, 1326216600, 1326581700, 1326946850, 1327312050, 1327677300, 1328042600, 1328407950, 1328773350, 1329138800, 1329504300, 1329869850, 1330235450, 1330601100, 1330966800, 1331332550, 1331698350, 1332064200, 1332430100, 1332796050, 1333162050, 1333528100, 1333894200, 1334260350, 1334626550, 1334992800, 1335359100, 1335725450, 1336091850, 1336458300, 1336824800, 1337191350, 1337557950, 1337924600, 1338291300, 1338658050, 1339024850, 1339391700, 1339758600, 1340125550, 1340492550, 1340859600, 1341226700, 1341593850, 1341961050, 1342328300, 1342695600, 1343062950, 1343430350, 1343797800, 1344165300, 1344532850, 1344900450, 1345268100, 1345635800, 1346003550, 1346371350, 1346739200, 1347107100, 1347475050, 1347843050, 1348211100, 1348579200, 1348947350, 1349315550, 1349683800, 1350052100, 1350420450, 1350788850, 1351157300, 1351525800, 1351894350, 1352262950, 1352631600, 1353000300, 1353369050, 1353737850, 1354106700, 1354475600, 1354844550, 1355213550, 1355582600, 1355951700, 1356320850, 1356690050, 1357059300, 1357428600, 1357797950, 1358167350, 1358536800, 1358906300, 1359275850, 1359645450, 1360015100, 1360384800, 1360754550, 1361124350, 1361494200, 1361864100, 1362234050, 1362604050, 1362974100, 1363344200, 1363714350, 1364084550, 1364454800, 1364825100, 1365195450, 1365565850, 1365936300, 1366306800, 1366677350, 1367047950, 1367418600, 1367789300, 1368160050, 1368530850, 1368901700, 1369272600, 1369643550, 1370014550, 1370385600, 1370756700, 1371127850, 1371499050, 1371870300, 1372241600, 1372612950, 1372984350, 1373355800, 1373727300, 1374098850, 1374470450, 1374842100, 1375213800, 1375585550, 1375957350, 1376329200, 1376701100, 1377073050, 1377445050, 1377817100, 1378189200, 1378561350, 1378933550, 1379305800, 1379678100, 1380050450, 1380422850, 1380795300, 1381167800, 1381540350, 1381912950, 1382285600, 1382658300, 1383031050, 1383403850, 1383776700, 1384149600, 1384522550, 1384895550, 1385268600, 1385641700, 1386014850, 1386388050, 1386761300, 1387134600, 1387507950, 1387881350, 1388254800, 1388628300, 1389001850, 1389375450, 1389749100, 1390122800, 1390496550, 1390870350, 1391244200, 1391618100, 1391992050, 1392366050, 1392740100, 1393114200, 1393488350, 1393862550, 1394236800, 1394611100, 1394985450, 1395359850, 1395734300, 1396108800, 1396483350, 1396857950, 1397232600, 1397607300, 1397982050, 1398356850, 1398731700, 1399106600, 1399481550, 1399856550, 1400231600, 1400606700, 1400981850, 1401357050, 1401732300, 1402107600, 1402482950, 1402858350, 1403233800, 1403609300, 1403984850, 1404360450, 1404736100, 1405111800, 1405487550, 1405863350, 1406239200, 1406615100, 1406991050, 1407367050, 1407743100, 1408119200, 1408495350, 1408871550, 1409247800, 1409624100, 1410000450, 1410376850, 1410753300, 1411129800, 1411506350, 1411882950, 1412259600, 1412636300, 1413013050, 1413389850, 1413766700, 1414143600, 1414520550, 1414897550, 1415274600, 1415651700, 1416028850, 1416406050, 1416783300, 1417160600, 1417537950, 1417915350, 1418292800, 1418670300, 1419047850, 1419425450, 1419803100, 1420180800, 1420558550, 1420936350, 1421314200, 1421692100, 1422070050, 1422448050, 1422826100, 1423204200, 1423582350, 1423960550, 1424338800, 1424717100, 1425095450, 1425473850, 1425852300, 1426230800, 1426609350, 1426987950, 1427366600, 1427745300, 1428124050, 1428502850, 1428881700, 1429260600, 1429639550, 1430018550, 1430397600, 1430776700, 1431155850, 1431535050, 1431914300, 1432293600, 1432672950, 1433052350, 1433431800, 1433811300, 1434190850, 1434570450, 1434950100, 1435329800, 1435709550, 1436089350, 1436469200, 1436849100, 1437229050, 1437609050, 1437989100, 1438369200, 1438749350, 1439129550, 1439509800, 1439890100, 1440270450, 1440650850, 1441031300, 1441411800, 1441792350, 1442172950, 1442553600, 1442934300, 1443315050, 1443695850, 1444076700, 1444457600, 1444838550, 1445219550, 1445600600, 1445981700, 1446362850, 1446744050, 1447125300, 1447506600, 1447887950, 1448269350, 1448650800, 1449032300, 1449413850, 1449795450, 1450177100, 1450558800, 1450940550, 1451322350, 1451704200, 1452086100, 1452468050, 1452850050, 1453232100, 1453614200, 1453996350, 1454378550, 1454760800, 1455143100, 1455525450, 1455907850, 1456290300, 1456672800, 1457055350, 1457437950, 1457820600, 1458203300, 1458586050, 1458968850, 1459351700, 1459734600, 1460117550, 1460500550, 1460883600, 1461266700, 1461649850, 1462033050, 1462416300, 1462799600, 1463182950, 1463566350, 1463949800, 1464333300, 1464716850, 1465100450, 1465484100, 1465867800, 1466251550, 1466635350, 1467019200, 1467403100, 1467787050, 1468171050, 1468555100, 1468939200, 1469323350, 1469707550, 1470091800, 1470476100, 1470860450, 1471244850, 1471629300, 1472013800, 1472398350, 1472782950, 1473167600, 1473552300, 1473937050, 1474321850, 1474706700, 1475091600, 1475476550, 1475861550, 1476246600, 1476631700, 1477016850, 1477402050, 1477787300, 1478172600, 1478557950, 1478943350, 1479328800, 1479714300, 1480099850, 1480485450, 1480871100, 1481256800, 1481642550, 1482028350, 1482414200, 1482800100, 1483186050, 1483572050, 1483958100, 1484344200, 1484730350, 1485116550, 1485502800, 1485889100, 1486275450, 1486661850, 1487048300, 1487434800, 1487821350, 1488207950, 1488594600, 1488981300, 1489368050, 1489754850, 1490141700, 1490528600, 1490915550, 1491302550, 1491689600, 1492076700, 1492463850, 1492851050, 1493238300, 1493625600, 1494012950, 1494400350, 1494787800, 1495175300, 1495562850, 1495950450, 1496338100, 1496725800, 1497113550, 1497501350, 1497889200, 1498277100, 1498665050, 1499053050, 1499441100, 1499829200, 1500217350, 1500605550, 1500993800, 1501382100, 1501770450, 1502158850, 1502547300, 1502935800, 1503324350, 1503712950, 1504101600, 1504490300, 1504879050, 1505267850, 1505656700, 1506045600, 1506434550, 1506823550, 1507212600, 1507601700, 1507990850, 1508380050, 1508769300, 1509158600, 1509547950, 1509937350, 1510326800, 1510716300, 1511105850, 1511495450, 1511885100, 1512274800, 1512664550, 1513054350, 1513444200, 1513834100, 1514224050, 1514614050, 1515004100, 1515394200, 1515784350, 1516174550, 1516564800, 1516955100, 1517345450, 1517735850, 1518126300, 1518516800, 1518907350, 1519297950, 1519688600, 1520079300, 1520470050, 1520860850, 1521251700, 1521642600, 1522033550, 1522424550, 1522815600, 1523206700, 1523597850, 1523989050, 1524380300, 1524771600, 1525162950, 1525554350, 1525945800, 1526337300, 1526728850, 1527120450, 1527512100, 1527903800, 1528295550, 1528687350, 1529079200, 1529471100, 1529863050, 1530255050, 1530647100, 1531039200, 1531431350, 1531823550, 1532215800, 1532608100, 1533000450, 1533392850, 1533785300, 1534177800, 1534570350, 1534962950, 1535355600, 1535748300, 1536141050, 1536533850, 1536926700, 1537319600, 1537712550, 1538105550, 1538498600, 1538891700, 1539284850, 1539678050, 1540071300, 1540464600, 1540857950, 1541251350, 1541644800, 1542038300, 1542431850, 1542825450, 1543219100, 1543612800, 1544006550, 1544400350, 1544794200, 1545188100, 1545582050, 1545976050, 1546370100, 1546764200, 1547158350, 1547552550, 1547946800, 1548341100, 1548735450, 1549129850, 1549524300, 1549918800, 1550313350, 1550707950, 1551102600, 1551497300, 1551892050, 1552286850, 1552681700, 1553076600, 1553471550, 1553866550, 1554261600, 1554656700, 1555051850, 1555447050, 1555842300, 1556237600, 1556632950, 1557028350, 1557423800, 1557819300, 1558214850, 1558610450, 1559006100, 1559401800, 1559797550, 1560193350, 1560589200, 1560985100, 1561381050, 1561777050, 1562173100, 1562569200, 1562965350, 1563361550, 1563757800, 1564154100, 1564550450, 1564946850, 1565343300, 1565739800, 1566136350, 1566532950, 1566929600, 1567326300, 1567723050, 1568119850, 1568516700, 1568913600, 1569310550, 1569707550, 1570104600, 1570501700, 1570898850, 1571296050, 1571693300, 1572090600, 1572487950, 1572885350, 1573282800, 1573680300, 1574077850, 1574475450, 1574873100, 1575270800, 1575668550, 1576066350, 1576464200, 1576862100, 1577260050, 1577658050, 1578056100, 1578454200, 1578852350, 1579250550, 1579648800, 1580047100, 1580445450, 1580843850, 1581242300, 1581640800, 1582039350, 1582437950, 1582836600, 1583235300, 1583634050, 1584032850, 1584431700, 1584830600, 1585229550, 1585628550, 1586027600, 1586426700, 1586825850, 1587225050, 1587624300, 1588023600, 1588422950, 1588822350, 1589221800, 1589621300, 1590020850, 1590420450, 1590820100, 1591219800, 1591619550, 1592019350, 1592419200, 1592819100, 1593219050, 1593619050, 1594019100, 1594419200, 1594819350, 1595219550, 1595619800, 1596020100, 1596420450, 1596820850, 1597221300, 1597621800, 1598022350, 1598422950, 1598823600, 1599224300, 1599625050, 1600025850, 1600426700, 1600827600, 1601228550, 1601629550, 1602030600, 1602431700, 1602832850, 1603234050, 1603635300, 1604036600, 1604437950, 1604839350, 1605240800, 1605642300, 1606043850, 1606445450, 1606847100, 1607248800, 1607650550, 1608052350, 1608454200, 1608856100, 1609258050, 1609660050, 1610062100, 1610464200, 1610866350, 1611268550, 1611670800, 1612073100, 1612475450, 1612877850, 1613280300, 1613682800, 1614085350, 1614487950, 1614890600, 1615293300, 1615696050, 1616098850, 1616501700, 1616904600, 1617307550, 1617710550, 1618113600, 1618516700, 1618919850, 1619323050, 1619726300, 1620129600, 1620532950, 1620936350, 1621339800, 1621743300, 1622146850, 1622550450, 1622954100, 1623357800, 1623761550, 1624165350, 1624569200, 1624973100, 1625377050, 1625781050, 1626185100, 1626589200, 1626993350, 1627397550, 1627801800, 1628206100, 1628610450, 1629014850, 1629419300, 1629823800, 1630228350, 1630632950, 1631037600, 1631442300, 1631847050, 1632251850, 1632656700, 1633061600, 1633466550, 1633871550, 1634276600, 1634681700, 1635086850, 1635492050, 1635897300, 1636302600, 1636707950, 1637113350, 1637518800, 1637924300, 1638329850, 1638735450, 1639141100, 1639546800, 1639952550, 1640358350, 1640764200, 1641170100, 1641576050, 1641982050, 1642388100, 1642794200, 1643200350, 1643606550, 1644012800, 1644419100, 1644825450, 1645231850, 1645638300, 1646044800, 1646451350, 1646857950, 1647264600, 1647671300, 1648078050, 1648484850, 1648891700, 1649298600, 1649705550, 1650112550, 1650519600, 1650926700, 1651333850, 1651741050, 1652148300, 1652555600, 1652962950, 1653370350, 1653777800, 1654185300, 1654592850, 1655000450, 1655408100, 1655815800, 1656223550, 1656631350, 1657039200, 1657447100, 1657855050, 1658263050, 1658671100, 1659079200, 1659487350, 1659895550, 1660303800, 1660712100, 1661120450, 1661528850, 1661937300, 1662345800, 1662754350, 1663162950, 1663571600, 1663980300, 1664389050, 1664797850, 1665206700, 1665615600, 1666024550, 1666433550, 1666842600, 1667251700, 1667660850, 1668070050, 1668479300, 1668888600, 1669297950, 1669707350, 1670116800, 1670526300, 1670935850, 1671345450, 1671755100, 1672164800, 1672574550, 1672984350, 1673394200, 1673804100, 1674214050, 1674624050, 1675034100, 1675444200, 1675854350, 1676264550, 1676674800, 1677085100, 1677495450, 1677905850, 1678316300, 1678726800, 1679137350, 1679547950, 1679958600, 1680369300, 1680780050, 1681190850, 1681601700, 1682012600, 1682423550, 1682834550, 1683245600, 1683656700, 1684067850, 1684479050, 1684890300, 1685301600, 1685712950, 1686124350, 1686535800, 1686947300, 1687358850, 1687770450, 1688182100, 1688593800, 1689005550, 1689417350, 1689829200, 1690241100, 1690653050, 1691065050, 1691477100, 1691889200, 1692301350, 1692713550, 1693125800, 1693538100, 1693950450, 1694362850, 1694775300, 1695187800, 1695600350, 1696012950, 1696425600, 1696838300, 1697251050, 1697663850, 1698076700, 1698489600, 1698902550, 1699315550, 1699728600, 1700141700, 1700554850, 1700968050, 1701381300, 1701794600, 1702207950, 1702621350, 1703034800, 1703448300, 1703861850, 1704275450, 1704689100, 1705102800, 1705516550, 1705930350, 1706344200, 1706758100, 1707172050, 1707586050, 1708000100, 1708414200, 1708828350, 1709242550, 1709656800, 1710071100, 1710485450, 1710899850, 1711314300, 1711728800, 1712143350, 1712557950, 1712972600, 1713387300, 1713802050, 1714216850, 1714631700, 1715046600, 1715461550, 1715876550, 1716291600, 1716706700, 1717121850, 1717537050, 1717952300, 1718367600, 1718782950, 1719198350, 1719613800, 1720029300, 1720444850, 1720860450, 1721276100, 1721691800, 1722107550, 1722523350, 1722939200, 1723355100, 1723771050, 1724187050, 1724603100, 1725019200, 1725435350, 1725851550, 1726267800, 1726684100, 1727100450, 1727516850, 1727933300, 1728349800, 1728766350, 1729182950, 1729599600, 1730016300, 1730433050, 1730849850, 1731266700, 1731683600, 1732100550, 1732517550, 1732934600, 1733351700, 1733768850, 1734186050, 1734603300, 1735020600, 1735437950, 1735855350, 1736272800, 1736690300, 1737107850, 1737525450, 1737943100, 1738360800, 1738778550, 1739196350, 1739614200, 1740032100, 1740450050, 1740868050, 1741286100, 1741704200, 1742122350, 1742540550, 1742958800, 1743377100, 1743795450, 1744213850, 1744632300, 1745050800, 1745469350, 1745887950, 1746306600, 1746725300, 1747144050, 1747562850, 1747981700, 1748400600, 1748819550, 1749238550, 1749657600, 1750076700, 1750495850, 1750915050, 1751334300, 1751753600, 1752172950, 1752592350, 1753011800, 1753431300, 1753850850, 1754270450, 1754690100, 1755109800, 1755529550, 1755949350, 1756369200, 1756789100, 1757209050, 1757629050, 1758049100, 1758469200, 1758889350, 1759309550, 1759729800, 1760150100, 1760570450, 1760990850, 1761411300, 1761831800, 1762252350, 1762672950, 1763093600, 1763514300, 1763935050, 1764355850, 1764776700, 1765197600, 1765618550, 1766039550, 1766460600, 1766881700, 1767302850, 1767724050, 1768145300, 1768566600, 1768987950, 1769409350, 1769830800, 1770252300, 1770673850, 1771095450, 1771517100, 1771938800, 1772360550, 1772782350, 1773204200, 1773626100, 1774048050, 1774470050, 1774892100, 1775314200, 1775736350, 1776158550, 1776580800, 1777003100, 1777425450, 1777847850, 1778270300, 1778692800, 1779115350, 1779537950, 1779960600, 1780383300, 1780806050, 1781228850, 1781651700, 1782074600, 1782497550, 1782920550, 1783343600, 1783766700, 1784189850, 1784613050, 1785036300, 1785459600, 1785882950, 1786306350, 1786729800, 1787153300, 1787576850 };
int Features::levelrp = 0;
void Features::SetRank(int rpvalue)
{
	if (rpvalue < 0 && rpvalue > 8000)
	{
		rpvalue = 8000;
	}
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_SET_RP_GIFT_ADMIN"), Features::Levels[rpvalue], 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_SET_RP_GIFT_ADMIN"), Features::Levels[rpvalue], 0);
}
bool Features::shootcashbool = false;
void Features::shootcash()
{
	//g_CallbackScript->AddCallback<ModelCallback>(-1666779307, [] {
	//	Ped PedID = PLAYER::PLAYER_PED_ID();
	//	Vector3 pos;
	//	pos.z + .5f;
	//	WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PedID, &pos);
	//	OBJECT::CREATE_AMBIENT_PICKUP(0x1E9A99F8, pos.x, pos.y, pos.z, 0, 2500, -1666779307, FALSE, TRUE);
	//});
}
bool Features::teleportbool = false;
void Features::teleportgun()
{
	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_SHOOTING_IN_AREA)
	{
		Vector3 iCoord;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &iCoord))
		{
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), iCoord.x, iCoord.y, iCoord.z, true, true, true, true);

		}


	}
}

bool Features::BunkerBool = false;
void Features::Bunker(bool toggle)
{
	globalHandle(262145).At(21389).As<int>() = 1;
}

bool Features::CashDropLocationBool;
Vector3 coordssss;
void Features::CashDropLocation()
{
	//Vector3 coords;
	//if (is_ped_shooting(PLAYER::PLAYER_PED_ID()))
	//{
	//	if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &coordssss)) {
	//	}
	//}
	//coords = coordssss;

	//g_CallbackScript->AddCallback<ModelCallback>(-1666779307, [coords] {
	//	OBJECT::CREATE_AMBIENT_PICKUP(0x1E9A99F8, coords.x, coords.y, coords.z + 0.5, 0, 2500, -1666779307, FALSE, TRUE);
		//});

}
bool Features::savenewdrop = false;
void Features::cashdropself()
{
	if ((timeGetTime() - Features::TimePD1) > Features::BagDelay)
	{
		g_CallbackScript->AddCallback<ModelCallback>(-1666779307, [] {
			Ped iPed = PLAYER::PLAYER_PED_ID();
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(iPed, 0);
			OBJECT::CREATE_AMBIENT_PICKUPP(0x1E9A99F8, pCoords, 0, Features::DropAmount, -1666779307, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-1666779307);
		});
		Features::TimePD1 = timeGetTime();

	}
}



bool Features::MoneyDropBool = false;
void Features::MoneyDrop()
{
	if ((timeGetTime() - TimePD55) > Features::BagDelay)
	{
		g_CallbackScript->AddCallback<ModelCallback>(Features::DROPHASH, [] {
			Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(iPed, 0);
			OBJECT::CREATE_AMBIENT_PICKUPP(0xDE78F17E, pCoords, 0, Features::DropAmount, Features::DROPHASH, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Features::DROPHASH);
			Features::TotalDropedMoney += Features::DropAmount;
			Features::TotalMoneyBags += 1;
		});
		TimePD55 = timeGetTime();
	}
}


bool Features::RPDropBool = false;
void Features::RPDrop()
{
	if ((timeGetTime() - TimePD55) > Features::RPDROPDELAY)
	{
		g_CallbackScript->AddCallback<ModelCallback>(0xd937a5e9, [] {
			Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(iPed, 0);
			OBJECT::CREATE_AMBIENT_PICKUPP(0xC3CD8B31, pCoords, 0, 0, 0xd937a5e9, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0xd937a5e9);
			Features::TotalMoneyBags += 1;
		});
		TimePD55 = timeGetTime();
	}
}


bool Features::KickDropBool = false;
void Features::KickDrop()
{
	if ((timeGetTime() - TimePD55) > 5)
	{
		g_CallbackScript->AddCallback<ModelCallback>(0xd937a5e9, [] {
			Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(iPed, 0);
			OBJECT::CREATE_AMBIENT_PICKUPP(0xC3CD8B31, pCoords, 0, 2500, 0xd937a5e9, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0xd937a5e9);
		});
		TimePD55 = timeGetTime();
	}
}



bool Features::ALLMoneyDropBool = false;
void Features::ALLMoneyDrop()
{
	if ((timeGetTime() - TimePD55) > Features::BagDelay)
	{


			g_CallbackScript->AddCallback<ModelCallback>(Features::DROPHASH, [] {
				for (int i = 0; i < 32; i++)
				{
					Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
					Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(iPed, 0);
					OBJECT::CREATE_AMBIENT_PICKUPP(0xDE78F17E, pCoords, 0, Features::DropAmount, Features::DROPHASH, FALSE, TRUE);// This works and all but seems to cause native execution errors on slower PC's.  
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Features::DROPHASH);
					Features::TotalDropedMoney += Features::DropAmount;
					Features::TotalMoneyBags += 1;
				}
			});
		
		TimePD55 = timeGetTime();
	}
}



void Features::AltStealth(int amount)
{
	Any ivar3 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1, 2147483647);;
	if (UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&ivar3, 1474183246, 312105838, 1445302971, amount, Features::ToBank ? 4 : 1))
		UNK3::_NETWORK_SHOP_CHECKOUT_START(ivar3);
}
bool Features::fakezerohealthbool = false;
void Features::fakezerohealth()
{
	ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 100);
}
bool Features::StealthLoop = false;
void Features::doStealth(int amount) {
	globalHandle(4264014 + 1).As<int>() = 2147483646;
	globalHandle(4264014 + 7).As<int>() = 2147483647;
	globalHandle(4264014 + 6).As<int>() = 0;
	globalHandle(4264014 + 5).As<int>() = 0;
	globalHandle(4264014 + 3).As<int>() = 312105838;
	globalHandle(4264014 + 2).As<int>() = amount;
	globalHandle(4264014).As<int>() = 1;	// 4264014
}
bool Features::ChatSensor = false;
int eclone[1000];
int egcount = 1;
void Features::Enemy(char* model)
{
	Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
	if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
	Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE");
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
	Hash pedm = GAMEPLAY::GET_HASH_KEY(model);
	g_CallbackScript->AddCallback<ModelCallback>(pedm, [pedm, pos, railgun, selectedplayer] {
		Ped attacker =  PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 0.5, 0, *g_GameVariables->is_session_started, 0);
		ENTITY::SET_ENTITY_INVINCIBLE(attacker, false);
		PED::SET_PED_COMBAT_ABILITY(attacker, 100);
		WEAPON::GIVE_WEAPON_TO_PED(attacker, railgun, railgun, 9999, 9999);
		PED::SET_PED_CAN_SWITCH_WEAPON(attacker, true);
		AI::TASK_COMBAT_PED(attacker, selectedplayer, 1, 1);
		PED::SET_PED_ALERTNESS(attacker, 1000);
		PED::SET_PED_COMBAT_RANGE(attacker, 1000);
	});
}
int clone[1000];
int gcount = 1;
void Features::Bodyguard(char* model)
{
	Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
	if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
	Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE");
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
	Hash pedm = GAMEPLAY::GET_HASH_KEY(model);
	g_CallbackScript->AddCallback<ModelCallback>(pedm, [pedm, pos, railgun, selectedplayer] {
		int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
		Ped bodyguard = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 0.5, 0, *g_GameVariables->is_session_started, 0);
		PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
		PED::SET_PED_AS_GROUP_MEMBER(bodyguard, my_group);
		PED::SET_PED_NEVER_LEAVES_GROUP(bodyguard, my_group);
		ENTITY::SET_ENTITY_INVINCIBLE(bodyguard, false);
		PED::SET_PED_COMBAT_ABILITY(bodyguard, 100);
		WEAPON::GIVE_WEAPON_TO_PED(bodyguard, railgun, railgun, 9999, 9999);
		PED::SET_PED_CAN_SWITCH_WEAPON(bodyguard, true);
		PED::SET_GROUP_FORMATION(my_group, 3);
		PED::SET_PED_MAX_HEALTH(bodyguard, 5000);

	});
}
void Features::RemoveStealth(int amount) {
	globalHandle(4264014 + 1).As<int>() = 2147483646;
	globalHandle(4264014 + 7).As<int>() = 2147483647;
	globalHandle(4264014 + 6).As<int>() = 0;
	globalHandle(4264014 + 5).As<int>() = 0;
	globalHandle(4264014 + 3).As<int>() = 537254313;
	globalHandle(4264014 + 2).As<int>() = -amount;
	globalHandle(4264014).As<int>() = 1;
}
bool Features::AntiMoneyDrop = false;
bool Features::ToBank = false;
void Features::UnlockSnacks()
{
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CIGARETTES_BOUGHT"), 2000000000, 1);
	ScriptEventLog("~g~Snacks Maxed...");
}
void Features::UnlockArmor()
{
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
	//
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
	ScriptEventLog("~g~Armor Maxed...");
}
void Features::UnlockFireworks()
{
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
	//
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_RED"), 2000000000, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
	ScriptEventLog("~g~Fireworks Maxed...");
}
void Features::UnlockStats()
{
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
	ScriptEventLog("~g~Stats Maxed...");
}
void Features::UnlockTattoos()
{

	// MP0_AWD_FMATTGANGHQ MP0_AWD_FMWINEVERYGAMEMODE MP0_AWD_FMRACEWORLDRECHOLDER MP0_AWD_FMFULLYMODDEDCAR MP0_AWD_FMMOSTKILLSSURVIVE MP0_AWD_FMKILL3ANDWINGTARACE MP0_AWD_FMKILLSTREAKSDM
	Hash Tattoos[] = { 0x49e3d35b, 0xbdda53b4, 0x655e0bad, 0xe9472bb4, 0xc41b8767, 0x43d56fad, 0x3099c3fe, 0x2039515C, 0x4AE88781, 0x90867F4C, 0xE7C84055, 0x98FF48A5, 0xBE3FD785, 0xF3D60861 };
	for (Hash h : Tattoos)
		STATS::STAT_SET_BOOL(h, 1, 1);

	STATS::STAT_SET_INT(0x12f3b311, 20, 1); // MP0_AWD_HOLD_UP_SHOPS
	STATS::STAT_SET_INT(0x36177F20, 20, 1); // MP0_AWD_HOLD_UP_SHOPS

											// MP0_AWD_LAPDANCES MP0_AWD_SECURITY_CARS_ROBBED MP0_AWD_FMKILLBOUNTY MP0_AWD_CAR_BOMBS_ENEMY_KILLS
	Hash Stats25[] = { 0x4314583e, 0x5413e4e9, 0xfb6b31f1, 0xaae88a2f, 0xF29D01D9, 0x5413E4E9, 0x4F6CDED8, 0x1AF2DE9E };
	for (Hash h : Stats25)
		STATS::STAT_SET_INT(h, 25, 1);

	// MP0_AWD_FM_DM_WINS MP0_AWD_FM_TDM_MVP MP0_AWD_RACES_WON MP0_AWD_FMREVENGEKILLSDM
	Hash Stats50[] = { 0x4c2e3849, 0xc479c331, 0x54305ac6, 0xb2f3860f, 0x34069BE5, 0x2199954E, 0x43BDA5D0, 0x52326867 };
	for (Hash h : Stats50)
		STATS::STAT_SET_INT(h, 50, 1);

	STATS::STAT_SET_INT(0xfac3eb18, 500, 1); // MP0_AWD_FM_DM_TOTALKILLS
	STATS::STAT_SET_INT(0x76DA8DDE, 500, 1); // MP1_AWD_FM_DM_TOTALKILLS

	STATS::STAT_SET_INT(0xee25f949, 500, 1); // MP0_PLAYER_HEADSHOTS
	STATS::STAT_SET_INT(0x3363CBA7, 500, 1); // MP1_PLAYER_HEADSHOTS
	STATS::STAT_SET_INT(0xcff5c480, 1000, 1); // MP0_DB_PLAYER_KILLS
	STATS::STAT_SET_INT(0xEEC100C9, 1000, 1); // MP1_DB_PLAYER_KILLS
	STATS::STAT_SET_INT(0xaba179f2, 50000, 1); // MP0_AWD_FMBBETWIN
	STATS::STAT_SET_INT(0xF678DE96, 50000, 1); // MP1_AWD_FMBBETWIN

	ScriptEventLog("~g~Tattoos Unlocked...");
}
void Features::UnlockParachutes()
{
	Hash Parachutes[] =
	{
		// MP0_CHAR_KIT_1_FM_UNLCK MP0_CHAR_KIT_2_FM_UNLCK MP0_CHAR_KIT_3_FM_UNLCK MP0_CHAR_KIT_4_FM_UNLCK MP0_CHAR_KIT_5_FM_UNLCK
		0xad72fbf2, 0x40bd0b85, 0xeda9551e, 0x5b09abba, 0xb2bef7f5,
		// MP0_CHAR_KIT_6_FM_UNLCK MP0_CHAR_KIT_7_FM_UNLCK MP0_CHAR_KIT_8_FM_UNLCK MP0_CHAR_KIT_9_FM_UNLCK MP0_CHAR_KIT_10_FM_UNLCK
		0xd6ae148f, 0x6ef3639f, 0x4e93ab72, 0xd958d97b, 0xabe64158,
		// MP0_CHAR_KIT_11_FM_UNLCK MP0_CHAR_KIT_12_FM_UNLCK
		0x9305c000, 0xe93fe20f,
		// MP0_CHAR_KIT_FM_PURCHASE MP0_CHAR_KIT_FM_PURCHASE2 MP0_CHAR_KIT_FM_PURCHASE3 MP0_CHAR_KIT_FM_PURCHASE4 MP0_CHAR_KIT_FM_PURCHASE5
		0x3d76c26c, 0x591945de, 0x66e0e16d, 0x3d268df9, 0xbc960cd2,
		// MP0_CHAR_KIT_FM_PURCHASE6 MP0_CHAR_KIT_FM_PURCHASE7 MP0_CHAR_KIT_FM_PURCHASE8 MP0_CHAR_KIT_FM_PURCHASE9 MP0_CHAR_KIT_FM_PURCHASE10
		0xca64a86f, 0xa1da575f, 0xb00bf3c2, 0xd8cac53f, 0x72f137e0,
		// MP0_CHAR_KIT_FM_PURCHASE11 MP0_CHAR_KIT_FM_PURCHASE12
		0xf2bc376c, 0x12d219
	};
	for (Hash h : Parachutes)
		STATS::STAT_SET_INT(h, -1, 1);
}
void Features::UnlockRims()
{
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_RACES_WON"), 50, 1);
	//Chrome Rims
	// MP0_AWD_WIN_CAPTURES MP0_AWD_FINISH_HEISTS MP0_AWD_FINISH_HEIST_SETUP_JOB MP0_AWD_WIN_LAST_TEAM_STANDINGS MP0_AWD_ONLY_PLAYER_ALIVE_LTS
	Hash Stats50[] = { 0xcfe6e176, 0x2f5bf8f, 0xe4c4cc91, 0x95546c90, 0xaa71df87, 0xD9C9649, 0x2037F997, 0x5550EA43, 0xB957BDE2, 0x512FC8F4 };
	for (Hash h : Stats50)
		STATS::STAT_SET_INT(h, 50, 1);

	// MP0_AWD_DROPOFF_CAP_PACKAGES MP0_AWD_KILL_CARRIER_CAPTURE MP0_AWD_NIGHTVISION_KILLS
	Hash Stats100[] = { 0x624901df, 0xbc4421b6, 0x3c9d6f53, 0x47AE528D, 0x2A8544EF, 0x77D6EA19 };
	for (Hash h : Stats100)
		STATS::STAT_SET_INT(h, 100, 1);
	ScriptEventLog("~g~Rims Unlocked...");
}
void Features::UnlockVehicles()
{

	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VEHICLE_ID_ADMIN_WEB"), 117401876, 1);
	Hash StatsMinusOne[] =
	{
		// MP0_CHAR_FM_CARMOD_1_UNLCK MP0_CHAR_FM_CARMOD_2_UNLCK MP0_CHAR_FM_CARMOD_3_UNLCK MP0_CHAR_FM_CARMOD_4_UNLCK MP0_CHAR_FM_CARMOD_5_UNLCK
		0x34e21552, 0x881f0a1e, 0x4ebf2ed2, 0xea7fe34c, 0xd20c5868, 0x672CDEEE, 0xF93314CE, 0x1C07E936, 0xA442C19A, 0xB0A6DAA9,
		// MP0_CHAR_FM_CARMOD_6_UNLCK MP0_CHAR_FM_CARMOD_7_UNLCK MP0_CHAR_FM_VEHICLE_1_UNLCK MP0_CHAR_FM_VEHICLE_2_UNLCK
		0xbee92cbe, 0x4d85836e, 0xb56ead95, 0x3d5d8200, 0x7799E88B, 0x993C61B8, 0x20553352,0x5A8BF1F7
	};
	for (Hash h : StatsMinusOne)
		STATS::STAT_SET_INT(h, -1, 1);

	// MP0_AWD_FMRALLYWONDRIVE MP0_AWD_FMRALLYWONNAV MP0_AWD_FMWINSEARACE MP0_AWD_FMWINAIRRACE
	Hash Stats1[] = { 0xbb5b1a96, 0x6ae2181d, 0xc5c0f286, 0x40bf1a36, 0xB43E0E1A, 0xB1590553, 0x58857E4, 0x16F2FD31 };
	for (Hash h : Stats1)
		STATS::STAT_SET_INT(h, 1, 1);

	// MP0_RACES_WON MP0_NUMBER_TURBO_STARTS_IN_RACE MP0_USJS_COMPLETED MP0_AWD_FM_RACES_FASTEST_LAP
	Hash Stats50[] = { 0x39a76053, 0x13c6b4b1, 0x13071b8f, 0xc13d4f3a, 0xB241D53B, 0xB0470AEA, 0xDE88D22F, 0xE751F17 };
	for (Hash h : Stats50)
		STATS::STAT_SET_INT(h, 50, 1);

	STATS::STAT_SET_INT(0xad05f506, 100, 1); // MP0_NUMBER_SLIPSTREAMS_IN_RACE
	STATS::STAT_SET_INT(0xE5FD50E2, 100, 1); // MP1_NUMBER_SLIPSTREAMS_IN_RACE

	ScriptEventLog("~g~Vehicles Unlocked...");
}
void Features::UnlockAchievements()
{
	STATS::STAT_SET_INT(0x53c59a8e, -1, 1); // MPPLY_HEIST_ACH_TRACKER
	STATS::STAT_SET_INT(0x796d2d6a, 25, 1); // MPPLY_AWD_FM_CR_DM_MADE
	STATS::STAT_SET_INT(0xd5d5279d, 25, 1); // MPPLY_AWD_FM_CR_RACES_MADE
	STATS::STAT_SET_INT(0xe00c1321, 100, 1); // MPPLY_AWD_FM_CR_PLAYED_BY_PEEP
	Hash StatsBools[] =
	{
		// MP0_AWD_FM_GOLF_HOLE_IN_1 MP0_AWD_FM_SHOOTRANG_GRAN_WON MP0_AWD_FM_TENNIS_STASETWIN MP0_AWD_FM6DARTCHKOUT MP0_AWD_FMATTGANGHQ
		0x22d9626f, 0x2bfe2b98, 0xcca40e6,  0xb6c51652, 0x49e3d35b,
		// MP0_AWD_BUY_EVERY_GUN MP0_AWD_FMWINEVERYGAMEMODE MP0_AWD_FM25DIFFERENTDM MP0_AWD_FM_TENNIS_5_SET_WINS MP0_AWD_FM25DIFFERENTRACES
		0x21f81ca1, 0xbdda53b4, 0x59de4ddc, 0x69e7c068, 0xb4f06c2f,
		// MP0_AWD_FM25DIFITEMSCLOTHES MP0_AWD_FMFULLYMODDEDCAR MP0_AWD_FMKILL3ANDWINGTARACE MP0_AWD_FMKILLSTREAKSDM MP0_AWD_FMMOSTKILLSGANGHIDE
		0x9ba12d14, 0xe9472bb4, 0x43d56fad, 0x3099c3fe, 0x5941fbad,
		// MP0_AWD_FMMOSTKILLSSURVIVE MP0_AWD_FMRACEWORLDRECHOLDER MP0_AWD_FMPICKUPDLCCRATE1ST MP0_AWD_FMWINCUSTOMRACE MP0_MP0_AWD_FMWINALLRACEMODES
		0xc41b8767, 0x655e0bad, 0x2ae837e4, 0x71212ddf, 0xda28ebe4,
		// MP0_AWD_FMTATTOOALLBODYPARTS
		0xe3520842
	};

	for (Hash h : StatsBools)
		STATS::STAT_SET_BOOL(h, 1, 1);
	STATS::STAT_SET_INT(0x723f39d6, 4, 1); // MP0_AWD_PASSENGERTIME
	STATS::STAT_SET_INT(0x653a8f83, 4, 1); // MP0_AWD_TIME_IN_HELICOPTER
	STATS::STAT_SET_INT(0x45e1432a, 5, 1); // MP0_MOST_FLIPS_IN_ONE_JUMP
	STATS::STAT_SET_INT(0xe9e500bc, 5, 1); // MP0_MOST_SPINS_IN_ONE_JUMP
	STATS::STAT_SET_INT(0x833d3192, 10, 1); // MP0_AWD_FMHORDWAVESSURVIVE
	STATS::STAT_SET_INT(0x12f3b311, 20, 1); // MP0_AWD_HOLD_UP_SHOPS
	Hash Stats25[] =
	{
		// MP0_AWD_CAR_BOMBS_ENEMY_KILLS MP0_AWD_FM_GOLF_WON MP0_AWD_FM_SHOOTRANG_CT_WON MP0_AWD_FM_SHOOTRANG_RT_WON MP0_AWD_FM_SHOOTRANG_TG_WON
		0xaae88a2f, 0xe847156c, 0x741f0838, 0xeac04cce, 0x898dab76, 0x1AF2DE9E, 0xA1787290, 0x5F76739A, 0x2C177BAD,
		// MP0_AWD_FM_TENNIS_WON MP0_AWD_SECURITY_CARS_ROBBED MP0_AWD_LAPDANCES MP0_MOST_ARM_WRESTLING_WINS MP0_AWD_NO_HAIRCUTS
		0xe51a03e4, 0x5413e4e9, 0x4314583e, 0xd9da214e, 0xa43c7aac, 0xEC234AE2, 0x46533E0C, 0xF29D01D9, 0x3EDE081C, 0xC55AAFAA,
		// MP0_AWD_WIN_AT_DARTS MP0_AWD_FM_GOLF_BIRDIES MP0_AWD_FM_TENNIS_ACE MP0_AWD_PARACHUTE_JUMPS_20M MP0_AWD_PARACHUTE_JUMPS_50M
		0x279625d2, 0x978c6413, 0x7036f468, 0x1e3139c0, 0xd95051b7, 0x61F5DB39, 0x786E5B58, 0xAE352AA3, 0xAFBB09A3, 0x2F6C1441,
		// MP0_AIR_LAUNCHES_OVER_40M MP0_AWD_FMCRATEDROPS MP0_AWD_FMKILLBOUNTY MP0_AWD_FMSHOOTDOWNCOPHELI MP0_AWD_FMRALLYWONDRIVE
		0x8a8786e7, 0x2671fd3,  0xfb6b31f1, 0xee270322, 0xbb5b1a96, 0xE7939C0B, 0x144E7D9F, 0x4F6CDED8, 0xF5EDCABA, 0xB43E0E1A,
		// MP0_AWD_FMRALLYWONNAV MP0_AWD_FMWINAIRRACE MP0_AWD_FMWINRACETOPOINTS MP0_AWD_FMWINSEARACE MP0_AWD_FMBASEJMP
		0x6ae2181d, 0x40bf1a36, 0xa11bb5b6, 0xc5c0f286, 0xe54057bd, 0xB1590553, 0x16F2FD31, 0x5A1942E7, 0x58857E4, 0xFA2E93FF,
		// MP0_AWD_FM_RACE_LAST_FIRST MP0_AWD_FM_RACES_FASTEST_LAP
		0x25609da9, 0xc13d4f3a, 0x3A2621D6, 0xE751F17
	};

	for (Hash h : Stats25)
		STATS::STAT_SET_INT(h, 25, 1);
	Hash Stats50[] =
	{
		// MP0_UNARMED_ENEMY_KILLS MP0_STKYBMB_ENEMY_KILLS MP0_GRENADE_ENEMY_KILLS MP0_RPG_ENEMY_KILLS MP0_AWD_FM_DM_WINS
		0x7b47f3c7, 0x2087c74c, 0x85cb967f, 0xb82d3c53, 0x4c2e3849, 0x88CD257A, 0x6E028B1B, 0x792B2764, 0x17855E7C, 0x34069BE5,
		// MP0_AWD_5STAR_WANTED_AVOIDANCE MP0_AWD_CARS_EXPORTED MP0_AWD_FM_GTA_RACES_WON MP0_AWD_FM_TDM_WINS MP0_AWD_RACES_WON
		0xbe3d4bc9, 0x6ad8bf16, 0x9edf3ad7, 0x1fad924e, 0x54305ac6, 0xF641F229, 0x616B3F61, 0xB22750E1, 0x1198DA99, 0x43BDA5D0,
		// MP0_AWD_FM_DM_3KILLSAMEGUY MP0_AWD_FM_DM_STOLENKILL MP0_AWD_FM_TDM_MVP MP0_AWD_FMREVENGEKILLSDM
		0x194298a4, 0x8401421f, 0xc479c331, 0xb2f3860f, 0x588CC6BC, 0x55E4F0B1, 0x2199954E, 0x52326867
	};

	for (Hash h : Stats50)
		STATS::STAT_SET_INT(h, 50, 1);
	// MP0_SNIPERRFL_ENEMY_KILLS MP0_PASS_DB_PLAYER_KILLS MP0_AWD_FM_DM_KILLSTREAK
	Hash Stats100[] = { 0x422d310, 0x2dd16b4e , 0xe41251dd, 0xFF18AD04, 0x5F639FB2, 0x2E9EECA9 };

	for (Hash h : Stats100)
		STATS::STAT_SET_INT(h, 100, 1);
	STATS::STAT_SET_INT(0x25ed089e, 255, 1); // MP0_AWD_FMDRIVEWITHOUTCRASH
	STATS::STAT_SET_INT(0x5EAA0099, 255, 1); // MP1_AWD_FMDRIVEWITHOUTCRASH

	Hash Stats500[] =
	{
		// MP0_PLAYER_HEADSHOTS MP0_PISTOL_ENEMY_KILLS MP0_SAWNOFF_ENEMY_KILLS MP0_MICROSMG_ENEMY_KILLS MP0_ASLTRIFLE_ENEMY_KILLS
		0xee25f949, 0x2216f7ae, 0x1b17a92, 0xb1c7ed0b, 0xaa58ca9d, 0x3363CBA7, 0x51931124, 0x2BE59E29, 0x3CE45119, 0xACCE32B0,
		// MP0_MG_ENEMY_KILLS MP0_AWD_VEHICLES_JACKEDR MP0_CARS_EXPLODED MP0_AWD_FM_DM_TOTALKILLS
		0x2dc218c3, 0x8e3ef0b7, 0xa255fada, 0xfac3eb18, 0x5356F2FB, 0x1D53D003, 0xBB7CDDD3, 0x76DA8DDE
	};

	for (Hash h : Stats500)
		STATS::STAT_SET_INT(h, 500, 1);
	STATS::STAT_SET_INT(0x7bd82f11, 1000, 1); // MP0_KILLS_PLAYERS
	STATS::STAT_SET_INT(0xF21F4859, 1000, 1); // MP1_KILLS_PLAYERS

	STATS::STAT_SET_FLOAT(0xb14148de, 1000, 1); // MP0_LONGEST_WHEELIE_DIST
	STATS::STAT_SET_FLOAT(0x361609BC, 1000, 1); // MP1_LONGEST_WHEELIE_DIST
	STATS::STAT_SET_INT(0x69a50e0d, 1000, 1); // MP0_CHAR_WANTED_LEVEL_TIME5STAR
	STATS::STAT_SET_INT(0x5873796D, 1000, 1); // MP0_CHAR_WANTED_LEVEL_TIME5STAR

	ScriptEventLog("~g~Achievements Unlocked ...");
}
void Features::UnlockHairstyles()
{

	// MP0_CLTHS_AVAILABLE_HAIR MP0_CLTHS_AVAILABLE_HAIR_1 MP0_CLTHS_AVAILABLE_HAIR_2 MP0_CLTHS_AVAILABLE_HAIR_3 MP0_CLTHS_AVAILABLE_HAIR_4 MP0_CLTHS_AVAILABLE_HAIR_5 MP0_CLTHS_AVAILABLE_HAIR_6 MP0_CLTHS_AVAILABLE_HAIR_7
	Hash HairStyles[] = { 0x3cc6316a, 0x50763097 ,0x67ad5f05 ,0x2d1769da, 0x4269947e, 0x2c646868, 0x42e09560, 0xa07a3af, 0x2A9FD8CE, 0x485A4609, 0x569FE294, 0xD6F4633B, 0xAC7E0E4F, 0xF94D47F, 0x1DC670E2, 0x81DA390C };
	for (Hash h : HairStyles)
		STATS::STAT_SET_INT(h, -1, 1);
	ScriptEventLog("~g~Hairstyles Unlocked...");
}
void Features::UnlockWeapons()
{

	// Weapons
	Hash StatsMinusOne[] =
	{
		// MP0_ADMIN_WEAPON_GV_BS_1 MP0_ADMIN_WEAPON_GV_BS_2 MP0_ADMIN_WEAPON_GV_BS_3 MP0_BOTTLE_IN_POSSESSION MP0_CHAR_FM_WEAP_UNLOCKED
		0x6b779763, 0x2fcea012, 0x4608cc86, 0xe0682331, 0xc0362f66, 0x2AC777EC, 0x1894D387, 0x1261471C, 0x9099E601, 0x811FAD39,
		// MP0_CHAR_FM_WEAP_UNLOCKED2 MP0_CHAR_WEAP_FM_PURCHASE MP0_CHAR_WEAP_FM_PURCHASE2 MP0_CHAR_FM_WEAP_ADDON_1_UNLCK MP0_CHAR_FM_WEAP_ADDON_2_UNLCK
		0xddff5128, 0x1b739cce, 0xf4b34427, 0xb0ffbb50, 0x2002f91, 0xE1551844, 0x25F16D26, 0x3211E42, 0x2A79D08A, 0xA9EA99F2,
		// MP0_CHAR_FM_WEAP_ADDON_3_UNLCK MP0_CHAR_FM_WEAP_ADDON_4_UNLCK MP0_CHAR_FM_WEAP_ADDON_5_UNLCK MP0_WEAP_FM_ADDON_PURCH MP0_WEAP_FM_ADDON_PURCH2
		0x77238ee3, 0x8BB0F098, 0x5D5099E7, 0xc0e8c793, 0xa06b70a7, 0x66310122, 0x77c2416b, 0xEC16309B, 0xE1EA41EC, 0x97DEB095,
		// MP0_WEAP_FM_ADDON_PURCH3 MP0_WEAP_FM_ADDON_PURCH4 MP0_WEAP_FM_ADDON_PURCH5  
		0xdb9d091b, 0xe97424c9, 0xbf3e505e, 0x3BA605AD, 0x4FCECF44, 0xBBF89BB8, 0xD2F7A23A, 0xB2F2F868, 0x3588ED7D, 0x56D18796, 0xA98D53F2, 0x1ED43E86, 0x2CC3DA65
	};
	for (Hash h : StatsMinusOne)
		STATS::STAT_SET_INT(h, -1, 1);
	//skins
	Hash Skins[] =
	{
		0x9FAB8BE1, 0x22F04348, 0xA0094888, 0x93FE1A03, 0x3CE45119,
		0xE076B62, 0xE31E5E37, 0xACCE32B0, 0x68DC8501, 0xE00B3050,
		0x5356F2FB, 0x75836942, 0x555D99A8, 0x97020ED3, 0x2BE59E29,
		0xDD2AB0F1, 0xB7D02DAF, 0xFF18AD04, 0xB51962A0, 0xABA404EB,
		0x17855E7C, 0x5FAC9C28, 0x792B2764, 0xA68AA848, 0x6E028B1B,
		0x9FAB8BE1,

		0x9ce23b8d, 0x34551d31, 0x72c8b289, 0xb3b0246b, 0xb1c7ed0b,
		0x7a42f6b3, 0x356623f1, 0xaa58ca9d, 0x5a9b4cdf, 0xab0ec253,
		0x2dc218c3, 0x9163995c, 0x3fe1312b, 0x1e6148ff, 0x1b17a92,
		0xf0a2b61a, 0x4d474708, 0x422d310, 0x1e6d5243, 0x8ac8e746,
		0xb82d3c53, 0x56baf664, 0x85cb967f, 0x4b31cd19, 0x2087c74c,
		0x9ce23b8d,
	};
	for (Hash h : Skins)
		STATS::STAT_SET_INT(h, 600, 1);
	ScriptEventLog("~g~Weapons Unlocked...");
}
void Features::UnlockClothes()
{

	Hash Clothes[] =
	{
		// MP0_CLTHS_AVAILABLE_HAIR MP0_CLTHS_AVAILABLE_HAIR_1 MP0_CLTHS_AVAILABLE_HAIR_2 MP0_CLTHS_AVAILABLE_HAIR_3 MP0_CLTHS_AVAILABLE_HAIR_4
		//0x3cc6316a, 0x50763097, 0x67ad5f05, 0x2d1769da, 0x4269947e,
		// MP0_CLTHS_AVAILABLE_HAIR_5 MP0_CLTHS_AVAILABLE_HAIR_6 MP0_CLTHS_AVAILABLE_HAIR_7
		//0x2c646868, 0x42e09560, 0xa07a3af,
		// MP0_CLTHS_AVAILABLE_JBIB MP0_CLTHS_AVAILABLE_JBIB_1 MP0_CLTHS_AVAILABLE_JBIB_2 MP0_CLTHS_AVAILABLE_JBIB_3 MP0_CLTHS_AVAILABLE_JBIB_4
		0x106936D7, 0x69EE4187, 0xea3729c5, 0x8c5f29f1, 0x65915c56, 0x67d160d6, 0xd143b3d5, 0x32D0534C, 0x676DBC86, 0xEA68AF9,
		// MP0_CLTHS_AVAILABLE_JBIB_5 MP0_CLTHS_AVAILABLE_JBIB_6 MP0_CLTHS_AVAILABLE_JBIB_7
		0xe38ad863, 0xb0e672ff, 0xc027119c, 0x4450F64D, 0x28A2BEED, 0x16C71B36,
		// MP0_CLTHS_AVAILABLE_LEGS MP0_CLTHS_AVAILABLE_LEGS_1 MP0_CLTHS_AVAILABLE_LEGS_2 MP0_CLTHS_AVAILABLE_LEGS_3 MP0_CLTHS_AVAILABLE_LEGS_4
		0xb8b3e0c6, 0xd1ebfd1,  0xc3aeacfa, 0xd7c408c,  0xe81375c3, 0xA17820E7, 0x942B0F3C, 0x2536B8B, 0xFC27DF34, 0xEA593B97,
		// MP0_CLTHS_AVAILABLE_LEGS_5 MP0_CLTHS_AVAILABLE_LEGS_6 MP0_CLTHS_AVAILABLE_LEGS_7
		0xb1730883, 0xce014193, 0xdf45e41c, 0xD7B3164B, 0x45B8725C, 0x355AD1A1,
		// MP0_CLTHS_AVAILABLE_FEET MP0_CLTHS_AVAILABLE_FEET_1 MP0_CLTHS_AVAILABLE_FEET_2 MP0_CLTHS_AVAILABLE_FEET_3 MP0_CLTHS_AVAILABLE_FEET_4
		0x97573104, 0x93ed984b, 0x623c34e5, 0x7369d740, 0x1cb129e0, 0xF48915A2, 0x5067864E, 0x5E3A21F3, 0x7BCC5D17, 0x8985F88A,
		// MP0_CLTHS_AVAILABLE_FEET_5 MP0_CLTHS_AVAILABLE_FEET_6 MP0_CLTHS_AVAILABLE_FEET_7
		0x2ce3ca45, 0xfb1866ab, 0x9a003be, 0x177C1478, 0x2D023F84, 0x3FB0E4E5,
		// MP0_CLTHS_AVAILABLE_BERD MP0_CLTHS_AVAILABLE_BERD_1 MP0_CLTHS_AVAILABLE_BERD_2 MP0_CLTHS_AVAILABLE_BERD_3 MP0_CLTHS_AVAILABLE_BERD_4
		0x14b08e07, 0x6f8f492d, 0x21a72d5e, 0x74f2d3f8, 0x269db74f, 0x72F2DA40, 0xE0B6E4BD, 0xCE604010, 0xCE1A3F84, 0xBC0C9B69,
		// MP0_CLTHS_AVAILABLE_BERD_5 MP0_CLTHS_AVAILABLE_BERD_6 MP0_CLTHS_AVAILABLE_BERD_7
		0x4f5708c1, 0x8133ec7a, 0xca99ff41, 0xE989F65B, 0xD8F75536, 0x8F4F41DF,
		// MP0_CLTHS_AVAILABLE_PROPS MP0_CLTHS_AVAILABLE_PROPS_1 MP0_CLTHS_AVAILABLE_PROPS_2 MP0_CLTHS_AVAILABLE_PROPS_3 MP0_CLTHS_AVAILABLE_PROPS_4
		0xb051c305, 0x7d5c4692, 0x7555b685, 0x62da918f, 0xd8217c1b, 0xC6EF3846, 0xB4FC36E4, 0xA641196E, 0xD967FFBB, 0xBAA5C237,
		// MP0_CLTHS_AVAILABLE_PROPS_5 MP0_CLTHS_AVAILABLE_PROPS_6 MP0_CLTHS_AVAILABLE_PROPS_7 MP0_CLTHS_AVAILABLE_PROPS_8 MP0_CLTHS_AVAILABLE_PROPS_9
		0xc665d8a4, 0xb6e439a1, 0xa431143b, 0xda520080, 0x9ca5f70, 0x59A48036, 0x8F1FEB2C, 0x7E7A49E1, 0xAF9B2C26, 0x22ED12C8,
		// MP0_CLTHS_AVAILABLE_PROPS_10 MP0_CLTHS_AVAILABLE_OUTFIT MP0_CLTHS_ACQUIRED_HAIR MP0_CLTHS_ACQUIRED_HAIR_1 MP0_CLTHS_ACQUIRED_HAIR_2
		0x4c7f28e9, 0xd4b41ccb, 0xa01511e1, 0x2415af29, 0x12630bc4, 0x5985C64E, 0x39BD13C2, 0xDD89D4C6, 0xE012DCE9, 0xCAECB29D,
		// MP0_CLTHS_ACQUIRED_HAIR_3 MP0_CLTHS_ACQUIRED_HAIR_4 MP0_CLTHS_ACQUIRED_HAIR_5 MP0_CLTHS_ACQUIRED_HAIR_6 MP0_CLTHS_ACQUIRED_HAIR_7
		0x41e4eabf, 0x2f96c623, 0x2b48bd87, 0x1922193a, 0x888a7809, 0xBD9917F6, 0x7340035D, 0xA58EE7FA, 0x5FBB5C54, 0x81C7A06C,
		// MP0_CLTHS_ACQUIRED_JBIB MP0_CLTHS_ACQUIRED_JBIB_1 MP0_CLTHS_ACQUIRED_JBIB_2 MP0_CLTHS_ACQUIRED_JBIB_3 MP0_CLTHS_ACQUIRED_JBIB_4
		0xaea92fe3, 0xa05ef149, 0x93bfd80b, 0x7a90a5ad, 0x69730372, 0x262E94CA, 0xA89BC9DF, 0x8EDA965D, 0xFBCBF03E, 0xF205DCB2,
		// MP0_CLTHS_ACQUIRED_JBIB_5 MP0_CLTHS_ACQUIRED_JBIB_6 MP0_CLTHS_ACQUIRED_JBIB_7
		0x5e0eeca6, 0x281f80d4, 0x1d856ba0, 0x6790C7CA, 0x5553234F, 0x4B2A0EFD,
		// MP0_CLTHS_ACQUIRED_LEGS MP0_CLTHS_ACQUIRED_LEGS_1 MP0_CLTHS_ACQUIRED_LEGS_2 MP0_CLTHS_ACQUIRED_LEGS_3 MP0_CLTHS_ACQUIRED_LEGS_4
		0x66e4ca67, 0x1b3dca99, 0x598d4737, 0x7c223a2,  0x3ce78dec, 0x7AD6ED44, 0x3180E8E0, 0x23384C4F, 0xDFE21DB, 0xFFA88530,
		// MP0_CLTHS_ACQUIRED_LEGS_5 MP0_CLTHS_ACQUIRED_LEGS_6 MP0_CLTHS_ACQUIRED_LEGS_7
		0x6b266a69, 0xa01cd459, 0x4df12fff, 0xFA5B7A96, 0xED0CDFF9, 0xD6C6B36D,
		// MP0_CLTHS_ACQUIRED_FEET MP0_CLTHS_ACQUIRED_FEET_1 MP0_CLTHS_ACQUIRED_FEET_2 MP0_CLTHS_ACQUIRED_FEET_3 MP0_CLTHS_ACQUIRED_FEET_4
		0x12b66dab, 0xcfd67d8b, 0x7964d0a9, 0xaeaf3b3d, 0x56a80b30, 0xBD702716, 0x2EEE3A4B, 0x212A9EC4, 0x824A6102, 0xAED8BA1E,
		// MP0_CLTHS_ACQUIRED_FEET_5 MP0_CLTHS_ACQUIRED_FEET_6 MP0_CLTHS_ACQUIRED_FEET_7
		0x88eaefb5, 0x327342bf, 0x63b5254a, 0x661BA8A5, 0x58760D5A, 0xCB61F32C,
		// MP0_CLTHS_ACQUIRED_BERD MP0_CLTHS_ACQUIRED_BERD_1 MP0_CLTHS_ACQUIRED_BERD_2 MP0_CLTHS_ACQUIRED_BERD_3 MP0_CLTHS_ACQUIRED_BERD_4
		0x2de14803, 0x19299a7d, 0x2b3e3ea6, 0x7574d312, 0x87e277ed, 0xD7C1EC04, 0x1039C4E0, 0x4A183894, 0x3D529F09, 0x6727F2B3,
		// MP0_CLTHS_ACQUIRED_BERD_5 MP0_CLTHS_ACQUIRED_BERD_6 MP0_CLTHS_ACQUIRED_BERD_7
		0x74a9d180, 0x86d375d3, 0x50ec0a05, 0x58ED563E, 0xD711D285, 0x88E6B630,
		// MP0_CLTHS_ACQUIRED_PROPS MP0_CLTHS_ACQUIRED_PROPS_1 MP0_CLTHS_ACQUIRED_PROPS_2 MP0_CLTHS_ACQUIRED_PROPS_3 MP0_CLTHS_ACQUIRED_PROPS_4
		0xd846c640, 0x18ea3634, 0x3460aec,  0xa1d5c80d, 0x5573af4a, 0xEF73F981, 0xF889C25C, 0xEB4F27E7, 0xD820818A, 0xC971E42D,
		// MP0_CLTHS_ACQUIRED_PROPS_5 MP0_CLTHS_ACQUIRED_PROPS_6 MP0_CLTHS_ACQUIRED_PROPS_7 MP0_CLTHS_ACQUIRED_PROPS_8 MP0_CLTHS_ACQUIRED_PROPS_9
		0x3f3182c6, 0x6ad05a03, 0xeaecda3a, 0x9d25bead, 0x87779351, 0xC47CDA43, 0xB6C33ED0, 0xA35917FC, 0x7C96CA7C, 0x6BC528D9,
		// MP0_CLTHS_ACQUIRED_PROPS_10 MP0_CLTHS_ACQUIRED_OUTFIT MP0_CLTHS_AVAILABLE_TORSO MP0_CLTHS_AVAILABLE_SPECIAL MP0_CLTHS_AVAILABLE_SPECIAL_1
		0x466c7ee5, 0xe667df2c, 0x8eb5a109, 0x135b7256, 0x17e66c11, 0x8987AF23, 0x558AD3B, 0x594926A5, 0xF72A91D0, 0x1AEE2BA3,
		// MP0_CLTHS_AVAILABLE_SPECIAL_2 MP0_CLTHS_AVAILABLE_SPECIAL_3 MP0_CLTHS_AVAILABLE_SPECIAL_4 MP0_CLTHS_AVAILABLE_SPECIAL_5 MP0_CLTHS_AVAILABLE_SPECIAL_6
		0x5e5b78fa, 0x2f9c9b7d, 0xeb7a1335, 0x11f3e7f,  0x753cae8, 0x6895C6F5, 0xE5D2416C, 0xD3A01D08, 0xE1E6B995, 0x2F8E54E3,
		// MP0_CLTHS_AVAILABLE_SPECIAL_7 MP0_CLTHS_AVAILABLE_DECL MP0_CLTHS_AVAILABLE_TEETH MP0_CLTHS_AVAILABLE_TEETH_1 MP0_CLTHS_AVAILABLE_TEETH_2
		0x1c91f564, 0x9c7866c7, 0xba50aedd, 0x2e99d7e,  0x112339f1, 0xACDA4F79, 0xA45F8FA5, 0x50EE4BB3, 0xA38FAC3D, 0x91C108A0,
		// MP0_CLTHS_ACQUIRED_TORSO MP0_CLTHS_ACQUIRED_SPECIAL MP0_CLTHS_ACQUIRED_SPECIAL_1 MP0_CLTHS_ACQUIRED_SPECIAL_2 MP0_CLTHS_ACQUIRED_SPECIAL_3
		0x85648a0a, 0xd1c336af, 0x5a1bdf57, 0x70020b23, 0x7cc0249f, 0xC7E1C824, 0x93CD00B9, 0xE1034060, 0x60FEC059, 0x733D64D6,
		// MP0_CLTHS_ACQUIRED_SPECIAL_4 MP0_CLTHS_ACQUIRED_SPECIAL_5 MP0_CLTHS_ACQUIRED_SPECIAL_6 MP0_CLTHS_ACQUIRED_SPECIAL_7 MP0_CLTHS_ACQUIRED_SPECIAL2
		0x42733006, 0xa132ed84, 0xd96fddfd, 0xe5b1f681, 0x8803887c, 0xA08CBF74, 0xAAD1D3FE, 0x2A4D52F7, 0x3BD5F608, 0x5E745104,
		// MP0_CLTHS_ACQUIRED_SPECIAL2_1 MP0_CLTHS_ACQUIRED_DECL MP0_CLTHS_ACQUIRED_TEETH MP0_CLTHS_ACQUIRED_TEETH_1 MP0_CLTHS_ACQUIRED_TEETH_2
		0x7e9b5630, 0x9e36043,  0xa1425b8,  0x91050cea, 0x68fc3cd5, 0x662CE27A, 0xAFF1B575, 0x9919F993, 0xDEC71135, 0xF48A3CBB,
		// MP0_DLC_APPAREL_ACQUIRED_0 MP0_DLC_APPAREL_ACQUIRED_1 MP0_DLC_APPAREL_ACQUIRED_2 MP0_DLC_APPAREL_ACQUIRED_3 MP0_DLC_APPAREL_ACQUIRED_4
		0x58087574, 0x4dffe16f, 0x402645bc, 0xf0942689, 0xea6a1a35, 0x94B71349, 0x9F8628E7, 0xAE0945ED, 0xBBCAE170, 0xDDF4A5C3,
		// MP0_DLC_APPAREL_ACQUIRED_5 MP0_DLC_APPAREL_ACQUIRED_6 MP0_DLC_APPAREL_ACQUIRED_7 MP0_DLC_APPAREL_ACQUIRED_8 MP0_DLC_APPAREL_ACQUIRED_9
		0x1b87fc70, 0x6e4d32a,  0xb80eb57f, 0xd156e80f, 0xa00e858b, 0xEC6E42B6, 0x9A319E42, 0xA9003BDF, 0x26AE3735, 0x31554C83,
		// MP0_DLC_APPAREL_ACQUIRED_10 MP0_DLC_APPAREL_ACQUIRED_11 MP0_DLC_APPAREL_ACQUIRED_12 MP0_DLC_APPAREL_ACQUIRED_13 MP0_DLC_APPAREL_ACQUIRED_14
		0x786ce981, 0x5e25b4f3, 0x851d82e2, 0xfa586d56, 0xb14a5b3b, 0x5E1EBA6B, 0x31BD61A9, 0x7BE775FC, 0x6C21D671, 0x966C2AF5,
		// MP0_DLC_APPAREL_ACQUIRED_15 MP0_DLC_APPAREL_ACQUIRED_16 MP0_DLC_APPAREL_ACQUIRED_17 MP0_DLC_APPAREL_ACQUIRED_18 MP0_DLC_APPAREL_ACQUIRED_19
		0x978b27bd, 0x41c27c29, 0x2fffd8a4, 0xde5e3562, 0xcca491ef, 0x85AD8978, 0xB2B6E38A, 0xA3F54607, 0x5D32B883, 0x50781F0E,
		// MP0_DLC_APPAREL_ACQUIRED_21 MP0_DLC_APPAREL_ACQUIRED_22 MP0_DLC_APPAREL_ACQUIRED_23 MP0_DLC_APPAREL_ACQUIRED_24 MP0_DLC_APPAREL_ACQUIRED_24
		0x6bc7cf17, 0xc7a886d7, 0xd543220c, 0x1d1931b7, 0x1d1931b7, 0xBE78FC56, 0xC8F61150, 0xC1D1831B, 0xB7606E39, 0xED675A46,
		// MP0_DLC_APPAREL_ACQUIRED_25 MP0_DLC_APPAREL_ACQUIRED_26 MP0_DLC_APPAREL_ACQUIRED_27 MP0_DLC_APPAREL_ACQUIRED_28 MP0_DLC_APPAREL_ACQUIRED_29
		0x32be5d01, 0xd594a2b7, 0xeb77ce7d, 0x3304dd96, 0x40c67919, 0xD33D25F2, 0x7ECB7D10, 0x6D3CD9F3, 0x9A6F3457, 0x889F90B8,
		// MP0_DLC_APPAREL_ACQUIRED_30 MP0_DLC_APPAREL_ACQUIRED_31 MP0_DLC_APPAREL_ACQUIRED_32 MP0_DLC_APPAREL_ACQUIRED_33 MP0_DLC_APPAREL_ACQUIRED_34
		0x21993997, 0x76cee405, 0x3d23f0ac, 0x32addbc0, 0xe09e37a2, 0xE7D8D00D, 0xDA163488, 0xCB5D9717, 0xB5C26BE1, 0x11CC23F7,
		// MP0_DLC_APPAREL_ACQUIRED_35 MP0_DLC_APPAREL_ACQUIRED_36 MP0_DLC_APPAREL_ACQUIRED_37 MP0_DLC_APPAREL_ACQUIRED_38 MP0_DLC_APPAREL_ACQUIRED_39
		0xce3492cf, 0x94611f25, 0x2c57bf0,  0x98902783, 0x865d831e, 0x30D867A, 0xED4D5AFA, 0xDE8FBD7F, 0x59E5B429, 0x442C88B7,
		// MP0_DLC_APPAREL_ACQUIRED_40 MP0_ADMIN_CLOTHES_GV_BS_1 MP0_ADMIN_CLOTHES_GV_BS_2 MP0_ADMIN_CLOTHES_GV_BS_3 MP0_ADMIN_CLOTHES_GV_BS_4
		0xd3c59cd1, 0x62e2d64,  0xbc5d19bb, 0xaaedf6dd, 0xd130c362, 0x64AC5C36, 0xF8AA28B5, 0x5EC2F4E9, 0x4EC854F4, 0x3C77B053,
		// MP0_ADMIN_CLOTHES_GV_BS_5 MP0_ADMIN_CLOTHES_GV_BS_6 MP0_ADMIN_CLOTHES_GV_BS_7 MP0_ADMIN_CLOTHES_GV_BS_8 MP0_ADMIN_CLOTHES_GV_BS_9
		0xcf3cbf7a, 0x65536ba9, 0x4f824007, 0x85d0aca3, 0x746309c8, 0x32E59D2F, 0x979E669F, 0x8C104F83, 0x7A00AB64, 0xDEA074A6,
		// MP0_ADMIN_CLOTHES_GV_BS_10 MP0_ADMIN_CLOTHES_GV_BS_11 MP0_ADMIN_CLOTHES_GV_BS_12 MP0_ADMIN_CLOTHES_GV_BS_13
		0xcb76a780, 0xe6a9dde6, 0xefe2f058, 0x1f90cd, 0xE5B0D20F, 0xFC21FEF1, 0xD2D02C32, 0xE267CB61
	};
	for (Hash h : Clothes)
		STATS::STAT_SET_INT(h, -1, 1);

	//tshirts
	STATS::STAT_SET_BOOL(0x9cf3d019, 1, 1); // MP0_AWD_FINISH_HEIST_NO_DAMAGE
	STATS::STAT_SET_BOOL(0x59D644B9, 1, 1); // MP1_AWD_FINISH_HEIST_NO_DAMAGE

	STATS::STAT_SET_BOOL(0x45b6712, 1, 1); // MP0_AWD_STORE_20_CAR_IN_GARAGES
	STATS::STAT_SET_BOOL(0xA5F06324, 1, 1); // MP1_AWD_STORE_20_CAR_IN_GARAGES

	STATS::STAT_SET_INT(0x2ae837e4, 1, 1); // MP0_AWD_FMPICKUPDLCCRATE1ST also in trophies
	STATS::STAT_SET_INT(0x3804231B, 1, 1); // MP1_AWD_FMPICKUPDLCCRATE1ST also in trophies

	STATS::STAT_SET_INT(0x833d3192, 10, 1); // MP0_AWD_FMHORDWAVESSURVIVE also in trophies
	STATS::STAT_SET_INT(0x18F27D05, 10, 1); // MP1_AWD_FMHORDWAVESSURVIVE also in trophies

											// MP0_AWD_WIN_CAPTURE_DONT_DYING MP0_AWD_DO_HEIST_AS_MEMBER MP0_AWD_WIN_GOLD_MEDAL_HEISTS MP0_AWD_KILL_TEAM_YOURSELF_LTS MP0_AWD_DO_HEIST_AS_THE_LEADER
	Hash Stats25[] = { 0x68d14c4e, 0x470055dc, 0x9f9ff03c, 0x4930d051, 0xc32a1dd9, 0x7B245DB0, 0xFFCB5243, 0x3D6A96C, 0x5C7450F8, 0xC13E46BC };
	for (Hash h : Stats25)
		STATS::STAT_SET_INT(h, 25, 1);

	STATS::STAT_SET_INT(0x30418014, 100, 1); // MP0_AWD_PICKUP_CAP_PACKAGES
	STATS::STAT_SET_INT(0x87B6D2D, 100, 1); // MP1_AWD_PICKUP_CAP_PACKAGES

	STATS::STAT_SET_INT(0xe2a9b0c4, 100, 1); // MP0_AWD_KILL_PSYCHOPATHS
	STATS::STAT_SET_INT(0xE5E29EEA, 100, 1); // MP1_AWD_KILL_PSYCHOPATHS

	ScriptEventLog("~g~Clothes Unlocked...");
}

bool Features::SnowBool = false;
bool Features::XmasShitBool = false;
bool Features::HalloweenShit = false;
bool Features::ValentineClothingBool = false;
bool Features::ValentineVehicleBool = false;
bool Features::ValentineGunBool = false;
bool Features::ValentineMaskBool = false;
bool Features::ValentineHairBool = false;
bool Features::HaloweenWeaponsBool = false;
bool Features::HeistBoxvilleBool = false;
bool Features::HeistEnduroBool = false;
bool Features::HeistHydraBool = false;
bool Features::HeistInsurgentBool = false;
bool Features::HeistInsurgent2Bool = false;
bool Features::HeistLectroBool = false;
bool Features::HeistMuleBool = false;
bool Features::HeistSavageBool = false;
bool Features::HeistTechnicalBool = false;
bool Features::HeistValkyrieBool = false;
bool Features::HeistPrisonBool = false;
bool Features::SnowballBool = false;
bool Features::ChristmasContentBool = false;
bool Features::ChristmasClothingBool = false;
bool Features::ChristmasMaskBool = false;
bool Features::ChristmasVehicleBool = false;

bool Features::IndpendenceDayBool = false;
bool Features::WesternSoverignBool = false;
bool Features::MonsterTruckBool = false;
bool Features::BeerHat1Bool = false;
bool Features::BeerHat2Bool = false;
bool Features::BeerHat3Bool = false;
bool Features::BeerHat4Bool = false;
bool Features::BeerHat5Bool = false;
bool Features::BeerHat6Bool = false;

void Features::BeerHats() {
	globalHandle(0x40001 + 7719).As<bool>() = 1;
	globalHandle(0x40001 + 7720).As<bool>() = 1;
	globalHandle(0x40001 + 7721).As<bool>() = 1;
	globalHandle(0x40001 + 7722).As<bool>() = 1;
	globalHandle(0x40001 + 7723).As<bool>() = 1;
	globalHandle(0x40001 + 7724).As<bool>() = 1;
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_31"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_41"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_42"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_43"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_44"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_45"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_46"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_47"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_48"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_49"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_50"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_51"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_52"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_53"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_54"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_55"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_56"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);//IDK
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_13"), -1, 1);//IDK
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_RM_BS_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_RM_BS_11"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_RM_BS_12"), -1, 1);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
}

string Features::Token = "761251633824137219";

std::string Features::ConsoleLogger;

bool Features::Nametag = false;
void Features::NameTagESP()
{
	Player playerPed = PLAYER::PLAYER_PED_ID();
	for (int i = 0; i < 32; i++)
	{
		Player playerHandle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		Vector3 handleCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerHandle, 0, 0, 0);
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
		char* Name = PLAYER::GET_PLAYER_NAME(PLAYER::INT_TO_PLAYERINDEX(i));

		if (ENTITY::DOES_ENTITY_EXIST(playerHandle))
		{
			float x1;
			float y1;

			BOOL screenCoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(handleCoords.x, handleCoords.y, handleCoords.z, &x1, &y1);

			std::string playerName = PLAYER::GET_PLAYER_NAME(PLAYER::INT_TO_PLAYERINDEX(i));

			std::string nameSetupRed = "~HUD_COLOUR_RED~" + playerName;
			std::string nameSetupGreen = "~HUD_COLOUR_BLUE~" + playerName;

			char* playerInfoRed = new char[nameSetupRed.length() + 1];
			char* playerInfoGreen = new char[nameSetupGreen.length() + 1];

			std::strcpy(playerInfoRed, nameSetupRed.c_str());
			std::strcpy(playerInfoGreen, nameSetupGreen.c_str());

			UI::SET_TEXT_FONT(7);
			UI::SET_TEXT_SCALE(0.0, 0.40);
			UI::SET_TEXT_COLOUR(0, 255, 0, 255);
			UI::SET_TEXT_CENTRE(0);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
			UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
			if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, playerHandle, 17))
			{
				UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(playerInfoGreen);
			}
			else
			{
				UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(playerInfoRed);
			}
			UI::END_TEXT_COMMAND_DISPLAY_TEXT(x1, y1);
			UI::SET_TEXT_OUTLINE();
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}
	}
}







bool Features::LogEvent = false;
bool Features::LogMetric = false;
bool Features::EventNotif = false;
bool Features::Hidden = false;
int Features::StealthAmount = 10000000;

void Features::TransactionError(int player)
{
	auto var0 = globalHandle(1626536 + 1 + player * 560 + 491).As<std::uint64_t>();
	auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
	DWORD64 args[8] = { TRANSACION_ERROR, player, 10000, 0, 0, var0, var1, var1 };
}

bool Features::ObjectGunBool = false;
void Features::objectgunpl()
{
		if (is_ped_shooting(PLAYER::PLAYER_PED_ID()))
		{
			Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			Vector3 Dir = RotationToDirection(Rot);
			Vector3 CPosition = CAM::GET_GAMEPLAY_CAM_COORD();
			Vector3 PlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			int random = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 2585);
			const int Obj[] = { 0x0042ea9f,
				0x00460fc5,
				0x0046397e,
				0x00633ddf,
				0x00a86f78,
				0x00b28bf8,
				0x00d2c275,
				0x00d7552a,
				0x00d7e7fa,
				0x0104614e,
				0x0105ce40,
				0x011193e0,
				0x0119735d,
				0x011d675e,
				0x0147ebe4,
				0x016e3f3d,
				0x017d003b,
				0x0185b135,
				0x01c0a3b6,
				0x01d58149,
				0x01e2fab2,
				0x0208e142,
				0x02475888,
				0x026be58c,
				0x02ac105d,
				0x0301d335,
				0x03154ddc,
				0x032019c0,
				0x0340f31f,
				0x0361f579,
				0x037153d6,
				0x038f86bf,
				0x03a41e1a,
				0x03aa904e,
				0x03c4ecdb,
				0x03cbf802,
				0x03d4f2a2,
				0x03fc0a5a,
				0x040c3a75,
				0x0426f46e,
				0x0429083b,
				0x0429e2c6,
				0x043a4b8e,
				0x045e91ee,
				0x04653780,
				0x046a474e,
				0x04891312,
				0x04917901,
				0x04a3c376,
				0x04ae6d62,
				0x04de7f33,
				0x0503e1c0,
				0x050c39c7,
				0x054258e1,
				0x055c8249,
				0x055f493b,
				0x05648b8b,
				0x05699673,
				0x05752b59,
				0x05985d75,
				0x05c617d3,
				0x05ccacf6,
				0x05ede99e,
				0x0623f9a3,
				0x06268470,
				0x063ba2ca,
				0x064a6680,
				0x0658a835,
				0x0674c35e,
				0x06833ef1,
				0x06aa3dec,
				0x06b21d02,
				0x06e51f7e,
				0x07144763,
				0x0724658f,
				0x0732d722,
				0x074a3557,
				0x074cba11,
				0x0752f68a,
				0x0757c28d,
				0x07601f29,
				0x0766f7ce,
				0x079324a2,
				0x07b9aa54,
				0x07ccb5e1,
				0x07ce549d,
				0x07d35238,
				0x07e253d2,
				0x07f8097e,
				0x0808cdb3,
				0x080b7b49,
				0x081ece1f,
				0x08250b39,
				0x08333c3c,
				0x084592ed,
				0x0869b691,
				0x086ec175,
				0x087f62f9,
				0x08f8085e,
				0x091cd3b2,
				0x09472c02,
				0x09816485,
				0x0999cf94,
				0x09a1dd77,
				0x09dda7e0,
				0x09fcbaed,
				0x0a22cea2,
				0x0a2ce7d2,
				0x0a5654f6,
				0x0a7a4a10,
				0x0ab0265f,
				0x0ad31c42,
				0x0af11755,
				0x0af617e0,
				0x0b24b944,
				0x0b26bab3,
				0x0b3c6b5c,
				0x0b4e2dc0,
				0x0b5daaec,
				0x0b8e8976,
				0x0bb143a8,
				0x0bfbdc9d,
				0x0c0522a1,
				0x0c0ba54b,
				0x0c452454,
				0x0c4f7e8e,
				0x0c59a0e3,
				0x0c72d355,
				0x0c853ce3,
				0x0c96ddeb,
				0x0c9b0a8a,
				0x0c9fcd09,
				0x0ca0e7c2,
				0x0cc73e90,
				0x0cf39a5f,
				0x0d06c604,
				0x0d8809a3,
				0x0dd52f22,
				0x0dd75614,
				0x0de5faae,
				0x0e1d31e7,
				0x0e336128,
				0x0e465c10,
				0x0e5fec54,
				0x0e805916,
				0x0eb31c78,
				0x0ec688eb,
				0x0ed57ec6,
				0x0ef82139,
				0x0f0048b0,
				0x0f287397,
				0x0f29dea9,
				0x0f4345e9,
				0x0f87eef6,
				0x0f89432b,
				0x0fa24c32,
				0x0fa4d707,
				0x0fbccda3,
				0x0fd6964f,
				0x0fe7673c,
				0x0ff3fcb5,
				0x0ff883c5,
				0x101ce8f5,
				0x103986f0,
				0x103c434e,
				0x104484c6,
				0x1055925d,
				0x10856e55,
				0x10869547,
				0x10a8dbbb,
				0x10ab8d56,
				0x10cb9eb4,
				0x110ac104,
				0x11266252,
				0x113fd533,
				0x11528878,
				0x1152f032,
				0x115d9ea5,
				0x118b6630,
				0x1207ca57,
				0x124608a4,
				0x1255fdfb,
				0x126ca09d,
				0x126f08f2,
				0x127150b8,
				0x12969ba3,
				0x12aebf2c,
				0x12bdebf2,
				0x12eec7a9,
				0x130d959f,
				0x13351f02,
				0x13357d9b,
				0x133d60a9,
				0x139d311f,
				0x13a5b821,
				0x13a6747a,
				0x13cebd36,
				0x13dd1f83,
				0x13edbd11,
				0x1405669b,
				0x140f36da,
				0x1428d590,
				0x1448713a,
				0x14697bb3,
				0x148b20a6,
				0x149e2243,
				0x14a30c7b,
				0x14e3d6eb,
				0x14f6bd6d,
				0x14ff3f1d,
				0x151c77af,
				0x15242f41,
				0x15582ecd,
				0x158c9081,
				0x158ebd66,
				0x15ab6bab,
				0x15adf001,
				0x15b9011a,
				0x15f22759,
				0x15ff352f,
				0x161fb75b,
				0x1651de5c,
				0x16581c8a,
				0x1661757f,
				0x1668a50b,
				0x169fa3da,
				0x16a39a90,
				0x16a7695b,
				0x16ae5135,
				0x16b2ee75,
				0x16dbace8,
				0x16ecec56,
				0x16f93072,
				0x17236aa7,
				0x17548d8d,
				0x1762b038,
				0x17713b39,
				0x177a4261,
				0x177b60ee,
				0x17dcc339,
				0x17e65d20,
				0x180a2a8a,
				0x18156c63,
				0x1880ce91,
				0x18a2a46e,
				0x18c49531,
				0x18fcd344,
				0x192567be,
				0x1951f087,
				0x1959bdf3,
				0x1960d682,
				0x1965cf4f,
				0x19aaadc3,
				0x19c11b82,
				0x19cb150e,
				0x1a0bc25b,
				0x1a0c3d41,
				0x1a0e2225,
				0x1a37e98b,
				0x1a688b13,
				0x1a92716c,
				0x1ab39621,
				0x1ad53ecf,
				0x1ae4039a,
				0x1b0e6b19,
				0x1b180974,
				0x1b276762,
				0x1b381a32,
				0x1b509699,
				0x1b6ed610,
				0x1b7c1d1e,
				0x1b803513,
				0x1b9a2388,
				0x1bb934e9,
				0x1bccd39c,
				0x1bcd37c6,
				0x1bd48138,
				0x1c407029,
				0x1c587fa6,
				0x1c8b91d9,
				0x1cb21205,
				0x1cd55ba0,
				0x1cd6d6ac,
				0x1cebcf06,
				0x1cf2ca01,
				0x1cf9d6d2,
				0x1d64808b,
				0x1d6f7b34,
				0x1d87f925,
				0x1d8a4162,
				0x1d8c18cd,
				0x1da17dd4,
				0x1db34f2a,
				0x1dc247fa,
				0x1de9372b,
				0x1df507eb,
				0x1e04df09,
				0x1e26f85a,
				0x1e2e4a36,
				0x1e34b5c2,
				0x1e63bcb4,
				0x1e6e69dc,
				0x1e6f920c,
				0x1e75866e,
				0x1e839152,
				0x1e9e215f,
				0x1e9ea015,
				0x1ed29497,
				0x1ee9cd57,
				0x1eea1590,
				0x1ef861ce,
				0x1efb7b6c,
				0x1f550c17,
				0x1f570a54,
				0x1f5a3957,
				0x1f811ce1,
				0x1fad22fb,
				0x1fbd6146,
				0x1fca2a6a,
				0x1fcbd2f1,
				0x1fd4cce1,
				0x1fda072d,
				0x1ff3cc2e,
				0x2015b51d,
				0x204ee4b6,
				0x2052b780,
				0x205d4274,
				0x2062352d,
				0x207a3ca8,
				0x207cec12,
				0x208f25b3,
				0x20911405,
				0x2097eea6,
				0x20cffdb5,
				0x20da9342,
				0x210974d7,
				0x211a00b0,
				0x217c2330,
				0x2185065a,
				0x21c545ea,
				0x21d743c3,
				0x21df89bf,
				0x21f6f9f5,
				0x221ee0fd,
				0x222846cb,
				0x2231808b,
				0x223c581b,
				0x224e7f06,
				0x2250309f,
				0x22606b68,
				0x227580ee,
				0x22b1476e,
				0x2346c249,
				0x2347ed83,
				0x2351f1b1,
				0x237e9a78,
				0x23e3b0ba,
				0x23fbac0f,
				0x240d3e4b,
				0x2413cee0,
				0x2418bd30,
				0x24786f38,
				0x24d07e95,
				0x24deb3e1,
				0x25286eb9,
				0x2537db7a,
				0x2571cda2,
				0x2575d371,
				0x2577a7bc,
				0x257bedda,
				0x25cbf0e5,
				0x26134929,
				0x263e279e,
				0x265d5856,
				0x26b91a25,
				0x26c432e8,
				0x26cf04db,
				0x26e7fcb1,
				0x2709fcea,
				0x2716b4ca,
				0x2726cc47,
				0x27483fc0,
				0x274ba905,
				0x27a12c72,
				0x27a173a8,
				0x27bc4f61,
				0x27bc58a9,
				0x27c33a11,
				0x27c67b62,
				0x27d1811a,
				0x27d8000e,
				0x27e363f7,
				0x27e54463,
				0x27fe17fd,
				0x2829c88d,
				0x282d6851,
				0x2834c4a3,
				0x28781518,
				0x2886deab,
				0x28885c83,
				0x288dc72a,
				0x28947d6c,
				0x28b2940f,
				0x28be7556,
				0x28c8a784,
				0x28cdf74c,
				0x28cf5961,
				0x28e797a3,
				0x28ead0e7,
				0x2904e007,
				0x2927a8c3,
				0x292f4238,
				0x295b365e,
				0x296a6654,
				0x2990c112,
				0x29970fab,
				0x29ca5f04,
				0x29cb0f3c,
				0x29db5e17,
				0x29e362ff,
				0x29f3f9d1,
				0x2a140363,
				0x2a41a51e,
				0x2a461cf4,
				0x2a48dbc9,
				0x2a6ebfef,
				0x2a77f8b0,
				0x2aa9be6a,
				0x2ab637df,
				0x2acf481a,
				0x2ae13dfa,
				0x2af4e9fb,
				0x2b1fc7b2,
				0x2b2d8c1d,
				0x2b3485db,
				0x2b3a93e1,
				0x2b3ad141,
				0x2b5bd8ba,
				0x2b8c0657,
				0x2b96d271,
				0x2b9c94da,
				0x2baf34d6,
				0x2bb25046,
				0x2bb8f7e0,
				0x2bc3f8b8,
				0x2bd57a5a,
				0x2be688e0,
				0x2c0683c7,
				0x2c0b2ffe,
				0x2c21abf9,
				0x2c2f9065,
				0x2c57eff1,
				0x2c7c3016,
				0x2c98b0ed,
				0x2cbe2fbe,
				0x2ce2804a,
				0x2ce556c0,
				0x2cf975f5,
				0x2cfee5fd,
				0x2d17574b,
				0x2d291c86,
				0x2d33a7e3,
				0x2d5af569,
				0x2d66be8f,
				0x2d72103d,
				0x2d80bd93,
				0x2d930b3b,
				0x2d96a89a,
				0x2d9a5028,
				0x2de9f1e4,
				0x2df8cf62,
				0x2e042597,
				0x2e0d79e8,
				0x2e43a2ff,
				0x2e7c9a23,
				0x2eb9fce9,
				0x2ef4cef2,
				0x2efbb698,
				0x2f3a5b38,
				0x2f84f70e,
				0x2f9b3eec,
				0x2f9f084d,
				0x2fa3ddbb,
				0x2fea25bf,
				0x30053b7a,
				0x300c41ef,
				0x30318fab,
				0x30371d34,
				0x304afda1,
				0x304dc78b,
				0x30597515,
				0x306e29b4,
				0x30b5a669,
				0x30b77f21,
				0x312f3a92,
				0x313c1fcc,
				0x3159696b,
				0x31627d68,
				0x31be5f40,
				0x31dcb7d1,
				0x31fd5263,
				0x323f3f40,
				0x3250a31d,
				0x326d3db1,
				0x3287a564,
				0x328d164d,
				0x32a956a6,
				0x32ece3bc,
				0x32ed2e9a,
				0x33158c22,
				0x332d24be,
				0x334049a3,
				0x336b391e,
				0x336fbbcf,
				0x33bee4be,
				0x33e70464,
				0x341d729b,
				0x3423f946,
				0x346968f4,
				0x346a8d93,
				0x347cd13a,
				0x347d8659,
				0x3482b62e,
				0x3489dcd8,
				0x34950018,
				0x34b41415,
				0x34c993be,
				0x34cb93ec,
				0x34d1e91a,
				0x34d5d3fd,
				0x34d7a451,
				0x34feb64d,
				0x35098d26,
				0x355241b6,
				0x357cba6d,
				0x35ae1f39,
				0x35b17206,
				0x35c9a934,
				0x35f7654e,
				0x3605424c,
				0x36393ea8,
				0x363ca3b6,
				0x366edcc0,
				0x367912e7,
				0x3680ec2f,
				0x368391cb,
				0x369d8410,
				0x36d89c82,
				0x36dac2c6,
				0x36e9ab93,
				0x36eb76de,
				0x37067ffb,
				0x370b4e30,
				0x371f753d,
				0x372987ad,
				0x374d00af,
				0x376024bc,
				0x376adae3,
				0x376c99f9,
				0x376cb307,
				0x37926aa6,
				0x37a41695,
				0x37aff890,
				0x37d80b0e,
				0x37fdc243,
				0x3852efd6,
				0x3860f7f9,
				0x3882907a,
				0x38b45feb,
				0x38c419eb,
				0x38d8d4d4,
				0x390a0159,
				0x3924b266,
				0x392d62aa,
				0x3ac1ea,
				0x393cea76,
				0x3961c88,
				0x39885bb5,
				0x399bae1e,
				0x39d0eaef,
				0x3a015e1b,
				0x3a12a4ba,
				0x3a1b896a,
				0x3a358535,
				0x3a3653b1,
				0x3a3f63bf,
				0x3a403cc9,
				0x3a6168f2,
				0x3a9245cd,
				0x3ab773db,
				0x3ad2a96e,
				0x3add57f6,
				0x3b14f8fc,
				0x3b2a8c05,
				0x3b5f7e01,
				0x3b613254,
				0x3b6561bf,
				0x3b829c8b,
				0x3bd8e67a,
				0x3be5240f,
				0x3be9850a,
				0x3bf5b2ef,
				0x3bfd37a7,
				0x3c1b83ba,
				0x3c3b89f0,
				0x3c3c6190,
				0x3c4673a4,
				0x3c4bc4e2,
				0x3c4dac35,
				0x3c662ff7,
				0x3ca58296,
				0x3cd5661d,
				0x3cef76a2,
				0x3cf34f26,
				0x3cf90808,
				0x3d0e127f,
				0x3d3ec7ae,
				0x3d41885,
				0x3d4a034f,
				0x3d724e0e,
				0x3d8b524a,
				0x3dd687f3,
				0x3df36023,
				0x3e25d399,
				0x3e2a1909,
				0x3e591630,
				0x3e611d30,
				0x3e90e8ca,
				0x3e94b9ef,
				0x3eb58c09,
				0x3ed6c49c,
				0x3ef6bb41,
				0x3efd32f2,
				0x3efd9223,
				0x3efe4664,
				0x3f2ec2b6,
				0x3f581495,
				0x3f58aa28,
				0x3f6c62cb,
				0x3f78bc5d,
				0x3fa676de,
				0x3fb16a90,
				0x3fbdad7c,
				0x3fca4571,
				0x3fd0afb6,
				0x3fd7c4d3,
				0x3fe27bae,
				0x401bad75,
				0x4056cc7d,
				0x4057c671,
				0x40695416,
				0x4087e762,
				0x408a2f40,
				0x40be41d1,
				0x40d23ece,
				0x40fd9557,
				0x410bfe7e,
				0x412ce32c,
				0x41478ee4,
				0x417e8ab8,
				0x417f7b18,
				0x41835dc0,
				0x41c9b744,
				0x41d5aa30,
				0x4200d129,
				0x420a3c0f,
				0x42104ce9,
				0x421ed535,
				0x4233ed5a,
				0x42348da0,
				0x423b306c,
				0x423fc8ad,
				0x428a7157,
				0x42b3fc09,
				0x42c280e4,
				0x433abc6d,
				0x435d7f24,
				0x43bd08f2,
				0x43d4d056,
				0x43ff8af8,
				0x44083a8f,
				0x441c79c2,
				0x441f12db,
				0x443a32d0,
				0x4495a765,
				0x44a06d53,
				0x44b1e844,
				0x44ca86a9,
				0x44d70dbb,
				0x451054d8,
				0x452414ad,
				0x4527e509,
				0x453dcf20,
				0x456aa864,
				0x4574a099,
				0x45af1650,
				0x45c35f6a,
				0x45f740d1,
				0x46174983,
				0x4685edaa,
				0x4694227e,
				0x46a578b5,
				0x46a97bb7,
				0x46ac8b8c,
				0x46bbf1a4,
				0x46bf8463,
				0x47031c9d,
				0x47460af4,
				0x47489549,
				0x47595e26,
				0x4759ff64,
				0x478a8882,
				0x479adf3f,
				0x47b98bd9,
				0x47fde645,
				0x484e7ea5,
				0x484fe6e1,
				0x486670a6,
				0x4867b323,
				0x48ac6542,
				0x48ce84e9,
				0x48d4f3e5,
				0x48f3da4c,
				0x49120bb3,
				0x4956de6e,
				0x49811c36,
				0x49816593,
				0x49829021,
				0x49996225,
				0x499d2f3c,
				0x49bf3df8,
				0x49c29ffa,
				0x49ee092b,
				0x4a41e13b,
				0x4a4266cc,
				0x4a72773d,
				0x4ab36b32,
				0x4adfc0c9,
				0x4af2ccb6,
				0x4af9d1d9,
				0x4b22c971,
				0x4b444dbc,
				0x4b6e534b,
				0x4b7b063a,
				0x4b9b237c,
				0x4bac0dd7,
				0x4c272c11,
				0x4c53dd18,
				0x4c61d617,
				0x4c6e3901,
				0x4c73b157,
				0x4c8e0520,
				0x4c9de316,
				0x4c9e2da4,
				0x4cacca75,
				0x4caef9fe,
				0x4cdd7ddd,
				0x4d0053c9,
				0x4d172765,
				0x4d1f76c4,
				0x4d33c98f,
				0x4d47e3ff,
				0x4d6410f7,
				0x4d7bec84,
				0x4d91e3b2,
				0x4d9413ef,
				0x4da19524,
				0x4db7e514,
				0x4dc3b39c,
				0x4de6a409,
				0x4de82456,
				0x4e022f83,
				0x4e0465de,
				0x4e28271b,
				0x4e46c5f7,
				0x4e7317f3,
				0x4e7a7476,
				0x4e7fc200,
				0x4e8f1075,
				0x4ebfc2e6,
				0x4ec0e5e9,
				0x4ee72833,
				0x4ef0966b,
				0x4efa1782,
				0x4f2b278a,
				0x4f3e643e,
				0x4f916559,
				0x4f9b8c0a,
				0x4fab9280,
				0x4fc63f36,
				0x4fcb0029,
				0x4ff8d110,
				0x500460b0,
				0x501707c8,
				0x503cdc7c,
				0x5063a4e8,
				0x5067eaaa,
				0x50a607d0,
				0x50c22184,
				0x50d213f4,
				0x50d60cee,
				0x511f0509,
				0x512e9a7f,
				0x513e1a3a,
				0x5144d666,
				0x51709adc,
				0x5193c198,
				0x51b3107e,
				0x51d9c9c0,
				0x51db4c7c,
				0x51dc477a,
				0x51eb4053,
				0x51ed3b8f,
				0x5206d422,
				0x522ce28e,
				0x524bae5e,
				0x52660dbb,
				0x5278a41d,
				0x52c18a5a,
				0x52ab4390,
				0x52db7cc8,
				0x532b1dd1,
				0x5337688f,
				0x536024e5,
				0x53bf42df,
				0x53c39067,
				0x53dd7075,
				0x53e0224d,
				0x54070aef,
				0x540c770f,
				0x5411322e,
				0x5420a5b9,
				0x5423f679,
				0x542ca274,
				0x54310d3e,
				0x54348167,
				0x543b872b,
				0x54776a53,
				0x54cda69d,
				0x54dd1196,
				0x54e961ab,
				0x54fc7cb6,
				0x550730c6,
				0x5518db12,
				0x552846a4,
				0x55343fa3,
				0x55425553,
				0x5571173d,
				0x558e77da,
				0x55a8cf2a,
				0x55afa712,
				0x55c32205,
				0x560c4f15,
				0x563313b7,
				0x5644e588,
				0x5652c758,
				0x5687d081,
				0x568950ee,
				0x569dbe05,
				0x56d3d7e9,
				0x5707dd4e,
				0x5732edcc,
				0x574d1999,
				0x575ece33,
				0x577bec3f,
				0x579774c0,
				0x57ca6238,
				0x57e01dcc,
				0x57e4975b,
				0x57e904e9,
				0x584071f3,
				0x5855ca79,
				0x585f2581,
				0x5869a8f8,
				0x588fc547,
				0x58a52f49,
				0x58a81454,
				0x58a9746b,
				0x58a98a1d,
				0x58d3b4ea,
				0x58e280a2,
				0x592f288a,
				0x593a9667,
				0x59764c58,
				0x59916c77,
				0x59aa6da9,
				0x59c5a033,
				0x59caecc7,
				0x59dcf9e1,
				0x59df96b5,
				0x5a101e71,
				0x5a19d69f,
				0x5a1a1bd9,
				0x5a1d76e4,
				0x5a3f5f93,
				0x5a509326,
				0x5a6df96a,
				0x5a743f85,
				0x5a7d355f,
				0x5a8f8cd2,
				0x5a9789a0,
				0x5acf37c5,
				0x5ae2fc35,
				0x5ae87f53,
				0x5af373e8,
				0x5afd248c,
				0x5b3dc1c0,
				0x5b5c4263,
				0x5b76d222,
				0x5b850339,
				0x5b97b7ac,
				0x5bb42c0b,
				0x5bbd60e4,
				0x5bc934ae,
				0x5bda1bf9,
				0x5be9b160,
				0x5c06866b,
				0x5c0cec9f,
				0x5c1d75a6,
				0x5c762663,
				0x5c7a3561,
				0x5c8957b5,
				0x5cb5a8fb,
				0x5ce284f6,
				0x5cfbce2b,
				0x5d20643d,
				0x5d21b20d,
				0x5d2cd6d1,
				0x5d2e8770,
				0x5d3742e1,
				0x5d3ff1e6,
				0x5dec10b0,
				0x5e2d1d2c,
				0x5e3f31ae,
				0x5e7d2624,
				0x5f254071,
				0x5f281414,
				0x5f37c0ff,
				0x5f455678,
				0x5f47dd93,
				0x5f5e76c9,
				0x5f74c0aa,
				0x5f8b572b,
				0x5f8f8668,
				0x5f989485,
				0x5f9a1284,
				0x5fb619d7,
				0x5fb9ad83,
				0x5fef4bd7,
				0x5ff0d1e7,
				0x5ff8d96f,
				0x600a8bd2,
				0x6023fd9b,
				0x605a3da9,
				0x608c65ed,
				0x6096a1e8,
				0x60f90ad4,
				0x60fea6d4,
				0x611ec062,
				0x614c63bd,
				0x615b4577,
				0x61704dd2,
				0x61721925,
				0x618ce28f,
				0x61bd02c9,
				0x61d7f0a0,
				0x6241dcf3,
				0x62481982,
				0x62874e42,
				0x6288a7bb,
				0x628d2ad4,
				0x6298590b,
				0x62b71cbf,
				0x62f3f6c8,
				0x62fc35b1,
				0x62fc37e5,
				0x63588fb6,
				0x6366ad70,
				0x636e3de1,
				0x638e89fa,
				0x63923871,
				0x63988e7c,
				0x639ab390,
				0x63a56f29,
				0x63ab426e,
				0x63adbebc,
				0x640abb61,
				0x640f2ea2,
				0x6430962d,
				0x643bc43a,
				0x644b9585,
				0x64a7339f,
				0x64d085ec,
				0x64e33712,
				0x6516fb2e,
				0x654179c1,
				0x65454e61,
				0x65474ead,
				0x6558b586,
				0x6560ec50,
				0x656a1380,
				0x659b9569,
				0x65a9198c,
				0x65c1b98f,
				0x65eaf4b2,
				0x661c9aa9,
				0x66254fb8,
				0x66544a00,
				0x66751ff2,
				0x6680cfdb,
				0x669e12f6,
				0x66a5801d,
				0x66cee88b,
				0x66e8c450,
				0x66f2b0e9,
				0x66f9eb27,
				0x671c5c38,
				0x67301e46,
				0x6738be12,
				0x676c1332,
				0x67858406,
				0x6789f4af,
				0x67a13c1c,
				0x67a9ad73,
				0x67c9e641,
				0x67da877f,
				0x67dbe3a8,
				0x67e1c4de,
				0x67f35f69,
				0x683475ee,
				0x683bcd93,
				0x684a97ae,
				0x685632fc,
				0x688060c6,
				0x688fd184,
				0x68905e57,
				0x68b491bd,
				0x68c5f335,
				0x68c79f57,
				0x69263442,
				0x692eb8a1,
				0x6952f148,
				0x69661c40,
				0x697c9014,
				0x699c8fc0,
				0x69a4607f,
				0x69a551a6,
				0x69ad49fb,
				0x69c09379,
				0x69ca00dd,
				0x69e9413e,
				0x69ee65e0,
				0x69ef0318,
				0x6a10dbb7,
				0x6a230b97,
				0x6a2d770f,
				0x6a2e74bc,
				0x6a5de110,
				0x6a62cee0,
				0x6a730537,
				0x6a7fac2a,
				0x6a8cb8ec,
				0x6adefee3,
				0x6b15d96e,
				0x6b23aff8,
				0x6b2d2e0d,
				0x6b4f81d3,
				0x6b5441d0,
				0x6b5ffa1d,
				0x6b6fde1a,
				0x6b73bb05,
				0x6b795ebc,
				0x6b867a1b,
				0x6b952fe2,
				0x6ba6419b,
				0x6bbf0da7,
				0x6c27933e,
				0x6c38910f,
				0x6c4d5af4,
				0x6c78c1f7,
				0x6ca22dda,
				0x6d0a0eba,
				0x6d39c37d,
				0x6d4996f6,
				0x6d51eecb,
				0x6d74805f,
				0x6da666cf,
				0x6db9599a,
				0x6dc2bf77,
				0x6dd6a2bc,
				0x6de3fc35,
				0x6de6824f,
				0x6e081207,
				0x6e201d39,
				0x6e2555d7,
				0x6e2f1928,
				0x6e3ba3c2,
				0x6e8d1996,
				0x6ea0e311,
				0x6ed4aabc,
				0x6eda7dc3,
				0x6efb7a99,
				0x6f028a4d,
				0x6f4bb7f9,
				0x6f5592c2,
				0x6f670837,
				0x6f74f2f3,
				0x6f815a80,
				0x6f8df2d9,
				0x6f9939c7,
				0x6fc0587b,
				0x6fde1cb0,
				0x6fe279b4,
				0x6fee58b0,
				0x6ff5c65c,
				0x70797471,
				0x708f4782,
				0x7091d310,
				0x70993fcb,
				0x70ba7af2,
				0x70cf23cb,
				0x710841e5,
				0x7118137d,
				0x7124eb9e,
				0x71b1d845,
				0x71b37307,
				0x71d1ca27,
				0x71ebe2ef,
				0x7203ba48,
				0x720736e5,
				0x72178dba,
				0x723d3168,
				0x723f9a34,
				0x72509c77,
				0x727e0df8,
				0x72b8156b,
				0x72c3cec1,
				0x72c8a3fb,
				0x72ec6797,
				0x72f54e90,
				0x7301570e,
				0x7305e0f3,
				0x7316eed7,
				0x731f4403,
				0x732a44b6,
				0x732cc3e0,
				0x7340f8cd,
				0x734f7683,
				0x7382b5ec,
				0x7384f37e,
				0x73abc218,
				0x73cb9e00,
				0x73e498db,
				0x73e568ed,
				0x73f55396,
				0x74019666,
				0x74072616,
				0x744387fc,
				0x744babe6,
				0x7462e0e7,
				0x74944d1a,
				0x7498c3ff,
				0x74cc685b,
				0x74cda413,
				0x74d34d79,
				0x74e05608,
				0x74e9f5bb,
				0x74fbd1ca,
				0x75447865,
				0x755ec29c,
				0x75686f53,
				0x756e9af5,
				0x75933c0b,
				0x75a38363,
				0x75ca7328,
				0x75cc8da1,
				0x75e0f65e,
				0x75ea88f0,
				0x7610d393,
				0x7621baaf,
				0x7631fbe6,
				0x7650219b,
				0x7650e782,
				0x76b3cc32,
				0x76d281de,
				0x76fdb175,
				0x771ef3d3,
				0x772114c9,
				0x776a7e45,
				0x7773ca4a,
				0x7774c705,
				0x77d1efd2,
				0x77ef6a33,
				0x78053c0e,
				0x7815b5e5,
				0x783a4be3,
				0x783d7451,
				0x7850409a,
				0x78879d04,
				0x78a1fb03,
				0x78a38920,
				0x78aa6b6f,
				0x78bf81c2,
				0x78c37971,
				0x78cde107,
				0x78df72d2,
				0x7955d3fc,
				0x7977b051,
				0x799f2b4b,
				0x79c14bf9,
				0x79d79665,
				0x79db7af1,
				0x79de70b4,
				0x79f87181,
				0x79facba8,
				0x7a0f96e9,
				0x7a3400ad,
				0x7a4789ee,
				0x7a56dc89,
				0x7a6450f5,
				0x7a7bcf73,
				0x7a8d1fa9,
				0x7a9b6ba1,
				0x7add3eeb,
				0x7af6808d,
				0x7b059043,
				0x7b0f49e6,
				0x7b11ed07,
				0x7b37c437,
				0x7b80c9d8,
				0x7bb34738,
				0x7bf5bcb1,
				0x7bfdaf4c,
				0x7c1aabec,
				0x7c1d6f5b,
				0x7c24c0b8,
				0x7c3d7cc4,
				0x7c445664,
				0x7c95fa6e,
				0x7ca40728,
				0x7cb5510c,
				0x7ce184ec,
				0x7cf536b4,
				0x7cfd8781,
				0x7d02b479,
				0x7d10b85c,
				0x7d4fdda3,
				0x7d770186,
				0x7d96d65f,
				0x7da33acb,
				0x7dbdb93c,
				0x7de28ae3,
				0x7e0fbc73,
				0x7e269d57,
				0x7e5e9fcf,
				0x7e6afba7,
				0x7ef9ef6c,
				0x7f0e43ad,
				0x7f23c467,
				0x7f2b2371,
				0x7f6095ae,
				0x7f79e1be,
				0x7f845900,
				0x7f8a47dd,
				0x7f98c8b3,
				0x7facfa03,
				0x7fb36cd2,
				0x7fc193ea,
				0x7fdfeffb,
				0x7ffbc1e2,
				0x800bbae7,
				0x80214ac1,
				0x8026e592,
				0x8062943c,
				0x8088304a,
				0x809e20d8,
				0x80db6725,
				0x80e69ae2,
				0x80eaa0c0,
				0x812d66f8,
				0x812eaa44,
				0x814b3f78,
				0x81509c7b,
				0x8181f746,
				0x81912047,
				0x819a69b8,
				0x81af56c4,
				0x81bfdf16,
				0x81d5c075,
				0x8205f110,
				0x82185f9f,
				0x821912e8,
				0x8225145b,
				0x82366265,
				0x82826cd2,
				0x82bac591,
				0x82d6907b,
				0x830f9716,
				0x830fade4,
				0x831c9112,
				0x83475c8d,
				0x837683f7,
				0x8383a09e,
				0x83c416e8,
				0x848b8aba,
				0x84b48684,
				0x850acf20,
				0x8538a366,
				0x85487de7,
				0x856832d3,
				0x857bc3bd,
				0x858bb1d0,
				0x85ab6bcc,
				0x85bbc2c8,
				0x85dd2666,
				0x8606f35d,
				0x86171275,
				0x864d4216,
				0x864e5bf0,
				0x867f49eb,
				0x86a16c34,
				0x86a83d68,
				0x86c8e4c3,
				0x86d9ceb3,
				0x87024c72,
				0x874b5974,
				0x874f7064,
				0x877772e0,
				0x87796afa,
				0x8781b51f,
				0x87915c35,
				0x87c1909d,
				0x87de68d5,
				0x87f79f2a,
				0x880ef5e8,
				0x88157112,
				0x8839fac4,
				0x88476b1f,
				0x884f2024,
				0x8860882b,
				0x889451fd,
				0x889a33ea,
				0x88d2bc34,
				0x88e1fd6b,
				0x88e225fd,
				0x88ffcce5,
				0x89003171,
				0x8909e2d4,
				0x8937d8c4,
				0x893ba3a0,
				0x894651c4,
				0x894e3b16,
				0x895e7218,
				0x8995960f,
				0x8a05053b,
				0x8a154872,
				0x8a3df14e,
				0x8a451c5c,
				0x8a5f0dc7,
				0x8a9c2061,
				0x8aac626b,
				0x8ac5cfc9,
				0x8ae084d2,
				0x8ae73fd0,
				0x8ae99900,
				0x8aeba3b7,
				0x8af58425,
				0x8afc333b,
				0x8b15792e,
				0x8b5220a5,
				0x8ba8a66f,
				0x8bbfb426,
				0x8bc159a9,
				0x8bd5c4f7,
				0x8bd7d5ea,
				0x8c195886,
				0x8c48ec59,
				0x8c5adea1,
				0x8c76b862,
				0x8c820201,
				0x8c97bf73,
				0x8cabc97f,
				0x8cb22929,
				0x8cb6d83c,
				0x8cffe91f,
				0x8d088ebc,
				0x8d202bf2,
				0x8d20b51f,
				0x8d85c9fd,
				0x8d998e21,
				0x8da65022,
				0x8dc65046,
				0x8dcb8036,
				0x8de4f79e,
				0x8deb748e,
				0x8dfd01e3,
				0x8e146bff,
				0x8e1e7ccf,
				0x8e220f73,
				0x8e8c7a5b,
				0x8e995498,
				0x8ea015a2,
				0x8ea2348c,
				0x8ea3c5e6,
				0x8ee87647,
				0x8ef8c09d,
				0x8f1b34fb,
				0x8f4a5914,
				0x8f4c4f62,
				0x8f87a849,
				0x8fa6f425,
				0x8fa7758f,
				0x8fa9b49b,
				0x8fb3826a,
				0x8fc476d9,
				0x8fd48cb3,
				0x8fe5b03d,
				0x9008eb42,
				0x9012d675,
				0x902961bc,
				0x902d2c9f,
				0x904bdecf,
				0x90aa8c4f,
				0x90b43798,
				0x90d292d7,
				0x9116fa25,
				0x911cc675,
				0x911dee4c,
				0x914b6c18,
				0x9159ad53,
				0x916c62fe,
				0x91b1ba50,
				0x91cc6389,
				0x91d4219d,
				0x91f17967,
				0x92258fae,
				0x9271a41a,
				0x927a5723,
				0x927f2484,
				0x92a01e24,
				0x92b1e4a4,
				0x92c6b793,
				0x92cc5296,
				0x92d2c561,
				0x92d9b756,
				0x92db8389,
				0x92e05029,
				0x92f001a2,
				0x92f6f2fd,
				0x9303e1a6,
				0x93206b10,
				0x93282ce8,
				0x9330c917,
				0x9344ecec,
				0x936cd0e4,
				0x93948e5e,
				0x93d669c6,
				0x93f175ae,
				0x94110818,
				0x9419253c,
				0x944aab6e,
				0x944d0adf,
				0x947a8766,
				0x94971e80,
				0x94b00453,
				0x94dd7cf9,
				0x94ffcae4,
				0x950434d6,
				0x951654db,
				0x9539c6a4,
				0x954c0ee1,
				0x95583589,
				0x955f607f,
				0x9572598e,
				0x957b7e46,
				0x95c5a22b,
				0x95c95659,
				0x95f357db,
				0x95f6a908,
				0x960fdf10,
				0x961ccc04,
				0x96218fb4,
				0x96283771,
				0x963025ed,
				0x96353472,
				0x964945d9,
				0x966522a9,
				0x968a47d1,
				0x96985633,
				0x96cf6d35,
				0x96d59d8b,
				0x96de904f,
				0x97255a03,
				0x97303d16,
				0x976850d8,
				0x976fbb46,
				0x978dabe5,
				0x97936677,
				0x97a58869,
				0x97ae51ca,
				0x97b477d0,
				0x97c3281b,
				0x97cd38c1,
				0x97dd124c,
				0x97ffa41f,
				0x9817aaaa,
				0x98477c5e,
				0x985e6de3,
				0x9866a5db,
				0x98752042,
				0x987b800e,
				0x988a98a8,
				0x98a41590,
				0x98a45cf6,
				0x98b1c712,
				0x98d449c4,
				0x98e54293,
				0x98ee1acd,
				0x9916784f,
				0x991b6c74,
				0x9969f1ed,
				0x997021a9,
				0x9970602c,
				0x9970981e,
				0x99877535,
				0x998e5402,
				0x99acc034,
				0x99b03830,
				0x99c95119,
				0x99d863c8,
				0x99e3b9c7,
				0x99eae44b,
				0x99fe0df3,
				0x9a1b0cec,
				0x9a1dc7f0,
				0x9a4be536,
				0x9a74201c,
				0x9a753742,
				0x9a7dc49f,
				0x9ae4d12b,
				0x9b064735,
				0x9b1aae33,
				0x9b25e98e,
				0x9b317c53,
				0x9b44f767,
				0x9b7140ef,
				0x9b7d0eb4,
				0x9b862e76,
				0x9b8b9be6,
				0x9b9fc8e2,
				0x9bab2887,
				0x9bb59df3,
				0x9bc6b6c6,
				0x9be6b714,
				0x9be9742e,
				0x9bfef7ce,
				0x9c034ede,
				0x9c2f238e,
				0x9c3ef8ab,
				0x9c5394a2,
				0x9c5d94d2,
				0x9c610e9f,
				0x9c762726,
				0x9c800a2b,
				0x9c8d09c9,
				0x9caf9ab7,
				0x9cdfb1e0,
				0x9ce03108,
				0x9d231778,
				0x9d35663f,
				0x9d5f6034,
				0x9d6c5792,
				0x9d7acaba,
				0x9d7bf225,
				0x9da73454,
				0x9df04bfa,
				0x9dfa9675,
				0x9e5fffcb,
				0x9e830ac7,
				0x9ec80810,
				0x9ec9a37c,
				0x9edc4d3e,
				0x9f408938,
				0x9f4438a1,
				0x9f652194,
				0x9f658eb1,
				0x9f77a13c,
				0x9f77c57f,
				0x9f7f98f0,
				0x9fb5f562,
				0x9fbc1b97,
				0x9fdb74e1,
				0xa0037ea2,
				0xa01d4764,
				0xa05821c3,
				0xa0591be3,
				0xa0680239,
				0xa0743a7a,
				0xa0768594,
				0xa09b3816,
				0xa0a2e767,
				0xa0ee190e,
				0xa10cb4e7,
				0xa1277190,
				0xa138ec7c,
				0xa13d3f8d,
				0xa175f894,
				0xa17e68a8,
				0xa18345de,
				0xa1c9127d,
				0xa1d04cda,
				0xa1e58f89,
				0xa1f54321,
				0xa258a1e7,
				0xa2632fc0,
				0xa276fa49,
				0xa27b3628,
				0xa284d099,
				0xa2937234,
				0xa2942448,
				0xa2995f30,
				0xa2ad7fce,
				0xa2af27fc,
				0xa2bef1d4,
				0xa2cc2989,
				0xa2e165e4,
				0xa32b067b,
				0xa34519ef,
				0xa345b107,
				0xa346ca47,
				0xa3791328,
				0xa38171bc,
				0xa396e074,
				0xa3e0ce51,
				0xa4045ef5,
				0xa46fdbe2,
				0xa47022ac,
				0xa4850630,
				0xa4a3757a,
				0xa4b0d6d0,
				0xa4b340ca,
				0xa4d4093e,
				0xa4de13e3,
				0xa4e7e0a7,
				0xa4f7b696,
				0xa50dddd0,
				0xa515d692,
				0xa529b342,
				0xa53de4d1,
				0xa5c3f740,
				0xa5f2f692,
				0xa6066e14,
				0xa60891f8,
				0xa60f936d,
				0xa61d8f53,
				0xa62143ac,
				0xa625557d,
				0xa640624d,
				0xa640636d,
				0xa6488382,
				0xa665334d,
				0xa67c935f,
				0xa692bac0,
				0xa6b0f2b1,
				0xa6b97967,
				0xa6cf67a8,
				0xa6db990b,
				0xa72060f8,
				0xa7303751,
				0xa73dfef6,
				0xa76eddfb,
				0xa77d3afc,
				0xa7904cef,
				0xa79405a5,
				0xa79cc3df,
				0xa7bfc4c9,
				0xa7ceb3d0,
				0xa7cf17c4,
				0xa7d055f0,
				0xa7de87a3,
				0xa81e7ca7,
				0xa8268e87,
				0xa8476032,
				0xa8514892,
				0xa879bc02,
				0xa8933da1,
				0xa8c10a3d,
				0xa8c85c30,
				0xa8fb693e,
				0xa91dbb39,
				0xa9319e55,
				0xa94a1f3e,
				0xa94dc27b,
				0xa95a8d8f,
				0xa9b04f7d,
				0xa9b621e9,
				0xa9bd0d16,
				0xa9e72ccb,
				0xa9e806b3,
				0xaa00e4cf,
				0xaa05e30f,
				0xaa435f77,
				0xaa4bd054,
				0xaa6f3ffd,
				0xaa9a17aa,
				0xaacc84b0,
				0xaad8f4d1,
				0xaae2760c,
				0xab0f542f,
				0xab2b066d,
				0xab57a27d,
				0xab787ab6,
				0xabb0b493,
				0xabb2ec9a,
				0xac174334,
				0xac3efb24,
				0xac3fd17d,
				0xac4a6a8d,
				0xac57b1a5,
				0xacb1c4f1,
				0xacb46408,
				0xacd6d1ab,
				0xace19e92,
				0xad3ae9fb,
				0xad4a3182,
				0xad533ecc,
				0xad62c8eb,
				0xad66545a,
				0xad679682,
				0xad85358a,
				0xad903651,
				0xad95334c,
				0xadb90f84,
				0xadbc8ae3,
				0xadc2588e,
				0xadca3fdc,
				0xadd86d53,
				0xadfa98da,
				0xae0ead76,
				0xae1411a3,
				0xae361b07,
				0xae575af5,
				0xae588c5f,
				0xae6808fc,
				0xae70bfe4,
				0xaea85e48,
				0xaeb63c4b,
				0xaeb74c05,
				0xaef842bf,
				0xaf0abbf0,
				0xaf0dd721,
				0xaf0e3f9f,
				0xaf23cb13,
				0xaf650a95,
				0xaf7f41f3,
				0xaf8e6723,
				0xaf9e03cd,
				0xafa0536a,
				0xafa09287,
				0xafcaa853,
				0xaffe1f5a,
				0xb0038764,
				0xb01315b4,
				0xb02174a9,
				0xb0b51271,
				0xb0e2f500,
				0xb0effbdd,
				0xb0f63288,
				0xb0f81a16,
				0xb10be2e6,
				0xb114d77b,
				0xb11eb1ed,
				0xb12ad7ef,
				0xb155b61d,
				0xb155fd87,
				0xb157c9e4,
				0xb172109b,
				0xb17cce7e,
				0xb18ddcad,
				0xb197b514,
				0xb1a02702,
				0xb1a9c764,
				0xb1b2b66b,
				0xb1e5edc9,
				0xb21c3926,
				0xb21fa9e0,
				0xb2266adc,
				0xb226e336,
				0xb2274905,
				0xb243e8a2,
				0xb28bb04b,
				0xb2a7a56c,
				0xb2b4cbc8,
				0xb2b71d87,
				0xb321dd82,
				0xb32adca8,
				0xb33f989e,
				0xb34d3ead,
				0xb36e2577,
				0xb388538b,
				0xb38e647c,
				0xb38fb370,
				0xb39b99e2,
				0xb3a1fbb6,
				0xb3b7b784,
				0xb3e59a0e,
				0xb3ef1c92,
				0xb3fab6e0,
				0xb45678b5,
				0xb4670015,
				0xb46b2bee,
				0xb4861eb7,
				0xb48ebc82,
				0xb4978950,
				0xb498df06,
				0xb4a37c24,
				0xb4cda44c,
				0xb4e9561a,
				0xb4fcc9e0,
				0xb519fa90,
				0xb52c7976,
				0xb56c3fb8,
				0xb5730901,
				0xb58259bd,
				0xb584bdf6,
				0xb5856054,
				0xb58be281,
				0xb5978b89,
				0xb5dd1656,
				0xb5e60c50,
				0xb63f6584,
				0xb666fc1a,
				0xb685e324,
				0xb69ac468,
				0xb6d12f0b,
				0xb7063b22,
				0xb716e023,
				0xb7458049,
				0xb7580398,
				0xb7631b41,
				0xb76c1605,
				0xb773c2e1,
				0xb78a2c75,
				0xb78eccb8,
				0xb7be26a9,
				0xb7bfe6ea,
				0xb7d52e66,
				0xb7e6afd4,
				0xb7ffff45,
				0xb82369d4,
				0xb8300543,
				0xb8389439,
				0xb8465008,
				0xb856d4ce,
				0xb861775a,
				0xb870d344,
				0xb8771db6,
				0xb87acfd1,
				0xb87e6de1,
				0xb8a61533,
				0xb8adc43d,
				0xb8cb3475,
				0xb8cfe3e3,
				0xb9127abd,
				0xb92678a6,
				0xb92b06e4,
				0xb936ff48,
				0xb93c9aec,
				0xb94b6276,
				0xb9551550,
				0xb9579ffa,
				0xb9b1c2ed,
				0xb9c4dfdf,
				0xb9d7756c,
				0xb9e09d51,
				0xb9f9d770,
				0xba07360d,
				0xba4270a1,
				0xba49a863,
				0xba869185,
				0xbab56423,
				0xbaea49d0,
				0xbaffedef,
				0xbb188579,
				0xbb2b5cd9,
				0xbb314853,
				0xbb3bf7f2,
				0xbb427a69,
				0xbb42ee78,
				0xbb453063,
				0xbb492bc0,
				0xbb97e555,
				0xbb9b1f5d,
				0xbbac2ce9,
				0xbbbd0cd0,
				0xbbfb2ad9,
				0xbc0f60d5,
				0xbc4649e5,
				0xbcb893c3,
				0xbcc5654d,
				0xbcc7f321,
				0xbcd19c9a,
				0xbcdefab5,
				0xbcf7c688,
				0xbd564507,
				0xbd65a104,
				0xbd7d6804,
				0xbda2fa15,
				0xbda702af,
				0xbdb71f30,
				0xbdc1dc1d,
				0xbddfe09a,
				0xbde0ccd4,
				0xbde777b6,
				0xbe053b7f,
				0xbe643e32,
				0xbe7c85d8,
				0xbe862050,
				0xbeac7c8f,
				0xbec44b8f,
				0xbee0b82c,
				0xbef068da,
				0xbf085fa5,
				0xbf7ce0ee,
				0xbf8909fa,
				0xbf8918de,
				0xbfb7cb54,
				0xbfe4c3dc,
				0xc03976a4,
				0xc06e378e,
				0xc0738078,
				0xc079b265,
				0xc0894af7,
				0xc09bfe41,
				0xc0af9e66,
				0xc0b01adf,
				0xc0d0c304,
				0xc0d710bf,
				0xc104fdc6,
				0xc114a65a,
				0xc135e006,
				0xc13a16f0,
				0xc16217aa,
				0xc162360a,
				0xc174e89a,
				0xc17c1428,
				0xc184dfd2,
				0xc19bc1d2,
				0xc1d16f23,
				0xc1f93e69,
				0xc200c0f1,
				0xc2033e67,
				0xc20633f4,
				0xc2161726,
				0xc2339364,
				0xc243827f,
				0xc297ff25,
				0xc29e736c,
				0xc2e3ab32,
				0xc2e3e902,
				0xc2ff6d4f,
				0xc303b70e,
				0xc3262c87,
				0xc32d74c9,
				0xc3674b40,
				0xc36c9e08,
				0xc375166f,
				0xc381b3e6,
				0xc3e04817,
				0xc3f13fcc,
				0xc40bbb0b,
				0xc41f32bf,
				0xc42c019a,
				0xc4495033,
				0xc44eca22,
				0xc450bd65,
				0xc486b3a9,
				0xc496788b,
				0xc4a5671c,
				0xc4b5775d,
				0xc4c2d702,
				0xc4cd1a66,
				0xc4d260d7,
				0xc4d413b8,
				0xc504912c,
				0xc512cb8e,
				0xc54c0cd2,
				0xc5553c15,
				0xc569d6a1,
				0xc56fc20c,
				0xc577ae9c,
				0xc5891bd6,
				0xc593081d,
				0xc5ac6a0a,
				0xc5b62161,
				0xc5dc419e,
				0xc5de8740,
				0xc5f996e4,
				0xc622d83c,
				0xc660c7aa,
				0xc67f8fca,
				0xc689b79b,
				0xc6922870,
				0xc692fd71,
				0xc6b254ae,
				0xc6e1f6a2,
				0xc6fd3b45,
				0xc6fed6dc,
				0xc71f2e9c,
				0xc732d5b3,
				0x7720344,
				0xc7911492,
				0xc79a987e,
				0xc7c649ff,
				0xc80116bc,
				0xc80467c6,
				0xc82334a0,
				0xc8264238,
				0xc82aa437,
				0xc83b7ca7,
				0xc84984b9,
				0xc84e4eb4,
				0xc89630b8,
				0xc8d5d232,
				0xc91dc9e5,
				0xc93d6143,
				0xc93e7ef7,
				0xc94c4b4c,
				0xc95d4c83,
				0xc9689c03,
				0xc974cdee,
				0xc9a01049,
				0xc9a375d8,
				0xc9ab355d,
				0xc9b3d1a2,
				0xc9da7eba,
				0xc9eb9378,
				0xc9f9fa76,
				0xca167027,
				0xca18c189,
				0xca213512,
				0xca43dfbb,
				0xca5f3c8c,
				0xca655896,
				0xca6d8185,
				0xca8dae8c,
				0xcac428f6,
				0xcad74d94,
				0xcae292d4,
				0xcb0099d4,
				0xcb290ee2,
				0xcb2bf389,
				0xcb2c3311,
				0xcb31aa82,
				0xcb3349a8,
				0xcb74fe41,
				0xcba3b7cb,
				0xcbab0735,
				0xcbc4558e,
				0xcbd626f4,
				0xcbd76893,
				0xcc4b16af,
				0xcc691808,
				0xcc853bb5,
				0xccab2ce8,
				0xccdc8715,
				0xcce52baa,
				0xccf19015,
				0xcd1311a4,
				0xcd1a7f03,
				0xcd4fd8a1,
				0xcd97e151,
				0xcdd8fe00,
				0xcdd9a9e6,
				0xcdeb2be6,
				0xcdf88e2d,
				0xcdff8619,
				0xce1f129d,
				0xce23960a,
				0xce67db4d,
				0xce7e374e,
				0xcea8daab,
				0xceb77eb2,
				0xcec5eb59,
				0xced642c5,
				0xcee6ecac,
				0xcf1e5a76,
				0xcf2f0e21,
				0xcfeca85c,
				0xcff38f71,
				0xd00e75f9,
				0xd02abbb2,
				0xd0357169,
				0xd0df4625,
				0xd0e57090,
				0xd0f2eb57,
				0xd1191a56,
				0xd15dd223,
				0xd186b292,
				0xd1b3e291,
				0xd1c3134d,
				0xd1cca233,
				0xd1cfa7e0,
				0xd1db5101,
				0xd1f5e145,
				0xd219e846,
				0xd2251200,
				0xd22a70cb,
				0xd22d5ad7,
				0xd22e15b8,
				0xd23519d2,
				0xd256393a,
				0xd258b1e2,
				0xd26366ec,
				0xd2786f70,
				0xd2b52967,
				0xd2d24770,
				0xd2e57652,
				0xd2e94182,
				0xd2fd26b7,
				0xd322a87f,
				0xd325cbe5,
				0xd32f8f53,
				0xd334fe8b,
				0xd37a5f68,
				0xd3873805,
				0xd3bef497,
				0xd41b42e1,
				0xd42523cd,
				0xd427b91b,
				0xd4405e08,
				0xd4484c93,
				0xd47c7bb9,
				0xd482b34e,
				0xd4936053,
				0xd4ae5a26,
				0xd4c514bd,
				0xd5094d6d,
				0xd519d463,
				0xd52631f1,
				0xd529e4be,
				0xd5362763,
				0xd588f0a5,
				0xd591aab4,
				0xd593f420,
				0xd59d6b1a,
				0xd5c0bc07,
				0xd5c12a95,
				0xd5f70bea,
				0xd600b572,
				0xd61aecba,
				0xd63183a8,
				0xd64fa0d6,
				0xd67b19e7,
				0xd68a9cdf,
				0xd6aa6804,
				0xd6b12b86,
				0xd6b8ec0c,
				0xd6bf7dbb,
				0xd714ee7c,
				0xd718ad9e,
				0xd71ec202,
				0xd722efa8,
				0xd7695070,
				0xd7744cb7,
				0xd790fc9e,
				0xd7c0143f,
				0xd7ca8d26,
				0xd7ec0edd,
				0xd82eba61,
				0xd84ae7c2,
				0xd8a5878d,
				0xd8bf9a2c,
				0xd8ee57f7,
				0xd8f28047,
				0xd8f7692d,
				0xd8fef003,
				0xd934d62b,
				0xd95a6f7d,
				0xd9601f1f,
				0xd9b2911f,
				0xda17460e,
				0xda5e8452,
				0xda76fe6e,
				0xda94526b,
				0xda9df33d,
				0xdacb82c1,
				0xdafa2489,
				0xdb00b30a,
				0xdb19ec33,
				0xdb24e373,
				0xdb60ad20,
				0xdb86cb89,
				0xdb8b3fc0,
				0xdb8f1a1a,
				0xdbf285f4,
				0xdc280c4e,
				0xdc551884,
				0xdc638ff8,
				0xdc6b48ca,
				0xdc6b5d07,
				0xdc6eae80,
				0xdc8f32e1,
				0xdca9a809,
				0xdcb0a8c7,
				0xdcc78b83,
				0xdce32fba,
				0xdcf1ed25,
				0xdcff71e4,
				0xdd12d554,
				0xdd433942,
				0xdd4b2236,
				0xdd8abbcf,
				0xdd9a1802,
				0xdd9ea431,
				0xdda42ad2,
				0xddb23012,
				0xdded2bb9,
				0xde0192e4,
				0xde08a82e,
				0xde4cbc3a,
				0xde6c3ffe,
				0xde83a424,
				0xde91e699,
				0xde962965,
				0xde9950af,
				0xdea4ebf4,
				0xdee74aff,
				0xdeeab297,
				0xdef387de,
				0xdef682af,
				0xdf217cdc,
				0xdf31c32b,
				0xdf325e57,
				0xdf59ff80,
				0xdf5f9f7f,
				0xdf6e8ace,
				0xdf9841d7,
				0xdfb0893d,
				0xdfd03ff2,
				0xdfd5aaa1,
				0xdfdb51b8,
				0xdff68a19,
				0xdffe95c6,
				0xe013a8b3,
				0xe0264f5d,
				0xe0311180,
				0xe0415048,
				0xe05d9217,
				0xe08ef8f2,
				0xe0b17fe0,
				0xe0c3d6ce,
				0xe0ed938f,
				0xe1497820,
				0xe1583df5,
				0xe15ca04a,
				0xe16f99fb,
				0xe188fb85,
				0xe1a1f963,
				0xe1a367ad,
				0xe1af1b43,
				0xe1b6fe0c,
				0xe1b9ffad,
				0xe1c17f6f,
				0xe1c21b3d,
				0xe1e4c1ca,
				0xe1e50f97,
				0xe2100c79,
				0xe211190e,
				0xe22a202a,
				0xe22b4cd9,
				0xe22f390b,
				0xe231f917,
				0xe258d3ce,
				0xe2ba016f,
				0xe2cf7922,
				0xe2d26e9f,
				0xe2eb322b,
				0xe2ee52b7,
				0xe2fba8d8,
				0xe32c6055,
				0xe33dcac4,
				0xe35b8830,
				0xe37a5f0f,
				0xe393768e,
				0xe39b04ac,
				0xe3ce09e2,
				0xe3d693e9,
				0xe3d71673,
				0xe40a0f8e,
				0xe4212e8d,
				0xe43d331b,
				0xe44d5cec,
				0xe4774712,
				0xe49edebd,
				0xe4a13b99,
				0xe4afb8d2,
				0xe4b0ae85,
				0xe4d12678,
				0xe4df846a,
				0xe508f544,
				0xe513c086,
				0xe51f88d9,
				0xe539c011,
				0xe54fb6c7,
				0xe55a7962,
				0xe567d04b,
				0xe573997b,
				0xe5ba1f6d,
				0xe5c038ba,
				0xe60d45ab,
				0xe62944fb,
				0xe63654e3,
				0xe661157e,
				0xe6bb31ab,
				0xe6c76e5e,
				0xe6cb661e,
				0xe6eae263,
				0xe6fa7770,
				0xe6fc3f54,
				0xe7088147,
				0xe70ed8f9,
				0xe786d826,
				0xe7925523,
				0xe79e68e7,
				0xe7b10066,
				0xe7c5df10,
				0xe7cb7050,
				0xe7d14cab,
				0xe7d3f252,
				0xe7d9dc8e,
				0xe7daa6e6,
				0xe7df9d40,
				0xe7f419bf,
				0xe8147d73,
				0xe817f25b,
				0xe81bda47,
				0xe8617484,
				0xe8842e39,
				0xe8ac7f0f,
				0xe8dad32f,
				0xe8e8aada,
				0xe9010c78,
				0xe918fefb,
				0xe92bfed2,
				0xe92e717e,
				0xe9501c24,
				0xe979d6cd,
				0xe9ddefbf,
				0xe9e2ec92,
				0xe9f7398f,
				0xe9f788ec,
				0xea01a75c,
				0xea52c1db,
				0xea5f89bc,
				0xea85b372,
				0xea892147,
				0xea909ab4,
				0xea98ac78,
				0xea9dab4c,
				0xeacd3c4b,
				0xeaf6c20a,
				0xeafbfa28,
				0xeb133ed3,
				0xeb25e6fc,
				0xeb278b23,
				0xeb2e00e0,
				0xeb4eb54e,
				0xeb59f0c3,
				0xeb7d0265,
				0xeb97ff8a,
				0xeb9f2052,
				0xeba60087,
				0xebcaa414,
				0xebe30bbb,
				0xec013325,
				0xec04c9b8,
				0xec06e146,
				0xec087846,
				0xec1cb97c,
				0xec2d6c2c,
				0xec42b38e,
				0xec48c402,
				0xec5d832a,
				0xec6f1f55,
				0xec9758cf,
				0xece03f63,
				0xecf7e8a8,
				0xed0a985e,
				0xed1357f5,
				0xed1840d2,
				0xed25f13b,
				0xed2e79f0,
				0xed3f3ad6,
				0xed4dfca2,
				0xed82c057,
				0xed92db77,
				0xeda770f8,
				0xeda96f47,
				0xedcdbe97,
				0xedd7c0d3,
				0xede36dc8,
				0xedeb881e,
				0xedf175e9,
				0xedf5cd3c,
				0xee01991c,
				0xee04e7a6,
				0xee0bf0c2,
				0xee1b2337,
				0xee36a8c9,
				0xee5616df,
				0xee57994a,
				0xee5b4c1c,
				0xee5ebc97,
				0xee5f8e23,
				0xee6d0843,
				0xee85163e,
				0xee8a4608,
				0xee8c528f,
				0xeea954bb,
				0xeefa0f14,
				0xef366503,
				0xef4b5cd0,
				0xef4fcfb5,
				0xef6d0839,
				0xef6e4362,
				0xef97ec60,
				0xefa64001,
				0xefaae110,
				0xefb5364b,
				0xefc4165a,
				0xf013c580,
				0xf017500d,
				0xf03beb5f,
				0xf03c985c,
				0xf042f402,
				0xf046ea37,
				0xf0481cc3,
				0xf0a61994,
				0xf0ae274e,
				0xf10c7160,
				0xf123e9f6,
				0xf12d5114,
				0xf14fa119,
				0xf15f72b2,
				0xf15fb3dd,
				0xf16de1ee,
				0xf1844d22,
				0xf1858017,
				0xf1c3c4ca,
				0xf1cc086e,
				0xf22a4ce0,
				0xf23d6019,
				0xf2775005,
				0xf27c4b96,
				0xf2b2e482,
				0xf2bd35bb,
				0xf2bde7de,
				0xf2be7d80,
				0xf3004a06,
				0xf32a6f24,
				0xf3445f43,
				0xf3565180,
				0xf3584679,
				0xf360f3d8,
				0xf394a932,
				0xf3aa2136,
				0xf3ae2877,
				0xf3bf3eb6,
				0xf3c33285,
				0xf3ca5bcb,
				0xf3d8a3c7,
				0xf4053ec1,
				0xf4092dd5,
				0xf4385d0d,
				0xf43fc5e6,
				0xf48428cd,
				0xf4a0ea8f,
				0xf4f1511e,
				0xf53a45fd,
				0xf561110a,
				0xf5676424,
				0xf57433a5,
				0xf578c00d,
				0xf5919088,
				0xf5994263,
				0xf5a7a176,
				0xf5af9d4a,
				0xf5c39f51,
				0xf5d66055,
				0xf62881d0,
				0xf62bc268,
				0xf6361ab7,
				0xf65181cf,
				0xf66f582f,
				0xf68387e8,
				0xf69bf55a,
				0xf6b49cae,
				0xf6ef38b3,
				0xf6ff3f3d,
				0xf71e3328,
				0xf724026d,
				0xf72be7e8,
				0xf73506d3,
				0xf7bab7db,
				0xf7f3479f,
				0xf7fcf988,
				0xf80e2102,
				0xf8275b68,
				0xf8357b46,
				0xf85dd961,
				0xf8bd70b3,
				0xf9132f55,
				0xf91d716c,
				0xf92bdd8a,
				0xf9372cc5,
				0xf9627c39,
				0xf9980bc3,
				0xf9b8b7a0,
				0xfa11bea2,
				0xfa3d47fa,
				0xfa4d7a73,
				0xfa546702,
				0xfa686c0e,
				0xfa7bcf6a,
				0xfae5c85d,
				0xfaeab60d,
				0xfaf5aa0c,
				0xfaf7a1ba,
				0xfb454066,
				0xfb4b9bb7,
				0xfb50d934,
				0xfb631122,
				0xfb6b8a4f,
				0xfb74d039,
				0xfb964e73,
				0xfba10656,
				0xfba21596,
				0xfbdd1813,
				0xfc022e61,
				0xfc0243f5,
				0xfc1c3dcb,
				0xfc27b091,
				0xfc2a1c15,
				0xfc43b487,
				0xfc612f85,
				0xfc818f56,
				0xfcb60416,
				0xfce1e2b7,
				0xfcef5842,
				0xfd17bd49,
				0xfd21dcef,
				0xfd26b232,
				0xfd3a6691,
				0xfd531f0c,
				0xfd595b36,
				0xfd6166a5,
				0xfd693ffe,
				0xfd6c9f0f,
				0xfd710be1,
				0xfd7a813a,
				0xfd8a3806,
				0xfd8dc6e8,
				0xfdbea6e8,
				0xfdbeb5b0,
				0xfdcc6b19,
				0xfdeb82cf,
				0xfe401883,
				0xfe64a913,
				0xfe692197,
				0xfe6e928a,
				0xfe9fd22c,
				0xfeb8b69b,
				0xfefa2a3a,
				0xff084195,
				0xff1f92a2,
				0xff2ea296,
				0xff374a2b,
				0xff426713,
				0xff7d7d88,
				0xff93aa35,
				0xffa54e54,
				0xffac631b,
				0xffdc3b30,
				0xfffca75c };
			DWORD Model = Obj[random];
			g_CallbackScript->AddCallback<ModelCallback>(Model, [Model, Dir, PlayerPosition] {

				Object ObJect;
				OBJECT::CREATE_OBJECT(Model, PlayerPosition.x, PlayerPosition.y, PlayerPosition.z, true, 1, -1, &ObJect, true, false, false);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);
				if (ENTITY::DOES_ENTITY_EXIST(ObJect))
				{
					ENTITY::SET_ENTITY_RECORDS_COLLISIONS(ObJect, true);
					for (float f = 0.0f; f < 75.0f; f++) {
							ENTITY::APPLY_FORCE_TO_ENTITY(ObJect, 1, Dir.x*10.0f, Dir.y*20.0f, Dir.z*10.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
					}
				}

			});
		}
}



bool Features::GravityGun = false;
bool grav_target_locked = false;
void Features::gravitygun() {

	Entity EntityTarget;
	DWORD equippedWeapon;
	WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &equippedWeapon, 1);
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = rot_to_direction(&rot);
	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	float spawnDistance = get_distance(&camPosition, &playerPosition);
	spawnDistance += 5;




	Vector3 spawnPosition = testadd(camPosition, multiply(&dir, spawnDistance));





	Player tempPed = PLAYER::PLAYER_ID();
	if (grav_target_locked)
	{
		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget) && GetAsyncKeyState(VK_RBUTTON))
		{
			Vector3 EntityTargetPos = ENTITY::GET_ENTITY_COORDS(EntityTarget, 0);
			PLAYER::DISABLE_PLAYER_FIRING(tempPed, true);
			if (ENTITY::IS_ENTITY_A_PED(EntityTarget) && PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1))
			{
				EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
			}

			RequestControlOfEnt(EntityTarget);

			if (ENTITY::IS_ENTITY_A_VEHICLE(EntityTarget))
				ENTITY::SET_ENTITY_HEADING(
					EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(EntityTarget, spawnPosition.x, spawnPosition.y, spawnPosition.z, 0, 0, 0);

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				AUDIO::PLAY_SOUND_FROM_ENTITY(-1, (char*)"Foot_Swish", EntityTarget, (char*)"docks_heist_finale_2a_sounds", 0, 0);
				ENTITY::SET_ENTITY_HEADING(EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));
				ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 10000.0f, dir.y * 10000.0f, dir.z * 10000.0f, 0.0f, 0.0f,
					0.0f, 0, 0, 1, 1, 0, 1);
				grav_target_locked = false;
				PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
			}
		}
	}
	if (!PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
	{
		grav_target_locked = true;
		PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
	}


}



Vector3 testmult(Vector3 vector, float x) {
	Vector3 result;
	result.x = vector.x;
	result.y = vector.y;
	result.z = vector.z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}

bool Features::VALKYIREROCKET = false;
void Features::valkyirerocket()
{
	static std::int32_t rocket, cam;
	static std::uint8_t y;
	static float bar;
	static bool init;
	if (is_ped_shooting(PLAYER::PLAYER_PED_ID())) {
		if (!init) init = true;
	}
	if (init) {
		if (!ENTITY::DOES_ENTITY_EXIST(rocket)) {
			auto weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
			auto c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon, 0.f, 1.f, 0.f);
			rocket;

			OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("w_lr_rpg_rocket"), c.x, c.y, c.z, true, 1, -1, &rocket, true, false, false);


			CAM::DESTROY_ALL_CAMS(true);
			cam = CAM::CREATE_CAM((char*)"DEFAULT_SCRIPTED_CAMERA", 1);
			CAM::ATTACH_CAM_TO_ENTITY(cam, rocket, 0.f, 0.f, 0.f, 1);
			CAM::RENDER_SCRIPT_CAMS(1, true, 700, 1, 1);
			CAM::SET_CAM_ACTIVE(cam, 1);
			ENTITY::SET_ENTITY_VISIBLE(rocket, 0, 0);
			bar = .5f; y = 255;
		}
		else {
			CAM::SET_CAM_ROT(cam, CAM::GET_GAMEPLAY_CAM_ROT(0).x, CAM::GET_GAMEPLAY_CAM_ROT(0).y, CAM::GET_GAMEPLAY_CAM_ROT(0).z, 0);
			ENTITY::SET_ENTITY_ROTATION(rocket, CAM::GET_GAMEPLAY_CAM_ROT(0).x, CAM::GET_GAMEPLAY_CAM_ROT(0).y, CAM::GET_GAMEPLAY_CAM_ROT(0).z, 0, 1);

			auto c = testadd(ENTITY::GET_ENTITY_COORDS(rocket, 1), testmult(RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0)), .8f));


			ENTITY::SET_ENTITY_COORDS(rocket, c.x, c.y, c.z, 0, 0, 0, 0);

			UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
			PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 1);
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 1);
			UI::_SHOW_WEAPON_WHEEL(false);

			GRAPHICS::DRAW_RECT(0.5f, 0.5f - 0.025f, 0.050f, 0.002f, 255, 255, 255, 255);
			GRAPHICS::DRAW_RECT(0.5f, 0.5f + 0.025f, 0.050f, 0.002f, 255, 255, 255, 255);
			GRAPHICS::DRAW_RECT(0.5f - 0.025f, 0.5f, 0.002f, 0.050f, 255, 255, 255, 255);
			GRAPHICS::DRAW_RECT(0.5f + 0.025f, 0.5f, 0.002f, 0.050f, 255, 255, 255, 255);
			GRAPHICS::DRAW_RECT(0.5f + 0.05f, 0.5f, 0.050f, 0.002f, 255, 255, 255, 255);
			GRAPHICS::DRAW_RECT(0.5f - 0.05f, 0.5f, 0.050f, 0.002f, 255, 255, 255, 255);
			GRAPHICS::DRAW_RECT(0.5f, 0.5f + 0.05f, 0.002f, 0.050f, 255, 255, 255, 255);
			GRAPHICS::DRAW_RECT(0.5f, 0.5f - 0.05f, 0.002f, 0.050f, 255, 255, 255, 255);
			GRAPHICS::SET_TIMECYCLE_MODIFIER((char*)"CAMERA_secuirity");

			GRAPHICS::DRAW_RECT(0.25f, 0.5f, 0.03f, 0.5f, 255, 255, 255, 255);
			static auto ticker = GetTickCount();
			if (GetTickCount() - ticker >= 100) {
				bar -= .01f; y -= 4; ticker = GetTickCount();
			}
			GRAPHICS::DRAW_RECT(0.25f, 0.75f - (bar / 2), 0.03f, bar, 255, y, 0, 255);

			float groundZ;
			GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(ENTITY::GET_ENTITY_COORDS(rocket, 1).x, ENTITY::GET_ENTITY_COORDS(rocket, 1).y, ENTITY::GET_ENTITY_COORDS(rocket, 1).z, &groundZ, 0);
			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(rocket) ||
				(std::abs(ENTITY::GET_ENTITY_COORDS(rocket, 1).z - groundZ) < .5f) ||
				bar <= 0.01) {
				auto impact_coord = ENTITY::GET_ENTITY_COORDS(rocket, 1); ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 0);
				FIRE::ADD_EXPLOSION(impact_coord.x, impact_coord.y, impact_coord.z, 0, 10.f, 1, 0, .4f);
				ENTITY::DELETE_ENTITY(&rocket);
				rocket = 0;
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 0);
				CAM::RENDER_SCRIPT_CAMS(0, true, 700, 1, 1);
				CAM::DESTROY_CAM(cam, 1);
				GRAPHICS::SET_TIMECYCLE_MODIFIER((char*)"DEFAULT");
				init = false;
			}
		}
	}
	if (!VALKYIREROCKET) {
		CAM::DESTROY_CAM(cam, 1);
		PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 0);
		rocket = 0;
		bar = .5f;
		y = 255;
		ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 0);
	}
}
bool Features::AimBool;
void Features::AimToDelete()
{
	if (IsPedShooting(PLAYER::PLAYER_PED_ID()))
	{
		Entity del_entity;
		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &del_entity))

			if (ENTITY::DOES_ENTITY_EXIST(del_entity) && NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(del_entity))
			{
				Vector3 tmp = ENTITY::GET_ENTITY_COORDS(del_entity, 1);
				ENTITY::DETACH_ENTITY(del_entity, 1, 1);
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(del_entity, 0, 0, 0, 0, 0, 0);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(del_entity, 0, 1);
				ENTITY::DELETE_ENTITY(&del_entity);
			}
	}
}



bool Features::MenuNotifyBool;
void Features::MenuNotify()
{

	//Get_events(74658346534, (char*)"Hypno");
	//Get_events(73858735564, (char*)"X-Force");
	//Get_events(7263263764, (char*)"Unknown");
	//Get_events(9939993233, (char*)"Explosive");
	//Get_events(7263263749, (char*)"Terror");
	//Get_events(72632637999, (char*)"Mister//ModzZ PC");
	//Get_events(7263268573, (char*)"Menace");
	//Get_events(7263437100, (char*)"Sodium");
	//Get_events(589401159237152, (char*)"Simfinity");
	//Get_events(8364956390, (char*)"DarkCheats");
}


bool Features::SentDetectionEventBool = true;
void Features::SentDetectionEvent()
{

	//if (NETWORK::NETWORK_IS_SESSION_ACTIVE())
	//{
	//	for (int i = 0; i < 32; i++)
	//	{
	//		int excludeMe = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
	//		if (excludeMe > 0 && excludeMe != PLAYER::PLAYER_PED_ID())
	//		{
	//			/*g_Logger->Info("Sent Detection Event");*/
	//			unsigned int Bit = (1 << i);
	//			DWORD64 kick[4] = { DETECT_MENU, i, 0, 0 };
	//			Hooks::TriggerScriptEvent(1, kick, 4, Bit);
	//		}
	//	}
	//}
}




bool Features::superman = false;
void Features::SuperMan()
{

	if (GetAsyncKeyState(VK_SPACE))
	{
		ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 10, 0, 0, 0, 1, true, true, true, true, true);
	}
	Hash hash = GAMEPLAY::GET_HASH_KEY("GADGET_PARACHUTE");
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 1, 1);

	if (ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_RAGDOLL(PLAYER::PLAYER_PED_ID()))
	{
		if (GetAsyncKeyState(0x57)) // W key
		{
			ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 3, 0, 0);
		}

		if (GetAsyncKeyState(0x53)) // S key
		{
			ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 3, 6, 0);
		}
		if (GetAsyncKeyState(VK_SHIFT))
		{
			ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 6, 0, 0);
		}
	}
}
void Features::OfficeMoney()
{
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_LIFETIME_CONTRA_EARNINGS"), 25000000, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_LIFETIME_CONTRA_EARNINGS"), 25000000, true);
	ScriptEventLog("You will need to sell at least a piece of stock in order for this to appear");
}
void Features::OfficeStatue()
{
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_LIFETIME_BUY_COMPLETE"), 2000, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_LIFETIME_BUY_UNDERTAKEN"), 2000, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_LIFETIME_SELL_COMPLETE"), 2000, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_LIFETIME_SELL_UNDERTAKEN"), 2000, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_LIFETIME_BUY_COMPLETE"), 2000, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_LIFETIME_BUY_UNDERTAKEN"), 2000, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_LIFETIME_SELL_COMPLETE"), 2000, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_LIFETIME_SELL_UNDERTAKEN"), 2000, true);
	ScriptEventLog("You may need to restart GTA:O for this to take effect!");
}


string GetPlayerWeapon(Player player)
{
	//Hash weaponHash;
	//WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), &weaponHash, 0);
	//switch (weaponHash)
	//{
	//	// melee
	//case -1569615261:
	//	return "Unarmed";
	//	break;
	//case -1716189206:
	//	return "Knife";
	//	break;
	//case 1737195953:
	//	return "Nightstick";
	//	break;
	//case 1317494643:
	//	return "Hammer";
	//	break;
	//case -1786099057:
	//	return "Bat";
	//	break;
	//case -2067956739:
	//	return "Crowbar";
	//	break;
	//case 1141786504:
	//	return "Golfclub";
	//	break;
	//case -102323637:
	//	return "Bottle";
	//	break;
	//case -1834847097:
	//	return "Dagger";
	//	break;
	//case -102973651:
	//	return "Hatchet";
	//	break;
	//case -656458692:
	//	return "Knuckle Duster";
	//	break;
	//case -581044007:
	//	return "Machete";
	//	break;
	//case -1951375401:
	//	return "Flashlight";
	//	break;
	//case -538741184:
	//	return "Switch Blade";
	//	break;
	//case -1810795771:
	//	return "Poolcue";
	//	break;
	//case 419712736:
	//	return "Wrench";
	//	break;
	//case -853065399:
	//	return "Battle Axe";
	//	break;
	//case 0x3813FC08:
	//	return "Stone Hatchet";
	//	break;
	//	// handguns
	//case 453432689:
	//	return "Pistol";
	//	break;
	//case 3219281620:
	//	return "Pistol Mk2";
	//	break;
	//case 1593441988:
	//	return "Combat Pistol";
	//	break;
	//case -1716589765:
	//	return "Pistol 50";
	//	break;
	//case -1076751822:
	//	return "SNS Pistol";
	//	break;
	//case 0x88374054:
	//	return "SNS Pistol Mk2";
	//	break;
	//case -771403250:
	//	return "Heavy Pistol";
	//	break;
	//case 137902532:
	//	return "Vintage Pistol";
	//	break;
	//case -598887786:
	//	return "Marksman Pistol";
	//	break;
	//case -1045183535:
	//	return "Revolver";
	//	break;
	//case 0xCB96392F:
	//	return "Revolver Mk2";
	//	break;
	//case 584646201:
	//	return "AP Pistol";
	//	break;
	//case 911657153:
	//	return "Stun Gun";
	//	break;
	//case 1198879012:
	//	return "Flare Gun";
	//	break;
	//case 0x97EA20B8:
	//	return "Double Action Revolver";
	//	break;
	//case 0xAF3696A1:
	//	return "Up-n-Atomizer";
	//	break;
	//	// machine guns
	//case 324215364:
	//	return "Micro SMG";
	//	break;
	//case -619010992:
	//	return "Machine Pistol";
	//	break;
	//case 736523883:
	//	return "SMG";
	//	break;
	//case 2024373456:
	//	return "SMG Mk2";
	//	break;
	//case -270015777:
	//	return "Assault SMG";
	//	break;
	//case 171789620:
	//	return "Combat PDW";
	//	break;
	//case -1660422300:
	//	return "MG";
	//	break;
	//case 2144741730:
	//	return "Combat MG";
	//	break;
	//case 368662592:
	//	return "Combat MG Mk2";
	//	break;
	//case 1627465347:
	//	return "Gusenberg";
	//	break;
	//case -1121678507:
	//	return "Mini SMG";
	//	break;
	//case 0x476BF155:
	//	return "Unholy Hellbringer";
	//	break;
	//	// assault rifles
	//case -1074790547:
	//	return "Assault Rifle";
	//	break;
	//case 961495388:
	//	return "Assault Rifle Mk2";
	//	break;
	//case -2084633992:
	//	return "Carbine Rifle";
	//	break;
	//case 4208062921:
	//	return "Carbine Rifle Mk2";
	//	break;
	//case -1357824103:
	//	return "Advanced Rifle";
	//	break;
	//case -1063057011:
	//	return "Special Carbine";
	//	break;
	//case 0x969C3D67:
	//	return "Special Carbine Mk2";
	//	break;
	//case 2132975508:
	//	return "Bullpup Rifle";
	//	break;
	//case 0x84D6FAFD:
	//	return "Bullpup Rifle Mk2";
	//	break;
	//case 1649403952:
	//	return "Compact Rifle";
	//	break;
	//	// Sniper Rifles
	//case 100416529:
	//	return "Sniper Rifle";
	//	break;
	//case 205991906:
	//	return "Heavy Sniper";
	//	break;
	//case 177293209:
	//	return "Heavy Sniper Mk2";
	//	break;
	//case -952879014:
	//	return "Marksman Rifle";
	//	break;
	//case 0x6A6C02E0:
	//	return "Marksman Rifle Mk2";
	//	break;
	//	// Shotguns
	//case 487013001:
	//	return "Pump Shotgun";
	//	break;
	//case 0x555AF99A:
	//	return "Pump Shotgun Mk2";
	//	break;
	//case 2017895192:
	//	return "Sawnoff Shotgun";
	//	break;
	//case -1654528753:
	//	return "Bullpup Shotgun";
	//	break;
	//case -494615257:
	//	return "Assault Shotgun";
	//	break;
	//case -1466123874:
	//	return "Musket";
	//	break;
	//case 984333226:
	//	return "Heavy Shotgun";
	//	break;
	//case -275439685:
	//	return "Double Barrel Shotgun";
	//	break;
	//case 317205821:
	//	return "Sweeper Shotgun";
	//	break;
	//	// Heavy Weapons
	//case -1568386805:
	//	return "Grenade Launcher";
	//	break;
	//case -1312131151:
	//	return "RPG";
	//	break;
	//case 1119849093:
	//	return "Minigun";
	//	break;
	//case 2138347493:
	//	return "Firework";
	//	break;
	//case 1834241177:
	//	return "Railgun";
	//	break;
	//case 1672152130:
	//	return "Homing Launcher";
	//	break;
	//case 1305664598:
	//	return "Grenade Launcher Smoke";
	//	break;
	//case 125959754:
	//	return "Compact Launcher";
	//	break;
	//case 0xB62D1F67:
	//	return "Widowmaker";
	//	break;
	//	// Thrown Weapons
	//case -1813897027:
	//	return "Grenade";
	//	break;
	//case 741814745:
	//	return "Sticky Bomb";
	//	break;
	//case -1420407917:
	//	return "Proximity Mine";
	//	break;
	//case -1600701090:
	//	return "BZ Gas";
	//	break;
	//case 615608432:
	//	return "Molotov";
	//	break;
	//case 101631238:
	//	return "Fire Extinguisher";
	//	break;
	//case 883325847:
	//	return "Petrol Can";
	//	break;
	//case 1233104067:
	//	return "Flare";
	//	break;
	//case 600439132:
	//	return "Ball";
	//	break;
	//case 126349499:
	//	return "Snowball";
	//	break;
	//case -37975472:
	//	return "Smoke Grenade";
	//	break;
	//case -1169823560:
	//	return "Pipebomb";
	//	break;
	//case -72657034:
	//	return "Parachute";
	//	break;

	//default:
	//	return "**UNKNOWN WEAPON**";
	//	break;
	//}
	return "**UNKNOWN**";
}

float Get3DDistance(Vector3 a, Vector3 b) {
	float x = pow((a.x - b.x), 2);
	float y = pow((a.y - b.y), 2);
	float z = pow((a.z - b.z), 2);
	return sqrt(x + y + z);
}



void Features::LoadPlayerInfo(int player) {
	Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
	g_UiManager->DrawInfoTitle(PLAYER::GET_PLAYER_NAME(player));
	Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, false);
	bool isConnected = NETWORK::NETWORK_IS_SESSION_ACTIVE();
	bool isInAnyVehicle = PED::IS_PED_IN_ANY_VEHICLE(ped, true);
	if (ped != PLAYER::PLAYER_PED_ID()) { GRAPHICS::DRAW_MARKER(2, coords.x, coords.y, coords.z + 1.3f, 0.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.3f, 0.3f, 0.3f, 169, 169, 169, 220, 1, 1, 1, 0, 0, 0, 0); }
	Hash street[2]{};
	PATHFIND::GET_STREET_NAME_AT_COORD(coords.x, coords.y, coords.z, &street[0], &street[1]);
	Vector3 selfCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
	float distance = get_distance(&selfCoords, &coords);
	float newDistance{};
	distance > 1000 ? newDistance = round((distance / 1000) * 100) / 100 : newDistance = round(distance * 1000) / 100;
	const char* headShot = "CHAR_MULTIPLAYER";

	int headshotIndex = 1389080;

	for (int x = 0; x <= 150; x += 5) {
		int playerId = globalHandle(headshotIndex).At(x).As<int>();

		if (playerId == player)
		{
			int logo = globalHandle(headshotIndex).At(x).At(1).As<int>();
			headShot = PED::GET_PEDHEADSHOT_TXD_STRING(logo);
		}
	}


	bool isHost = false;
	if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT((char*)"freemode", -1, 0) == player) {
		isHost = true;
	}

	std::string PlayerIP;

	char ipBuf[32] = {};

	static auto nigNog = (std::uintptr_t(*)(int))(Memory::pattern("40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C").count(1).get(0).get<void>(0));
	auto nigger = nigNog(player);

	auto faggot = *(uintptr_t*)(nigger + 0x10C8);
	auto ip = (BYTE*)(faggot + 0x44);
	std::snprintf(ipBuf, sizeof(ipBuf) - 1, "~r~IP: %u.%u.%u.%u", ip[3], ip[2], ip[1], *ip);
	PlayerIP = std::to_string(ip[3]) + "." + std::to_string(ip[2]) + "." + std::to_string(ip[1]) + "." + std::to_string(*ip);



	std::string port_str;
	auto port = reinterpret_cast<uint16_t*>(faggot + 0x1F4EBA0);
	char buffer[5 + 1];
	std::snprintf(buffer, sizeof(buffer), "%i", *port);
	port_str = buffer;



	float health = (float)ENTITY::GET_ENTITY_HEALTH(ped);
	float maxHealth = (float)ENTITY::GET_ENTITY_MAX_HEALTH(ped);
	float healthPercent = health * 100 / maxHealth;
	float armor = (float)PED::GET_PED_ARMOUR(ped);
	float maxArmor = (float)PLAYER::GET_PLAYER_MAX_ARMOUR(player);
	float armorPercent = armor * 100 / maxArmor;
	int rp = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(5).As<int>();
	int money = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(3).As<int>();
	int rank = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(6).As<int>();
	int kills = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(28).As<int>();
	int deaths = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(29).As<int>();
	int handle = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(56).As<int>();
	int handle2 = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(3).As<int>();
	int bank = handle - 10 - handle2 + (5 * 1 + 3 + 2);
	int raceswon = globalHandle(1590682).At(g_SelectedPlayer, 833).At(122).At(1).As<int>();
	int raceslost = globalHandle(1590682).At(g_SelectedPlayer, 833).At(122).At(1).At(1).As<int>();
	float kd = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(26).As<float>();
	int earnings = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(56).As<int>();
	int tempMoney = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(3).As<int>();
	int death = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(20).As<int>();
	int deathlost = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(21).As<int>();
	int races = globalHandle(1590682).At(g_SelectedPlayer, 833).At(211).At(15).As<int>();
	int isOtr = globalHandle(1590682).At(g_SelectedPlayer, 833).At(208).As<int>();





	Hash vehHash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(ped, 0));
	g_UiManager->AddInfoSprite("Headshot", isConnected ? headShot : "CHAR_MULTIPLAYER");
	g_UiManager->AddInfo("Invincible", PLAYER::GET_PLAYER_INVINCIBLE(player) ? "Yes" : "No");
	g_UiManager->AddInfo("Health", fmt::format("{0}%", healthPercent));
	g_UiManager->AddInfo("Armour", fmt::format("{0}%", armorPercent));
	g_UiManager->AddInfo("Alive", ENTITY::IS_ENTITY_DEAD(player) ? "No" : "Yes");

	if (isConnected)
	{
		g_UiManager->AddInfo("Money", fmt::format("${0}", money));
		g_UiManager->AddInfo("Bank", fmt::format("${0}", bank));
		g_UiManager->AddInfo("RP", fmt::format("{0}", rp));
		g_UiManager->AddInfo("Rank", fmt::format("{0}", rank));
		g_UiManager->AddInfo("Kills", fmt::format("{0}", kills));
		g_UiManager->AddInfo("Deaths", fmt::format("{0}", deaths));
		g_UiManager->AddInfo("Races-Won", fmt::format("{0}", raceswon));
		g_UiManager->AddInfo("Races-Lost", fmt::format("{0}", raceslost));
		g_UiManager->AddInfo("Earnings", fmt::format("{0}", earnings));
		g_UiManager->AddInfo("KD", fmt::format("{0}", kd));
		g_UiManager->AddInfo("IsHost", fmt::format("{0}", isHost ? "~r~Yes" : "No"));
		g_UiManager->AddInfo("IP", fmt::format("{0}", PlayerIP));
		g_UiManager->AddInfo("Port", fmt::format("{0}", port_str));
	}
	g_UiManager->AddInfo("Speed", fmt::format("{0} m/s", (round(isInAnyVehicle ? (ENTITY::GET_ENTITY_SPEED(vehicle) * 100) : (ENTITY::GET_ENTITY_SPEED(ped) * 100)) / 100)));
	g_UiManager->AddInfo("Vehicle", isInAnyVehicle ? UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehHash)) : "~r~Not In A Vehicle");

	g_UiManager->AddInfo("Wanted Level", fmt::format("{0}", PLAYER::GET_PLAYER_WANTED_LEVEL(player)));


	g_UiManager->AddInfo("Distance", fmt::format("{0} {1}", newDistance, distance > 1000 ? "Kilometers" : "Meters"));

	g_UiManager->AddInfo("Zone", UI::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(coords.x, coords.y, coords.z)));




	g_UiManager->AddInfo("Street", UI::GET_STREET_NAME_FROM_HASH_KEY(street[0]));


	int netHandle[13];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, netHandle, 13);
	char* UserID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);
	g_UiManager->AddInfo("Rockstar ID", fmt::format("{0}", UserID));
}