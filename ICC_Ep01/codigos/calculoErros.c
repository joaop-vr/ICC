#include "calculoErros.h"
#include <math.h>
#include <stdlib.h>

float calcularEA(struct operandos resultado) {

    float a,b, dif;

    a = resultado.anterior;
    b = resultado.posterior;
    dif = fabs(b-a);

    return dif;

}

float calcularER(struct operandos resultado) {

    float a, b, dif;
    a = resultado.anterior;
    b = resultado.posterior;

    if (a != 0)
        dif = fabs((b - a) / a);
    else
        dif = fabs(b - a);

    return dif;
}

int calcularULPs(struct operandos resultado) {
    
    Float_t a;
    Float_t b;
    a.f = resultado.anterior;
    b.f = resultado.posterior;

    int dif = abs(a.i - b.i);
    return dif - 1;
}