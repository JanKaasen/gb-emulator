#include "../include/opcodes.h"

opcode op_table[256] = {0};

void opcodes_init(void)
{
	opcodes_00_3F_init();
}
