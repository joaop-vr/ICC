//#include "likwid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#include "operaEstrutura.h"
#include "calculoIntervalar.h"

struct ajustePol* montarEstrutura() {

    struct ajustePol* sistema = malloc(sizeof(struct ajustePol));
    int grau, qntdPontos;

    // Lê o grau do polinomio
    if (scanf("%d", &grau) != 1) {
        fprintf(stderr, "Erro na leitura do grau do polinômio.\n");
        exit(1);
    }

    // Lê a quantidade de pontos
    if (scanf("%d", &qntdPontos) != 1) {
        fprintf(stderr, "Erro na leitura de quantidade de pontos.\n");
        exit(1);
    }

    grau += 1;
    sistema->grauPol = grau;
    sistema->qntdPontos = qntdPontos;    

    sistema->matriz = alocarMatriz(grau);
    sistema->resultados = alocarVetor(grau);
    sistema->coeficientes = alocarVetor(grau);
    sistema->tabelaPontos = alocarVetor(2*qntdPontos);    

    preencherEstrutura(sistema);

    return sistema;
}

void preencherEstrutura(struct ajustePol* sistema) {

    char aux[100], *token;
    double valor;
    int N;

    N = 2*sistema->qntdPontos;

    for (int i = 0; i < N ; i++) {

        // Obtém a linha com o ponto (x,y)
        if (scanf("%s", aux) != 1) {
            fprintf(stderr, "Erro na leitura de entrada dos pontos.\n");
            exit(1);
        }   

        // Obtém a coordenada no eixo X e calcula o intervalo
        token = strtok(aux, " ");
        if (token != NULL) {
            valor = strtod(token, NULL);
            sistema->tabelaPontos[i] = calcularIntervalo(valor);
        }

        // Obtém a coordenada no eixo Y e calcula o intervalo
        token = strtok(NULL, " ");
        if (token != NULL) {
            valor = strtod(token, NULL);
            sistema->tabelaPontos[i] = calcularIntervalo(valor);
        }
    }    
}

void imprimir(struct ajustePol* sistema) {

    printf("Grau: %d\n", sistema->grauPol);
    printf("Quantidade de pontos: %d\n", sistema->qntdPontos);

    for (int i = 0; i < (sistema->qntdPontos) ; i++) {
        printf("X%d: %2.2f [%2.2f|%2.2f]  Y%d: %2.2f [%2.2f|%2.2f]\n", i, sistema->tabelaPontos[2*i].num, sistema->tabelaPontos[2*i].anterior, sistema->tabelaPontos[2*i].posterior, i, sistema->tabelaPontos[2*i+1].num, sistema->tabelaPontos[2*i+1].anterior, sistema->tabelaPontos[2*i+1].posterior);
    }
}

void destruirEstrutura(struct tabPontos* tabela) {

    free(tabela->vetPontos);
    free(tabela);
}