// adapted from https://github.com/hsoju/anim-event-logger

namespace AnimEvents
{
    void AddEventSink();
    static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent> *a_this, RE::BSAnimationGraphEvent &a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent> *a_src);
    static RE::BSEventNotifyControl PCProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent> *a_this, RE::BSAnimationGraphEvent &a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent> *a_src);
    static inline REL::Relocation<decltype(ProcessEvent)> _PCProcessEvent;
}
