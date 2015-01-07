#ifndef UQCSM_MEMSCAN_H
#define UQCSM_MEMSCAN_H

#include "asm_instr.h"

#include <string>

using namespace std;

class MemoryScan {
public:
	void init(char *base, int size);

	MemoryScan& FindMemoryClone(const basic_string<char> pattern, char *start = NULL, int size = 0);
	MemoryScan& FindReference(const ASM_INSTR &instr, char *start = NULL, int size = 0);
	MemoryScan& Dereference(int offset = 0);

	operator char*() { return m_result; }

private:
	char *m_base;
	int m_size;

	char *m_result;
};

#endif //UQCSM_MEMSCAN_H
