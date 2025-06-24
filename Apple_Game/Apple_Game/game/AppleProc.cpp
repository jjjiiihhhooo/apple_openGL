#include "AppleProc.h"


Apple* apple;
iImage* appleBgImg;
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
		//a->exist = (rand() % 100 < 7);
		a->selected = false;
	}

	iGraphics* g = iGraphics::share();
	iSize size = iSizeMake(30, 30);

#if 0 // 사과이미지로 변경
	texAppleBg = new Texture * [2];
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
#else
	appleBgImg = new iImage();
	Texture* tex = createImage("assets/apple.png");
	float r = size.width / tex->width;
	tex->width *= r;
	tex->height *= r;
	tex->potWidth *= r;
	tex->potHeight *= r;
	appleBgImg->add(tex);
	freeImage(tex);
#endif

	texAppleNum = new Texture * [10];
	setStringSize(15);
	setStringRGBA(1, 1, 1, 1);
	for (int i = 0; i < 10; i++)
	{
		g->init(size.width, size.height);
		g->drawString(size.width / 2, size.height / 2 + 3, VCENTER | HCENTER, "%d", i);
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
	delete appleBgImg;

	for (int i = 0; i < 10; i++)
		delete texAppleNum[i];
	delete texAppleNum;

	freeAppleProcUI();
	freeAppleSetting();
	freeAppleCountDown();
}

void drawAppleProc(float dt)
{
	setRGBA(1, 1, 1, 1);
	clear();

	setRGBA(0, 1, 0, 1);
	fillRect(20, 20, devSize.width - 40, devSize.height - 40);
	setRGBA(1, 1, 1, 0.6f);
	fillRect(25, 25, devSize.width - 50, devSize.height - 50);
	setRGBA(1, 1, 1, 1);
	for (int i = 0; i < 170; i++)
	{
		int x = APPLE_SX + 30 * (i % 17);
		int y = APPLE_SY + 30 * (i / 17);
		Apple* a = &apple[i];

		//drawImage(texAppleBg[a->selected], x, y, TOP | LEFT);
		/*if (a->exist)
		{
			setRGBA(1, 1, 0, 1);
			fillRect(x + 10, y + 10, 10, 10);
			setRGBA(1, 1, 1, 1);
		}*/

		appleBgImg->paint(dt, iPointMake(x, y));

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

	switch (stat)
	{
	case iKeyStatBegan:
	{
		int x = point.x - APPLE_SX;
		x /= APPLE_SX;
		int y = point.y - APPLE_SY;
		y /= APPLE_SY;
		if (x < 0) x = 0;
		else if (x > 16) x = 16;
		if (y < 0) y = 0;
		else if (y > 16) y = 16;

		Apple* a = &apple[17 * y + x];
		a->selected = true;

		dragApple = true;
		sx = x;
		sy = y;
	}
	break;

	case iKeyStatMoved:
		if (dragApple)
		{
			int x = point.x - APPLE_SX;
			x /= APPLE_SX;
			int y = point.y - APPLE_SY;
			y /= APPLE_SY;
			if (x < 0) x = 0;
			else if (x > 16) x = 16;
			if (y < 0) y = 0;
			else if (y > 16) y = 16;

			if (x == sx && y == sy)
			{
				for (int i = 0; i < 170; i++)
				{
					Apple* a = &apple[i];
					a->selected = false;
				}
				Apple* a = &apple[17 * sy + sx];
				a->selected = true;
			}
			else
			{
				for (int i = 0; i < 170; i++)
				{
					Apple* a = &apple[i];
					a->selected = false;
				}

				int cx = x < sx ? x : sx;
				int cy = y < sy ? y : sy;
				int nx = cx + abs(x - sx) + 1;
				int ny = cy + abs(y - sy) + 1;
				for (int j = cy; j < ny; j++)
				{
					for (int i = cx; i < nx; i++)
					{
						Apple* a = &apple[17 * j + i];
						a->selected = true;
					}
				}
			}
		}
		break;
	case iKeyStatEnded:
		if (dragApple)
		{
			dragApple = false;

			int sum = 0;
			for (int i = 0; i < 170; i++)
			{
				Apple* a = &apple[i];
				if (a->selected == false || a->num == 10) continue;
				sum += a->num;
			}
			if (sum == 10)
			{
				int n = 0;
				for (int i = 0; i < 170; i++)
				{
					Apple* a = &apple[i];
					if (a->selected == false) continue;
					a->selected = false;
					if (a->num == 10) continue;
					a->num = 10;
					n += 1;
				}

				score->add(n);
			}
			else
			{
				for (int i = 0; i < 170; i++)
				{
					Apple* a = &apple[i];
					a->selected = false;
				}
			}
		}
	
		break;
	}
}

//====================================================
// ProcUI
//====================================================
Number* score;

float takeTime;
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
	curr = 0;
	next = 0;
	_delta = 0.5f;
	delta = _delta;
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

