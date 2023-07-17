#pragma once
#include "SKSE/Impl/Stubs.h"
#include "higgsinterface001.h"
#include "nativePapyrus.h"

namespace VRExample {
    extern RE::PlayerCharacter* g_player;
    extern SKSE::detail::SKSETaskInterface* g_task;

    /// Main plugin entry point/ initialization function
    void StartMod();
    /// kPostLoadGame do stuff once player has loaded
    void GameLoad();

    /// HIGGS StartTwoHandingCallback
    void onWeaponGrab();
}  // namespace VRExample