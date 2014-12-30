#include "kbdhook.h"

static struct {
	void (*callback)(BYTE, void*);
	void *cb_argument;
	DWORD dwMessageThread;
	HANDLE hMessageThread;
	HHOOK hKeyboardHook;
} KBDHook_Data;

LRESULT CALLBACK KBDHook_Event(int nCode, WPARAM wParam, LPARAM lParam) {
	if(nCode == HC_ACTION && (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN)) {
		BYTE keys[256] = { 0 };
		WORD c;
		GetKeyState(0);
		GetKeyboardState(keys);
		if(ToAscii(((KBDLLHOOKSTRUCT*)lParam)->vkCode, ((KBDLLHOOKSTRUCT*)lParam)->scanCode, keys, &c, 0))
			KBDHook_Data.callback(c, KBDHook_Data.cb_argument);
	}
	return CallNextHookEx(KBDHook_Data.hKeyboardHook, nCode, wParam, lParam);
}

DWORD WINAPI KBDHook_Thread(LPVOID lpParam) {
	MSG msg;

	if((KBDHook_Data.hKeyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, KBDHook_Event, NULL, NULL)) == NULL) {
		return -2;
	}
	
	while(GetMessageA(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	
	return UnhookWindowsHookEx(KBDHook_Data.hKeyboardHook) - 1;
}

static void KBDHook_Term(void) {
	memset(&KBDHook_Data, 0, sizeof(KBDHook_Data));
}

int KBDHook_Start(void (*callback)(BYTE, void*), void *cb_argument) {
	if(KBDHook_Data.hMessageThread != NULL)
		return -1;

	KBDHook_Data.callback = callback;
	KBDHook_Data.cb_argument = cb_argument;

	KBDHook_Data.hMessageThread = CreateThread(NULL, NULL, KBDHook_Thread, NULL, NULL, &KBDHook_Data.dwMessageThread);
	if(KBDHook_Data.hMessageThread == NULL) {
		KBDHook_Term();
		return 0;
	} else {
		return 1;
	}
}

void KBDHook_Stop(void) {
	PostThreadMessageA(KBDHook_Data.dwMessageThread, WM_QUIT, 0, 0);
	WaitForSingleObject(KBDHook_Data.hMessageThread, INFINITE);
	KBDHook_Term();
}
