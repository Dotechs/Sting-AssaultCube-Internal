#include "WallBang.h"
#include "Settings.h"
#include "GeneratedCode.h"
#include "Cheat.h"
#include "Memory.h"
#include "Constants.h"


void WallBang::ActivateWallBang() {

    if (Settings::WallBang::bWallBangState) {
        float ClosestDistance = 1e15f;
        float HTempDistance = 0.0f;
        float FTempDistance = 0.0f;

        for (auto& enemy : EnemiesList) {
            vec3 HEnemyScreen = vec3(0, 0, 0);
            vec3 FEnemyScreen = vec3(0, 0, 0);

            switch (Settings::WallBang::WallBangHitPosIndex)
            {
            case 0:
                if (!Cheat::WorldToScreenEx((Vector3(enemy->HeadPos.x, enemy->HeadPos.y, enemy->HeadPos.z - 0.35f)), HEnemyScreen, ViewMatrix, WindowX, WindowY)) {
                    continue;
                }
                break;
            case 1:
                if (!Cheat::WorldToScreenEx((Vector3(enemy->HeadPos.x, enemy->HeadPos.y, enemy->HeadPos.z - 1.88f)), HEnemyScreen, ViewMatrix, WindowX, WindowY)) {
                    continue;
                }
                break;
            case 2:
                if (!Cheat::WorldToScreenEx((Vector3(enemy->FeetPos.x, enemy->FeetPos.y, enemy->FeetPos.z + 0.5f)), HEnemyScreen, ViewMatrix, WindowX, WindowY)) {
                    continue;
                }
                break;
            default:
                exit(-1);
                break;
            }

            if (HEnemyScreen.z < 0 /*|| FEnemyScreen.z < 0*/)//behind
                continue;

            HTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(HEnemyScreen.x, HEnemyScreen.y)));
            FTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(FEnemyScreen.x, FEnemyScreen.y)));///

            if (Settings::WallBang::bWallBangFOV) {
                if (HTempDistance > Settings::WallBang::WallBangFOV && FTempDistance > Settings::WallBang::WallBangFOV) {
                    Constants::WallBangNoppingRight = false;
                    continue;
                }
            }

            if (HTempDistance < ClosestDistance || FTempDistance < ClosestDistance) {
                WallBanged = enemy;
                ClosestDistance = HTempDistance;
            }


            if (WallBanged && LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 &&
                LocalPlayer->Health > 0 && WallBanged->PlayerMode == 0 && WallBanged->Health > 0) {

                //Patch All Cross Writers
                if (Constants::WallBangNoppingRight && !Constants::WallBangNopped) {
                    Memory::Nop((BYTE*)(Constants::AcModuleBase + 0x56c18), 8u);
                    Memory::Nop((BYTE*)(Constants::AcModuleBase + 0x56c4e), 8u);
                    Memory::Nop((BYTE*)(Constants::AcModuleBase + 0x56c56), 8u);
                    Memory::Nop((BYTE*)(Constants::AcModuleBase + 0xcd506), 4u);
                    printf("Nopped\n");
                    Constants::WallBangNopped = true;
                    //Constants::WallBangNoppingRight = false;
                    //Settings::WallBang::bWallBangState = false;
                }
                if (Constants::WallBangNopped) {
                    switch (Settings::WallBang::WallBangHitPosIndex) {
                    case 0:
                        *CursorPos = Vector3(WallBanged->HeadPos.x, WallBanged->HeadPos.y, WallBanged->HeadPos.z - 0.35f);
                        break;
                    case 1:
                        *CursorPos = Vector3(WallBanged->HeadPos.x, WallBanged->HeadPos.y, WallBanged->HeadPos.z - 1.88f);
                        break;
                    case 2:
                        *CursorPos = Vector3(WallBanged->FeetPos.x, WallBanged->FeetPos.y, WallBanged->FeetPos.z + 0.5f);
                        break;
                    }
                }
            }
        }
    }
    else if (Constants::WallBangNopped && !Constants::WallBangNoppingRight) {
        printf("Patched\n");
        Memory::Patch((BYTE*)(Constants::AcModuleBase + 0x56c18), (BYTE*)"\xF3\x0F\x11\x05\x64\x20\x59\x00", 8u);
        Memory::Patch((BYTE*)(Constants::AcModuleBase + 0x56c4e), (BYTE*)"\xF3\x0F\x11\x0D\x68\x20\x59\x00", 8u);
        Memory::Patch((BYTE*)(Constants::AcModuleBase + 0x56c56), (BYTE*)"\xF3\x0F\x11\x2D\x6C\x20\x59\x00", 8u);
        Memory::Patch((BYTE*)(Constants::AcModuleBase + 0xcd506), (BYTE*)"\x66\x0F\xD6\x06", 4u);
        Constants::WallBangNopped = false;
    }
}
void WallBang::AimLine(PlayerEnt* aimedAt)
{
    if (!Settings::WallBang::bWallBangState || !Settings::WallBang::bWallBang || !Settings::WallBang::bWallBangAimLine || !WallBanged || WallBanged->PlayerMode != 0 || WallBanged->Health < 0)
        return;

    vec3 feetScreenPos = vec3(0, 0, 0);
    bool IsLoadedFeet = Cheat::WorldToScreenEx(std::move(WallBanged->FeetPos), feetScreenPos, ViewMatrix, WindowX, WindowY);
    float FTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(feetScreenPos.x, feetScreenPos.y)));

    if (!IsLoadedFeet || FTempDistance > Settings::WallBang::WallBangFOV) {
        return;
    }
    if (LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 && LocalPlayer->Health > 0 && aimedAt && aimedAt->Health > 0 && aimedAt->PlayerMode == 0)
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(WindowX / 2, WindowY), ImVec2(feetScreenPos.x, feetScreenPos.y), Settings::WallBang::WallBangAimLineC, 0.60f);
}