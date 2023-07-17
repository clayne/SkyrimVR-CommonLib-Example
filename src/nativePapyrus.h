#pragma once
#include "SKSE/Impl/Stubs.h"
#include "Relocation.h"

using namespace RE;

namespace Papyrus {
    class taskAddItem : public SKSE::detail::TaskDelegate {
    public:
        virtual void Run();
        virtual void Dispose();

        taskAddItem(TESObjectREFR* akSource, TESForm* akItemToAdd, int count);
        TESObjectREFR* m_akSource;
        TESForm* m_akItemToAdd;
        int m_count;
    };
}