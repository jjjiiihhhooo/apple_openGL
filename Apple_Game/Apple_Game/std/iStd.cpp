#include "iStd.h"

iSize devSize;
iRect viewport;

static float _r, _g, _b, _a;

METHOD_VOID methodFree;
METHOD_FLOAT methodDraw;
METHOD_KEY methodKey;

void loadApp(HWND hWnd, METHOD_VOID load, METHOD_VOID free, METHOD_FLOAT draw, METHOD_KEY key)
{
	_r = 1.0f;
	_g = 1.0f;
	_b = 1.0f;
	_a = 1.0f;

	load();

	methodFree = free;
	methodDraw = draw;
	methodKey = key;
}

void freeApp()
{
	methodFree();
}

void drawApp(float dt)
{
	methodDraw(dt);
}

void keyApp(iKeyStat stat, iPoint point)
{
	methodKey(stat, point);
}

void getRGBA(float& r, float& g, float& b, float& a)
{
	r = _r, g = _g, b = _b, a = _a;
}

void setRGBA(float r, float g, float b, float a)
{
	_r = r, _g = g, _b = b, _a = a;
}

void clear()
{

}

float lineWidth = 1;
void setLineWidth(float width)
{
	lineWidth = width;
}

void drawLine(float x0, float y0, float x1, float y1)
{

}

void drawLine(iPoint p0, iPoint p1)
{
}

void drawRect(float x, float y, float width, float height, float radius)
{
}

void drawRect(iRect rt, float radius)
{
}

void fillRect(float x, float y, float width, float height, float radius)
{
}

void fillRect(iRect rt, float radius)
{
}

uint32 nextPot(uint32 x)
{
	return uint32();
}

uint8* bmp2rgba(Bitmap* bmp, int& width, int& height)
{
	return nullptr;
}

Texture* createImageWithRGBA(uint8* rgba, int width, int height)
{
	return nullptr;
}

Texture* createImage(const char* szFormat, ...)
{
	return nullptr;
}

Texture** createImage(int wNum, int hNum, const char* szFormat, ...)
{
	return nullptr;
}

void freeImage(Texture* tex)
{
}

void drawImage(Texture* tex, float x, float y, int anc)
{
}

void drawImage(Texture* tex, float x, float y, int sx, int sy, int sw, int sh, float rateX, float rateY, int xyz, float degree, int anc, int reverse)
{
}

const char* getStringName()
{
	return nullptr;
}

void setStringName(const char* name)
{
}

float getStringSize()
{
	return 0.0f;
}

void setStringSize(float size)
{
}

float getStringLineHeight()
{
	return 0.0f;
}

void setStringLineHeight(float height)
{
}

void getStringRGBA(float& r, float& g, float& b, float& a)
{
}

void setStringRGBA(float r, float g, float b, float a)
{
}

iRect rectOfString(const char* szFormat, ...)
{
	return iRect();
}

void drawString(float x, float y, int anc, const char* szFormat, ...)
{
}

wchar_t* utf8_to_utf16(const char* szFormat, ...)
{
	return nullptr;
}

char* utf16_to_utf8(const wchar_t* wStr)
{
	return nullptr;
}

float clamp(float f, float min, float max)
{
	return 0.0f;
}

char* loadFile(int& len, const char* szFormat, ...)
{
	return nullptr;
}

void saveFile(char* buf, int bufLen, const char* szFormat, ...)
{
}
