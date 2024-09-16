//#include "pch.h"
#include "Structures.h"

class PlayerEnt
{
public:
	char pad_0000[4]; //0x0000
	Vector3 HeadPos; //0x0004
	Vector2 VelocityByDirection; //0x0010
	float JumpPower; //0x0018
	char pad_001C[12]; //0x001C
	Vector3 FeetPos; //0x0028
	Angle ViewAngles; //0x0034
	char pad_0040[8]; //0x0040
	int32_t Gravity; //0x0048
	float CharacterShape1; //0x004C
	float CharacterHight; //0x0050
	float CharacterShape2; //0x0054
	float MovementRelated; //0x0058
	int32_t IsJumping; //0x005C
	char pad_0060[1]; //0x0060
	int8_t IsShifting; //0x0061
	char pad_0062[2]; //0x0062
	int32_t IsMoving; //0x0064
	char pad_0068[14]; //0x0068
	int8_t PlayerMode; //0x0076
	char pad_0077[9]; //0x0077
	int32_t IsWASD; //0x0080
	char pad_0084[104]; //0x0084
	int32_t Health; //0x00EC
	int32_t Armor; //0x00F0
	char pad_00F4[80]; //0x00F4
	int32_t Gernade; //0x0144
	char pad_0148[4]; //0x0148
	bool IsKnifing; //0x014C
	char pad_014D[183]; //0x014D
	int8_t AutoShoot; //0x0204
	char Name[16]; //0x0205
	char pad_0215[247]; //0x0215
	int8_t TeamID; //0x030C
	char pad_030D[87]; //0x030D
	class GunEnt* GunEnt; //0x0364
	char pad_0368[260]; //0x0368
}; //Size: 0x046C

class GunEnt
{
public:
	char pad_0000[4]; //0x0000
	int32_t Code; //0x0004
	class PlayerEnt* Owner; //0x0008
	class GunData* GeneralData; //0x000C
	class AmmoData* AmmoData1; //0x0010
	char pad_0014[8]; //0x0014
	int32_t Spread; //0x001C
	char pad_0020[8]; //0x0020
	int8_t IsScoping; //0x0028
	char pad_0029[1096]; //0x0029
}; //Size: 0x0471

class AmmoData
{
public:
	int32_t CurrentMag; //0x0000
	char pad_0004[32]; //0x0004
	int32_t CurrentAmmo; //0x0024
	char pad_0028[68]; //0x0028
	int32_t BulletsShot; //0x006C
	char pad_0070[148]; //0x0070
}; //Size: 0x0104

//class GunData
//{
//public:
//	char pad_0000[23]; //0x0000
//	char GunName[13]; //0x0017
//	char pad_0024[49]; //0x0024
//	int16_t GunDamage; //0x0055
//	char pad_0057[958]; //0x0057
//}; //Size: 0x0415
class GunData
{
public:
	char pad_0000[23]; //0x0000
	char GunName[13]; //0x0017
	char pad_0024[38]; //0x0024
	int16_t GunDamage; //0x004A
	char pad_004C[997]; //0x004C
}; //Size: 0x0431


class GernadeEnt
{
public:
	int32_t Rtti; //0x0000
	Vector3 Pos; //0x0004
	char pad_0010[132]; //0x0010
	class PlayerEnt* GernadeOwner; //0x0094
	char pad_0098[176]; //0x0098
}; //Size: 0x0148



//~RECLASS

extern bool IsFirstTime;
extern bool CoolDown;
extern bool BeingAttacked;
extern const char* AttackerName;
extern bool bTrace;
//Cheats
extern float* FOV;
extern float* Speed;
extern DWORD* PlayerEntAddress;

//General Game
extern PlayerEnt* LocalPlayer;
extern int32_t CurPlayers;
extern uintptr_t* TimeRemaining;
extern GernadeEnt* Gernade;
extern DWORD** GernadeAddr;
extern uintptr_t MaxEnemies;
extern uintptr_t MapName;
extern int32_t* EntList;
extern uintptr_t RealEnemyCount;
extern std::vector<PlayerEnt*> EnemiesList;
extern int8_t* PRealLocalMode;
extern int32_t* PRealHealth;

extern Vector3* CursorPos;


//Patches Addresses
extern uintptr_t AmmoLoc;
extern uintptr_t GravityLoc;
extern uintptr_t RapidLoc;
extern uintptr_t SmallSpreadLoc;
extern uintptr_t SmallSpread2Loc;
extern uintptr_t SpreadLoc;
extern uintptr_t RXveloLoc;
extern uintptr_t RYveloLoc;
extern uintptr_t RJumpVeloLoc;
extern uintptr_t RectanglesLoc;
extern uintptr_t ParticlesLoc;
extern int WindowX;
extern uintptr_t WindowY;
extern float* ViewMatrix;

extern PlayerEnt* Aimbotted;
extern PlayerEnt* WallBanged;
extern PlayerEnt* Silented;


namespace GeneratedCode {
	void EnemyVecUpdate();
}