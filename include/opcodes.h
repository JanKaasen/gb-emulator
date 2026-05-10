#ifndef OPCODES

#define OPCODES

#include "common.h"
#include "cpu.h"

typedef int (*opcode)(cpu_t *cpu);
extern opcode op_table[256];

void opcodes_00_3F_init(void);
void opcodes_40_7F_init(void);
void opcodes_80_BF_init(void);
void opcodes_C0_FF_init(void);
void opcodes_cb_init(void);

#endif
