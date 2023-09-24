#include "likwid.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "auxiliares.h"
#include "elimGauss.h"

struct sistemaLinear* montarSistema() {

    int N;
    struct sistemaLinear* sistema = malloc(sizeof(struct sistemaLinear));

    // Lê a ordem da matriz
    if (scanf("%d", &N) != 1) {
        printf("Erro na leitura de entrada.\n");
        exit(1);
    }

    // Alocando os campos do sistema
    sistema->ordem = N;
    sistema->matriz = alocarMatriz(N);
    sistema->constantes = alocarVetor(N);
    sistema->solucoes = alocarVetor(N);
    sistema->residuos = alocarVetor(N);

    // Alocando os campos do backup do sistema
    sistema->backup = malloc(sizeof(struct sistemaLinear));
    sistema->backup->ordem = N;
    sistema->backup->matriz = alocarMatriz(N);
    sistema->backup->constantes = alocarVetor(N);
    sistema->backup->solucoes = alocarVetor(N);
    sistema->backup->residuos = NULL;
    sistema->backup->backup = NULL;

    preencherSistema(sistema, N);

    return sistema;
}

double** alocarMatriz(int N) {

    // Alocação dinâmica da matriz
    double **matriz = (double **)malloc(N * sizeof(double *));

    if (!(matriz)) {
        printf("Erro: falha ao alocar matriz!.\n");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        matriz[i] = (double *)malloc(N * sizeof(double));
        if (!(matriz[i])) {
            printf("Erro: falha ao alocar matriz!.\n");
            exit(1);
        }
    }

    return matriz;
}

double* alocarVetor(int N) {

    // Alocação dinâmica da vetor
    double *vet = (double *)malloc(N * sizeof(double));

    if (!(vet)) {
        printf("Erro: falha ao alocar matriz!.\n");
        exit(1);
    }

    return vet;
}

void preencherSistema(struct sistemaLinear* sistema, int N) {

    double valor;

    // Preenche o sistema com os valores passados pelo usuário
    for (int l = 0; l < N; l++) {
        for (int c = 0; c < N; c++) {

            // Lê os coeficientes da matriz
            if (scanf("%lf", &valor) != 1) {
                printf("Erro na leitura de entrada.\n");
                exit(1);
            }
            sistema->matriz[l][c] = valor;
            sistema->backup->matriz[l][c] = valor;
        }

        // Lê as contantes do sistema
        if (scanf("%lf", &valor) != 1) {
            printf("Erro na leitura de entrada.\n");
            exit(1);
        }
        sistema->constantes[l] = valor;
        sistema->backup->constantes[l] = valor;
    }
}

void imprimirSistema(struct sistemaLinear* sistema, int N) {

    for (int l = 0; l < N; l++) {
        for (int c = 0; c < N; c++) {
            printf("%2f  ", sistema->matriz[l][c]);
        }
        
        printf("%2f", sistema->constantes[l]);
        printf("\n");
    }
}

void reiniciarSistema(struct sistemaLinear* sistema) {

    for (int l = 0; l < sistema->ordem; l++) {
        for (int c = 0; c < sistema->ordem; c++)
            sistema->matriz[l][c] = sistema->backup->matriz[l][c];

        sistema->constantes[l] = sistema->backup->constantes[l];
        sistema->solucoes[l] = 0.0;
        sistema->residuos[l] = 0.0;
    }
}

double timestamp() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)(tp.tv_sec * 1000.0 + tp.tv_usec / 1000.0));
}

void imprimirSaida(struct sistemaLinear* sistema, int modelo, double dif) {

    printf("\n##### METODO %d #####\n", modelo);

    printf("\nX = [");
    for (int i = 0; i < sistema->ordem; i++) {
        printf(" %.5f ", sistema->solucoes[i]);
    }
    printf("]\n");

    printf("\nTempo medio: %.5f\n", dif);

    calcularResiduo(sistema);
    printf("\nResiduos:\n");
    for (int i = 0; i < sistema->ordem; i++) {
        printf("linha %d: %2f\n", i+1, sistema->residuos[i]);
    }    
}

void calcularResiduo(struct sistemaLinear* sistema) {

    for (int l = 0; l < sistema->ordem; l++) {
        sistema->residuos[l] = 0.0;
        for (int c = 0; c < sistema->ordem; c++) {
            sistema->residuos[l] += sistema->backup->matriz[l][c]*sistema->solucoes[c]; // Calculando a parte esqeurda da equação
        }
        sistema->residuos[l] -= sistema->backup->constantes[l];     // Subtraindo a parte direita da parte esquerda da equação
    }   
}

void destruirSistema(struct sistemaLinear* sistema) {

    for (int i = 0; i < sistema->ordem; i++) {
        free(sistema->matriz[i]);
    }
    free(sistema->matriz);
    free(sistema->constantes);
    free(sistema->solucoes);
    free(sistema->residuos);

    for (int i = 0; i < sistema->ordem; i++) {
        free(sistema->backup->matriz[i]);
    }
    free(sistema->backup->matriz);
    free(sistema->backup->constantes);
    free(sistema->backup->solucoes);
    free(sistema->backup);
    free(sistema);
}