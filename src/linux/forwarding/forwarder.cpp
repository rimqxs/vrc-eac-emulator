#include "forwarder.h"

#include <Windows.h>
#include <plog/Log.h>

void forwarder::setup() {
    TCHAR tzPath[MAX_PATH];
    HMODULE sysdll;

    // Get original DLL path and Load it
    GetSystemDirectory(tzPath, MAX_PATH);
    lstrcat(tzPath, TEXT("\\version"));

    sysdll = LoadLibrary(tzPath);
    if (sysdll != NULL) {
        // Correct self export address
        originalGetFileVersionInfoA = GetProcAddress(sysdll, "GetFileVersionInfoA");
        originalGetFileVersionInfoByHandle = GetProcAddress(sysdll, "GetFileVersionInfoByHandle");
        originalGetFileVersionInfoExA = GetProcAddress(sysdll, "GetFileVersionInfoExA");
        originalGetFileVersionInfoExW = GetProcAddress(sysdll, "GetFileVersionInfoExW");
        originalGetFileVersionInfoSizeA = GetProcAddress(sysdll, "GetFileVersionInfoSizeA");
        originalGetFileVersionInfoSizeExA = GetProcAddress(sysdll, "GetFileVersionInfoSizeExA");
        originalGetFileVersionInfoSizeExW = GetProcAddress(sysdll, "GetFileVersionInfoSizeExW");
        originalGetFileVersionInfoSizeW = GetProcAddress(sysdll, "GetFileVersionInfoSizeW");
        originalGetFileVersionInfoW = GetProcAddress(sysdll, "GetFileVersionInfoW");
        originalVerFindFileA = GetProcAddress(sysdll, "VerFindFileA");
        originalVerFindFileW = GetProcAddress(sysdll, "VerFindFileW");
        originalVerInstallFileA = GetProcAddress(sysdll, "VerInstallFileA");
        originalVerInstallFileW = GetProcAddress(sysdll, "VerInstallFileW");
        originalVerLanguageNameA = GetProcAddress(sysdll, "VerLanguageNameA");
        originalVerLanguageNameW = GetProcAddress(sysdll, "VerLanguageNameW");
        originalVerQueryValueA = GetProcAddress(sysdll, "VerQueryValueA");
        originalVerQueryValueW = GetProcAddress(sysdll, "VerQueryValueW");
    }
}
