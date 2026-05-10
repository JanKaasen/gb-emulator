#include "../include/opcodes_common.h"

void inc_helper(cpu_t *cpu, byte *cpu_register)
{
	SET_FLAG_VALUE(
	    cpu, FLAG_H, ((*cpu_register & 0x0F) + (1 & 0x0F)) > 0x0F);
	(*cpu_register)++;
	SET_FLAG_VALUE(cpu, FLAG_Z, *cpu_register == 0);
	CLEAR_FLAG(cpu, FLAG_N);
}

void dec_helper(cpu_t *cpu, byte *cpu_register)
{
	SET_FLAG_VALUE(cpu, FLAG_H, (*cpu_register & 0x0F) == 0);
	(*cpu_register)--;
	SET_FLAG_VALUE(cpu, FLAG_Z, *cpu_register == 0);
	SET_FLAG(cpu, FLAG_N);
}

void byte_add_helper(cpu_t *cpu, byte val)
{
	word result = cpu->A + val;

	SET_FLAG_VALUE(cpu, FLAG_H, ((cpu->A & 0x0F) + (val & 0x0F)) > 0x0F);
	SET_FLAG_VALUE(cpu, FLAG_C, result > 0xFF);

	cpu->A = result & 0xFF;

	SET_FLAG_VALUE(cpu, FLAG_Z, cpu->A == 0);
	CLEAR_FLAG(cpu, FLAG_N);
}

void byte_adc_helper(cpu_t *cpu, byte val)
{
	byte carry = GET_FLAG(cpu, FLAG_C) ? 1 : 0;
	word result = cpu->A + val + carry;

	SET_FLAG_VALUE(
	    cpu, FLAG_H, ((cpu->A & 0x0F) + (val & 0x0F) + carry) > 0x0F);
	SET_FLAG_VALUE(cpu, FLAG_C, result > 0xFF);

	cpu->A = result & 0xFF;

	SET_FLAG_VALUE(cpu, FLAG_Z, cpu->A == 0);
	CLEAR_FLAG(cpu, FLAG_N);
}

void byte_sub_helper(cpu_t *cpu, byte val)
{
	word result = cpu->A - val;

	SET_FLAG_VALUE(cpu, FLAG_H, (cpu->A & 0x0F) < (val & 0x0F));
	SET_FLAG_VALUE(cpu, FLAG_C, result > 0xFF);

	cpu->A = result & 0xFF;

	SET_FLAG_VALUE(cpu, FLAG_Z, cpu->A == 0);
	SET_FLAG(cpu, FLAG_N);
}

void byte_subc_helper(cpu_t *cpu, byte val)
{
	byte carry = GET_FLAG(cpu, FLAG_C) ? 1 : 0;
	word result = cpu->A - val - carry;

	SET_FLAG_VALUE(cpu, FLAG_H, (cpu->A & 0x0F) < ((val & 0x0F) + carry));
	SET_FLAG_VALUE(cpu, FLAG_C, result > 0xFF);

	cpu->A = result & 0xFF;

	SET_FLAG_VALUE(cpu, FLAG_Z, cpu->A == 0);
	SET_FLAG(cpu, FLAG_N);
}

void and_helper(cpu_t *cpu, byte val)
{
	cpu->A = cpu->A & val;

	SET_FLAG_VALUE(cpu, FLAG_Z, cpu->A == 0);
	SET_FLAG_VALUE(cpu, FLAG_H, 1);
	CLEAR_FLAG(cpu, FLAG_N);
	CLEAR_FLAG(cpu, FLAG_C);
}

void or_helper(cpu_t *cpu, byte val)
{
	cpu->A = cpu->A | val;
	SET_FLAG_VALUE(cpu, FLAG_Z, cpu->A == 0);
	CLEAR_FLAG(cpu, FLAG_N);
	CLEAR_FLAG(cpu, FLAG_H);
	CLEAR_FLAG(cpu, FLAG_C);
}

void xor_helper(cpu_t *cpu, byte val)
{
	cpu->A = cpu->A ^ val;
	SET_FLAG_VALUE(cpu, FLAG_Z, cpu->A == 0);
	CLEAR_FLAG(cpu, FLAG_N);
	CLEAR_FLAG(cpu, FLAG_H);
	CLEAR_FLAG(cpu, FLAG_C);
}

void word_add_helper(cpu_t *cpu, word val)
{
	word HL_value = (cpu->H << 8) | cpu->L;
	uint32_t result = HL_value + val;

	SET_FLAG_VALUE(
	    cpu, FLAG_H, ((HL_value & 0x0FFF) + (val & 0x0FFF)) > 0x0FFF);
	SET_FLAG_VALUE(cpu, FLAG_C, result > 0xFFFF);
	cpu->L = result & 0xFF;
	cpu->H = (result >> 8) & 0xFF;
	CLEAR_FLAG(cpu, FLAG_N);
}

void compare_helper(cpu_t *cpu, byte val)
{
	SET_FLAG_VALUE(cpu, FLAG_H, ((cpu->A & 0x0F) < (val & 0x0F)));
	SET_FLAG_VALUE(cpu, FLAG_C, cpu->A < val);

	SET_FLAG_VALUE(cpu, FLAG_Z, cpu->A - val == 0);
	SET_FLAG(cpu, FLAG_N);
}
