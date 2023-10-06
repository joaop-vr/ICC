#ifndef _AUXILIARES_H_
#define _AUXILIARES_H_

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Parâmetros: número inteiro
// Retorno: endereço do vetor alocado de tamanho N
struct operandos* alocarVetor(int N);

// Parâmetros: número inteiro
// Retorno: endereço da matriz alocada de tamanho NxN
struct operandos** alocarMatriz(int N);

// Parâmetro: vetor de double [4]
// Retorno: maior número do vetor (double)
double max (double vet[4]);

// Parâmetro: vetor de double [4]
// Retorno: menor número do vetor (double)
double min (double vet[4]);

// Calcula e imprime o resíduo da cada valor de X gerado pelo polinômio encontrado
void calculaResiduos(struct ajustePol* sistema);

#endif