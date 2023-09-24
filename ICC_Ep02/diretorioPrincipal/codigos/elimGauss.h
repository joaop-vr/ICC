#ifndef ELIMGAUSS_H_
#define ELIMGAUSS_H_

#include "auxiliares.h"

// Realiza o método 1 e retorna o seu tempo execução
double elimGaussClassico(struct sistemaLinear* sistema);

// Realiza os métodos 2 e retorna o seu tempo execução
double elimGaussSemMulti(struct sistemaLinear* sistema);

// Realiza o método 3 e retorna o seu tempo execução
double elimGaussAlternativa(struct sistemaLinear* sistema);

// Encontra o maior coeficiente das linhas, para posteriormente realizar o pivoteamento
int max (struct sistemaLinear* sistema, int c);

// Realiza o pivoteamento parcial
void trocarLinha (struct sistemaLinear* sistema, int i, int iPivo);

// Realiza a substituição retroativa no SL
void retroSubst(struct sistemaLinear* sistema);

// Divide todos os coeficientes da linha pelo pivô
void divisaoPivo(struct sistemaLinear* sistema, int i);

#endif