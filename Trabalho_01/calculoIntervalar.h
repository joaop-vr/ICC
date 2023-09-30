/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno:  , GRR:
 * 
****************************/

#ifndef _CALCULOINTERVALAR_
#define _CALCULOINTERVALAR_

#include <float.h>
#include <fenv.h>
#include <math.h>
#include "estruturas.h"
#include "auxiliares.h"

struct operandos calcularIntervalo (double num);

struct operandos calcularOperacao (struct operandos x, struct operandos y, char operador);


#endif