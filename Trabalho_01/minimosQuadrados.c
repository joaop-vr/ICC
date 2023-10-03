#include "estruturas.h"
#include "calculoIntervalar.h"
#include "minimosQuadrados.h"

void minimosQuadrados(struct ajustePol* sistema) {

    struct operandos aux1, aux2, aux3;

    for (int i = 0; i < sistema->grauPol; i++) {
        for (int j = 0; j < sistema->grauPol; j++) {
            //sistema->matriz[i][j].num = 0.0;
            sistema->matriz[i][j] = calcularIntervalo(0.0);
            for(int k = 0; k < sistema->qntdPontos; k++) {
                //sistema->matriz[i][j].num += pow(sistema->tabelaPontos[2*k].num, i)*pow(sistema->tabelaPontos[2*k].num, j);
                //aux1 = calcularOperacao(sistema->tabelaPontos[2*k], inutilizado, i, '^');
                //aux2 = calcularOperacao(sistema->tabelaPontos[2*k], inutilizado, j, '^');
                aux1 = calcularExpo(sistema->tabelaPontos[2*k], i);
                aux2 = calcularExpo(sistema->tabelaPontos[2*k], j);
                aux3 = calcularMulticacao(aux1,aux2);
                sistema->matriz[i][j] = calcularSoma(sistema->matriz[i][j], aux3);
            }
        }
        //sistema->resultados[i].num = 0.0;
        sistema->resultados[i] = calcularIntervalo(0.0);
        for (int k = 0; k < sistema->qntdPontos; k++) {
            //sistema->resultados[i].num += pow(sistema->tabelaPontos[2*k].num, i)*sistema->tabelaPontos[2*k+1].num;
            aux1 = calcularExpo(sistema->tabelaPontos[2*k], i);
            //printf("\naux1: %.4lf  [%.4lf | %.4lf]  <-  (%.4lf  [%.4lf | %.4lf])^%d\n", aux1.num, aux1.anterior, aux1.posterior, sistema->tabelaPontos[2*k].num, sistema->tabelaPontos[2*k].anterior, sistema->tabelaPontos[2*k].posterior, i);
            
            aux2 = calcularMulticacao(aux1,sistema->tabelaPontos[2*k+1]);
            //printf("aux2: %.4lf  [%.4lf | %.4lf]  <-  (%.4lf  [%.4lf | %.4lf]) * (%.4lf  [%.4lf | %.4lf])\n",
            //aux2.num, aux2.anterior, aux2.posterior, aux1.num, aux1.anterior, aux1.posterior, sistema->tabelaPontos[2*k+1].num, sistema->tabelaPontos[2*k+1].anterior, sistema->tabelaPontos[2*k+1].posterior);
            
            //struct operandos versaoResultadoANterior = sistema->resultados[i];
            sistema->resultados[i] = calcularSoma(sistema->resultados[i], aux2);
            //printf("sistema->resultados[i]  <-  (%.4lf  [%.4lf | %.4lf]) + (%.4lf  [%.4lf | %.4lf])\n",
            //versaoResultadoANterior.num, versaoResultadoANterior.anterior, versaoResultadoANterior.posterior, aux2.num, aux2.anterior, aux2.posterior);
            
            //printf("Portanto: sistema->resultados[%d]  <-  (%.4lf  [%.4lf | %.4lf])\n", i, sistema->resultados[i].num, sistema->resultados[i].anterior, sistema->resultados[i].posterior);
        }
    }

    /*for (int i = 0; i < sistema->grauPol; i++) {
        for (int j = 0; j < sistema->grauPol; j++) {
            printf("funcaoMQ matriz[%d][%d]: %.4lf  [%.4lf | %.4lf]\n", i, j, sistema->matriz[i][j].num, sistema->matriz[i][j].anterior, sistema->matriz[i][j].posterior);
        }
    }
    
    for (int i = 0; i < sistema->grauPol; i++) {
        printf("resultados[%d]: %.4lf  [%.4lf | %.4lf]\n", i, sistema->resultados[i].num, sistema->resultados[i].anterior, sistema->resultados[i].posterior);
    }*/
    gauss(sistema);
}

void gauss(struct ajustePol* sistema) {

    struct operandos aux;

    for (int i = 0; i < sistema->grauPol; i++) {
        int pivo = encontraMax(sistema, i);

        printf("\n\n######## i = %d ########", i);
        printf("\n\n######## pivo = %d ########\n", pivo);
        /*for (int i = 0; i < sistema->grauPol; i++) {
            for (int j = 0; j < sistema->grauPol; j++) {
                printf("%10.4lf [%.4lf | %.4lf]\n", sistema->matriz[i][j].num, sistema->matriz[i][j].anterior, sistema->matriz[i][j].posterior);
            }
            printf(" %2.4lf [%.4lf | %.4lf]\n\n\n", sistema->resultados[i].num, sistema->resultados[i].anterior, sistema->resultados[i].posterior);
        }*/
        for (int i = 0; i < sistema->grauPol; i++) {
            for (int j = 0; j < sistema->grauPol; j++) {
                printf("%10.4lf  ", sistema->matriz[i][j].num);
            }
            printf(" %2.4lf\n", sistema->resultados[i].num);
        }
        printf("\n\n");

        if (i != pivo) {
            printf("VAI TROCAR A LINHAAAAAA\n");
            trocaLinha(sistema, i, pivo);
        }

        /*for (int i = 0; i < sistema->grauPol; i++) {
            for (int j = 0; j < sistema->grauPol; j++) {
                printf("%10.4lf [%.4lf | %.4lf]\n", sistema->matriz[i][j].num, sistema->matriz[i][j].anterior, sistema->matriz[i][j].posterior);
            }
            printf(" %2.4lf [%.4lf | %.4lf]\n\n\n", sistema->resultados[i].num, sistema->resultados[i].anterior, sistema->resultados[i].posterior);
        }*/
        for (int i = 0; i < sistema->grauPol; i++) {
            for (int j = 0; j < sistema->grauPol; j++) {
                printf("%10.4lf  ", sistema->matriz[i][j].num);
            }
            printf(" %2.4lf\n", sistema->resultados[i].num);
        }
        printf("\n\n");
        printf("\n\n");
        
        for (int k = i+1; k < sistema->grauPol; k++) {
            //double m = sistema->matriz[k][i].num / sistema->matriz[i][i].num;
            struct operandos m = calcularDivisao(sistema->matriz[k][i], sistema->matriz[i][i]);
            //sistema->matriz[k][i].num = 0.0;
            sistema->matriz[k][i] = calcularIntervalo(0.0);
            for (int j = i+1; j < sistema->grauPol; j++) {
                //sistema->matriz[k][j].num -= sistema->matriz[i][j].num*m;
                aux = calcularMulticacao(sistema->matriz[i][j], m);
                sistema->matriz[k][j] = calcularSubtracao(sistema->matriz[k][j], aux);
            }
            //sistema->resultados[k].num -= sistema->resultados[i].num*m;
            aux = calcularMulticacao(sistema->resultados[i], m);
            sistema->resultados[k] = calcularSubtracao(sistema->resultados[k], aux);
        }
    }

    for (int i = 0; i < sistema->grauPol; i++) {
        for (int j = 0; j < sistema->grauPol; j++) {
            printf("matriz[%d][%d]: %.4lf  [%.4lf | %.4lf]\n", i, j, sistema->matriz[i][j].num, sistema->matriz[i][j].anterior, sistema->matriz[i][j].posterior);
        }
    }
    
    for (int i = 0; i < sistema->grauPol; i++) {
        printf("resultados[%d]: %.4lf  [%.4lf | %.4lf]\n", i, sistema->resultados[i].num, sistema->resultados[i].anterior, sistema->resultados[i].posterior);
    }

    printf("\n\n");
    for (int i = 0; i < sistema->grauPol; i++) {
        for (int j = 0; j < sistema->grauPol; j++) {
            printf("%10.4lf [%.4lf | %.4lf]\n", sistema->matriz[i][j].num, sistema->matriz[i][j].anterior, sistema->matriz[i][j].posterior);
        }
        printf(" %2.4lf [%.4lf | %.4lf]\n\n\n", sistema->resultados[i].num, sistema->resultados[i].anterior, sistema->resultados[i].posterior);
    }
    printf("\n\n");
    
    retroSubst(sistema);

    for (int i = 0; i < sistema->grauPol; i++)
    {
        printf("coeficiente[%d]: %.4lf [%.4lf | %.4lf]\n", i, sistema->coeficientes[i].num, sistema->coeficientes[i].anterior, sistema->coeficientes[i].posterior);
    }
    
}

int encontraMax(struct ajustePol* sistema, int i) {
    double maior = sistema->matriz[i][0].posterior;
    int indMaior = 0;
    for (int j=1; j < sistema->grauPol; j++){
        if (fabs(sistema->matriz[i][j].posterior) > maior){
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

    struct operandos aux;

    for (int i = (sistema->grauPol-1); i >= 0; i--) {
        sistema->coeficientes[i] = sistema->resultados[i];
        for (int j = (i+1); j < sistema->grauPol; j++) {
            //sistema->coeficientes[i].num -= sistema->matriz[i][j].num*sistema->coeficientes[j].num;
            aux = calcularMulticacao(sistema->matriz[i][j], sistema->coeficientes[j]);
            sistema->coeficientes[i] = calcularSubtracao(sistema->coeficientes[i], aux);
        }
        //sistema->coeficientes[i].num /= sistema->matriz[i][i].num;
        sistema->coeficientes[i] = calcularDivisao(sistema->coeficientes[i], sistema->matriz[i][i]);
    }
}

double polinomio(struct ajustePol* sistema, double x0) {
    double resultado = 0.0;
    for (int i = 0; i < sistema->grauPol; i++)
        resultado += sistema->coeficientes[i].num*pow(x0, i);
    return resultado;
}