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

#include <thread>
#include <cstdio>
#include <iostream>

#include "SimpleHook.h"
#include "Translator.h"
#include "Utils.h"

// Configuration from GarageDoor.ini
bool g_translatorMode = false;
bool g_debugConsole = false;

void LoadConfig()
{
	char result[256] = "";
	DWORD success = GetPrivateProfileStringA("Settings", "translator_mode", "0", result, sizeof(result), ".\\GarageDoor.ini");
	g_translatorMode = (strcmp(result, "1") == 0 || strcmp(result, "true") == 0);
	
	success = GetPrivateProfileStringA("Settings", "debug_console", "0", result, sizeof(result), ".\\GarageDoor.ini");
	g_debugConsole = (strcmp(result, "1") == 0 || strcmp(result, "true") == 0);
	
	if (g_debugConsole)
	{
		std::cout << "[CONFIG] translator_mode=" << (g_translatorMode ? "1" : "0") << "\n";
		std::cout << "[CONFIG] debug_console=" << (g_debugConsole ? "1" : "0") << "\n";
	}
}

// Typedef for the original function
typedef BOOL(__stdcall* PFN_TextOutA) (HDC hdc, int x, int y, LPCSTR lpString, int length_lpString);

// Pointer to the original TextOutA function (before hook)
PFN_TextOutA TextOutA_Original = NULL;
HookInfo hookInfo = {0};

// Buffer for trampoline code - allocated dynamically
LPVOID trampolineBuffer = NULL;

Translator translator;

int _stdcall TextOutA_Detour(HDC hdc, int x, int y, LPCSTR lpString, int length_lpString)
{
	// if it's an ignorable text (in this case a text with only numbers)
	if (!translator.isIgnorable(lpString))
	{
		// If I've never seen this text before
		if (!translator.hasTranslation(lpString))
		{
			if (g_translatorMode)
			{
				std::cout << "[!] Unknown text found: :" << lpString << "\n";
				translator.saveUnknownText(lpString, "NOT_TRANSLATED_TEXT");
			}
			return TextOutA_Original(hdc, x, y, lpString, length_lpString);
		}
		else // I know about this text
		{
			std::string translated = translator.getTranslation(lpString);

			// I already have this text saved but I don't have a translation
			if (translated.compare("NOT_TRANSLATED_TEXT") == 0)
			{
				if (g_debugConsole)
				{
					std::cout << "[NO] Message not translated: " << lpString << "\n";
				}
				// Use original text - NOT translated version
				return TextOutA_Original(hdc, x, y, lpString, length_lpString);
			}
			else // I have a translation for this text
			{
				if (g_debugConsole)
				{
					std::cout << "[OK] Translated message: " << lpString << " -> " << translated.c_str() << "\n";
				}
				// Use translated text
				return TextOutA_Original(hdc, x, y, translated.c_str(), translated.length());
			}
		}
	}
	else // Ignore the text and pass the same value to the original function
	{
		if (g_debugConsole)
		{
			std::cout << "[-] Ignored text: :" << lpString << "\n";
		}
		return TextOutA_Original(hdc, x, y, lpString, length_lpString);
	}
}

// Hook TextOutA function
int Hook_TextOutA()
{
	FILE* log = fopen(".\\hook_log.txt", "w");
	if (!log)
	{
		std::cout << "[ERROR] Could not open hook_log.txt for writing\n";
		return 1;
	}
	
	fprintf(log, "Getting TextOutA address from GDI32.dll\n");
	fflush(log);
	std::cout << "[DEBUG] Getting TextOutA address from GDI32.dll\n";
	
	HMODULE hGdi32 = GetModuleHandleA("GDI32.dll");
	if (!hGdi32)
	{
		fprintf(log, "[ERROR] Could not get GDI32.dll handle\n");
		std::cout << "[ERROR] Could not get GDI32.dll handle\n";
		fclose(log);
		return 1;
	}
	
	LPVOID pTextOutA_Addr = (LPVOID)GetProcAddress(hGdi32, "TextOutA");
	if (!pTextOutA_Addr)
	{
		fprintf(log, "[ERROR] Could not get TextOutA address\n");
		std::cout << "[ERROR] Could not get TextOutA address\n";
		fclose(log);
		return 1;
	}
	
	fprintf(log, "TextOutA found at: 0x%p\n", pTextOutA_Addr);
	std::cout << "[DEBUG] TextOutA found at: 0x" << std::hex << (unsigned long)pTextOutA_Addr << std::dec << "\n";
	fflush(log);
	
	// Allocate executable memory for trampoline (32 bytes to be safe)
	trampolineBuffer = VirtualAlloc(NULL, 32, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!trampolineBuffer)
	{
		fprintf(log, "[ERROR] Could not allocate trampoline memory\n");
		std::cout << "[ERROR] Could not allocate trampoline memory\n";
		fclose(log);
		return 1;
	}
	
	fprintf(log, "Trampoline buffer allocated at: 0x%p\n", trampolineBuffer);
	std::cout << "[DEBUG] Trampoline buffer allocated at: 0x" << std::hex << (unsigned long)trampolineBuffer << std::dec << "\n";
	fflush(log);
	
	// Copy first 5 bytes (we'll overwrite them with JMP in the original)
	unsigned char* pTramp = (unsigned char*)trampolineBuffer;
	memcpy(pTramp, pTextOutA_Addr, 5);
	
	// Add JMP to skip past the original JMP we're about to install
	// Jump to (original + 5)
	// Use UINT_PTR for proper 32/64-bit compatibility
	pTramp[5] = 0xE9; // JMP opcode
	UINT_PTR trampOffset = ((UINT_PTR)pTextOutA_Addr + 5) - ((UINT_PTR)pTramp + 5 + 5);
	// For x86/x64, we only encode the low 32 bits (relative offset is 32-bit signed)
	DWORD relativeOffset = (DWORD)trampOffset;
	memcpy(&pTramp[6], &relativeOffset, 4);
	
	// Flush instruction cache
	FlushInstructionCache(GetCurrentProcess(), trampolineBuffer, 32);
	
	// Now point TextOutA_Original to our trampoline
	TextOutA_Original = (PFN_TextOutA)trampolineBuffer;
	
	fprintf(log, "Trampoline created at: 0x%p\n", trampolineBuffer);
	std::cout << "[DEBUG] Trampoline created\n";
	fflush(log);
	
	// Now install the hook (this patches the original function with JMP to detour)
	if (!InstallHook(pTextOutA_Addr, (LPVOID)&TextOutA_Detour, hookInfo))
	{
		fprintf(log, "[ERROR] InstallHook failed\n");
		std::cout << "[ERROR] InstallHook failed\n";
		fclose(log);
		return 1;
	}
	
	fprintf(log, "Hook installed successfully\n");
	std::cout << "[DEBUG] Hook installed successfully\n";
	fflush(log);
	fclose(log);
	
	return 0;
}

// Main function of the injected dll
static unsigned long __stdcall CheatMain(void *arg)
{
	// Load configuration first
	LoadConfig();
	
	// Show console
	if (g_debugConsole)
	{
		AllocConsole();
		ShowWindow(GetConsoleWindow(), SW_NORMAL);
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitleA("Garage Dev Console - by LoneDev (github.com/LoneDev6)");

		::SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		::ShowWindow(GetConsoleWindow(), SW_NORMAL);
		
		std::cout << "[DEBUG] CheatMain thread started\n";
	}

	std::cout << "[DEBUG] Creating Translator instance...\n";
	translator = Translator();
	std::cout << "[DEBUG] Translator created successfully\n";
	
	std::cout << "[DEBUG] Installing TextOutA hook...\n";
	int hookResult = Hook_TextOutA();
	std::cout << "[DEBUG] Hook_TextOutA returned: " << hookResult << "\n";
	
	if (hookResult != 0)
	{
		std::cout << "[ERROR] Hook installation failed!\n";
	}
	else
	{
		std::cout << "[OK] Hook installed successfully, entering main loop\n";
	}

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}

int __stdcall DllMain(const HMODULE self, const unsigned long reason_for_call, void *reserved)
{
	if (reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(self);
		CreateThread(nullptr, 0, &CheatMain, nullptr, 0, nullptr);
		return 1;
	}

	return 0;
}
