#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <Windowsx.h>
#define EXPORT  __declspec(dllexport)

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
EXPORT void _doInstallHook(HWND hWnd);
EXPORT void _doRemoveHook(HWND hWnd);