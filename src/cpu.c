#include "cpu.h"
#include "memory.h"


void setFlag(cpu_t *cpu, uint8_t flag){
   cpu->reg.F |= flag;
}

void resetFlag(cpu_t *cpu, uint8_t flag){
   cpu->reg.F &= ~flag;
}

//0x00
void nop(cpu_t *cpu){
   printf("nop\n");
}

//0x10
void stop(cpu_t *cpu){
   printf("no stop i guess\n");
} 

//0x20 todo
void jr_NZ_e(cpu_t *cpu){
   //idk;
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
   if(HALF_CARRY_CHECK_ADD(cpu->reg.B, 1)){
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
   if(HALF_CARRY_CHECK_ADD(cpu->reg.D, 1)){
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
   if(HALF_CARRY_CHECK_ADD(cpu->reg.H, 1)){
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
   if(HALF_CARRY_CHECK_ADD(cpu->mem.ram[cpu->reg.HL], 1)){
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
   if(HALF_CARRY_CHECK_ADD(cpu->reg.C, 1)){
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
   if(HALF_CARRY_CHECK_ADD(cpu->reg.E, 1)){
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
   if(HALF_CARRY_CHECK_ADD(cpu->reg.L, 1)){
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
   if(HALF_CARRY_CHECK_ADD(cpu->reg.A, 1)){
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

//0x05
void dec_B(cpu_t *cpu){
   if(HALF_CARRY_CHECK_SUB(cpu->reg.B, 1)){
      setFlag(cpu, H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.B--;
   if(cpu->reg.B == 0){
      setFlag(cpu, Z_FLAG);
   }
   else{
      resetFlag(cpu, Z_FLAG);
   }
   setFlag(cpu, N_FLAG);
}
//0x15
void dec_D(cpu_t *cpu){
   if(HALF_CARRY_CHECK_SUB(cpu->reg.D, 1)){
      setFlag(cpu, H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.D--;
   if(cpu->reg.D == 0){
      setFlag(cpu, Z_FLAG);
   }
   else{
      resetFlag(cpu, Z_FLAG);
   }
   setFlag(cpu, N_FLAG);
}

//0x25
void dec_H(cpu_t *cpu){
   if(HALF_CARRY_CHECK_SUB(cpu->reg.H, 1)){
      setFlag(cpu, H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.H--;
   if(cpu->reg.H == 0){
      setFlag(cpu, Z_FLAG);
   }
   else{
      resetFlag(cpu, Z_FLAG);
   }
   setFlag(cpu, N_FLAG);
}

//0x35
void dec_atHl(cpu_t *cpu){
   if(HALF_CARRY_CHECK_SUB(cpu->mem.ram[cpu->reg.HL], 1)){
      setFlag(cpu, H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->mem.ram[cpu->reg.HL]--;
   if(cpu->mem.ram[cpu->reg.HL] == 0){
      setFlag(cpu, Z_FLAG);
   }
   else{
      resetFlag(cpu, Z_FLAG);
   }
   setFlag(cpu, N_FLAG);
}

//0x0D
void dec_C(cpu_t *cpu){
   if(HALF_CARRY_CHECK_SUB(cpu->reg.C, 1)){
      setFlag(cpu, H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.C--;
   if(cpu->reg.C == 0){
      setFlag(cpu, Z_FLAG);
   }
   else{
      resetFlag(cpu, Z_FLAG);
   }
   setFlag(cpu, N_FLAG);
}

//0x1D
void dec_E(cpu_t *cpu){
   if(HALF_CARRY_CHECK_SUB(cpu->reg.E, 1)){
      setFlag(cpu, H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.E--;
   if(cpu->reg.E == 0){
      setFlag(cpu, Z_FLAG);
   }
   else{
      resetFlag(cpu, Z_FLAG);
   }
   setFlag(cpu, N_FLAG);
}

//0x2D
void dec_L(cpu_t *cpu){
   if(HALF_CARRY_CHECK_SUB(cpu->reg.L, 1)){
      setFlag(cpu, H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.L--;
   if(cpu->reg.L == 0){
      setFlag(cpu, Z_FLAG);
   }
   else{
      resetFlag(cpu, Z_FLAG);
   }
   setFlag(cpu, N_FLAG);
}

//0x3D
void dec_A(cpu_t *cpu){
   if(HALF_CARRY_CHECK_SUB(cpu->reg.A, 1)){
      setFlag(cpu, H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.A--;
   if(cpu->reg.A == 0){
      setFlag(cpu, Z_FLAG);
   }
   else{
      resetFlag(cpu, Z_FLAG);
   }
   setFlag(cpu, N_FLAG);
}

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

//0x40
void ld_B_B(cpu_t *cpu){
   cpu->reg.B = cpu->reg.B;
}

//0x41
void ld_B_C(cpu_t *cpu){
   cpu->reg.B = cpu->reg.C;
}

//0x42
void ld_B_D(cpu_t *cpu){
   cpu->reg.B = cpu->reg.D;
}

//0x43
void ld_B_E(cpu_t *cpu){
   cpu->reg.B = cpu->reg.E;
}

//0x44
void ld_B_H(cpu_t *cpu){
   cpu->reg.B = cpu->reg.H;
}

//0x45
void ld_B_L(cpu_t *cpu){
   cpu->reg.B = cpu->reg.L;
}

//0x46
void ld_B_atHL(cpu_t *cpu){
   cpu->reg.B = cpu->mem.ram[cpu->reg.HL];
}

//0x47
void ld_B_A(cpu_t *cpu){
   cpu->reg.B = cpu->reg.A;
}

//0x48
void ld_C_B(cpu_t *cpu){
   cpu->reg.C = cpu->reg.B;
}

//0x49
void ld_C_C(cpu_t *cpu){
   cpu->reg.C = cpu->reg.C;
}

//0x4A
void ld_C_D(cpu_t *cpu){
   cpu->reg.C = cpu->reg.D;
}

//0x4B
void ld_C_E(cpu_t *cpu){
   cpu->reg.C = cpu->reg.E;
}

//0x4C
void ld_C_H(cpu_t *cpu){
   cpu->reg.C = cpu->reg.H;
}

//0x4D
void ld_C_L(cpu_t *cpu){
   cpu->reg.C = cpu->reg.L;
}

//0x4E
void ld_C_atHL(cpu_t *cpu){
   cpu->reg.C = cpu->mem.ram[cpu->reg.HL];
}

//0x4F
void ld_C_A(cpu_t *cpu){
   cpu->reg.C = cpu->reg.A;
}

//0x50
void ld_D_B(cpu_t *cpu){
   cpu->reg.D = cpu->reg.B;
}

//0x51
void ld_D_C(cpu_t *cpu){
   cpu->reg.D = cpu->reg.C;
}

//0x52
void ld_D_D(cpu_t *cpu){
   cpu->reg.D = cpu->reg.D;
}

//0x53
void ld_D_E(cpu_t *cpu){
   cpu->reg.D = cpu->reg.E;
}

//0x54
void ld_D_H(cpu_t *cpu){
   cpu->reg.D = cpu->reg.H;
}

//0x55
void ld_D_L(cpu_t *cpu){
   cpu->reg.D = cpu->reg.L;
}

//0x56
void ld_D_atHL(cpu_t *cpu){
   cpu->reg.D = cpu->mem.ram[cpu->reg.HL];
}

//0x57
void ld_D_A(cpu_t *cpu){
   cpu->reg.D = cpu->reg.A;
}

//0x58
void ld_E_B(cpu_t *cpu){
   cpu->reg.E = cpu->reg.B;
}

//0x59
void ld_E_C(cpu_t *cpu){
   cpu->reg.E = cpu->reg.C;
}

//0x5A
void ld_E_D(cpu_t *cpu){
   cpu->reg.E = cpu->reg.D;
}

//0x5B
void ld_E_E(cpu_t *cpu){
   cpu->reg.E = cpu->reg.E;
}

//0x5C
void ld_E_H(cpu_t *cpu){
   cpu->reg.E = cpu->reg.H;
}

//0x5D
void ld_E_L(cpu_t *cpu){
   cpu->reg.E = cpu->reg.L;
}

//0x5E
void ld_E_atHL(cpu_t *cpu){
   cpu->reg.E = cpu->mem.ram[cpu->reg.HL];
}

//0x5F
void ld_E_A(cpu_t *cpu){
   cpu->reg.E = cpu->reg.A;
}


//0x60
void ld_H_B(cpu_t *cpu){
   cpu->reg.H = cpu->reg.B;
}

//0x61
void ld_H_C(cpu_t *cpu){
   cpu->reg.H = cpu->reg.C;
}

//0x62
void ld_H_D(cpu_t *cpu){
   cpu->reg.H = cpu->reg.D;
}

//0x63
void ld_H_E(cpu_t *cpu){
   cpu->reg.H = cpu->reg.E;
}

//0x64
void ld_H_H(cpu_t *cpu){
   cpu->reg.H = cpu->reg.H;
}

//0x65
void ld_H_L(cpu_t *cpu){
   cpu->reg.H = cpu->reg.L;
}

//0x66
void ld_H_atHL(cpu_t *cpu){
   cpu->reg.H = cpu->mem.ram[cpu->reg.HL];
}

//0x67
void ld_H_A(cpu_t *cpu){
   cpu->reg.H = cpu->reg.A;
}

//0x68
void ld_L_B(cpu_t *cpu){
   cpu->reg.L = cpu->reg.B;
}

//0x69
void ld_L_C(cpu_t *cpu){
   cpu->reg.L = cpu->reg.C;
}

//0x6A
void ld_L_D(cpu_t *cpu){
   cpu->reg.L = cpu->reg.D;
}

//0x6B
void ld_L_E(cpu_t *cpu){
   cpu->reg.L = cpu->reg.E;
}

//0x6C
void ld_L_H(cpu_t *cpu){
   cpu->reg.L = cpu->reg.H;
}

//0x6D
void ld_L_L(cpu_t *cpu){
   cpu->reg.L = cpu->reg.L;
}

//0x6E
void ld_L_atHL(cpu_t *cpu){
   cpu->reg.L = cpu->mem.ram[cpu->reg.HL];
}

//0x6F
void ld_L_A(cpu_t *cpu){
   cpu->reg.L = cpu->reg.B;
}

//0x70
void ld_atHL_B(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.B;
}

//0x71
void ld_atHL_C(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.C;
}

//0x72
void ld_atHL_D(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.D;
}

//0x73
void ld_atHL_E(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.E;
}

//0x74
void ld_atHL_H(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.H;
}

//0x75
void ld_atHL_L(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.L;
}

//0x76 todo
void HALT(cpu_t *cpu){
   printf("idk todo HALT");
}

//0x77
void ld_atHL_A(cpu_t *cpu){
   cpu->mem.ram[cpu->reg.HL] = cpu->reg.A;
}

//0x78
void ld_A_B(cpu_t *cpu){
   cpu->reg.A = cpu->reg.B;
}

//0x79
void ld_A_C(cpu_t *cpu){
   cpu->reg.A = cpu->reg.C;
}

//0x7A
void ld_A_D(cpu_t *cpu){
   cpu->reg.A = cpu->reg.D;
}

//0x7B
void ld_A_E(cpu_t *cpu){
   cpu->reg.A = cpu->reg.E;
}

//0x7C
void ld_A_H(cpu_t *cpu){
   cpu->reg.A = cpu->reg.H;
}

//0x7D
void ld_A_L(cpu_t *cpu){
   cpu->reg.A = cpu->reg.L;
}

//0x7E
void ld_A_atHL(cpu_t *cpu){
   cpu->reg.A = cpu->mem.ram[cpu->reg.HL];
}

//0x7F
void ld_A_A(cpu_t *cpu){
   cpu->reg.A = cpu->reg.A;
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

//0x2F
void cpl(cpu_t *cpu){
   cpu->reg.A = ~cpu->reg.A ;
   setFlag(cpu, N_FLAG);
   setFlag(cpu, H_FLAG);
}

//0x3F

void ccf(cpu_t *cpu){
   resetFlag(cpu,N_FLAG);
   resetFlag(cpu,H_FLAG);
   if(GET_CARRY_FLAG_VALUE){
      resetFlag(cpu,C_FLAG);
   }
   else{
      setFlag(cpu,C_FLAG);
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
void ld_a_SP(cpu_t *cpu){
   uint16_t address = readMemory16(cpu);
   uint16_t sp = cpu->reg.SP;
   cpu->mem.ram[address] = sp & 0xFF;
   address++;
   cpu->mem.ram[address] = (sp >> 8) & 0xFF;
}

//0x18
void JR_e(cpu_t *cpu){
   int8_t e = (int8_t) readMemory8(cpu);
   cpu->reg.PC += e;
}

//0x09
void add_HL_BC(cpu_t *cpu){
   if(((uint32_t)cpu->reg.HL + (uint32_t)cpu->reg.BC) > 0xFFFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu, C_FLAG);
   }
   if((cpu->reg.HL & 0x0FFF) + (cpu->reg.BC & 0x0FFF) > 0x0FFF){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.HL += cpu->reg.BC;
   resetFlag(cpu,N_FLAG);
}

//0x19
void add_HL_DE(cpu_t *cpu){
   if(((uint32_t)cpu->reg.HL + (uint32_t)cpu->reg.DE) > 0xFFFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu, C_FLAG);
   }
   if((cpu->reg.HL & 0x0FFF) + (cpu->reg.DE & 0x0FFF) > 0x0FFF){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.HL += cpu->reg.DE;
   resetFlag(cpu,N_FLAG);
}

//0x29
void add_HL_HL(cpu_t *cpu){
   if(((uint32_t)cpu->reg.HL + (uint32_t)cpu->reg.HL) > 0xFFFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu, C_FLAG);
   }
   if((cpu->reg.HL & 0x0FFF) + (cpu->reg.HL & 0x0FFF) > 0x0FFF){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.HL += cpu->reg.HL;
   resetFlag(cpu,N_FLAG);
}

//0x39
void add_HL_SP(cpu_t *cpu){
   if(((uint32_t)cpu->reg.HL + (uint32_t)cpu->reg.SP) > 0xFFFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu, C_FLAG);
   }
   if((cpu->reg.HL & 0x0FFF) + (cpu->reg.SP & 0x0FFF) > 0x0FFF){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }
   cpu->reg.HL += cpu->reg.SP;
   resetFlag(cpu,N_FLAG);
}

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

//0x80
void add_A_B(cpu_t *cpu){
   if((cpu->reg.A & 0x0F) + (cpu->reg.B & 0x0F) > 0x0F){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }

   if(cpu->reg.A + cpu->reg.B > 0xFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   resetFlag(cpu,N_FLAG);
   cpu->reg.A += cpu->reg.B;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x81
void add_A_C(cpu_t *cpu){
   if((cpu->reg.A & 0x0F) + (cpu->reg.C & 0x0F) > 0x0F){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }

   if(cpu->reg.A + cpu->reg.C > 0xFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   resetFlag(cpu,N_FLAG);
   cpu->reg.A += cpu->reg.C;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x82
void add_A_D(cpu_t *cpu){
   if((cpu->reg.A & 0x0F) + (cpu->reg.D & 0x0F) > 0x0F){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }

   if(cpu->reg.A + cpu->reg.D > 0xFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   resetFlag(cpu,N_FLAG);
   cpu->reg.A += cpu->reg.D;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x83
void add_A_E(cpu_t *cpu){
   if((cpu->reg.A & 0x0F) + (cpu->reg.E & 0x0F) > 0x0F){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }

   if(cpu->reg.A + cpu->reg.E > 0xFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   resetFlag(cpu,N_FLAG);
   cpu->reg.A += cpu->reg.E;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x84
void add_A_H(cpu_t *cpu){
   if((cpu->reg.A & 0x0F) + (cpu->reg.H & 0x0F) > 0x0F){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }

   if(cpu->reg.A + cpu->reg.H > 0xFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   resetFlag(cpu,N_FLAG);
   cpu->reg.A += cpu->reg.H;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x85
void add_A_L(cpu_t *cpu){
   if((cpu->reg.A & 0x0F) + (cpu->reg.L & 0x0F) > 0x0F){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }

   if(cpu->reg.A + cpu->reg.L > 0xFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   resetFlag(cpu,N_FLAG);
   cpu->reg.A += cpu->reg.L;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x86
void add_A_atHL(cpu_t *cpu){
   uint8_t Hlval = cpu->mem.ram[cpu->reg.HL];
   if((cpu->reg.A & 0x0F) + (Hlval & 0x0F) > 0x0F){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }

   if(cpu->reg.A + Hlval > 0xFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   resetFlag(cpu,N_FLAG);
   cpu->reg.A += Hlval;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x87
void add_A_A(cpu_t *cpu){
   if((cpu->reg.A & 0x0F) + (cpu->reg.A & 0x0F) > 0x0F){
      setFlag(cpu,H_FLAG);
   }
   else{
      resetFlag(cpu,H_FLAG);
   }

   if(cpu->reg.A + cpu->reg.A > 0xFF){
      setFlag(cpu,C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   resetFlag(cpu,N_FLAG);
   cpu->reg.A += cpu->reg.A;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x90
void sub_A_B(cpu_t *cpu){
   setFlag(cpu,N_FLAG);
   if((cpu->reg.A & 0x0F) < (cpu->reg.B & 0x0F)){
      setFlag(cpu, H_FLAG);
   } 
   else {
      resetFlag(cpu, H_FLAG);
   }
   if(cpu->reg.A < cpu->reg.B){
      setFlag(cpu, C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   cpu->reg.A -= cpu->reg.B;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x91
void sub_A_C(cpu_t *cpu){
   setFlag(cpu,N_FLAG);
   if((cpu->reg.A & 0x0F) < (cpu->reg.C & 0x0F)){
      setFlag(cpu, H_FLAG);
   } 
   else {
      resetFlag(cpu, H_FLAG);
   }
   if(cpu->reg.A < cpu->reg.C){
      setFlag(cpu, C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   cpu->reg.A -= cpu->reg.C;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x92
void sub_A_D(cpu_t *cpu){
   setFlag(cpu,N_FLAG);
   if((cpu->reg.A & 0x0F) < (cpu->reg.D & 0x0F)){
      setFlag(cpu, H_FLAG);
   } 
   else {
      resetFlag(cpu, H_FLAG);
   }
   if(cpu->reg.A < cpu->reg.D){
      setFlag(cpu, C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   cpu->reg.A -= cpu->reg.D;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x93
void sub_A_E(cpu_t *cpu){
   setFlag(cpu,N_FLAG);
   if((cpu->reg.A & 0x0F) < (cpu->reg.E & 0x0F)){
      setFlag(cpu, H_FLAG);
   } 
   else {
      resetFlag(cpu, H_FLAG);
   }
   if(cpu->reg.A < cpu->reg.E){
      setFlag(cpu, C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   cpu->reg.A -= cpu->reg.E;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x94
void sub_A_H(cpu_t *cpu){
   setFlag(cpu,N_FLAG);
   if((cpu->reg.A & 0x0F) < (cpu->reg.H & 0x0F)){
      setFlag(cpu, H_FLAG);
   } 
   else {
      resetFlag(cpu, H_FLAG);
   }
   if(cpu->reg.A < cpu->reg.H){
      setFlag(cpu, C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   cpu->reg.A -= cpu->reg.H;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x95
void sub_A_L(cpu_t *cpu){
   setFlag(cpu,N_FLAG);
   if((cpu->reg.A & 0x0F) < (cpu->reg.L & 0x0F)){
      setFlag(cpu, H_FLAG);
   } 
   else {
      resetFlag(cpu, H_FLAG);
   }
   if(cpu->reg.A < cpu->reg.L){
      setFlag(cpu, C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   cpu->reg.A -= cpu->reg.L;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}

//0x96
void sub_A_atHL(cpu_t *cpu){
   setFlag(cpu,N_FLAG);
   if((cpu->reg.A & 0x0F) < (cpu->reg.E & 0x0F)){
      setFlag(cpu, H_FLAG);
   } 
   else {
      resetFlag(cpu, H_FLAG);
   }
   if(cpu->reg.A < cpu->reg.E){
      setFlag(cpu, C_FLAG);
   }
   else{
      resetFlag(cpu,C_FLAG);
   }
   cpu->reg.A -= cpu->reg.E;
   if(cpu->reg.A == 0){
      setFlag(cpu,Z_FLAG);
   }
   else{
      resetFlag(cpu,Z_FLAG);
   }
}


instruction_t instructions[256] = {
   {"nop", nop, 4},
   {"LD BC, n16", ld_BC_n, 12},
   {"LD [BC], A", ld_atBC_A, 8},
   {"INC BC", inc_BC, 8},
   {"INC B", inc_B, 4},
   {"DEC_B", dec_B,4},
   {"LD B, n8", ld_B_n, 8},
   {"RLCA", rlca, 4},
   {"LD[a16], SP", ld_a_SP, 20},
   {"ADD HL, BC", add_HL_BC, 8},
   {"LD A, [BC]",ld_A_atBC, 8},
   {"DEC BC",dec_BC, 8},
   {"INc C", inc_C, 4},
   {"DEC C", dec_C, 4},
   {"LD C, n8", ld_C_n, 8},
   {"RRCA", rrca, 4},
   {"stop", stop, 4},
   {"LD DE, n16", ld_DE_n, 12},
   {"LD [DE], A", ld_atDE_A, 8},
   {"INC DE", inc_DE, 8},
   {"INC D", inc_D, 4},
   {"DEC D", dec_C, 4},
   {"LD D, n8", ld_D_n, 8},
   {"RLA", rla, 4},
   {"JR e8", JR_e, 12},
   {"ADD HL, DE", add_HL_DE, 8},
   {"LD A, [DE]", ld_A_atDE, 8},
   {"DEC DE", dec_DE, 8},
   {"INC E", inc_B, 4},
   {"DEC E", dec_E, 4},
   {"LD E, n8", ld_E_n, 8},
   {"RRA", rra, 4},
   {"JR NZ, e8", jr_NZ_e, 12 /*todo 12/8*/},
   {"LD HL, n16", ld_HL_n, 12},
   {"LD[HL+], A", ld_atHLinc_A, 8},
   {"INC HL", inc_HL, 8},
   {"INC H", inc_H, 4},
   {"DEC H", dec_H, 4},
   {"LD H, n8", ld_H_n, 8},
   {"DAA", /*todo*/nop, 4},
   {"JR Z, e8", /*todo*/nop, 12/8},
   {"ADD HL, HL", add_HL_HL, 8},
   {"LD A, [hl+]", ld_A_atHLinc, 8},
   {"DEC HL", dec_HL, 8},
   {"INC L", inc_L, 4},
   {"DEC L", dec_L, 4},
   {"LD L, n8", ld_L_n, 8},
   {"CPL", cpl, 4},
   {"JR NC, e8", /*todo*/nop, 12/8},
   {"LD SP, n16", ld_SP_n, 12},
   {"LD[hl-], A", ld_atHLdec_A, 8},
   {"INC SP", inc_SP, 8},
   {"INC [HL]", inc_atHL, 12},
   {"DEC [Hl]", dec_atHl, 12},
   {"LD [hl], n8", ld_atHL_n, 12},
   {"SCF", scf, 4},
   {"JR c, e8", /*todo*/nop, 12/8},
   {"ADD HL, SP", add_HL_SP, 8},
   {"LD a, [hl-]", ld_A_atHLdec, 8},
   {"DEC SP", dec_SP, 8},
   {"INC A", inc_A, 4},
   {"DEC A", dec_A, 4},
   {"LD A, n8", ld_A_n, 8},
   {"CCF", ccf, 4},
   {"LD B, B", ld_B_B, 4},
   {"LD B, C", ld_B_C, 4},
   {"LD B, D", ld_B_D, 4},
   {"LD B, E", ld_B_E, 4},
   {"LD B, H", ld_B_H, 4},
   {"LD B, L", ld_B_L, 4},
   {"LD B, [hl]", ld_B_atHL, 8},
   {"LD B, A", ld_B_A, 4},
   {"LD C, B", ld_C_B, 4},
   {"LD C, C", ld_C_C, 4},
   {"LD C, D", ld_C_D, 4},
   {"LD C, E", ld_C_E, 4},
   {"LD C, H", ld_C_H, 4},
   {"LD C, L", ld_C_L, 4},
   {"LD C, [hl]", ld_C_atHL, 8},
   {"LD C, A", ld_C_A, 4},
   {"LD D, B", ld_D_B, 4},
   {"LD D, C", ld_D_C, 4},
   {"LD D, D", ld_D_D, 4},
   {"LD D, E", ld_D_E, 4},
   {"LD D, H", ld_D_H, 4},
   {"LD D, L", ld_D_L, 4},
   {"LD D, [hl]", ld_D_atHL, 8},
   {"LD D, A", ld_D_A, 4},
   {"LD E, B", ld_E_B, 4},
   {"LD E, C", ld_E_C, 4},
   {"LD E, D", ld_E_D, 4},
   {"LD E, E", ld_E_E, 4},
   {"LD E, H", ld_E_H, 4},
   {"LD E, L", ld_E_L, 4},
   {"LD E, [hl]", ld_E_atHL, 8},
   {"LD E, A", ld_E_A, 4},
   {"LD H, B", ld_H_B, 4},
   {"LD H, C", ld_H_C, 4},
   {"LD H, D", ld_H_D, 4},
   {"LD H, E", ld_H_E, 4},
   {"LD H, H", ld_H_H, 4},
   {"LD H, L", ld_H_L, 4},
   {"LD H, [hl]", ld_H_atHL, 8},
   {"LD H, A", ld_H_A, 4},
   {"LD L, B", ld_L_B, 4},
   {"LD L, C", ld_L_C, 4},
   {"LD L, D", ld_L_D, 4},
   {"LD L, E", ld_L_E, 4},
   {"LD L, H", ld_L_H, 4},
   {"LD L, L", ld_L_L, 4},
   {"LD L, [hl]", ld_L_atHL, 8},
   {"LD L, A", ld_L_A, 4},
   {"LD [hl], B", ld_atHL_B, 8},
   {"LD [hl], C", ld_atHL_C, 8},
   {"LD [hl], D", ld_atHL_D, 8},
   {"LD [hl], E", ld_atHL_E, 8},
   {"LD [hl], H", ld_atHL_H, 8},
   {"LD [hl], L", ld_atHL_L, 8},
   {"HALT", HALT, 8},
   {"LD [hl], A", ld_atHL_A, 8},
   {"LD A, B", ld_A_B, 4},
   {"LD A, C", ld_A_C, 4},
   {"LD A, D", ld_A_D, 4},
   {"LD A, E", ld_A_E, 4},
   {"LD A, H", ld_A_H, 4},
   {"LD A, L", ld_A_L, 4},
   {"LD A, [hl]", ld_A_atHL, 8},
   {"LD A, A", ld_A_A, 4},
   {"ADD A, B", add_A_B, 4},
   {"ADD A, C", add_A_C, 4},
   {"ADD A, D", add_A_D, 4},
   {"ADD A, E", add_A_E, 4},
   {"ADD A, H", add_A_H, 4},
   {"ADD A, L", add_A_L, 4},
   {"ADD A, [hl]", add_A_atHL, 8},
   {"ADD A, A", add_A_A, 4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
   {"unknown",nop,4},
};

cpu_t init_cpu(uint8_t rom[]){
   cpu_t *cpu = malloc(sizeof(cpu_t));
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
   while (1)
   {
      uint8_t opcode = readMemory8(cpu);
      readOpcode(cpu, opcode);
   }
}

void readOpcode(cpu_t* cpu, uint8_t opcode){
   printf("%x\t",opcode);
   instructions[opcode].function(cpu);
   printf("\n");
}
