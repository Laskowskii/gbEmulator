#include "memory.h"
#include "cpu.h"

int loadRomToBank(cpu_t *cpu, uint8_t rom[]){
    memcpy(cpu->mem.ram, rom, ROM_BANK00_SIZE);
}