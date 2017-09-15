#ifndef __GREEDY_LENGTH_OPT_DEF_H__
#define __GREEDY_LENGTH_OPT_DEF_H__
#pragma once

#ifdef _BUILD_GREEDY_LENGTH_OPT
    #define GREEDY_LENGTH_OPT_API __declspec(dllexport)
#else
    #define GREEDY_LENGTH_OPT_API __declspec(dllimport)

    #ifdef _DEBUG
        #define _GREEDY_LENGTH_OPT_LIB "GreedyLengthOptD.lib"
    #else
        #define _GREEDY_LENGTH_OPT_LIB "GreedyLengthOpt.lib"
    #endif

    #pragma message("Automatic link with " _GREEDY_LENGTH_OPT_LIB)
    #pragma comment(lib, _GREEDY_LENGTH_OPT_LIB)
#endif

#endif


