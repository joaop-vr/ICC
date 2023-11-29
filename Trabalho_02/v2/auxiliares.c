/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#include "estruturas.h"
#include "auxiliares.h"
#include "calculoIntervalar.h"
#include "minimosQuadrados.h"
#include <time.h>
#include <likwid.h>

// Aloca um vetor de structs operandos* de tamanho N e retorna um ponteiro para ele
struct operandos* alocarVetor(int N) {

    // Alocação dinâmica da vetor
    struct operandos *vet = (struct operandos *)malloc(N * sizeof(struct operandos));

    if (!(vet)) {
        fprintf(stderr, "Erro falha ao alocar vetor.\n");
        exit(1);
    }

    return vet;
}

// Aloca uma matriz de structs operandos* de tamanho NxN e retorna um ponteiro para ela
struct operandos** alocarMatriz(int N) {

    // Alocação dinâmica da matriz
    struct operandos** matriz = (struct operandos**)malloc(N * sizeof(struct operandos*));

    if (!(matriz)) {
        fprintf(stderr, "Erro falha ao alocar vetor.\n");
        exit(1);
    }

    matriz[0] = malloc(N * N * sizeof(struct operandos));

    for (int i = 1; i < N; i++) {
        matriz[i] = matriz[0] + i * N;
        if (!(matriz[i])) {
            fprintf(stderr, "Erro falha ao alocar vetor.\n");
            exit(1);
        }
    }

    return matriz;
}

// Retorna o maior elemento de vet[4]
double max (double vet[4]) {

    double maior, dif;

    // Inicializa 'maior' com o valor do primeiro elemento
    maior = vet[0]; 
    for (int i = 1; i < 4; i++) {
        dif = fabs(vet[i] - maior);

        // Verificando se o valor do vetor é o maior
        // levando em consideração a margem de erro (DBL_EPSILON)
        if ((vet[i] > maior) && (dif > DBL_EPSILON)) {
            maior = vet[i];
        }
    }

    return maior;
}

// retorna o menor elemento de vet[4]
double min (double vet[4]) {

    double menor, dif;

    // Inicializa 'menor' com o valor do primeiro elemento
    menor = vet[0]; 
    for (int i = 1; i < 4; i++) {
        dif = fabs(vet[i] - menor);

        // Verificando se o valor do vetor é o menor
        // levando em consideração a margem de erro (DBL_EPSILON)
        if ((vet[i] < menor) && (dif > DBL_EPSILON)) {
            menor = vet[i];
        }
    }

    return menor;
}

// Retorna um valor de tempo atual em milissegundos, usando o tempo do sistema operacional
double timestamp(void){
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    return ((double)tp.tv_sec*1.0e3 + (double)tp.tv_nsec*1.0e-6);
}

// Calcula o resíduo de cada ponto e imprime o intervalo
void calculaResiduos(struct ajustePol* sistema) {    

    struct operandos *residuos = malloc(sistema->qntdPontos*(sizeof(struct operandos)));
    struct operandos FXi, Yi;

    // Percorre pela tabela de pontos calculando o resíduo de cada f(Xi)
    for (int i = 0; i < sistema->qntdPontos - sistema->qntdPontos%4; i+=4) {
        Yi = sistema->pontos_y[i];
        FXi = polinomio(sistema, sistema->pontos_x[i]);
        residuos[i] = calcularSubtracao(Yi, FXi);
        Yi = sistema->pontos_y[i+1];
        FXi = polinomio(sistema, sistema->pontos_x[i+1]);
        residuos[i+1] = calcularSubtracao(Yi, FXi);
        Yi = sistema->pontos_y[i+2];
        FXi = polinomio(sistema, sistema->pontos_x[i+2]);
        residuos[i+2] = calcularSubtracao(Yi, FXi);
        Yi = sistema->pontos_y[i+3];
        FXi = polinomio(sistema, sistema->pontos_x[i+3]);
        residuos[i+3] = calcularSubtracao(Yi, FXi);
        //printf("[%1.8e,%1.8e]  ", residuos[i].anterior, residuos[i].posterior);
    }
    for (int i = sistema->qntdPontos - sistema->qntdPontos%4; i < sistema->qntdPontos; i++) {
        Yi = sistema->pontos_y[i];
        FXi = polinomio(sistema, sistema->pontos_x[i]);
        residuos[i] = calcularSubtracao(Yi, FXi);
    }
}