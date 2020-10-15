#ifndef __LENGTH_GREEDY_OPT_H__
#define __LENGTH_GREEDY_OPT_H__
#pragma once

#ifndef __LENGTH_OPT_RESULTS_H__
    #include "LengthOptResults.h"
#endif

namespace greedy_opt
{
    CLengthOptResults *Optimize(std::vector<size_t> &arr, CLenArray::value_type dLen, CLenArray::value_type nSaw);
};

#endif 