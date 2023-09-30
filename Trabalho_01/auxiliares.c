#include "auxiliares.h"

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