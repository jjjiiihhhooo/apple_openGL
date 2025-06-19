#pragma once

#if _DEBUG
#pragma comment(linker, "/entry:wWindMainCRTStartup /subsystem:console")
#endif


//#define WIN32_LEAN_AND_MEAN   // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>

#if 1
#define VSNPRINTF _vsnprintf
#else
#define VSNPRINTF vsnprintf
#endif

#define va_start_end(szFormat, szText)						\
		va_list args;										\
		va_start(args, szFormat);							\
		_vsnprintf(szText, sizeof(szText), szFormat, args);	\
		va_end(args);
