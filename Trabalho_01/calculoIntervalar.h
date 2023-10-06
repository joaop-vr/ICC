#ifndef _CALCULOINTERVALAR_
#define _CALCULOINTERVALAR_

#include <stdlib.h>
#include <float.h>
#include <fenv.h>
#include <math.h>
#include "estruturas.h"
#include "auxiliares.h"

/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

// Parâmetros: número float
// Retorno: struct operandos com o intervalo que compreende o número fornecido
struct operandos calcularIntervalo (double num);

// Parâmetro: structs operandos X e Y
// Retorno: struct operandos com o resultado da soma de X e Y e seus intervalos
struct operandos calcularSoma(struct operandos x, struct operandos y);

// Parâmetro: structs operandos X e Y
// Retorno: struct operandos com o resultado da subtração de X por Y e seus intervalos
struct operandos calcularSubtracao(struct operandos x, struct operandos y);

// Parâmetro: structs operandos X e Y
// Retorno: struct operandos com o resultado da multiplicação entre X e Y e seus intervalos
struct operandos calcularMulticacao(struct operandos x, struct operandos y);

// Parâmetro: structs operandos X e Y
// Retorno: struct operandos com o resultado da divisão de X por Y e seus intervalos
struct operandos calcularDivisao(struct operandos x, struct operandos y);

// Parâmetro: struct operando X e 
// Retorno: struct operandos com o resultado da exponenciação de X por i e seus intervalos
struct operandos calcularExpo(struct operandos x, int expoente);

#endif