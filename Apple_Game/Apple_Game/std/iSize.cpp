#include "iSize.h"

iSize& iSize::operator =(const iPoint& p)
{
	width = p.x;
	height = p.y;
	return *this;
}
	 
iSize& iSize::operator +=(const iPoint& p)
{
	width += p.x;
	height += p.y;
	return *this;
}

iSize& iSize::operator +=(const iSize& s)
{
	width += s.width;
	height += s.height;
	return *this;
}
	   
iSize& iSize::operator *=(float f)
{
	width *= f;
	height *= f;
	return *this;
}