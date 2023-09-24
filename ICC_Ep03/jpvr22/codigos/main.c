#include <likwid.h>
#include <stdio.h>
#include <stdlib.h>

#include "metodosInterpol.h"
#include "auxiliares.h"

int main(int argc, char *argv[]) {
    
    struct tabPontos* tabela = montarEstrutura(argv);
    double tempExec_1, tempExec_2;

    verificarIntervalo(tabela);

    LIKWID_MARKER_INIT;

    // Interpolação de Lagrange
    tempExec_1 = interpolLagrange(tabela);
    printf("%2.5lf\n", tabela->Px);
    
    // Interpolação de Newton
    tabela->Px = 0.0;
    tempExec_2 = interpolNewton(tabela);
    printf("%2.5lf\n", tabela->Px);

    printf("%2.5lf\n%2.5lf\n", tempExec_1, tempExec_2);

    LIKWID_MARKER_CLOSE;

    // Desalocando sistema
    destruirEstrutura(tabela);

    return 0;
}
