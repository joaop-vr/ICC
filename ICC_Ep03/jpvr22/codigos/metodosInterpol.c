#include <likwid.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <fenv.h>
#include <math.h>

#include "metodosInterpol.h"

double interpolLagrange (struct tabPontos* tabela) {

    double L, xe, xi, xk, y, tempInicial, tempFinal, dif;

    tempInicial = timestamp();
    LIKWID_MARKER_START("metodo1");

    xe = tabela->xe;
    tabela->Px = 0.0;
    for (int i = 0; i < (tabela->N); i++) {

        L = 1.0;
        xi = tabela->vetPontos[2*i];
        for (int k = 0; k < (tabela->N); k++) {
            if (i != k) { // Evita divisões por zero
                xk = tabela->vetPontos[2*k];
                L *= (xe - xk)/(xi - xk);
            }
        }
        y = tabela->vetPontos[2*i+1];
        tabela->Px += L*y;
    }

    LIKWID_MARKER_STOP("metodo1");
    tempFinal = timestamp();
    dif = tempFinal - tempInicial;

    return dif;
}


double interpolNewton (struct tabPontos* tabela) {

    double di, xe, xk, tempInicial, tempFinal, dif;

    tempInicial = timestamp();
    LIKWID_MARKER_START("metodo2");

    xe = tabela->xe;
    tabela->Px = 0.0;
    for (int i = 0; i < (tabela->N); i++) {

        if (i == 0) {
            di = tabela->vetPontos[1]; // di <- d0
        } else {
            di = calcularDi(tabela, i, tabela->N);
        }

        for (int k = 0; k < i; k++) {
            xk = tabela->vetPontos[2*k];
            di *= (xe - xk);
        }
        tabela->Px += di;
    }

    LIKWID_MARKER_STOP("metodo2");
    tempFinal = timestamp();
    dif = tempFinal - tempInicial;

    return dif;
}

double calcularDi(struct tabPontos* tabela, int ordem, int N) {

    double output;
    double* ordem1 = malloc((N-1)*sizeof(double));

    // Calcula a Ordem 1 da tabela
    for (int i = 0; i < (N-1); i++) {
        ordem1[i] = (tabela->vetPontos[2*(i+1)+1] - tabela->vetPontos[2*i+1]) / (tabela->vetPontos[2*(i+1)] - tabela->vetPontos[2*i]);
    }

    // Calcula as demais ordem, sendo que o Di final será armazenado em ordem1[0]
    for (int i = 2; i <= ordem; i++) {
        for (int j = 0; j < (N-j); j++) {
            ordem1[j] = (ordem1[j+1] - ordem1[j]) / (tabela->vetPontos[ordem] - tabela->vetPontos[0]);
        }
    }

    output = ordem1[0];
    free(ordem1);
    
    return output;
}