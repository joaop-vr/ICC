#include "estruturas.h"
#include "auxiliares.h"
#include "calculoIntervalar.h"
#include "minimosQuadrados.h"

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
    maior = vet[0]; 
    for (int i = 1; i < 4; i++) {
        dif = fabs(vet[i] - maior);

        // Verificando se o valor do vetor é o maior
        // levando em consideração a margem de erro (FLT_EPSILON)
        if ((vet[i] > maior) && (dif > FLT_EPSILON)) {
            maior = vet[i];
        }
    }

    return maior;
}

double min (double vet[4]) {

    double menor, dif;

    // Inicializa 'menor' com o valor absoluto do primeiro elemento
    menor = vet[0]; 
    for (int i = 1; i < 4; i++) {
        dif = fabs(vet[i] - menor);

        // Verificando se o valor do vetor é o menor
        // levando em consideração a margem de erro (FLT_EPSILON)
        if ((vet[i] < menor) && (dif > FLT_EPSILON)) {
            menor = vet[i];
        }
    }

    return menor;
}

void calculaResiduos(struct ajustePol* sistema) {

    printf("\nteste\n");
    

    struct operandos residuos[sistema->qntdPontos], FXi, Yi;

    for (int i = 0; i < sistema->qntdPontos; i++) {
        Yi = sistema->tabelaPontos[2*i+1];
        FXi = polinomio(sistema, sistema->tabelaPontos[2*i]);
        residuos[i] = calcularSubtracao(Yi, FXi);

        //printf("x%d: %1.8e  y%d: %1.8e\n", i, sistema->tabelaPontos[2*i].num, i, sistema->tabelaPontos[2*i+1].num);
        //printf("FX%d: %1.8e  Y%d: %1.8e\n\n", i, FXi.num, i, Yi.num);
        printf("%.4lf  [%.4lf | %.4lf]\n", residuos[i].num, residuos[i].anterior, residuos[i].posterior);
    }

}