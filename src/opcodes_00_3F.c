#include "../include/opcodes.h"
#include "../include/opcodes_common.h"
#include <stdint.h>

int nop(cpu_t *cpu)
{
	return 4;
}

int ld_bc_n16(cpu_t *cpu)
{
	SET_BC(cpu, read_n16(cpu));
	return 12;
}

int ld_bc_a(cpu_t *cpu)
{
	WRITE_BYTE(GET_BC(cpu), cpu->A);
	return 8;
}

int inc_bc(cpu_t *cpu)
{
	cpu->C++;
	if (cpu->C == 0) {
		cpu->B++;
	}
	return 8;
}

int inc_b(cpu_t *cpu)
{
	inc_helper(cpu, &cpu->B);
	return 4;
}

int dec_b(cpu_t *cpu)
{
	dec_helper(cpu, &cpu->B);
	return 4;
}

int ld_b_n8(cpu_t *cpu)
{
	cpu->B = READ_BYTE(cpu->PC++);
	return 8;
}

// TODO: Implement rlca
int rlca(cpu_t *cpu)
{
	return 4;
}

int ld_n16_sp(cpu_t *cpu)
{
	WRITE_WORD(read_n16(cpu), cpu->SP);
	return 20;
}

int add_hl_bc(cpu_t *cpu)
{
	word_add_helper(cpu, GET_BC(cpu));
	return 8;
}

int ld_a_bc(cpu_t *cpu)
{
	cpu->A = READ_BYTE(GET_BC(cpu));
	return 8;
}

int dec_bc(cpu_t *cpu)
{
	word val = GET_BC(cpu);
	val--;
	SET_BC(cpu, val);
	return 8;
}

int inc_c(cpu_t *cpu)
{
	inc_helper(cpu, &cpu->C);
	return 4;
}
int dec_c(cpu_t *cpu)
{
	dec_helper(cpu, &cpu->C);
	return 4;
}

int ld_c_n8(cpu_t *cpu)
{
	cpu->C = READ_BYTE(cpu->PC++);
	return 8;
	cpu->C = READ_BYTE(cpu->PC++);
	return 8;
}

// TODO: Implement rrca
int rrca(cpu_t *cpu)
{
	return 4;
}

// TODO: Implement stop
int stop(cpu_t *cpu)
{
	return 4;
}

int ld_de_n16(cpu_t *cpu)
{
	SET_DE(cpu, read_n16(cpu));
	return 12;
}

int ld_de_a(cpu_t *cpu)
{
	WRITE_BYTE(GET_DE(cpu), cpu->A);
	return 8;
}
int inc_de(cpu_t *cpu)
{
	cpu->D++;
	if (cpu->D == 0) {
		cpu->E++;
	}
	return 8;
}

int inc_d(cpu_t *cpu)
{
	inc_helper(cpu, &cpu->D);
	return 4;
}

int dec_d(cpu_t *cpu)
{
	dec_helper(cpu, &cpu->D);
	return 4;
}

int ld_d_n8(cpu_t *cpu)
{
	cpu->D = READ_BYTE(cpu->PC++);
	return 8;
}

// TODO: Implement RLA
int rla(cpu_t *cpu)
{
	return 4;
}

int jr_e8(cpu_t *cpu)
{
	int8_t offset = READ_BYTE(cpu->PC++);
	cpu->PC += offset;
	return 12;
}

int add_hl_de(cpu_t *cpu)
{
	word_add_helper(cpu, GET_DE(cpu));
	return 8;
}

int ld_a_de(cpu_t *cpu)
{
	cpu->A = READ_BYTE(GET_DE(cpu));
	return 8;
}

int dec_de(cpu_t *cpu)
{
	word val = GET_DE(cpu);
	val--;
	SET_DE(cpu, val);
	return 8;
}

int inc_e(cpu_t *cpu)
{
	inc_helper(cpu, &cpu->E);
	return 4;
}

int dec_e(cpu_t *cpu)
{
	dec_helper(cpu, &cpu->E);
	return 4;
}

int ld_e_n8(cpu_t *cpu)
{
	cpu->E = READ_BYTE(cpu->PC++);
	return 8;
}

// TODO: implement rra
int rra(cpu_t *cpu)
{
	return 4;
}

int jr_nz_e8(cpu_t *cpu)
{
	int8_t offset = READ_BYTE(cpu->PC++);
	if (!GET_FLAG(cpu, FLAG_Z)) {
		cpu->PC += offset;
		return 12;
	} else {
		return 8;
	}
}

int ld_hl_n16(cpu_t *cpu)
{
	SET_HL(cpu, read_n16(cpu));
	return 12;
}

int ld_hli_a(cpu_t *cpu)
{
	address addr = GET_HL(cpu);
	WRITE_BYTE(addr, cpu->A);
	addr++;
	SET_HL(cpu, addr);
	return 8;
}

int inc_hl(cpu_t *cpu)
{
	word val = GET_HL(cpu);
	val--;
	SET_HL(cpu, val);
	return 8;
}

int inc_h(cpu_t *cpu)
{
	inc_helper(cpu, &cpu->H);
	return 4;
}

int dec_h(cpu_t *cpu)
{
	dec_helper(cpu, &cpu->H);
	return 4;
}

int ld_h_n8(cpu_t *cpu)
{
	cpu->H = READ_BYTE(cpu->PC++);
	return 8;
}

int daa(cpu_t *cpu)
{

	return 4;
}

int jr_z_e8(cpu_t *cpu)
{
	int8_t offset = READ_BYTE(cpu->PC++);
	if (GET_FLAG(cpu, FLAG_Z)) {
		cpu->PC += offset;
		return 12;
	} else {
		return 8;
	}
}
int add_hl_hl(cpu_t *cpu)
{
	word val = GET_HL(cpu);
	word_add_helper(cpu, val);
	return 8;
}

int ld_a_hli(cpu_t *cpu)
{
	address HL_value = GET_HL(cpu);
	cpu->A = READ_BYTE(HL_value);
	SET_HL(cpu, HL_value + 1);
	return 8;
}

int dec_hl(cpu_t *cpu)
{
	word val = GET_HL(cpu);
	val--;
	SET_HL(cpu, val);
	return 8;
}

int inc_l(cpu_t *cpu)
{
	inc_helper(cpu, &cpu->L);
	return 4;
}

int dec_l(cpu_t *cpu)
{
	dec_helper(cpu, &cpu->L);
	return 4;
}

int ld_l_n8(cpu_t *cpu)
{
	cpu->L = READ_BYTE(cpu->PC++);
	return 8;
}

int cpl(cpu_t *cpu)
{
	cpu->A = ~cpu->A;
	SET_FLAG_VALUE(cpu, FLAG_N, 1);
	SET_FLAG_VALUE(cpu, FLAG_H, 1);
	return 4;
}

int jr_nc_e8(cpu_t *cpu)
{
	int8_t offset = READ_BYTE(cpu->PC);
	cpu->PC++;
	if (GET_FLAG(cpu, FLAG_C)) {
		return 8;
	} else {
		cpu->PC += offset;
		return 12;
	}
}

int ld_sp_n16(cpu_t *cpu)
{
	WRITE_WORD(cpu->SP, read_n16(cpu));
	return 12;
}

int ld_hld_a(cpu_t *cpu)
{
	byte HL_value = GET_HL(cpu);
	WRITE_WORD(cpu->A, GET_HL(cpu));
	SET_HL(cpu, HL_value - 1);
	return 8;
}

int inc_sp(cpu_t *cpu)
{
	cpu->SP++;
	return 8;
}

int inc_hl_mem(cpu_t *cpu)
{
	address addr = GET_HL(cpu);
	byte val = READ_BYTE(addr);
	inc_helper(cpu, &val);
	WRITE_BYTE(addr, val);
	return 12;
}

int dec_hl_mem(cpu_t *cpu)
{
	address addr = GET_HL(cpu);
	byte val = READ_BYTE(addr);
	dec_helper(cpu, &val);
	WRITE_BYTE(addr, val);
	return 12;
}

int ld_hl_n8(cpu_t *cpu)
{
	byte val = READ_BYTE(cpu->PC++);
	WRITE_BYTE(GET_HL(cpu), val);
	return 12;
}

int scf(cpu_t *cpu)
{
	CLEAR_FLAG(cpu, FLAG_H);
	CLEAR_FLAG(cpu, FLAG_N);
	SET_FLAG(cpu, FLAG_C);
	return 4;
}

int jr_c_e8(cpu_t *cpu)
{
	int8_t offset = READ_BYTE(cpu->PC);
	cpu->PC++;
	if (GET_FLAG(cpu, FLAG_C)) {
		cpu->PC += offset;
		return 12;
	} else {
		return 8;
	}
}

int add_hl_sp(cpu_t *cpu)
{
	word_add_helper(cpu, cpu->SP);
	return 8;
}

int ld_a_hld(cpu_t *cpu)
{
	address HL_value = GET_HL(cpu);
	cpu->A = READ_BYTE(HL_value);
	SET_HL(cpu, HL_value - 1);
	return 8;
}

int dec_sp(cpu_t *cpu)
{
	cpu->SP--;
	return 8;
}

int inc_a(cpu_t *cpu)
{
	inc_helper(cpu, &cpu->A);
	return 4;
}

int dec_a(cpu_t *cpu)
{
	dec_helper(cpu, &cpu->A);
	return 4;
}

int ld_a_n8(cpu_t *cpu)
{
	cpu->A = READ_BYTE(cpu->PC++);
	return 8;
}

int ccf(cpu_t *cpu)
{
	CLEAR_FLAG(cpu, FLAG_N);
	CLEAR_FLAG(cpu, FLAG_H);
	SET_FLAG_VALUE(cpu, FLAG_C, !GET_FLAG(cpu, FLAG_C));
	return 4;
}

void opcodes_00_3F_init(void)
{
	op_table[0x00] = nop;
	op_table[0x01] = ld_bc_n16;
	op_table[0x02] = ld_bc_a;
	op_table[0x03] = inc_bc;
	op_table[0x04] = inc_b;
	op_table[0x05] = dec_b;
	op_table[0x06] = ld_b_n8;
	op_table[0x07] = rlca;
	op_table[0x08] = ld_n16_sp;
	op_table[0x09] = add_hl_bc;
	op_table[0x0A] = ld_a_bc;
	op_table[0x0B] = dec_bc;
	op_table[0x0C] = inc_c;
	op_table[0x0D] = dec_c;
	op_table[0x0E] = ld_c_n8;
	op_table[0x0F] = rrca;
	op_table[0x10] = stop;
	op_table[0x11] = ld_de_n16;
	op_table[0x12] = ld_de_a;
	op_table[0x13] = inc_de;
	op_table[0x14] = inc_d;
	op_table[0x15] = dec_d;
	op_table[0x16] = ld_d_n8;
	op_table[0x17] = rla;
	op_table[0x18] = jr_e8;
	op_table[0x19] = add_hl_de;
	op_table[0x1A] = ld_a_de;
	op_table[0x1B] = dec_de;
	op_table[0x1C] = inc_e;
	op_table[0x1D] = dec_e;
	op_table[0x1E] = ld_e_n8;
	op_table[0x1F] = rra;
	op_table[0x20] = jr_nz_e8;
	op_table[0x21] = ld_hl_n16;
	op_table[0x22] = ld_hli_a;
	op_table[0x23] = inc_hl;
	op_table[0x24] = inc_h;
	op_table[0x25] = dec_h;
	op_table[0x26] = ld_h_n8;
	op_table[0x27] = daa;
	op_table[0x28] = jr_z_e8;
	op_table[0x29] = add_hl_hl;
	op_table[0x2A] = ld_a_hli;
	op_table[0x2B] = dec_hl;
	op_table[0x2C] = inc_l;
	op_table[0x2D] = dec_l;
	op_table[0x2E] = ld_l_n8;
	op_table[0x2F] = cpl;
	op_table[0x30] = jr_nc_e8;
	op_table[0x31] = ld_sp_n16;
	op_table[0x32] = ld_hld_a;
	op_table[0x33] = inc_sp;
	op_table[0x34] = inc_hl_mem;
	op_table[0x35] = dec_hl_mem;
	op_table[0x36] = ld_hl_n8;
	op_table[0x37] = scf;
	op_table[0x38] = jr_c_e8;
	op_table[0x39] = add_hl_sp;
	op_table[0x3A] = ld_a_hld;
	op_table[0x3B] = dec_sp;
	op_table[0x3C] = inc_a;
	op_table[0x3D] = dec_a;
	op_table[0x3E] = ld_a_n8;
	op_table[0x3F] = ccf;
}
