#ifndef MEMORY_H
#define MEMORY_H

#define ROM_BANK00_SIZE 0x3FFF + 1
#define VRAM_SIZE 0x2000 + 1
#include <stdint.h>
#include <string.h>


typedef struct cpu_s cpu_t;

typedef struct memory_s
{
    uint8_t romBank00[ROM_BANK00_SIZE];
    uint8_t romBank01[0x3FFF + 1];
    uint8_t vram[VRAM_SIZE];
    uint8_t wram[VRAM_SIZE];
}memory_t;

int loadRomToBank(cpu_t *cpu, uint8_t rom[]);

#endif