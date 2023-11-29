/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#include "operaEstrutura.h"
#include "calculoIntervalar.h"

// Aloca os componentes de ajustepol e então chama a função preencherEstrutura()
struct ajustePol* montarEstrutura() {

    struct ajustePol* sistema = malloc(sizeof(struct ajustePol));
    int grau;
    long long int qntdPontos;

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

    grau += 1; // pois o primeiro índice do vetor é o 0
    sistema->grauPol = grau;
    sistema->qntdPontos = qntdPontos;    

    sistema->matriz = alocarMatriz(grau);
    sistema->resultados = alocarVetor(grau);
    sistema->coeficientes = alocarVetor(grau);
    sistema->tabelaPontos = alocarVetor(2*qntdPontos);    

    preencherEstrutura(sistema);

    return sistema;
}

// Preenche a struct ajustePol com os pontos da tabela
void preencherEstrutura(struct ajustePol* sistema) {

    char aux[100], *token;
    double valor;
    long long int N;

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

// Imprime todos os metadados da struct ajustePol
void imprimir(struct ajustePol* sistema) {

    printf("Grau: %d\n", sistema->grauPol);
    printf("Quantidade de pontos: %ld\n", sistema->qntdPontos);

    for (int i = 0; i < sistema->grauPol; i++) {
        for (int j = 0; j < sistema->grauPol; j++) {
            printf("%2.4lf ", sistema->matriz[i][j].num);
        }
        printf(" = %2.4lf\n", sistema->resultados[i].num);
    }

    // for (long long int i = 0; i < (sistema->qntdPontos) ; i++) {
    //     printf("X%d: %1.8e [%1.8e|%1.8e]  Y%d: %1.8e [%1.8e|%1.8e]\n",
    //         i, sistema->tabelaPontos[2*i].num, sistema->tabelaPontos[2*i].anterior, 
    //         sistema->tabelaPontos[2*i].posterior, i, sistema->tabelaPontos[2*i+1].num, 
    //         sistema->tabelaPontos[2*i+1].anterior, sistema->tabelaPontos[2*i+1].posterior);
    // }
}

// Desaloca toda a struct ajustePol
void destruirEstrutura(struct ajustePol* sistema) {

    for (int i = 0; i < sistema->grauPol; i++) {
        free(sistema->matriz[i]);
    }
    free(sistema->matriz);
    free(sistema->resultados);
    free(sistema->coeficientes);
    free(sistema->tabelaPontos);
}