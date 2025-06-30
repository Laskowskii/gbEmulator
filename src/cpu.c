#include "cpu.h"
#include "memory.h"
cpu_t init_cpu(uint8_t rom[]){
   cpu_t cpu;
   cpu.reg.PC = 0x0100; 
   loadRomToBank(&cpu, rom);
}