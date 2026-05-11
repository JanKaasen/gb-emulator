#include "../include/opcodes.h"
#include "../include/opcodes_common.h"

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
}
int inc_e(cpu_t *cpu)
{
}
int dec_e(cpu_t *cpu)
{
}
int ld_e_n8(cpu_t *cpu)
{
}
int rra(cpu_t *cpu)
{
}
int jr_nz_e8(cpu_t *cpu)
{
}
int ld_hl_n16(cpu_t *cpu)
{
}
int ld_hli_a(cpu_t *cpu)
{
}
int inc_hl(cpu_t *cpu)
{
}
int inc_h(cpu_t *cpu)
{
}
int dec_h(cpu_t *cpu)
{
}
int ld_h_n8(cpu_t *cpu)
{
}
int daa(cpu_t *cpu)
{
}
int jr_z_e8(cpu_t *cpu)
{
}
int add_hl_hl(cpu_t *cpu)
{
}
int ld_a_hli(cpu_t *cpu)
{
}
int dec_hl(cpu_t *cpu)
{
}
int inc_l(cpu_t *cpu)
{
}
int dec_l(cpu_t *cpu)
{
}
int ld_l_n8(cpu_t *cpu)
{
}
int cpl(cpu_t *cpu)
{
}
int jr_nc_e8(cpu_t *cpu)
{
}
int ld_sp_n16(cpu_t *cpu)
{
}
int ld_hld_a(cpu_t *cpu)
{
}
int inc_sp(cpu_t *cpu)
{
}
int inc_hl_mem(cpu_t *cpu)
{
}
int dec_hl_mem(cpu_t *cpu)
{
}
int ld_hl_n8(cpu_t *cpu)
{
}
int scf(cpu_t *cpu)
{
}
int jr_c_e8(cpu_t *cpu)
{
}
int add_hl_sp(cpu_t *cpu)
{
}
int ld_a_hld(cpu_t *cpu)
{
}
int dec_sp(cpu_t *cpu)
{
}
int inc_a(cpu_t *cpu)
{
}
int dec_a(cpu_t *cpu)
{
}
int ld_a_n8(cpu_t *cpu)
{
}
int ccf(cpu_t *cpu)
{
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
