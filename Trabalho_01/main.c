/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno:  , GRR:
 * 
****************************/

#include "operaEstrutura.h"
#include "calculoIntervalar.h"
#include "estruturas.h"
#include <stdlib.h>

int main() {

    struct sistemaLinear* sistema = montarEstrutura();

    imprimir(sistema);
  
    return 0;
}