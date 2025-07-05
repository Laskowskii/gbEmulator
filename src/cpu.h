#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdio.h>
#include "memory.h"

#define Z_FLAG (1 << 7)
#define N_FLAG (1 << 6)
#define H_FLAG (1 << 5)
#define C_FLAG (1 << 4)

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
}registers_t;


typedef struct cpu_s
{
    registers_t reg;
    memory_t mem;
}cpu_t;


cpu_t init_cpu(uint8_t rom[]);
void readOpcode(cpu_t* cpu, uint8_t value);
void setFlag(cpu_t *cpu, uint8_t flag);
void resetFlag(cpu_t *cpu, uint8_t flag);

void ld_BC_n(cpu_t *cpu);

#endif