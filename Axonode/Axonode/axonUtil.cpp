#include "stdafx.h"
#include "axonUtil.h"
#include <string>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#pragma warning(disable: 4996)

#pragma region RetrieveOS
int getOS()
{
	/**
	* OS VERSIONS AS FOLLOWS:
	* 0 - Windows 2000
	* 1 - Windows XP
	* 2 - Widnows XP Pro x64 / Server 2003(R2)
	* 3 - Windows Vista / Server 2008
	* 4 - Windows 7 / Server 2008 R2
	* 5 - Windows 8 / Server 2012
	* 6 - Windows 8.1 / Server 2012 R2
	* 7 - Windows 10 / Server 2016
	*/

	int os = NULL;

	OSVERSIONINFO info;
	ZeroMemory(&info, sizeof(OSVERSIONINFO));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&info);

	switch (info.dwMajorVersion)
	{
	case 5:
		if (info.dwMinorVersion == 0)
			os = 0;
		else if (info.dwMinorVersion == 1)
			os = 1;
		else if (info.dwMinorVersion == 2)
			os = 2;
		break;
	case 6:
		if (info.dwMinorVersion == 0)
			os = 3;
		else if (info.dwMinorVersion == 1)
			os = 4;
		else if (info.dwMinorVersion == 2)
			os = 5;
		else if (info.dwMinorVersion == 3)
			os = 6;
		break;
	case 10:
		if (info.dwMinorVersion == 0)
			os = 7;
		break;
	default:
		os = 4; //Set the deafult to most used OS, Windows 7.
		break;
	}

	return os;
}
#pragma endregion

#pragma region winTitle

char* GetActiveWindowTitle()
{
	HWND hWnd = GetForegroundWindow();
	int nLen = GetWindowTextLength(hWnd) + 1;
	char *szTitle = (char*)malloc(nLen + 1);
	GetWindowTextA(hWnd, szTitle, nLen);

	return szTitle;

	free(szTitle);
}

#pragma endregion

#pragma region SS

void dumpSS()
{
	HDC hScreen = GetDC(NULL);
	HDC hDC = CreateCompatibleDC(hScreen);
	int width = GetDeviceCaps(hDC, HORZRES);
	int height = GetDeviceCaps(hDC, VERTRES);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL bRet = BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hBitmap);
	CloseClipboard();

	SelectObject(hDC, old_obj);
	DeleteDC(hDC);
	ReleaseDC(NULL, hScreen);
	DeleteObject(hBitmap);
}

#pragma endregion