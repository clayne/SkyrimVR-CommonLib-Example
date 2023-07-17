#include "VRExample.h"
#include "nativePapyrus.h"

namespace VRExample {
    RE::PlayerCharacter* g_player;
    SKSE::detail::SKSETaskInterface* g_task;

    void StartMod() {
        SKSE::log::info("StartMod entry");
        if (g_higgsInterface) {
            SKSE::log::info("adding HIGGS callback");
            g_higgsInterface->AddStartTwoHandingCallback(onWeaponGrab);
        }
    }

    void onWeaponGrab() {
        if (g_higgsInterface) {
            float fingCurl[5] = {};
            g_higgsInterface->GetFingerValues(true, fingCurl);
            SKSE::log::info("Weapon Grab finger curl values: {} {} {} {} {} ", fingCurl[0], fingCurl[1], fingCurl[2],
                            fingCurl[3], fingCurl[4]);
        }
    }

    void GameLoad() {
        // add cabbage to player inventory
        g_player = RE::PlayerCharacter::GetSingleton();
        TESForm* cabbageForm = TESForm::LookupByID(0x00064b3f);

        g_task->AddTask(new Papyrus::taskAddItem((TESObjectREFR*)g_player, cabbageForm, 1));
    }
}  // namespace VRExample