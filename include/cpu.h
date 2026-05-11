#ifndef CPU_H

#define CPU_H

#include "./common.h"
#include "./memory.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct cpu cpu_t;

struct cpu {
	byte A, F;
	byte B, C;
	byte D, E;
	byte H, L;
	
	word SP;
	word PC;
	
	memory_system_t *memory;
};

bool cpu_init(cpu_t *cpu, memory_system_t *memory);
int fetch_decode_exec(cpu_t *cpu);

#endif
