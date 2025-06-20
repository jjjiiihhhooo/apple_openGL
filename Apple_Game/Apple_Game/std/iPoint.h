#pragma once

#include <math.h>

struct iPoint
{
	float x, y;

	bool operator == (const iPoint& p);
	bool operator != (const iPoint& p);

	iPoint& operator += (const iPoint& p);
	iPoint& operator -= (const iPoint& p);

	iPoint operator + (const iPoint& p);
	iPoint operator - (const iPoint& p);
	iPoint operator * (const iPoint& p);

	iPoint operator * (float f);
	iPoint operator / (float f);

};

iPoint iPointMake(float x, float y);
#define iPointZero iPointMake(0, 0);