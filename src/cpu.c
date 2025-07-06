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
   printf("nop\n");
}

//0x10
void stop(){
   printf("no stop i guess\n");
} 

//0x20
void jr_NZ_e(){
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

//0x70 todo
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
   printf("idk todo");
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
void ld_A_SP(cpu_t *cpu){
   uint16_t address = readMemory16(cpu);
   uint16_t sp = cpu->reg.SP;
   //todo write16
   cpu->mem.ram[address] = sp & 0xFF;
   address++;
   cpu->mem.ram[address] = (sp >> 8) & 0xFF;
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

