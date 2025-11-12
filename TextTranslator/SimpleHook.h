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
#include <cstdio>

// Structure to store original bytes backup
struct HookInfo
{
    LPVOID targetFunc;
    unsigned char originalBytes[5];
    bool hooked;
};

// Save 5 bytes and replace them with a JMP
bool InstallHook(LPVOID targetFunc, LPVOID detourFunc, HookInfo& info)
{
    DWORD oldProtect;
    
    // Save original bytes
    memcpy(info.originalBytes, (void*)targetFunc, 5);
    info.targetFunc = targetFunc;
    
    // Make the memory writable
    if (!VirtualProtect(targetFunc, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        fprintf(stderr, "[ERROR] VirtualProtect failed\n");
        return false;
    }
    
    // Calculate relative offset for JMP
    // JMP is: E9 [32-bit relative offset]
    unsigned char jmpCode[5];
    jmpCode[0] = 0xE9; // JMP opcode
    
    // offset = destination - (source + 5)
    // Use UINT_PTR for proper 32/64-bit compatibility
    UINT_PTR offset = (UINT_PTR)detourFunc - ((UINT_PTR)targetFunc + 5);
    // Only use low 32 bits for relative jump (it's a signed 32-bit offset)
    DWORD relOffset = (DWORD)offset;
    
    // Calculate the offset (little-endian)
    memcpy(&jmpCode[1], &relOffset, 4);
    
    // Write the JMP
    memcpy(targetFunc, jmpCode, 5);
    
    // Restore original permissions
    VirtualProtect(targetFunc, 5, oldProtect, &oldProtect);
    
    info.hooked = true;
    return true;
}

// Uninstall the hook
bool UninstallHook(HookInfo& info)
{
    DWORD oldProtect;
    
    if (!info.hooked)
        return false;
    
    if (!VirtualProtect(info.targetFunc, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        fprintf(stderr, "[ERROR] VirtualProtect failed\n");
        return false;
    }
    
    // Restore original bytes
    memcpy(info.targetFunc, info.originalBytes, 5);
    
    VirtualProtect(info.targetFunc, 5, oldProtect, &oldProtect);
    
    info.hooked = false;
    return true;
}
