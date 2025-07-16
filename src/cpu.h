#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"


#define Z_FLAG (1 << 7)
#define N_FLAG (1 << 6)
#define H_FLAG (1 << 5)
#define C_FLAG (1 << 4)

#define HALF_CARRY_CHECK_ADD(deafultValue,addValue) (((deafultValue & 0x0F) + (addValue & 0x0F)) > 0x0F)
#define HALF_CARRY_CHECK_SUB(deafultValue,addValue) (deafultValue & 0x0F) < (addValue & 0x0F)

#define GET_CARRY_FLAG_VALUE ((cpu->reg.F & 0b00010000) >> 4)


typedef struct
{
    union
    {
        struct
        {
            uint8_t A;
            uint8_t F;
        };    
        uint16_t AF;
    };
    union
    {
        uint16_t BC;
        struct
        {
            uint8_t B;
            uint8_t C;
        };  
    };
    union
    {
        uint16_t DE;
        struct
        {
            uint8_t D;
            uint8_t E;
        };  
    };
    union
    {
        uint16_t HL;
        struct
        {
            uint8_t H;
            uint8_t L;
        };  
    };
    uint16_t SP;
    uint16_t PC;
    uint8_t IR;
    uint8_t IE;
}registers_t;


typedef struct cpu_s
{
    registers_t reg;
    memory_t mem;
}cpu_t;


typedef struct
{
    char name[20];
    void (*function)(cpu_t *cpu);
    uint8_t tCycles;
}instruction_t;


cpu_t init_cpu(uint8_t rom[]);
void readOpcode(cpu_t* cpu, uint8_t value);
void setFlag(cpu_t *cpu, uint8_t flag);
void resetFlag(cpu_t *cpu, uint8_t flag);

void ld_BC_n(cpu_t *cpu);



#endif