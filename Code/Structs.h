#pragma once
#include "Types.hpp"
#include "srcEngine.h"
//Addresses from GTAV.exe module
#ifdef __SC_VERSION__
#define ADDRESS_WORLD					0x2328EC8		//42
#define ADDRESS_WAYPOINT				0x1F7F400		//wtb a (mini)map struct
#define ADDRESS_OBJECTIVE				0x1F7F4B0
#define ADDRESS_AMMO					0x0F706C5		//Ammo dec code; 41 2B D1 E8; 90 90 90 E8
#define ADDRESS_MAGAZINE				0x0F70680		//Magazine dec code; 41 2B C9 3B C8 0F; 90 90 90 3B C8 0F
#endif
#ifdef __STEAM_VERSION__
#define ADDRESS_WORLD					0x024CD000 //0x232BC00
#define ADDRESS_WAYPOINT				0x1F7A860 //0x1F82460
#define ADDRESS_OBJECTIVE				0x1F82510
#define ADDRESS_AMMO					0x0F71C38
#define ADDRESS_MAGAZINE				0x0F71C7D
#endif


//offset from WORLD
#define OFFSET_PLAYER					0x08			//playerbase

//entity offsets
#define OFFSET_ENTITY_POSBASE			0x30			//base of a structure that contains entity coords
#define OFFSET_ENTITY_POSBASE_POS		0x50			//vector3
#define OFFSET_ENTITY_POS				0x90			//vector3
#define OFFSET_ENTITY_HEALTH			0x280			//entity health (except for vehicles); float cur, float max
#define OFFSET_ENTITY_HEALTH_MAX		0x2A0			//they moved this away from curHealth in 1.36 :(
#define OFFSET_ENTITY_ATTACKER			0x2A8			//base to a list of the last 3 entities that attacked the current entity
#define OFFSET_ENTITY_GOD				0x189			//godmode; on = 1, off = 0; byte

//player (entity) offsets
#define OFFSET_PLAYER_ARMOR						0x14B8			//armour
#define OFFSET_PLAYER_INFO						0x10C8			//playerInfo struct
#define OFFSET_PLAYER_INFO_WANTED_CAN_CHANGE	0x71C			//fWantedCanChange
#define OFFSET_PLAYER_INFO_WANTED				0x868			//wanted level; DWORD
#define	OFFSET_PLAYER_INFO_RUN_SPD				0x0CD0			//run speed; def 1; float
#define OFFSET_PLAYER_INFO_SWIM_SPD				0x0150			//swim speed; def 1; float
#define OFFSET_PLAYER_INFO_FRAMEFLAGS			0x01F9			//frame flags; DWORD
#define OFFSET_PLAYER_INFO_STAMINA				0x0CD4			//fStamina, fStaminaMax
#define OFFSET_PLAYER_VEHICLE					0xD28			//ptr to last used vehicle
#define OFFSET_PLAYER_NAME						0x7C
#define OFFSET_PLAYER_RAGDOLL					0x10A8			//byte; CPed.noRagdoll: 0x20 = off; 0x00/0x01 = on
#define OFFSET_PLAYER_SEATBELT					0x13EC			//byte; CPed.seatBelt: 0xC8 = off; 0xC9 = on
#define OFFSET_PLAYER_INVEHICLE					0x146B

//vehicle offsets
#define OFFSET_VEHICLE_HEALTH						0x84C			//vehicle health; 0.f-1000.f
#define OFFSET_VEHICLE_GRAVITY						0xB7C			//fGravity
#define OFFSET_VEHICLE_BULLETPROOF_TIRES			0x8D3			//btBulletproofTires;  (btBulletproofTires & 0x20) ? true : false
#define OFFSET_VEHICLE_HANDLING						0x938
#define OFFSET_VEHICLE_HANDLING_ACCELERATION		0x4C
#define OFFSET_VEHICLE_HANDLING_BRAKEFORCE			0x6C
#define OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_MIN	0x90			//fTractionCurveMin
#define OFFSET_VEHICLE_HANDLING_DEFORM_MULTIPLIER	0xF8			//fDeformationDamageMult
#define OFFSET_VEHICLE_HANDLING_UPSHIFT				0x58
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_FORCE	0xBC			//fSuspensionForce 

//weapon offsets
#define OFFSET_WEAPON_MANAGER			0x10D8			//from playerbase
#define OFFSET_WEAPON_CURRENT			0x20			//from weapon manager
#define OFFSET_WEAPON_AMMOINFO			0x48			//from weaponbase
#define OFFSET_WEAPON_AMMOINFO_MAX		0x28			//ammoinfo
#define OFFSET_WEAPON_AMMOINFO_CUR_1	0x08			//ptr lvl 1, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CUR_2	0x00			//ptr tr lvl 2, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CURAMMO	0x18			//offset to cur ammo
#define OFFSET_WEAPON_AMMOINFO_TYPE		0x0C			//offset to projectile type?
#define OFFSET_WEAPON_SPREAD			0x70			//float set to 0
#define OFFSET_WEAPON_BULLET_DMG		0x98			//float times 10 (so when 0, it will stay 0)
#define OFFSET_WEAPON_RELOAD_MULTIPLIER	0x13C			//float times 10
#define OFFSET_WEAPON_RECOIL			0x2A4			//float set to 0
#define OFFSET_WEAPON_MODEL_HASH		0x14
#define OFFSET_WEAPON_NAME_HASH			0x10
#define OFFSET_WEAPON_RELOAD_VEHICLE	0x110
#define OFFSET_WEAPON_RANGE				0x25C
#define OFFSET_WEAPON_SPINUP			0x124
#define OFFSET_WEAPON_SPIN				0x128
#define OFFSET_WEAPON_BULLET_BATCH		0x100			//dwBulletInBatch
#define OFFSET_WEAPON_MUZZLE_VELOCITY	0xFC			//fMuzzleVelocity
#define OFFSET_WEAPON_BATCH_SPREAD		0x104			//fBatchSpread

#define OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_B          0x3A0           //btNeonLightBlue
#define OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_L         0x402           //btNeonLightLeft; 0x0 = off; 0x1 = on
#define OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_R         0x403           //btNeonLightRight; 0x0 = off; 0x1 = on
#define OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_F         0x404           //btNeonLightFront; 0x0 = off; 0x1 = on
#define OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_B         0x405
#define OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_R          0x3A2           //btNeonLightRed
#define OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_G          0x3A1           //btNeonLightGreen
#define OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_B          0x3A0           //btNeonLightBlue
#define OFFSET_ATTACKER_DISTANCE		0x18			//changed to 0x18, from 0x10
typedef struct
{
	float x, y;
} vector2;
typedef struct
{
	float x, y, w, h;
} vector4;
typedef struct
{
	int r, g, b, a;
} rgba;
typedef struct
{
	int r, g, b, a, f;
} rgbaf;
struct ScInAddr
{
	uint64_t unkKey1;
	uint64_t unkKey2;
	uint32_t secKeyTime; // added in 393
	uint32_t ipLan;
	uint16_t portLan;
	uint32_t ipUnk;
	uint16_t portUnk;
	uint32_t ipOnline;
	uint16_t portOnline;
	uint16_t pad3;
	uint32_t newVal; // added in 372
	uint64_t rockstarAccountId; // 463/505 addition - really R*? given this field one could easily replace everything with a Steam-like implementation only passing around user IDs...
};


struct ScPlayerData
{
	ScInAddr addr;
};
class CNetworkPlayer
{
public:
	virtual ~CNetworkPlayer() = 0;

	virtual void Reset() = 0;

	virtual void m_10() = 0;

	virtual const char* GetName() = 0;

	virtual void m_20() = 0;

	virtual void m_28() = 0;

	// contains ScInAddr as well
	virtual ScPlayerData* GetPlatformPlayerData() = 0;
};
class CWorld;
class CPed;
class CNavigation;
class CWorld_Wrap;
class CAttacker;
class CVehicle;
class CPlayerInfo;
class CWeaponManager;
class CWeapon;
class CAmmoInfo;
//class CVehicleColors;
//class CVehicleColorOptions;
class CVehicleHandling;
class CWantedData;
class CItemInfo;
class CAmmo;
class CViewPort;
class CVehicleMods;
class CVehicleModsVisual;
class CTireInfo;
class CLicencePlateInfo;
class CColor;
class CTextInfo;
class CPedStyle;

class CCameraInterface;
class CVehicleInterface;
class CPedInterface;
class CPickupInterface;
class CPickupList;
class CPickupHandle;
class CPickup;
class CPedList;
class CPedHandle;
class CVehList;
class CVehHandle;
class CObjectInterface;
class CObjectList;
class CObjectHandle;
class CObject;
class netLoggingInterface;
class CPed
{
public:
	char pad_0x0000[0x2C]; //0x0000
	BYTE btInvisibleSP; //0x002C
	char pad_0x002D[0x1]; //0x002D
	BYTE btFreezeMomentum; //0x002E
	char pad_0x002F[0x1]; //0x002F
	CNavigation* CNavigation; //0x0030
	char pad_0x0038[0x58]; //0x0038
	char pad_0x009C[0xED]; //0x009C
	BYTE btGodMode; //0x0189
	char pad_0x018A[0xF6]; //0x018A
	float fHealth; //0x0280
	char pad_0x0284[0x1C]; //0x0284
	float fHealthMax; //0x02A0
	char pad_0x02A4[0x4]; //0x02A4
	CAttacker* CAttacker; //0x02A8
	char pad_0x02B0[0x70]; //0x02B0
	char pad_0x032C[0x9FC]; //0x032C
	CVehicle* CVehicleLast; //0x0D28
	char pad_0x0D30[0x378]; //0x0D30
	BYTE btNoRagdoll; //0x10A8
	char pad_0x10A9[0xF]; //0x10A9
	CPlayerInfo* CPlayerInfo; //0x10B8
	char pad_0x10C0[0x8]; //0x10C0
	CWeaponManager* CWeaponManager; //0x10C8
	char pad_0x10D0[0x31C]; //0x10D0
	BYTE btSeatBelt; //0x13EC
	char pad_0x13ED[0xB]; //0x13ED
	BYTE btSeatbeltWindshield; //0x13F8
	char pad_0x13F9[0x72]; //0x13F9
	BYTE btIsInVehicle; //0x146B
	char pad_0x146C[0x44]; //0x146C
	float fArmor; //0x14B0
	char pad_0x14B4[0x3C]; //0x14B4
	CVehicle* CVehicleLast2; //0x14F0

}; //Size=0x14F8
class CPickupRewardMoney;
class CPedStyle
{
public:
	char _0x0000[48];
	void* N4100AE4A; //0x0030 
	void* pColors; //0x0038 
	char _0x0040[168];
	BYTE propIndex[12]; //0x00E8 
	char _0x00F4[12];
	BYTE textureIndex[12]; //0x0100 
	BYTE paletteIndex[12]; //0x10C
	char _0x010C[9];
	BYTE N4100F70F; //0x0121 
	BYTE N4134BE09; //0x0122 
	BYTE N4134C676; //0x0123 
	BYTE btEars; //0x0124 
	char _0x0125[3];
	BYTE btEarsTexture; //0x0128 
	char _0x0129[72];
	BYTE N4100F719; //0x0171 
	BYTE N413811BF; //0x0172 
	BYTE N41381E8E; //0x0173 
	BYTE btHats; //0x0174 
	char _0x0175[3];
	BYTE btHatsTexture; //0x0178 
	BYTE N4100F71A; //0x0179 
	BYTE N4461C523; //0x017A 
	BYTE N4461D118; //0x017B 
	BYTE N4461C524; //0x017C 
	BYTE N445D0F2B; //0x017D 
	BYTE N445D279D; //0x017E 
	BYTE N445D3102; //0x017F 
	BYTE N445D279E; //0x0180 
	BYTE N4100F71B; //0x0181 
	BYTE N445D522D; //0x0182 
	BYTE N445D5D09; //0x0183 
	char _0x0184[61];
	BYTE N4100F723; //0x01C1 
	BYTE N4132EABE; //0x01C2 
	BYTE N4132F80B; //0x01C3 
	BYTE btGlasses; //0x01C4 
	char _0x01C5[3];
	BYTE btGlassesTexture; //0x01C8 
};//Size=0x03A8
class CNavigation
{
public:
	char pad_0x0000[0x20]; //0x0000
	float fHeading; //0x0020 
	float fHeading2; //0x0024 
	char pad_0x0028[0x8]; //0x0028
	Big::Vector3 Vector3Rotation; //0x0030 
	char pad_0x003C[0x14]; //0x003C
	Big::Vector3 Vector3Pos; //0x0050 

}; //Size=0x005C
class CWorld_Wrap
{
public:
	CWorld* CWorld; //0x0000 

}; //Size=0x0008
class CAttacker
{
public:
	CPed* CPed0; //0x0000 
	char pad_0x0008[0x10]; //0x0008
	CPed* CPed1; //0x0018 
	char pad_0x0020[0x10]; //0x0020
	CPed* CPed2; //0x0030 

}; //Size=0x0038
class CVehicle
{
public:
	char pad_0x0000[0x30]; //0x0000
	CNavigation* pCNavigation; //0x0030 
	char pad_0x0038[0x10]; //0x0038
	CVehicleMods* pCVehicleMods; //0x0048 
	char pad_0x0050[0x40]; //0x0050
	Big::Vector3 Vector3VisualPos; //0x0090 
	char pad_0x009C[0x3C]; //0x009C
	BYTE btState; //0x00D8 
	char pad_0x00D9[0xB0]; //0x00D9
	BYTE btGodMode; //0x0189 
	char pad_0x018A[0xF6]; //0x018A
	float fHealth; //0x0280 
	char pad_0x0284[0x1C]; //0x0284
	float fHealthMax; //0x02A0 
	char pad_0x02A4[0x4]; //0x02A4
	CAttacker* pCAttacker; //0x02A8 
	char pad_0x02B0[0x6A]; //0x02B0
	BYTE btVolticRocketState; //0x031A 
	char pad_0x031B[0x1]; //0x031B
	float fVolticRocketEnergy; //0x031C 
	char pad_0x0320[0x430]; //0x0320
	Big::Vector3 Vector3Velocity; //0x0750 
	char pad_0x075C[0xF0]; //0x075C
	float fHealth2; //0x084C 
	char pad_0x0850[0x28]; //0x0850
	CVehicleHandling* pCVehicleHandling; //0x0878 
	char pad_0x0880[0x3]; //0x0880
	BYTE btBulletproofTires; //0x0883 
	char pad_0x0884[0x4]; //0x0884
	BYTE btStolen; //0x0888 
	char pad_0x0889[0x11]; //0x0889
	BYTE N00000954; //0x089A 
	char pad_0x089B[0x41]; //0x089B
	float N0000081E; //0x08DC 
	char pad_0x08E0[0x58]; //0x08E0
	float fDirtLevel; //0x0938			max = 15.f
	char pad_0x093C[0xA8]; //0x093C
	DWORD dwCarAlarmLength; //0x09E4 
	char pad_0x09E8[0x148]; //0x09E8
	BYTE btOpenableDoors; //0x0B30 
	char pad_0x0B31[0x4B]; //0x0B31
	float fGravity; //0x0B7C
	BYTE btMaxPassengers; //0x0B80 
	char pad_0x0B81[0x1]; //0x0B81
	BYTE btNumOfPassengers; //0x0B82 
	char pad_0x0B83[0x3D]; //0x0B83

	bool isGod()
	{
		return (btGodMode & 0x01) ? true : false;
	}

	bool hasBulletproofTires()
	{
		return (btBulletproofTires & 0x20) ? true : false;
	}

	bool disabledDoors()
	{
		return (btOpenableDoors == 0) ? true : false;
	}

	void giveHealth()
	{
		if (fHealth < fHealthMax)
			fHealth = fHealthMax;
		if (fHealth2 < fHealthMax)
			fHealth2 = fHealthMax;
	}

	//btState & 7    0 = inside of vehicle, 2 = outside of vehicle, 3 = vehicle blown up
	bool isVehicleDestroyed()
	{
		return (btState & 7) == 3;
	}

	void set_stolen(bool toggle)
	{
		this->btStolen &= 0xFEu;
		this->btStolen |= toggle & 1;
	}
}; //Size=0x0BC0
class CWantedData
{
public:
	char pad_0x0000[0x1C]; //0x0000
	float fWantedCanChange; //0x001C 
	char pad_0x0020[0x10]; //0x0020
	Big::Vector3 Vector3WantedCenterPos; //0x0030 
	char pad_0x003C[0x4]; //0x003C
	Big::Vector3 Vector3WantedCenterPos2; //0x0040 
	char pad_0x004C[0x38]; //0x004C
	BYTE btFlag0; //0x0084 
	BYTE btFlag1; //0x0085 
	BYTE btFlag2; //0x0086 
	BYTE btFlag3; //0x0087 
	char pad_0x0088[0xC]; //0x0088
	DWORD dwWantedLevelFake; //0x0094 
	DWORD dwWantedLevel; //0x0098 

}; //Size=0x00AC
class CPlayerInfo
{
public:
	char pad_0x0000[0x34]; //0x0000
	__int32 iInternalIP; //0x0034 
	__int16 iInternalPort; //0x0038 
	char pad_0x003A[0x2]; //0x003A
	__int32 iRelayIP; //0x003C 
	__int16 iRelayPort; //0x0040 
	char pad_0x0042[0x2]; //0x0042
	__int32 iExternalIP; //0x0044 
	__int16 iExternalPort; //0x0048 
	char pad_0x004A[0x32]; //0x004A
	char sName[20]; //0x007C 
	char pad_0x0090[0x4]; //0x0090
	__int32 iTeam; //0x0094 
	char pad_0x0098[0x4C]; //0x0098
	float fSwimSpeed; //0x00E4 
	float fRunSpeed; //0x00E8 
	char pad_0x00EC[0x74]; //0x00EC
	CPed* pCPed; //0x0160 
	char pad_0x0168[0x29]; //0x0168
	BYTE btFrameFlags; //0x0191 
	char pad_0x0192[0x56E]; //0x0192
	CWantedData CWantedData; //0x0700 
	char pad_0x079C[0x464]; //0x079C
	float fStamina; //0x0C00 
	float fStaminaMax; //0x0C04 

	void removeWanted()
	{
		if (CWantedData.dwWantedLevel > 0)
			CWantedData.dwWantedLevel = 0;
	}
}; //Size=0x0C08
class CWeaponManager
{
public:
	char pad_0x0000[0x20]; //0x0000
	CWeapon* CWeaponCur; //0x0020 

}; //Size=0x0028
class CWeapon
{
public:
	char pad_0x0000[0x10]; //0x0000
	DWORD dwNameHash; //0x0010 
	DWORD dwModelHash; //0x0014 
	char pad_0x0018[0x24]; //0x0018
	DWORD dwAmmoType; //0x003C 
	DWORD dwWeaponWheelSlot; //0x0040 
	char pad_0x0044[0x4]; //0x0044
	CAmmoInfo* CAmmoInfo; //0x0048 
	char pad_0x0050[0xC]; //0x0050
	float fSpread; //0x005C 
	char pad_0x0060[0x38]; //0x0060
	float fBulletDamage; //0x0098 
	char pad_0x009C[0x1C]; //0x009C
	float fForce; //0x00B8 
	float fForcePed; //0x00BC 
	float fForceVehicle; //0x00C0 
	float fForceFlying; //0x00C4 
	char pad_0x00C8[0x34]; //0x00C8
	float fMuzzleVelocity; //0x00FC 
	DWORD dwBulletInBatch; //0x0100 
	float fBatchSpread; //0x0104 
	char pad_0x0108[0x8]; //0x0108
	float fVehicleReloadTime; //0x0110 
	float fAnimReloadRate; //0x0114 
	char pad_0x0118[0xC]; //0x0118
	float fSpinUpTime; //0x0124 
	float fSpinTime; //0x0128 
	char pad_0x012C[0x12C]; //0x012C
	float fLockOnRange; //0x0258 
	float fWeaponRange; //0x025C 
	char pad_0x0260[0x44]; //0x0260
	DWORD dwRecoil; //0x02A4 
	DWORD dwRecoilFP; //0x02A8 

}; //Size=0x02A8
class CAmmo
{
public:
	char pad_0x0000[0xC]; //0x0000
	DWORD dwUnknown; //0x000C 
	char pad_0x0010[0x8]; //0x0010
	DWORD dwAmmo; //0x0018 

}; //Size=0x001C
class CAmmoWrap
{
public:
	CAmmo* CAmmo; //0x0000 
	CAmmoWrap* AmmoWrap; //0x0008 

}; //Size=0x0010
class CAmmoInfo
{
public:
	char pad_0x0000[0x8]; //0x0000
	CAmmoWrap* CAmmoWrap; //0x0008 
	char pad_0x0010[0x18]; //0x0010
	DWORD dwMaxAmmo; //0x0028 

}; //Size=0x002C
class CColor
{
public:
	BYTE	r, g, b, a;

	CColor&	swap_r_b()
	{
		std::swap(r, b);
		return *this;
	}
};
class CWorld
{
public:
	char pad_0x0000[0x8]; //0x0000
	CPed* CPedLocalPlayer; //0x0008 

}; //Size=0x0010
class CVehicleMods
{
public:
	void* N00002582; //0x0000 
	void* N00002583; //0x0008 
	char _0x0010[16];
	CVehicleModsVisual* vehicleModsVisual; //0x0020 
	char _0x0028[840];
	CTireInfo* pTireInfo; //0x0370 
	char _0x0378[40];
	CColor NeonColor; //0x03A0 
	char _0x03A4[12];
	BYTE btTuningTires; //0x03B0 
	BYTE N41D07714; //0x03B1 
	BYTE btSpoiler; //0x03B2 
	BYTE btFrontBumper; //0x03B3 
	BYTE btRearBumber; //0x03B4 
	BYTE btSideSkirt; //0x03B5 
	BYTE btExhaust; //0x03B6 
	BYTE btChassis; //0x03B7 
	BYTE btGrille; //0x03B8 
	BYTE btHood; //0x03B9 
	BYTE btFender; //0x03BA 
	BYTE btRightfender; //0x03BB 
	BYTE btRoof; //0x03BC 
	BYTE btPlateholder; //0x03BD 
	BYTE btVanityPlates; //0x03BE 
	BYTE btTrim; //0x03BF 
	BYTE btOrnamentHead; //0x03C0 
	BYTE btDashboard; //0x03C1 
	BYTE btDial; //0x03C2 
	BYTE btDoorSpeaker; //0x03C3 
	BYTE btSteats; //0x03C4 
	BYTE btSteeringwheel; //0x03C5 
	BYTE btShifterLeavers; //0x03C6 
	BYTE btPlaques; //0x03C7 
	BYTE btSpeakers; //0x03C8 
	BYTE btTrunk; //0x03C9 
	BYTE btHydraulics; //0x03CA 
	BYTE btEngineBlock; //0x03CB 
	BYTE btAirFilter; //0x03CC 
	BYTE btStruts; //0x03CD 
	BYTE btArchCover; //0x03CE 
	BYTE btAerials; //0x03CF 
	BYTE btTrim2; //0x03D0 
	BYTE btFuel; //0x03D1 
	BYTE btWindow; //0x03D2 
	BYTE btunk1; //0x03D3 
	BYTE btLivery; //0x03D4 
	BYTE N41D48824; //0x03D5 
	BYTE btEngine; //0x03D6 
	BYTE btBreaks; //0x03D7 
	BYTE btTransmission; //0x03D8 
	BYTE btHorns; //0x03D9 
	BYTE btSuspension; //0x03DA 
	BYTE btArmor; //0x03DB 
	BYTE N41884B66; //0x03DC 
	BYTE btTurbo; //0x03DD 
	BYTE N41D63CF5; //0x03DE 
	BYTE btTireSmoke; //0x03DF 
	BYTE N41D63CF6; //0x03E0 
	BYTE btXenonLight; //0x03E1 
	BYTE btTireIndex; //0x03E2 
	BYTE N41D631AD; //0x03E3 
	BYTE N41884B65; //0x03E4 
	BYTE btOrnamentBody; //0x03E5 
	char _0x03E6[14];
	BYTE N41D9A820; //0x03F4 
	BYTE btPrimary; //0x03F5 
	BYTE btSecondary; //0x03F6 
	BYTE btPearlescent; //0x03F7 
	BYTE btWheelColor; //0x03F8 
	BYTE N41DA70FC; //0x03F9 
	BYTE N41DA7E0A; //0x03FA 
	BYTE btTireColorR; //0x03FB 
	BYTE btTireColorG; //0x03FC 
	BYTE btTireColorB; //0x03FD 
	BYTE btWindowTint; //0x03FE 
	BYTE btTireType; //0x03FF 
	BYTE N41884B5A; //0x0400 
	BYTE btNeonLeft; //0x0401 
	BYTE btNeonRight; //0x0402 
	BYTE btNeonFront; //0x0403 
	BYTE btNeonBack; //0x0404 
};
class CTireInfo
{
public:
	char _0x0000[8];
	CColor tireColor; //0x0008 
	char _0x000C[4];
	BYTE btCustumTires; //0x0010 
};//Size=0x0108
class datBitBuffer
{
public:
	inline datBitBuffer(void* data, size_t size)
	{
		m_data = data;
		m_f8 = 0;
		m_maxBit = size * 8;
		m_unkBit = 0;
		m_curBit = 0;
		m_unk2Bit = 0;
		m_f1C = 0;
	}

	inline uint32_t GetPosition()
	{
		return m_unkBit;
	}

	inline bool Seek(int bits)
	{
		if (bits >= 0)
		{
			uint32_t length = (m_f1C & 1) ? m_maxBit : m_curBit;

			if (bits <= length)
			{
				m_unkBit = bits;
			}
		}

		return false;
	}

	inline size_t GetDataLength()
	{
		char leftoverBit = (m_curBit % 8) ? 1 : 0;

		return (m_curBit / 8) + leftoverBit;
	}

	bool ReadInteger(uint32_t* integer, int bits)
	{
	}

	// NOTE: SIGNED
	bool WriteInteger(uint32_t integer, int bits);

	bool WriteUns(uint32_t integer, int bits);

	bool WriteBit(bool bit);

public:
	void* m_data;
	uint32_t m_f8;
	uint32_t m_maxBit;
	uint32_t m_unkBit;
	uint32_t m_curBit;
	uint32_t m_unk2Bit;
	uint8_t m_f1C;
};
class CLicencePlateInfo
{
public:
	char _0x0000[40];
	char* plateName; //0x0028 
	char _0x0030[136];
	char* tireName; //0x00B8 
	char _0x00C0[136];
	char* visualName; //0x0148 
	char _0x0150[48];
};
class CVehicleModsVisual
{
public:
	char _0x0000[164];
	CColor PrimaryColor; //0x00A4 
	CColor SecondaryColor; //0x00A8 
	CColor unknownColor; //0x00AC 
	CColor wheelColor; //0x00B0 
	CColor modelColor; //0x00B4 
	CColor seatColor; //0x00B8 
	CColor speedometerColor; //0x00BC 
	CColor perlColor; //0x00C0 
	char _0x00C4[92];
	CLicencePlateInfo* pLicencePlateInfo; //0x0120 
	char licencePlate[8]; //0x0128 
	char _0x0130[2956];

};//Size=0x0CBC


class CVehicleHandling
{
public:
	char pad_0x0000[0xC]; //0x0000
	float fMass; //0x000C 
	char pad_0x0010[0x10]; //0x0010
	Big::Vector3 Vector3CentreOfMassOffset; //0x0020 
	char pad_0x002C[0x4]; //0x002C
	Big::Vector3 Vector3InertiaMult; //0x0030 
	char pad_0x003C[0x4]; //0x003C
	float fPercentSubmerged; //0x0040 
	char pad_0x0044[0x8]; //0x0044
	float fAcceleration; //0x004C 
	BYTE btInitialDriveGears; //0x0050 
	char pad_0x0051[0x3]; //0x0051
	float fDriveInertia; //0x0054 
	float fClutchChangeRateScaleUpShift; //0x0058 
	float fClutchChangeRateScaleDownShift; //0x005C 
	float fInitialDriveForce; //0x0060 
	char pad_0x0064[0x8]; //0x0064
	float fBrakeForce; //0x006C 
	char pad_0x0070[0x4]; //0x0070
	float fBrakeBiasFront; //0x0074 
	char pad_0x0078[0x4]; //0x0078
	float fHandBrakeForce; //0x007C 
	char pad_0x0080[0x8]; //0x0080
	float fTractionCurveMax; //0x0088 
	char pad_0x008C[0x4]; //0x008C
	float fTractionCurveMin; //0x0090 
	char pad_0x0094[0xC]; //0x0094
	float fTractionSpringDeltaMax; //0x00A0 
	char pad_0x00A4[0x4]; //0x00A4
	float fLowSpeedTractionLossMult; //0x00A8 
	float fCamberStiffnesss; //0x00AC 
	float fTractionBiasFront; //0x00B0 
	float fTwoMinus_fTractionBiasFront; //0x00B4 
	float fTractionLossMult; //0x00B8 
	float fSuspensionForce; //0x00BC 
	float fSuspensionCompDamp; //0x00C0 
	float fSuspensionReboundDamp; //0x00C4 
	float fSuspensionUpperLimit; //0x00C8 
	float fSuspensionLowerLimit; //0x00CC 
	char pad_0x00D0[0xC]; //0x00D0
	float fAntiRollBarForce; //0x00DC 
	char pad_0x00E0[0x8]; //0x00E0
	float fRollCentreHeightFront; //0x00E8 
	float fRollCentreHeightRear; //0x00EC 
	float fCollisionDamageMult; //0x00F0 
	float fWeaponDamageMult; //0x00F4 
	float fDeformationDamageMult; //0x00F8 
	float fEngineDamageMult; //0x00FC 
	float fPetrolTankVolume; //0x0100 
	float fOilVolume; //0x0104 

}; //Size=0x0108
class CGameScriptId
{
public:
	char m_padding[0x04];         // 0x2C
	std::int32_t m_timestamp;     // 0x30
	std::int32_t m_position_hash; // 0x34
	std::int32_t m_instance_id;   // 0x38
	std::int32_t m_unk;           // 0x3C
};
class CViewPort
{
public:
	char _0x0000[0x24C];
	float fViewMatrix[0x10];
};//Size=0x028C





class CObjectWrapper
{
public:
	char _0x0000[168];
	CPlayerInfo* playerInfo; //0x00A8 

};//Size=0x00B0

class CPlayers
{
public:
	char _0x0000[376];
	__int32 numPlayersOnline; //0x0178 
	char _0x017C[4];
	CObjectWrapper* ObjectWrapperList[256]; //0x0180 
};





class CPickupHandle
{
public:
	CPickup* pCPickup; //0x0000 
	__int32 iHandle; //0x0008 
	char pad_0x000C[0x4]; //0x000C

}; //Size=0x0010

class CPickupList
{
public:
	CPickupHandle pickups[73]; //0x0000 

}; //Size=0x0490

class CPickup
{
public:
	char pad_0x0000[0x30]; //0x0000
	CNavigation* pCNavigation; //0x0030 
	char pad_0x0038[0x58]; //0x0038
	Big::Vector3 Vector3VisualPos; //0x0090 
	char pad_0x009C[0x3F4]; //0x009C
	__int32 iValue; //0x0490 
	char pad_0x0494[0xC4]; //0x0494

}; //Size=0x0558

class CPedHandle
{
public:
	CPed* pCPed; //0x0000 
	__int32 iHandle;
	char _pad0[0x4];

}; //Size=0x0010

class CPedList
{
public:
	CPedHandle peds[256]; //0x0000 

}; //Size=0x1000

class CVehHandle
{
public:
	CVehicle* pCVehicle; //0x0000 
	__int32 iHandle;
	char _pad0[0x4];

}; //Size=0x0010

class CVehList
{
public:
	CVehHandle vehs[300]; //0x0000 

}; //Size=0x1000

class CObjectHandle
{
public:
	CObject* pCObject; //0x0000 
	__int32 iHandle; //0x0008 
	char pad_0x000C[0x4]; //0x000C

}; //Size=0x0010

class CObjectList
{
public:
	CObjectHandle ObjectList[2300]; //0x0000 

}; //Size=0x8FC0

class CObject
{
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008


class CCameraInterface
{
public:
	char pad_0x0000[0x248]; //0x0000

}; //Size=0x0248

class CObjectInterface
{
public:
	char pad_0x0000[0x158]; //0x0000
	CObjectList* pCObjectList; //0x0158 
	__int32 iMaxObjects; //0x0160 
	char pad_0x0164[0x4]; //0x0164
	__int32 iCurObjects; //0x0168 
	char pad_0x016C[0x5C]; //0x016C

}; //Size=0x01C8

class CVehicleInterface
{
public:
	char pad_0x0000[0x180]; //0x0000
	CVehList* VehList; //0x0180 
	__int32 iMaxVehicles; //0x0188 
	char pad_0x018C[0x4]; //0x018C
	__int32 iCurVehicles; //0x0190 
	char pad_0x0194[0x74]; //0x0194

	CVehicle* get_vehicle(const int& index)
	{
		if (index < iMaxVehicles)
			return VehList->vehs[index].pCVehicle;
		return nullptr;
	}
}; //Size=0x0208

class CPedInterface
{
public:
	char pad_0x0000[0x100]; //0x0000
	CPedList* PedLIst; //0x0100 
	__int32 iMaxPeds; //0x0108 
	char pad_0x010C[0x4]; //0x010C
	__int32 iCurPeds; //0x0110 
	char pad_0x0114[0x34]; //0x0114

	CPed* get_ped(const int& index)
	{
		if (index < iMaxPeds)
			return PedLIst->peds[index].pCPed;
		return nullptr;
	}
}; //Size=0x0148

class CPickupInterface
{
public:
	char pad_0x0000[0x100]; //0x0000
	CPickupList* pCPickupList; //0x0100 
	__int32 iMaxPickups; //0x0108 
	char pad_0x010C[0x4]; //0x010C
	__int32 iCurPickups; //0x0110 

	CPickup* get_pickup(const int& index)
	{
		if (index < iMaxPickups)
			return pCPickupList->pickups[index].pCPickup;
		return nullptr;
	}
}; //Size=0x0114

class CReplayInterface
{
public:
	void* N000006F5; //0x0000 
	CCameraInterface* pCCameraInterface; //0x0008 
	CVehicleInterface* pCVehicleInterface; //0x0010 
	CPedInterface* pCPedInterface; //0x0018 
	CPickupInterface* pCPickupInterface; //0x0020 
	CObjectInterface* pCObjectInterface; //0x0028 

}; //Size=0x0030






class CBlip
{
public:
	__int32 iID; //0x0000 
	__int8 iID2; //0x0004 
	char _0x0005[3];
	BYTE N000010FB; //0x0008 (80 = moves with player, some values will turn icon into map cursor and break it)
	char _0x0009[7];
	Big::Vector3 Vector3Pos;
	char _0x001C[6];
	BYTE btFocused; //0x0022   (Focused? 0100 0000)
	char _0x0023[5];
	char* szMessage; //0x0028 If not null, contains the string of whatever the blip says when selected.
	char _0x0030[16];
	int iIcon; //0x0040
	char _0x0044[4];
	DWORD dwColor; //0x0048 (Sometimes works?)
	char _0x004C[4];
	float fScale; //0x0050 
	__int16 iRotation; //0x0054 Heading
	BYTE btInfoIDType; //0x0056 GET_BLIP_INFO_ID_TYPE
	BYTE btZIndex; //0x0057 
	BYTE btDisplay; //0x0058  Also Visibility 0010
	BYTE btAlpha; //0x0059
};//Size=0x005A

class CBlipList
{
public:
	CBlip* m_Blips[0x400]; //0x0000 

};//Size=0x2F18




class CTextInfo
{
public:
	CColor	color;
	float	fTextScale1;
	float	fTextScale2;
	float	fTextWrapStart;
	float	fTextWrapEnd;
	int64_t	iFont;
	WORD	wNotCentered;
	BYTE	btDropShadow;
	BYTE	btTextOutline;

	void	setColor(CColor c)
	{
		c.swap_r_b();
		color = c;
	}

	void	setScale(float f)
	{
		fTextScale1 = f;
		fTextScale2 = f;
	}
};
struct CPlayer
{
	bool		m_active;
	int			m_pedId,
		m_teamId;
	CPed*		m_pCPed;
};
class CPlayerMem
{
public:

	static int	player_id();
	static bool is_player_valid(int player);
	static int		player_ped_id();
	static int		get_player_ped(int player);
	static int		get_player_team(int player);
	static CPed*	get_player_cped(int player);
	static bool		is_player_in_any_vehicle(int player);
	static float	get_player_health(int player);
	static float	get_player_max_health(int player);
	static float	get_player_armour(int player);
	static bool		is_player_god(int player);
	static int		get_player_from_ped(int ped);
private:
	CPlayerMem() {};
	~CPlayerMem() {};

	static int				m_localPlayerId;
	static CPlayer			m_player[0x20];		//player buffer
};
using joaat_t = std::uint32_t;
class scriptIdBase
{
public:
	virtual ~scriptIdBase() = default;                            // 0 (0x00)

	// Assumes the thread's identity.
	virtual void assume_thread_identity(scrThread*) {};           // 1 (0x08)

	// Returns whether the hash of the script id is valid.
	virtual bool is_valid() {};                                   // 2 (0x10)

	// Gets the hash of the script id.
	virtual joaat_t *get_hash(joaat_t *out) {};                   // 3 (0x18)

	// Gets an unknown value from the script id.
	virtual std::uint32_t *get_hash2(std::uint32_t *out) {};      // 4 (0x20)

	// Gets the name of the script id.
	virtual const char *get_name() {};                            // 5 (0x28)

	// Serializes the script id from the buffer.
	virtual void deserialize(datBitBuffer* buffer) {};            // 6 (0x30)

	// Serializes the script id to the buffer.
	virtual void serialize(datBitBuffer* buffer) {};              // 7 (0x38)

	// Calculates some information with the position hash & instance id.
	virtual std::uint32_t _0x40() {};                             // 8 (0x40)

	// Calls _0x40 and returns it's value added to another value.
	virtual std::uint32_t _0x48() {};                             // 9 (0x48)

	// Logs some information about the script id.
	virtual void log_information(netLoggingInterface* logger) {}; // 10 (0x50)

	// Copies the information of other to this object.
	virtual void copy_data(scriptIdBase *other) {}                // 11 (0x58)

	// Returns whether the other script id is equal.
	virtual bool operator==(scriptIdBase*) {};                    // 12 (0x60)

	virtual bool _0x68(void*) {};                                 // 13 (0x68)
};
class netEventMgr;
class CUpdateFxnEvent;
class CNetworkInfoChangeEvent;

class datJson;

class rlMetric
{
public:
	virtual ~rlMetric() = default;

	virtual int _0x08() = 0;

	virtual int _0x10() = 0;

	virtual const char *GetName() = 0;

	virtual void Serialize(datJson*) = 0;

	virtual int GetSize() = 0;

	virtual joaat_t GetHashOfName() = 0;
};
class CNetGamePlayer : public CNetworkPlayer
{
public:
	virtual ~CNetGamePlayer() = 0;
	char m_Pad1[0x08];                               // 0x08
	void* m_NonPhysicalPlayerData; // 0x10
	char m_Pad2[0x15];                               // 0x18
	std::uint8_t m_player_id;                               // 0x2D
	char m_Pad3[0x7A];                               // 0x2E
	CPlayerInfo* playerInfo;                       // 0xA8
	char m_Pad4[0xF1];                               // 0xB0
	bool m_IsRockstarDev;                            // 0x1A1
	char m_Pad5[0x01];                               // 0x1A2
	bool m_IsCheater;                                // 0x1A3
	char m_Pad6[0xFC];                               // 0x1A4

};
class CNetGamePlayers : public CNetworkPlayer
{
public:
	char m_pad_0x000[0x2D];
	uint8_t m_player_id;
	char m_pad_0x002R[0x7A];
	CPlayerInfo* PlayerInfo;
	char m_pad_0x00B0[0x1B8];
};
class netGameEvent
{
public:
	virtual ~netGameEvent() = 0;
	virtual const char* GetName() = 0;
	virtual bool IsApplicableToPlayer(CNetGamePlayers* player) = 0;
	virtual bool TimeToResend(uint32_t time) = 0;
	virtual bool IsNeedReply() = 0;
	virtual void PrepareData(datBitBuffer* buffer, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer) = 0;
	virtual void HandleData(datBitBuffer* buffer, CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer) = 0;
	virtual bool Decide(CNetGamePlayers* sourcePlayer, CNetGamePlayers* targetPlayer) = 0;
	virtual void PrepareReply(datBitBuffer* buffer, CNetGamePlayers* replyPlayer) = 0;
	virtual void HandleReply(datBitBuffer* buffer, CNetGamePlayers* sourcePlayer) = 0;
	virtual void PrepareExtraData(datBitBuffer* buffer, bool isReply, CNetGamePlayers* player, CNetGamePlayers* unkPlayer) = 0;
	virtual void HandleExtraData(datBitBuffer* buffer, bool isReply, CNetGamePlayers* player, CNetGamePlayers* unkPlayer) = 0;
	virtual void m_60() = 0;
	virtual void m_68() = 0;
	virtual void m_70() = 0;
	virtual void m_78() = 0;
	virtual bool operator==(const netGameEvent* event) = 0;
	virtual bool operator!=(const netGameEvent* event) = 0;
	virtual bool MustPersist() = 0;
	virtual bool MustPersistWhenOutOfScope() = 0;
	virtual bool HasTimedOut() = 0;
public:
	std::uint16_t eventId; //0x08
	bool requiresReply : 1; //0x0A
	char m_padding1[0x05]; // 0x0B
	CNetGamePlayers* sourcePlayer; //0x10
	CNetGamePlayers* targetPlayer; //0x18
	uint32_t dword_0x20; //0x20
	uint16_t word_0x24; //0x24
	uint8_t byte_0x26; //0x26
	char m_padding2[0x01]; // 0x27
	uint32_t dword_0x28; //0x28
	char m_padding3[0x04]; // 0x2C
};
class CScriptedGameEvent : public netGameEvent
{
public:
	CGameScriptId*  m_script_id; // 0x30
	std::int64_t m_args[54];   // 0x70
	std::uint32_t m_bitset;    // 0x220
	std::uint32_t m_args_size; // 0x224
};
/*
	//CPlayerMem private
*/

#define VK_NOTHING	0x00				/*NULL*/
#define VK_KEY_0	0x30                //('0')	0
#define VK_KEY_1	0x31                //('1')	1
#define VK_KEY_2	0x32                //('2')	2
#define VK_KEY_3	0x33                //('3')	3
#define VK_KEY_4	0x34                //('4')	4
#define VK_KEY_5	0x35                //('5')	5
#define VK_KEY_6	0x36                //('6')	6
#define VK_KEY_7	0x37                //('7')	7
#define VK_KEY_8	0x38                //('8')	8
#define VK_KEY_9	0x39                //('9')	9
#define VK_KEY_A	0x41                //('A')	A
#define VK_KEY_B	0x42                //('B')	B
#define VK_KEY_C	0x43                //('C')	C
#define VK_KEY_D	0x44                //('D')	D
#define VK_KEY_E	0x45                //('E')	E
#define VK_KEY_F	0x46                //('F')	F
#define VK_KEY_G	0x47                //('G')	G
#define VK_KEY_H	0x48                //('H')	H
#define VK_KEY_I	0x49                //('I')	I
#define VK_KEY_J	0x4A                //('J')	J
#define VK_KEY_K	0x4B                //('K')	K
#define VK_KEY_L	0x4C                //('L')	L
#define VK_KEY_M	0x4D                //('M')	M
#define VK_KEY_N	0x4E                //('N')	N
#define VK_KEY_O	0x4F                //('O')	O
#define VK_KEY_P	0x50                //('P')	P
#define VK_KEY_Q	0x51                //('Q')	Q
#define VK_KEY_R	0x52                //('R')	R
#define VK_KEY_S	0x53                //('S')	S
#define VK_KEY_T	0x54                //('T')	T
#define VK_KEY_U	0x55                //('U')	U
#define VK_KEY_V	0x56                //('V')	V
#define VK_KEY_W	0x57                //('W')	W
#define VK_KEY_X	0x58                //('X')	X
#define VK_KEY_Y	0x59                //('Y')	Y
#define VK_KEY_Z	0x5A                //('Z')	Z