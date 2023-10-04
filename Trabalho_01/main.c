/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#include "calculoIntervalar.h"
#include "operaEstrutura.h"
#include "minimosQuadrados.h"
#include "estruturas.h"

int main() {

    struct ajustePol* sistema = montarEstrutura();

    imprimir(sistema);

    minimosQuadrados(sistema);

    printf("\nCoeficientes do polinomio:\n");
    for (int i = 0; i < sistema->grauPol; i++)
        printf("a%d = %1.8e  [%1.8e | %1.8e]\n", i, sistema->coeficientes[i].num, sistema->coeficientes[i].anterior, sistema->coeficientes[i].posterior);

    printf("\n\n");
    for (int i = 0; i < sistema->grauPol; i++) {
        sistema->coeficientes[i] = calcularIntervalo(sistema->coeficientes[i].num);
        printf("a%d = %1.8e  [%1.8e | %1.8e]\n", i, sistema->coeficientes[i].num, sistema->coeficientes[i].anterior, sistema->coeficientes[i].posterior);
    }
    double x_teste = 2000;
    double resultado = polinomio(sistema, x_teste);
    printf("Para x = %.2lf, y = %.4lf\n", x_teste, resultado);
  
    return 0;
}
