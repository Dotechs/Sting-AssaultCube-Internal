#pragma once
#include "Structures.h"

extern class PlayerEnt;
extern class GernadeEnt;
extern struct ImColor;
class Cheat{
public:

	//General Cheat Functions
	static vec3 WorldToScreen(vec3&& pos);
	static bool WorldToScreenEx(vec3&& pos, vec3& screen, float matrix[16], int windowWidth, int windowHeight);
	static bool WorldToScreenEx(vec3& pos, vec3& screen, float matrix[16], int windowWidth, int windowHeight);
	static bool IsEnemyAimingAtMe(PlayerEnt* enemy);
	static float Dist(PlayerEnt*);

	static float DotProduct(const vec3& v1, const vec3& v2);
	static Vector3 CrossProduct(const Vector3& a, const Vector3& b);
	static void Normalize(Vector3& v);
	static float CalculateVectorAngle(Vector3& v1, Vector3& v2);
    static Vector3 AngleToDirection(float pitch, float yaw);

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
