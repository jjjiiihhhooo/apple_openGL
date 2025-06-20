#include "iPoint.h"

bool iPoint::operator == (const iPoint& p)
{
	bool same = fabsf(x - p.x) < 0.0001 && fabsf(y - p.y) < 0.0001;
	if (same)
	{
		x = p.x;
		y = p.y;
	}
	return same;
}

bool iPoint::operator != (const iPoint& p)
{
	return x != p.x || y != p.y;
}


iPoint& iPoint::operator += (const iPoint& p)
{
	x += p.x;
	y += p.y;
	return *this;
}

iPoint& iPoint::operator -= (const iPoint& p)
{
	x -= p.x;
	y -= p.y;
	return *this;
}

iPoint iPoint::operator + (const iPoint& p)
{
	iPoint r;
	r.x = x + p.x;
	r.y = y + p.y;
	return r;
}
iPoint iPoint::operator - (const iPoint& p)
{
	iPoint r;
	r.x = x - p.x;
	r.y = y - p.y;
	return r;
}
iPoint iPoint::operator * (const iPoint& p)
{
	iPoint r;
	r.x = x * p.x;
	r.y = y * p.y;
	return r;
}

iPoint iPoint::operator * (float f)
{
	iPoint r;
	r.x = x * f;
	r.y = y * f;
	return r;
}

iPoint iPoint::operator / (float f)
{
	iPoint r;
	r.x = x / f;
	r.y = y / f;
	return r;
}

iPoint iPointMake(float x, float y)
{
	iPoint p;
	p.x = x;
	p.y = y;
	return p;
}
