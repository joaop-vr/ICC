/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

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
                sistema->matriz[i][j] = (calcularSoma(sistema->matriz[i][j], aux3));
                sistema->matriz[i][j] = calcularIntervalo(sistema->matriz[i][j].num);
            }
        }
        //sistema->resultados[i].num = 0.0;
        sistema->resultados[i] = calcularIntervalo(0.0);
        for (int k = 0; k < sistema->qntdPontos; k++) {
            //sistema->resultados[i].num += pow(sistema->tabelaPontos[2*k].num, i)*sistema->tabelaPontos[2*k+1].num;
            aux1 = calcularExpo(sistema->tabelaPontos[2*k], i);
            aux2 = calcularMulticacao(aux1,sistema->tabelaPontos[2*k+1]);
            sistema->resultados[i] = calcularSoma(sistema->resultados[i], aux2);
            sistema->resultados[i] = calcularIntervalo(sistema->resultados[i].num);
       }
    }

    gauss(sistema);
}

void gauss(struct ajustePol* sistema) {

    struct operandos aux;

    for (int i = 0; i < sistema->grauPol; i++) {

        int pivo = encontraMax(sistema, i);
        if (i != pivo) {
            trocaLinha(sistema, i, pivo);
        }
        
        for (int k = i+1; k < sistema->grauPol; k++) {
            //double m = sistema->matriz[k][i].num / sistema->matriz[i][i].num;
            struct operandos m = calcularDivisao(sistema->matriz[k][i], sistema->matriz[i][i]);
            //sistema->matriz[k][i].num = 0.0;
            sistema->matriz[k][i] = calcularIntervalo(0.0);
            for (int j = i+1; j < sistema->grauPol; j++) {
                //sistema->matriz[k][j].num -= sistema->matriz[i][j].num*m;
                aux = calcularMulticacao(sistema->matriz[i][j], m);
                sistema->matriz[k][j] = calcularSubtracao(sistema->matriz[k][j], aux);
                sistema->matriz[k][j] = calcularIntervalo(sistema->matriz[k][j].num);
            }
            //sistema->resultados[k].num -= sistema->resultados[i].num*m;
            aux = calcularMulticacao(sistema->resultados[i], m);
            sistema->resultados[k] = calcularSubtracao(sistema->resultados[k], aux);
            sistema->resultados[k] = calcularIntervalo(sistema->resultados[k].num);
        }
    }
    
    retroSubst(sistema);
    
}

int encontraMax(struct ajustePol* sistema, int i) {
    double maior = sistema->matriz[i][0].posterior;
    int indMaior = 0;
    for (int j=1; j < sistema->grauPol; j++){
        if (fabs(sistema->matriz[i][j].posterior - maior) > FLT_EPSILON){
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
            sistema->coeficientes[i] = calcularIntervalo(sistema->coeficientes[i].num);
        }
        //sistema->coeficientes[i].num /= sistema->matriz[i][i].num;
        sistema->coeficientes[i] = calcularDivisao(sistema->coeficientes[i], sistema->matriz[i][i]);
        sistema->coeficientes[i] = calcularIntervalo(sistema->coeficientes[i].num);
    }
}

struct operandos polinomio(struct ajustePol* sistema, struct operandos x0) {

    struct operandos aux1, aux2, resultado;
    resultado.num = 0.0;
    resultado.anterior = 0.0;
    resultado.posterior = 0.0;

    for (int i = 0; i < sistema->grauPol; i++) {
        
        /*printf("\n\n### i=%d ###\n", i);
        printf("aux1 <- x0 ^ %d\n", i);
        printf("aux1 <- %1.8e  [%1.8e | %1.8e] ^ %d\n", x0.num, x0.anterior, x0.posterior, i);
        */
        aux1 = calcularExpo(x0, i);

        /*printf("aux2 <- sistema->coeficientes[%d] * aux1\n", i);
        printf("aux2 <- %1.8e  [%1.8e | %1.8e] * %1.8e  [%1.8e | %1.8e]\n", i, sistema->coeficientes[i].num, sistema->coeficientes[i].anterior, sistema->coeficientes[i].posterior,
        aux1.num, aux1.anterior, aux1.posterior);
        */
        aux2 = calcularMulticacao(sistema->coeficientes[i], aux1);

        /*printf("resultado <- resultado + aux2\n");
        printf("resultado <- %1.8e  [%1.8e | %1.8e] + %1.8e  [%1.8e | %1.8e]\n", i, resultado.num, resultado.anterior, resultado.posterior,
        aux2.num, aux2.anterior, aux2.posterior);
        */
        resultado = calcularSoma(resultado, aux2);
    }
        //resultado += sistema->coeficientes[i].num*pow(x0, i);
    return resultado;
}