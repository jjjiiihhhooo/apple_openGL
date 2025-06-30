#include "Apple.h"

#include "AppleAudio.h"
#include "AppleLoading.h"
#include "AppleMenu.h"
#include "AppleProc.h"
#include "AppleResult.h"


void loadApple()
{
	loadAppleMenu();
	as = AppleStateMenu;

	loadAudio();
	playAudio(AudioBGM);
}

void freeApple()
{
	switch (as)
	{
	case AppleStateMenu: freeAppleMenu(); break;
	case AppleStateProc: freeAppleProc(); break;
	case AppleStateResult: freeAppleResult(); break;
	}
}

void drawApple(float dt)
{
	switch (as)
	{
	case AppleStateMenu: drawAppleMenu(dt); break;
	case AppleStateProc: drawAppleProc(dt); break;
	case AppleStateResult: drawAppleResult(dt); break;
	}

	drawAppleLoading(dt);
}

void keyApple(iKeyStat stat, iPoint point)
{
	if (keyAppleLoading(stat, point)) return;

	switch (as)
	{
	case AppleStateMenu: keyAppleMenu(stat, point); break;
	case AppleStateProc: keyAppleProc(stat, point); break;
	case AppleStateResult: keyAppleResult(stat, point); break;
	}
}
