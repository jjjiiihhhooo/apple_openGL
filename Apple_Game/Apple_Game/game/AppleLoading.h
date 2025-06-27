#pragma once

#include "iStd.h"

enum AppleState
{
	AppleStateMenu = 0,
	AppleStateProc,
	AppleStateResult,

	AppleStateMax
};

extern AppleState as;

void setLoading(AppleState asNext, METHOD_VOID free, METHOD_VOID load);
void drawAppleLoading(float dt);
bool keyAppleLoading(iKeyStat stat, iPoint point);