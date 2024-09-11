#pragma once
#include <Windows.h>
#include <imgui.h>
#define HealthD			LocalPlayer->Health
#define PlayerModeD		LocalPlayer->PlayerMode
#define CurrentAmmoD	LocalPlayer->GunEnt->AmmoData1->CurrentAmmo
#define CurrentMagD		LocalPlayer->GunEnt->AmmoData1->CurrentMag
#define GunEntD			LocalPlayer->GunEnt
#define SpreadD			LocalPlayer->inventory->Spread
#define DamageD			LocalPlayer->GunEnt->GeneralData->GunDamage
#define M_PI			3.14159265358979323846
//#define obf(std::string) []() { static auto result = Obf::Xor_String<sizeof(std::string)/sizeof(char)>(std::string); return result(); }()

const ImVec4 Red4 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
const ImVec4 Green4 = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
const ImVec4 Blue4 = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
const ImVec4 Yellow4 = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
const ImVec4 Orange4 = ImVec4(1.0f, 0.65f, 0.0f, 1.0f);
const ImVec4 Purple4 = ImVec4(0.5f, 0.0f, 0.5f, 1.0f);
const ImVec4 Cyan4 = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
const ImVec4 Magenta4 = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);
const ImVec4 White4 = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
const ImVec4 Black4 = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
const ImVec4 LightBlack4 = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
const ImVec4 Gray4 = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
const ImVec4 Pink4= ImVec4(1.0f, 0.75f, 0.8f, 1.0f);
const ImVec4 Lime4 = ImVec4(0.75f, 1.0f, 0.0f, 1.0f);
const ImVec4 DarkRed4 = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
const ImU32 White = IM_COL32(255, 255, 255, 255);
const ImU32 Black = IM_COL32(0, 0, 0, 255);
const ImU32 Red = IM_COL32(255, 0, 0, 255);
const ImU32 Green = IM_COL32(0, 255, 0, 255);
const ImU32 Blue = IM_COL32(0, 0, 255, 255);
const ImU32 Yellow = IM_COL32(255, 255, 0, 255);
const ImU32 Cyan = IM_COL32(0, 255, 255, 255);
const ImU32 Magenta = IM_COL32(255, 0, 255, 255);
const ImU32 Orange = IM_COL32(255, 165, 0, 255);
const ImU32 Purple = IM_COL32(128, 0, 128, 255);
const ImU32 Pink = IM_COL32(255, 192, 203, 255);
const ImU32 Brown = IM_COL32(165, 42, 42, 255);
const ImU32 Gray = IM_COL32(128, 128, 128, 255);
const ImU32 LightGray = IM_COL32(211, 211, 211, 255);
const ImU32 DarkGray = IM_COL32(64, 64, 64, 255);
const ImU32 DarkRed = IM_COL32(139, 0, 0, 255);
const ImU32 DarkGreen = IM_COL32(0, 100, 0, 255);
const ImU32 DarkBlue = IM_COL32(0, 0, 139, 255);
const ImU32 Gold = IM_COL32(255, 215, 0, 255);

struct Constants {
	static HMODULE DllHandle;
	static HMODULE AimbotHandle;
	static HMODULE EspHandle;
	static HMODULE AimLineHandle;
	static uintptr_t AcModuleBase;
	static bool  ChoosingAimbotKey;
	static bool  ChoosingWallBangKey;
	static bool  ChoosingSilentKey;

	//WallBang
	static bool WallBangNopped;
	static bool WallBangNoppingRight;

	//Silent
	static bool SilentNopped;
	static bool SilentNoppingRight;
};