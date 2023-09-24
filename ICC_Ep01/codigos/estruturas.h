#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdint.h>

struct operandos {
    float num;
    float anterior;
    float posterior;
};

typedef union
{
    int32_t i;
    float f;
    struct
    {   // Bitfields for exploration (32 bits = sign|exponent|mantissa)
        uint32_t mantissa : 23; // primeiros 23 bits (da direita para a esquerda)
        uint32_t exponent : 8;  // próximos 8 bits
        uint32_t sign : 1;      // proximo bit (ou seja, o bit mais a esquerda)
    } parts;
} Float_t;

#endif