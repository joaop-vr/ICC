/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno:  , GRR:
 * 
****************************/

#include "operaEstrutura.h"
#include "calculoIntervalar.h"
#include "minimosQuadrados.h"
#include "estruturas.h"

int main() {

    struct ajustePol* sistema = montarEstrutura();

    imprimir(sistema);

    minimosQuadrados(sistema);

    printf("\n\nCoeficientes do polinomio:\n");
    for (int i = 0; i < sistema->grauPol; i++)
        printf("a%d = %.4lf\n", i, sistema->coeficientes[i].num);

    double x_teste = 2000;
    double resultado = polinomio(sistema, x_teste);
    printf("Para x = %.2lf, y = %.4lf\n", x_teste, resultado);
  
    return 0;
}