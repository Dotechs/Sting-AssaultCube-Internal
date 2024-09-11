#include "Esp.h"
//#include "imgui.h"
#include "Settings.h"
#include "GeneratedCode.h"
#include "Cheat.h"
#include "Constants.h"

vec3 GernadeScreenPos;
vec3 GernadeOwnerScreenPos;
ImVec2 GernadePos;
ImVec2 GernadeOwnerPos;
float xVal = 0.0f;



void Esp::DrawScalingVerticalBar(float x, float y, float width, float height, size_t currentHealth, size_t maxHealth) {
	// Ensure the health value is clamped between 0 and maxHealth
	currentHealth = (currentHealth < 0) ? 0 : (currentHealth > maxHealth) ? maxHealth : currentHealth;

	// Calculate the height of the health portion
	float healthRatio = currentHealth / maxHealth;
	float healthHeight = height * healthRatio;
	float lostHeight = height - healthHeight;

	// Define the bounding box of the health bar
	float x1 = x;
	float y1 = y;
	float x2 = x + width;
	float y2 = y + height;


	// Draw border
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + width + 1, y + height + 1), White);

	// Draw background
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y + height - lostHeight), ImVec2(x + width, y + height), Red);

	// Draw health portion
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y + height - healthHeight), ImVec2(x + width, y + height), Green);
}

void Esp::DrawEsp() {

	if (Settings::Aimbot::bAimbot && Settings::Aimbot::bAimbotFOV && Settings::Aimbot::AimbotTypeIndex == 1) {
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(WindowX / 2, WindowY / 2), Settings::Aimbot::AimbotFOV, Settings::Aimbot::AimbotFOVC, 0.5f);
	}
	if (Settings::WallBang::bWallBang && Settings::WallBang::bWallBangFOV) {
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(WindowX / 2, WindowY / 2), Settings::WallBang::WallBangFOV, Settings::WallBang::WallBangFOVC, 0.5f);
	}
	if (Settings::Silent::bSilent && Settings::Silent::bSilentFOV) {
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(WindowX / 2, WindowY / 2), Settings::Silent::SilentFov, Settings::Silent::SilentFovC, 0.5f);
	}
	
	//Players Around you
	if (Settings::ESP::bShowPlayerCount){
		//Setting-Up The Menu Style
		ImGui::PushStyleColor(ImGuiCol_FrameBg, LightBlack4);
		ImGui::PushStyleColor(ImGuiCol_Border, Red4);

		//Size Management
		if(RealEnemyCount <= 9){
			ImGui::SetNextWindowPos(ImVec2(WindowX / 2 - 120/2, WindowY / 8));
			ImGui::SetNextWindowSize(ImVec2(125, 13));
		}
		else {
			ImGui::SetNextWindowPos(ImVec2(WindowX / 2 - 135/2, WindowY / 8));
			ImGui::SetNextWindowSize(ImVec2(132, 13));
		}

		// Create the box with text
		if (ImGui::Begin("Box", nullptr,
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoNav |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%d Players Around You!", RealEnemyCount);
			ImGui::End();
		}
		ImGui::PopStyleColor(2);
	}

	//Gernades
	if (Settings::ESP::bGernades) {
		if (Gernade) {
			if (Gernade->Rtti == 5592536) {

				GernadeScreenPos = vec3(0, 0, 0);
				GernadeOwnerScreenPos = vec3(0, 0, 0);

				bool IsGernadeLoaded = Cheat::WorldToScreenEx(std::move(Gernade->Pos), GernadeScreenPos, ViewMatrix, WindowX, WindowY);
				bool IsGernadeOwnerLoaded = Cheat::WorldToScreenEx(std::move(Gernade->GernadeOwner->HeadPos), GernadeOwnerScreenPos, ViewMatrix, WindowX, WindowY);
				
				GernadePos = ImVec2(GernadeScreenPos.x, GernadeScreenPos.y);
				GernadeOwnerPos = ImVec2(GernadeOwnerScreenPos.x + 5, GernadeOwnerScreenPos.y);
				//"Gernade" : ImVec2(50,13)

				if (Gernade->Pos.x == 0.0f && Gernade->Pos.y == 0.0f && Gernade->Pos.z == 0.0f && IsGernadeOwnerLoaded) {
					ImGui::GetBackgroundDrawList()->AddCircleFilled(GernadeOwnerPos, 14, Red);
				}
				else {
					ImGui::GetBackgroundDrawList()->AddCircleFilled(GernadePos, 14, Red);
				}
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(GernadePos.x - 50 / 2, GernadePos.y - 35), White, "GERNADE");

			}
		}

	}


	if (!Settings::ESP::bBoxes && !Settings::ESP::bBones && !Settings::ESP::bSnapLines && !Settings::ESP::bNames && !Settings::ESP::bDistance && !Settings::ESP::bGun && !Settings::ESP::bHealthBar)
		return;

	if (LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 && LocalPlayer->Health > 0) {

		for (auto& enemy : EnemiesList) {
			ImVec2 topLeft;
			ImVec2 topRight;
			ImVec2 bottomRight;
			ImVec2 bottomLeft;


			vec3 headScreenPos = vec3(0, 0, 0);
			vec3 feetScreenPos = vec3(0, 0, 0);

			bool IsLoadedHead = Cheat::WorldToScreenEx(std::move(enemy->HeadPos), headScreenPos, ViewMatrix, WindowX, WindowY);
			bool IsLoadedFeet = Cheat::WorldToScreenEx(std::move(enemy->FeetPos), feetScreenPos, ViewMatrix, WindowX, WindowY);
			if (Settings::ESP::bShowWhoIsAiming) {
				if (Cheat::IsEnemyAimingAtMe(enemy)) {
					Esp::DrawEnemyWarning(feetScreenPos);
				}
			}
			if (!IsLoadedHead || !IsLoadedFeet) {
				continue;
			}

			//Top, Down
			if (Settings::ESP::bBoxes || Settings::ESP::bHealthBar) {
				float height = headScreenPos.y - feetScreenPos.y;
				float width = height / 4;


				topLeft = ImVec2(headScreenPos.x - width, headScreenPos.y/* - 17.0f*/);
				topRight = ImVec2(headScreenPos.x + width, headScreenPos.y/* - 17.0f*/);
				bottomRight = ImVec2(feetScreenPos.x + width, feetScreenPos.y);
				bottomLeft = ImVec2(feetScreenPos.x - width, feetScreenPos.y);
			}

			//Box
			if (Settings::ESP::bBoxes) {

				ImGui::GetBackgroundDrawList()->AddQuad(bottomRight, bottomLeft, topLeft, topRight, Settings::ESP::BoxC, 1.0f);
			}

			//Health
			if (Settings::ESP::bHealthBar) {
				//DrawScalingVerticalBar(bottomLeft.x , bottomLeft.y, bottomLeft.x, topLeft.y, 0.7f, 100.0f, enemy->Health);
				DrawScalingVerticalBar(bottomLeft.x, bottomLeft.y, 2.0f, headScreenPos.y - feetScreenPos.y, enemy->Health, 100);
			}

			//Names
			if (Settings::ESP::bNames /*&& !IsTeammate*/) {
				float textWidth = ImGui::CalcTextSize(enemy->Name).x;
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(headScreenPos.x - textWidth / 2, headScreenPos.y - 42), Orange, enemy->Name);//Orange
			}

			//Gun
			if (Settings::ESP::bGun) {
				float textWidth = ImGui::CalcTextSize(enemy->GunEnt->GeneralData->GunName).x;
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(headScreenPos.x - textWidth / 2, headScreenPos.y - 50), Cyan, enemy->GunEnt->GeneralData->GunName);// Cyan
			}

			//Bone
			if (Settings::ESP::bBones) {
				//TODO Teammate,Enemy
			}

			//Lines
			if (Settings::ESP::bSnapLines) {
				switch (Settings::ESP::EspLineIndex)
				{
				case 0: // Top
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(WindowX / 2, 0), ImVec2(headScreenPos.x, headScreenPos.y), Settings::ESP::SnapLinesC, 1.0f);
					break;
				case 1: // Middle
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(WindowX / 2, WindowY / 2), ImVec2(headScreenPos.x, headScreenPos.y), Settings::ESP::SnapLinesC, 1.0f);
					break;
				case 2:// Bottom
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(WindowX / 2, WindowY), ImVec2(feetScreenPos.x, feetScreenPos.y), Settings::ESP::SnapLinesC, 1.0f);
					break;
				default:
					break;
				}
			}

			//Distance
			if (Settings::ESP::bDistance) {
				char distStr[32];
				snprintf(distStr, sizeof(distStr), "%.0fm", Cheat::Dist(enemy));
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(feetScreenPos.x - ImGui::CalcTextSize(distStr).x / 2, feetScreenPos.y), Purple, distStr);

			}



		}

	}
}


void Esp::DrawEnemyWarning(vec3& feetScreenPos) {
	// Define the colors of the rainbow using ImGui's colors
	std::vector<ImVec4> rainbowColors = {
	 ImVec4(1.00f, 0.00f, 0.00f, 1.00f), // Red
	 ImVec4(1.00f, 0.65f, 0.00f, 1.00f), // Orange
	 ImVec4(1.00f, 1.00f, 0.00f, 1.00f), // Yellow
	 ImVec4(0.00f, 1.00f, 0.00f, 1.00f), // Green
	 ImVec4(0.00f, 0.00f, 1.00f, 1.00f), // Blue
	 ImVec4(0.29f, 0.00f, 0.51f, 1.00f), // Indigo
	 ImVec4(0.93f, 0.51f, 0.93f, 1.00f)  // Violet
	};

	int colorIndex = 0;
	for (size_t i = 0; i < 7; ++i) {
		// Set the color for the current character
		ImU32 color = ImGui::GetColorU32(rainbowColors[colorIndex]);

		// Calculate position for the current character
		//ImVec2 pos = ImVec2(Pos.x + (i * fontSize * 0.5f), Pos.y);
		ImFont* Font = ImGui::GetFont();

		float textWidth = ImGui::CalcTextSize("ENEMY IS AIMING AT YOU!!").x;
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(feetScreenPos.x - ImGui::CalcTextSize("Aiming!").x / 2, feetScreenPos.y+15), Purple, "Aiming!");
		ImGui::GetBackgroundDrawList()->AddText(Font, 37, ImVec2(WindowX /2 - textWidth/* / 2 */ , WindowY / 10), color, "ENEMY IS AIMING AT YOU!!");// Cyan

		//ImGui::GetBackgroundDrawList()->AddText(Pos, color,"ENEMY IS AIMING AT YOU!!");
		//ImGui::GetBackgroundDrawList()->AddText(font, fontSize, pos, color, &text[i], &text[i] + 1);

		// Move to the next color in the rainbow
		colorIndex = (colorIndex + 1) % 7;
	}
}
