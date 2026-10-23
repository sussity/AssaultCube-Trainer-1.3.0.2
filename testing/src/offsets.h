#pragma once
#include <cstdint>

// Offsets for AssaultCube 1.3.0.2 (ac_client.exe, 32-bit).
// If the game updates these will break - re-find them with Cheat Engine / ReClass.
//
// Coordinates: AssaultCube (Cube engine) uses Z as "up"; X/Y are the ground plane.

// Static addresses, relative to the ac_client.exe module base.
// Read them as `moduleBase + Pointers::X`. Pointers in the game are 4 bytes - use readPtr().
namespace Pointers {
    constexpr uintptr_t LocalPlayer = 0x18AC00;   // -> Player*. Tested. (0x17E0A8 is the camera: same as you while alive, a different object while dead)
    constexpr uintptr_t EntityList = 0x18AC04;    // -> Player*[PlayerCount], slot 0 is empty
    constexpr uintptr_t PlayerCount = 0x18AC0C;   // int, number of slots in EntityList
    constexpr uintptr_t ViewMatrix = 0x17DFD0;    // float[16], column-major; needed for world-to-screen ESP
    constexpr uintptr_t FOV = 0x18A7CC;           // float, the game's horizontal fov setting in degrees. Tested (120.0 = saved.cfg = view matrix).
}

// Offsets inside a player object.
// Read them as `playerAddress + offsets::X`.
namespace offsets {

    // Head position, float (use for aimbot)
    constexpr uintptr_t HeadX = 0x04;
    constexpr uintptr_t HeadY = 0x08;
    constexpr uintptr_t HeadZ = 0x0C;

    // Feet position, float
    constexpr uintptr_t PosX = 0x28;
    constexpr uintptr_t PosY = 0x2C;
    constexpr uintptr_t PosZ = 0x30;

    // Camera, float, degrees
    constexpr uintptr_t Yaw = 0x34;    // 0-360, horizontal
    constexpr uintptr_t Pitch = 0x38;  // -90 (down) to 90 (up)

    // Stats
    constexpr uintptr_t Health = 0xEC;  // int
    constexpr uintptr_t Armour = 0xF0;  // int
    constexpr uintptr_t Name = 0x205;   // char[16], null-terminated
    constexpr uintptr_t Team = 0x30C;   // int, 0 = CLA, 1 = RVSF

    // Reserve ammo (spare mags), int
    namespace Reserve {
        constexpr uintptr_t Pistol = 0x108;
        constexpr uintptr_t TMP = 0x10C;
        constexpr uintptr_t Shotgun = 0x110;
        constexpr uintptr_t SMG = 0x114;
        constexpr uintptr_t Sniper = 0x118;
        constexpr uintptr_t AR = 0x11C;
    }

    // Ammo in the current mag, int
    namespace Ammo {
        constexpr uintptr_t Pistol = 0x12C;
        constexpr uintptr_t TMP = 0x130;
        constexpr uintptr_t Shotgun = 0x134;
        constexpr uintptr_t SMG = 0x138;
        constexpr uintptr_t Sniper = 0x13C;
        constexpr uintptr_t AR = 0x140;
        constexpr uintptr_t Grenade = 0x144;
    }

    // Delay between shots in ms, int. Set to 0 for fast fire (used by Rapid fire).
    // Less certain than the offsets above - if Rapid fire does nothing, re-check these.
    namespace FastFire {
        constexpr uintptr_t Pistol = 0x150;
        constexpr uintptr_t TMP = 0x154;
        constexpr uintptr_t Shotgun = 0x158;
        constexpr uintptr_t SMG = 0x15C;
        constexpr uintptr_t Sniper = 0x160;
        constexpr uintptr_t AR = 0x164;
    }

    // Misc
    constexpr uintptr_t Attacking = 0x204;  // bool (1 byte), 1 while the fire button is held. Writing 1 makes you shoot.
}
