#pragma once

#include "iDefine.h"

#include "iPoint.h"
#include "iSize.h"
#include "iRect.h"
#include "iFPS.h"

void loadApp(HWND hWnd, METHOD_VOID load, METHOD_VOID free, METHOD_FLOAT draw, METHOD_KEY key);
void freeApp();
void drawApp(float dt);
void keyApp(iKeyStat stat, iPoint point);