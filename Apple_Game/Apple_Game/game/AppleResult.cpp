#include "AppleResult.h"

#include "AppleAudio.h"
#include "AppleLoading.h"
#include "AppleProc.h"

Texture* scoreTex;
iImage** imgResultBtn;

int scoreNum = 0; 
int selectedResultBtn;
bool isReStart;

void loadAppleResult()
{
	setStringSize(55);
	setStringRGBA(1, 1, 1, 1);

	iGraphics* g = iGraphics::share();
	iSize size = iSizeMake(400, 200);
	g->init(size.width, size.height);
	g->fillRect(0, 0, size.width, size.height);

	setRGBA(1, 0.278f, 0.298f, 1);
	g->fillRect(0, 0, size.width, size.height);
	setRGBA(1, 1, 1, 1);
	g->drawRect(2, 2, size.width - 5, size.height - 5);

	g->drawString(size.width / 2, size.height / 2, VCENTER | HCENTER, "SCORE : %d", scoreNum);

	scoreTex = g->getTexture();
	g->clean();

	const char* strBtn[] = { "다시 하기", "게임 종료" };
	imgResultBtn = new iImage * [2];
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
		imgResultBtn[i] = img;
	}

	isReStart = false;
	selectedResultBtn = -1;
}

void freeAppleResult()
{
	delete scoreTex;
	
	for (int i = 0; i < 2; i++)
		delete imgResultBtn[i];
	delete imgResultBtn;
}

void drawAppleResult(float dt)
{
	setRGBA(1, 1, 1, 1);
	clear();

	setRGBA(0.333f, 0.933f, 0.58f, 1);
	fillRect(10, 10, devSize.width - 20, devSize.height - 20);
	setRGBA(0.9f, 1.0, 0.9f, 1.0);
	fillRect(30, 30, devSize.width - 60, devSize.height - 60);
	setRGBA(1, 1, 1, 1);
	drawImage(scoreTex, devSize.width / 2, (devSize.height / 2) - 50, VCENTER | HCENTER);

	for (int i = 0; i < 2; i++)
	{
		imgResultBtn[i]->index = (i == selectedResultBtn);
		imgResultBtn[i]->paint(dt, iPointZero);
	}

	if (isReStart)
	{
		isReStart = false;
		setLoading(AppleStateProc, freeAppleResult, loadAppleProc);
	}
}

void keyAppleResult(iKeyStat stat, iPoint point)
{
	int i, j = -1;

	switch (stat)
	{
	case iKeyStatBegan:
		if (selectedResultBtn == -1) break;

		playAudio(AudioBtnClr);
		if (selectedResultBtn == 0)
		{
			isReStart = true;
		}
		else
		{
			printf("게임 종료\n");
			exit(0);
		}
		break;
	case iKeyStatMoved:
		for (i = 0; i < 2; i++)
		{
			if (containPoint(point, imgResultBtn[i]->touchRect()))
			{
				j = i;
				break;
			}
		}
		if (selectedResultBtn != j)
		{
			//printf("sound : 버튼음\n");
		}
		selectedResultBtn = j;
		break;
	case iKeyStatEnded:
		break;
	}
}
