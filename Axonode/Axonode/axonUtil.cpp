#include "stdafx.h"
#include "axonUtil.h"
#include <windows.h>
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