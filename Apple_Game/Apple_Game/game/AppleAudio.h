#pragma once

#include "iStd.h"

void loadAudio();
void freeAudio();
void playAudio(int index);
void stopAudio(int stop = 0);
void volumeAudio(float sfx, float bgm);

enum Audio
{
	AudioBtnClr = 0,
	AudioBtnOk,
	AudioCountDown,
	AudioBGM,
	AudioProcBGM,
	AudioMax
};