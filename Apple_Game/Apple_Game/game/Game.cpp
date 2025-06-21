#include "Game.h"

#include "AppleMenu.h"

void loadGame()
{
	loadAppleMenu();
}

void freeGame()
{
	freeAppleMenu();
}

void drawGame(float dt)
{
	drawAppleMenu(dt);
}

void keyGame(iKeyStat stat, iPoint point)
{
	keyAppleMenu(stat, point);
}
