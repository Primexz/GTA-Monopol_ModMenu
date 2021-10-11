#pragma once
#include "Structs.h"
namespace Big
{
	typedef DWORD Void;
	typedef DWORD Any;
	typedef DWORD uint;
	typedef DWORD Hash;
	typedef int Entity;
	typedef int Player;
	typedef int FireId;
	typedef int Ped;
	typedef int Vehicle;
	typedef int Cam;
	typedef int CarGenerator;
	typedef int Group;
	typedef int Train;
	typedef int Pickup;
	typedef int Object;
	typedef int Weapon;
	typedef int Interior;
	typedef int Blip;
	typedef int Texture;
	typedef int TextureDict;
	//typedef int ObjectInfo;
	typedef int CoverPoint;
	typedef int Camera;
	typedef int TaskSequence;
	typedef int ColourIndex;
	typedef int Sphere;
	typedef int ScrHandle;

	class CEventMgr;
	struct clockTime {
		int hour, minute, second;
	};
	struct NetGameEvent_t
	{
		std::uint16_t m_Id;
		std::string m_Name;
		std::uint32_t m_Hash;
		void* m_Handler;

		explicit NetGameEvent_t(std::uint16_t id, std::string name, void* handler) :
			m_Id(id), m_Name(std::move(name)), m_Hash(/*Big::Joaat(m_Name.c_str())*/1), m_Handler(handler)
		{}
	};
#pragma pack(push, 1)
	struct Vector2
	{
		float x{};
		float y{};
	};
	typedef struct RGBAF {
		int r, g, b, a, f;
	};
	typedef struct VECTOR2_2 {
		float w, h;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct NativeVector3
	{
	public:
		NativeVector3() = default;
		NativeVector3(float x, float y, float z):
			x(x), y(y), z(z)
		{}
	public:
		float x{};
	private:
		char paddingX[4];
	public:
		float y{};
	private:
		char paddingY[4];
	public:
		float z{};
	private:
		char paddingZ[4];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Vector3
	{
		float x;
		DWORD _paddingx;
		float y;
		DWORD _paddingy;
		float z;
		DWORD _paddingz;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Color
	{
		std::uint8_t r{ 255 };
		std::uint8_t g{ 255 };
		std::uint8_t b{ 255 };
		std::uint8_t a{ 255 };
	};
#pragma pack(pop)
struct ObjectInfo
{
	DWORD hash;
	float X;
	float Y;
	float Z;
	float RotX;
	float RotY;
	float RotZ;
};
struct MemoryPool
{
	uintptr_t ListAddr;
	char* BoolAdr;
	int MaxCount;
	int ItemSize;
};
#pragma pack(push, 1)
typedef struct
{
	float x;
	float y;
	float z;
} Vector3_t;
#pragma pack(push, 1)
#pragma pack(pop)
}

struct Blip_t {
public:
	__int32 iID; //0x0000 
	__int8 iID2; //0x0004 
	char _0x0005[3];
	BYTE N000010FB; //0x0008 (80 = moves with player, some values will turn icon into map cursor and break it)
	char _0x0009[7];
	Big::Vector3 coords;
	char _0x001C[6];
	BYTE bFocused; //0x0022   (Focused? 0100 0000)
	char _0x0023[5];
	char* szMessage; //0x0028 If not null, contains the string of whatever the blip says when selected.
	char _0x0030[16];
	int iIcon; //0x0040
	char _0x0044[4];
	DWORD dwColor; //0x0048 (Sometimes works?)
	char _0x004C[4];
	float fScale; //0x0050 
	__int16 iRotation; //0x0054 Heading
	BYTE bInfoIDType; //0x0056 GET_BLIP_INFO_ID_TYPE
	BYTE bZIndex; //0x0057 
	BYTE bDisplay; //0x0058  Also Visibility 0010
	BYTE bAlpha; //0x0059
};//Size=0x005A

struct BlipList {
public:
	Blip_t* m_Blips[1500]; //0x0000 

};//Size=0x2F18