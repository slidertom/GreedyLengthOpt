#include "stdafx.h"
#include "LengthGreedyOpt.h"

#include "numeric"
#include "algorithm"
#include "string"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static inline size_t RemoveMatch(std::vector<size_t> &arr, CLenArray::value_type nLen)
{
	size_t nCount = 0;
	for (auto i1 = arr.begin(); i1 != arr.end(); ++i1)
	{
		if ( *i1 == nLen )
		{
            auto del_it = i1;
			arr.erase(del_it);
			--i1;
			++nCount;
			continue;
		}
		ASSERT(*i1 < nLen);
	}
	return nCount;
}

static inline bool CompareIntStl(size_t arg1, size_t arg2) {
	if (arg1 < arg2 || arg1 == arg2 ) {
		return false;
	}
	return true;
}

static inline void GetCountGreedy(const std::vector<size_t> &arr, size_t nTotal, size_t nSaw, CLengthOptResults &results)
{
	for (const CLenArray::value_type val : arr) {
		results.AddEx(val, nTotal, nSaw);
	}
}

static bool TraceLengths(const CLenArray &arr)
{
	for (auto nLen : arr) {
		std::wstring str = std::to_wstring(nLen);
		TRACE(str.c_str());
		TRACE(L"\n");
	}
	return true;
}

namespace greedy_opt
{
    CLengthOptResults *Optimize(std::vector<size_t> &arr, CLenArray::value_type nLen, size_t nSaw)
    {
	    const size_t nMatchCount = ::RemoveMatch(arr, nLen);

	    //ASSERT(TraceLengths(arr));
	    std::sort(arr.begin(), arr.end(), ::CompareIntStl);
		//ASSERT(TraceLengths(arr));

	    CLengthOptResults *pResults = new CLengthOptResults;
	    const ptrdiff_t nCnt = arr.size() - 2;
	    if ( nCnt <= 0 ) {
		    pResults->AddTotalLengths(nLen, nMatchCount);
		    GetCountGreedy(arr, nLen, nSaw, *pResults);
		    return pResults;
	    }

	    GetCountGreedy(arr, nLen, nSaw, *pResults);
		ASSERT(pResults->GetLengthsCount() == arr.size());

	    //return nCount;
	    ASSERT(pResults);
        #ifdef _DEBUG
        size_t nLenCnt1 = pResults->GetLengthsCount();
		//size_t nCnt1 = pResults->size();
		//bool bDo = true;
		//while (bDo) { // multiple iiterations does not provide better resutls
		//	bDo = false;
        #endif
		//pResults->Compact(nLen, nSaw);
        //pResults->Distribute(nLen, nSaw);
        #ifdef _DEBUG
		//	size_t nCnt2 = pResults->size();
		//	if ( nCnt1 != nCnt2 ) {
		//		nCnt1 = nCnt2;
		//		bDo = true;
		//	}
		//}
        size_t nLenCnt2 = pResults->GetLengthsCount();
        ASSERT(nLenCnt1 == nLenCnt2);
        #endif

		#ifdef _DEBUG
		ASSERT(pResults->Validate(nLen, nSaw));
		size_t nRessAllLen = pResults->GetAllLength();
		size_t nSrcAllLen  = 0;
		for (const auto &val : arr) {
			nSrcAllLen += val;
		}
		ASSERT(nRessAllLen == nSrcAllLen);
		#endif

	    pResults->AddTotalLengths(nLen, nMatchCount);
	    return pResults;
    }
};
