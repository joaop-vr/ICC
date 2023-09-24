#include "auxiliares.h"
#include "calculoErros.h"
#include "principais.h"
#include "estruturas.h"

int main() {

    char operadores[4];
    float valores[5];

    obterExpressao(operadores, valores);

    struct operandos a, b;
    a = calcularIntervalo(valores[0]);

    // Percorre o vetor valores[] efetuando as operações
    for (int i = 0; i < 4; i++) {
        b = calcularIntervalo(valores[i+1]);
        printf("\n%i:\n", i+1);
        a = calcularOperacao(a, b, operadores[i]);
    }

    return 0;
}