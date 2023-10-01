#include "estruturas.h"
#include "auxiliares.h"

struct operandos* alocarVetor(int N) {

    // Alocação dinâmica da vetor
    struct operandos *vet = (struct operandos *)malloc(N * sizeof(struct operandos));

    if (!(vet)) {
        fprintf(stderr, "Erro falha ao alocar vetor.\n");
        exit(1);
    }

    return vet;
}

struct operandos** alocarMatriz(int N) {

    // Alocação dinâmica da matriz
    struct operandos** matriz = (struct operandos**)malloc(N * sizeof(struct operandos*));

    if (!(matriz)) {
        fprintf(stderr, "Erro falha ao alocar vetor.\n");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        matriz[i] = (struct operandos*)malloc(N * sizeof(struct operandos));
        if (!(matriz[i])) {
            fprintf(stderr, "Erro falha ao alocar vetor.\n");
            exit(1);
        }
    }

    return matriz;
}

double max (double vet[4]) {

    double maior, dif;

    // Inicializa 'maior' com o valor absoluto do primeiro elemento
    maior = fabs(vet[0]); 
    for (int i = 1; i < 4; i++) {
        dif = fabs(vet[i] - maior);

        // Verificando se o valor do vetor é o maior
        // levando em consideração a margem de erro (FLT_EPSILON)
        if ((fabs(vet[i]) > maior) && (dif > FLT_EPSILON)) {
            maior = fabs(vet[i]);
        }
    }

    return maior;
}

double min (double vet[4]) {

    double menor, dif;

    // Inicializa 'menor' com o valor absoluto do primeiro elemento
    menor = fabs(vet[0]); 
    for (int i = 1; i < 4; i++) {
        dif = fabs(vet[i] - menor);

        // Verificando se o valor do vetor é o menor
        // levando em consideração a margem de erro (FLT_EPSILON)
        if ((fabs(vet[i]) < menor) && (dif > FLT_EPSILON)) {
            menor = fabs(vet[i]);
        }
    }

    return menor;
}