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

            float ClosestDistance = 1e5f;
            float Yaw = 0.0f, Pitch = 0.0f;
            PlayerEnt* LocalAimbotted = nullptr;

            for (auto& enemy : EnemiesList) {

                float AbsPosX = (enemy->HeadPos.x) - LocalPlayer->HeadPos.x;
                float AbsPosY = (enemy->HeadPos.y) - LocalPlayer->HeadPos.y;

                float temp_distance = sqrtf(AbsPosX * AbsPosX + AbsPosY * AbsPosY);

                if (temp_distance < ClosestDistance) {
                    ClosestDistance = temp_distance;
                    LocalAimbotted = enemy;


                    //Aimbot Logic
                    float AbsPosX;
                    float AbsPosY;
                    float AbsPosZ;

                    switch (Settings::Aimbot::AimbotHitPosIndex)
                    {
                    case 0:
                        AbsPosX = (LocalAimbotted->HeadPos.x) - LocalPlayer->HeadPos.x;
                        AbsPosY = (LocalAimbotted->HeadPos.y) - LocalPlayer->HeadPos.y;
                        AbsPosZ = (LocalAimbotted->HeadPos.z) - LocalPlayer->HeadPos.z;
                        break;
                    case 1:
                        AbsPosX = (LocalAimbotted->HeadPos.x) - LocalPlayer->HeadPos.x;
                        AbsPosY = (LocalAimbotted->HeadPos.y) - LocalPlayer->HeadPos.y;
                        AbsPosZ = (LocalAimbotted->HeadPos.z - 1.88f) - LocalPlayer->HeadPos.z;
                        break;
                    case 2:
                        AbsPosX = (LocalAimbotted->FeetPos.x) - LocalPlayer->HeadPos.x;
                        AbsPosY = (LocalAimbotted->FeetPos.y) - LocalPlayer->HeadPos.y;
                        AbsPosZ = (LocalAimbotted->FeetPos.z + 0.5f) - LocalPlayer->HeadPos.z;
                        break;
                    default:
                        exit(-1);
                        break;
                    }
                    Angle angletoenemy = Cheat::AngleToEnemy(LocalAimbotted, vec3(AbsPosX, AbsPosY, AbsPosZ));
                    Yaw = angletoenemy.yaw; Pitch = angletoenemy.pitch;


                    //float azimuth_xy = atan2f(AbsPosY, AbsPosX);
                    //Yaw = azimuth_xy * (180.0f / M_PI) + 90.0f;
                    //float hypotenuse = sqrtf(AbsPosX * AbsPosX + AbsPosY * AbsPosY + AbsPosZ * AbsPosZ);
                    //Pitch = asinf(AbsPosZ / hypotenuse) * (180.0f / M_PI) + 1.0f;
                }
            }
            Aimbotted = LocalAimbotted;
                    
            if (LocalAimbotted && LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 &&
                LocalPlayer->Health > 0 && LocalAimbotted->PlayerMode == 0 && LocalAimbotted->Health > 0) {

                float DYaw = Yaw - LocalPlayer->ViewAngles.yaw;
                float DPitch = Pitch - LocalPlayer->ViewAngles.pitch;

                // Normalizing The Angle!
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

        if (Settings::Aimbot::AimbotTypeIndex == 1) {

            float ClosestDistance = 1e5f;
            float Yaw = 0, Pitch = 0;
            PlayerEnt* LocalAimbotted = nullptr;
            
            for (auto& enemy : EnemiesList) {
                vec2 HEnemyScreen = vec2(0, 0);
                vec2 FEnemyScreen = vec2(0, 0);
                vec2 TempDistances = vec2(0, 0); // x = HeadTemp , y = FeetTemp

                if (!Cheat::IsEnemyLoadedR(enemy, HEnemyScreen, FEnemyScreen, HEAD_AND_FEET))
                    continue;
                if (!Cheat::IsEnemyInFOV(enemy, &Settings::Aimbot::AimbotFOV, HEnemyScreen, FEnemyScreen, TempDistances, ANY))
                    continue;
                //if (!Cheat::WorldToScreenEx(enemy->HeadPos, HEnemyScreen, ViewMatrix, WindowX, WindowY) || !Cheat::WorldToScreenEx(enemy->FeetPos, FEnemyScreen, ViewMatrix, WindowX, WindowY))
                //    continue;
                //if (HEnemyScreen.z < 0 || FEnemyScreen.z < 0) //behind
                //    continue;
                // 
                //HTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(HEnemyScreen.x, HEnemyScreen.y)));
                //FTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(FEnemyScreen.x, FEnemyScreen.y)));
                //if (HTempDistance > Settings::Aimbot::AimbotFOV && FTempDistance > Settings::Aimbot::AimbotFOV) {
                //    continue;
                //}
                if (TempDistances.x < ClosestDistance || TempDistances.y < ClosestDistance) {
                    //Closer than the last loop ent enemy!
                    LocalAimbotted = enemy;
                    ClosestDistance = TempDistances.y;

                    float AbsPosX;
                    float AbsPosY;
                    float AbsPosZ;

                    //Switching User HitPos Choise!
                    switch (Settings::Aimbot::AimbotHitPosIndex)
                    {
                    case 0:
                        AbsPosX = (LocalAimbotted->HeadPos.x) - LocalPlayer->HeadPos.x;
                        AbsPosY = (LocalAimbotted->HeadPos.y) - LocalPlayer->HeadPos.y;
                        AbsPosZ = (LocalAimbotted->HeadPos.z) - LocalPlayer->HeadPos.z;
                        break;
                    case 1:
                        AbsPosX = (LocalAimbotted->HeadPos.x) - LocalPlayer->HeadPos.x;
                        AbsPosY = (LocalAimbotted->HeadPos.y) - LocalPlayer->HeadPos.y;
                        AbsPosZ = (LocalAimbotted->HeadPos.z - 1.88f) - LocalPlayer->HeadPos.z;
                        break;
                    case 2:
                        AbsPosX = (LocalAimbotted->FeetPos.x) - LocalPlayer->HeadPos.x;
                        AbsPosY = (LocalAimbotted->FeetPos.y) - LocalPlayer->HeadPos.y;
                        AbsPosZ = (LocalAimbotted->FeetPos.z + 0.5f) - LocalPlayer->HeadPos.z;
                        break;
                    default:
                        exit(-1);
                        break;
                    }

                    //Getting Angle To Enemy!
                    Angle angletoenemy = Cheat::AngleToEnemy(LocalAimbotted, vec3(AbsPosX, AbsPosY, AbsPosZ));
                    Yaw = angletoenemy.yaw; Pitch = angletoenemy.pitch;
                }
               
            }
            Aimbotted = LocalAimbotted;
            if (LocalAimbotted && LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 &&
                LocalPlayer->Health > 0 && LocalAimbotted->PlayerMode == 0 && LocalAimbotted->Health > 0) {


                float DYaw = Yaw - LocalPlayer->ViewAngles.yaw;
                float DPitch = Pitch - LocalPlayer->ViewAngles.pitch;

                // Normalizing The Angle!
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
