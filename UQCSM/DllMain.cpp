#include <Windows.h>

#include "hidedll.h"

DWORD WINAPI StartupThread(LPVOID lpParam) {
	return NULL;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if(fdwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hinstDLL);
		HideDLL(hinstDLL);
		CloseHandle(CreateThread(NULL, NULL, StartupThread, hinstDLL, NULL, NULL));
	}
	return TRUE;
}
