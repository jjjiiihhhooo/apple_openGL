#pragma once

class iFPS
{
private:
	iFPS();
public:
	virtual ~iFPS();

	static iFPS* share();
	float update();
	
	unsigned long lastUpdate;

	int framePerSec();
	int count;
	float takeTime;
};

#define fpsInterval 5.0f