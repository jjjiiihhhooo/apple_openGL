#include "Apple.h"
#include "AppleMenu.h"

GameState gameState;

void loadApple()
{
	gameState = GameStateMenu;
	loadAppleMenu();
}

void freeApple()
{
	switch (gameState)
	{
	case GameStateMenu: freeAppleMenu(); break;
	case GameStateProc: break;
	case GameStateResult: break;
	}
}

void drawApple(float dt)
{
	switch (gameState)
	{
	case GameStateMenu: drawAppleMenu(dt); break;
	case GameStateProc: break;
	case GameStateResult: break;
	}
}

void keyApple(iKeyStat stat, iPoint point)
{
	switch (gameState)
	{
	case GameStateMenu: keyAppleMenu(stat, point); break;
	case GameStateProc: break;
	case GameStateResult: break;
	}
}
