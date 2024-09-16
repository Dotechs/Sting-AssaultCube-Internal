
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <iostream>
#include <vector>
#include<thread>
#include<chrono>
#include "MinHook.h"
#include <cmath>
#include <thread>
#include <future>

#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
//Imgui
#include "imgui_impl_opengl2.h"
#include "imgui_impl_win32.h"
#include <imgui.h>

#if _WIN64
#pragma comment(lib, "libMinHook-x64-v141-mtd.lib")
#else
#pragma comment(lib, "libMinHook-x86-v141-mtd.lib")
#endif
