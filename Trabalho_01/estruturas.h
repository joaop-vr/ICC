#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdint.h>

struct operandos {
    double num;
    double anterior;
    double posterior;
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

/***************************
 * Stuct sistemaLinear corresponde a todos os componentes de um sistema linear AX = B de ordem N
 * 
 * N = int ordem
 * A = double** matriz
 * B = double* constantes
 * X = double* solucoes
 * 
 * O componente "struct sistemaLinear* backup" servirá para que possamos solucionar o sistema
 * mais de uma vez
 * 
 * O componente "double* residuos" será utilizado na hora de contabilizar 
 * o resíduo do sistema
 * 
****************************/
struct sistemaLinear {
    int ordem;
    double** matriz;        
    double* constantes;
    double* solucoes;
    double* residuos;
};

#endif