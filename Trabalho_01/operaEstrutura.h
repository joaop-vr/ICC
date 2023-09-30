#ifndef OPERAESTRUTURA_H_
#define OPERAESTRUTURA_H_

#include "estruturas.h"

struct sistemaLinear* montarEstrutura();

void preencherEstrutura(struct sistemaLinear* sistema);

void imprimir(struct sistemaLinear* sistema);

struct operandos* alocarVetor(int N);

double timestamp();

#endif