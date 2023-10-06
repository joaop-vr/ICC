#ifndef _AUXILIARES_H_
#define _AUXILIARES_H_

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct operandos* alocarVetor(int N);

struct operandos** alocarMatriz(int N);

// Parâmetro: vetor de double [4]
// Retorno: maior número do vetor (double)
double max (double vet[4]);

// Parâmetro: vetor de double [4]
// Retorno: menor número do vetor (double)
double min (double vet[4]);

void calculaResiduos(struct ajustePol* sistema);
#endif