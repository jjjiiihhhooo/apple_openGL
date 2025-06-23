
#include "iFPS.h"

#include "Windows.h"
#include "iGraphics.h"

iFPS::iFPS()
{
	lastUpdate = GetTickCount();
}

iFPS::~iFPS()
{

}


iFPS* iFPS::share()
{
#if 0
	static iFPS* fps = new iFPS();
	return fps;
#else
	static iFPS instance;
	return &instance;
#endif
}



float iFPS::update()
{
	DWORD now = GetTickCount();
	float delta = (now - lastUpdate) / 1000.0f;
	lastUpdate = now;

	count++;
	takeTime += delta;

	while (takeTime > fpsInterval)
	{
		int m = count / takeTime;
		takeTime -= fpsInterval;
		count = m * takeTime;
	}

	return delta;
}

int iFPS::framePerSec()
{
	int fps = count / takeTime;
	return fps;
}