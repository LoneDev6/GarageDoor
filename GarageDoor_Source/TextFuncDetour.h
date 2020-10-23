#pragma once

#include <windows.h>
#include "MinHook.h"

typedef BOOL(__stdcall* original_TextOutA) (HDC hdc, int x, int y, LPCSTR lpString, int length_lpString);

template <typename T> inline MH_STATUS MH_CreateHookApiEx(LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, T** ppOriginal)
{
	return MH_CreateHookApi(
		pszModule, pszProcName, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
}