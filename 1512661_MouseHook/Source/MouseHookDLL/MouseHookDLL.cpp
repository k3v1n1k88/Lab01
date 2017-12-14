#include "MouseHookDLL.h"

HHOOK hHook = NULL;
HINSTANCE hinstLib;

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	if (nCode < 0) // không xử lý message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	// xử lý message: Ctrl + Right mouse click
	if (wParam == WM_LBUTTONDOWN)
	{
		return true;
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void _doInstallHook(HWND hWnd)
{
	if (hHook!=NULL) return;

	hHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC) MouseHookProc, hinstLib, 0);
	if (hHook)
		MessageBox(hWnd, L"Setup hook successfully", L"Result", MB_OK);
	else
		MessageBox(hWnd, L"Setup hook fail", L"Result", MB_OK);
}

void _doRemoveHook(HWND hWnd)
{
	if (hHook==NULL) return;
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
	MessageBox(hWnd, L"Remove hook successfully", L"Result", MB_OK);
}