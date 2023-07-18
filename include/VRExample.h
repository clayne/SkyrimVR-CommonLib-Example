#pragma once
#include "SKSE/Impl/Stubs.h"
#include "higgsinterface001.h"
#include "nativePapyrus.h"
#include "animEvent.h"

namespace VRExample
{
    extern RE::PlayerCharacter *g_player;
    extern SKSE::detail::SKSETaskInterface *g_task;

    /// Main plugin entry point/ initialization function
    void StartMod();
    /// kPostLoadGame do stuff once player has loaded
    void GameLoad();

    /// HIGGS StartTwoHandingCallback
    void onWeaponGrab();

    class taskLaunchProjectile : public SKSE::detail::TaskDelegate
    {
    public:
        virtual void Run();
        virtual void Dispose();

        taskLaunchProjectile(RE::Actor *blameActor, const RE::NiPoint3 &a_origin, float x, float z, RE::TESForm *akAmmo, RE::TESObjectWEAP *a_weap, RE::BSPointerHandle<RE::Projectile> *handle);
        RE::TESObjectREFR *m_akBlameActor;
        const RE::NiPoint3 *m_origin;
        float _x, _z;
        RE::TESForm *m_akAmmo;
        RE::TESObjectWEAP *m_weap;
        RE::BSPointerHandle<RE::Projectile> *m_handle;
        RE::Projectile::LaunchData *launchData;
    };



} // namespace VRExample