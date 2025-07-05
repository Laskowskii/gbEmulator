#include "memory.h"
#include "cpu.h"



uint16_t readMemory16(cpu_t *cpu){
   uint8_t byte1 = cpu->mem.ram[cpu->reg.PC];
   cpu->reg.PC++;
   uint8_t byte2 = cpu->mem.ram[cpu->reg.PC];
   cpu->reg.PC++;
   uint16_t value = (byte2 << 8) | byte1;
   return value;
}

uint8_t readMemory8(cpu_t *cpu){
   uint8_t byte = cpu->mem.ram[cpu->reg.PC];
   cpu->reg.PC++;
   return byte;
}


int loadRomToBank(cpu_t *cpu, uint8_t rom[]){
    memcpy(cpu->mem.ram, rom, ROM_BANK00_SIZE + ROM_BANKNN_SIZE);
}