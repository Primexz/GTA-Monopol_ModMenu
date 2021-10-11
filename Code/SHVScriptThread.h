#pragma once
#pragma once
#include "enums.h"
#include "srcEngine.h"
inline SHVscrThread* GetActiveThread()
{
	char* moduleTls = *(char**)__readgsqword(88);
	return *reinterpret_cast<SHVscrThread**>(moduleTls + 2096);
}

inline void SetActiveThread(SHVscrThread* thread)
{
	char* moduleTls = *(char**)__readgsqword(88);

	*reinterpret_cast<SHVscrThread**>(moduleTls + 2096) = thread;
}