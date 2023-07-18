// adapted from https://github.com/hsoju/anim-event-logger
#pragma once

namespace AnimEvents
{
    void HookProcessEvent();
    static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent> *a_this, RE::BSAnimationGraphEvent &a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent> *a_src);
    static inline REL::Relocation<decltype(ProcessEvent)> _PCProcessEvent;
}