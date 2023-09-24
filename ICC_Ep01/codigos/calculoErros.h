#ifndef CALCULOERROS_H
#define CALCULOERROS_H

#include "estruturas.h"

//Parâmetro: struct operandos resultado
//Módulo da diferença (resultado.posterior - resultado.anterior)
//Retorno: erro absoluto do intervalo do resultado (float)
float calcularEA(struct operandos resultado);

//Parâmetro: struct operandos resultado
//Módulo da diferença (resultado.posterior - resultado.anterior)/resultando.anterior
//Retorno: erro relativo do intervalo do resultado (float)
float calcularER(struct operandos resultado);

//Parâmetro: struct operandos resultado
//Retorno: contagem de ULPS no intervalo do resultado (float)
int calcularULPs(struct operandos resultado);

#endif