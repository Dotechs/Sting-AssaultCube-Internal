#include "Cheat.h"

#include <imgui.h>
#include "Constants.h"
#include "GeneratedCode.h"
#include "Memory.h"
#include "Settings.h"
#include "Structures.h"
#include "Hooks.h"

// Math
float Cheat::DotProduct(const vec3& v1, const vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Cheat::CrossProduct(const Vector3& a, const Vector3& b) {
	return Vector3{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

Vector3 Cheat::AngleToDirection(float pitch, float yaw)
{
	float pitchRad = pitch * (M_PI / 180.0f);
	float yawRad = yaw * (M_PI / 180.0f);
	return Vector3(
		cosf(pitchRad) * cosf(yawRad),
		cosf(pitchRad) * sinf(yawRad),
		sinf(pitchRad)
	);
}

float Cheat::Distance2D(const Vector2& a, const Vector2& b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Vector3 Cheat::CalculateAngle(Vector3& from, Vector3& to)
{
	Vector3 delta = to - from;
	float hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
	float pitch = atan2(-delta.z, hyp) * 180.0f / M_PI;
	float yaw = atan2(delta.y, delta.x) * 180.0f / M_PI;
	vec3 res = Vector3(yaw, pitch, 0.0f);
	return res;
}

void Cheat::Normalize(Vector3& v) {
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length != 0)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
}

float Cheat::CalculateVectorAngle(Vector3& v1, Vector3& v2) {
	Normalize(v1); Normalize(v2);
	return acos(DotProduct(v1, v2) / DotProduct(v1, v2));
}

//SnapLines
void Cheat::SnapAimLine(PlayerEnt* AimedAt, ImColor& Color, float* Fov){
	if (!AimedAt || AimedAt->PlayerMode != 0 || AimedAt->Health <= 0 || LocalPlayer->PlayerMode != 0 || *PRealLocalMode != 0 || LocalPlayer->Health <= 0)
		return;

	vec2 feetScreenPos = vec2(0, 0);
	vec2 headScreenPos = vec2(0, 0);

	if (!Cheat::IsEnemyLoadedR(AimedAt, headScreenPos, feetScreenPos, FEET_ONLY) &&
		!Cheat::IsEnemyInFOV(AimedAt, Fov, headScreenPos, feetScreenPos, ANY)) {
		return;
	}
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(WindowX / 2, WindowY), ImVec2(feetScreenPos.x, feetScreenPos.y), Color, 0.60f);
	//bool IsLoadedFeet = Cheat::WorldToScreenEx(AimedAt->FeetPos, feetScreenPos, ViewMatrix, WindowX, WindowY);
	//float FTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(feetScreenPos.x, feetScreenPos.y)));
}
void Cheat::SnapAimLine(PlayerEnt* AimedAt, ImColor& Color) {

	if (!AimedAt || AimedAt->PlayerMode != 0 || AimedAt->Health <= 0 || LocalPlayer->PlayerMode != 0 || *PRealLocalMode != 0 || LocalPlayer->Health <= 0)
		return;

	//bool IsLoadedFeet = Cheat::WorldToScreenEx(AimedAt->FeetPos, feetScreenPos, ViewMatrix, WindowX, WindowY);
	//float FTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(feetScreenPos.x, feetScreenPos.y)));


	vec2 feetScreenPos = vec2(0, 0);
	vec2 headScreenPos = vec2(0, 0);
	if (!Cheat::IsEnemyLoadedR(AimedAt, headScreenPos, feetScreenPos, FEET_ONLY))
		return;
	
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(WindowX / 2, WindowY), ImVec2(feetScreenPos.x, feetScreenPos.y), Color, 0.60f);
}



// Enemy Functions
Angle Cheat::AngleToEnemy(PlayerEnt* enemy, vec3 AbsPositions) {
	Angle Res = Angle(0, 0, 0);
	// Calculate Yaw (horizontal angle)
	float azimuth_xy = atan2f(AbsPositions.y, AbsPositions.x);
	Res.yaw = azimuth_xy * (180.0f / M_PI) + 90.0f;

	// Calculate Pitch (vertical angle)
	float hypotenuse = sqrtf(AbsPositions.x * AbsPositions.x + AbsPositions.y * AbsPositions.y + AbsPositions.z * AbsPositions.z);
	Res.pitch = asinf(AbsPositions.z / hypotenuse) * (180.0f / M_PI);
	Res.roll = 0.0f;
	return Res;
}
Angle Cheat::AngleToEnemy(PlayerEnt* enemy) {
	Angle Res = Angle(0, 0, 0);
	// Angle To HEAD!
	float abspos_x = (enemy->HeadPos.x) - LocalPlayer->HeadPos.x;
	float abspos_y = (enemy->HeadPos.y) - LocalPlayer->HeadPos.y;
	float abspos_z = (enemy->HeadPos.z) - LocalPlayer->HeadPos.z;


	// Calculate Yaw (horizontal angle)
	float azimuth_xy = atan2f(abspos_y, abspos_x);
	Res.yaw = azimuth_xy * (180.0f / M_PI) + 90.0f;

	// Calculate Pitch (vertical angle)
	float hypotenuse = sqrtf(abspos_x * abspos_x + abspos_y * abspos_y + abspos_z * abspos_z);
	Res.pitch = asinf(abspos_z / hypotenuse) * (180.0f / M_PI);
	Res.roll = 0.0f;
	return Res;
}

float Cheat::Dist(PlayerEnt* enemy)
{
	float abspos_x = (enemy->HeadPos.x) - LocalPlayer->HeadPos.x;
	float abspos_y = (enemy->HeadPos.y) - LocalPlayer->HeadPos.y;
	float abspos_z = (enemy->HeadPos.z) - LocalPlayer->HeadPos.z;
	return sqrtf(abspos_x * abspos_x + abspos_y * abspos_y);
}

bool Cheat::IsEnemyLoaded(PlayerEnt* enemy, vec2 HeadScreen, vec2 FeetScreen, int Index) {
	switch (Index)
	{
	case HEAD_ONLY:
		if (Cheat::WorldToScreenEx(enemy->HeadPos, HeadScreen, ViewMatrix, WindowX, WindowY))
			return true;
		break;
	case FEET_ONLY:
		if (Cheat::WorldToScreenEx(enemy->FeetPos, FeetScreen, ViewMatrix, WindowX, WindowY))
			return true;
		break;
	case HEAD_AND_FEET:
		if (Cheat::WorldToScreenEx(enemy->HeadPos, HeadScreen, ViewMatrix, WindowX, WindowY) && Cheat::WorldToScreenEx(enemy->FeetPos, FeetScreen, ViewMatrix, WindowX, WindowY))
			return true;
		break;
	case ANY:
		if (Cheat::WorldToScreenEx(enemy->HeadPos, HeadScreen, ViewMatrix, WindowX, WindowY) || Cheat::WorldToScreenEx(enemy->FeetPos, FeetScreen, ViewMatrix, WindowX, WindowY))
			return true;
		break;
	default:
		return false;
		break;
	}


	return true;
}
bool Cheat::IsEnemyLoadedR(PlayerEnt* enemy, vec2& HeadScreen, vec2& FeetScreen, int Index) {

	switch (Index)
	{
	case HEAD_ONLY:
		if (Cheat::WorldToScreenEx(enemy->HeadPos, HeadScreen, ViewMatrix, WindowX, WindowY))
			return true;
		break;
	case FEET_ONLY:
		if (Cheat::WorldToScreenEx(enemy->FeetPos, FeetScreen, ViewMatrix, WindowX, WindowY))
			return true;
		break;
	case HEAD_AND_FEET:
		if (Cheat::WorldToScreenEx(enemy->HeadPos, HeadScreen, ViewMatrix, WindowX, WindowY) && Cheat::WorldToScreenEx(enemy->FeetPos, FeetScreen, ViewMatrix, WindowX, WindowY))
			return true;
		break;
	//case ANY:
	//	if (Cheat::WorldToScreenEx(enemy->HeadPos, HeadScreen, ViewMatrix, WindowX, WindowY) || Cheat::WorldToScreenEx(enemy->FeetPos, FeetScreen, ViewMatrix, WindowX, WindowY))
	//		return true;
	//	break;
	default:
		return false;
		break;
	}
	return true;
}


//Cares About The Dist!
bool Cheat::IsEnemyInFOV(PlayerEnt* enemy, float* FOV, vec2 HEnemyScreen, vec2 FEnemyScreen, vec2& DistToEnemy, int index) {
	DistToEnemy.x = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(HEnemyScreen.x, HEnemyScreen.y)));
	DistToEnemy.y = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(FEnemyScreen.x, FEnemyScreen.y)));
	switch (index)
	{
	case HEAD_ONLY:
		if (DistToEnemy.x < *FOV) {
			return true;
		}
		break;
	case FEET_ONLY:
		if (DistToEnemy.y < *FOV) {
			return true;
		}
		break;
	case HEAD_AND_FEET:
		if (DistToEnemy.x < *FOV && DistToEnemy.y < *FOV) {
			return true;
		}
		break;
	case ANY:
		if (DistToEnemy.x < *FOV || DistToEnemy.y < *FOV) {
			return true;
		}
		break;
	default:
		return false;
		break;
	}

	return false;
}

//Doesn't Care about Dist, Just Wants The Result!
bool Cheat::IsEnemyInFOV(PlayerEnt* enemy, float* FOV, vec2& HEnemyScreen, vec2& FEnemyScreen, int index) {
	vec2 DistToEnemy = vec2(abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(HEnemyScreen.x, HEnemyScreen.y))),
						    abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(FEnemyScreen.x, FEnemyScreen.y))));

	switch (index)
	{
	case HEAD_ONLY:
		if (DistToEnemy.x < *FOV) {
			return true;
		}
		break;
	case FEET_ONLY:
		if (DistToEnemy.y < *FOV) {
			return true;
		}
		break;
	case HEAD_AND_FEET:
		if (DistToEnemy.x < *FOV && DistToEnemy.y < *FOV) {
			return true;
		}
		break;
	case ANY:
		if (DistToEnemy.x < *FOV || DistToEnemy.y < *FOV) {
			return true;
		}
		break;
	default:
		return false;
		break;
	}

	return false;
}

bool Cheat::IsEnemyAimingAtMe(PlayerEnt* enemy) {

	Vector3 dirToPlayer = { LocalPlayer->HeadPos.x - enemy->HeadPos.x,
							LocalPlayer->HeadPos.y - enemy->HeadPos.y,
							LocalPlayer->HeadPos.z - enemy->HeadPos.z };

	Normalize(dirToPlayer);

	float EnemyYaw = enemy->ViewAngles.yaw * (M_PI / 180.0f);
	float EnemyPitch = enemy->ViewAngles.pitch * (M_PI / 180.0f);

	Vector3 EnemyForward = {
		cosf(EnemyPitch) * cosf(EnemyYaw),
		cosf(EnemyPitch) * sinf(EnemyYaw),
		sinf(EnemyPitch)
	};


	float EnemyDot = DotProduct(EnemyForward, dirToPlayer);
	float EnemyAngle = acosf(EnemyDot) * (180.0f / M_PI);

	Vector3 crossProduct = CrossProduct(EnemyForward, dirToPlayer);

	//printf("Enemy Angle: %.2f\nEnemy Dot: %.2f\nCross Z: %.2f\n\n", EnemyAngle, EnemyDot, crossProduct.z);


	if (900 > EnemyAngle && EnemyAngle <= 95.5f && EnemyAngle >= 84.0f && crossProduct.z < 0.0f)
		return true;
	return false;
}



//Gun Cheats (Done)
void GunCheats::InfAmmo(){
	if (Settings::GunCheats::bInfiniteAmmo && LocalPlayer && HealthD > 0 && !PlayerModeD) {
		CurrentAmmoD = 99;
		CurrentMagD = 99;
		Memory::Nop((BYTE*)(AmmoLoc), 2);
	}
	else if(LocalPlayer && HealthD > 0 && !PlayerModeD) {
		CurrentAmmoD = 50;
		CurrentMagD = 50;
		Memory::Patch((BYTE*)(AmmoLoc), (BYTE*)"\xFF\x08", 2);
	}
}
void GunCheats::NoRecoil()
{
	if (Settings::GunCheats::bNoRecoil && LocalPlayer && HealthD > 0 && !PlayerModeD) {

		Memory::Nop((BYTE*)(SmallSpreadLoc), 3);//Spread
		Memory::Nop((BYTE*)(SmallSpread2Loc), 8);//Spread

		Memory::Patch((BYTE*)SpreadLoc, (BYTE*)"\x90\x90\x90\x90\x90", 5);//Pitch-Spread
		Memory::Patch((BYTE*)RXveloLoc, (BYTE*)"\x90\x90\x90\x90\x90", 5);//Spread X-Velocity KnockBack
		Memory::Patch((BYTE*)RYveloLoc, (BYTE*)"\x90\x90\x90\x90\x90", 5);//Spread Y-Velocity KnockBack
		Memory::Patch((BYTE*)RJumpVeloLoc, (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90", 8);//Spread Jump KnockBack
	}
	else if (LocalPlayer && HealthD > 0 && !PlayerModeD){
		Memory::Patch((BYTE*)(SmallSpreadLoc), (BYTE*)"\xFF\x46\x1C", 3);//Spread
		Memory::Patch((BYTE*)(SmallSpread2Loc), (BYTE*)"\xF3\x0F\x5C\x05\x88\xBB\x55\x00", 8);//Random Bullet

		Memory::Patch((BYTE*)SpreadLoc, (BYTE*)"\xF3\x0F\x11\x56\x38", 5);//Pitch-Spread
		Memory::Patch((BYTE*)RXveloLoc, (BYTE*)"\xF3\x0F\x11\x40\x10", 5);//Spread X-Velocity KnockBack
		Memory::Patch((BYTE*)RYveloLoc, (BYTE*)"\xF3\x0F\x58\x40\x10", 5);//Spread Y-Velocity KnockBack
		Memory::Patch((BYTE*)RJumpVeloLoc, (BYTE*)"\x0F\x57\xC0\xF3\x0F\x11\x48\x18", 8);//Spread Jump KnockBack
	}
}
void GunCheats::RapidFire()
{
	if (Settings::GunCheats::bRapidFire && LocalPlayer && HealthD > 0 && !PlayerModeD) {
		Memory::Patch((BYTE*)RapidLoc, (BYTE*)"\x90\x90\x90\x90\x90\x90", 6);//Rapid-Fire
	}
	else if(LocalPlayer && HealthD > 0 && !PlayerModeD){
		Memory::Patch((BYTE*)RapidLoc, (BYTE*)"\x89\x9D\xEC\x01\x00\x00", 6);//Rapid-Fire
	}
}
void GunCheats::OneShotKill()
{
	if (LocalPlayer && HealthD > 0 && !PlayerModeD) {
		if (Settings::GunCheats::bOneShotKill) {
			DamageD = 9999;
		}
		else {
			DamageD = 20;
		}
	}
}


//Player Cheats
void PlayerCheats::DisableParticles()
{
	if (Settings::PlayerCheats::ParticlesState) {
		Memory::Nop((BYTE*)ParticlesLoc, 7u);
		Memory::Nop((BYTE*)RectanglesLoc, 5u);
	}
	else {
		Memory::Patch((BYTE*)ParticlesLoc, (BYTE*)"\x89\x14\x8D\x30\xED\x57\x00", 7);
		Memory::Patch((BYTE*)RectanglesLoc, (BYTE*)"\xE8\x83\x10\xFE\xFF", 5);
	}
}
void PlayerCheats::NoGravity() {
	if (Settings::PlayerCheats::NoGravityState)
		Memory::Nop((BYTE*)GravityLoc, 3);
	else
		Memory::Patch((BYTE*)GravityLoc,(BYTE*)"\x89\x4E\x48", 3);
	
}
//TODO
void PlayerCheats::NoClip()
{
}
//TODO
void PlayerCheats::InfHealth()
{
}

//W2s's
bool Cheat::WorldToScreenEx(vec3&& pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight)
{
	Vector4 clipCoords;

	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 2.0f)
	{

		return false;
	}
	vec3 NDC{ clipCoords.x / clipCoords.w, clipCoords.y / clipCoords.w, clipCoords.z / clipCoords.w };

	// Corrected the screen coordinates calculation
	screen.x = (NDC.x + 1.0f) * 0.5f * windowWidth;
	screen.y = (1.0f - NDC.y) * 0.5f * windowHeight;
	//	screen.x = (windowWidth / 2.0f * NDC.x) + (windowWidth / 2.0f);
	//	screen.y = -(windowHeight / 2.0f * NDC.y) + (windowHeight / 2.0f);

	return true;
}
bool Cheat::WorldToScreenEx(vec3& pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight)
{
	Vector4 clipCoords;

	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 2.0f)
	{

		return false;
	}
	vec3 NDC{ clipCoords.x / clipCoords.w, clipCoords.y / clipCoords.w, clipCoords.z / clipCoords.w };

	// Corrected the screen coordinates calculation
	screen.x = (NDC.x + 1.0f) * 0.5f * windowWidth;
	screen.y = (1.0f - NDC.y) * 0.5f * windowHeight;
	//	screen.x = (windowWidth / 2.0f * NDC.x) + (windowWidth / 2.0f);
	//	screen.y = -(windowHeight / 2.0f * NDC.y) + (windowHeight / 2.0f);

	return true;
}

