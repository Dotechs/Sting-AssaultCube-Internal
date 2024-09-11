#include "pch.h"
#include "GeneratedCode.h"
#include "Constants.h"

bool IsFirstTime = true;
bool CoolDown = false;
bool BeingAttacked;
const char* AttackerName = "";

bool bTrace;

PlayerEnt* LocalPlayer = nullptr;

int32_t CurPlayers;
int32_t* EntList= nullptr;
uintptr_t RealEnemyCount = 0;
std::vector<PlayerEnt*> EnemiesList;
int8_t IsSpectating;
int8_t* PRealLocalMode;
int32_t* PRealHealth;

Vector3* CursorPos;


uintptr_t* TimeRemaining;
GernadeEnt* Gernade;
DWORD** GernadeAddr;
uintptr_t MaxEnemies;
uintptr_t MapName;


DWORD* PlayerEntAddress = nullptr;

float* FOV = (float*)(Constants::AcModuleBase + 0x18A7CC);
float* Speed = (float*)(0x55BAD0);
uintptr_t AmmoLoc = (Constants::AcModuleBase + 0xC73EF);
uintptr_t GravityLoc = (Constants::AcModuleBase + 0xC2375);
uintptr_t RapidLoc = (Constants::AcModuleBase + 0xCB795);
uintptr_t SmallSpreadLoc = (Constants::AcModuleBase + 0xC730E);
uintptr_t SmallSpread2Loc = (Constants::AcModuleBase + 0xC7376); //Random Bullet
uintptr_t SpreadLoc = (Constants::AcModuleBase + 0xC2EC3);
uintptr_t RXveloLoc = (Constants::AcModuleBase + 0xC8DD2);
uintptr_t RYveloLoc = (Constants::AcModuleBase + 0xC8DFB);
uintptr_t RJumpVeloLoc = (Constants::AcModuleBase + 0xC8E00);
uintptr_t RectanglesLoc = (Constants::AcModuleBase + 0x7D188);
uintptr_t ParticlesLoc = (Constants::AcModuleBase + 0x692A2);
int WindowX = *(uintptr_t*)0x591ED8;
uintptr_t WindowY = *(uintptr_t*)0x57DFB0;
float* ViewMatrix = (float*)0x57DFD0;


PlayerEnt* Aimbotted = nullptr;
PlayerEnt* WallBanged = nullptr;
PlayerEnt* Silented = nullptr;


void GeneratedCode::EnemyVecUpdate() {
    if (MaxEnemies > 0) {
        for (size_t i = 0; i <= MaxEnemies; i++) {
            DWORD* enemy_offset = (DWORD*)(*EntList + (i * sizeof(DWORD)));
            PlayerEnt* enemy = (PlayerEnt*)(*enemy_offset);

            if (enemy && enemy->PlayerMode == 0 && enemy->Health > 0 && enemy->TeamID != LocalPlayer->TeamID) {
                // Check if the enemy is already in the list
                auto it = std::find(EnemiesList.begin(), EnemiesList.end(), enemy);
                if (it == EnemiesList.end()) {
                    // If the enemy is not in the list, add it
                    EnemiesList.push_back(enemy);
                }
            }
        }

        // Iterate through the list in reverse to safely remove invalid entities
        for (auto it = EnemiesList.begin(); it != EnemiesList.end(); ) {
            PlayerEnt* enemy = *it;

            if (!enemy || enemy->PlayerMode != 0 || enemy->Health <= 0 || enemy->TeamID == LocalPlayer->TeamID) {
                // If the entity is invalid, remove it from the list
                it = EnemiesList.erase(it);
            }
            else {
                ++it; // Move to the next entity
            }
        }
    }

    // Update the count of valid enemies
    RealEnemyCount = EnemiesList.size();
}
