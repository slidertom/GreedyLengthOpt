#ifndef __GREEDY_LENGTH_OPT_H__
#define __GREEDY_LENGTH_OPT_H__
#pragma once

#ifndef __GREEDY_LENGTH_OPT_DEF_H__
    #include "GreedyLengthOptDef.h"
#endif

#ifndef __LENGTH_OPT_RESULTS_H__
    #include "Greedy/LengthOptResults.h"
#endif

class GREEDY_LENGTH_OPT_API CLengthGreedyOpt
{
// Static operations
public:
	static CLengthOptResults *OptimizeGreedy(std::vector<size_t> &arr, size_t nLen, size_t nSaw);
};

typedef void (*fnResultsCallback)(double* res, int row_count, int col_count);
extern "C" GREEDY_LENGTH_OPT_API void Wrapper_OptimizeGreedy(const int* arr_src, const int arr_src_count, const int nLen, const int nSaw, const fnResultsCallback res_callBack);

#endif


