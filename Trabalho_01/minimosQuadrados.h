/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#ifndef _MINIMOSQUADRADOS_
#define _MINIMOSQUADRADOS_

void minimosQuadrados(struct ajustePol* sistema);

void gauss(struct ajustePol* sistema);

int encontraMax(struct ajustePol* sistema, int i);

void trocaLinha (struct ajustePol* sistema, int i, int iPivo);

void retroSubst(struct ajustePol* sistema);

struct operandos polinomio(struct ajustePol* sistema, struct operandos x0);
#endif