#pragma once
#include "Structures.h"

extern class PlayerEnt;
extern class GernadeEnt;
extern struct ImColor;
class Cheat{
public:

	//Screen Functions
	static bool WorldToScreenEx(vec3&& pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight);
	static bool WorldToScreenEx(vec3& pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight);
	
	//Enemies Functions
	static bool IsEnemyAimingAtMe(PlayerEnt* enemy);
	// Index = 0 (Head Only), = 1 (FeetOnly), = 2 (Both!), = 3 (Any!)
	static bool IsEnemyLoaded(PlayerEnt* enemy, vec2 HeadScreen, vec2 FeetScreeen, int Index);
	static bool IsEnemyLoadedR(PlayerEnt* enemy, vec2& HeadScreen, vec2& FeetScreeen, int Index);

	// Index = 0 (Head Only), = 1 (FeetOnly), = 2 (Both!), = 3 (Any!)
	static bool IsEnemyInFOV(PlayerEnt* enemy, float* FOV, vec2 HEnemyScreen, vec2 FEnemyScreen, vec2& DistToEnemy, int index);
	static bool IsEnemyInFOV(PlayerEnt* enemy, float* FOV, vec2& HeadScreen, vec2& FeetScreen, int index);

	// Default, Will get the angle to enemy's head
	static Angle AngleToEnemy(PlayerEnt* enemy);
	// Gets the angle to enemy's custom position
	static Angle AngleToEnemy(PlayerEnt* enemy, vec3 AbsPositions);
	static float Dist(PlayerEnt*);



	static float DotProduct(const vec3& v1, const vec3& v2);
	static Vector3 CrossProduct(const Vector3& a, const Vector3& b);
	static void Normalize(Vector3& v);
	static float CalculateVectorAngle(Vector3& v1, Vector3& v2);
    static Vector3 AngleToDirection(float pitch, float yaw);

	static void SnapAimLine(PlayerEnt* aimedAt, ImColor& Color, float* FOV);
	static void SnapAimLine(PlayerEnt* aimedAt, ImColor& Color);

    // Function to calculate the 2D distance between two Vector2 points
	static float Distance2D(const Vector2& a, const Vector2& b);

    // Function to calculate angles between two 3D points
	static Vector3 CalculateAngle(Vector3& from, Vector3& to);



};

class GunCheats {
public:
	static void InfAmmo();
	static void NoRecoil();
	static void RapidFire();
	static void OneShotKill();
};

class PlayerCheats {
public:
	static void InfHealth();			//TODO
	static void NoClip();				//TODO
	static void Fly();					//TODO
	static void NoGravity();
	static void DisableParticles();
};
