#include "iString.h"

#include <stdio.h>
#include <string.h>

iString::iString()
{
	//printf("iString()\n");
	s = NULL;
}

iString::iString(const iString& s)
{
	//printf("iString(const iString& s)\n");
	int len = strlen(s.s);
	char* t = new char[len + 1];
	strcpy(t, s.s);
	this->s = t;
}

iString::iString(const char* s)
{
	//printf("iString(const char* s)\n");
	int len = strlen(s);
	char* t = new char[len + 1];
	strcpy(t, s);
	this->s = t;
}

iString::~iString()
{
	//printf("~iString %s\n", s);
	if (s)
		delete s;
}

iString iString::operator +(const char* s)
{
	int len0 = strlen(this->s);
	int len1 = strlen(s);

	char* t = new char[len0 + len1 + 1];
	strcpy(t, this->s);
	strcpy(&t[len0], s);

	iString r(t);
	return r;
}

iString& iString::operator +=(const char* s)
{
	int len0 = strlen(this->s);
	int len1 = strlen(s);

	char* t = new char[len0 + len1 + 1];
	strcpy(t, this->s);
	strcpy(&t[len0], s);

	if (this->s)
		delete this->s;
	this->s = t;

	return *this;
}

iString& iString::operator+=(const iString& s)
{
	int len0 = strlen(this->s);
	int len1 = strlen(s.s);

	char* t = new char[len0 + len1 + 1];
	strcpy(t, this->s);
	strcpy(&t[len0], s.s);

	if (this->s)
		delete this->s;
	this->s = t;

	return *this;
}

bool iString::operator==(const iString& s)
{
	if (strcmp(this->s, s.s))
		return false;
	return true;
}

bool iString::operator==(const char* s)
{
	if (strcmp(this->s, s))
		return false;
	return true;
}

iString& iString::operator=(const iString& s)
{
	int len = strlen(s.s);
	char* t = new char[len + 1];
	strcpy(t, s.s);

	if (this->s)
		delete this->s;
	this->s = t;
	return *this;
}

iString& iString::operator=(const char* s)
{
	int len = strlen(s);
	char* t = new char[len + 1];
	strcpy(t, s);

	if (this->s)
		delete this->s;
	this->s = t;
	return *this;
}

char** iString::split(int& lineNum, const char* s, char d)
{
	lineNum = 1;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == d)
			lineNum++;
	}

	char** line = new char* [lineNum];
	lineNum = 0;
	int i, off;
	for (i = 0, off = 0; s[i]; i++)
	{
		if (s[i] == d)
		{
			// off ~ i-1
			int len = i - off;// i - 1 - off + 1;
			char* t = new char[len + 1];
			memcpy(t, &s[off], sizeof(char) * len);
			t[len] = 0;

			line[lineNum] = t;
			lineNum++;

			off = i + 1;
		}
	}
	//int len = strlen(s) - off;
	int len = i - off;// i - 1 - off + 1;
	if (len)
	{
		char* t = new char[len + 1];
		memcpy(t, &s[off], sizeof(char) * len);
		t[len] = 0;

		line[lineNum] = t;
		lineNum++;
	}

	return line;
}
#include "iStd.h"
char** iString::splitWidth(int& lineNum, const char* s, int width)
{
	char t[512];
	int off = 0;
	iArray* array = new iArray();

	int i, j;
	for (i = 0, j = 0; s[i]; )
	{
		int cpy = isUTF8(&s[i]) ? 3 : 1;

		//t[j] = s[i];
		//t[j + 1] = 0;
		memcpy(&t[j], &s[i], sizeof(char) * cpy);
		t[j + cpy] = 0;

		if (rectOfString(t).size.width > width)
		{
			int len = i - off;// off ~ i - 1
			char* str = new char[len + 1];
			memcpy(str, &s[off], sizeof(char) * len);
			str[len] = 0;

			off = i;
			i -= cpy;// <<< 
			j = -cpy;// j = -1 => j++

			array->add(str);
		}

		i += cpy;// i++;
		j += cpy;// j++;
	}
#if 1// off ~ i - 1
	int len = i - off;
	char* str = new char[len + 1];
	memcpy(str, &s[off], sizeof(char) * len);
	str[len] = 0;

	//off = i + 1;
	//j = -1;

	array->add(str);
#endif

	char** line = new char* [array->count];
	for (int i = 0; i < array->count; i++)
		line[i] = (char*)array->at(i);
	lineNum = array->count;
	delete array;

	return line;
}


void iString::free(char** line, int lineNum)
{
	for (int i = 0; i < lineNum; i++)
		delete line[i];
	delete line;
}

bool iString::isUTF8(const char* str)
{
	return  (str[0] & 0xF0) == 0xE0 &&
		(str[1] & 0xC0) == 0x80 &&
		(str[2] & 0xC0) == 0x80;
}


bool iString::trim() { return true; }
char* iString::subString(int from, int to) { return NULL; }
char* iString::copy()
{
	int len = strlen(s);
	char* t = new char[len + 1];
	strcpy(t, s);
	return t;
}
char* iString::copy(const char* s)
{
	int len = strlen(s);
	char* t = new char[len + 1];
	strcpy(t, s);
	return t;
}
