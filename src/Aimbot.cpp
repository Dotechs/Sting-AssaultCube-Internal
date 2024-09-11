#include "Aimbot.h"
#include "Constants.h"
#include "GeneratedCode.h"
#include "Settings.h"
#include "Cheat.h"
#include "imgui.h"
//std::thread Aimbot::AimbotThread;
HMODULE Constants::AimbotHandle;
HMODULE Constants::AimLineHandle;

void Aimbot::ActivateAimbot() {
    if (Settings::Aimbot::bAimbotState) {
        if (Settings::Aimbot::AimbotTypeIndex == 0) {

            float closest_player = 1e30f;
            float closest_yaw = 0.0f;
            float closest_pitch = 0.0f;

            for (auto& enemy : EnemiesList) {



                float abspos_x = (enemy->HeadPos.x) - LocalPlayer->HeadPos.x;
                float abspos_y = (enemy->HeadPos.y) - LocalPlayer->HeadPos.y;
                float abspos_z = (enemy->HeadPos.z) - LocalPlayer->HeadPos.z;

                float temp_distance = sqrtf(abspos_x * abspos_x + abspos_y * abspos_y);

                if (temp_distance < closest_player) {
                    closest_player = temp_distance;


                    //Aimbot Logic
                    float abspos_x;
                    float abspos_y;
                    float abspos_z;

                    switch (Settings::Aimbot::AimbotHitPosIndex)
                    {
                    case 0:
                        abspos_x = (enemy->HeadPos.x) - LocalPlayer->HeadPos.x;
                        abspos_y = (enemy->HeadPos.y) - LocalPlayer->HeadPos.y;
                        abspos_z = (enemy->HeadPos.z) - LocalPlayer->HeadPos.z;
                        break;
                    case 1:
                        abspos_x = (enemy->HeadPos.x) - LocalPlayer->HeadPos.x;
                        abspos_y = (enemy->HeadPos.y) - LocalPlayer->HeadPos.y;
                        abspos_z = (enemy->HeadPos.z - 1.88f) - LocalPlayer->HeadPos.z;
                        break;
                    case 2:
                        abspos_x = (enemy->FeetPos.x) - LocalPlayer->HeadPos.x;
                        abspos_y = (enemy->FeetPos.y) - LocalPlayer->HeadPos.y;
                        abspos_z = (enemy->FeetPos.z + 0.5f) - LocalPlayer->HeadPos.z;
                        break;
                    default:
                        exit(-1);
                        break;
                    }

                    float azimuth_xy = atan2f(abspos_y, abspos_x);
                    closest_yaw = azimuth_xy * (180.0f / M_PI) + 90.0f;

                    float hypotenuse = sqrtf(abspos_x * abspos_x + abspos_y * abspos_y + abspos_z * abspos_z);
                    closest_pitch = asinf(abspos_z / hypotenuse) * (180.0f / M_PI) + 1.0f;
                    Aimbotted = enemy;
                }

            }

            // Check if a valid target was found
            if (Aimbotted && LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 &&
                LocalPlayer->Health > 0 && Aimbotted->PlayerMode == 0 && Aimbotted->Health > 0) {
                // Calculate yaw and pitch differences
                float yaw_diff = closest_yaw - LocalPlayer->ViewAngles.yaw;
                float pitch_diff = closest_pitch - LocalPlayer->ViewAngles.pitch;

                // Adjust yaw_diff to be within the range [-180, 180]
                if (yaw_diff > 180.0f) {
                    yaw_diff -= 360.0f;
                }
                else if (yaw_diff < -180.0f) {
                    yaw_diff += 360.0f;
                }

                // Adjust pitch_diff to be within the range [-180, 180]
                if (pitch_diff > 180.0f) {
                    pitch_diff -= 360.0f;
                }
                else if (pitch_diff < -180.0f) {
                    pitch_diff += 360.0f;
                }

                LocalPlayer->ViewAngles.yaw += yaw_diff * Settings::Aimbot::Smoothness;
                LocalPlayer->ViewAngles.pitch += pitch_diff * Settings::Aimbot::Smoothness;

            }
        }

        if (Settings::Aimbot::AimbotTypeIndex == 1) {
            float ClosestDistance = 1e15f;
            float HTempDistance = 0.0f;
            float FTempDistance = 0.0f;
            //Aimbotted = nullptr;

            float Yaw = 0, Pitch = 0, DYaw = 0.0f, DPitch = 0.0f;

            for (auto& enemy : EnemiesList) {
                vec3 HEnemyScreen = vec3(0, 0, 0);
                vec3 FEnemyScreen = vec3(0, 0, 0);
                if (!Cheat::WorldToScreenEx(std::move(enemy->HeadPos), HEnemyScreen, ViewMatrix, WindowX, WindowY) || !Cheat::WorldToScreenEx(std::move(enemy->FeetPos), FEnemyScreen, ViewMatrix, WindowX, WindowY))
                    continue;
                if (HEnemyScreen.z < 0 || FEnemyScreen.z < 0) //behind
                    continue;
                HTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(HEnemyScreen.x, HEnemyScreen.y)));
                FTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(FEnemyScreen.x, FEnemyScreen.y)));

                if (HTempDistance > Settings::Aimbot::AimbotFOV && FTempDistance > Settings::Aimbot::AimbotFOV) {
                    continue;
                }
                if (HTempDistance < ClosestDistance && FTempDistance < ClosestDistance) {

                    Aimbotted = enemy;
                    ClosestDistance = HTempDistance;

                    //Aimbot Logic
                    float abspos_x;
                    float abspos_y;
                    float abspos_z;

                    switch (Settings::Aimbot::AimbotHitPosIndex)
                    {
                    case 0:
                        abspos_x = (Aimbotted->HeadPos.x) - LocalPlayer->HeadPos.x;
                        abspos_y = (Aimbotted->HeadPos.y) - LocalPlayer->HeadPos.y;
                        abspos_z = (Aimbotted->HeadPos.z) - LocalPlayer->HeadPos.z;
                        break;
                    case 1:
                        abspos_x = (Aimbotted->HeadPos.x) - LocalPlayer->HeadPos.x;
                        abspos_y = (Aimbotted->HeadPos.y) - LocalPlayer->HeadPos.y;
                        abspos_z = (Aimbotted->HeadPos.z - 1.88f) - LocalPlayer->HeadPos.z;
                        break;
                    case 2:
                        abspos_x = (Aimbotted->FeetPos.x) - LocalPlayer->HeadPos.x;
                        abspos_y = (Aimbotted->FeetPos.y) - LocalPlayer->HeadPos.y;
                        abspos_z = (Aimbotted->FeetPos.z + 0.5f) - LocalPlayer->HeadPos.z;
                        break;
                    default:
                        exit(-1);
                        break;
                    }
                    // Calculate Yaw (horizontal angle)
                    float azimuth_xy = atan2f(abspos_y, abspos_x);
                    Yaw = azimuth_xy * (180.0f / M_PI) + 90.0f;

                    // Calculate Pitch (vertical angle)
                    float hypotenuse = sqrtf(abspos_x * abspos_x + abspos_y * abspos_y + abspos_z * abspos_z);
                    Pitch = asinf(abspos_z / hypotenuse) * (180.0f / M_PI);
                }

                if (Aimbotted && LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 &&
                    LocalPlayer->Health > 0 && Aimbotted->PlayerMode == 0 && Aimbotted->Health > 0) {


                    DYaw = Yaw - LocalPlayer->ViewAngles.yaw;
                    DPitch = Pitch - LocalPlayer->ViewAngles.pitch;

                    if (DYaw > 180.0f) {
                        DYaw -= 360.0f;
                    }
                    else if (DYaw < -180.0f) {
                        DYaw += 360.0f;
                    }
                    if (DPitch > 180.0f) {
                        DPitch -= 360.0f;
                    }
                    else if (DPitch < -180.0f) {
                        DPitch += 360.0f;
                    }

                    float LerpFactor = 1.0f / Settings::Aimbot::Smoothness;

                    LocalPlayer->ViewAngles.yaw += DYaw / LerpFactor;
                    LocalPlayer->ViewAngles.pitch += DPitch / LerpFactor;
                }
            }
        }
    }
}
void Aimbot::AimLine(PlayerEnt* aimedAt)
{
	if (!Settings::Aimbot::bAimbotState||!Settings::Aimbot::bAimbot && !Settings::Aimbot::bAimbotAimLine || !Aimbotted || Aimbotted->PlayerMode != 0 || Aimbotted->Health < 0)
		return;

	vec3 FeetPos = { Aimbotted->FeetPos.x, Aimbotted->FeetPos.y, Aimbotted->FeetPos.z };
	vec3 feetScreenPos = vec3(0, 0, 0);
	bool IsLoadedFeet = Cheat::WorldToScreenEx(std::move(Aimbotted->FeetPos), feetScreenPos, ViewMatrix, WindowX, WindowY);
    float FTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(feetScreenPos.x, feetScreenPos.y)));

    if (!IsLoadedFeet || FTempDistance > Settings::Aimbot::AimbotFOV && Settings::Aimbot::AimbotTypeIndex ==1) {
        return;
    }
	if (LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 && LocalPlayer->Health > 0 && aimedAt && aimedAt->Health > 0 && aimedAt->PlayerMode == 0)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(WindowX / 2, WindowY), ImVec2(feetScreenPos.x, feetScreenPos.y), Settings::Aimbot::AimbotAimLineC, 1.0f);
	//std::this_thread::sleep_for(std::chrono::milliseconds(5));
}



