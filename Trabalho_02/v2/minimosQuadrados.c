/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#include "estruturas.h"
#include "calculoIntervalar.h"
#include "minimosQuadrados.h"
#include "operaEstrutura.h"

// Aplica o método dos mínimos quadrados e posteriormente chama a função "gauss()"
struct ajustePol* minimosQuadrados(struct ajustePol* sistema) {

    struct operandos aux1, aux2, aux3;
    double start,end;

    for (int i = 0; i < sistema->grauPol; i++) {

        // Aplica as operações aritméticas apenas sobre os valores 
        // no triangulo superior da matriz de coeficientes, pois ela é espelhada 
        // no eixo da diagonal principal. Logo, podemos reutiliza-los e 
        // transpô-los para a região do triangulo inferior
        for (int j = i; j < sistema->grauPol; j++) {
            sistema->matriz[i][j] = calcularIntervalo(0.0);

            // Unroll+Jam na quantidade de pontos
            for(int k = 0; k < sistema->qntdPontos-sistema->qntdPontos%4; k+=4) {
                aux1 = calcularExpo(sistema->pontos_x[k], i);
                aux2 = calcularExpo(sistema->pontos_x[k], j);
                aux3 = calcularMultiplicacao(aux1,aux2);
                sistema->matriz[i][j] = calcularSoma(sistema->matriz[i][j], aux3);
                aux1 = calcularExpo(sistema->pontos_x[k+1], i);
                aux2 = calcularExpo(sistema->pontos_x[k+1], j);
                aux3 = calcularMultiplicacao(aux1,aux2);
                sistema->matriz[i][j] = calcularSoma(sistema->matriz[i][j], aux3);
                aux1 = calcularExpo(sistema->pontos_x[k+2], i);
                aux2 = calcularExpo(sistema->pontos_x[k+2], j);
                aux3 = calcularMultiplicacao(aux1,aux2);
                sistema->matriz[i][j] = calcularSoma(sistema->matriz[i][j], aux3);
                aux1 = calcularExpo(sistema->pontos_x[k+3], i);
                aux2 = calcularExpo(sistema->pontos_x[k+3], j);
                aux3 = calcularMultiplicacao(aux1,aux2);
                sistema->matriz[i][j] = calcularSoma(sistema->matriz[i][j], aux3);
            }

            // Resíduo do Unroll+Jam
            for (int k = sistema->qntdPontos-sistema->qntdPontos%4; k < sistema->qntdPontos; k++){
                aux1 = calcularExpo(sistema->pontos_x[k], i);
                aux2 = calcularExpo(sistema->pontos_x[k], j);
                aux3 = calcularMultiplicacao(aux1,aux2);
            }
        }

        // Aplica as operações aritméticas sobre os resultados de cada linha da matriz, 
        // ou seja, sobre os valores de B do sistema linear AX=B
        sistema->resultados[i] = calcularIntervalo(0.0);
        // Unroll+Jam na quantidade de pontos
        for (int k = 0; k < sistema->qntdPontos-sistema->qntdPontos%4; k+=4) {
            aux1 = calcularExpo(sistema->pontos_x[k], i);
            aux2 = calcularMultiplicacao(aux1,sistema->pontos_y[k]);
            sistema->resultados[i] = calcularSoma(sistema->resultados[i], aux2);
            aux1 = calcularExpo(sistema->pontos_x[k+1], i);
            aux2 = calcularMultiplicacao(aux1,sistema->pontos_y[k+1]);
            sistema->resultados[i] = calcularSoma(sistema->resultados[i], aux2);
            aux1 = calcularExpo(sistema->pontos_x[k+2], i);
            aux2 = calcularMultiplicacao(aux1,sistema->pontos_y[k+2]);
            sistema->resultados[i] = calcularSoma(sistema->resultados[i], aux2);
            aux1 = calcularExpo(sistema->pontos_x[k+3], i);
            aux2 = calcularMultiplicacao(aux1,sistema->pontos_y[k+3]);
            sistema->resultados[i] = calcularSoma(sistema->resultados[i], aux2);
        }
        
        // Resíduo do Unroll+Jam
        for (int k = sistema->qntdPontos-sistema->qntdPontos%4; k < sistema->qntdPontos; k++){
            aux1 = calcularExpo(sistema->pontos_x[k], i);
            aux2 = calcularMultiplicacao(aux1,sistema->pontos_y[k]);
            sistema->resultados[i] = calcularSoma(sistema->resultados[i], aux2);
        }
    }


    // Transpondo a matriz
    // para reutilizar os valores do triângulo superior
    for (int i=0; i < sistema->grauPol; i++) {
        for (int j=0; j<i; ++j){
            sistema->matriz[i][j].anterior = sistema->matriz[j][i].anterior;
            sistema->matriz[i][j].num = sistema->matriz[j][i].num;
            sistema->matriz[i][j].posterior = sistema->matriz[j][i].posterior;
        }
    }

    return sistema;
}

// Aplica o método de eliminação de gauss com pivoteamento parcial
void gauss(struct ajustePol* sistema) {

    struct operandos aux;
    double start, end;

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
                aux = calcularMultiplicacao(sistema->matriz[i][j], m);
                sistema->matriz[k][j] = calcularSubtracao(sistema->matriz[k][j], aux);
            }

            // Aplica as operações aritméticas sobre os resultados de cada linha da matriz, 
            // ou seja, sobre os valores de B do sistema linear AX=B
            aux = calcularMultiplicacao(sistema->resultados[i], m);
            sistema->resultados[k] = calcularSubtracao(sistema->resultados[k], aux);
        }
    }
    
    // Aplica a retro substituição no sistema linear triangularizado
    retroSubst(sistema);
}

// Varre a matriz da struct ajustePol e retorna o indice do maior double
// presente na linha "i" da matriz
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

// Efetua a troca entre as linhas "i" e "iPivo" da matriz da struct ajustePol
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

// Aplica a técnica de retro substituição
void retroSubst(struct ajustePol* sistema) {

    struct operandos aux;

    for (int i = (sistema->grauPol-1); i >= 0; i--) {
        sistema->coeficientes[i] = sistema->resultados[i];

        // Aplica as operações aritméticas sobre os valores da matriz de coeficientes do sistema linear e
        // guarda o resultado no vetor dos coeficientes do polinômio
        for (int j = (i+1); j < sistema->grauPol; j++) {
            aux = calcularMultiplicacao(sistema->matriz[i][j], sistema->coeficientes[j]);
            sistema->coeficientes[i] = calcularSubtracao(sistema->coeficientes[i], aux);
        }

        sistema->coeficientes[i] = calcularDivisao(sistema->coeficientes[i], sistema->matriz[i][i]);
    }
}

// Recebe uma struct operandos X0 e retorna f(X0)
struct operandos polinomio(struct ajustePol* sistema, struct operandos x0) {

    struct operandos aux1, aux2, resultado;
    resultado.num = 0.0;
    resultado.anterior = 0.0;
    resultado.posterior = 0.0;

    // Percorre o vetor dos coeficientes aplicando exponenciação no parâmetro
    // para então multiplicar pelo coeficiente correspondente
    for (int i = 0; i < sistema->grauPol; i++) {
        aux1 = calcularExpo(x0, i);
        aux2 = calcularMultiplicacao(sistema->coeficientes[i], aux1);
        resultado = calcularSoma(resultado, aux2);
    }

    return resultado;
}