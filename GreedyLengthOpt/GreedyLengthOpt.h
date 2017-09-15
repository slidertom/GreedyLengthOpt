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

#endif


