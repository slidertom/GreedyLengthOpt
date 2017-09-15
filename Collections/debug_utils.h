#ifndef __DEBUG_UTILS_H__
#define __DEBUG_UTILS_H__
#pragma once

#ifdef _DEBUG
	#include "debugapi.h" // msw specific

// Should be in the separe file
// Trace functionality
inline void TraceDump(const wchar_t *lpsz)
{
	if (!lpsz) {
		OutputDebugString(L"(NULL)");
	}

	#ifndef _countof
		#define _countof(array) (sizeof(array)/sizeof(array[0]))
	#endif

	wchar_t szBuffer[512];
	LPTSTR lpBuf = szBuffer;
	while (*lpsz != '\0')
	{
		if (lpBuf > szBuffer + _countof(szBuffer) - 3)
		{
			*lpBuf = '\0';
			OutputDebugString(szBuffer);
			lpBuf = szBuffer;
		}
		if (*lpsz == '\n')
			*lpBuf++ = '\r';
		*lpBuf++ = *lpsz++;
	}

	*lpBuf = '\0';
	OutputDebugString(szBuffer);
}

#include <stdio.h>

inline void Trace(const wchar_t *format, ... )
{
	va_list args;
	wchar_t buf[1500]; 
					   
	va_start(args, format);
	vswprintf(buf, format, args);
	va_end(args);

	OutputDebugString(buf);
}
#endif //_DEBUG

// Define TRACE
#ifdef _DEBUG
	#ifndef TRACE 
		#define TRACE Trace
	#endif
#else
	#ifndef TRACE
		#define TRACE 
	#endif
#endif

// TRACE defined


#ifdef _DEBUG

#ifndef __LEAK_WATCH
#define __LEAK_WATCH

#include <crtdbg.h>

__inline void* __cdecl operator new(size_t nSize, const char * lpszFileName, int nLine)
{
    return ::operator new(nSize, 1, lpszFileName, nLine);
}

//Disabling recursive function call warning since it does not cause any crash and
//delete operator required for new to be overrided
#pragma warning(disable: 4717)

__inline void __cdecl operator delete(void * _P, const char * lpszFileName, int nLine)
{
	::operator delete(_P, lpszFileName, nLine);
}

#define DEBUG_NEW new(__FILE__, __LINE__)
#define malloc(s)       _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define calloc(c, s)    _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(p, s)   _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _expand(p, s)   _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define free(p)         _free_dbg(p, _NORMAL_BLOCK)
#define _msize(p)       _msize_dbg(p, _NORMAL_BLOCK)

#endif

#endif // _DEBUG

#ifndef DEBUG_ONLY
    #ifdef _DEBUG
        #define DEBUG_ONLY(f)      (f)
    #else
        #define DEBUG_ONLY(f)      ((void)0)
    #endif
#endif

#ifndef ASSERT
    #ifdef _DEBUG
        #include "crtdbg.h" // msw specific
		#include <assert.h>
        inline BOOL AssertFailedLine(LPCSTR lpszFileName, int nLine) // MSW specific do stop on line
        {
            // we remove WM_QUIT because if it is in the queue then the message box
            // won't display
            MSG msg;
            BOOL bQuit = PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);
            BOOL bResult = _CrtDbgReport(_CRT_ASSERT, lpszFileName, nLine, NULL, NULL);
            if (bQuit)
	            PostQuitMessage((int)msg.wParam);
            return bResult;
        }
        #define ASSERT(f)          DEBUG_ONLY((void) ((f) || !::AssertFailedLine(__FILE__, __LINE__) || (__debugbreak(), 0)))
		//#define ASSERT(f) assert((f)) // non msw impl
    #else
        #define ASSERT(f) 
    #endif
#endif

#endif