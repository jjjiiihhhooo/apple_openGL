#pragma once

#include "resource.h"

#include "iDefine.h"

void resize(int width, int height);
iPoint convertCoord(float x, float y);
void setCurrentMonitor(HWND hWnd, RECT& rt);
void setWindowStyle(bool fullscreen, DWORD& dwExStyle, DWORD& dwStyle);
void enforceSize(int edge, RECT& rect);
void goFullscreen();