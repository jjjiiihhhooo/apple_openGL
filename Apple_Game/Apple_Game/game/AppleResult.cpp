#include "AppleResult.h"


void loadAppleResult()
{

}

void freeAppleResult()
{

}

void drawAppleResult(float dt)
{
	setRGBA(1, 1, 1, 1);
	clear();

	setRGBA(0.333f, 0.933f, 0.58f, 1);
	fillRect(10, 10, devSize.width - 20, devSize.height - 20);
	setRGBA(0.9f, 1.0, 0.9f, 1.0);
	fillRect(30, 30, devSize.width - 60, devSize.height - 60);
	setRGBA(1, 1, 1, 1);
}

void keyAppleResult(iKeyStat stat, iPoint point)
{

}
