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

//0x21C
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
void ld_atBC_A(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.BC] = cpu->reg.A;
}

//0x12
void ld_atDE_A(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.DE] = cpu->reg.A;
}

//0x22
void ld_atHLinc_A(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.A;
   cpu->reg.HL++;
}

//0x32
void ld_atHLdec_A(cpu_t *cpu){
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
   if(HALF_CARRY_CHECK(cpu->reg.B, 1)){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.B++;
   if(cpu->reg.B == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
   resetFlag(cpu,N_FLAG);
}

//0x14
void inc_D(cpu_t *cpu){
   if(HALF_CARRY_CHECK(cpu->reg.D, 1)){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.D++;
   if(cpu->reg.D == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
   resetFlag(cpu,N_FLAG);
}

//0x24
void inc_H(cpu_t *cpu){
   if(HALF_CARRY_CHECK(cpu->reg.H, 1)){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.H++;
   if(cpu->reg.H == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
   resetFlag(cpu,N_FLAG);
}

//0x34
void inc_atHL(cpu_t *cpu){
   if(HALF_CARRY_CHECK(cpu->mem.ram[cpu->reg.HL], 1)){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->mem.ram[cpu->reg.HL]++;
   if(cpu->mem.ram[cpu->reg.HL] == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
   resetFlag(cpu,N_FLAG);
}

//0x0C
void inc_C(cpu_t *cpu){
   if(HALF_CARRY_CHECK(cpu->reg.C, 1)){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.C++;
   if(cpu->reg.C == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
   resetFlag(cpu,N_FLAG);
}

//0x1C
void inc_E(cpu_t *cpu){
   if(HALF_CARRY_CHECK(cpu->reg.E, 1)){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.E++;
   if(cpu->reg.E == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
   resetFlag(cpu,N_FLAG);
}

//0x2C
void inc_L(cpu_t *cpu){
   if(HALF_CARRY_CHECK(cpu->reg.L, 1)){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.L++;
   if(cpu->reg.L == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
   resetFlag(cpu,N_FLAG);
}

//0x3C
void inc_A(cpu_t *cpu){
   if(HALF_CARRY_CHECK(cpu->reg.A, 1)){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.A++;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
   resetFlag(cpu,N_FLAG);
}

//0x05 + 0x0D
//zrobic dec i te jebane half cary kurestwo


//0x06
void ld_B_n(cpu_t *cpu){
   cpu->reg.B = readMemory8(cpu);
}

//0x16
void ld_D_n(cpu_t *cpu){
   cpu->reg.D = readMemory8(cpu);
}

//0x26
void ld_H_n(cpu_t *cpu){
   cpu->reg.H = readMemory8(cpu);
}

//0x36
void ld_atHL_n(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = readMemory8(cpu);
}

//0x0E
void ld_C_n(cpu_t *cpu){
   cpu->reg.C = readMemory8(cpu);
}

//0x1E
void ld_E_n(cpu_t *cpu){
   cpu->reg.E = readMemory8(cpu);
}

//0x2E
void ld_L_n(cpu_t *cpu){
   cpu->reg.L = readMemory8(cpu);
}

//0x3E
void ld_A_n(cpu_t *cpu){
   cpu->reg.A = readMemory8(cpu);
}

//0x07
void rlca(cpu_t *cpu){
   uint8_t bit7;
   bit7 = cpu->reg.A & 0b10000000;
   bit7 >>= 7;
   cpu->reg.A <<= 1;
   cpu->reg.A |= bit7;
   resetFlag(cpu, Z_FLAG);
   resetFlag(cpu, N_FLAG);
   resetFlag(cpu, H_FLAG);
   if(bit7){
      setFlag(cpu, C_FLAG);
   }
   else{
      resetFlag(cpu, C_FLAG);
   }
}

//0x17
void rla(cpu_t *cpu){
   uint8_t bit7;
   bit7 = cpu->reg.A & 0b10000000;
   bit7 >>= 7;
   cpu->reg.A <<= 1;
   cpu->reg.A |= GET_CARRY_FLAG_VALUE; //carry flag location
   resetFlag(cpu, Z_FLAG);
   resetFlag(cpu, N_FLAG);
   resetFlag(cpu, H_FLAG);
   if(bit7){
      setFlag(cpu, C_FLAG);
   }
   else{
      resetFlag(cpu, C_FLAG);
   }
}

//0x0F
void rrca(cpu_t *cpu){
      uint8_t bit0;
      bit0 = cpu->reg.A & 0b00000001;
      cpu->reg.A >>= 1;
      cpu->reg.A |= (bit0 << 7);
      resetFlag(cpu, Z_FLAG);
      resetFlag(cpu, N_FLAG);
      resetFlag(cpu, H_FLAG);
      if(bit0){
         setFlag(cpu, C_FLAG);
      }
      else{
         resetFlag(cpu, C_FLAG);
      }
}

//0x1F
void rra(cpu_t *cpu){
      uint8_t bit0, cflag;
      cflag = GET_CARRY_FLAG_VALUE;
      bit0 = cpu->reg.A & 0b00000001;
      cpu->reg.A >>= 1;
      cpu->reg.A |= (cflag << 7);
      resetFlag(cpu, Z_FLAG);
      resetFlag(cpu, N_FLAG);
      resetFlag(cpu, H_FLAG);
      if(bit0){
         setFlag(cpu, C_FLAG);
      }
      else{
         resetFlag(cpu, C_FLAG);
      }
}

//0x27 todo

//0x37
void scf(cpu_t *cpu){
   resetFlag(cpu, N_FLAG);
   resetFlag(cpu, H_FLAG);
   setFlag(cpu, C_FLAG);
}

//0x08
//todo

//0x09
//todo

//0x0A
void ld_A_atBC(cpu_t *cpu){
   cpu->reg.A = cpu->mem.ram[cpu->reg.BC];
}

//0x1A
void ld_A_atDE(cpu_t *cpu){
   cpu->reg.A = cpu->mem.ram[cpu->reg.DE];
}

//0x2A
void ld_A_atHLinc(cpu_t *cpu){
   cpu->reg.A = cpu->mem.ram[cpu->reg.HL];
   cpu->reg.HL++;
}

//0x3A
void ld_A_atHLdec(cpu_t *cpu){
   cpu->reg.A = cpu->mem.ram[cpu->reg.HL];
   cpu->reg.HL--;
}

//0x0B
void dec_BC(cpu_t *cpu){
   cpu->reg.BC--;
}

//0x1B
void dec_DE(cpu_t *cpu){
   cpu->reg.DE--;
}

//0x2B
void dec_HL(cpu_t *cpu){
   cpu->reg.HL--;
}

//0x3B
void dec_SP(cpu_t *cpu){
   cpu->reg.SP--;
}