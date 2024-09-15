#pragma once
#include <imgui.h>

namespace Settings {

	/*extern int AimFeaturesIndex;*/
	extern const char* AimLocations[3];


	namespace ESP {

		extern int EspLineIndex;						//Index of SnapLine location
		extern const char* SnapLinePosition[3];

		extern bool bESP;								//ESP toggle

		extern bool bBoxes;								//Boxes toggle
		extern bool bBones;								//Bones toggle
		extern bool bNames;								//Names toggle
		extern bool bSnapLines;							//SnapLines toggle
		extern bool bHealthBar;							//Health Bars toggle
		extern bool bGernades;							//Gernades Notifier toggle
		extern bool bGun;								//Enemy gun toggle
		extern bool bDistance;							//Distance toggle
		extern bool bShowPlayerCount;					//PlayerCount notifier toggle
		extern bool bShowWhoIsAiming;					//WhoIsAiming Notifier toggle
		
		extern ImColor BoxC; 							//Enemy Boxes Color
		extern ImColor BoneC;							//Enemy Bones Color
		extern ImColor SnapLinesC;						//Enemy SnapLines Color
	};

	namespace GunCheats {
		extern bool bInfiniteAmmo;
		extern bool bNoRecoil;
		extern bool bRapidFire;
		extern bool bOneShotKill;
	};
	
	namespace PlayerCheats {
		extern bool NoClipState;
		extern bool SpeedHack;
		extern bool NoGravityState;
		extern bool ParticlesState;
		extern bool FovChanger;
		extern bool GameInfo;
	};
	
	namespace Aimbot {
		extern int AimbotHitPosIndex;					//Index of aimbot hit location
		//extern const char* AimLocations[3];

		extern int AimbotTypeIndex;						//Index of aimbot hit location
		extern const char* AimbotTypes[2];

		extern bool bAimbot;							//Aimbot toggle
		extern bool bAimbotState;						//Aimbot real state
		extern int AimbotKey;							//Aimbot VK

		extern bool bSmoothness;						//Smoothness toggle
		extern float Smoothness;						//Smoothness value

		extern bool bAimbotAimLine;						//Aimbot aim line toggle
		extern ImColor AimbotAimLineC;					//Aimbot aim line color

		extern bool bAimbotFOV;							//Aimbot FOV toggle
		extern float AimbotFOV;							//Aimbot FOV radius
		extern ImColor AimbotFOVC;						//Aimbot FOV color
	};

	namespace WallBang {
		extern bool bWallBang;							//WallBang toggle
		extern bool bWallBangState;						//WallBang(HotKey) real state
		extern bool bPreiousState;						//WallBang(HotKey) real state
		//extern bool bWallBangNoHotKeyState;				//WallBang real state
		extern int WallBangKey;							//WallBang VK
		
		extern int WallBangHitPosIndex;					//Index of WallBang hit location
		//extern const char* AimLocations[3];

		extern int WallBangAimTypeIndex;			//Index of WallBang hit location
		//extern const char* AimTypes[2];

		extern bool bWallBangAimLine;					//WallBang aim line toggle
		extern ImColor WallBangAimLineC;				//WallBang aim line colorneC

		extern bool bWallBangFOV;						//WallBang FOV toggle
		extern float WallBangFOV;						//WallBang FOV radius
		extern ImColor WallBangFOVC;					//WallBang FOV color
	};

	namespace Silent {
		extern bool bSilent;							//SilentAim toggle
		extern bool bSilentState;						//SilentAim real state
		//extern bool bSilentNoHotKeyState;				//SilentAim real state
		extern int SilentKey;							//SilentAim VK

		extern int SilentAimHitPosIndex;				//Index of WallBang hit location
		//extern const char* AimLocations[3];

		extern bool bSilentAimLine;						//SilentAim aim line toggle
		extern ImColor SilentAimLineC;					//SilentAim aim line colorneC

		extern bool bSilentFOV;							//SilentAim FOV toggle
		extern float SilentFov;							//SilentAim FOV radius
		extern ImColor SilentFovC;						//SilentAim FOV color
	};


};