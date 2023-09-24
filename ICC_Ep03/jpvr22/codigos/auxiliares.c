#include "likwid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#include "auxiliares.h"

struct tabPontos* montarEstrutura(char *argv[]) {

    int N;
    struct tabPontos* tabela = malloc(sizeof(struct tabPontos));

    // Lê o número de pontos
    if (scanf("%d", &N) != 1) {
        fprintf(stderr, "Erro na leitura de entrada.\n");
        exit(1);
    }

    tabela->N = N;

    // Alocando os campos da struct
    tabela->vetPontos = alocarVetor(2*N);

    preencherEstrutura(tabela, 2*N, argv);

    return tabela;
}

void preencherEstrutura(struct tabPontos* tabela, int N, char *argv[]) {

    char aux[100], *token;
    double min, max;


    token = strtok(argv[1], " ");
    tabela->xe = strtod(token, NULL);

    min = 0.0;
    max = 0.0;
    for (int i = 0; i < N ; i++) {

        if (scanf("%s", aux) != 1) {
            fprintf(stderr, "Erro na leitura de entrada.\n");
            exit(1);
        }   

        token = strtok(aux, " ");
        if (token != NULL)
            tabela->vetPontos[i] = strtod(token, NULL);

        if (i == 0) {
            min = tabela->vetPontos[i];
            max = tabela->vetPontos[i];
        }

        // Obtendo os limites superiores e inferiores do intervalo de pontos no eixo X
        if ((i % 2) == 0) {
            if (tabela->vetPontos[i] < min)
                min = tabela->vetPontos[i];

            if (max < tabela->vetPontos[i])
                max = tabela->vetPontos[i];
        }        

        token = strtok(NULL, " ");
        if (token != NULL)
            tabela->vetPontos[i] = strtod(token, NULL);
    }

    // Atribuindo os limites superiores e inferiores do intervalo de pontos
    tabela->limiteInf = min;
    tabela->limiteSup = max;
    
}

void imprimir(struct tabPontos* tabela) {

    printf("N: %d\n", tabela->N);
    printf("xe: %lf\n", tabela->xe);
    printf("Limite superior: %2f\n", tabela->limiteSup);
    printf("Limite inferior: %2f\n", tabela->limiteInf);

    for (int i = 0; i < (tabela->N) ; i++) {
        printf("X%d: %2f   Y%d: %2f\n", i, tabela->vetPontos[2*i], i, tabela->vetPontos[2*i+1]);
    }
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

double timestamp() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)(tp.tv_sec * 1000.0 + tp.tv_usec / 1000.0));
}

void verificarIntervalo(struct tabPontos* tabela) {

    if ((tabela->xe < tabela->limiteInf) || (tabela->limiteSup < tabela->xe)) {
        fprintf(stderr, "O valor de xe nao pertence ao intervalo da tabela de pontos.\n");
        exit(1);
    }
}

void destruirEstrutura(struct tabPontos* tabela) {

    free(tabela->vetPontos);
    free(tabela);
}