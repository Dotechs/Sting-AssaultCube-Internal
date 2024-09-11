#include "Constants.h"
#include "GeneratedCode.h"
#include "Hooks.h"
#include "Menu.h"
#include <Cheat.h>

//SwapBuffers
Hooks::SwapBuffersT Hooks::SwapBuffersO;
uintptr_t* Hooks::SwapBuffersTar;

//WndProc
LONG_PTR Hooks::WndProcOState;

//ClipCursor
Hooks::ClipCursorT Hooks::ClipCursorO;
uintptr_t* Hooks::ClipCursorTar;

//TraceShoot
Hooks::TraceShootWrapperT Hooks::TraceShootWrapperO;
uintptr_t* Hooks::TraceShootWrapperTar;

//TraceLine
Hooks::TraceLineT Hooks::TraceLineO;
uintptr_t* Hooks::TraceLineTar;

int __cdecl Hooks::TraceLineH(float* CrossLocation, int EnemyLoopEnt, int  LocalLocation, int* SomeBool)
{
	return TraceLineO(CrossLocation, EnemyLoopEnt, LocalLocation, SomeBool);
}

//{
//	//int8_t res1;
//	//TraceLineO(a1, a2, arg_0, arg_4, a5, a6);
//	//__asm {
//	//	mov res1, al
//	//}
//	//if (a1 = (float*)LocalPlayer) {
//	//	printf("%c\n", res1);
//	//}
//	return TraceLineO(a1, a2, arg_0, arg_4, a5, a6);
//}
bool IsFirst = true;
std::thread th;
void ChangeState() {
	std::this_thread::sleep_for(std::chrono::seconds(3));
	IsFirst = false;
	CoolDown = false;
}
int __cdecl Hooks::TraceShootWrapperH(int* a, float* b, int c, float* d, int* e, char f){//Who Is shooting?

	if ((PlayerEnt*)a != LocalPlayer && !*PRealLocalMode && !LocalPlayer->PlayerMode && *PRealHealth > 0 && !CoolDown)
	{
		PlayerEnt* Attacker = (PlayerEnt*)a;
		AttackerName = Attacker->Name;
		
		CoolDown = true;
		if(IsFirst)
			th = std::thread(ChangeState);
		else {
			th.join();
			th = std::thread(ChangeState);
		}


	}

	////return Attacked;
	return TraceShootWrapperO(a, b, c, d, e, f);
}


//TraceLine:
//
//int Hooks::TraceLineH(float* LocalPos, int* LoopEnt, float* CrossHairPos, int* num)
//{
//	if (*LocalPos == LocalPlayer->HeadPos.x && LoopEnt != (int*)LocalPlayer) {
//		PlayerEnt* LoopModel = (PlayerEnt*)LoopEnt;
//		if (LoopModel->TeamID != LocalPlayer->TeamID) {
//			return 2;
//		}
//		else {
//			return 0;
//		}
//	}
//
//	//return 2;// Crazy HeadShot
//	//return 1;// Crazy BodyShot
//	//return 0;// Can't hit :(
//	return TraceLineO( &LocalPlayer->HeadPos.x,LoopEnt, CrossHairPos, num );
//}
//




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
