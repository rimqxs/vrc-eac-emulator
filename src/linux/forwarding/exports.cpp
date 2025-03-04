#include <Windows.h>

#include "forwarder.h"

extern "C" __declspec( dllexport ) BOOL DummyGetFileVersionInfoA(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
    typedef BOOL(__stdcall* GetFileVersionInfoA)(LPCSTR, DWORD, DWORD, LPVOID);
    return reinterpret_cast<GetFileVersionInfoA>(originalGetFileVersionInfoA)(lptstrFilename, dwHandle, dwLen, lpData);
}

extern "C" __declspec( dllexport ) BOOL DummyGetFileVersionInfoByHandle(DWORD dwFlags, HANDLE hFile, LPVOID* lplpData, PDWORD pdwLen) {
    typedef BOOL(__stdcall* GetFileVersionInfoByHandle)(DWORD, HANDLE, LPVOID*, PDWORD);
    return reinterpret_cast<GetFileVersionInfoByHandle>(originalGetFileVersionInfoByHandle)(dwFlags, hFile, lplpData, pdwLen);
}

extern "C" __declspec( dllexport ) BOOL DummyGetFileVersionInfoExA(DWORD dwFlags, LPCSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
    typedef BOOL(__stdcall* GetFileVersionInfoExA)(DWORD, LPCSTR, DWORD, DWORD, LPVOID);
    return reinterpret_cast<GetFileVersionInfoExA>(originalGetFileVersionInfoExA)(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

extern "C" __declspec( dllexport ) BOOL DummyGetFileVersionInfoExW(DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
    typedef BOOL(__stdcall* GetFileVersionInfoExW)(DWORD, LPCWSTR, DWORD, DWORD, LPVOID);
    return reinterpret_cast<GetFileVersionInfoExW>(originalGetFileVersionInfoExW)(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

extern "C" __declspec( dllexport ) DWORD DummyGetFileVersionInfoSizeA(LPCSTR lptstrFilename, LPDWORD lpdwHandle) {
    typedef DWORD(__stdcall* GetFileVersionInfoSizeA)(LPCSTR, LPDWORD);
    return reinterpret_cast<GetFileVersionInfoSizeA>(originalGetFileVersionInfoSizeA)(lptstrFilename, lpdwHandle);
}

extern "C" __declspec( dllexport ) DWORD DummyGetFileVersionInfoSizeExA(DWORD dwFlags, LPCSTR lpwstrFilename, LPDWORD lpdwHandle) {
    typedef DWORD(__stdcall* GetFileVersionInfoSizeExA)(DWORD, LPCSTR, LPDWORD);
    return reinterpret_cast<GetFileVersionInfoSizeExA>(originalGetFileVersionInfoSizeExA)(dwFlags, lpwstrFilename, lpdwHandle);
}

extern "C" __declspec( dllexport ) DWORD DummyGetFileVersionInfoSizeExW(DWORD dwFlags, LPCWSTR lpwstrFilename, LPDWORD lpdwHandle) {
    typedef DWORD(__stdcall* GetFileVersionInfoSizeExW)(DWORD, LPCWSTR, LPDWORD);
    return reinterpret_cast<GetFileVersionInfoSizeExW>(originalGetFileVersionInfoSizeExW)(dwFlags, lpwstrFilename, lpdwHandle);
}

extern "C" __declspec( dllexport ) DWORD DummyGetFileVersionInfoSizeW(LPCWSTR lptstrFilename, LPDWORD lpdwHandle) {
    typedef DWORD(__stdcall* GetFileVersionInfoSizeW)(LPCWSTR, LPDWORD);
    return reinterpret_cast<GetFileVersionInfoSizeW>(originalGetFileVersionInfoSizeW)(lptstrFilename, lpdwHandle);
}

extern "C" __declspec( dllexport ) BOOL DummyGetFileVersionInfoW(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
    typedef BOOL(__stdcall* GetFileVersionInfoW)(LPCWSTR, DWORD, DWORD, LPVOID);
    return reinterpret_cast<GetFileVersionInfoW>(originalGetFileVersionInfoW)(lptstrFilename, dwHandle, dwLen, lpData);
}

extern "C" __declspec( dllexport ) DWORD DummyVerFindFileA(DWORD uFlags, LPCSTR szFileName, LPCSTR szWinDir, LPCSTR szAppDir, LPSTR szCurDir, PUINT puCurDirLen, LPSTR szDestDir, PUINT puDestDirLen) {
    typedef DWORD(__stdcall* VerFindFileA)(DWORD, LPCSTR, LPCSTR, LPCSTR, LPSTR, PUINT, LPSTR, PUINT);
    return reinterpret_cast<VerFindFileA>(originalVerFindFileA)(uFlags, szFileName, szWinDir, szAppDir, szCurDir, puCurDirLen, szDestDir, puDestDirLen);
}

extern "C" __declspec( dllexport ) DWORD DummyVerFindFileW(DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPWSTR szCurDir, PUINT puCurDirLen, LPWSTR szDestDir, PUINT puDestDirLen) {
    typedef DWORD(__stdcall* VerFindFileW)(DWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPWSTR, PUINT, LPWSTR, PUINT);
    return reinterpret_cast<VerFindFileW>(originalVerFindFileW)(uFlags, szFileName, szWinDir, szAppDir, szCurDir, puCurDirLen, szDestDir, puDestDirLen);
}

extern "C" __declspec( dllexport ) DWORD DummyVerInstallFileA(DWORD uFlags, LPCSTR szSrcFileName, LPCSTR szDestFileName, LPCSTR szSrcDir, LPCSTR szDestDir, LPCSTR szCurDir, LPSTR szTmpFile, PUINT puTmpFileLen) {
    typedef DWORD(__stdcall* VerInstallFileA)(DWORD, LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPSTR, PUINT);
    return reinterpret_cast<VerInstallFileA>(originalVerInstallFileA)(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, puTmpFileLen);
}

extern "C" __declspec( dllexport ) DWORD DummyVerInstallFileW(DWORD uFlags, LPCWSTR szSrcFileName, LPCWSTR szDestFileName, LPCWSTR szSrcDir, LPCWSTR szDestDir, LPCWSTR szCurDir, LPWSTR szTmpFile, PUINT puTmpFileLen) {
    typedef DWORD(__stdcall* VerInstallFileW)(DWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPWSTR, PUINT);
    return reinterpret_cast<VerInstallFileW>(originalVerInstallFileW)(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, puTmpFileLen);
}

extern "C" __declspec( dllexport ) DWORD DummyVerLanguageNameA(DWORD wLang, LPSTR szLang, DWORD cchLang) {
    typedef DWORD(__stdcall* VerLanguageNameA)(DWORD, LPSTR, DWORD);
    return reinterpret_cast<VerLanguageNameA>(originalVerLanguageNameA)(wLang, szLang, cchLang);
}

extern "C" __declspec( dllexport ) DWORD DummyVerLanguageNameW(DWORD wLang, LPWSTR szLang, DWORD cchLang) {
    typedef DWORD(__stdcall* VerLanguageNameW)(DWORD, LPWSTR, DWORD);
    return reinterpret_cast<VerLanguageNameW>(originalVerLanguageNameW)(wLang, szLang, cchLang);
}

extern "C" __declspec( dllexport ) BOOL DummyVerQueryValueA(LPCVOID pBlock, LPCSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen) {
    typedef BOOL(__stdcall* VerQueryValueA)(LPCVOID, LPCSTR, LPVOID*, PUINT);
    return reinterpret_cast<VerQueryValueA>(originalVerQueryValueA)(pBlock, lpSubBlock, lplpBuffer, puLen);
}

extern "C" __declspec( dllexport ) BOOL DummyVerQueryValueW(LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen) {
    typedef BOOL(__stdcall* VerQueryValueW)(LPCVOID, LPCWSTR, LPVOID*, PUINT);
    return reinterpret_cast<VerQueryValueW>(originalVerQueryValueW)(pBlock, lpSubBlock, lplpBuffer, puLen);
}