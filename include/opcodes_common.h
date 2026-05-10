#ifndef OPCODES_COMMON

#define OPCODES_COMMON

#include "cpu.h"

#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

#define GET_FLAG(cpu, flag) (((cpu)->F & (flag)) != 0)
#define SET_FLAG(cpu, flag) ((cpu)->F |= (flag))
#define CLEAR_FLAG(cpu, flag) ((cpu)->F &= ~(flag))
#define SET_FLAG_VALUE(cpu, flag, value)                                       \
	if (value)                                                             \
		SET_FLAG(cpu, flag);                                           \
	else                                                                   \
		CLEAR_FLAG(cpu, flag)

#define READ_BYTE(addr) memory_read_byte(cpu->memory, (addr))
#define WRITE_BYTE(addr, val) memory_write_byte(cpu->memory, (addr), (val))

#define GET_BC(cpu) ((cpu->B << 8) | cpu->C)
#define GET_DE(cpu) ((cpu->D << 8) | cpu->E)
#define GET_HL(cpu) ((cpu->H << 8) | cpu->L)

#define SET_BC(cpu, val)                                                       \
	do {                                                                   \
		cpu->B = ((val) >> 8);                                         \
		cpu->C = (val) & 0xFF;                                         \
	} while (0)
#define SET_DE(cpu, val)                                                       \
	do {                                                                   \
		cpu->D = ((val) >> 8);                                         \
		cpu->E = (val) & 0xFF;                                         \
	} while (0)
#define SET_HL(cpu, val)                                                       \
	do {                                                                   \
		cpu->H = ((val) >> 8);                                         \
		cpu->L = (val) & 0xFF;                                         \
	} while (0)

void inc_helper(cpu_t *cpu, byte *cpu_register);
void dec_helper(cpu_t *cpu, byte *cpu_register);
void byte_add_helper(cpu_t *cpu, byte val);
void byte_adc_helper(cpu_t *cpu, byte val);
void byte_sub_helper(cpu_t *cpu, byte val);
void byte_subc_helper(cpu_t *cpu, byte val);
void and_helper(cpu_t *cpu, byte val);
void or_helper(cpu_t *cpu, byte val);
void xor_helper(cpu_t *cpu, byte val);
void compare_helper(cpu_t *cpu, byte val);
void word_add_helper(cpu_t *cpu, word val);

#endif
