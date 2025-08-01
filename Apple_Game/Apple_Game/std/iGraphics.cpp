#include "iGraphics.h"

#include "iStd.h"

iGraphics::iGraphics()
{
	bmp = NULL;
	g = NULL;
}

iGraphics::~iGraphics()
{
	clean();
}

void iGraphics::clear()
{
	float r, g, b, a;
	getRGBA(r, g, b, a);

	this->g->Clear(Color(a * 0xFF, r * 0xFF, g * 0xFF, b * 0xFF));
}

void iGraphics::clear(Graphics* graphics, float r, float g, float b, float a)
{
	graphics->Clear(Color(a * 0xFF, r * 0xFF, g * 0xFF, b * 0xFF));
}


iGraphics* iGraphics::share()
{
	static iGraphics* g = new iGraphics();
	return g;
}

void iGraphics::init(int width, int height)
{
	clean();

	bmp = new Bitmap(width, height);
	g = Graphics::FromImage(bmp);
}

Texture* iGraphics::getTexture()
{
	if (bmp == NULL)
		return NULL;

	int width, height;
	uint8* rgba = bmp2rgba(bmp, width, height);
	clean();

	Texture* tex = createImageWithRGBA(rgba, width, height);
	delete rgba;

	return tex;
}

void iGraphics::clean()
{
	if (bmp)
	{
		delete bmp;
		bmp = NULL;
	}
	if (g)
	{
		delete g;
		g = NULL;
	}
}

void iGraphics::drawLine(float x0, float y0, float x1, float y1)
{
	float r, g, b, a;
	getRGBA(r, g, b, a);
	Pen pen(Color(a * 0xFF, r * 0xFF, g * 0xFF, b * 0xFF));

	this->g->DrawLine(&pen, x0, y0, x1, y1);
}

void iGraphics::drawLine(iPoint p0, iPoint p1)
{
	drawLine(p0.x, p0.y, p1.x, p1.y);
}

void iGraphics::drawRect(float x, float y, float width, float height)
{
	float r, g, b, a;
	getRGBA(r, g, b, a);
	Pen pen(Color(a * 0xFF, r * 0xFF, g * 0xFF, b * 0xFF));
	this->g->DrawRectangle(&pen, x, y, width, height);
}

void iGraphics::drawRect(iRect rt)
{
	drawRect(rt.origin.x, rt.origin.y, rt.size.width, rt.size.height);
}

void iGraphics::fillRect(float x, float y, float width, float height)
{
	float r, g, b, a;
	getRGBA(r, g, b, a);
	SolidBrush brush(Color(a * 0xFF, r * 0xFF, g * 0xFF, b * 0xFF));
	this->g->FillRectangle(&brush, x, y, width, height);
}

void iGraphics::fillRect(iRect rt)
{
	fillRect(rt.origin.x, rt.origin.y, rt.size.width, rt.size.height);
}

void iGraphics::drawImage(Texture* tex, float x, float y, int anc)
{
#if 0
	Graphics* bk = getGraphics();
	setGraphics(g);
	::drawImage(tex, x, y, anc);
	setGraphics(bk);
#endif
}

void iGraphics::drawImage(Texture* tex, float x, float y, int sx, int sy, int sw, int sh, float rateX, float rateY, int xyz, float degree, int anc, int reverse)
{

}

void iGraphics::drawString(float x, float y, int anc, const char* szFormat, ...)
{
	char szText[512];
	va_start_end(szFormat, szText);

	drawString(g, x, y, anc, szText);
}

void checkFontFamily(const char* stringName, FontFamily* ff, FontStyle& fs)
{
	if (strncmp(stringName, "ass", 3))
	{
		wchar_t* sn = utf8_to_utf16(stringName);
		FontFamily  fontFamily(sn);
		delete sn;
		memcpy(ff, &fontFamily, sizeof(FontFamily));
		fs = FontStyleRegular;
	}
	else
	{
		PrivateFontCollection* pfc = new PrivateFontCollection();
		wchar_t* path = utf8_to_utf16(stringName);
		pfc->AddFontFile(path);
		delete path;

		int count = pfc->GetFamilyCount();
		int found;
		pfc->GetFamilies(count, ff, &found);// ff

		for (int i = 0; i < found; i++)
		{
			if (ff->IsStyleAvailable(FontStyleRegular))
			{
				fs = FontStyleRegular;// fs
				break;
			}
			else if (ff->IsStyleAvailable(FontStyleBold))
			{
				fs = FontStyleBold;
				break;
			}
		}
		delete pfc;
	}
}

void iGraphics::drawString(Graphics* graphics, float x, float y, int anc, const char* szFormat, ...)
{
	char szText[512];
	va_start_end(szFormat, szText);

	iRect rt = rectOfString(szText);
	x -= rt.origin.x;
	y -= rt.origin.y;
	int w = rt.size.width, h = rt.size.height;
	switch (anc) {
	case TOP | LEFT:                               break;
	case TOP | HCENTER:     x -= w / 2;            break;
	case TOP | RIGHT:       x -= w;                break;
	case VCENTER | LEFT:    x;         y -= h / 2; break;
	case VCENTER | HCENTER: x -= w / 2; y -= h / 2; break;
	case VCENTER | RIGHT:   x -= w;    y -= h / 2; break;
	case BOTTOM | LEFT:                y -= h;     break;
	case BOTTOM | HCENTER:  x -= w / 2; y -= h;     break;
	case BOTTOM | RIGHT:    x -= w;    y -= h;     break;
	}

#if 0
	wchar_t* sn = utf8_to_utf16(getStringName());
	FontFamily  fontFamily(sn);
	delete sn;
	Font        font(&fontFamily, getStringSize(), FontStyleRegular, UnitPixel);
#else
	FontFamily ff;
	FontStyle fs;
	checkFontFamily(getStringName(), &ff, fs);
	Font        font(&ff, getStringSize(), fs, UnitPixel);
#endif
	PointF      pointF(x, y);
	float r, g, b, a;
	getStringRGBA(r, g, b, a);
	SolidBrush  solidBrush(Color(a * 0xFF, r * 0xFF, g * 0xFF, b * 0xFF));

	wchar_t* wStr = utf8_to_utf16(szText);
	graphics->DrawString(wStr, -1, &font, pointF, &solidBrush);
	delete wStr;
}

void iGraphics::drawString(Graphics* graphics, float x, float y, const char* szFormat, ...)
{
	char szText[512];
	va_start_end(szFormat, szText);

#if 0
	wchar_t* sn = utf8_to_utf16(getStringName());
	FontFamily  fontFamily(sn);
	delete sn;
	Font        font(&fontFamily, getStringSize(), FontStyleRegular, UnitPixel);
#else
	FontFamily ff;
	FontStyle fs;
	checkFontFamily(getStringName(), &ff, fs);
	Font        font(&ff, getStringSize(), fs, UnitPixel);
#endif
	PointF      pointF(x, y);
	float r, g, b, a;
	getStringRGBA(r, g, b, a);
	SolidBrush  solidBrush(Color(a * 0xFF, r * 0xFF, g * 0xFF, b * 0xFF));

	wchar_t* wStr = utf8_to_utf16(szText);
	graphics->DrawString(wStr, -1, &font, pointF, &solidBrush);
	delete wStr;
}
