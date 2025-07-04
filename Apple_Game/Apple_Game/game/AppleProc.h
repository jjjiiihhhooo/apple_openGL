#pragma once

#include "iStd.h"

struct Apple
{
	int num;
	float plusX;
	float plusY;
	float xRate;
	float yRate;
	float xV;
	float yV;
	bool exist;
	bool selected;
};

extern Apple* apple;

#define APPLE_SX 60
#define APPLE_SY 100

#define APPLE_W 30
#define APPLE_H 30

//====================================================
// Proc (17 x 10)
//====================================================
void loadAppleProc();
void freeAppleProc();
void drawAppleProc(float dt);
void keyAppleProc(iKeyStat stat, iPoint point);

//====================================================
// ProcUI
//====================================================
struct Number;
extern Number* score;
extern float takeTime;

void loadAppleProcUI();
void freeAppleProcUI();
void drawAppleProcUI(float dt);

struct Number
{
	Number();
public:
	virtual ~Number();

	void update(float dt);
	int get();
	void add(int n);

	float delta, _delta;
	int curr;
	int next;

	Number& operator += (int n) { add(n); return *this; }
};

//====================================================
// CountDown
//====================================================
extern int numCountDown;

void loadAppleCountDown();
void freeAppleCountDown();
void drawAppleCountDown(float dt);
bool keyAppleCountDown(iKeyStat stat, iPoint point);