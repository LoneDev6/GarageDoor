/*
LoneDev super professional License


Copyright (c) 2020 LoneDev


Permissions:
- You can edit this source and use it in any free project you want

Limitations:
- You cannot use this source or edited versions in commercial projects
- You cannot use this code in projects that earn using advertisements or that take donations
- You cannot resell this code
- You cannot state that this is your code
- You must include LoneDev in the credits of your project
- You must share the edited source code
- You must include this license file
*/

#pragma once

#include <windows.h>
#include "MinHook.h"

typedef BOOL(__stdcall* original_TextOutA) (HDC hdc, int x, int y, LPCSTR lpString, int length_lpString);

template <typename T> inline MH_STATUS MH_CreateHookApiEx(LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, T** ppOriginal)
{
	return MH_CreateHookApi(
		pszModule, pszProcName, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
}