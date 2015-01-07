#ifndef UQCSM_ASM_INSTR_H
#define UQCSM_ASM_INSTR_H

struct ASM_INSTR {
	unsigned char opcode[15];
	unsigned char size;
};

ASM_INSTR ASM_INSTR_PUSH_DWORD = { { 0x68 }, 1 };

#endif
