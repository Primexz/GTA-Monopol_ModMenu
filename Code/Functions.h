#pragma once
#include "Common.hpp"
#include "Natives.hpp"
#include "Types.hpp"
#include "Structs.h"
using namespace Big;
using namespace rage;
//=================
// PED FUNCTIONS
//=================
extern bool protex1;
extern int Join;
extern bool Joiner;
int getInputs();
char* getCharInput();
extern bool loggedin;
extern bool protex2;
extern int minimumchips;
extern int tradeinchips;
extern int maxchips;
extern bool ResearchUnlocks;
extern bool CayoPericoProt;
extern bool Modders[32];
extern bool protex3;
extern bool protex4;
extern bool Elite;
extern bool protex5;
extern bool m_Controller;
extern bool protex6;
extern bool IsKeyboardActive;
extern bool protex7;
extern bool protex8;
extern bool protex9;
extern bool protex10;
extern bool protex11;
extern bool protex12;
extern bool protex17;
extern int testa;
extern int testb;
extern int testc;
extern int testd;
extern int teste;
extern int testf;
extern int testg;
extern int testh;
extern int testi;
extern int testj;
extern int testk;
extern int testl;
extern int testm;
extern int testn;
extern int testo;
extern int32_t Spoiler, FBumper, RBumper, SSkirt, Exhaust, Grille, Chasis, Hood, Fender, RFender, Roof, Engine, Brakes, Transmission, Horns, Suspension, Armor, Turbo, TSmoke, Xenon, Wheels, Windows, Plateholder, Vanity, Trims, Ornaments, Dashboard, Dial, DoorSpeaker, Seats, SteeringWheel, Shifter, Plaques, Speakers, Trunk, Hydraulics, EngineBlock, Filter, Struts, Arch, Aerials, TrimTwo, Tank, Livery;
Player getPlayerId(const char* name);
extern Big::Vector3 get_blip_marker();
bool IsPlayerFriend(int player);
std::string PlayerName(int Player);
void SaveOutfit();
Ped ClonePed(Ped ped);
Ped CreatePed(char* PedName, Vector3 SpawnCoordinates, int ped_type, bool network_handle);

//Animations
extern std::string show_keyboard();
void LoadAnim(char * dict);
void playAnimation(Ped ped, bool loop, char * dict, char * anim);
void drawSprite(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
//SKINS
void ScriptEventLog(const std::string& text);
//void applyChosenSkin(string model);
bool isSolo();
//CONTROL
void RequestControlOfEnt(Entity entity);
uintptr_t	get_address_of_item_in_pool(MemoryPool* pool, int handle);
void RequestControlOfid(Entity netid);
Vector3 add(Vector3*vectorA, Vector3*vectorB);
void draw_noti(const std::string& text);

void WelcomeBannerBool(bool toggle);

Vector3 multiply(Vector3*vector, float x);
float get_distance(Vector3*pointA, Vector3*pointB);
float get_vector_length(Vector3*vector);
std::string float2string(float f);
void VectorToFloat(Vector3 unk, float *Out);
bool get_key_pressed(int nVirtKey);
void offset_from_entity(int entity, float X, float Y, float Z, float * Out);
void setupdraw(bool outline = 1);
extern int m_OpenKey;
extern int m_BackKey;
extern int m_EnterKey;
extern int m_UpKey;
const std::string GetModulePath(HMODULE module);
extern int m_ForwardBoost;
extern int m_BackwardBoost;
std::string get_input();
std::string get_all_asi_files(std::string asi_path);
extern int m_DownKey;
extern int m_LeftKey;
extern int m_RightKey;
void drawstring(char* text, float X, float Y);
void drawinteger(int text, float X, float Y);
void drawfloat(float text, DWORD decimal_places, float X, float Y, bool usetext);
void PlaySoundFrontend(char* sound_dict, char* sound_name);
void PlaySoundFrontend_default(char* sound_name);
bool Check_compare_string_length(char* unk1, size_t max_length);
int StringToInt(char* text);
void PrintBottomLeft(char* text);
void spawn_vehicle(const char* toSpawn, Ped player = PLAYER::PLAYER_PED_ID());
char* AddStrings(char* string1, char* string2);
char* AddInt_S(char* string1, int int2);
//FORCE
void ApplyForceToEntity(Entity e, float x, float y, float z);
void setFrameFlag(uint32_t flag);
void SetPlate();
void SetName();
extern std::string DocumentsPath();
extern std::string DocumentsPatha();
//GOD MODE
void GodMode(bool toggle);

//CALM PEDS

//NEARBY PEDS
void update_nearby_peds(Ped playerPed, int count);

//little one-line function called '$' to convert $TRING into a hash-key:
//Converts Radians to Degrees
float degToRad(float degs);

//quick function to get-coords-of-entity:
Vector3 coordsOf(Entity entity);

//quick function to get distance between 2 points:
float distanceBetween(Vector3 A, Vector3 B);


void WelcomeBannerLoop();
//quick "get random int in range 0-x" function:
int rndInt(int start, int end);

//TELEPORTATION
void teleport_to_marker();
void teleport_to_coords(Entity e, Vector3 coords);

//KEYBOARD
std::string show_keyboard(char* title_id, char* prepopulated_text);

//NOTIFICATION
void notifyMap(std::string msg, BOOL blink);

//VEHICLE