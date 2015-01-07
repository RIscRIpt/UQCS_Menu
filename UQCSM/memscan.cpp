#include "memscan.h"

void MemoryScan::init(char *base, int size) {
	m_base = base;
	m_size = size;
}

MemoryScan& MemoryScan::FindMemoryClone(const basic_string<char> pattern, char *start, int size) {
	if(start == NULL) start = m_base;
	if(size == 0) size = m_size;

	size -= pattern.size();
	
	m_result = NULL;

	for(; size >= 0; size--) {
		if(*(char*)start == *pattern.begin()) {
			if(!pattern.compare(1, pattern.size() - 1, (char*)start + 1)) {
				m_result = start;
				break;
			}
		}
		start++;
	}
	return *this;
}

MemoryScan& MemoryScan::FindReference(const ASM_INSTR &instr, char *start, int size) {
	if(m_result != NULL) {
		char pattern[20];

		*(int*)&pattern[0] = (int)m_result;
		memcpy(&pattern[4], instr.opcode, instr.size);

		return FindMemoryClone(pattern, start, size);
	}
	return *this;
}

MemoryScan& MemoryScan::Dereference(int offset) {
	m_result = (char*)*(int*)((int)m_result + offset);
	return *this;
}
