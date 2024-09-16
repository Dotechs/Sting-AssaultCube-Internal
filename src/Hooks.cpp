#include "Constants.h"
#include "GeneratedCode.h"
#include "Hooks.h"
#include "Menu.h"

void Hooks::InitHooks() {
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
}

//SwapBuffers
Hooks::SwapBuffersT Hooks::SwapBuffersO;
uintptr_t* Hooks::SwapBuffersTar;

//WndProc
LONG_PTR Hooks::WndProcOState;

//ClipCursor
Hooks::ClipCursorT Hooks::ClipCursorO;
uintptr_t* Hooks::ClipCursorTar;

////TraceShoot
//Hooks::TraceShootWrapperT Hooks::TraceShootWrapperO;
//uintptr_t* Hooks::TraceShootWrapperTar;
////TraceLine
//Hooks::TraceLineT Hooks::TraceLineO;
//uintptr_t* Hooks::TraceLineTar;



//TODO :FIX (SHOOTS EVERY PLAYER)
//bool IsFirst = true;
//std::thread th;
//void ChangeState() {
//	std::this_thread::sleep_for(std::chrono::seconds(3));
//	IsFirst = false;
//	CoolDown = false;
//}
//int __cdecl Hooks::TraceShootWrapperH(int* a, float* b, int c, float* d, int* e, char f){//Who Is shooting?
//
//	//printf("CALLED\n\n");
//	if (a != (int*)LocalPlayer && !*PRealLocalMode && !LocalPlayer->PlayerMode && *PRealHealth > 0 && !CoolDown)
//	{
//		PlayerEnt* Attacker = (PlayerEnt*)a;
//		AttackerName = Attacker->Name;
//
//		CoolDown = true;
//		if(IsFirst)
//			th = std::thread(ChangeState);
//		else {
//			th.join();
//			th = std::thread(ChangeState);
//		}
//
//		return TraceShootWrapperO(a, b, c, d, e, f);
//
//	}
//
//	////return Attacked;
//}


