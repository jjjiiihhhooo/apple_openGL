#pragma once

struct iString
{
    // Default
    iString();
    iString(const iString& s);

    // Custome
    iString(const char* s);
    virtual ~iString();

    char* s;

    iString operator +(const char* s);
    iString& operator+=(const char* s);
    iString& operator+=(const iString& s);

    bool operator==(const iString& s);
    bool operator==(const char* s);

    iString& operator=(const iString& s);
    iString& operator=(const char* s);

    static char** split(int& lineNum, const char* s, char d = '\n');
    static char** splitWidth(int& lineNum, const char* s, int width);
    static void free(char** line, int lineNum);

    static bool isUTF8(const char* str);

    bool trim();
    char* subString(int from, int to);
    char* copy();
    static char* copy(const char* s);
};

