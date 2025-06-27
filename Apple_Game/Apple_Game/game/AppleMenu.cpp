#include "AppleMenu.h"

#include "AppleLoading.h"
#include "AppleProc.h"

iImage** imgMenuBtn;
iImage* imgLogo;

Texture* MenuBgTex;
Texture* exTex;

int selectedMenuBtn;
bool exOpen;

Texture* MethodStLogoUI(const char* str);


void loadAppleMenu()
{
	exOpen = false;
	iGraphics* g = iGraphics::share();
	setStringName("assets/CRRegular.ttf");

	imgLogo = new iImage();

	iSize size = iSizeMake(500, 500);
	g->init(size.width, size.height);
	setStringSize(50);
	setStringRGBA(1, 0.278f, 0.298f, 1);
	setRGBA(1, 1, 1, 1);

	Texture* aTex = createImage("assets/apple.png");
	float r = 100.0f / aTex->width;
	aTex->width *= r;
	aTex->height *= r;
	aTex->potWidth *= r;
	aTex->potHeight *= r;
	
	g->drawString(devSize.width / 2 - 50, devSize.height / 2 - 20, VCENTER | HCENTER, "APPLE GAME");
		
	Texture* logoTex = g->getTexture();
	imgLogo->add(aTex);
	imgLogo->add(logoTex);
	//imgLogo->position = iPointMake(devSize.width / 2, devSize.height / 2);
	g->clean();
	freeImage(aTex);
	freeImage(logoTex);

	setStringSize(16);
	setStringRGBA(1, 1, 1, 1);

	size = iSizeMake(500, 250);
	g->init(size.width, size.height);
	g->fillRect(0, 0, size.width, size.height);

	setRGBA(1, 0.278f, 0.298f, 1);
	g->fillRect(0, 0, size.width, size.height);
	setRGBA(1, 1, 1, 1);
	g->drawRect(2, 2, size.width - 5, size.height - 5);

	const char* ss[4] = {
		"1. 화면에 1부터 9까지의 숫자가 적힌 사가들이 무작위로 배치됩니다.",
		"2. 숫자 합이 10이 되도록 두 개 이상의 사과를 선택합니다.",
		"3. 선택한 사과들의 숫자 합이 10이면, 사과들이 팡! 하고 사라집니다.",
		"4. 제한 시간 안에 최대한 많은 사과를 없애면 됩니다."
	};

	for (int i = 0; i < 4; i++)
		g->drawString(10, 40 + (i * 50), TOP | LEFT, ss[i]);

	exTex = g->getTexture();
	g->clean();

	const char* strBtn[] = { "게임 방법", "게임 시작" };
	imgMenuBtn = new iImage * [2];
	size = iSizeMake(130, 60);
	setStringSize(20);
	for (int i = 0; i < 2; i++)
	{
		iImage* img = new iImage();
		for (int j = 0; j < 2; j++)
		{
			g->init(size.width, size.height);
			if (j == 0)
			{
				setStringRGBA(1, 1, 1, 1);
				setRGBA(1, 0.278f, 0.298f, 1);
				g->fillRect(0, 0, size.width, size.height);
				setRGBA(1, 1, 1, 1);
				g->drawRect(2, 2, size.width - 5, size.height - 5);
			}
			else
			{
				setStringRGBA(1, 1, 1, 1);
				setRGBA(1, 0.647f, 0, 1);
				g->fillRect(5, 5, size.width - 10, size.height - 10);
				setRGBA(1, 1, 1, 1);
				g->drawRect(7, 7, size.width - 15, size.height - 15);
			}
			g->drawString(size.width / 2, size.height / 2, VCENTER | HCENTER, strBtn[i]);

			Texture* tex = g->getTexture();

			img->add(tex);
			g->clean();
			freeImage(tex);
		}
		img->position = iPointMake((devSize.width - ((size.width * 2) + 20)) / 2 + (size.width + 20) * i, devSize.height - size.height - 60);
		imgMenuBtn[i] = img;
	}

	selectedMenuBtn = -1;
}

void freeAppleMenu()
{
	delete imgLogo;
	delete exTex;
	for (int i = 0; i < 2; i++)
		delete imgMenuBtn[i];
	delete imgMenuBtn;
}

bool isStart = false;

void drawAppleMenu(float dt)
{
	setRGBA(1, 1, 1, 1);
	clear();

	setRGBA(0.333f, 0.933f, 0.58f, 1);
	fillRect(10, 10, devSize.width - 20, devSize.height - 20);
	setRGBA(0.9f, 1.0, 0.9f, 1.0);
	fillRect(30, 30, devSize.width - 60, devSize.height - 60);
	setRGBA(1, 1, 1, 1);

	for (int i = 0; i < 2; i++)
	{
		imgLogo->index = i;
		
		if (i == 0) imgLogo->paint(dt, iPointMake(devSize.width / 2 + 120, devSize.height / 2 - 70), 20.0f);
		else imgLogo->paint(dt, iPointZero);

		imgMenuBtn[i]->index = (i == selectedMenuBtn);
		imgMenuBtn[i]->paint(dt, iPointZero);
	}
	
	if (exOpen)
		drawImage(exTex, devSize.width / 2, (devSize.height / 2) - 50, VCENTER | HCENTER);

	if (isStart)
	{
		isStart = false;
		setLoading(AppleStateProc, freeAppleMenu, loadAppleProc);
	}
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
			isStart = true;
			/*setMakeCurrent(true);
			freeAppleMenu();
			loadAppleProc();
			setMakeCurrent(false);
			gameState = GameStateProc;*/
			
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
