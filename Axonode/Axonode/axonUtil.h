#include <string>
#include <windows.h>
#pragma once
using namespace std;
extern int getOS();
char* getWindowTitle();
string getPath();
wchar_t* getWChar(string in);
void saveBMP(HBITMAP bitmap, HDC hDC, LPTSTR filename);
void getScreenShot();
BOOL getStartup(PCWSTR appName);
void addStartup();