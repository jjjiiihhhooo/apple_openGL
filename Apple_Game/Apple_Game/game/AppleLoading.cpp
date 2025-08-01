#include "AppleLoading.h"

#include "iShadertoy.h"

AppleState as;

static AppleState asNext;
static METHOD_VOID methodFree, methodLoad;
static float delta = 0.0f;

static iShadertoy* st = NULL;
extern Texture* texGame;

void setLoading(AppleState asNext, METHOD_VOID free, METHOD_VOID load)
{
	::asNext = asNext;
	methodFree = free;
	methodLoad = load;
	delta = 0.000001f;

	if (st)
		return;
	STInfo stInfo = {
		"assets/shader/gdi.vert",
		{
			NULL,
			NULL,
			NULL,
			NULL,
			"assets/shader/fade.frag"
		},
		{
			{ NULL, NULL, NULL, NULL },// buffer A
			{ },// buffer B
			{ },// buffer C
			{ },// buffer D
			{ texGame, NULL, NULL, NULL},// Image
		},
		{
			{ -1, -1, -1, -1 },// buffer A
			{ -1, -1, -1, -1 },// buffer B
			{ -1, -1, -1, -1 },// buffer C
			{ -1, -1, -1, -1 },// buffer D
			{ -1, -1, -1, -1 },// Image
		}
	};
	setMakeCurrent(true);
	st = new iShadertoy(&stInfo);
	setMakeCurrent(false);
}

#define _delta 1.0f

void drawAppleLoading(float dt)
{
	if (delta == 0.0f)
		return;

	float a;
	if (delta < _delta)
	{
		delta += dt;
		a = delta / _delta;

		if (delta >= _delta)
		{
			delta = _delta;
			// OnPreLoad()
			methodFree();
			methodLoad();
			// PostLoad()
			as = asNext;
		}
	}
	else// if (delta < _delta * 2)
	{
		delta += dt;
		a = 1.0f - (delta - _delta) / _delta;

		if (delta >= _delta * 2)
			delta = 0.0f;
	}

	//setRGBA(0, 0, 0, a);
	//fillRect(0, 0, devSize.width, devSize.height);
	//setRGBA(1, 1, 1, 1);
	st->iTime = (1.0f - a) * M_PI / 2;
	
	st->paint(0.0f);
}

bool keyAppleLoading(iKeyStat stat, iPoint point)
{
	if (delta)
		return true;
	return false;
}
