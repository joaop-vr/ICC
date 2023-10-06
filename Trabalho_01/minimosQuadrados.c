/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#include "estruturas.h"
#include "calculoIntervalar.h"
#include "minimosQuadrados.h"
#include "auxiliares.h"

void minimosQuadrados(struct ajustePol* sistema) {

    struct operandos aux1, aux2, aux3;
    double start,end;

    for (int i = 0; i < sistema->grauPol; i++) {

        start = timestamp();

        // Aplica as operações aritméticas sobre os valores da matriz de coeficientes do sistema linear,
        // ou seja, sobre os valores de A do sistema linear AX=B
        for (int j = 0; j < sistema->grauPol; j++) {
            sistema->matriz[i][j] = calcularIntervalo(0.0);
            for(int k = 0; k < sistema->qntdPontos; k++) {
                aux1 = calcularExpo(sistema->tabelaPontos[2*k], i);
                aux2 = calcularExpo(sistema->tabelaPontos[2*k], j);
                aux3 = calcularMulticacao(aux1,aux2);
                sistema->matriz[i][j] = calcularSoma(sistema->matriz[i][j], aux3);
                sistema->matriz[i][j] = calcularIntervalo(sistema->matriz[i][j].num);
            }
        }

        // Aplica as operações aritméticas sobre os resultados de cada linha da matriz, 
        // ou seja, sobre os valores de B do sistema linear AX=B
        sistema->resultados[i] = calcularIntervalo(0.0);
        for (int k = 0; k < sistema->qntdPontos; k++) {
            aux1 = calcularExpo(sistema->tabelaPontos[2*k], i);
            aux2 = calcularMulticacao(aux1,sistema->tabelaPontos[2*k+1]);
            sistema->resultados[i] = calcularSoma(sistema->resultados[i], aux2);
            sistema->resultados[i] = calcularIntervalo(sistema->resultados[i].num);
       }
    }

    end = timestamp();
    printf("%lf\n", end-start); // Tempo para calcular geração dos coeficientes e termos independentes do sistema linear 

    // Aplica a eliminação de gauss no sistema linear montado acima 
    gauss(sistema);
}

void gauss(struct ajustePol* sistema) {

    struct operandos aux;
    double start, end;

    start = timestamp();

    for (int i = 0; i < sistema->grauPol; i++) {

        // Pivoteamento parcial
        int pivo = encontraMax(sistema, i);
        if (i != pivo) {
            trocaLinha(sistema, i, pivo);
        }
        
        for (int k = i+1; k < sistema->grauPol; k++) {

            // Calcula o múltiplo entre matriz[k][i] e matriz[i][i]
            struct operandos m = calcularDivisao(sistema->matriz[k][i], sistema->matriz[i][i]);
            sistema->matriz[k][i] = calcularIntervalo(0.0);

            // Aplica as operações aritméticas sobre os valores da matriz de coeficientes do sistema linear,
            // ou seja, sobre os valores de A do sistema linear AX=B
            for (int j = i+1; j < sistema->grauPol; j++) {
                aux = calcularMulticacao(sistema->matriz[i][j], m);
                sistema->matriz[k][j] = calcularSubtracao(sistema->matriz[k][j], aux);
                sistema->matriz[k][j] = calcularIntervalo(sistema->matriz[k][j].num);
            }

            // Aplica as operações aritméticas sobre os resultados de cada linha da matriz, 
            // ou seja, sobre os valores de B do sistema linear AX=B
            aux = calcularMulticacao(sistema->resultados[i], m);
            sistema->resultados[k] = calcularSubtracao(sistema->resultados[k], aux);
            sistema->resultados[k] = calcularIntervalo(sistema->resultados[k].num);
        }
    }
    
    end = timestamp();
    printf("%lf\n", end-start); // Tempo gasto na solução do sistema linear

    // Aplica a retro substituição no sistema linear triangularizado
    retroSubst(sistema);
    
}

int encontraMax(struct ajustePol* sistema, int i) {

    double maior = sistema->matriz[i][0].posterior;
    int indMaior = 0;

    // Varre a matriz para encontrar o indice do maior valor da linha i
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

        // Aplica as operações aritméticas sobre os valores da matriz de coeficientes do sistema linear e
        // guarda o resultado no vetor dos coeficientes do polinômio
        for (int j = (i+1); j < sistema->grauPol; j++) {
            aux = calcularMulticacao(sistema->matriz[i][j], sistema->coeficientes[j]);
            sistema->coeficientes[i] = calcularSubtracao(sistema->coeficientes[i], aux);
            sistema->coeficientes[i] = calcularIntervalo(sistema->coeficientes[i].num);
        }

        sistema->coeficientes[i] = calcularDivisao(sistema->coeficientes[i], sistema->matriz[i][i]);
        sistema->coeficientes[i] = calcularIntervalo(sistema->coeficientes[i].num);
    }
}

struct operandos polinomio(struct ajustePol* sistema, struct operandos x0) {

    struct operandos aux1, aux2, resultado;
    resultado.num = 0.0;
    resultado.anterior = 0.0;
    resultado.posterior = 0.0;

    // Percorre o vetor dos coeficientes aplicando exponenciação no 
    // valor X0 da entrada e então multiplica pelo coeficiente correspondente
    for (int i = 0; i < sistema->grauPol; i++) {
        aux1 = calcularExpo(x0, i);
        aux2 = calcularMulticacao(sistema->coeficientes[i], aux1);
        resultado = calcularSoma(resultado, aux2);
    }

    return resultado;
}