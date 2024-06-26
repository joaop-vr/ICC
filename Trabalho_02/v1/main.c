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
    double start, end, tsolSL, tgeraSL, tResSL;
    LIKWID_MARKER_START("minQuad");

    start = timestamp();
    sistema = minimosQuadrados(sistema); //Aplica o método dos mínimos quadrados para ajuste de curva
    end = timestamp();

    LIKWID_MARKER_STOP("minQuad");
    tgeraSL = end-start;

    LIKWID_MARKER_START("gauss");
    start = timestamp();
    gauss(sistema);
    end = timestamp();
    LIKWID_MARKER_STOP("gauss");
    tsolSL = end-start;
    
    #ifdef DEBUG
        imprimir(sistema);

        // Imprime os coeficientes do polinômio
        for (int i = 0; i < sistema->grauPol; i++)
            printf("[%1.8e,%1.8e]  ", sistema->coeficientes[i].anterior, sistema->coeficientes[i].posterior);
        printf("\n");
    #endif
    
    // Calcula e imprime os resíduos
    LIKWID_MARKER_START("residuos");
    start = timestamp();
    calculaResiduos(sistema);
    end = timestamp();
    LIKWID_MARKER_STOP("residuos");
    tResSL = end - start;
    
    LIKWID_MARKER_CLOSE;

    printf("%lf ", tgeraSL);
    printf("%lf ", tsolSL);
    printf("%lf\n", tResSL);
    fflush(stdout);
    // Libera a memória alocada nas structs
    destruirEstrutura(sistema);
  
    return 0;
}
