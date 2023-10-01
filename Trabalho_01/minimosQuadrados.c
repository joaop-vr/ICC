#include "estruturas.h"
#include "calculoIntervalar.h"
#include "minimosQuadrados.h"

void minimosQuadrados(struct ajustePol* sistema) {

    for (int i = 0; i < sistema->grauPol; i++) {
        for (int j = 0; j < sistema->grauPol; j++) {
            sistema->matriz[i][j].num = 0.0;
            for(int k = 0; k < sistema->qntdPontos; k++) {
                sistema->matriz[i][j].num += pow(sistema->tabelaPontos[2*k].num, i)*pow(sistema->tabelaPontos[2*k].num, j);
            }
        }
        sistema->resultados[i].num = 0.0;
        for (int k = 0; k < sistema->qntdPontos; k++)
            sistema->resultados[i].num += pow(sistema->tabelaPontos[2*k].num, i)*sistema->tabelaPontos[2*k+1].num;
    }
    
    gauss(sistema);
}

void gauss(struct ajustePol* sistema) {
    for (int i = 0; i < sistema->grauPol; i++) {
        int pivo = encontraMax(sistema, i);
        if (i != pivo)
            trocaLinha(sistema, i, pivo);
        
        for (int k = i+1; k < sistema->grauPol; k++) {
            double m = sistema->matriz[k][i].num / sistema->matriz[i][i].num;
            sistema->matriz[k][i].num = 0.0;
            for (int j = i+1; j < sistema->grauPol; j++)
                sistema->matriz[k][j].num -= sistema->matriz[i][j].num*m;
            sistema->resultados[k].num -= sistema->resultados[i].num*m;
        }
    }
    
    retroSubst(sistema);
}

int encontraMax(struct ajustePol* sistema, int i) {
    double maior = 0.0;
    int indMaior = 0;
    for (int j=0; j < sistema->grauPol; j++){
        if (fabs(sistema->matriz[i][j].num) > maior){
            maior = sistema->matriz[i][j].num;
            indMaior = j;
        }
    }
    return indMaior;
}

void trocaLinha (struct ajustePol* sistema, int i, int iPivo) {

    struct operandos aux;

    // Trocando as linhas na matriz de coeficientes
    for (int k = 0; k < sistema->grauPol; k++) {
        aux = sistema->matriz[i][k];
        sistema->matriz[i][k] = sistema->matriz[iPivo][k];
        sistema->matriz[iPivo][k] = aux;
    }

    // Trocando as linhas no vetor de resultados do sistema (vetor B em AX=B)
    aux = sistema->resultados[i];
    sistema->resultados[i] = sistema->resultados[iPivo];
    sistema->resultados[iPivo] = aux;
}

void retroSubst(struct ajustePol* sistema) {

    for (int i = (sistema->grauPol-1); i >= 0; i--) {
        sistema->coeficientes[i] = sistema->resultados[i];
        for (int j = (i+1); j < sistema->grauPol; j++)
            sistema->coeficientes[i].num -= sistema->matriz[i][j].num*sistema->coeficientes[j].num;
        sistema->coeficientes[i].num /= sistema->matriz[i][i].num;
    }
}

double polinomio(struct ajustePol* sistema, double x0) {
    double resultado = 0.0;
    for (int i = 0; i < sistema->grauPol; i++)
        resultado += sistema->coeficientes[i].num*pow(x0, i);
    return resultado;
}