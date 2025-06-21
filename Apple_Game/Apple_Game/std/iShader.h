#pragma once

#include "iDefine.h"
#include "iPoint.h"
#include "iArray.h"
#include "iRect.h"

struct iImage
{
public:
	iImage();
	virtual ~iImage();

	static void cbArray(void* data);

	void add(Texture* tex);

	void paint(float dt, iPoint position, float degree = 0.0f);

	iRect touchRect(iPoint position = iPointZero);
public:
	iArray* array;
	Texture* tex;
	int index, anc, reverse;
	float rate;
	iPoint position;
};
