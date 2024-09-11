#pragma once

extern class PlayerEnt;

class Aimbot {
public:
	static void ActivateAimbot();
	static void ToggleAimbot();
	static void AimLine(PlayerEnt*);
};