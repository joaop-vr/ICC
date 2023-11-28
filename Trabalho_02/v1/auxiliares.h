#ifndef _AUXILIARES_H_
#define _AUXILIARES_H_

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

// Parâmetros: número inteiro
// Retorno: endereço do vetor alocado de tamanho N
struct operandos* alocarVetor(long long int N);

// Parâmetros: número inteiro
// Retorno: endereço da matriz alocada de tamanho NxN
struct operandos** alocarMatriz(long long int N);

// Parâmetro: vetor de double [4]
// Retorno: maior número do vetor (double)
double max (double vet[4]);

// Parâmetro: vetor de double [4]
// Retorno: menor número do vetor (double)
double min (double vet[4]);

// Retorna um valor de tempo atual em milissegundos, usando o tempo do sistema operacional
double timestamp(void);

// Calcula e imprime o resíduo da cada valor de X gerado pelo polinômio encontrado
void calculaResiduos(struct ajustePol* sistema);

#endif
