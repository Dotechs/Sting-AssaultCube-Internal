#pragma once

class Hooks {
public:
	//SwapBuffers
	typedef BOOL(__stdcall* SwapBuffersT)(HDC hdc);
	static SwapBuffersT SwapBuffersO;

	static uintptr_t* SwapBuffersTar;

	static BOOL __stdcall SwapBuffersH(HDC hdc);
	//~Swap Buffers
	

	//WndProc
	static LONG_PTR WndProcOState; //instantiate
	static LRESULT __stdcall WndProcH(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//ClipCursor
	typedef BOOL(__stdcall* ClipCursorT)(const RECT*);//
	static ClipCursorT ClipCursorO;

	static uintptr_t* ClipCursorTar;


	static BOOL __stdcall ClipCursorH(const RECT* lpRect);



	//TraceLine
	//typedef int(__cdecl* TraceLineT)(float*, int, int, int*);
	//static TraceLineT TraceLineO;

	//static uintptr_t* TraceLineTar;
	//static int __cdecl TraceLineH(float*, int, int, int*);



	////TraceShootWrapper
	//typedef int(__cdecl* TraceShootWrapperT)(int*, float*, int, float*, int*, char);
	//static TraceShootWrapperT TraceShootWrapperO;

	//static uintptr_t* TraceShootWrapperTar;
	//static int __cdecl TraceShootWrapperH(int*, float*, int, float*, int*, char);


	//Functions
	static void InitHooks();
};