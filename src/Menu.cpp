#include "pch.h"

#include "Cheat.h"
#include "Constants.h"
#include "GeneratedCode.h"
#include "Hooks.h"
#include "Menu.h"
#include "Settings.h"
#include "Aimbot.h"
#include "WallBang.h"
#include "Esp.h"
#include "Silent.h"
//OpenGL

bool Menu::ShowMenu;
bool Menu::ImguiDone;
bool Menu::ContextDone;
HGLRC Menu::MenuContext;
HGLRC Menu::GameConext;
HWND Menu::GameWindowH;
const ImVec2 WindowSize = ImVec2(600, 500);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern struct IMGUI_API ImGuiWindow;
//ImGui

std::string Menu::vkToString(int vk) {
#define caseStringify(x) case x: return std::string(#x + 3)
	char c[2] = { 0 };
	if (vk >= '0' && vk <= '9') { c[0] = (char)vk; return std::string(c); }
	if (vk >= 'A' && vk <= 'Z') { c[0] = (char)vk; return std::string(c); }
	switch (vk) {
	case VK_LBUTTON: return "LMB";
	case VK_RBUTTON: return "RMB";
		caseStringify(VK_CANCEL);
	case VK_MBUTTON: return "MMB";
	case VK_XBUTTON1: return "MB1";
	case VK_XBUTTON2: return "MB2";

		caseStringify(VK_BACK);
		caseStringify(VK_TAB);
		caseStringify(VK_CLEAR);
		caseStringify(VK_RETURN);
		caseStringify(VK_SHIFT);
		caseStringify(VK_CONTROL);
		caseStringify(VK_MENU);
		caseStringify(VK_PAUSE);
		caseStringify(VK_CAPITAL);
		caseStringify(VK_KANA);
		caseStringify(VK_JUNJA);
		caseStringify(VK_FINAL);
		caseStringify(VK_KANJI);
		caseStringify(VK_ESCAPE);
		caseStringify(VK_CONVERT);
		caseStringify(VK_NONCONVERT);
		caseStringify(VK_ACCEPT);
		caseStringify(VK_MODECHANGE);
		caseStringify(VK_SPACE);
		caseStringify(VK_PRIOR);
		caseStringify(VK_NEXT);
		caseStringify(VK_END);
		caseStringify(VK_HOME);
		caseStringify(VK_LEFT);
		caseStringify(VK_UP);
		caseStringify(VK_RIGHT);
		caseStringify(VK_DOWN);
		caseStringify(VK_SELECT);
		caseStringify(VK_PRINT);
		caseStringify(VK_EXECUTE);
		caseStringify(VK_SNAPSHOT);
		caseStringify(VK_INSERT);
		caseStringify(VK_DELETE);
		caseStringify(VK_HELP);
		caseStringify(VK_LWIN);
		caseStringify(VK_RWIN);
		caseStringify(VK_APPS);
		caseStringify(VK_SLEEP);
		caseStringify(VK_NUMPAD0);
		caseStringify(VK_NUMPAD1);
		caseStringify(VK_NUMPAD2);
		caseStringify(VK_NUMPAD3);
		caseStringify(VK_NUMPAD4);
		caseStringify(VK_NUMPAD5);
		caseStringify(VK_NUMPAD6);
		caseStringify(VK_NUMPAD7);
		caseStringify(VK_NUMPAD8);
		caseStringify(VK_NUMPAD9);
	case VK_MULTIPLY: return "*";
		caseStringify(VK_ADD);
		caseStringify(VK_SEPARATOR);
		caseStringify(VK_SUBTRACT);
		caseStringify(VK_DECIMAL);
	case VK_DIVIDE: return "/";
		caseStringify(VK_F1);
		caseStringify(VK_F2);
		caseStringify(VK_F3);
		caseStringify(VK_F4);
		caseStringify(VK_F5);
		caseStringify(VK_F6);
		caseStringify(VK_F7);
		caseStringify(VK_F8);
		caseStringify(VK_F9);
		caseStringify(VK_F10);
		caseStringify(VK_F11);
		caseStringify(VK_F12);
		caseStringify(VK_F13);
		caseStringify(VK_F14);
		caseStringify(VK_F15);
		caseStringify(VK_F16);
		caseStringify(VK_F17);
		caseStringify(VK_F18);
		caseStringify(VK_F19);
		caseStringify(VK_F20);
		caseStringify(VK_F21);
		caseStringify(VK_F22);
		caseStringify(VK_F23);
		caseStringify(VK_F24);
		caseStringify(VK_NUMLOCK);
		caseStringify(VK_SCROLL);
		caseStringify(VK_OEM_NEC_EQUAL);  // '=' key on numpad
		caseStringify(VK_OEM_FJ_MASSHOU); // 'Unregister word' key
		caseStringify(VK_OEM_FJ_TOUROKU); // 'Register word' key
		caseStringify(VK_OEM_FJ_LOYA);    // 'Left OYAYUBI' key
		caseStringify(VK_OEM_FJ_ROYA);    // 'Right OYAYUBI' key
		caseStringify(VK_LSHIFT);
		caseStringify(VK_RSHIFT);
		caseStringify(VK_LCONTROL);
		caseStringify(VK_RCONTROL);
	case VK_LMENU: return "LALT";
	case VK_RMENU: return "RALT";
		caseStringify(VK_BROWSER_BACK);
		caseStringify(VK_BROWSER_FORWARD);
		caseStringify(VK_BROWSER_REFRESH);
		caseStringify(VK_BROWSER_STOP);
		caseStringify(VK_BROWSER_SEARCH);
		caseStringify(VK_BROWSER_FAVORITES);
		caseStringify(VK_BROWSER_HOME);
		caseStringify(VK_VOLUME_MUTE);
		caseStringify(VK_VOLUME_DOWN);
		caseStringify(VK_VOLUME_UP);
		caseStringify(VK_MEDIA_NEXT_TRACK);
		caseStringify(VK_MEDIA_PREV_TRACK);
		caseStringify(VK_MEDIA_STOP);
		caseStringify(VK_MEDIA_PLAY_PAUSE);
		caseStringify(VK_LAUNCH_MAIL);
		caseStringify(VK_LAUNCH_MEDIA_SELECT);
		caseStringify(VK_LAUNCH_APP1);
		caseStringify(VK_LAUNCH_APP2);
		caseStringify(VK_OEM_1);      // ';:' for US
	case VK_OEM_PLUS: return "+";
	case VK_OEM_COMMA: return ",";
	case VK_OEM_MINUS: return "-";
	case VK_OEM_PERIOD: return ".";
	case VK_OEM_2: return "#";
		caseStringify(VK_OEM_3);  // '`~' for US
		caseStringify(VK_OEM_4);  //  '[{' for US
	case VK_OEM_5: return "^";
		caseStringify(VK_OEM_6);  //  ']}' for US
		caseStringify(VK_OEM_7);  //  ''"' for US
		caseStringify(VK_OEM_8);
		caseStringify(VK_OEM_AX);   //  'AX' key on Japanese AX kbd
	case VK_OEM_102: return "<";
		caseStringify(VK_ICO_HELP); //  Help key on ICO
		caseStringify(VK_ICO_00);   //  00 key on ICO
		caseStringify(VK_PROCESSKEY);
		caseStringify(VK_ICO_CLEAR);
		caseStringify(VK_PACKET);

	case 0: return "None";
	}

	// should not happen
	c[0] = (char)vk;
	return std::string(c);
}
bool Menu::Hotkey(const char* label, int* key, const ImVec2& size) {
	ImGui::Button(*key == 0 ? "Press!" : Menu::vkToString(*key).c_str(), size);
	if (ImGui::IsItemHovered()) {
		//Constants::ChoosingAimbotKey = true;
		//Constants::ChoosingSilentKey = true;
		//Constants::ChoosingWallBangKey = true;

		for (auto i = 0; i <= VK_PACKET; i++) {
			if (i == VK_INSERT || i == VK_END || i == VK_ESCAPE) continue;
			if (key == &Settings::Aimbot::AimbotKey) { if (i == Settings::WallBang::WallBangKey) { continue; } }
			else if (i == Settings::Aimbot::AimbotKey) continue;
			if (GetAsyncKeyState(i) & 0x8000) { // 0x8000 Flag checks if Key is currently being hold
				*key = i;
			}
		}
		if (Settings::WallBang::WallBangKey == VK_LBUTTON) {
			ImGui::BeginTooltip();
			ImGui::TextUnformatted("Left-Mouse isn't recommended for snipers or single shooting! Choose a long-holded key.");
			ImGui::EndTooltip();
		}
	}
	//Constants::ChoosingAimbotKey = false;
	//Constants::ChoosingSilentKey = false;
	//Constants::ChoosingWallBangKey = false;

	return true;
}

DWORD OLD = NULL;

void Menu::CreateDebugConsole() {
	if (AllocConsole()) {
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		freopen_s((FILE**)stdin, "CONIN$", "w", stdin);
		freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
	}
}
void Menu::Init() {
	GameWindowH = FindWindowA(NULL, "AssaultCube");

	ImGui::CreateContext();

	ImGui_ImplWin32_Init(GameWindowH);
	ImGui_ImplOpenGL2_Init();
	IMGUI_CHECKVERSION();

	Hooks::WndProcOState = SetWindowLongPtr(Menu::GameWindowH, GWLP_WNDPROC, (LONG_PTR)Hooks::WndProcH);


	ImGuiStyle* style = &ImGui::GetStyle();

	//style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	//style->ItemSpacing = ImVec2(12, 8);
	//style->ItemInnerSpacing = ImVec2(8, 6);
	//style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;      // Enable Gamepad Controls
	io.Fonts->AddFontFromFileTTF("C:\\Users\\Dot\\Desktop\\Fonts\\Roboto-Regular.ttf",13.0f); //Change

	ImGui::SetCurrentContext(ImGui::GetCurrentContext());
	ImGui::SetNextWindowSize(WindowSize);
	ImguiDone = true;
	std::cout << "Menu Init Success!\n";
}
void Menu::VerticalSeperator()
{
	ImGui::SameLine();
	ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
	ImGui::GetWindowDrawList()->AddLine(ImVec2(cursor_pos.x, cursor_pos.y), ImVec2(cursor_pos.x, cursor_pos.y + 300), IM_COL32(255, 255, 255, 255), 1.0f);
	ImGui::SameLine();
}
void Menu::SetupContext(HDC& hdc) {
	MenuContext = wglCreateContext(hdc);
	wglMakeCurrent(hdc, MenuContext);

	glMatrixMode(GL_PROJECTION);
	GLint ViewPort[4];
	glGetIntegerv(GL_VIEWPORT, ViewPort);
	glOrtho(0, ViewPort[2], ViewPort[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	ContextDone = true;
}
void Menu::StartRender()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	auto renderESP = std::async(std::launch::async, Menu::RenderM);
	//Menu::RenderM();

	renderESP.get();

}

void RenderVnHaxMenu() {
	ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiCond_Once);
	if (ImGui::Begin("VnHax Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {

		// Tabs at the top (Memory, ESP, Aimbot, Settings)
		if (ImGui::BeginTabBar("##MainTabs")) {
			if (ImGui::BeginTabItem("Aimbot")) {

				// Left side - Aimbot and Marco checkboxes (Sub-tabs)
				ImGui::BeginChild("##SideNav", ImVec2(150, 0), true);
				static bool aimbotEnabled = true;
				static bool marcoEnabled = false;

				ImGui::Checkbox("Aimbot", &aimbotEnabled);
				ImGui::Checkbox("Marco", &marcoEnabled);
				ImGui::EndChild();

				ImGui::SameLine();

				// Vertical separator
				ImDrawList* draw_list = ImGui::GetWindowDrawList();
				ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
				draw_list->AddLine(ImVec2(cursor_pos.x, cursor_pos.y), ImVec2(cursor_pos.x, cursor_pos.y + 500), IM_COL32(255, 255, 255, 255), 1.0f);

				ImGui::SameLine();

				// Right side - Main content area
				ImGui::BeginChild("##MainContent", ImVec2(0, 0), true);

				if (aimbotEnabled) {
					// Aimbot Settings
					ImGui::Text("Aimbot Settings");
					ImGui::Separator();

					static int aimbotMode = 2;
					static float aimbotSpeed = 22.0f;
					static float aimRegion = 86.24f;

					ImGui::Combo("Aimbot Mode", &aimbotMode, "Mode 1\0Mode 2\0Mode 3\0");
					ImGui::SliderFloat("Aimbot Speed", &aimbotSpeed, 0.0f, 100.0f, "%.0f");
					ImGui::SliderFloat("Aim Region Limit", &aimRegion, 0.0f, 100.0f, "%.3f");

					static ImVec4 aimColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
					ImGui::ColorEdit4("Aim Region Color", (float*)&aimColor);

					static bool aimAtDowned = true;
					static bool autoShoot = false;
					ImGui::Checkbox("Aim at Downed Enemies", &aimAtDowned);
					ImGui::Checkbox("Auto Shoot", &autoShoot);
				}

				if (marcoEnabled) {
					// Marco Settings
					ImGui::Text("Marco Settings");
					ImGui::Separator();

					static float mouseDragRatio = 3.0f;
					static bool autoFire = false;

					// Mouse Drag Ratio Slider
					ImGui::SliderFloat("Mouse Drag Ratio", &mouseDragRatio, 1.0f, 10.0f, "%.0f");

					// Auto Fire Checkbox
					ImGui::Checkbox("Auto Fire", &autoFire);
				}

				ImGui::EndChild();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Memory")) {
				// Memory Tab Content (Placeholder)
				ImGui::Text("Memory Settings");
				ImGui::Separator();
				ImGui::Text("Memory settings would go here.");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("ESP")) {
				// ESP Tab Content (Placeholder)
				ImGui::Text("ESP Settings");
				ImGui::Separator();
				ImGui::Text("ESP settings would go here.");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Settings")) {
				// Settings Tab Content (Placeholder)
				ImGui::Text("Settings");
				ImGui::Separator();
				ImGui::Text("Settings options would go here.");
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
	ImGui::End();
}


void Menu::RenderM()
{

	Esp::DrawEsp();

	if (Settings::PlayerCheats::GameInfo) {
		ImVec2 windowPos = ImVec2(/*WindowX/ 1.284, WindowY/ 4.087*/WindowX - 250, WindowY / 4.087); // Set to your desired position
		ImVec2 windowSize = ImVec2(250, 105); // Set to your desired size

		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Appearing /*ImGuiCond_FirstUseEver*/);
		ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

		ImGui::Begin("Game Information", nullptr,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoFocusOnAppearing);


		// Is Being Attacked
		if (CoolDown)
		{
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Under Attack by: %s", AttackerName);//Working
		}
		else
		{
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Safe");
		}



		// Match Time
		const char* Time = reinterpret_cast<const char*>(TimeRemaining);
		ImGui::Text("Match Time: %s", Time);
		ImGui::Text("Speed : %.2f", (LocalPlayer->VelocityByDirection.x * LocalPlayer->VelocityByDirection.x + LocalPlayer->VelocityByDirection.y * LocalPlayer->VelocityByDirection.y));

		// Map Name
		const char* Map = reinterpret_cast<const char*>(MapName);
		if (Map[0] == 'a' && Map[1] == 'c' && Map[2] == '_')
			ImGui::Text("Map: %s", Map);
		else
			ImGui::Text("Join A Game!");

		ImGui::End();
	}

	if (!ShowMenu) {
		return;
	}

	if (ImGui::Begin("Sting", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize)) {

		//Fix injecting on spectating ?
		ImGui::Text("Player State :");
		ImGui::SameLine();
		if (!*PRealLocalMode && *PRealHealth > 0)
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Alive");//Working
		else if (*PRealLocalMode == 1 && *PRealHealth < 0)
			ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Spectating");//Gray
		else if (*PRealLocalMode == 4) {
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Editing Mode");//Yellow
		}
		else
		{
			ImGui::TextColored(ImVec4(0.5f, 0.0f, 0.5f, 1.0f), "Disabled");//Working
		}


		if (*PRealLocalMode)
			ImGui::BeginDisabled();

		if (ImGui::BeginTabBar("Sting"))
		{
			//Esp Tab
			if (ImGui::BeginTabItem("ESP")) {
				// Left side - Aimbot and Marco checkboxes (Sub-tabs)
				if (ImGui::BeginChild("##EspSideNav", ImVec2(150, 300), true)) {
					ImGui::Checkbox("Box", &Settings::ESP::bBoxes);
					ImGui::Checkbox("Bones", &Settings::ESP::bBones);
					ImGui::Checkbox("Lines", &Settings::ESP::bSnapLines);
					ImGui::Checkbox("Gun", &Settings::ESP::bGun);
					ImGui::Checkbox("Distance", &Settings::ESP::bDistance);
					ImGui::Checkbox("Health", &Settings::ESP::bHealthBar);
					ImGui::Checkbox("Gernades", &Settings::ESP::bGernades);
					ImGui::Checkbox("Name", &Settings::ESP::bNames);
					ImGui::Checkbox("Show Player Count", &Settings::ESP::bShowPlayerCount);
					ImGui::Checkbox("Show Who is Aiming", &Settings::ESP::bShowWhoIsAiming);
					ImGui::EndChild();
				}

				VerticalSeperator();

				// Right side - Main content area
				if (ImGui::BeginChild("##MainEspContent", ImVec2(350, 300), true)) {
					//Boxes
					if (Settings::ESP::bBoxes) {
						if (ImGui::CollapsingHeader("Boxes", ImGuiTreeNodeFlags_SpanAvailWidth)) {
							ImGui::ColorEdit3("Box Color", (float*)&Settings::ESP::BoxC.Value);
						}
					}

					//Bones
					if (Settings::ESP::bBones) {
						if (ImGui::CollapsingHeader("Bones", ImGuiTreeNodeFlags_SpanAvailWidth)) {
							ImGui::ColorEdit3("Bone Color", (float*)&Settings::ESP::BoneC.Value);
						}
					}

					// Lines section
					if (Settings::ESP::bSnapLines) {
						if (ImGui::CollapsingHeader("Lines", ImGuiTreeNodeFlags_SpanAvailWidth)) {
							ImGui::ColorEdit3("Line Color", (float*)&Settings::ESP::SnapLinesC.Value);
							ImGui::Combo("Line Position", &Settings::ESP::EspLineIndex, Settings::ESP::SnapLinePosition, IM_ARRAYSIZE(Settings::ESP::SnapLinePosition));
						}
					}

					ImGui::EndChild();
				}
				//}
				ImGui::EndTabItem();
			}

			// Gun Tab
			if (ImGui::BeginTabItem("Player"))
			{
				if (ImGui::BeginChild("##GunSideNav", ImVec2(150, 300), true)) {
					if (ImGui::Checkbox("No Recoil", &Settings::GunCheats::bNoRecoil))
						GunCheats::NoRecoil();
					if (ImGui::Checkbox("Rapid Fire", &Settings::GunCheats::bRapidFire))
						GunCheats::RapidFire();
					if (ImGui::Checkbox("No Gravity", &Settings::PlayerCheats::NoGravityState))
						PlayerCheats::NoGravity();
					if (ImGui::Checkbox("One Shot Kill (Offline)", &Settings::GunCheats::bOneShotKill))
						GunCheats::OneShotKill();
					if (ImGui::Checkbox("Infinite Ammo (Offline)", &Settings::GunCheats::bInfiniteAmmo))
						GunCheats::InfAmmo();
					if (ImGui::Checkbox("Speed Hack V1", &Settings::PlayerCheats::SpeedHack)) {
						if (!Settings::PlayerCheats::SpeedHack) {
							VirtualProtect(Speed, 0x4, PAGE_EXECUTE_READWRITE, &OLD);
							*Speed = 0.001f;
							VirtualProtect(Speed, 0x4, OLD, &OLD);
						}
						else if (Settings::PlayerCheats::SpeedHack) {
							VirtualProtect(Speed, 0x4, PAGE_EXECUTE_READWRITE, &OLD);
						}
					}

					//if (ImGui::Checkbox("NoClip (Offline)", &Settings::PlayerCheats::NoClipState))
						//PlayerCheats::NoClip(); //Work on it, It  triggers
					ImGui::EndChild();

				}
				VerticalSeperator();

				if (ImGui::BeginChild("##MainGunContent", ImVec2(350, 300), true)) {

					if (Settings::PlayerCheats::SpeedHack) {
						ImGui::SliderFloat("Speed##Slider", Speed, 0.001f, 0.006000000354f, "%.7f", ImGuiSliderFlags_NoInput);
					}
					ImGui::EndChild();
				}
				ImGui::EndTabItem();
			}

			// Aimbot Tab
			if (ImGui::BeginTabItem("Aim"))
			{
				if (ImGui::BeginChild("##AimSideNav", ImVec2(150, 300), true)) {
					ImGui::Checkbox("Aimbot", &Settings::Aimbot::bAimbot);
					ImGui::Checkbox("Silent Aim", &Settings::Silent::bSilent);
					ImGui::Checkbox("WallBang", &Settings::WallBang::bWallBang);
					ImGui::EndChild();
				}

				VerticalSeperator();

				if (ImGui::BeginChild("##MainAimContent", ImVec2(350, 300), true)) {
					if (Settings::Aimbot::bAimbot) {
						if (ImGui::CollapsingHeader("Aimbot", ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen)) {

							ImGui::Combo("Aimbot Type", &Settings::Aimbot::AimbotTypeIndex, Settings::Aimbot::AimbotTypes, IM_ARRAYSIZE(Settings::Aimbot::AimbotTypes));
							ImGui::Combo("Aim Location", &Settings::Aimbot::AimbotHitPosIndex, Settings::AimLocations, IM_ARRAYSIZE(Settings::AimLocations));

							Menu::Hotkey("Aimbot Key", &Settings::Aimbot::AimbotKey, ImVec2(50, 30));


							if (Settings::Aimbot::AimbotTypeIndex == 1) {
								Settings::Aimbot::bAimbotFOV = true;
								ImGui::ColorEdit3("FOV Color", (float*)&Settings::Aimbot::AimbotFOVC.Value);
								ImGui::SliderFloat("FOV##slider", &Settings::Aimbot::AimbotFOV, 30.0f, 250.0f, "%.1f", ImGuiSliderFlags_NoInput);
								/*if (ImGui::TreeNodeEx("Aimbot FOV", ImGuiTreeNodeFlags_DefaultOpen)) {
									ImGui::TreePop();
								}*/
							}
							ImGui::Checkbox("Aim Line", &Settings::Aimbot::bAimbotAimLine);
							if (Settings::Aimbot::bAimbotAimLine) {
								ImGui::ColorEdit3("AimLine Color", (float*)&Settings::Aimbot::AimbotAimLineC.Value);
								/*if (ImGui::TreeNodeEx("Aimbot Aim Line",ImGuiTreeNodeFlags_DefaultOpen)) {
									ImGui::TreePop();
								}*/
							}
							ImGui::Checkbox("Smoothness", &Settings::Aimbot::bSmoothness);

							if (Settings::Aimbot::bSmoothness) {
								ImGui::SliderFloat("Smoothnes##slider", &Settings::Aimbot::Smoothness, 1.0f, 0.1f, "%.2f", ImGuiSliderFlags_NoInput);
								/*if (ImGui::TreeNodeEx("Aimbot Smoothness", ImGuiTreeNodeFlags_DefaultOpen)) {
									ImGui::TreePop();
								}*/
							}
						}
					}
					if (Settings::Silent::bSilent) {
						if (ImGui::CollapsingHeader("Silent", ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen)) {
							ImGui::Combo("Silent Hit Location", &Settings::Silent::SilentAimHitPosIndex, Settings::AimLocations, IM_ARRAYSIZE(Settings::AimLocations));
							Menu::Hotkey("Silent Aim Key", &Settings::Silent::SilentKey, ImVec2(50, 30));

							ImGui::Checkbox("Silent FOV", &Settings::Silent::bSilentFOV);
							if (Settings::Silent::bSilentFOV) {
								ImGui::SliderFloat("FOV##SilentFov", &Settings::Silent::SilentFov, 30.0f, 250.0f, "%.1f");
								ImGui::ColorEdit3("FOV Color##SilentFovColor", (float*)&Settings::Silent::SilentFovC.Value);
							}

							ImGui::Checkbox("AimLine##SilentAimLine", &Settings::Silent::bSilentAimLine);
							if (Settings::Silent::bSilentAimLine) {
								ImGui::ColorEdit3("AimLine Color##SilentAimLineColor", (float*)&Settings::Silent::SilentAimLineC.Value);
							}
						}
					}
					if (Settings::WallBang::bWallBang) {
						if (ImGui::CollapsingHeader("WallBang", ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen)) {
							ImGui::Combo("WallBang Hit Location", &Settings::WallBang::WallBangHitPosIndex, Settings::AimLocations, IM_ARRAYSIZE(Settings::AimLocations));
							Menu::Hotkey("WallBang Aim Key", &Settings::WallBang::WallBangKey, ImVec2(50, 30));

							ImGui::Checkbox("WallBang FOV", &Settings::WallBang::bWallBangFOV);
							if (Settings::WallBang::bWallBangFOV) {
								ImGui::SliderFloat("FOV##WallBangFov", &Settings::WallBang::WallBangFOV, 30.0f, 250.0f, "%.1f");
								ImGui::ColorEdit3("FOV Color##WallBangFovColor", (float*)&Settings::WallBang::WallBangFOVC.Value);
							}

							ImGui::Checkbox("AimLine##WallBangAimLine", &Settings::WallBang::bWallBangAimLine);
							if (Settings::WallBang::bWallBangAimLine) {
								ImGui::ColorEdit3("AimLine Color##WallBangAimLineColor", (float*)&Settings::WallBang::WallBangAimLineC.Value);

							}
						}
					}
					ImGui::EndChild();
				}
				ImGui::EndTabItem();
			}

			//Misc Tab
			if (ImGui::BeginTabItem("Misc"))
			{

				if (ImGui::BeginChild("##MiscSideNav", ImVec2(150, 300), true)) {
					//TESTING
					if (ImGui::Checkbox("Hook Trace Shoot", &bTrace)) { //LOOk
						if (!bTrace) {
							if (MH_CreateHook((LPVOID)Hooks::TraceShootWrapperTar, (LPVOID)Hooks::TraceShootWrapperH, (LPVOID*)&Hooks::TraceShootWrapperO) != MH_OK) {
								std::cout << "[Failed] Hooking WhoIsShooting!\n";
								Menu::CleanAndExit();
							}
							if (MH_EnableHook((LPVOID)Hooks::TraceShootWrapperTar) != MH_OK) { // Enables The Hook
								std::cerr << "[Error] Failed to enable WhoIsShooting Hooks!\n";
								Menu::CleanAndExit();
							}
							bTrace = true;
						}
					}

					if (ImGui::Checkbox("Disable Effects (Fast Mode)", &Settings::PlayerCheats::ParticlesState))
						PlayerCheats::DisableParticles();
					ImGui::Checkbox("FOV", &Settings::PlayerCheats::FovChanger);
					ImGui::Checkbox("GameInfo", &Settings::PlayerCheats::GameInfo);

					ImGui::EndChild();
				}
				if (ImGui::BeginChild("##MainMiscContent", ImVec2(300, 300), true)) {
					if(Settings::PlayerCheats::FovChanger)
						ImGui::SliderFloat("FOV", FOV, 80.0f, 155.0f, "%.1f", ImGuiSliderFlags_NoInput);
					ImGui::EndChild();
				}

				ImGui::EndTabItem();
			}


			//// WallBang Tab
			//if (ImGui::BeginTabItem("WallBang")) {
			//	ImGui::Combo("Aim Type", &Settings::AimFeaturesIndex, Settings::AimFeatures, IM_ARRAYSIZE(Settings::AimFeatures));
			//	//SilentAim
			//	if (Settings::AimFeaturesIndex == 0) {
			//		//if (Settings::Silent::bSilent) 
			//		Settings::Silent::bSilent = true;
			//		if (Settings::Aimbot::AimbotKey == Settings::Silent::SilentKey) {
			//			Settings::Aimbot::bAimbot = false;
			//		}
			//		ImGui::Combo("Silent Aim Location", &Settings::Silent::SilentAimHitPosIndex, Settings::AimLocations, IM_ARRAYSIZE(Settings::AimLocations));

			//		Menu::Hotkey("Silent Aim Key", &Settings::Silent::SilentKey, ImVec2(50, 30));

			//		ImGui::SliderFloat("FOV##slider1", &Settings::Silent::SilentFov, 30.0f, 250.0f, "%.1f");
			//		ImGui::ColorEdit3("FOV Color##Color", (float*)&Settings::Silent::SilentFovC.Value);

			//		ImGui::Checkbox("AimLine##checkbox", &Settings::Silent::bSilentAimLine);
			//		if (Settings::Silent::bSilentAimLine) {
			//			ImGui::ColorEdit3("AimLine Color##Color", (float*)&Settings::Silent::SilentAimLineC.Value);
			//		}
			//		//}
			//	}
			//	else
			//		Settings::Silent::bSilent = false;
			//	if (Settings::AimFeaturesIndex == 1) {
			//		//WallBang
			//		//if(Settings::WallBang::bWallBang){
			//		Settings::WallBang::bWallBang = true;
			//		if (Settings::Aimbot::AimbotKey == Settings::WallBang::WallBangKey) {
			//			Settings::Aimbot::bAimbot = false;
			//		}
			//		else if (Settings::Silent::SilentKey == Settings::WallBang::WallBangKey) {
			//			Settings::Silent::bSilent = false;
			//		}
			//		ImGui::Combo("Bang Location", &Settings::WallBang::WallBangHitPosIndex, Settings::AimLocations, IM_ARRAYSIZE(Settings::AimLocations));

			//		Menu::Hotkey("WallBang Key", &Settings::WallBang::WallBangKey, ImVec2(50, 30));

			//		ImGui::SliderFloat("FOV##slider", &Settings::WallBang::WallBangFOV, 30.0f, 250.0f, "%.1f");
			//		ImGui::ColorEdit3("FOV Color", (float*)&Settings::WallBang::WallBangFOVC.Value);

			//		ImGui::Checkbox("AimLine", &Settings::WallBang::bWallBangAimLine);
			//		if (Settings::WallBang::bWallBangAimLine) {
			//			ImGui::ColorEdit3("AimLine Color", (float*)&Settings::WallBang::WallBangAimLineC.Value);
			//		}
			//		//}
			//	}
			//	else
			//		Settings::WallBang::bWallBang = false;
			//	ImGui::EndTabItem();
			//}



			ImGui::EndTabBar();
		}


		if (*PRealLocalMode)
			ImGui::EndDisabled();
		ImGui::End();
	}
}


void Menu::ToggleMenu()
{
	ShowMenu = !ShowMenu;
}



//Main Loop
BOOL __stdcall Hooks::SwapBuffersH(HDC hdc) { // MAIN LOOP

	Menu::GameConext = wglGetCurrentContext();
	if (!Menu::ImguiDone) {
		Menu::Init();
	}

	if (!Menu::ContextDone)
		Menu::SetupContext(hdc);
	wglMakeCurrent(hdc, Menu::MenuContext);

	Menu::StartRender();

	// Aimbot
	if(Settings::Aimbot::bAimbot) {

		if (Settings::Aimbot::AimbotKey == 0) {
			if (Settings::Aimbot::bAimbotAimLine)
				Aimbot::AimLine(Aimbotted);
		}
		else if(!Constants::ChoosingAimbotKey){
			if (Settings::Aimbot::bAimbotAimLine)
				Aimbot::AimLine(Aimbotted);
		}
	}
	//WallBang
	if (Settings::WallBang::bWallBang) {
		if (Settings::WallBang::WallBangKey == 0) { // No Custom WallBang Key
			if (Settings::WallBang::bWallBangAimLine) {
				WallBang::AimLine(WallBanged);
			}
			//WallBang::ActivateWallBang();

		}
		else if (!Constants::ChoosingWallBangKey) { // Custom Key!
			if (Settings::WallBang::bWallBangAimLine) {
				WallBang::AimLine(WallBanged);
			}
			//WallBang::ActivateWallBang();
		}
	}

	//Silent Key Check
	if (Settings::Silent::bSilent) {
		if (Settings::Silent::SilentKey == 0) { // No Custom Silent Key
			if (Settings::Silent::bSilentAimLine) {
				Silent::AimLine(Silented);
			}

		}
		else if (!Constants::ChoosingSilentKey) { // Custom Key!
			if (Settings::Silent::bSilentAimLine) {
				Silent::AimLine(Silented);
			}
		}
	}

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	wglMakeCurrent(hdc, Menu::GameConext);
	return Hooks::SwapBuffersO(hdc);
}

//Mouse Movement In Menu
LRESULT __stdcall Hooks::WndProcH(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ImGuiIO& io = ImGui::GetIO();
	if (Menu::ShowMenu && Menu::ImguiDone) {
		RECT rect;
		GetWindowRect(hWnd, &rect);  // Get the window's dimensions
		Hooks::ClipCursorH(&rect); // Unlock Cursor.

		io.MouseDrawCursor = TRUE;

		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);//Works Like Butter!
		switch (uMsg) {
			case WM_CLOSE:
			case WM_QUIT:
			case WM_DESTROY:
			case WM_MOUSEMOVE:
			case WM_MOUSEACTIVATE:
			case WM_MOUSEHOVER:
			case WM_NCMOUSEMOVE:
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			case WM_LBUTTONDBLCLK:
			case WM_RBUTTONDBLCLK:
			case WM_MBUTTONDBLCLK:
			case WM_MOUSEWHEEL:
			case WM_MOUSEHWHEEL:
			case WM_NCLBUTTONDOWN:
			case WM_NCRBUTTONDOWN:
			case WM_NCMBUTTONDOWN:
			case WM_NCLBUTTONUP:
			case WM_NCRBUTTONUP:
			case WM_NCMBUTTONUP:
			case WM_NCLBUTTONDBLCLK:
			case WM_NCRBUTTONDBLCLK:
			case WM_NCMBUTTONDBLCLK:
			case WM_INPUT:
			case WM_TOUCH:
			case WM_POINTERDOWN:
			case WM_POINTERUP:
			case WM_POINTERUPDATE:
			case WM_NCMOUSELEAVE:
			case WM_MOUSELEAVE:
			case WM_NCHITTEST:
			case WM_SETCURSOR:
			case WM_ACTIVATE:
			case WM_SIZE:
			case WM_MOVE:
			case WM_PAINT:
			case WM_ENTERSIZEMOVE:
			case WM_EXITSIZEMOVE:
			case WM_GETMINMAXINFO:
			case WM_SETFOCUS:
			case WM_KILLFOCUS:
			case WM_ACTIVATEAPP:
			case WM_APPCOMMAND:
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_CHAR:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_SYSCHAR:
			case WM_DEADCHAR:
			case WM_SYSDEADCHAR:
				return true;  // Block these messages from reaching the game
			}
	}
	io.MouseDrawCursor = FALSE;
	return CallWindowProcW((WNDPROC)Hooks::WndProcOState, hWnd, uMsg, wParam, lParam);
}
BOOL __stdcall Hooks::ClipCursorH(const RECT* lpRect)// So we can move when the menu shown!
{
	if (Menu::ShowMenu && Menu::ImguiDone) {
		return Hooks::ClipCursorO(NULL);
	}
	return Hooks::ClipCursorO(lpRect);
}

//Clean & UnLoad Dll
void Menu::CleanAndExit() {
	// Cleanup ImGui
	if (ImGui::GetCurrentContext()) {
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	// Cleanup hooks
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	// Close the debug console
	fclose(stdout);
	fclose(stdin);
	fclose(stderr);
	FreeConsole();
	//if(Settings::Aimbot::bAimbotState)
	//	if(Aimbot::AimbotThread.joinable())
	//		Aimbot::AimbotThread.join();

	// Unload the DLL
	FreeLibraryAndExitThread(Constants::AimbotHandle, 0);
	FreeLibraryAndExitThread(Constants::DllHandle, 0);
}