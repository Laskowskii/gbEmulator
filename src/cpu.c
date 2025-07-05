#include "cpu.h"
#include "memory.h"
cpu_t init_cpu(uint8_t rom[]){
   cpu_t *cpu;
   cpu->reg.A = 0x01;
   cpu->reg.F = 0x00;
   setFlag(cpu, Z_FLAG);
   cpu->reg.B = 0x00;
   cpu->reg.C = 0x13;
   cpu->reg.D = 0x00;
   cpu->reg.E = 0xD8;
   cpu->reg.H = 0x01;
   cpu->reg.L = 0x4D;
   cpu->reg.PC = 0x0100; 
   cpu->reg.SP = 0xFFFE;

   loadRomToBank(cpu, rom);
   uint8_t opcode = readMemory8(cpu);
   readOpcode(cpu, opcode);
}

void setFlag(cpu_t *cpu, uint8_t flag){
   cpu->reg.F |= flag;
}

void resetFlag(cpu_t *cpu, uint8_t flag){
   cpu->reg.F &= ~flag;
}

void readOpcode(cpu_t* cpu, uint8_t opcode){
      switch (opcode)
      {
      //todo
      case 0x00: printf("nop");  break;;
      case 0x01: printf("LD BC, n16"); ld_BC_n(cpu); printf("%x",cpu->reg.BC); break;
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
         printf("undefined func: %02X",opcode);
         break;
      }
      printf("\n");

}


//0x00
void nop(){
   printf("lol");
}

//0x01
void ld_BC_n(cpu_t *cpu){
   uint16_t n = readMemory16(cpu);
   cpu->reg.BC = n;
}

//0x11
void ld_DE_n(cpu_t *cpu){
   uint16_t n = readMemory16(cpu);
   cpu->reg.DE = n;
}

//0x21
void ld_HL_n(cpu_t *cpu){
   uint16_t n = readMemory16(cpu);
   cpu->reg.HL = n;
}

//0x31
void ld_SP_n(cpu_t *cpu){
   uint16_t n = readMemory16(cpu);
   cpu->reg.SP = n;
}

//0x02
void ld_BC_A(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.BC] = cpu->reg.A;
}

//0x12
void ld_DE_A(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.DE] = cpu->reg.A;
}

//0x22
void ld_HLinc_A(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.A;
   cpu->reg.HL++;
}

//0x32
void ld_HLdec_A(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.A;
   cpu->reg.HL--;
}

//0x03
void inc_BC(cpu_t *cpu){
   cpu->reg.BC++;
}

//0x13
void inc_DE(cpu_t *cpu){
   cpu->reg.DE++;
}

//0x23
void inc_HL(cpu_t *cpu){
   cpu->reg.HL++;
}

//0x33
void inc_SP(cpu_t *cpu){
   cpu->reg.SP++;
}

//0x04
void inc_B(cpu_t *cpu){
   cpu->reg.B++;
   if(cpu->reg.B == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
   resetFlag(cpu,N_FLAG);
   //todo half carry
}

