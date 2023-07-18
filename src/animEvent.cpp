namespace AnimEvent
{
    struct AnimationEventSink : public RE::BSTEventSink<RE::BSAnimationGraphEvent>
    {
        AnimationEventSink(RE::Actor *actor) : a_actor(actor) {}
        RE::Actor *a_actor{nullptr};

        RE::BSEventNotifyControl ProcessEvent(const RE::BSAnimationGraphEvent *a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent> *)
        {
            if (a_event)
            {
                if (a_event->tag == "JumpUp")
                {
                    SKSE::log::info("event: {}", a_event->tag.c_str());
                }
            }
            return RE::BSEventNotifyControl::kContinue;
        }
    };

    std::unordered_map<RE::Actor *, std::unique_ptr<AnimationEventSink>> actorEventSinks;

    AnimationEventSink *GetOrCreateEventSink(RE::Actor *a_actor)
    {
        AnimationEventSink *eventSink = nullptr;
        auto it = actorEventSinks.find(a_actor);

        if (a_actor && it != actorEventSinks.end())
        {
            eventSink = it->second.get();
        }
        else
        {
            eventSink = new AnimationEventSink(a_actor);
            actorEventSinks[a_actor] = std::unique_ptr<AnimationEventSink>(eventSink);
            a_actor->AddAnimationGraphEventSink(eventSink);
        }
        return eventSink;
    }
}