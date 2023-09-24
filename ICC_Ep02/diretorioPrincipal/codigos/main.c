#include <likwid.h>
#include <stdio.h>
#include <stdlib.h>

#include "elimGauss.h"

int main(int argc, char const *argv[]) {
    
    struct sistemaLinear* sistema = montarSistema();
    double tempExec;

    LIKWID_MARKER_INIT;

    // Primeiro Método
    tempExec = elimGaussClassico(sistema);
    imprimirSaida(sistema, 1, tempExec);

    
    // Segundo Método
    reiniciarSistema(sistema);
    tempExec = elimGaussSemMulti(sistema);
    imprimirSaida(sistema, 2, tempExec);
 
    
    // Terceiro Método
    reiniciarSistema(sistema);
    tempExec = elimGaussAlternativa(sistema);
    imprimirSaida(sistema, 3, tempExec);


    // Desalocando sistema
    destruirSistema(sistema);

    LIKWID_MARKER_CLOSE;

    return 0;
}
