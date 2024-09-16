#include "Silent.h"
#include "Settings.h"
#include "GeneratedCode.h"
#include "Cheat.h"
#include "Memory.h"
#include "Constants.h"

void Silent::ActivateSilent()
{
    if (Settings::Silent::bSilentState) {

        float ClosestDistance = 1e15f;
        float HTempDistance = 0.0f;
        float FTempDistance = 0.0f;

        float Yaw, Pitch, DYaw = 0.0f, DPitch = 0.0f;

        for (auto& enemy : EnemiesList) {
            vec2 HEnemyScreen = vec2(0, 0);
            vec2 FEnemyScreen = vec2(0, 0);

            switch (Settings::Silent::SilentAimHitPosIndex)
            {
            case 0:
                if (!Cheat::WorldToScreenEx(std::move(Vector3(enemy->HeadPos.x, enemy->HeadPos.y, enemy->HeadPos.z - 0.35f)), HEnemyScreen, ViewMatrix, WindowX, WindowY) || !Cheat::WorldToScreenEx(std::move(enemy->FeetPos), FEnemyScreen, ViewMatrix, WindowX, WindowY)) {
                    continue;
                }
                break;
            case 1:
                if (!Cheat::WorldToScreenEx(std::move(Vector3(enemy->HeadPos.x, enemy->HeadPos.y, enemy->HeadPos.z - 1.88f)), HEnemyScreen, ViewMatrix, WindowX, WindowY) || !Cheat::WorldToScreenEx(std::move(enemy->FeetPos), FEnemyScreen, ViewMatrix, WindowX, WindowY)) {
                    continue;
                }
                break;
            case 2:
                if (!Cheat::WorldToScreenEx(std::move(Vector3(enemy->FeetPos.x, enemy->FeetPos.y, enemy->FeetPos.z + 0.5f)), HEnemyScreen, ViewMatrix, WindowX, WindowY) || !Cheat::WorldToScreenEx(std::move(enemy->FeetPos), FEnemyScreen, ViewMatrix, WindowX, WindowY)) {
                    continue;
                }
                break;
            default:
                exit(-1);
                break;
            }

            HTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(HEnemyScreen.x, HEnemyScreen.y)));
            FTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(FEnemyScreen.x, FEnemyScreen.y)));

            if (HTempDistance > Settings::Silent::SilentFov &&/*||*/  FTempDistance > Settings::Silent::SilentFov) {

                continue;
            }

            if (HTempDistance < ClosestDistance && FTempDistance < ClosestDistance) {

                Silented = enemy;
                ClosestDistance = HTempDistance;
            }


            if (Silented && LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 &&
                LocalPlayer->Health > 0 && Silented->PlayerMode == 0 && Silented->Health > 0) {

                //Patch All Cross Writers
                if (Constants::SilentNoppingRight) {
                    Memory::Nop((BYTE*)(Constants::AcModuleBase + 0x56c18), 8u);
                    Memory::Nop((BYTE*)(Constants::AcModuleBase + 0x56c4e), 8u);
                    Memory::Nop((BYTE*)(Constants::AcModuleBase + 0x56c56), 8u);
                    Memory::Nop((BYTE*)(Constants::AcModuleBase + 0xcd506), 4u);
                    Constants::SilentNopped = true;
                    Constants::SilentNoppingRight = false;
                }
                if (Constants::SilentNopped) {
                    float closest_yaw = 0.0f, closest_pitch = 0.0f;
                    switch (Settings::Silent::SilentAimHitPosIndex) {
                    case 0:
                        //Aimbot Logic
                        float abspos_x;
                        float abspos_y;
                        float abspos_z;

                        abspos_x = (enemy->HeadPos.x) - LocalPlayer->HeadPos.x;
                        abspos_y = (enemy->HeadPos.y) - LocalPlayer->HeadPos.y;
                        abspos_z = (enemy->HeadPos.z) - LocalPlayer->HeadPos.z;


                        float azimuth_xy = atan2f(abspos_y, abspos_x);
                        closest_yaw = azimuth_xy * (180.0f / M_PI) + 90.0f;

                        float hypotenuse = sqrtf(abspos_x * abspos_x + abspos_y * abspos_y + abspos_z * abspos_z);
                        closest_pitch = asinf(abspos_z / hypotenuse) * (180.0f / M_PI) + 1.0f;

                        vec3  myvec = Cheat::AngleToDirection(closest_pitch, closest_yaw);
                        *CursorPos = myvec;

                    }

                }



            }
        }
    }
    else {
        if (Constants::SilentNopped && !Constants::SilentNoppingRight) {
            Memory::Patch((BYTE*)(Constants::AcModuleBase + 0x56c18), (BYTE*)"\xF3\x0F\x11\x05\x64\x20\x59\x00", 8u);
            Memory::Patch((BYTE*)(Constants::AcModuleBase + 0x56c4e), (BYTE*)"\xF3\x0F\x11\x0D\x68\x20\x59\x00", 8u);
            Memory::Patch((BYTE*)(Constants::AcModuleBase + 0x56c56), (BYTE*)"\xF3\x0F\x11\x2D\x6C\x20\x59\x00", 8u);
            Memory::Patch((BYTE*)(Constants::AcModuleBase + 0xcd506), (BYTE*)"\x66\x0F\xD6\x06", 4u);
            Constants::SilentNopped = false;
        }
    }
}
