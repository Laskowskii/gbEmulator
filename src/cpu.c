#include "cpu.h"
#include "memory.h"
cpu_t init_cpu(uint8_t rom[]){
   cpu_t cpu;
   cpu.reg.PC = 0x0100; 
   loadRomToBank(&cpu, rom);
   fetch(&cpu);
}


void readOpcode(cpu_t* cpu, uint8_t opcode){
      switch (opcode)
      {
      //todo
      case 0x00: printf("nop"); break;
      case 0x01: printf("LD BC, %x",read16(cpu)); break;
      case 0x02: printf("nop"); break;
      case 0x03: printf("nop"); break;
      case 0x04: printf("nop"); break;
      case 0x05: printf("nop"); break;
      case 0x06: printf("nop"); break;
      case 0x07: printf("nop"); break;
      case 0x08: printf("nop"); break;
      case 0x09: printf("nop"); break;
      case 0x0A: printf("nop"); break;
      case 0x0B: printf("nop"); break;
      case 0x0E: printf("nop"); break;
      case 0x0F: printf("nop"); break;
      default:
         break;
      }
}

void fetch(cpu_t *cpu){
   uint16_t pc = cpu->reg.PC;
   if(pc >= 0x0000 && pc <= 0x3FFF){
      readOpcode(cpu,cpu->mem.ram[cpu->reg.PC]);
      readOpcode(cpu,cpu->mem.ram[cpu->reg.PC]);
      readOpcode(cpu,cpu->mem.ram[cpu->reg.PC]);
   }
   //remove this shit
}