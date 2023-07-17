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
        AnimEvents::AddEventSink();
    }
} // namespace VRExample