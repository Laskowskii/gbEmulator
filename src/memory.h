#ifndef MEMORY_H
#define MEMORY_H

#define RAM_SIZE 0x10000
#define ROM_BANK00_SIZE 0x3FFF + 1
#define ROM_BANKNN_SIZE 0x3FFF + 1

#define ROM_BANK00_START 0x0000 
#define ROM_BANK00_END 0x3FFF
#define ROM_BANK01_START 0x4000
#define ROM_BANK01_END 0x7FFF
#define VRAM_START 0x8000
#define VRAM_END 0x9FFF
#define SRAM_START 0xA000
#define SRAM_END 0xBFFF
#define WRAM_START 0xC000
#define WRAM_END 0xDFFF
#define ECHO_RAM_START 0xE000
#define ECHO_RAM_END 0xFDFF
#define OAM_START 0xFE00
#define OAM_END 0xFE9F
#define IO_REGISTERS_START 0xFF80
#define IO_REGISTERS_END 0xFF7F
#define HRAM_START 0xFF80
#define HRAM_END 0xFFFE

#define VRAM_SIZE ((VRAM_END-VRAM_START) + 1)
#define WRAM_SIZE ((WRAM_END-WRAM_START) + 1)
#define HRAM_SIZE ((HRAM_END-HRAM_START) + 1)
#define IO_REGISTERS_SIZE ((IO_REGISTERS_END-IO_REGISTERS_START) + 1)
#define OAM_SIZE ((OAM_END - OAM_SIZE) + 1)

#include <stdint.h>
#include <string.h>


typedef struct cpu_s cpu_t;

typedef struct memory_s
{
    uint8_t ram[RAM_SIZE];
}memory_t;


int loadRomToBank(cpu_t *cpu, uint8_t rom[]);
uint16_t readMemory16(cpu_t* cpu);
uint8_t readMemory8(cpu_t *cpu);

#endif