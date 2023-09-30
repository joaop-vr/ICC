//#include "likwid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#include "operaEstrutura.h"
#include "calculoIntervalar.h"

struct sistemaLinear* montarEstrutura() {

    struct sistemaLinear* sistema = malloc(sizeof(struct sistemaLinear));
    sistema->tabela = malloc(sizeof(struct tabPontos));
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

    sistema->grauPolinomio = grau;
    sistema->tabela->qntdPontos = qntdPontos;    

    // Aloca o vetor que contém a tabela de pontos
    sistema->tabela->vetPontos = alocarVetor(2*qntdPontos);

    preencherEstrutura(sistema);

    return sistema;
}

void preencherEstrutura(struct sistemaLinear* sistema) {

    char aux[100], *token;
    double valor;
    int N;

    N = 2*sistema->tabela->qntdPontos;

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
            printf("x%d: %2.2f\n", 2*i, valor);
            sistema->tabela->vetPontos[i] = calcularIntervalo(valor);
        }

        // Obtém a coordenada no eixo Y e calcula o intervalo
        token = strtok(NULL, " ");
        if (token != NULL) {
            valor = strtod(token, NULL);
            printf("x%d: %2.2f\n", 2*i+1, valor);
            sistema->tabela->vetPontos[i] = calcularIntervalo(valor);
        }
    }    
}

void imprimir(struct sistemaLinear* sistema) {

    printf("Grau: %d\n", sistema->grauPolinomio);
    printf("Quantidade de pontos: %d\n", sistema->tabela->qntdPontos);

    for (int i = 0; i < (sistema->tabela->qntdPontos) ; i++) {
        printf("X%d: %2.2f [%2.2f|%2.2f]  Y%d: %2.2f [%2.2f|%2.2f]\n", i, sistema->tabela->vetPontos[2*i].num, sistema->tabela->vetPontos[2*i].anterior, sistema->tabela->vetPontos[2*i].posterior, i, sistema->tabela->vetPontos[2*i+1].num, sistema->tabela->vetPontos[2*i+1].anterior, sistema->tabela->vetPontos[2*i+1].posterior);
    }
}

struct operandos* alocarVetor(int N) {

    // Alocação dinâmica da vetor
    struct operandos *vet = (struct operandos *)malloc(N * sizeof(struct operandos));

    if (!(vet)) {
        fprintf(stderr, "Erro falha ao alocar vetor.\n");
        exit(1);
    }

    return vet;
}

void destruirEstrutura(struct tabPontos* tabela) {

    free(tabela->vetPontos);
    free(tabela);
}