#include "Game.h"

#include "Apple.h"

void loadGame()
{
	loadApple();
}

void freeGame()
{
	freeApple();
}

void drawGame(float dt)
{
	drawApple(dt);
}

void keyGame(iKeyStat stat, iPoint point)
{
	keyApple(stat, point);
}
