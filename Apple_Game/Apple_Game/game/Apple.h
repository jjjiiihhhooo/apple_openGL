#pragma once

#include "iStd.h"

void loadApple();
void freeApple();
void drawApple(float dt);
void keyApple(iKeyStat stat, iPoint point);

enum GameState
{
	GameStateMenu, GameStateProc, GameStateResult
};

extern GameState gameState