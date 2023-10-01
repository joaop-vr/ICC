/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno:  , GRR:
 * 
****************************/

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdint.h>

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
 * Struct struct operandos corresponde a estrutura de dados que contém 
 * o valor dos pontos e o intervalo em que estão inseridos
 * 
 * num = número (double) passado pelo usuário
 * anterior = limite inferior do intervalo
 * posterior = limite superior do intervalo
 * 
****************************/
struct operandos {
    double num;
    double anterior;
    double posterior;
};


/***************************
 * Struct tabPontos corresponde á tabela de pontos com a qual trabalharemos
 * 
 * qntdPontos = quantidade de pontos da tabela
 * vetPontos = vetor com os pontos
 * 
 * O componente "struct operandos* vetPontos" está organizado de forma que:
 * X0 e Y0 estão nos indices 0 e 1 do vetor
 * X1 e Y1 estão nos indices 2 e 3 do vetor
 * X2 e Y2 estão nos indices 4 e 5 do vetor
 * (...)
 * Xi e Yi estão nos indices 2*i e 2*i+1
 * 
****************************/
struct tabPontos {
    int qntdPontos;
    struct operandos* vetPontos;
};


/***************************
 * Stuct ajustePol <AINDA EM DESENVOLVIMENTO>
 * 
****************************/
struct ajustePol {
    int grauPol;
    int qntdPontos;
    /*double** matriz;        
    double* constantes;
    double* solucoes;
    double* residuos;*/
    struct operandos** matriz;
    struct operandos* resultados;
    struct operandos* coeficientes;
    struct operandos* tabelaPontos;
};

#endif