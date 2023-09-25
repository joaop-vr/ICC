#ifndef _METODOSINTERPOL_
#define _METODOSINTERPOL_

#include "auxiliares.h"

// Executa a Interpolação de Lagrange de retorna o seu tempo de execução
double interpolLagrange (struct tabPontos* tabela);

// Executa a Interpolação de Newton de retorna o seu tempo de execução
double interpolNewton (struct tabPontos* tabela);

double calcularDi(struct tabPontos* tabela, int ordem, int N);
#endif