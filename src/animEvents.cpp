#include "animEvents.h"

void AnimEvents::AddEventSink()
{
    REL::Relocation<uintptr_t> PCProcessAnimGraphEventVtbl{RE::VTABLE_PlayerCharacter[2]};

    _PCProcessEvent = PCProcessAnimGraphEventVtbl.write_vfunc(0x1, &PCProcessEvent);
}

RE::BSEventNotifyControl AnimEvents::ProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent> *a_this, RE::BSAnimationGraphEvent &a_event,
                                                    RE::BSTEventSource<RE::BSAnimationGraphEvent> *a_src)
{
    if (a_event.holder != NULL)
    {
        SKSE::log::info("event name: {}", a_event.tag);
        if (a_event.tag == "JumpUp"){
            SKSE::log::info("Reacting to JumpUp event");
        }
    }
    return RE::BSEventNotifyControl::kContinue;
}

RE::BSEventNotifyControl AnimEvents::PCProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent> *a_this, RE::BSAnimationGraphEvent &a_event,
                                                      RE::BSTEventSource<RE::BSAnimationGraphEvent> *a_src)
{
    ProcessEvent(a_this, a_event, a_src);
    return _PCProcessEvent(a_this, a_event, a_src);
}