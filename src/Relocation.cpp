// copied from SKSE64_common at https://skse.silverlock.org/
#include "Relocation.h"

#pragma warning(disable: 4073)	// yes this is intentional
#pragma init_seg(lib)

static RelocationManager s_relocMgr;

uintptr_t RelocationManager::s_baseAddr = 0;

RelocationManager::RelocationManager()
{
	s_baseAddr = reinterpret_cast<uintptr_t>(GetModuleHandle((char*)NULL));
}
