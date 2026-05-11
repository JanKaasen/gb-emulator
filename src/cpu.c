#include "../include/cpu.h"
#include "../include/common.h"
#include "../include/memory.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


bool cpu_init(cpu_t *cpu, memory_system_t *memory)
{
	if (cpu == NULL) {
		printf("CANNOT INITIALIZE NULL CPU");
		return false;
	}

	cpu->A = 0x01;
	cpu->F = 0xB0;
	cpu->B = 0x00;
	cpu->C = 0x13;
	cpu->D = 0x00;
	cpu->E = 0xD8;
	cpu->H = 0x01;
	cpu->L = 0x40;
	cpu->PC = 0x0100;
	cpu->SP = 0xFFFE;

	cpu->memory = memory;

	return true;
}

int fetch_decode_exec(cpu_t *cpu)
{
	byte opcode = memory_read_byte(cpu->memory, cpu->PC);
	cpu->PC++;
	return 4;
}
