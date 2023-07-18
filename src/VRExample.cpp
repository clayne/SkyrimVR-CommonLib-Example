#include "VRExample.h"

namespace VRExample
{
    RE::PlayerCharacter *g_player;
    SKSE::detail::SKSETaskInterface *g_task;

    void StartMod()
    {
        SKSE::log::info("StartMod entry");
        if (g_higgsInterface)
        {
            SKSE::log::info("adding HIGGS callback");
            g_higgsInterface->AddStartTwoHandingCallback(onWeaponGrab);
        }
    }

    void onWeaponGrab()
    {
        if (g_higgsInterface)
        {
            float fingCurl[5] = {};
            g_higgsInterface->GetFingerValues(true, fingCurl);
            SKSE::log::info("Weapon Grab finger curl values: {} {} {} {} {} ", fingCurl[0], fingCurl[1], fingCurl[2],
                            fingCurl[3], fingCurl[4]);
        }
    }

    void GameLoad()
    {
        // add cabbage to player inventory
        g_player = RE::PlayerCharacter::GetSingleton();

        RE::TESForm *cabbageForm = RE::TESForm::LookupByID(0x00064b3f);
        g_task->AddTask(new Papyrus::taskAddItem((RE::TESObjectREFR *)g_player, cabbageForm, 1));

        // Add animation event sink to player
        AnimEvent::AnimationEventSink *eventSinkPlayer = AnimEvent::GetOrCreateEventSink(g_player);
    }

    taskLaunchProjectile::taskLaunchProjectile(RE::Actor *blameActor, const RE::NiPoint3 &a_origin, float x, float z, RE::TESForm *akAmmo, RE::TESObjectWEAP *a_weap, RE::BSPointerHandle<RE::Projectile> *handle)
    {
        m_akBlameActor = (RE::TESObjectREFR *)blameActor;
        m_akAmmo = akAmmo;
        *m_akBlameActor;
        m_origin = &a_origin;
        _x = x;
        _z = z;
        m_akAmmo = akAmmo;
        m_weap = a_weap;
        m_handle = handle;
        launchData = new RE::Projectile::LaunchData();
    }

    void taskLaunchProjectile::Run()
    {
        RE::Projectile::Launch(m_handle, *launchData);
    }

    void taskLaunchProjectile::Dispose()
    {

        delete this;
    }

} // namespace VRExample