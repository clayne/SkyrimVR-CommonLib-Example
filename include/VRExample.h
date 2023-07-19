#pragma once
#include "SKSE/Impl/Stubs.h"
#include "higgsinterface001.h"
#include "nativePapyrus.h"
#include "customEventSink.hpp"
#include "menu_checker.h"

namespace VRExample
{
    extern RE::PlayerCharacter *g_player;
    extern SKSE::detail::SKSETaskInterface *g_task;

    /// Main plugin entry point/ initialization function
    void StartMod();
    /// kPostLoadGame do stuff once player has loaded
    void GameLoad();

    // HIGGS example
    void onWeaponGrab();

    // Custom event handlers
    void onButtonPress(RE::InputEvent *const *eventPtr);
    void onMenuOpenClose(const RE::MenuOpenCloseEvent *event);
    void onAnimEvent(const RE::BSAnimationGraphEvent *event);

} // namespace VRExample