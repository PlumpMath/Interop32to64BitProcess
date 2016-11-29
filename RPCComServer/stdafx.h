// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#undef UNICODE
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <ComDef.h>

#if defined(INPROCESS)
    #define INPROC_SERVER 1
#else
    #define OUTPROC_SERVER 1
#endif



// TODO: reference additional headers your program requires here
