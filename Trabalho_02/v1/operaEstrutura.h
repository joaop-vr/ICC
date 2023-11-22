/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#ifndef OPERAESTRUTURA_H_
#define OPERAESTRUTURA_H_

#include "estruturas.h"

// Aloca os componentes de ajustepol e então chama a função preencherEstrutura()
struct ajustePol* montarEstrutura();

// Preenche a struct ajustePol com os pontos da tabela
void preencherEstrutura(struct ajustePol* sistema);

// Imprime todos os metadados da struct ajustePol
void imprimir(struct ajustePol* sistema);

// Libera toda a memória que foi alocada no decorrer do código 
void destruirEstrutura(struct ajustePol* sistema);

#endif