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

void Wrapper_OptimizeGreedy(const int* arr_src, const int arr_src_count, const int nLen, const int nSaw, const fnResultsCallback res_callBack)
{
    std::vector<size_t> v_arr;
    for ( int i = 0; i < arr_src_count; ++i ) {
        v_arr.push_back(arr_src[i]);
    }

    CLengthOptResults *pRes = CLengthGreedyOpt::OptimizeGreedy(v_arr, nLen, nSaw);

    // find max count in order to create a table with same amount of columns where undefined value = -1
    int max_count = 0;

    const int count = (int)pRes->size();
    for ( int i = 0; i < count; ++i ) {
        max_count = max_count > (int)(*pRes)[i]->size() ? max_count : (int)(*pRes)[i]->size();
    }

    const double undef_val = -1.0;
    double *res = new double[count * max_count];

    for ( int i = 0; i < count; ++i ) {
        for (int j = 0; j < max_count; ++j) {
            double val = j >= (int)(*pRes)[i]->size() ? undef_val : (*pRes)[i]->at(j);
            res[i * max_count + j] = val;
        }
    }

    if ( res_callBack ) {
        res_callBack(res, count, max_count);
    }

    delete [] res;
    delete pRes;
}
