#include "Common.hpp"
#include "Natives.hpp"
#include "Types.hpp"
#include "Structs.h"
#include "Common.hpp"
#include "Types.hpp"
#include "Functions.h"
#include "Structs.H"
#include "Invoker.hpp"
#include "Natives.hpp"
#include <string>
#include <string.h>
#include <WinUser.h>
#include <xutility>
#include "ScriptCallback.hpp"
#include <KnownFolders.h>
#include <ShlObj.h>
#include <comutil.h>
#include "UI/UIManager.hpp"
#include "Fibers.hpp"
using namespace Big;
using namespace rage;
std::set<Ped> lastSeenPeds;
int minimumchips = 10;
int tradeinchips = 1;
int maxchips = 50000;
bool ResearchUnlocks = 0;
 int testa = 0;
 int testb = 0;
 int testc = 0;
 int testd = 0;
 int teste = 0;
 int testf = 0;
 int testg = 0;
 int testh = 0;
 int testi = 0;
 int testj = 0;
 int testk = 0;
 int testl = 0;
 int testm = 0;
 int testn = 0;
 int testo = 0;
 bool Elite = true;
int32_t Spoiler, FBumper, RBumper, SSkirt, Exhaust, Grille, Chasis, Hood, Fender, RFender, Roof, Engine, Brakes, Transmission, Horns, Suspension, Armor, Turbo, TSmoke, Xenon, Wheels, Windows, Plateholder, Vanity, Trims, Ornaments, Dashboard, Dial, DoorSpeaker, Seats, SteeringWheel, Shifter, Plaques, Speakers, Trunk, Hydraulics, EngineBlock, Filter, Struts, Arch, Aerials, TrimTwo, Tank, Livery = 0;
std::string get_all_asi_files(std::string asi_path)
{
	std::string asi_list{};
	for (auto& p : fs::recursive_directory_iterator(asi_path))
	{
		if (p.path().extension() == ".asi")
		{//
			asi_list = p.path().string();
		}
	}
	return asi_list;
}
const std::string GetModulePath(HMODULE module)
{
	std::string path;
	char buffer[MAX_PATH];
	GetModuleFileNameA(module, buffer, MAX_PATH);
	PathRemoveFileSpecA(buffer);
	path = buffer;
	return path;
}

std::string monopolstring() {
	char charlist[] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x3a, 0x2e, 0x2f, 0x2c, 0x3d, 0x26, 0x25, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x21, 0x3f, 0x2a, 0x2b, 0x2d, 0x5f, 0x23, 0x7e, 0x5c, 0x28, 0x29, 0x5b, 0x5d, 0x7b, 0x7d, 0x24, 0x60, 0x22, 0x3b };
	std::string x = "";
	int input[] = { 46, 67, 14, 67, 16, 67, 12 };
	for (int i = 0; i < sizeof(input) / sizeof(*input); i++) {
		if (input[i] == 0) x += 0x20;
		else x += charlist[input[i] - 1];
	}
	return x;
}

int getInputs()
{
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
		return stoi(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
}


char* getCharInput()
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(false, (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
	{
		IsKeyboardActive = true;
		g_UiManager->ResetInput();
		g_FiberScript->Wait(0);
	}
	IsKeyboardActive = false;
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
		return 0;
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}

//=================
// PED FUNCTIONS
//=================
void drawSprite(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}
/*
		m_OpenKeyPressed = IsKeyPressed(VK_MULTIPLY);
		m_BackKeyPressed = IsKeyPressed(VK_NUMPAD0) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel);
		m_EnterKeyPressed = IsKeyPressed(VK_NUMPAD5);
		m_UpKeyPressed = IsKeyPressed(VK_NUMPAD8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp);
		m_DownKeyPressed = IsKeyPressed(VK_NUMPAD2) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown);
		m_LeftKeyPressed = IsKeyPressed(VK_NUMPAD4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendLeft);
		m_RightKeyPressed = IsKeyPressed(VK_NUMPAD6) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendRight);

*/
bool IsKeyboardActive;
int m_OpenKey;
int m_clickkey;
int m_BackKey;
int m_EnterKey;
int m_UpKey;
int m_DownKey;
int m_LeftKey;
int m_RightKey;
int m_ForwardBoost;
int m_BackwardBoost;
bool m_Controller = false;


void ScriptEventLog(const std::string& text)
{
	//g_CallbackScript->AddCallback<TextureCallback>("MainTexture", [text] {
	//UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
	//UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	//char* role = (char*)"Free";
	//role = (char*)"~c~Free";
	//UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2((char*)"MainTexture", (char*)"logo", 1, 8, (char*)monopolstring().c_str(), role, 0.5, (char*)"___Menu", 9, 0);
	//UI::_DRAW_NOTIFICATION(FALSE, FALSE);
//});
}
Ped ClonePed(Ped ped)
{
	if (ENTITY::DOES_ENTITY_EXIST(ped) && !ENTITY::IS_ENTITY_DEAD(ped))
	{
		return PED::CLONE_PED(ped, ENTITY::GET_ENTITY_HEADING(ped), 1, 1);
	}

	return 0;
}
void setFrameFlag(uint32_t flag)
{
	auto actual = Memory::get_value<uint32_t>({ 0x8, 0x10B8, 0x1F8 });
	Memory::set_value<uint32_t>({ 0x8, 0x10B8, 0x1F8 }, actual |= flag);
}
Ped CreatePed(char* PedName, Vector3 SpawnCoordinates, int ped_type, bool network_handle)
{
	Ped NewPed;
	int PedHash = GAMEPLAY::GET_HASH_KEY(PedName);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(PedHash))
	{
		if (STREAMING::IS_MODEL_VALID(PedHash))
		{
			STREAMING::REQUEST_MODEL(PedHash);
			while (!STREAMING::HAS_MODEL_LOADED(PedHash)) 

			NewPed = PED::CREATE_PED(ped_type, PedHash, SpawnCoordinates.x, SpawnCoordinates.y, SpawnCoordinates.z, 0, network_handle, 1);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);
			return NewPed;
		}
	}

	return -1;
}

//Animations
void LoadAnim(char * dict)
{
	int tick = 0;
	STREAMING::REQUEST_ANIM_DICT(dict);
	while (tick < 100 && !STREAMING::HAS_ANIM_DICT_LOADED(dict))
	{
		tick++;
		
	}
}

void playAnimation(Ped ped, bool loop, char * dict, char * anim)
{
	LoadAnim(dict);
	int a = -1;
	int b = 1;

	if (!loop)
	{
		a = 1;
		b = 0;
	}

	AI::TASK_PLAY_ANIM(ped, dict, anim, 10000.0f, -1.5f, a, b, 0.445f, false, false, false);

}
//Skins
void applyChosenSkin(string model)
{
	Hash hash = GAMEPLAY::GET_HASH_KEY(model);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash))
	{
		g_CallbackScript->AddCallback<ModelCallback>(hash, [hash] {
			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), hash);
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
		});
	}
}
Vector3 add(Vector3 vectorA, Vector3 vectorB) {
	Vector3 result;
	result.x = vectorA.x;
	result.y = vectorA.y;
	result.z = vectorA.z;
	result.x += vectorB.x;
	result.y += vectorB.y;
	result.z += vectorB.z;
	return result;
}

Vector3 multiply(Vector3*vector, float x) {
	Vector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}

float get_distance(Vector3*pointA, Vector3*pointB) {
	float a_x = pointA->x;
	float a_y = pointA->y;
	float a_z = pointA->z;
	float b_x = pointB->x;
	float b_y = pointB->y;
	float b_z = pointB->z;
	double x_ba = (double)(b_x - a_x);
	double y_ba = (double)(b_y - a_y);
	double z_ba = (double)(b_z - a_z);
	double y_2 = y_ba * y_ba;
	double x_2 = x_ba * x_ba;
	double sum_2 = y_2 + x_2;
	return(float)sqrt(sum_2 + z_ba);
}

float get_vector_length(Vector3*vector) {
	double x = (double)vector->x;
	double y = (double)vector->y;
	double z = (double)vector->z;
	return(float)sqrt(x*x + y * y + z * z);
}
//CONTROL
void RequestControlOfid(Entity netid)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		tick++;
	}
}


void Sprite(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}
int VAR_INSTRUCTIONAL_CONTAINER;
int VAR_INSTRUCTIONAL_COUNT;

void InstructionsInit() {
	VAR_INSTRUCTIONAL_COUNT = 0;
	VAR_INSTRUCTIONAL_CONTAINER = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(VAR_INSTRUCTIONAL_CONTAINER, 255, 255, 255, 0, 0);
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(VAR_INSTRUCTIONAL_CONTAINER, "CLEAR_ALL");
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(VAR_INSTRUCTIONAL_CONTAINER, "SET_CLEAR_SPACE");
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(200);
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}



void InstructionsAdd(char* text, int button) {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(VAR_INSTRUCTIONAL_CONTAINER, "SET_DATA_SLOT");
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(VAR_INSTRUCTIONAL_COUNT);
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(button);
	GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	VAR_INSTRUCTIONAL_COUNT++;
}
void InstructionsEnd() {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(VAR_INSTRUCTIONAL_CONTAINER, "DRAW_INSTRUCTIONAL_BUTTONS");
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(VAR_INSTRUCTIONAL_CONTAINER, "SET_BACKGROUND_COLOUR");
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(80);
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}

float position_y_of_h = -0.1f;
unsigned int cnt = 0;
void WelcomeBannerBool(bool toggle) {
//	auto string1 = skCrypt("~g~Monopol ~w~Menu\n ~b~Version 1.4");
//	auto string2 = skCrypt("mp_big_message_freemode");
//	auto string3 = skCrypt("SHOW_SHARD_WASTED_MP_MESSAGE");
//	auto string4 = skCrypt("ursprite stream");
//	auto string5 = skCrypt("ursprite text");
//
//
//
//	int gay = GRAPHICS::REQUEST_SCALEFORM_MOVIE(string2.decrypt());
//	GRAPHICS::_END_SCALEFORM_MOVIE_METHOD_RETURN();
//	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(gay, string3.decrypt());
//	Sprite(string4.decrypt(), string5.decrypt(), 0.1f, position_y_of_h, 0, 0, 0, 255, 255, 255, 255); //} // you ened to fi
//	char* _elem = string1.decrypt();
//	GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_STRING(_elem);
//	GRAPHICS::_END_SCALEFORM_MOVIE_METHOD_RETURN();
//	GRAPHICS::DRAW_SCALEFORM_MOVIE(gay, .5f, position_y_of_h, 1.4, 1.4, 255, 255, 255, 255, 1);
//
//	string1.clear();
//	string2.clear();
//	string3.clear();
//	string4.clear();
//	string5.clear();
//}
//
//
//void WelcomeBannerLoop()
//{
//	if (cnt < 1500)
//	{
//		if (position_y_of_h <= .3f)
//		{
//			position_y_of_h += 0.003f;
//		}
//		WelcomeBannerBool(true);
//		cnt++;
//	}
}

void RequestControlOfEnt(Entity entity)
{
	int tick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		RequestControlOfid(netID);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
	}
}

//FORCE
void ApplyForceToEntity(Entity e, float x, float y, float z)
{
	if (e != PLAYER::PLAYER_PED_ID() && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == FALSE)
	{
		RequestControlOfEnt(e);
	}

	ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);

}

//GOD MODE
void GodMode(bool toggle)
{
	static int armour_player = 0;
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (armour_player == 0)
	{
		armour_player = PED::GET_PED_ARMOUR(playerPed);
	}

	if (toggle)
	{
		//set_status_text("Activating godmode");
		PLAYER::SET_PLAYER_INVINCIBLE(player, true);
		ENTITY::SET_ENTITY_PROOFS(playerPed, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
		PED::SET_PED_CAN_RAGDOLL(playerPed, FALSE);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, FALSE);
		PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
	}
	else
	{
		//set_status_text("Deactivating godmode");
		PLAYER::SET_PLAYER_INVINCIBLE(player, false);
		ENTITY::SET_ENTITY_PROOFS(playerPed, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
		PED::SET_PED_CAN_RAGDOLL(playerPed, TRUE);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, TRUE);
		if (armour_player != 0)
		{
			PED::SET_PED_ARMOUR(playerPed, armour_player);
			armour_player = 0;
		}
	}
}

//NEARBY PEDS

void update_nearby_peds(Ped playerPed, int count)
{
	const int numElements = count;
	const int arrSize = numElements * 2 + 2;

	Ped *peds = new Ped[arrSize];
	peds[0] = numElements;
	int found = PED::GET_PED_NEARBY_PEDS(playerPed, peds, -1);

	for (int i = 0; i < found; i++)
	{
		int offsettedID = i * 2 + 2;

		if (!ENTITY::DOES_ENTITY_EXIST(peds[offsettedID]))
		{
			continue;
		}

		Ped xped = peds[offsettedID];

		bool inSet = lastSeenPeds.find(xped) != lastSeenPeds.end();
		if (!inSet)
		{
			lastSeenPeds.insert(xped);
		}
	}
	std::set<Ped>::iterator it;
	for (it = lastSeenPeds.begin(); it != lastSeenPeds.end();)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(*it))
		{
			lastSeenPeds.erase(it++);
		}
		else
		{
			++it;
		}
	}

	delete peds;
}

//CALM PEDS

//Converts Radians to Degrees
float degToRad(float degs)
{
	return degs * 3.141592653589793f / 180.f;
}
//little one-line function called '$' to convert $TRING into a hash-key:

// quick function to get - coords - of - entity:
Vector3 coordsOf(Entity entity) {
	return ENTITY::GET_ENTITY_COORDS(entity, 1);
}

//quick function to get distance between 2 points: eg - if (distanceBetween(coordsOf(player), targetCoords) < 50)
float distanceBetween(Vector3 A, Vector3 B) {
	return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
}

//quick "get random int in range 0-x" function:
int rndInt(int start, int end) {
	return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(start, end);
}

//TELEPORTATION
void teleport_to_coords(Entity e, Vector3 coords)
{
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
	
}

Big::Vector3 get_blip_marker()
{
	static Vector3 zero;
	Vector3 coords;

	bool blipFound = false;
	// search for marker blip
	int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
	for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
	{
		if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
		{
			coords = UI::GET_BLIP_INFO_ID_COORD(i);
			blipFound = true;
			break;
		}
	}
	if (blipFound)
	{
		return coords;
	}

	return zero;
}
bool protex1 = false;
bool protex2 = false;
bool protex3 = false;
bool protex4 = false;
bool CayoPericoProt = false;
bool protex5 = false;
bool protex6 = false;
bool protex7 = false;
bool protex8 = false;
bool protex9 = false;
bool protex10 = false;
bool protex11 = false;
bool protex12 = false;
bool protex17 = false;
double startTime = GetTickCount();
void NEWWAIT(int ms)
{
	int delay = GAMEPLAY::GET_GAME_TIMER() + ms;
	while (GAMEPLAY::GET_GAME_TIMER() == delay)
	{
		return;
	}
}
CBlip*	get_blip_waypoint()
{
	CBlip* r = nullptr;
	for (int i = 0; i < 0x400; i++)
	{
		CBlip*	blip = g_GameVariables->m_blipList->m_Blips[i];
		if (blip == nullptr
			|| blip->dwColor != ColorWaypoint
			|| blip->iIcon != SpriteWaypoint)
			continue;

		r = blip;
		break;
	}
	return r;
}
bool loggedin = true;
std::string token  = "NULL";
void teleport_to_marker() { // Sudomod way

	g_FiberScript->addTask([]() {
		Vector3 coords = get_blip_marker();
		Ped ped = PLAYER::PLAYER_PED_ID();

		if (coords.x == 0 && coords.y == 0)
		{
			return;
		}

		if (PED::IS_PED_IN_ANY_VEHICLE(ped, 0))
			ped = PED::GET_VEHICLE_PED_IS_USING(ped);

		bool isGroundAvailable = false;
		std::vector<float> GROUND_HEIGHT{ 100.0f, 150.0f, 50.0f, 0.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f };

		for (int i = 0; i < GROUND_HEIGHT.size(); i++)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, GROUND_HEIGHT[i], 0, 0, 1);



			if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, GROUND_HEIGHT[i], &coords.z, 0))
			{
				isGroundAvailable = true;
				coords.z += 3.0;
				break;
			}
		}
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, 0, 0, 1);
	});
}
bool Modders[32];
bool IsPlayerFriend(int player)
{
	BOOL BplayerFriend = false;
	bool bplayerFriend = false;
	int handle[76]; //var num3 = sub_34009(A_0, (A_1) + 264, (A_1) + 272);
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13))
	{
		BplayerFriend = NETWORK::NETWORK_IS_FRIEND(&handle[0]);
	}
	if (BplayerFriend == 1)
		bplayerFriend = true;
	else
		bplayerFriend = false;

	return bplayerFriend;
}
std::string PlayerName(int Player) {
	if (IsPlayerFriend(Player)) {
		if (Modders[Player])
		{
			return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~g~[FRIEND] ~r~[Modder]";
		}
		return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~g~[FRIEND]";
	}
	else {
		if (Modders[Player])
		{
			return PLAYER::GET_PLAYER_NAME(Player) + (std::string)" ~r~[Modder]";
		}
		return PLAYER::GET_PLAYER_NAME(Player);
	}
}
enum eKeyboardOwner
{
	KBOWNER_NONE,
	KBOWNER_LICENSE,
	KBOWNER_NAMECHANGE,
};
void	show_ingame_keyboard(char* title, char* default_text)
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)(title == nullptr ? monopolstring().c_str() : title), (char*)"", (char*)(default_text == nullptr ? "" : default_text), (char*)"", (char*)"", (char*)"", 64);
}
bool	get_ingame_keyboard_result(std::string& str)
{
	str = "Failed";
	bool r = !!GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD();
	if (r)
		str = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
	return r;
}
bool	ingame_keyboard(std::string& out, eKeyboardOwner owner, bool reset)
{
	static bool				active = false;
	static eKeyboardOwner	curOwner = KBOWNER_NONE;
	if (reset)
	{
		show_ingame_keyboard((char*)"Insert Text", (char*)"Insert Text");
		curOwner = owner;
		active = true;
	}
	if (curOwner != owner)
		return true;
	if (active && curOwner != KBOWNER_NONE)
	{
		std::string str;
		get_ingame_keyboard_result(str);
		if (str != "!!INVALID!!" && str != "")
		{
			out = str;
			curOwner = KBOWNER_NONE;
			active = false;
		}
	}
	return !active;
}
Player getPlayerId(const char* name)
{
	for (int i = 0; i < 32; i++)
	{
		if (PLAYER::GET_PLAYER_NAME(i) == name)
			return i;
	}
	return -1;
}
bool isSolo()
{
	//if (NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS() == 1) //Deteccccc native
	//{
	//	return true;
	//}
	return false;
}
void SetPlate()
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Set Plate:", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 32);
	g_CallbackScript->AddCallback<KeyboardCallback>("Multi",[] {
	});
}
void SetName()
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Set Name:", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 32);
	g_CallbackScript->AddCallback<KeyboardCallback>("NAME",[] {
	});

}
void SaveOutfit()
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Name Outfit:", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 32);
	g_CallbackScript->AddCallback<KeyboardCallback>("OUTFIT",[] {
	});
}
//In Game KEYBOARD


std::string get_input()
{
	g_FiberScript->addTask([]() {
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 32);
	while (!GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD())
	{
			g_FiberScript->Wait(0);
	}
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
		return (char*)"";
	return (char*)GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
	});
	return 0;
}


std::string show_keyboard()
{
	DWORD time = GetTickCount() + 400;
	while (GetTickCount() < time)
	{
		
	}

	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)(monopolstring().c_str() == NULL ? "HUD_TITLE" : ""), (char*)"", (char*)("" == NULL ? "" : ""), (char*)"", (char*)"", (char*)"", 64);

	std::stringstream ss;
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
	{
		return std::string("");
	}
	else
	{
		return std::string(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
	}
}

//VEHICLE

//NOTIFICATIONS
void notifyMap(std::string msg, BOOL blink) {
	UI::SET_TEXT_OUTLINE();
	UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(&msg[0u]);
	UI::_DRAW_NOTIFICATION(blink, FALSE);
}

Vector3 GetCoordsFromCam(float distance)
{
	Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	static Vector3 Coord = CAM::GET_GAMEPLAY_CAM_COORD();

	Rot.y = distance * cos(Rot.x);
	Coord.x = Coord.x + Rot.y * sin(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * cos(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * sin(Rot.x);

	return Coord;
}
std::string float2string(float f) {
	std::ostringstream ss;
	ss << f;
	std::string str(ss.str());
	return str;
}
void VectorToFloat(Vector3 unk, float *Out)
{
	Out[0] = unk.x;
	Out[1] = unk.y;
	Out[2] = unk.z;
}
bool get_key_pressed(int nVirtKey)
{
	return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0;
}
void offset_from_entity(int entity, float X, float Y, float Z, float * Out)
{
	VectorToFloat(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, X, Y, Z), Out);
}
void setupdraw(bool outline)
{
	UI::SET_TEXT_FONT(1);
	UI::SET_TEXT_SCALE(0.4f, 0.4f);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	if (outline)
	{
		UI::SET_TEXT_OUTLINE();
	}
}
void drawstring(char* text, float X, float Y)
{
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(X, Y);
}
void drawinteger(int text, float X, float Y)
{
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"NUMBER");
	UI::ADD_TEXT_COMPONENT_INTEGER(text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(X, Y);
}
void drawfloat(float text, DWORD decimal_places, float X, float Y, bool usetext)
{
	if (usetext)
	{
		char* strn = &float2string(text)[0u];
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(strn);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(X, Y);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"NUMBER");
		UI::ADD_TEXT_COMPONENT_FLOAT(text, decimal_places);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(X, Y);
	}
	else
	{
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"NUMBER");
		UI::ADD_TEXT_COMPONENT_FLOAT(text, decimal_places);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(X, Y);
	}
}
void PlaySoundFrontend(char* sound_dict, char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, sound_dict, 0);
}
void PlaySoundFrontend_default(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}
bool Check_compare_string_length(char* unk1, size_t max_length)
{
	if (strlen(unk1) <= max_length) return true; else return false;
}





int StringToInt(char* text)
{
	int tempp;
	if (text == "") return NULL;
	if (GAMEPLAY::STRING_TO_INT(text, &tempp)) return NULL;

	return tempp;
}
uintptr_t	get_address_of_item_in_pool(MemoryPool* pool, int handle)
{
	if (pool == nullptr)
		return 0;

	int index = handle >> 8;
	int flag = pool->BoolAdr[index];

	if (flag & 0x80 || flag != (handle & 0xFF))
		return 0;

	return pool->ListAddr + index * pool->ItemSize;
}
void draw_noti(const std::string& text)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2((char*)"CHAR_SOCIAL_CLUB", (char*)"CHAR_SOCIAL_CLUB", true, 5, (char*)monopolstring().c_str(),
		(char*)"", 1.f, (char*)"", 5, 0);
	UI::_DRAW_NOTIFICATION(false, false);
}
void PrintBottomLeft(char* text)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::_SET_NOTIFICATION_FLASH_COLOR(255, 0, 0, 255);
	UI::_DRAW_NOTIFICATION(0, 1);
}
int Join = 0;
bool Joiner;
void spawn_vehicle(const char* toSpawn, Ped player) {
	globalHandle(4269479).As<bool>() = true;
	globalHandle(4268340).At(43).As<bool>() = true;

	Hash model = GAMEPLAY::GET_HASH_KEY(toSpawn);
	if (STREAMING::IS_MODEL_VALID(model))
	{
		g_CallbackScript->AddCallback<ModelCallback>(model, [model, player] {
			Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(player, false);
			float heading = ENTITY::GET_ENTITY_HEADING(player);
			ourCoords.x + 5;
			Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords, heading, *g_GameVariables->is_session_started, false);
	
			RequestControlOfEnt(veh);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			DECORATOR::DECOR_SET_INT(veh, (char*)"MPBitset", 0);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			if (player == PLAYER::PLAYER_PED_ID())
			{
				if(Features::SpawnEffect) { STREAMING::REQUEST_NAMED_PTFX_ASSET((char*)"scr_rcbarry2"); GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL((char*)"scr_rcbarry2"); GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY((char*)"scr_clown_appears", veh, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, false, false, false); }
				if (Features::SpawnInCar) { PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1); }
				if (Features::SpawnMaxed) {

					VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
					for (int i = 0; i < 50; i++)
					{
						VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
					}
				}
			}
		});
	}
	else
	{
		ScriptEventLog("This Vehicle is not valid!");
	}
}
std::string DocumentsPath()
{
	return "";
}
std::string DocumentsPatha()
{

	return "";
}
char str[69];
char* AddStrings(char* string1, char* string2)
{
	memset(str, 0, sizeof(str));
	strcpy_s(str, "");
	strcpy_s(str, string1);
	strcat_s(str, string2);
	return str;
}
char* AddInt_S(char* string1, int int2)
{
	char* Return;
	printf_s(Return, "%i", int2);
	Return = AddStrings(string1, Return);
	return Return;
}
#pragma region Icons
const char* CHAR_DEFAULT = "CHAR_DEFAULT"; /* Default profile pic*/
const char* CHAR_FACEBOOK = "CHAR_FACEBOOK"; /* Facebook*/
const char* CHAR_SOCIAL_CLUB = "CHAR_SOCIAL_CLUB"; /* Social Club Star*/
const char* CHAR_CARSITE2 = "CHAR_CARSITE2"; /* Super Auto San Andreas Car Site*/
const char* CHAR_BOATSITE = "CHAR_BOATSITE"; /* Boat Site Anchor*/
const char* CHAR_BANK_MAZE = "CHAR_BANK_MAZE"; /* Maze Bank Logo*/
const char* CHAR_BANK_FLEECA = "CHAR_BANK_FLEECA"; /* Fleeca Bank*/
const char * CHAR_BANK_BOL = "CHAR_BANK_BOL"; /* Bank Bell Icon*/
const char * CHAR_MINOTAUR = "CHAR_MINOTAUR"; /* Minotaur Icon*/
const char * CHAR_EPSILON = "CHAR_EPSILON"; /* Epsilon E*/
const char * CHAR_MILSITE = "CHAR_MILSITE"; /* Warstock W*/
const char * CHAR_CARSITE = "CHAR_CARSITE"; /* Legendary Motorsports Icon*/
const char * CHAR_DR_FRIEDLANDER = "CHAR_DR_FRIEDLANDER"; /* Dr Freidlander Face*/
const char * CHAR_BIKESITE = "CHAR_BIKESITE"; /* P&M Logo*/
const char * CHAR_LIFEINVADER = "CHAR_LIFEINVADER"; /* Liveinvader*/
const char * CHAR_PLANESITE = "CHAR_PLANESITE"; /* Plane Site E*/
const char * CHAR_MICHAEL = "CHAR_MICHAEL"; /* Michael's Face*/
const char * CHAR_FRANKLIN = "CHAR_FRANKLIN"; /* Franklin's Face*/
const char * CHAR_TREVOR = "CHAR_TREVOR"; /* Trevor's Face*/
const char * CHAR_SIMEON = "CHAR_SIMEON"; /* Simeon's Face*/
const char * CHAR_RON = "CHAR_RON"; /* Ron's Face*/
const char * CHAR_JIMMY = "CHAR_JIMMY"; /* Jimmy's Face*/
const char * CHAR_LESTER = "CHAR_LESTER"; /* Lester's Shadowed Face*/
const char * CHAR_DAVE = "CHAR_DAVE"; /* Dave Norton's Face*/
const char * CHAR_LAMAR = "CHAR_LAMAR"; /* Chop's Face*/
const char * CHAR_DEVIN = "CHAR_DEVIN"; /* Devin Weston's Face*/
const char * CHAR_AMANDA = "CHAR_AMANDA"; /* Amanda's Face*/
const char * CHAR_TRACEY = "CHAR_TRACEY"; /* Tracey's Face*/
const char * CHAR_STRETCH = "CHAR_STRETCH"; /* Stretch's Face*/
const char * CHAR_WADE = "CHAR_WADE"; /* Wade's Face*/
const char * CHAR_MARTIN = "CHAR_MARTIN"; /* Martin Madrazo's Face*/
#pragma endregion
