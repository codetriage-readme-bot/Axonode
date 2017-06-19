#include <string>
#include <windows.h>
#pragma once

std::string getOS();
char* getWindowTitle();
std::string getPath();
wchar_t* getWChar(std::string in);
void saveBMP(HBITMAP bitmap, HDC hDC, LPTSTR filename);
void getScreenShot();
BOOL getStartup(PCWSTR appName);
void addStartup();
const bool ProtectProcess();