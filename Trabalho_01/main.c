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

    calculaResiduos(sistema);

    printf("\nCoeficientes do polinomio:\n");
    for (int i = 0; i < sistema->grauPol; i++)
        printf("a%d = %1.8e  [%1.8e | %1.8e]\n", i, sistema->coeficientes[i].num, sistema->coeficientes[i].anterior, sistema->coeficientes[i].posterior);

    struct operandos x_teste = calcularIntervalo(2000);
    struct operandos resultado = polinomio(sistema, x_teste);
    printf("Para x = %.2lf, y = %.4lf\n", x_teste.num, resultado.num);
  
    return 0;
}
