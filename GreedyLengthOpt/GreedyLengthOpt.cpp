#include "stdafx.h"
#include "GreedyLengthOpt.h"

#include "Greedy/LengthGreedyOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static inline bool DisableThreadLibraryCallsImpl(HINSTANCE hInstance)
{
    const bool bRetVal = DisableThreadLibraryCalls(hInstance) != FALSE;
    ASSERT(bRetVal);
    return bRetVal;
}

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE(L"GREEDYLENGTHOPT.DLL Initializing!\n");
        ::DisableThreadLibraryCallsImpl(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE(L"GREEDYLENGTHOPT.DLL Terminating!\n");
	}

	return 1;
}

CLengthOptResults *CLengthGreedyOpt::OptimizeGreedy(std::vector<size_t> &arr, size_t nLen, size_t nSaw)
{
	ASSERT(arr.size() > 0);
	CLengthOptResults *pResults = greedy_opt::Optimize(arr, nLen, nSaw);
	ASSERT(pResults);
	return pResults;
}
