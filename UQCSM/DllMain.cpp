#include <Windows.h>

DWORD WINAPI StartupThread(LPVOID lpParam) {
	return NULL;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if(fdwReason == DLL_PROCESS_ATTACH) {
		//TODO? Initialize
		//TODO: Hide DLL
		CloseHandle(CreateThread(NULL, NULL, StartupThread, hinstDLL, NULL, NULL));
	}
	return TRUE;
}
