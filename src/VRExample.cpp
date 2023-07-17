#include "VRExample.h"

namespace VRExample {
    HiggsPluginAPI::IHiggsInterface001* higgsInterface;
    float fingCurl[5] = {};

    void StartMod() {
        SKSE::log::info("StartMod entry");
        if (higgsInterface) {
            SKSE::log::info("adding HIGGS callback");
            higgsInterface->AddStartTwoHandingCallback(onWeaponGrab);
        }
    }

    void onWeaponGrab() {
        if (higgsInterface) {
            higgsInterface->GetFingerValues(true, fingCurl);
            SKSE::log::info("Weapon Grab finger curl values: {} {} {} {} {} ", fingCurl[0], fingCurl[1],
                             fingCurl[2], fingCurl[3], fingCurl[4]);
        }
    }

}  // namespace VRExample