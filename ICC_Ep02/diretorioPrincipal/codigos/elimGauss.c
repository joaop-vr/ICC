#include <likwid.h>
#include <stdio.h>
#include <float.h>
#include <fenv.h>
#include <math.h>

#include "elimGauss.h"

double elimGaussClassico(struct sistemaLinear* sistema) {

    double tempInicial, tempFinal, dif;
    //fesetround(FE_DOWNWARD);
    tempInicial = timestamp();
    LIKWID_MARKER_START("metodo1");

    for (int i = 0; i < sistema->ordem; i++) {
        int iPivo = max(sistema, i);
        if (i != iPivo)
            trocarLinha(sistema, i, iPivo);
        
        for (int k = i+1; k < sistema->ordem; k++) {
            double multi = sistema->matriz[k][i] / sistema->matriz[i][i];
            sistema->matriz[k][i] = 0.0;
            for (int j = i+1; j < sistema->ordem; j++)
                sistema->matriz[k][j] -= sistema->matriz[i][j]*multi;
            sistema->constantes[k] -= sistema->constantes[i]*multi;
        }
    }

    retroSubst(sistema);

    LIKWID_MARKER_STOP("metodo1");

    //fesetround(FE_UPWARD);
    tempFinal = timestamp();
    dif = tempFinal - tempInicial;

    return dif;
}

double elimGaussSemMulti(struct sistemaLinear* sistema) {

    double tempInicial, tempFinal, dif;

    //fesetround(FE_DOWNWARD);
    tempInicial = timestamp();
    LIKWID_MARKER_START("metodo2");

    for (int i = 0; i < sistema->ordem; i++) {
        int iPivo = max(sistema, i);
        if (i != iPivo)
            trocarLinha(sistema, i, iPivo);
        
        for (int k = i+1; k < sistema->ordem; k++) {            
            for (int j = i+1; j < sistema->ordem; j++)
                sistema->matriz[k][j] = sistema->matriz[k][j]*sistema->matriz[i][i] - sistema->matriz[i][j]*sistema->matriz[k][i];
            sistema->constantes[k] = sistema->constantes[k]*sistema->matriz[i][i] - sistema->constantes[i]*sistema->matriz[k][i];
        }
    }

    retroSubst(sistema);

    LIKWID_MARKER_STOP("metodo2");

    //fesetround(FE_UPWARD);
    tempFinal = timestamp();
    dif = tempFinal - tempInicial;

    return dif;
}

double elimGaussAlternativa(struct sistemaLinear* sistema) {

    double tempInicial, tempFinal, dif;

    //fesetround(FE_DOWNWARD);
    tempInicial = timestamp();
    LIKWID_MARKER_START("metodo3");

    for (int i = 0; i < sistema->ordem; i++) {
        
        divisaoPivo(sistema, i);
        
        for (int k = i+1; k < sistema->ordem; k++) {
            double multi = sistema->matriz[k][i] / sistema->matriz[i][i];
            sistema->matriz[k][i] = 0.0;
            
            for (int j = i+1; j < sistema->ordem; j++)
                sistema->matriz[k][j] -= sistema->matriz[i][j]*multi;
            sistema->constantes[k] -= sistema->constantes[i]*multi;
        }
    }

    retroSubst(sistema);

    LIKWID_MARKER_STOP("metodo3");

    //fesetround(FE_UPWARD);
    tempFinal = timestamp();
    dif = tempFinal - tempInicial;

    return dif;
}

int max (struct sistemaLinear* sistema, int c) {

    int maior;
    double dif;

    // Inicializa 'maior' com o indice 0 da coluna "c", ou seja, matriz[0][c]
    maior = 0; 
    for (int l = 1; l < sistema->ordem; l++) {

        dif = fabs(sistema->matriz[l][c] - sistema->matriz[maior][c]);

        // Verificando matriz[l][c] é o maior valor da coluna "c"
        // levando em consideração a margem de erro (FLT_EPSILON)
        if ((fabs(sistema->matriz[l][c]) > maior) && (dif > FLT_EPSILON)) {
            maior = l;
        }
    }

    return maior;
}

void trocarLinha (struct sistemaLinear* sistema, int i, int iPivo) {

    double aux;

    // Trocando as linhas na matriz de coeficientes
    for (int k = 0; k < sistema->ordem; k++) {
        aux = sistema->matriz[i][k];
        sistema->matriz[i][k] = sistema->matriz[iPivo][k];
        sistema->matriz[iPivo][k] = aux;
    }

    // Trocando as linhas no vetor de constantes (vetor B em AX=B)
    aux = sistema->constantes[i];
    sistema->constantes[i] = sistema->constantes[iPivo];
    sistema->constantes[iPivo] = aux;
}

void retroSubst(struct sistemaLinear* sistema) {

    for (int i = (sistema->ordem -1); i >= 0; i--) {
        sistema->solucoes[i] = sistema->constantes[i];
        for (int j = (i+1); j < sistema->ordem; j++)
            sistema->solucoes[i] -= sistema->matriz[i][j] * sistema->solucoes[j];
        sistema->solucoes[i] /= sistema->matriz[i][i];
    }
}

void divisaoPivo(struct sistemaLinear* sistema, int i) {

    double pivo;

    pivo = sistema->matriz[i][i];

    for (int k = i; k < sistema->ordem; k++) {
        sistema->matriz[i][k] /= pivo;
    }

    sistema->constantes[i] /= pivo;
}