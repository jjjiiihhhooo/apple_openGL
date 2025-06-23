#include "Apple.h"

#include "AppleMenu.h"
#include "AppleProc.h"

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
	case GameStateProc: freeAppleProc(); break;
	case GameStateResult: break;
	}
}

void drawApple(float dt)
{
	switch (gameState)
	{
	case GameStateMenu: drawAppleMenu(dt); break;
	case GameStateProc: drawAppleProc(dt); break;
	case GameStateResult: break;
	}
}

void keyApple(iKeyStat stat, iPoint point)
{
	switch (gameState)
	{
	case GameStateMenu: keyAppleMenu(stat, point); break;
	case GameStateProc: keyAppleProc(stat, point); break;
	case GameStateResult: break;
	}
}
