#pragma once
extern enum ImGuiKey;
extern struct ImVec2;
using std::string;
struct Menu {
	static int8_t TraceRes;

	//Debug Console
	static void CreateDebugConsole();
	static void CleanAndExit();

	static bool ShowMenu;

	static void VerticalSeperator();

	static bool ContextDone;
	static void SetupContext(HDC& hdc);

	static std::string vkToString(int vk);
	static bool ImguiDone;

	static HGLRC MenuContext;
	static HGLRC GameConext;

	static HWND GameWindowH;
	static bool Hotkey(const char* label, int* key, const ImVec2& size);
	static void Init();
	static void ToggleMenu();
	static void StartRender();
	static void RenderM();
};

