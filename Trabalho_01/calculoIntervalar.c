/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno:  , GRR:
 * 
****************************/

#include "calculoIntervalar.h"

struct operandos calcularIntervalo (double num) {

    struct operandos output;
    
    output.num = num;

    // Setando o arredondamento para baixo
    fesetround(FE_DOWNWARD);
    output.anterior = nextafter(num, -INFINITY);

    // Setando o arredondamento para cima
    fesetround(FE_UPWARD);
    output.posterior = nextafter(num, INFINITY);

    return output;

}

struct operandos calcularOperacao (struct operandos x, struct operandos y, char operador) {

    struct operandos resultado;
    
    switch (operador) {

        case '+':   // X + Y = [a+c, b+d]

            resultado.num = x.num + y.num;

            // Setando o arredondamento para baixo
            fesetround(FE_DOWNWARD);
            resultado.anterior = x.anterior + y.anterior;

            // Setando o arredondamento para cima
            fesetround(FE_UPWARD);
            resultado.posterior = x.posterior + y.posterior;

            break;

        case '-':   // X - Y = [a-d, b-c]            

            resultado.num = x.num - y.num;

            fesetround(FE_DOWNWARD);
            resultado.anterior = x.anterior - y.posterior;

            fesetround(FE_UPWARD);
            resultado.posterior = x.posterior - y.anterior;

            break;

        case '*':   // X * Y = [a,b] * [c,d]           

            resultado.num = x.num * y.num;    

            float aux[4];                     

            // Realizando multiplicações para o limite inferior
            fesetround(FE_DOWNWARD);
            aux[0] = x.anterior * y.anterior;
            aux[1] = x.anterior * y.posterior;
            aux[2] = x.posterior * y.anterior;
            aux[3] = x.posterior * y.posterior;

            resultado.anterior = min(aux);

            // Realizando multiplicações para o limite superior
            fesetround(FE_UPWARD);
            aux[0] = x.anterior * y.anterior;
            aux[1] = x.anterior * y.posterior;
            aux[2] = x.posterior * y.anterior;
            aux[3] = x.posterior * y.posterior;

            resultado.posterior = max(aux);

            break;

        case '/':  { // X / Y = [a,b] * [1/d,1/c],

            Float_t a;
            Float_t b;
            a.f = y.anterior;
            b.f = y.posterior;

            // Verificando se os intervalos possuem sinais opostos
            if (a.parts.sign != b.parts.sign) {
                resultado.anterior = -INFINITY;
                resultado.posterior = INFINITY;

            } else {

                resultado.num = x.num * y.num;

                float aux[4];

                // Realizando operações para o limite inferior
                fesetround(FE_DOWNWARD);
                aux[0] = x.anterior * (1/y.posterior);
                aux[1] = x.anterior * (1/y.anterior);
                aux[2] = x.posterior * (1/y.posterior);
                aux[3] = x.posterior * (1/y.anterior);

                resultado.anterior = min(aux);

                // Realizando operações para o limite superior
                fesetround(FE_UPWARD);
                aux[0] = x.anterior * (1/y.posterior);
                aux[1] = x.anterior * (1/y.anterior);
                aux[2] = x.posterior * (1/y.posterior);
                aux[3] = x.posterior * (1/y.anterior);

                resultado.posterior = max(aux);
            }

            break;
        }

        default:
            printf("Operador inválido.\n");
    }

    // Imprime os resultados e precisões
    imprimir(x, y, resultado, operador);

    return resultado;
}