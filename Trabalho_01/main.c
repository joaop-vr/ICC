#include "calculoIntervalar.h"
#include "operaEstrutura.h"
#include "minimosQuadrados.h"
#include "estruturas.h"
#include "auxiliares.h"
#include <likwid.h>

/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

int main() {

    LIKWID_MARKER_INIT;

    // Aloca as estruturas de dados necessárias e guarda a tabela de pontos
    struct ajustePol* sistema = montarEstrutura();
    double start, end, tsolSL, tgeraSL;
    LIKWID_MARKER_START("main");

    // Aplica o método dos mínimos quadrados para ajuste de curva
    start = timestamp();

    sistema = minimosQuadrados(sistema);

    end = timestamp();
    tgeraSL = end-start;

    start = timestamp();
    gauss(sistema);
    end = timestamp();
    tsolSL = end-start;
    
    // Imprime os coeficientes do polinômio
    for (int i = 0; i < sistema->grauPol; i++)
        printf("[%1.8e,%1.8e]  ", sistema->coeficientes[i].anterior, sistema->coeficientes[i].posterior);
    printf("\n");

    // Calcula e imprime os resíduos
    calculaResiduos(sistema);

    LIKWID_MARKER_STOP("main");

    LIKWID_MARKER_CLOSE;
    

    printf("%lf\n", tgeraSL);
    printf("%lf\n", tsolSL);

    // Áreea de testes
    // struct operandos x_teste = calcularIntervalo(2000);
    // struct operandos resultado = polinomio(sistema, x_teste);
    // printf("\n\nPara x = %.2lf, y = %.4lf\n", x_teste.num, resultado.num);

    // Libera a memória alocada nas structs
    destruirEstrutura(sistema);
  
    return 0;
}
