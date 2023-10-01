#ifndef _MINIMOSQUADRADOS_
#define _MINIMOSQUADRADOS_

void minimosQuadrados(struct ajustePol* sistema);

void gauss(struct ajustePol* sistema);

int encontraMax(struct ajustePol* sistema, int i);

void trocaLinha (struct ajustePol* sistema, int i, int iPivo);

void retroSubst(struct ajustePol* sistema);

double polinomio(struct ajustePol* sistema, double x0);
#endif