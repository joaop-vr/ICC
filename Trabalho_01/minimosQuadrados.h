/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#ifndef _MINIMOSQUADRADOS_
#define _MINIMOSQUADRADOS_

// Aplica o método dos mínimos quadrados e posteriormente chama a função "gauss()"
struct ajustePol* minimosQuadrados(struct ajustePol* sistema);

// Aplica o método de eliminação de gauss com pivoteamento parcial na matriz da struct ajustePol
void gauss(struct ajustePol* sistema);

// Varre a matriz da struct ajustePol e retorna o indice do maior valor double
// presente na linha "i"
int encontraMax(struct ajustePol* sistema, int i);

// Efetua a troca entre as linhas "i" e "iPivo" da matriz da struct ajustePol
void trocaLinha (struct ajustePol* sistema, int i, int iPivo);

// Aplica a técnica de retro substituição na matriz da struct ajustePol
void retroSubst(struct ajustePol* sistema);

// Recebe uma struct operandos X0 e retorna 
struct operandos polinomio(struct ajustePol* sistema, struct operandos x0);

#endif