#include "SHVInputHook.h"
#include "SHVScriptManager.h"

WNDPROC	oWndProc;

LRESULT APIENTRY InputHook::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	SHVScriptManager::WndProc(hwnd, uMsg, wParam, lParam);

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

bool InputHook::Initialize() {

	HWND windowHandle = NULL;
	while (windowHandle == NULL) {

		windowHandle = FindWindow("grcWindow", NULL);
		Sleep(100);
	}

	oWndProc = (WNDPROC)SetWindowLongPtr(windowHandle, GWLP_WNDPROC, (LONG_PTR)WndProc);
	if (oWndProc == NULL) {

		//g_Logger->Info("Failed to attach input hook");
		return false;
	}
	else {

		//g_Logger->Info("Input hook attached: WndProc 0x%p", (DWORD_PTR)oWndProc);
		return true;
	}
}

void InputHook::Remove() {

	HWND windowHandle = FindWindow("grcWindow", NULL);
	SetWindowLongPtr(windowHandle, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	//g_Logger->Info("Removed input hook");
}
