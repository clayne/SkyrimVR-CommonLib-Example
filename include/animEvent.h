#pragma once

namespace AnimEvent
{
    struct AnimationEventSink : public RE::BSTEventSink<RE::BSAnimationGraphEvent>
    {
        AnimationEventSink(RE::Actor *actor) : a_actor(actor) {}
        RE::Actor *a_actor{nullptr};

        RE::BSEventNotifyControl ProcessEvent(const RE::BSAnimationGraphEvent *a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent> *);
    };

    AnimationEventSink *GetOrCreateEventSink(RE::Actor *a_actor);
}
