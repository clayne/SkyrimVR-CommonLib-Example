#include "nativePapyrus.h"

namespace Papyrus
{
    // AddItem
    typedef void (*_AddItem)(BSTSmartPointer<BSScript::IVirtualMachine> registry, uint32_t stackId, TESObjectREFR *akSource, TESForm *akItemToAdd, int aiCount, bool abSilent);
    RelocAddr<_AddItem> AddItem(0x009CDC20);

    taskAddItem::taskAddItem(TESObjectREFR *akSource, TESForm *akItemToAdd, int count)
    {
        m_akSource = akSource;
        m_akItemToAdd = akItemToAdd;
        m_count = count;
    }

    void taskAddItem::Run()
    {
        AddItem(RE::SkyrimVM::GetSingleton()->impl, 0, m_akSource, m_akItemToAdd, m_count, true);
    }

    void taskAddItem::Dispose() { delete this; }
}