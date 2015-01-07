#ifndef UQCSM_AUTOOFFSETS_H
#define UQCSM_AUTOOFFSETS_H

#include "memscan.h"

#include <Windows.h>
#include <Psapi.h>

#include <cstdarg>

class AutoOffsets {
public:
	static void init();

private:
	static bool inited;

	enum DLL {
		HW,
		CL,
		DLL_COUNT
	};
	typedef struct {
		const DLL dll;
		const char *dll_name;
		MODULEINFO dll_info;
		bool inited;
	} dll_t;

	MemoryScan Scan[DLL_COUNT];

	char *pEngineFuncs;

	void Verify(char *p, dll_t &dll, const char *errmsg, ...);

	void* GetEngineFuncsPtr();

	static dll_t DLL_List[];
};

#endif //UQCSM_AUTOOFFSETS_H
