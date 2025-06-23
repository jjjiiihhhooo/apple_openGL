#include "AppleProc.h"


Apple* apple;
Texture** texAppleBg;
Texture** texAppleNum;
//====================================================
// Proc (17 x 10)
//====================================================
void loadAppleProc()
{
	srand(time(NULL));
	apple = new Apple[170];
	for (int i = 0; i < 170; i++)
	{
		Apple* a = &apple[i];
		a->num = 1 + rand() % 8;
		a->exist = (rand() % 100 < 7);
		a->selected = false;
	}

	texAppleBg = new Texture * [2];
	iGraphics* g = iGraphics::share();
	iSize size = iSizeMake(30, 30);
	for (int i = 0; i < 2; i++)
	{
		g->init(size.width, size.height);

		setRGBA(1, 1, 1, 1);
		g->fillRect(0, 0, size.width, size.height);
		if (i == 0)
		{
			setLineWidth(2);
			setRGBA(0, 0, 0, 1);
			g->drawRect(2, 2, size.width - 4, size.height - 4);
		}
		else
		{
			setRGBA(0, 1, 0, 0.5f);
			g->fillRect(0, 0, size.width, size.height);
			setRGBA(0, 1, 0, 1);
			g->drawRect(0, 0, size.width, size.height);
		}
		
		texAppleBg[i] = g->getTexture();
		g->clean();
	}

	texAppleNum = new Texture * [10];
	setStringSize(20);
	setStringRGBA(0, 0, 0, 1);
	for (int i = 0; i < 10; i++)
	{
		g->init(size.width, size.height);
		g->drawString(size.width / 2, size.height / 2, VCENTER | HCENTER, "%d", i);
		texAppleNum[i] = g->getTexture();
		g->clean();
	}
		
	loadAppleProcUI();
	loadAppleSetting();
	loadAppleCountDown();
}

void freeAppleProc()
{
	delete apple;
	for (int i = 0; i < 2; i++)
		delete texAppleBg[i];
	delete texAppleBg;
	for (int i = 0; i < 2; i++)
		delete texAppleNum[i];
	delete texAppleNum;

	freeAppleProcUI();
	freeAppleSetting();
	freeAppleCountDown();
}

void drawAppleProc(float dt)
{
	setRGBA(0, 0, 0, 1);
	clear();
	setRGBA(1, 1, 1, 1);

	for (int i = 0; i < 170; i++)
	{
		int x = APPLE_SX + 30 * (i % 17);
		int y = APPLE_SY + 30 * (i / 17);
		Apple* a = &apple[i];

		drawImage(texAppleBg[a->selected], x, y, TOP | LEFT);
		if (a->exist)
		{
			setRGBA(1, 1, 0, 1);
			fillRect(x + 10, y + 10, 10, 10);
			setRGBA(1, 1, 1, 1);
		}
		drawImage(texAppleNum[a->num], x, y, TOP | LEFT);
	}

	drawAppleProcUI(dt);
	drawAppleSetting(dt);
	drawAppleCountDown(dt);
}

bool dragApple = false;
int sx = -1, sy = -1;
void keyAppleProc(iKeyStat stat, iPoint point)
{
	if (keyAppleSetting(stat, point) ||
		keyAppleCountDown(stat, point))
		return;
}

//====================================================
// ProcUI
//====================================================
void loadAppleProcUI()
{
}

void freeAppleProcUI()
{
}

void drawAppleProcUI(float dt)
{
}

Number::Number()
{
}

Number::~Number()
{
}

void Number::update(float dt)
{
}

int Number::get()
{
	return 0;
}

void Number::add(int n)
{
}

//====================================================
// Setting
//====================================================
void loadAppleSetting()
{
}

void freeAppleSetting()
{
}

void drawAppleSetting(float dt)
{
}

bool keyAppleSetting(iKeyStat stat, iPoint point)
{
	return false;
}

//====================================================
// CountDown
//====================================================
void loadAppleCountDown()
{
}

void freeAppleCountDown()
{
}

void drawAppleCountDown(float dt)
{
}

bool keyAppleCountDown(iKeyStat stat, iPoint point)
{
	return false;
}

