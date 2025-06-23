#include "AppleMenu.h"

#include "Apple.h"

iStrTex* stEx;
Texture* methodStEx(const char* s);

iImage** imgMenuBtn;
int selectedMenuBtn;

bool exOpen;

void loadAppleMenu()
{
	exOpen = false;
	iGraphics* g = iGraphics::share();
	setStringName("assets/CRRegular.ttf");
	setStringSize(25);
	setStringRGBA(1, 1, 1, 1);

	stEx = new iStrTex(methodStEx);
	stEx->set("aa");

	const char* strBtn[] = { "게임 방법", "게임 시작" };
	imgMenuBtn = new iImage * [2];
	iSize size = iSizeMake(130, 60);
	setStringRGBA(0, 0, 0, 1);
	for (int i = 0; i < 2; i++)
	{
		iImage* img = new iImage();
		for (int j = 0; j < 2; j++)
		{
			g->init(size.width, size.height);
			if (j == 0)
			{
				setStringRGBA(1, 1, 1, 1);
				setRGBA(0.2f, 0.2f, 0.2f, 1);
				g->fillRect(0, 0, size.width, size.height);
				setRGBA(1, 1, 1, 1);
				g->drawRect(2, 2, size.width - 5, size.height - 5);
			}
			else
			{
				setStringRGBA(0, 0, 0, 1);
				setRGBA(1, 1, 1, 1);
				g->fillRect(5, 5, size.width - 10, size.height - 10);
				setRGBA(0, 0, 0, 1);
				g->drawRect(7, 7, size.width - 15, size.height - 15);
			}
			g->drawString(size.width / 2, size.height / 2, VCENTER | HCENTER, strBtn[i]);

			Texture* tex = g->getTexture();
			img->add(tex);
			g->clean();
		}

		img->position = iPointMake((devSize.width - ((size.width * 2) + 20)) / 2 + (size.width + 20) * i, devSize.height - size.height - 100);
		imgMenuBtn[i] = img;
	}

	selectedMenuBtn = -1;
}

void freeAppleMenu()
{
	delete stEx;
	for (int i = 0; i < 2; i++)
		delete imgMenuBtn[i];
	delete imgMenuBtn;
}

Texture* methodStEx(const char* s)
{
	iGraphics* g = iGraphics::share();
	iSize size = iSizeMake(600, 250);
	g->init(size.width, size.height);

	setRGBA(1, 1, 1, 1);
	g->fillRect(0, 0, size.width, size.height);

	setStringRGBA(1, 1, 1, 1);
	setRGBA(0.2f, 0.2f, 0.2f, 1);
	g->fillRect(0, 0, size.width, size.height);
	setRGBA(1, 1, 1, 1);
	g->drawRect(2, 2, size.width - 5, size.height - 5);

	const char* ss[4] = {
		"1. 화면에 1부터 9까지의 숫자가 적힌 사가들이 무작위로 배치됩니다.",
		"2. 숫자 합이 10이 되도록 두 개 이상의 사과를 선택합니다.",
		"3. 선택한 사과들의 숫자 합이 10이면, 사과들이 팡! 하고 사라집니다.",
		"4. 제한 시간 안에 최대한 많은 사과를 없애면 됩니다."
	};

	setStringName("assets/CRRegular.ttf");
	setStringSize(20);
	setStringRGBA(1, 1, 1, 1);

	
	for (int i = 0; i < 4; i++)
	{
		g->drawString(10, 40 + (i * 50), TOP | LEFT, ss[i]);
	}

	Texture* tex = g->getTexture();
	g->clean();
	return tex;
}

void drawAppleMenu(float dt)
{
	setRGBA(0, 0, 0, 1);
	clear();
	setRGBA(1, 1, 1, 1);

	for (int i = 0; i < 2; i++)
	{
		imgMenuBtn[i]->index = (i == selectedMenuBtn);
		imgMenuBtn[i]->paint(dt, iPointZero);
	}

	if(exOpen)
		stEx->paint(20, 50, TOP | LEFT);

}

void keyAppleMenu(iKeyStat stat, iPoint point)
{
	int i, j = -1;

	switch (stat)
	{
	case iKeyStatBegan:
		if (selectedMenuBtn == -1) break;

		if (selectedMenuBtn == 0)
		{
			exOpen = !exOpen;
		}
		else
		{
			printf("게임 시작\n");
		}
		break;
	case iKeyStatMoved:
		for (i = 0; i < 2; i++)
		{
			if (containPoint(point, imgMenuBtn[i]->touchRect()))
			{
				j = i;
				break;
			}
		}
		if (selectedMenuBtn != j)
			printf("sound : 버튼음\n");
		selectedMenuBtn = j;
		break;
	case iKeyStatEnded:
		break;
	}
}
