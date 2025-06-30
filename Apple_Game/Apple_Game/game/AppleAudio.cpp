#include "AppleAudio.h"

iOpenAL* openal;

struct SndInfo
{
	const char* path;
	bool repeat;
	float vol;
};

void loadAudio()
{
	SndInfo si[5] = {
		{ "btn0", false, 0.2f },
		{ "btn1", false, 0.2f },
		{ "countdown", false, 0.2f},
		{ "bgm", true, 0.02f },
	};

	openal = new iOpenAL(4);
	for (int i = 0; i < 4; i++)
	{
		SndInfo* info = &si[i];
		openal->initBuffer(i, "assets/snd/%s.wav", info->path);
		openal->initSource(i, info->repeat);
		openal->volume(i, info->vol);
	}

	
}

void freeAudio()
{
	delete openal;
}

void playAudio(int index)
{
	openal->play(index);
}

void stopAudio(int index)
{
	if (index == -1)
	{
		for (int i = 0; i < openal->bufCount; i++)
			openal->stop(i);
		return;
	}
	openal->stop(index);
}

void volumeAudio(float sfx, float bgm)
{
}
