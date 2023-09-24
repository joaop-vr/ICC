#ifndef PRINCIPAIS_H
#define PRINCIPAIS_H

#include <float.h>
#include <fenv.h>
#include <math.h>
#include "estruturas.h"

//Parâmetros: número float
//Retorno: struct operandos com o intervalo que compreende o número fornecido
struct operandos calcularIntervalo (float num);

//Parâmetros: struct operandos x e y, caractere do operador
//Resolve a expressão x 'operador' y
//Retorno: struct operandos com o intervalo resultante da operação realizada
struct operandos calcularOperacao (struct operandos x, struct operandos y, char operador);

#endif