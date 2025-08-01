#pragma once

#include "iPoint.h"

struct iSize
{
	float width, height;

	iSize& operator = (const iPoint& p);
	
	iSize& operator += (const iPoint& p);
	iSize& operator += (const iSize& s);

	iSize& operator *= (float f);
};

iSize iSizeMake(float width, float height);
#define iSizeZero iSizeMake(0, 0)