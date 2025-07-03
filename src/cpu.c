#include "cpu.h"
#include "memory.h"
cpu_t init_cpu(uint8_t rom[]){
   cpu_t cpu;
   cpu.reg.PC = 0x0100; 
   loadRomToBank(&cpu, rom);
   fetch(&cpu);
}

void inc16BitRegister(uint16_t *reg){
   *reg++;
}

void dec16BitRegister(uint16_t *reg){
   *reg--;
}

void LD_into16BitRegister(char *reg,cpu_t *cpu ,uint16_t value){
   if(strcmp(reg, "BC")){
      cpu->reg.BC = value;
   }
}

void readOpcode(cpu_t* cpu, uint8_t opcode){
      switch (opcode)
      {
      //todo
      case 0x00: printf("nop");  break;;
      case 0x01: printf("LD BC, n16"); LD_into16BitRegister("BC",cpu, read16(cpu)); printf("%x",cpu->reg.BC); break;
      case 0x02: printf("LD [BC], A"); break;
      case 0x03: printf("INC BC"); break;
      case 0x04: printf("INC B"); break;
      case 0x05: printf("DEC B"); break;
      case 0x06: printf("LD B, n8"); break;
      case 0x07: printf("RLCA"); break;
      case 0x08: printf("LD [a16], SP"); break;
      case 0x09: printf("ADD HL BC"); break;
      case 0x0A: printf("LD A [BC]"); break;
      case 0x0B: printf("DEC BC"); break;
      case 0x0C: printf("INC C"); break;
      case 0x0D: printf("DEC C"); break;
      case 0x0E: printf("LD, C, n8"); break;
      case 0x0F: printf("RRCA"); break;
      default:
         printf("undefined func");
         break;
      }
      printf("\n");
      cpu->reg.PC++;
}

void fetch(cpu_t *cpu){
   uint16_t pc = cpu->reg.PC;
   readOpcode(cpu,cpu->mem.ram[cpu->reg.PC]);
   readOpcode(cpu,cpu->mem.ram[cpu->reg.PC]);
   readOpcode(cpu,cpu->mem.ram[cpu->reg.PC]);
   readOpcode(cpu,cpu->mem.ram[cpu->reg.PC]);
   readOpcode(cpu,cpu->mem.ram[cpu->reg.PC]);
   //remove this shit
}