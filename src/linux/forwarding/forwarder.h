#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

inline FARPROC originalGetFileVersionInfoA, originalGetFileVersionInfoByHandle, originalGetFileVersionInfoExA,
	originalGetFileVersionInfoExW, originalGetFileVersionInfoSizeA, originalGetFileVersionInfoSizeExA,
	originalGetFileVersionInfoSizeExW, originalGetFileVersionInfoSizeW, originalGetFileVersionInfoW,
	originalVerFindFileA, originalVerFindFileW, originalVerInstallFileA,
	originalVerInstallFileW, originalVerLanguageNameA, originalVerLanguageNameW,
	originalVerQueryValueA, originalVerQueryValueW;

class forwarder {
public:
	static void setup();
};
