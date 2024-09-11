#include "Settings.h"
#include "Constants.h"
#include <imgui.h>

namespace Settings {
	/*int AimFeaturesIndex = 0;*/
	//const char* AimFeatures[2] = { "Silent Aim", "WallBang" };
	const char* AimLocations[3] = { "Head", "Body", "Feet" };
}

namespace Settings::GunCheats {

	bool bInfiniteAmmo = false;
	bool bNoRecoil = false;
	bool bRapidFire = false;
	bool bOneShotKill = false;
}

namespace Settings::PlayerCheats {

	bool NoClipState = false;
	bool SpeedHack = false;
	bool NoGravityState = false;
	bool ParticlesState = false;
	bool FovChanger = false;
	bool GameInfo = false;
};

namespace Settings::Aimbot {
	int AimbotHitPosIndex = 0;						//Index of aimbot hit location

	int AimbotTypeIndex = 0;					//Index of aimbot type location
	const char* AimbotTypes[2] = { "Position Based", "Cursor Position Base" };


	bool bAimbot = false;							//Aimbot toggle
	bool bAimbotState = false;						//Aimbot real state
	int AimbotKey = 0;							//Aimbot VK

	bool bSmoothness = false;						//Smoothness toggle
	float Smoothness = 1.0f;						//Smoothness value

	bool bAimbotAimLine = false;					//Aimbot aim line toggle
	ImColor AimbotAimLineC = Green;					//Aimbot aim line color

	bool bAimbotFOV = false;						//Aimbot FOV toggle
	float AimbotFOV = 30.0f;						//Aimbot FOV radius
	ImColor AimbotFOVC = Red;						//Aimbot FOV color
};


namespace Settings::WallBang {
	bool bWallBang = false; 						//WallBang toggle
	bool bWallBangState = false;					//WallBang(HotKey) real state
	//bool bWallBangNoHotKeyState = false;			//WallBang real state
	int WallBangKey = 0;							//WallBang VK

	int WallBangHitPosIndex = 0;					//Index of WallBang hit location

	bool bWallBangAimLine = false;					//WallBang aim line toggle
	ImColor WallBangAimLineC = Green;				//WallBang aim line colorneC

	bool bWallBangFOV = false;						//WallBang FOV toggle
	float WallBangFOV = 30.0f;						//WallBang FOV radius
	ImColor WallBangFOVC = Red;						//WallBang FOV color
};

namespace Settings::Silent {
	bool bSilent = false;							//SilentAim toggle
	bool bSilentState = false;						//SilentAim real state
	//bool bSilentNoHotKeyState = false;				//WallBang real state
	int SilentKey = 0;								//SilentAim VK

	int SilentAimHitPosIndex = 0;					//Index of WallBang hit location

	bool bSilentAimLine = false;					//SilentAim aim line toggle
	ImColor SilentAimLineC = Green;					//SilentAim aim line colorneC

	bool bSilentFOV = false;						//SilentAim FOV toggle
	float SilentFov = 30.0f;						//SilentAim FOV radius
	ImColor SilentFovC = Red;						//SilentAim FOV color
};

namespace Settings::ESP {
	int EspLineIndex = 0;							//Index of SnapLine location
	const char* SnapLinePosition[3] = { "Top", "Middle", "Bottom" };

	bool bESP = false;								//ESP toggle

	bool bBones = false;							//Bones toggle
	bool bBoxes = false;							//Boxes toggle
	bool bNames = false;							//Names toggle
	bool bSnapLines = false;						//SnapLines toggle
	bool bHealthBar = false;						//Health Bars toggle
	bool bGernades = false;							//Gernades Notifier toggle
	bool bGun = false;								//Enemy gun toggle
	bool bDistance = false;							//Distance toggle
	bool bShowPlayerCount = false;					//PlayerCount notifier toggle
	bool bShowWhoIsAiming = false;					//WhoIsAiming Notifier toggle

	ImColor BoxC = Orange;							//Enemy Boxes Color
	ImColor BoneC = White;							//Enemy Bones Color
	ImColor SnapLinesC = Orange;					//Enemy SnapLines Color

};
