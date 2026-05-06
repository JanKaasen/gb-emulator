#include "../include/memory.h"
#include "../include/common.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

bool memory_init(memory_system_t *mem_sys)
{
	if (mem_sys == NULL) {
		printf("Cannot initialize NULL memory system");
		return false;
	}

	memset(mem_sys->rom, 0x00, ROM_SIZE);
	memset(mem_sys->vram, 0x00, VRAM_SIZE);
	memset(mem_sys->wram, 0x00, WRAM_SIZE);
	memset(mem_sys->oam, 0x00, OAM_SIZE);
	memset(mem_sys->io_registers, 0x00, IO_REGISTERS_SIZE);
	memset(mem_sys->hram, 0x00, HRAM_SIZE);
	mem_sys->interrupt_enable = 0x00;
	mem_sys->rom_loaded = false;

	return true;
}

void memory_cleanup(memory_system_t *mem_sys)
{
	if (mem_sys == NULL) {
		printf("ERROR: CANNOT CLEANUP NULL MEMORY SYSTEM\n");
		return;
	}

	memset(mem_sys->rom, 0x00, ROM_SIZE);
	memset(mem_sys->vram, 0x00, VRAM_SIZE);
	memset(mem_sys->wram, 0x00, WRAM_SIZE);
	memset(mem_sys->oam, 0x00, OAM_SIZE);
	memset(mem_sys->io_registers, 0x00, IO_REGISTERS_SIZE);
	memset(mem_sys->hram, 0x00, HRAM_SIZE);
	mem_sys->interrupt_enable = 0x00;
	mem_sys->rom_loaded = false;

	printf("Memory cleaned up successfully\n");
}

static byte *memory_get_pointer(memory_system_t *mem_sys, address addr)
{
	if (addr >= ROM_START && addr <= ROM_END) {
		return &mem_sys->rom[addr - ROM_START];
	}
	if (addr >= VRAM_START && addr <= VRAM_END) {
		return &mem_sys->vram[addr - VRAM_START];
	}
	if (addr >= WRAM_START && addr <= WRAM_END) {
		return &mem_sys->wram[addr - WRAM_START];
	}
	if (addr >= OAM_START && addr <= OAM_END) {
		return &mem_sys->oam[addr - OAM_START];
	}
	if (addr >= IO_REGISTERS_START && addr <= IO_REGISTERS_END) {
		return &mem_sys->io_registers[addr - IO_REGISTERS_START];
	}
	if (addr >= HRAM_START && addr <= HRAM_END) {
		return &mem_sys->hram[addr - HRAM_START];
	}
	return NULL;
}

byte memory_read_byte(memory_system_t *mem_sys, address addr)
{
	assert(mem_sys != NULL);

	if (addr == INTERRUPT_ENABLE_REGISTER) {
		return mem_sys->interrupt_enable;
	}

	if (addr >= ECHO_RAM_START && addr <= ECHO_RAM_END) {
		return memory_read_byte(mem_sys, addr - 0x2000);
	}

	if (addr >= PROHIBITED_START && addr <= PROHIBITED_END) {
		return 0xFF;
	}

	byte *ptr = memory_get_pointer(mem_sys, addr);
	return ptr ? *ptr : 0xFF;
}

void memory_write_byte(memory_system_t *mem_sys, address addr, byte value)
{
	assert(mem_sys != NULL);

	if (addr == INTERRUPT_ENABLE_REGISTER) {
		mem_sys->interrupt_enable = value;
		return;
	}

	if (addr >= ECHO_RAM_START && addr <= ECHO_RAM_END) {
		memory_write_byte(mem_sys, addr - 0x2000, value);
		return;
	}

	if (addr >= ROM_START && addr <= ROM_END)
		return;

	byte *ptr = memory_get_pointer(mem_sys, addr);
	if (ptr) {
		*ptr = value;
	}
}

word memory_read_word(memory_system_t *mem_sys, address addr)
{
	byte low_byte = memory_read_byte(mem_sys, addr);
	byte high_byte = memory_read_byte(mem_sys, addr + 1);

	return low_byte | (high_byte << 8);
}

void memory_write_word(memory_system_t *mem_sys, address addr, word value)
{
	byte low_byte = value & 0xFF;
	byte high_byte = (value >> 8) & 0xFF;

	memory_write_byte(mem_sys, addr, low_byte);
	memory_write_byte(mem_sys, addr + 1, high_byte);
}

bool memory_is_valid_address(address addr)
{
	if (addr >= PROHIBITED_START && addr <= PROHIBITED_END) {
		return false;
	}

	return addr <= 0xFFFF;
}

const char *memory_get_region_name(address addr)
{
	if (addr >= ROM_START && addr <= ROM_END) {
		return "ROM";
	}
	if (addr >= VRAM_START && addr <= VRAM_END) {
		return "VRAM";
	}
	if (addr >= WRAM_START && addr <= WRAM_END) {
		return "WRAM";
	}
	if (addr >= ECHO_RAM_START && addr <= ECHO_RAM_END) {
		return "Echo RAM";
	}
	if (addr >= OAM_START && addr <= OAM_END) {
		return "OAM";
	}
	if (addr >= PROHIBITED_START && addr <= PROHIBITED_END) {
		return "Prohibited";
	}
	if (addr >= IO_REGISTERS_START && addr <= IO_REGISTERS_END) {
		return "IO";
	}
	if (addr >= HRAM_START && addr <= HRAM_END) {
		return "HRAM";
	}
	if (addr == INTERRUPT_ENABLE_REGISTER) {
		return "IE";
	}
	return "Invalid";
}
void memory_dump_region(memory_system_t *mem_sys, address start, address end)
{
	if (mem_sys == NULL) {
		printf("Error: Cannot dump memory with NULL memory system\n");
		return;
	}

	if (start > end) {
		printf("Error: Start address (0x%04X) > end address (0x%04X)\n",
		       start, end);
		return;
	}

	printf("Memory dump from 0x%04X to 0x%04X (%s):\n", start, end,
	       memory_get_region_name(start));
	printf("Address  : 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | "
	       "ASCII\n");
	printf("---------|------------------------------------------------|----"
	       "------------\n");

	for (address addr = start; addr <= end; addr += 16) {
		printf("0x%04X : ", addr);

		for (int offset = 0; offset < 16 && (addr + offset) <= end;
		     offset++) {
			byte value = memory_read_byte(mem_sys, addr + offset);
			printf("%02X ", value);
		}

		int bytes_in_row = (end >= addr + 15) ? 16 : (end - addr + 1);
		for (int i = bytes_in_row; i < 16; i++) {
			printf("   ");
		}

		printf("| ");

		for (int offset = 0; offset < 16 && (addr + offset) <= end;
		     offset++) {
			byte value = memory_read_byte(mem_sys, addr + offset);
			if (value >= 32 && value <= 126) {
				printf("%c", value);
			} else {
				printf(".");
			}
		}

		printf("\n");
	}
	printf("\n");
}

/**
 * @brief loads rom to ROM addresses in memory
 *
 * @param mem_sys memory system to load rom into
 * @param filename file name for rom
 * @return true if rom loaded to memory else false
 */
bool memory_load_rom(memory_system_t *mem_sys, const char *filename)
{
	if (mem_sys == NULL || filename == NULL) {
		printf("ERROR: INVALID PARAMETERS FOR LOADING ROM\n");
		return false;
	}

	FILE *rom_file = fopen(filename, "rb");
	if (rom_file == NULL) {
		printf("ERROR: COULD NOT READ ROM FILE '%s' \n", filename);
		return false;
	}

	size_t bytes_read = fread(mem_sys->rom, 1, ROM_SIZE, rom_file);
	fclose(rom_file);

	if (bytes_read == 0) {
		printf("ERROR: FAILED TO READ ROM DATA\n");
		return false;
	}

	mem_sys->rom_loaded = true;
	printf("ROM LOADED SUCCESSFULLY\n");
	return true;
}
