#include "auxiliares.h"
#include "calculoErros.h"
#include <math.h>
#include <string.h>

#define MAX 100

void obterExpressao(char operadores[4], float valores[5]) {
    char *token, expressao[MAX];
    int i, j, k;

    printf("Expressao: ");
    scanf("%[^\n]", expressao);
    getchar();

    i = 0;  // contagem de token obtidos da expresao
    j = 0;  // indice do vetor valores[]
    k = 0;  // indice do vetor operadores[]

    // Variavel token recebe o primeiro valor da operação aritmética 
    token = strtok(expressao, " ");
    
    while (token != NULL) {
        if (i % 2 != 0) {
            operadores[k] = token[0]; // Armazenar diretamente o caractere como operador;
            k++;
        } else {
            sscanf(token, "%e", &valores[j]); // Converter a string para um número float
            j++;
        }
        token = strtok(NULL, " ");
        i++;
    }
}

void imprimir(struct operandos x, struct operandos y, struct operandos resultado, char operador) {

    printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] =\n[%1.8e,%1.8e]\n",
    x.anterior, x.posterior, operador, y.anterior, y.posterior,
    resultado.anterior, resultado.posterior);

    printf("EA: %1.8e; ER: %1.8e; ULPs: %d\n", calcularEA(resultado), calcularER(resultado), calcularULPs(resultado));

}

float max (float vet[4]) {

    float maior, dif;

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

float min (float vet[4]) {

    float menor, dif;

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