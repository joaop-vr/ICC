/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
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
 * Struct struct operandos corresponde à estrutura de dados que contém 
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
 * Struct ajustePol corresponde à estrutura de dados que engloba todos os vetores e matrizes que utilizamos 
 * para a implementação do método dos Mínimos Quadrados
 * 
 * grauPol = grau do polinômio
 * qntdPontos = número de pontos da tabela
 * matriz = matriz com os coeficientes do sistema linear
 * coeficientes = vetor com os coeficientes do polinômio
 * pontos_x = vetor com os valores de X passados pelo usuário
 * pontos_y = vetor com os valores de Y passados pelo usuário
 * 
****************************/
struct ajustePol {
    int grauPol;
    int qntdPontos;
    struct operandos** matriz;
    struct operandos* resultados;
    struct operandos* coeficientes;
    struct operandos* pontos_x;
    struct operandos* pontos_y;
};

#endif