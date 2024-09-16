#include "WallBang.h"
#include "Settings.h"
#include "GeneratedCode.h"
#include "Cheat.h"
#include "Memory.h"
#include "Constants.h"


void WallBang::ActivateWallBang() {
    if (Settings::WallBang::bWallBangState) {
        float ClosestDistance = 1e15f;
        PlayerEnt* LocalWallBanged = nullptr;

        for (auto& enemy : EnemiesList) {
            vec2 HEnemyScreen = vec2(0, 0);
            vec2 FEnemyScreen = vec2(0, 0);
            vec2 TempDistances = vec2(0, 0); // x = HeadTemp , y = FeetTemp


            if (!Cheat::IsEnemyLoadedR(enemy, HEnemyScreen, FEnemyScreen, HEAD_AND_FEET))
                continue;

            if (Settings::WallBang::bWallBangFOV) {
                if (!Cheat::IsEnemyInFOV(enemy, &Settings::WallBang::WallBangFOV, HEnemyScreen, FEnemyScreen, TempDistances, ANY))
                    continue;
            }
            else {
                TempDistances.x = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(HEnemyScreen.x, HEnemyScreen.y)));
                TempDistances.y = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(FEnemyScreen.x, FEnemyScreen.y)));
            }

            if (TempDistances.x < ClosestDistance || TempDistances.y < ClosestDistance) {
                LocalWallBanged = enemy;
                ClosestDistance = TempDistances.x;
            }
            //HTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(HEnemyScreen.x, HEnemyScreen.y)));
            //FTempDistance = abs(Cheat::Distance2D(vec2(WindowX / 2, WindowY / 2), vec2(FEnemyScreen.x, FEnemyScreen.y)));///
            //if (Settings::WallBang::bWallBangFOV) {
            //    if (HTempDistance > Settings::WallBang::WallBangFOV && FTempDistance > Settings::WallBang::WallBangFOV) {
            //        continue;
            //    }
            //}
            //if (HTempDistance < ClosestDistance || FTempDistance < ClosestDistance) {
            //    LocalWallBanged = enemy;
            //    ClosestDistance = HTempDistance;
            //}
        }
        WallBanged = LocalWallBanged;
        if (LocalWallBanged && LocalPlayer->PlayerMode == 0 && *PRealLocalMode == 0 &&
            LocalPlayer->Health > 0 && LocalWallBanged->PlayerMode == 0 && LocalWallBanged->Health > 0) {

            //Patch All Cross Writers
            if (Constants::WallBangNopped) {
                switch (Settings::WallBang::WallBangHitPosIndex) {
                case 0:
                    *CursorPos = Vector3(LocalWallBanged->HeadPos.x, LocalWallBanged->HeadPos.y, LocalWallBanged->HeadPos.z - 0.35f);
                    break;
                case 1:
                    *CursorPos = Vector3(LocalWallBanged->HeadPos.x, LocalWallBanged->HeadPos.y, LocalWallBanged->HeadPos.z - 1.88f);
                    break;
                case 2:
                    *CursorPos = Vector3(LocalWallBanged->FeetPos.x, LocalWallBanged->FeetPos.y, LocalWallBanged->FeetPos.z + 0.5f);
                    break;
                }
            }
            else{
                Memory::Nop((BYTE*)(Constants::AcModuleBase + 0x56c18), 8u);
                Memory::Nop((BYTE*)(Constants::AcModuleBase + 0x56c4e), 8u);
                Memory::Nop((BYTE*)(Constants::AcModuleBase + 0x56c56), 8u);
                Memory::Nop((BYTE*)(Constants::AcModuleBase + 0xcd506), 4u);
                Constants::WallBangNopped = true;

                //printf("Nopped\n");
            }
        }
        else {
            //WallBanged = nullptr;
            goto Patch;
        }
    }
    else {
        Patch:
        if (Constants::WallBangNopped) {
            Memory::Patch((BYTE*)(Constants::AcModuleBase + 0x56c18), (BYTE*)"\xF3\x0F\x11\x05\x64\x20\x59\x00", 8u);
            Memory::Patch((BYTE*)(Constants::AcModuleBase + 0x56c4e), (BYTE*)"\xF3\x0F\x11\x0D\x68\x20\x59\x00", 8u);
            Memory::Patch((BYTE*)(Constants::AcModuleBase + 0x56c56), (BYTE*)"\xF3\x0F\x11\x2D\x6C\x20\x59\x00", 8u);
            Memory::Patch((BYTE*)(Constants::AcModuleBase + 0xcd506), (BYTE*)"\x66\x0F\xD6\x06", 4u);
            Constants::WallBangNopped = false;
            
            //printf("Patched\n");
        }
    }
}

