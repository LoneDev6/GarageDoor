/*
Garage English Patch - Launcher & Injector (C version for XP compatibility)
*/

#define _WIN32_WINNT _WIN32_WINNT_WINXP

#include <windows.h>
#include <tlhelp32.h>
#include <shellapi.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

BOOL g_debugConsoleEnabled = FALSE;
BOOL g_lowResolutionMode = TRUE;

// Forward declarations
DWORD FindProcessByName(const char* processName);
void DebugPrintf(const char *format, ...);

// Helper function to pause or exit, wait for game to close, and restore resolution
void PauseOrExit(HANDLE hGameProcess)
{
	// Wait for Garage.exe to close if a handle was provided
	if (hGameProcess != NULL)
	{
		DebugPrintf("[INFO] Waiting for Garage.exe to close before cleanup...\n");
		WaitForSingleObject(hGameProcess, INFINITE);
		CloseHandle(hGameProcess);
	}
	else
	{
		// Fallback: search by name if no handle provided
		DWORD gameCheckPid = FindProcessByName("Garage.exe");
		if (gameCheckPid != 0)
		{
			DebugPrintf("[INFO] Waiting for Garage.exe to close before cleanup...\n");
			HANDLE hGameProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, gameCheckPid);
			if (hGameProcess != NULL)
			{
				WaitForSingleObject(hGameProcess, INFINITE);
				CloseHandle(hGameProcess);
			}
		}
	}
	
	// Pause or exit based on debug console setting
	if (g_debugConsoleEnabled)
		system("pause");
	else
		ExitProcess(1);
}

// Load configuration settings from GarageDoor.ini
void LoadConfigSettings()
{
	char result[256] = "";
	
	// Load debug console setting
	char debugResult[256] = "";
	DWORD success = GetPrivateProfileStringA("Settings", "debug_console", "0", debugResult, sizeof(debugResult), ".\\GarageDoor.ini");
	g_debugConsoleEnabled = (strcmp(debugResult, "1") == 0 || strcmp(debugResult, "true") == 0);
	
	// Load low resolution mode setting
	char lowResResult[256] = "";
	success = GetPrivateProfileStringA("Settings", "low_resolution_mode", "1", lowResResult, sizeof(lowResResult), ".\\GarageDoor.ini");
	g_lowResolutionMode = (strcmp(lowResResult, "1") == 0 || strcmp(lowResResult, "true") == 0);
	
	if (g_debugConsoleEnabled)
	{
		printf("[CONFIG] debug_console: %s\n", g_debugConsoleEnabled ? "enabled" : "disabled");
		printf("[CONFIG] low_resolution_mode: %s\n", g_lowResolutionMode ? "enabled" : "disabled");
	}
}

void DebugPrintf(const char *format, ...)
{
	if (!g_debugConsoleEnabled)
		return;
	
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

BOOL IsWindowsXP()
{
	OSVERSIONINFOA osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);

	if (GetVersionExA(&osvi))
	{
		// Windows XP is version 5.1
		return (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1);
	}
	return FALSE;
}

// Set debug privilege for process injection
BOOL SetPrivilege(HANDLE hToken, LPCTSTR Privilege, BOOL bEnablePrivilege)
{
	LUID luid;
	BOOL bRet = FALSE;

	if (LookupPrivilegeValueA(NULL, Privilege, &luid))
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Luid = luid;
		tp.Privileges[0].Attributes = (bEnablePrivilege) ? SE_PRIVILEGE_ENABLED : 0;

		if (AdjustTokenPrivileges(hToken, FALSE, &tp, (DWORD)NULL, (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
			bRet = (GetLastError() == ERROR_SUCCESS);
	}
	return bRet;
}

void ForceResolution640x480(const char *exePath)
{
	  // Tested on Windows 11, seems to work fine
		if(!IsWindowsXP())
		{
			HKEY hKey;
			const char *subKey = "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers";
			if (RegCreateKeyExA(HKEY_CURRENT_USER, subKey, 0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS)
			{
				const char *flags = "640X480 16BITCOLOR RUNASADMIN";
				RegSetValueExA(hKey, exePath, 0, REG_SZ, (const BYTE *)flags, (DWORD)(strlen(flags) + 1));
				RegCloseKey(hKey);
				printf("[OK] Compatibility flags applied to: %s\n", exePath);
			}
			return;
		}

		// Force resolution change for Windows XP
    DEVMODEA devMode;
    ZeroMemory(&devMode, sizeof(devMode));
    devMode.dmSize = sizeof(devMode);
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
    devMode.dmPelsWidth = 640;
    devMode.dmPelsHeight = 480;
    devMode.dmBitsPerPel = 16; // Seems to be ignored for some reason
    
    LONG result = ChangeDisplaySettingsA(&devMode, CDS_FULLSCREEN);
    
    if (result == DISP_CHANGE_SUCCESSFUL)
    {
			printf("[OK] Resolution forced to 640x480\n");
    }
    else
    {
			fprintf(stderr, "[ERROR] Failed to change resolution: %ld\n", result);
    }
}

int LaunchGameWithLocaleEmulator(const char *basePath)
{
	char leprocPath[MAX_PATH];
	char garageExePath[MAX_PATH];
	char params[1024];
	const char *GUID = "a3672ec3-6336-4c41-8141-dfccf238fbe8";

	// Build paths
	sprintf(leprocPath, "%sLocaleEmulator\\LEProc.exe", basePath);
	sprintf(garageExePath, "%sGarage.exe", basePath);
	sprintf(params, "-runas \"%s\" \"%s\"", GUID, garageExePath);

	DebugPrintf("[LAUNCHER] Starting LocaleEmulator...\n");
	DebugPrintf("[LAUNCHER] LEProc path: %s\n", leprocPath);
	DebugPrintf("[LAUNCHER] Garage path: %s\n", garageExePath);

	if(g_lowResolutionMode)
		ForceResolution640x480(garageExePath);
	else
		DebugPrintf("[INFO] Low resolution mode disabled - using native resolution\n");

	// Try ShellExecute
	HINSTANCE shellexec = ShellExecuteA(NULL, "runas", leprocPath, params, basePath, SW_SHOWNORMAL);
	if ((INT_PTR)shellexec <= 32)
	{
		DebugPrintf("[LAUNCHER] ShellExecute failed, trying CreateProcess...\n");
		
		// Fallback CreateProcess
		char cmdline[2048];
		if(g_debugConsoleEnabled)
			sprintf(cmdline, "\"%s\" %s", leprocPath, params);

		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (!CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, basePath, &si, &pi))
		{
			if(g_debugConsoleEnabled)
				fprintf(stderr, "[ERROR] CreateProcess failed\n");
			return 0;
		}
		
		if (pi.hProcess)
			CloseHandle(pi.hProcess);
		if (pi.hThread)
			CloseHandle(pi.hThread);
	}

	DebugPrintf("[OK] LocaleEmulator launched!\n");
	return 1;
}

DWORD FindProcessByName(const char* processName)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "Error: CreateToolhelp32Snapshot failed\n");
		return 0;
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "Error: Process32First failed\n");
		CloseHandle(hProcessSnap);
		return 0;
	}

	DWORD pidTarget = 0;
	do
	{
		if (strcmp(pe32.szExeFile, processName) == 0)
		{
			pidTarget = pe32.th32ProcessID;
			DebugPrintf("[OK] Process found: %s (PID: %lu)\n", processName, pidTarget);
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return pidTarget;
}

int InjectDLL(DWORD pid, const char* dllPath)
{
	// Verify file exists
	HANDLE hFile = CreateFileA(dllPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "[ERROR] File not found: %s\n", dllPath);
		return 0;
	}
	CloseHandle(hFile);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == NULL)
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "[ERROR] Cannot open process (PID: %lu)\n", pid);
		return 0;
	}

	// Allocate memory in target process for DLL path
	size_t dllPathLen = strlen(dllPath) + 1;
	LPVOID pDllPath = VirtualAllocEx(hProcess, NULL, dllPathLen, MEM_COMMIT, PAGE_READWRITE);
	if (pDllPath == NULL)
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "[ERROR] VirtualAllocEx failed\n");
		CloseHandle(hProcess);
		return 0;
	}

	// Write DLL path to target process memory
	if (!WriteProcessMemory(hProcess, pDllPath, (LPVOID)dllPath, dllPathLen, NULL))
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "[ERROR] WriteProcessMemory failed\n");
		VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return 0;
	}

	// Get LoadLibraryA address
	HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
	LPVOID pLoadLibraryA = (LPVOID)GetProcAddress(hKernel32, "LoadLibraryA");
	if (pLoadLibraryA == NULL)
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "[ERROR] Cannot find LoadLibraryA\n");
		VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return 0;
	}

	// Create remote thread
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibraryA, pDllPath, 0, NULL);
	if (hThread == NULL)
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "[ERROR] CreateRemoteThread failed\n");
		VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return 0;
	}

	// Wait for thread to finish
	WaitForSingleObject(hThread, INFINITE);

	// Get thread exit code
	DWORD threadExitCode = 0;
	GetExitCodeThread(hThread, &threadExitCode);
	
	if (threadExitCode == 0)
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "[ERROR] LoadLibraryA returned NULL - DLL not loaded\n");
		VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return 0;
	}
	
	DebugPrintf("[INFO] LoadLibraryA returned: 0x%lx\n", threadExitCode);
	DebugPrintf("[OK] DLL injected: %s\n", dllPath);
	
	// Cleanup
	VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
	CloseHandle(hThread);
	CloseHandle(hProcess);

	return 1;
}

// Find TextTranslator.dll to inject (returns 1 if found, 0 if not, -1 if disabled)
int FindTextTranslatorDLL(char *outPath)
{
	char exePath[MAX_PATH];
	char exeDir[MAX_PATH];
	
	// Get the path of the current executable (GarageDoor.exe)
	GetModuleFileNameA(NULL, exePath, MAX_PATH);
	
	DebugPrintf("[DEBUG] Full executable path: %s\n", exePath);
	
	// Copy to exeDir and remove the filename to get just the directory
	strncpy(exeDir, exePath, MAX_PATH - 1);
	exeDir[MAX_PATH - 1] = '\0';
	
	char *lastBackslash = strrchr(exeDir, '\\');
	if (lastBackslash)
	{
		*lastBackslash = '\0';
	}

	printf("[DEBUG] Executable directory: %s\n", exeDir);

	char translatorPath[MAX_PATH];
	sprintf(translatorPath, "%s\\TextTranslator.dll", exeDir);
	
	DebugPrintf("[DEBUG] Looking for DLL at: %s\n", translatorPath);
	
	// Check if TextTranslator.dll exists
	HANDLE hFile = CreateFileA(translatorPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		strncpy(outPath, translatorPath, MAX_PATH - 1);
		outPath[MAX_PATH - 1] = '\0';
		DebugPrintf("[FOUND] %s\n", outPath);
		return 1;
	}
	else
	{
		DWORD dwError = GetLastError();
		fprintf(stderr, "[WARNING] TextTranslator.dll not found at: %s (Error: %lu)\n", translatorPath, dwError);
		return 0; // Return 0 to indicate file not found
	}
}

// Check if Japanese locale is properly configured for display
BOOL CanDisplayJapanese()
{
	// Try to detect if output device can handle Japanese
	// This is a fallback check - on XP with proper config, this should work
	// We verify by trying to set console output code page to Shift-JIS (932)
	UINT currentCodePage = GetConsoleCP();
	UINT currentOutputCodePage = GetConsoleOutputCP();
	
	DebugPrintf("[DEBUG] Current console input code page: %u\n", currentCodePage);
	DebugPrintf("[DEBUG] Current console output code page: %u\n", currentOutputCodePage);
	
	// Shift-JIS is code page 932
	// If neither is 932, Japanese might not display correctly
	if (currentCodePage != 932 && currentOutputCodePage != 932)
	{
		DebugPrintf("[WARNING] Console code pages are not set to Shift-JIS (932)\n");
		DebugPrintf("[WARNING] Attempting to set output code page to 932...\n");
		
		if (!SetConsoleOutputCP(932))
		{
			DebugPrintf("[ERROR] Could not set console output code page to 932\n");
			return FALSE;
		}
	}
	
	return TRUE;
}

int main()
{
	// Load configuration settings first
	LoadConfigSettings();
	
	// Show console only if debug_console is enabled in GarageDoor.ini
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	SetConsoleTitleA("Garage Patch - Injector Debug Console");
	
	// Minimize console to taskbar instead of showing it
	ShowWindow(GetConsoleWindow(), SW_NORMAL);
	
	DebugPrintf("\n========================================\n");
	DebugPrintf("Garage English Patch - Launcher & Injector\n");
	DebugPrintf("========================================\n\n");

	if (IsWindowsXP())
	{
		DebugPrintf("[DETECTED] Windows XP detected!\n");
		
		// Check if console can display Japanese characters
		if (!CanDisplayJapanese())
		{
			MessageBoxA(NULL,
				"Cannot display Japanese characters!\n\n"
				"Please follow these steps:\n"
				"1. Go to 'Control Panel' > 'Regional and Language Options'\n"
				"2. Go to 'Languages' tab\n"
				"3. Check 'Install files for East Asian languages'\n"
				"4. Insert a Windows XP installation CD (a Japanese CD might be required)\n"
				"5. Finish the installation and restart your computer\n"
				"6. Go to 'Advanced'\n"
				"7. Set 'Language for non-Unicode programs' to 'Japanese'\n"
				"8. Restart your computer",
				"Garage Patch - Locale Error",
				MB_ICONERROR | MB_OK);
			return 1;
		}
		
		DebugPrintf("[OK] Japanese locale configuration verified!\n");
		DebugPrintf("[INFO] Launching Garage.exe and injecting DLL directly (no LEProc)...\n\n");

		// Get base directory
		char basePath[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, basePath);
		size_t len = strlen(basePath);
		if (basePath[len - 1] != '\\')
			strcat(basePath, "\\");

		// Launch Garage directly
		char garageExePath[MAX_PATH];
		sprintf(garageExePath, "%sGarage.exe", basePath);

		DebugPrintf("[LAUNCHER] Launching Garage.exe directly...\n");
		DebugPrintf("[LAUNCHER] Path: %s\n", garageExePath);

		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (!CreateProcessA(garageExePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, basePath, &si, &pi))
		{
			MessageBoxA(NULL,
				"Failed to launch Garage.exe!\n"
				"Please ensure the game is installed correctly.",
				"Garage Patch - Launch Error",
				MB_ICONERROR | MB_OK);
			return 1;
		}
		
		if(g_lowResolutionMode)
			ForceResolution640x480(garageExePath);
		else
			DebugPrintf("[INFO] Low resolution mode disabled - using native resolution\n");

		DebugPrintf("[OK] Garage.exe launched (suspended)\n");
		Sleep(1000);

		// Now inject DLL into the suspended process
		DebugPrintf("\n[INJECTION] Injecting TextTranslator.dll into Garage.exe (PID: %lu)...\n", pi.dwProcessId);

		// Find and inject DLL
		char dllPath[MAX_PATH];
		int findResult = FindTextTranslatorDLL(dllPath);
		
		if (findResult == -1)
		{
			// DLL injection disabled - just resume and run game
			DebugPrintf("\n[RESUMING] Resuming Garage.exe (DLL injection disabled)...\n");
			ResumeThread(pi.hThread);
			CloseHandle(pi.hThread);

			DebugPrintf("\n========================================\n");
			DebugPrintf("[RESULT] Done (no DLL injected)\n");
			DebugPrintf("========================================\n\n");
			PauseOrExit(pi.hProcess);
			return 0;
		}
		else if (findResult == 1)
		{
			DebugPrintf("\n[STARTING INJECTION]\n");
			if (InjectDLL(pi.dwProcessId, dllPath))
			{
				DebugPrintf("\n[RESUMING] Resuming Garage.exe...\n");
				ResumeThread(pi.hThread);
				CloseHandle(pi.hThread);
				DebugPrintf("\n========================================\n");
				DebugPrintf("[RESULT] Done - DLL injected successfully\n");
				DebugPrintf("========================================\n\n");
				PauseOrExit(pi.hProcess);
				return 0;
			}
			else
			{
				if(g_debugConsoleEnabled)
					fprintf(stderr, "[FAILED] Injection failed: %s\n", dllPath);
				TerminateProcess(pi.hProcess, 1);
				CloseHandle(pi.hThread);
				PauseOrExit(pi.hProcess);
				return 1;
			}
		}
		else
		{
			if(g_debugConsoleEnabled)
				fprintf(stderr, "[ERROR] TextTranslator.dll not found!\n");
			TerminateProcess(pi.hProcess, 1);
			CloseHandle(pi.hThread);
			PauseOrExit(pi.hProcess);
			return 1;
		}
	}

	DebugPrintf("[INFO] Windows version other than XP detected - proceeding with LocaleEmulator and injection...\n\n");

	// Enable debug privilege for DLL injection
	DebugPrintf("[SETUP] Enabling debug privilege...\n");
	HANDLE currentProc = GetCurrentProcess();
	HANDLE token;
	if (OpenProcessToken(currentProc, TOKEN_ADJUST_PRIVILEGES, &token))
	{
		BOOL bPriv = SetPrivilege(token, SE_DEBUG_NAME, TRUE);
		if (bPriv == FALSE)
		{
			DebugPrintf("[WARNING] Failed to set debug privilege (may cause issues on XP)\n");
		}
		else
		{
			DebugPrintf("[OK] Debug privilege enabled\n");
		}
		CloseHandle(token);
	}

	// Get base directory
	char basePath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, basePath);
	size_t len = strlen(basePath);
	if (basePath[len - 1] != '\\')
		strcat(basePath, "\\");
	
	// Launch the game with LocaleEmulator
	if (!LaunchGameWithLocaleEmulator(basePath))
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "[ERROR] Failed to launch game!\n");
		PauseOrExit(NULL);
		return 1;
	}

	// Wait for the game to start
	DebugPrintf("\n[WAITING] Giving game time to start...\n");
	Sleep(3000);

	// Search for Garage.exe and inject DLL
	DebugPrintf("\n[INJECTION] Looking for Garage.exe...\n");
	DWORD pid = FindProcessByName("Garage.exe");
	if (pid == 0)
	{
		if(g_debugConsoleEnabled)
				fprintf(stderr, "[ERROR] Garage.exe not found!\n");
		if(g_debugConsoleEnabled)
				fprintf(stderr, "The game may not have loaded yet. Try again.\n");
		PauseOrExit(NULL);
		return 1;
	}

	// Find and inject DLL
	char dllPath[MAX_PATH];
	int findResult = FindTextTranslatorDLL(dllPath);
	
	if (findResult == -1)
	{
		// DLL injection disabled - game is already running, no injection needed
		DebugPrintf("\n[INFO] DLL injection disabled, game is running without translation\n");
		DebugPrintf("\n========================================\n");
		DebugPrintf("[RESULT] Done (no DLL injected)\n");
		DebugPrintf("========================================\n\n");
		PauseOrExit(NULL);
		return 0;
	}
	else if (findResult == 1)
	{
		DebugPrintf("\n[STARTING INJECTION]\n");
		if (InjectDLL(pid, dllPath))
		{
			DebugPrintf("\n========================================\n");
			DebugPrintf("[RESULT] Done - DLL injected successfully\n");
			DebugPrintf("========================================\n\n");
			PauseOrExit(NULL);
			return 0;
		}
		else
		{
			if(g_debugConsoleEnabled)
				fprintf(stderr, "[FAILED] Injection failed: %s\n", dllPath);
			PauseOrExit(NULL);
			return 1;
		}
	}
	else
	{
		if(g_debugConsoleEnabled)
			fprintf(stderr, "[ERROR] TextTranslator.dll not found!\n");
		PauseOrExit(NULL);
		return 1;
	}
}
