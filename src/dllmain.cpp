#include "pch.h"

#include "Constants.h"
#include "Menu.h"
#include "Hooks.h"
#include"Settings.h"
#include"Aimbot.h"
#include <GeneratedCode.h>
#include "WallBang.h"
#include <Memory.h>
HMODULE Constants::DllHandle;
uintptr_t Constants::AcModuleBase;
HMODULE Constants::EspHandle;
bool Constants::ChoosingAimbotKey = false;
bool Constants::ChoosingWallBangKey = false;
bool Constants::ChoosingSilentKey = false;

bool Constants::WallBangNopped = false;
bool Constants::WallBangNoppingRight = false;

bool Constants::SilentNopped = false;
bool Constants::SilentNoppingRight = false;

void Updating() {
	if (!Constants::AcModuleBase)
		Constants::AcModuleBase = (uintptr_t)GetModuleHandleA("ac_client.exe");
	while (Constants::AcModuleBase) {
		PlayerEntAddress = (DWORD*)(Constants::AcModuleBase + 0x17E0A8);
		LocalPlayer = (PlayerEnt*)(*PlayerEntAddress);
		CurPlayers = *((int32_t*)(Constants::AcModuleBase + 0x18AC0C));
		EntList = (int32_t*)(Constants::AcModuleBase + 0x18AC04);

		WindowX = *(uintptr_t*)0x591ED8;
		WindowY = *(uintptr_t*)0x591EDC;
		ViewMatrix = (float*)0x57DFD0;
		CursorPos = (Vector3*)(0x592064);

		FOV = (float*)(Constants::AcModuleBase + 0x18A7CC);
		Speed = (float*)(0x55BAD0);
		AmmoLoc = (Constants::AcModuleBase + 0xC73EF);
		GravityLoc = (Constants::AcModuleBase + 0xC2375);
		RapidLoc = (Constants::AcModuleBase + 0xCB795);
		SmallSpreadLoc = (Constants::AcModuleBase + 0xC730E);
		SpreadLoc = (Constants::AcModuleBase + 0xC2EC3);
		RXveloLoc = (Constants::AcModuleBase + 0xC8DD2);
		RYveloLoc = (Constants::AcModuleBase + 0xC8DFB);
		RJumpVeloLoc = (Constants::AcModuleBase + 0xC8E00);
		RectanglesLoc = (Constants::AcModuleBase + 0x7D188);
		ParticlesLoc = (Constants::AcModuleBase + 0x692A2);
		TimeRemaining = (uintptr_t*)(Constants::AcModuleBase + 0x17E150);
		SmallSpread2Loc = (uintptr_t)(Constants::AcModuleBase + 0xc7376);

		GernadeAddr = (DWORD**)(Constants::AcModuleBase + 0x190D10);
		if (GernadeAddr != nullptr && *GernadeAddr != nullptr)
			Gernade = (GernadeEnt*)(**GernadeAddr);

		MaxEnemies = ((CurPlayers - 1) < 0) ? 0 : (CurPlayers - 1);

		GeneratedCode::EnemyVecUpdate();
		MapName = (0x5987A0);
		if (IsFirstTime && LocalPlayer) {
			PRealLocalMode = &LocalPlayer->PlayerMode;
			PRealHealth = &LocalPlayer->Health;
			IsFirstTime = false;
		}
	}
}

void BackLoop() {
	if (!Constants::AcModuleBase)
		Constants::AcModuleBase = (uintptr_t)GetModuleHandleA("ac_client.exe");
	while (Constants::AcModuleBase) {
		/////////////////
		if (GetAsyncKeyState(VK_INSERT) & 0b1) {
			Menu::ToggleMenu();
		}
		if (GetAsyncKeyState(VK_END) & 0b1) {
			Menu::CleanAndExit();
		}

		//Aimbot KeyCheck
		if (Settings::Aimbot::AimbotKey != 0) {
			if (GetAsyncKeyState(Settings::Aimbot::AimbotKey) && !Constants::ChoosingAimbotKey/* && !Settings::Aimbot::bAimbotState*/) {
				Settings::Aimbot::bAimbotState = true;
			}
			else {
				Settings::Aimbot::bAimbotState = false;
			}
		}
		else {
			Settings::Aimbot::bAimbotState = true;
		}

		//WallBang KeyCheck
		if (Settings::WallBang::bWallBang) {

			if (Settings::WallBang::WallBangKey != 0) {
				if (GetAsyncKeyState(Settings::WallBang::WallBangKey/* & 0b1*/)/* && !Constants::ChoosingWallBangKey*/) {
					Settings::WallBang::bWallBangState = true;
					WallBang::ActivateWallBang();
					//Constants::WallBangNoppingRight = true;
				}
				else {
					Settings::WallBang::bWallBangState = false;
					WallBang::ActivateWallBang();
					//Constants::WallBangNoppingRight = false;
				}
			}
			else {
				Settings::WallBang::bWallBangState = true;
				//Constants::WallBangNoppingRight = true;
				WallBang::ActivateWallBang(); 
			}
			//printf("State : &b\nInstruction : &b", Settings::WallBang::bWallBangState)

		}
		else {
			Settings::WallBang::bWallBangState = false;
			WallBang::ActivateWallBang(); 
		}

		//Silent KeyCheck
		if (Settings::Silent::SilentKey != 0) {
			if (GetAsyncKeyState(Settings::Silent::SilentKey)/* && !Constants::ChoosingSilentKey*/) {
				Settings::Silent::bSilentState = true;
				Constants::SilentNoppingRight = true;
			}
			else {
				Settings::Silent::bSilentState = false;
				Constants::SilentNoppingRight = false;
			}
		}
		else {
			Settings::Silent::bSilentState = true;
			Constants::SilentNoppingRight = true;
		}
	}
}

void SwapBuffersInit() {
	Menu::CreateDebugConsole();

	Constants::AcModuleBase = (uintptr_t)GetModuleHandleA("ac_client.exe");

	MH_STATUS MhStats = MH_Initialize();
	if (MhStats != MH_OK)
	{
		std::cerr << "[Error] Failed To Initialize MinHook : " << MH_StatusToString(MhStats) << "\t\tExiting...\n";
		Sleep(1000);
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
		FreeConsole();
		FreeLibraryAndExitThread(Constants::DllHandle, 0);
	}

	Hooks::SwapBuffersTar = (uintptr_t*)GetProcAddress(GetModuleHandleA("gdi32.dll"), "SwapBuffers"); 
	Hooks::ClipCursorTar = (uintptr_t*)GetProcAddress(GetModuleHandleA("user32.dll"), "ClipCursor");
	Hooks::TraceShootWrapperTar = (uintptr_t*)(Constants::AcModuleBase + 0xCA250);
	Hooks::TraceLineTar = (uintptr_t*)(Constants::AcModuleBase + 0xCA5E0);

	if (MH_CreateHook((LPVOID)Hooks::SwapBuffersTar,(LPVOID)Hooks::SwapBuffersH,(LPVOID*)&Hooks::SwapBuffersO) != MH_OK) {
		std::cout << "[Failed] Hooking SwapBuffers!\n";
		Menu::CleanAndExit();
	}

	if (MH_CreateHook((LPVOID)Hooks::ClipCursorTar, (LPVOID)Hooks::ClipCursorH, (LPVOID*)&Hooks::ClipCursorO) != MH_OK) {
		std::cout << "[Failed] Hooking ClipCursor!\n";
		Menu::CleanAndExit();
	}

	//if (MH_CreateHook((LPVOID)Hooks::TraceLineTar, (LPVOID)Hooks::TraceLineH, (LPVOID*)&Hooks::TraceLineO) != MH_OK) {
	//	std::cout << "[Failed] Hooking TraceLine!\n";
	//	Menu::CleanAndExit();
	//}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) { // Enables The Hook
		std::cerr << "[Error] Failed to enable All Hooks!\n";
		Menu::CleanAndExit();
	}

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Constants::DllHandle = hModule;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SwapBuffersInit, hModule, NULL, NULL);
		Sleep(1000);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Updating, hModule, NULL, NULL);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)BackLoop, hModule, NULL, NULL);
	}
	return TRUE;
}

