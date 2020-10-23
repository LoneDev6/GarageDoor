#pragma once

#include <thread>

#include "MinHook.h"
#pragma comment(lib, "libMinHook.lib")

#include "Translator.h"
#include "TextFuncDetour.h"
#include "Utils.h"

//Translator logic
Translator translator;
//Pointer used to call original TextOutA.
original_TextOutA pTextOutA = NULL;

//TextOutA detour that proxies all on screen messages.
int _stdcall TextOutA_Detour(HDC hdc, int x, int y, LPCSTR lpString, int length_lpString)
{
	//if it's an ignorable text (in this case a text with only numbers)
	if (!translator.isIgnorable(lpString))
	{
		// If I've never seen this text before
		if (!translator.hasTranslation(lpString))
		{
			std::cout << "[!] Unknown text found: :" << lpString << "\n";
			translator.saveUnknownText(lpString, "NOT_TRANSLATED_TEXT");
			return pTextOutA(hdc, x, y, lpString, length_lpString);
		}
		else // I know about this text
		{
			std::string translated = translator.getTranslation(lpString);

			// I already have this text saved but I don't have a translation
			if (translated.compare("NOT_TRANSLATED_TEXT") == 0)
			{
				translated = lpString;
				std::cout << "[NO] Message not translated: " << lpString << " -> " << translated.c_str() << "\n";
			}
			else // I have a translation for this text
			{
				std::cout << "[OK] Translated message: " << lpString << " -> " << translated.c_str() << "\n";
			}
			// Pass the edited value to the original function
			return pTextOutA(hdc, x, y, translated.c_str(), translated.length());
		}
	}
	else // Ignore the text and pass the same value to the original function
	{
		std::cout << "[-] Ignored text: :" << lpString << "\n";
		return pTextOutA(hdc, x, y, lpString, length_lpString);
	}
}

// Hook original TextOutA function from GDI32.dll in order to call my detour.
// Macromedia Director 6 uses this native Windows libs function to draw text on screen.
int Hook_TextOutA()
{
	MH_STATUS state = MH_CreateHookApiEx(L"GDI32.dll", "TextOutA", &TextOutA_Detour, &pTextOutA);
	std::cout << "Hook text function result: " << as_integer(state) << "\n\n";
	if (state != MH_OK)
		std::cout << "Error hooking text function" << "\n\n";
	
	if (MH_EnableHook(&TextOutA) != MH_OK)
		return 1;
	return 0;
}

// Main function of the injected dll
static unsigned long __stdcall CheatMain(void *arg)
{
	AllocConsole();
	ShowWindow(GetConsoleWindow(), SW_NORMAL);
	_iobuf *data;
	freopen_s(&data, "CONIN$", "r", stdin);
	freopen_s(&data, "CONOUT$", "w", stdout);
	SetConsoleTitleA("Garage Dev Console - by LoneDev (github.com/LoneDev6)");

	::SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::ShowWindow(GetConsoleWindow(), SW_NORMAL);

	const auto window_handle = find_main_window();

	const uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
	if (!base)
		return 1;
	std::cout << "Game base address: 0x" << std::hex << std::uppercase << base << "\n";

	// Initialize MinHook.
	if (MH_Initialize() != MH_OK)
	{
		std::cout << "MH_Initialize() != MH_OK" << "\n\n";
		return 1;
	}

	translator = Translator();
	Hook_TextOutA();

	//main loop
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
