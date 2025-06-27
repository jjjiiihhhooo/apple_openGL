#include "Game.h"

#include "Apple.h"

Texture* texGame;

void loadGame()
{
	loadApple();

	texGame = iFBO::createImage(devSize.width, devSize.height);

}

void freeGame()
{
	freeApple();
}

void drawGame(float dt)
{
	fbo->bind(texGame);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	drawApple(dt);

	fbo->unbind();

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);// Pre-multiplied Apha

	drawImage(texGame, 0, 0, 0, 0, texGame->width, texGame->height,
		1.0f, 1.0f, 2, 0, TOP | LEFT, REVERSE_HEIGHT);
}

void keyGame(iKeyStat stat, iPoint point)
{
	keyApple(stat, point);
}
