#pragma once

#if _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#include <Windows.h>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib, "opengl32")

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#define DEV_WIDTH 640
#define DEV_HEIGHT 480

typedef unsigned char uint8, byte;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint32;
typedef signed int int32;

enum iKeyStat
{
	iKeyStatBegan = 0,
	iKeyStatMoved,
	iKeyStatEnded,
	iKeyStatCancel
};

struct iPoint;
struct iSize;
struct iRect;

#define keydown_none 0// 00000000 00000000 00000000 00000000 
#define keydown_w    1// 00000000 00000000 00000000 00000001 
#define keydown_a    2// 00000000 00000000 00000000 00000010 
#define keydown_s    4// 00000000 00000000 00000000 00000100 
#define keydown_d    8// 00000000 00000000 00000000 00001000 
#define keydown_up   16// 00000000 00000000 00000000 00001000 
#define keydown_left  32// 00000000 00000000 00000000 00001000 
#define keydown_down   64// 00000000 00000000 00000000 00001000 
#define keydown_right   128// 00000000 00000000 00000000 00001000 
#define keydown_space 256
#define keydown_what   1<<31// 10000000 00000000 00000000 00000000 

#define LEFT		1
#define RIGHT		2
#define HCENTER		4
#define TOP			8
#define BOTTOM		16
#define VCENTER		32

#define REVERSE_NONE	0
#define REVERSE_WIDTH	1
#define REVERSE_HEIGHT	2


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
