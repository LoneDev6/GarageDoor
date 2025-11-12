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

#define MAX_DLLS 20

BOOL g_debugConsoleEnabled = FALSE;

// Helper macro to pause or exit based on debug console setting
#define PauseOrExit() do { \
	if (g_debugConsoleEnabled) { \
		system("pause"); \
	} else { \
		ExitProcess(1); \
	} \
} while(0)

// Load debug console setting from GarageDoor.ini
void LoadDebugConsoleConfig()
{
	char result[256] = "";
	DWORD success = GetPrivateProfileStringA("Settings", "debug_console", "0", result, sizeof(result), ".\\GarageDoor.ini");
	g_debugConsoleEnabled = (strcmp(result, "1") == 0 || strcmp(result, "true") == 0);
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

// Just in case Windows ignores the compatibility flags for some reason, forcibly change resolution
void ForceResolution640x480()
{
    DEVMODEA devMode;
    ZeroMemory(&devMode, sizeof(devMode));
    devMode.dmSize = sizeof(devMode);
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
    devMode.dmPelsWidth = 640;
    devMode.dmPelsHeight = 480;
    devMode.dmBitsPerPel = 16;
    
    LONG result = ChangeDisplaySettingsA(&devMode, CDS_FULLSCREEN);
    
    if (result == DISP_CHANGE_SUCCESSFUL)
    {
        printf("[OK] Resolution forced to 640x480 16-bit\n");
    }
    else
    {
        fprintf(stderr, "[ERROR] Failed to change resolution: %ld\n", result);
    }
}

// This makes the Garage.exe process run with compatibility flags
void ApplyCompatibilityFlags(const char *exePath)
{
	HKEY hKey;
	const char *subKey = "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers";
	if (RegCreateKeyExA(HKEY_CURRENT_USER, subKey, 0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS)
	{
		const char *flags;
		// Windows XP uses a different format.
		// Anyway it seems it totally ignores this when launching via GarageDoor.exe for some reason
		// but not when launching the game via Garage.exe (useless as translation DLLs won't be injected)
		if (IsWindowsXP())
			flags = "256COLOR 640X480";
		else
			flags = "640X480 16BITCOLOR RUNASADMIN";
		RegSetValueExA(hKey, exePath, 0, REG_SZ, (const BYTE *)flags, (DWORD)(strlen(flags) + 1));
		RegCloseKey(hKey);
		printf("[OK] Compatibility flags applied to: %s\n", exePath);
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

	printf("[LAUNCHER] Starting LocaleEmulator...\n");
	printf("[LAUNCHER] LEProc path: %s\n", leprocPath);
	printf("[LAUNCHER] Garage path: %s\n", garageExePath);

	ApplyCompatibilityFlags(garageExePath);

	// Try ShellExecute
	HINSTANCE shellexec = ShellExecuteA(NULL, "runas", leprocPath, params, basePath, SW_SHOWNORMAL);
	if ((INT_PTR)shellexec <= 32)
	{
		printf("[LAUNCHER] ShellExecute failed, trying CreateProcess...\n");
		
		// Fallback CreateProcess
		char cmdline[2048];
		sprintf(cmdline, "\"%s\" %s", leprocPath, params);

		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (!CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, basePath, &si, &pi))
		{
			fprintf(stderr, "[ERROR] CreateProcess failed\n");
			return 0;
		}
		
		if (pi.hProcess)
			CloseHandle(pi.hProcess);
		if (pi.hThread)
			CloseHandle(pi.hThread);
	}

	printf("[OK] LocaleEmulator launched!\n");
	return 1;
}

DWORD FindProcessByName(const char* processName)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Error: CreateToolhelp32Snapshot failed\n");
		return 0;
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
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
			printf("[OK] Process found: %s (PID: %lu)\n", processName, pidTarget);
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
		fprintf(stderr, "[ERROR] File not found: %s\n", dllPath);
		return 0;
	}
	CloseHandle(hFile);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == NULL)
	{
		fprintf(stderr, "[ERROR] Cannot open process (PID: %lu)\n", pid);
		return 0;
	}

	// Allocate memory in target process for DLL path
	size_t dllPathLen = strlen(dllPath) + 1;
	LPVOID pDllPath = VirtualAllocEx(hProcess, NULL, dllPathLen, MEM_COMMIT, PAGE_READWRITE);
	if (pDllPath == NULL)
	{
		fprintf(stderr, "[ERROR] VirtualAllocEx failed\n");
		CloseHandle(hProcess);
		return 0;
	}

	// Write DLL path to target process memory
	if (!WriteProcessMemory(hProcess, pDllPath, (LPVOID)dllPath, dllPathLen, NULL))
	{
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
		fprintf(stderr, "[ERROR] Cannot find LoadLibraryA\n");
		VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return 0;
	}

	// Create remote thread
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibraryA, pDllPath, 0, NULL);
	if (hThread == NULL)
	{
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
		fprintf(stderr, "[ERROR] LoadLibraryA returned NULL - DLL not loaded\n");
		VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return 0;
	}
	
	printf("[INFO] LoadLibraryA returned: 0x%lx\n", threadExitCode);
	printf("[OK] DLL injected: %s\n", dllPath);
	
	// Cleanup
	VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
	CloseHandle(hThread);
	CloseHandle(hProcess);

	return 1;
}

// Find all DLLs in current directory
int FindDLLsInCurrentDir(char dllPaths[MAX_DLLS][MAX_PATH])
{
	char currentDir[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDir);

	printf("[DEBUG] Current directory: %s\n", currentDir);

	WIN32_FIND_DATAA findData;
	HANDLE findHandle = FindFirstFileA("*.dll", &findData);

	int count = 0;
	if (findHandle == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "[ERROR] No DLL files found\n");
		return 0;
	}

	do
	{
		sprintf(dllPaths[count], "%s\\%s", currentDir, findData.cFileName);
		printf("[FOUND] %s\n", dllPaths[count]);
		count++;
		if (count >= MAX_DLLS)
			break;
	} while (FindNextFileA(findHandle, &findData));

	FindClose(findHandle);
	return count;
}

// Check if Japanese locale is properly configured for display
BOOL CanDisplayJapanese()
{
	// Try to detect if output device can handle Japanese
	// This is a fallback check - on XP with proper config, this should work
	// We verify by trying to set console output code page to Shift-JIS (932)
	
	UINT currentCodePage = GetConsoleCP();
	UINT currentOutputCodePage = GetConsoleOutputCP();
	
	printf("[DEBUG] Current console input code page: %u\n", currentCodePage);
	printf("[DEBUG] Current console output code page: %u\n", currentOutputCodePage);
	
	// Shift-JIS is code page 932
	// If neither is 932, Japanese might not display correctly
	if (currentCodePage != 932 && currentOutputCodePage != 932)
	{
		printf("[WARNING] Console code pages are not set to Shift-JIS (932)\n");
		printf("[WARNING] Attempting to set output code page to 932...\n");
		
		if (!SetConsoleOutputCP(932))
		{
			printf("[ERROR] Could not set console output code page to 932\n");
			return FALSE;
		}
	}
	
	return TRUE;
}


int main()
{
	// Load debug console configuration first
	LoadDebugConsoleConfig();
	
	// Show console only if debug_console is enabled in GarageDoor.ini
	if (g_debugConsoleEnabled)
	{
		AllocConsole();
		ShowWindow(GetConsoleWindow(), SW_NORMAL);
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitleA("Garage Patch - Injector Debug Console");
	}
	
	printf("\n========================================\n");
	printf("Garage English Patch - Launcher & Injector\n");
	printf("========================================\n\n");

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

		ApplyCompatibilityFlags(garageExePath);

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

		printf("[OK] Garage.exe launched (suspended)\n");
		Sleep(1000);

		// Now inject DLLs into the suspended process
		printf("\n[INJECTION] Injecting DLLs into Garage.exe (PID: %lu)...\n", pi.dwProcessId);

		// Find all DLLs in current directory
		char dllPaths[MAX_DLLS][MAX_PATH];
		int dllCount = FindDLLsInCurrentDir(dllPaths);
		if (dllCount == 0)
		{
			fprintf(stderr, "[ERROR] No DLL files found in current directory!\n");
			TerminateProcess(pi.hProcess, 1);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			PauseOrExit();
			return 1;
		}

		// Inject all found DLLs
		printf("\n[STARTING INJECTION]\n");
		int successCount = 0;
		int i;
		for (i = 0; i < dllCount; i++)
		{
			if (InjectDLL(pi.dwProcessId, dllPaths[i]))
			{
				successCount++;
			}
			else
			{
				fprintf(stderr, "[FAILED] %s\n", dllPaths[i]);
			}
		}

		// Resume the main thread
		printf("\n[RESUMING] Resuming Garage.exe...\n");
		ForceResolution640x480(); 
		ResumeThread(pi.hThread);

		// Aspetta che Garage.exe termini
		WaitForSingleObject(pi.hProcess, INFINITE);
		printf("[INFO] Garage.exe has closed\n");

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		printf("\n========================================\n");
		printf("[RESULT] %d/%d DLLs injected successfully\n", successCount, dllCount);
		printf("========================================\n\n");

		PauseOrExit();
		return 0;
	}

	printf("[INFO] Windows version other than XP detected - proceeding with LocaleEmulator and injection...\n\n");

	// Enable debug privilege for DLL injection
	printf("[SETUP] Enabling debug privilege...\n");
	HANDLE currentProc = GetCurrentProcess();
	HANDLE token;
	if (OpenProcessToken(currentProc, TOKEN_ADJUST_PRIVILEGES, &token))
	{
		BOOL bPriv = SetPrivilege(token, SE_DEBUG_NAME, TRUE);
		if (bPriv == FALSE)
		{
			printf("[WARNING] Failed to set debug privilege (may cause issues on XP)\n");
		}
		else
		{
			printf("[OK] Debug privilege enabled\n");
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
		fprintf(stderr, "[ERROR] Failed to launch game!\n");
		PauseOrExit();
		return 1;
	}

	// Wait for the game to start
	printf("\n[WAITING] Giving game time to start...\n");
	Sleep(3000);

	// Search for Garage.exe and inject DLLs
	printf("\n[INJECTION] Looking for Garage.exe...\n");
	DWORD pid = FindProcessByName("Garage.exe");
	if (pid == 0)
	{
		fprintf(stderr, "[ERROR] Garage.exe not found!\n");
		fprintf(stderr, "The game may not have loaded yet. Try again.\n");
		PauseOrExit();
		return 1;
	}

	// Find all DLLs in current directory
	char dllPaths[MAX_DLLS][MAX_PATH];
	int dllCount = FindDLLsInCurrentDir(dllPaths);
	if (dllCount == 0)
	{
		fprintf(stderr, "[ERROR] No DLL files found in current directory!\n");
		PauseOrExit();
		return 1;
	}

	// Inject all found DLLs
	printf("\n[STARTING INJECTION]\n");
	int successCount = 0;
	int i;
	for (i = 0; i < dllCount; i++)
	{
		if (InjectDLL(pid, dllPaths[i]))
		{
			successCount++;
		}
		else
		{
			fprintf(stderr, "[FAILED] %s\n", dllPaths[i]);
		}
	}

	printf("\n========================================\n");
	printf("[RESULT] %d/%d DLLs injected successfully\n", successCount, dllCount);
	printf("========================================\n\n");

	PauseOrExit();
	return 0;
}
