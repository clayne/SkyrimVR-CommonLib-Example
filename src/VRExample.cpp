#include "VRExample.h"

namespace VRExample
{
    RE::PlayerCharacter *g_player;
    SKSE::detail::SKSETaskInterface *g_task;

    void StartMod()
    {
        SKSE::log::info("StartMod entry");

        // Register MenuOpenCloseEvent handler 
        MenuChecker::begin();

        // HIGGS example
        if (g_higgsInterface)
        {
            SKSE::log::info("adding HIGGS callback");
            g_higgsInterface->AddStartTwoHandingCallback(onWeaponGrab);
        }

        // Input event example
        auto inputSink = EventSink<RE::InputEvent *>::GetSingleton();
        inputSink->AddCallback(onButtonPress);
        RE::BSInputDeviceManager::GetSingleton()->AddEventSink(inputSink);

        // Animation event example
        auto animSink = EventSink<RE::BSAnimationGraphEvent>::GetSingleton();
        animSink->AddCallback(onAnimEvent);
        // adding multiple AnimationGraphEventSinks to the same actor will CTD, should have logic here to prevent that
        RE::PlayerCharacter::GetSingleton()->AddAnimationGraphEventSink(animSink);
    }

    void GameLoad()
    {
        // add cabbage to player inventory
        g_player = RE::PlayerCharacter::GetSingleton();

        RE::TESForm *cabbageForm = RE::TESForm::LookupByID(0x00064b3f);
        g_task->AddTask(new Papyrus::taskAddItem((RE::TESObjectREFR *)g_player, cabbageForm, 1));
    }

    // HIGGS example
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

    // Input event example
    void onButtonPress(RE::InputEvent *const *eventPtr)
    {
        static bool latch = false;
        if (!eventPtr || MenuChecker::isGameStopped())
            return;

        auto *event = *eventPtr;
        if (!event)
            return;

        if (event->GetEventType() == RE::INPUT_EVENT_TYPE::kButton && event->GetDevice() == RE::INPUT_DEVICES::kVRLeft)
        {
            auto *buttonEvent = event->AsButtonEvent();
            if (buttonEvent)
            {
                latch = buttonEvent->IsDown();
                SKSE::log::info("buttonevent {} id: {}", buttonEvent->IsDown(), buttonEvent->idCode); // latch ? "down" : "up", buttonEvent->idCode);
            }
        }
    }

    // Animation event example
    void onAnimEvent(const RE::BSAnimationGraphEvent *event)
    {
        SKSE::log::info("animation event holder: {}", event->holder->GetName());
    }
} // namespace VRExample