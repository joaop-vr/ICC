#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <float.h>
#include "estruturas.h"

//Parâmetro: vetor de char [4]; vetor de float [5]
//Leitura da expressão e manipulação dos vetores com a atribuição dos operadores (char) e dos operandos (float)
//Retorno: void
void obterExpressao(char operadores[4], float valores[5]);

//Parâmetro: struct operandos x (operando 1), y (operando 2) e resultado, caractere operador
//Imprime, em ordem: x 'operador' y = resultado, Erro Absoluto, Erro Relativo e ULPs
//Retorno: void
void imprimir(struct operandos x, struct operandos y, struct operandos resultado, char operador);

//Parâmetro: vetor de float [4]
//Retorno: maior número do vetor (float)
float max (float vet[4]);

//Parâmetro: vetor de float [4]
//Retorno: menor número do vetor (float)
float min (float vet[4]);

#endif