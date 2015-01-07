#include "autooffsets.h"

AutoOffsets::dll_t AutoOffsets::DLL_List[] = {
	{ HW, "hw.dll" }
};

void AutoOffsets::init() {
	if(inited)
		return;

	bool allModulesLoaded = true;
	HANDLE hCurrentProc = GetCurrentProcess();

	do {
		if(!allModulesLoaded)
			Sleep(0);

		allModulesLoaded = true;
		for(auto dll : DLL_List) {
			if(!dll.inited) {
				HMODULE hModule = GetModuleHandleA(dll.dll_name);
				if(hModule) {
					if(GetModuleInformation(hCurrentProc, hModule, &dll.dll_info, sizeof(dll.dll_info))) {
						continue;
					}
				}
				allModulesLoaded = false;
			}
		}
	} while(!allModulesLoaded);

	inited = true;
}

void AutoOffsets::Verify(char *p, dll_t &dll, const char *errmsg, ...) {
	if(dll.dll_info.lpBaseOfDll > p || p >= (char*)dll.dll_info.lpBaseOfDll + dll.dll_info.SizeOfImage) {
		char buf[256];
		va_list ap;
		va_start(ap, errmsg);
		vsnprintf(buf, sizeof(buf), errmsg, ap);
		MessageBoxA(HWND_DESKTOP, buf, "Auto Offsets Error!", MB_ICONERROR);
		va_end(ap);
		TerminateProcess(GetCurrentProcess(), 0xA0);
		_asm int3
	}
}

void* AutoOffsets::GetEngineFuncsPtr() {
	if(!pEngineFuncs) {
		pEngineFuncs = Scan[HW].FindMemoryClone("ScreenFade").FindReference(ASM_INSTR_PUSH_DWORD).Dereference(0x0D);
		//TODO: Make exception handler instead of Verify proc
		Verify(pEngineFuncs, DLL_List[HW], "Failed to find pEngineFuncs");
	}
	return pEngineFuncs;
}
