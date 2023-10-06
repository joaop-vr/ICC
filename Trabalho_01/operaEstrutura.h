#ifndef OPERAESTRUTURA_H_
#define OPERAESTRUTURA_H_

/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#include "estruturas.h"

struct ajustePol* montarEstrutura();

void preencherEstrutura(struct ajustePol* sistema);

void imprimir(struct ajustePol* sistema);

// Libera toda a memória que foi alocada no decorrer do código 
void destruirEstrutura(struct ajustePol* sistema);

#endif