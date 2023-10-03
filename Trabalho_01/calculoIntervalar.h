/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno:  , GRR:
 * 
****************************/

#ifndef _CALCULOINTERVALAR_
#define _CALCULOINTERVALAR_

#include <stdlib.h>
#include <float.h>
#include <fenv.h>
#include <math.h>
#include "estruturas.h"
#include "auxiliares.h"

struct operandos calcularIntervalo (double num);

struct operandos calcularOperacao (struct operandos x, struct operandos y, int expoente, char operador);

struct operandos calcularSoma(struct operandos x, struct operandos y);

struct operandos calcularSubtracao(struct operandos x, struct operandos y);

struct operandos calcularMulticacao(struct operandos x, struct operandos y);

struct operandos calcularDivisao(struct operandos x, struct operandos y);

struct operandos calcularExpo(struct operandos x, int expoente);
#endif