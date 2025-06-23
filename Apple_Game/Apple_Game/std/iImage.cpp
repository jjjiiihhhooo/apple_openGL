#include "iImage.h"
#include "iStd.h"

iImage::iImage()
{
	array = new iArray(cbArray);
	tex = nullptr;
	index = 0;
	anc = TOP | LEFT;
	reverse = REVERSE_NONE;
	rate = 1.0f;
	position = iPointZero;
}

iImage::~iImage()
{
	delete array;
}

void iImage::cbArray(void* data)
{
	Texture* tex = (Texture*)data;
}

void iImage::add(Texture* tex)
{
	array->add(tex);
	tex->retainCount++;
}

void iImage::paint(float dt, iPoint position, float degree)
{
	tex = (Texture*)array->at(index);
	iPoint p = this->position * rate + position;
	drawImage(tex, p.x, p.y, 0, 0, tex->width, tex->height, rate, rate, 2, degree, anc, reverse);
}

iRect iImage::touchRect(iPoint position)
{
	if (tex == nullptr)
		return iRectMake(0, 0, 0, 0);

	iPoint p = this->position + position;
	return iRectMake(p.x, p.y, tex->width, tex->height);
}
