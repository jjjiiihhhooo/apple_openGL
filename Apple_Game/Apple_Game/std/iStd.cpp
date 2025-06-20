#include "iStd.h"

METHOD_VOID methodFree;
METHOD_FLOAT methodDraw;
METHOD_KEY methodKey;

void loadApp(HWND hWnd, METHOD_VOID load, METHOD_VOID free, METHOD_FLOAT draw, METHOD_KEY key)
{
	load();

	methodFree = free;
	methodDraw = draw;
	methodKey = key;
}

void freeApp()
{
	methodFree();
}

void drawApp(float dt)
{
	methodDraw(dt);
}

void keyApp(iKeyStat stat, iPoint point)
{
	methodKey(stat, point);
}
