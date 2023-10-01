#ifndef OPERAESTRUTURA_H_
#define OPERAESTRUTURA_H_

#include "estruturas.h"

struct ajustePol* montarEstrutura();

void preencherEstrutura(struct ajustePol* sistema);

void imprimir(struct ajustePol* sistema);

double timestamp();

#endif