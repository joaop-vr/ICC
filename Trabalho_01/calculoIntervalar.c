/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
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

struct operandos calcularOperacao (struct operandos x, struct operandos y, int expoente, char operador) {

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

            double aux[4];                     

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

                double aux[4];

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

        case '^': {

            Float_t a;
            Float_t b;
            a.f = x.anterior;
            b.f = x.posterior;
            double baseAnt, basePost;

            if (expoente == 0) {   //  [1,1], se expoente = 0 
                resultado.num = 1;
                resultado.anterior = 1;
                resultado.posterior = 1;
                break;
            }
            else if ((expoente % 2) != 0) {    // [a^expoente,b^expoente], se expoente é ímpar
                baseAnt = x.anterior;
                basePost = x.posterior;
            }
            else if (a.parts.sign == 0) {      //  [a^expoente,b^expoente], se expoente é par e a ≥ 0
                baseAnt = x.anterior;
                basePost = x.posterior;
            }
            else if (b.parts.sign == 1) {      // [b^expoente,a^expoente], se expoente é par e b < 0
                baseAnt = x.posterior;
                basePost = x.anterior;
            }
            else if ((a.parts.sign == 1) && (b.parts.sign == 0)) {  // [0,max{a^expoente,b^expoente}], se expoente é par e a < 0 ≤ b 
                
                double max, aExp, bExp;

                aExp = (double) pow(x.anterior, expoente);
                bExp = (double) pow(x.posterior, expoente);

                max = ((aExp - bExp) > FLT_EPSILON) ? aExp : bExp;

                resultado.num = (double) pow(x.num, expoente);
                resultado.anterior = 0;
                resultado.posterior = max;

                break;
            }

            resultado.num = (double) pow(x.num, expoente);

            fesetround(FE_DOWNWARD);
            resultado.anterior = (double) pow(baseAnt, expoente);

            fesetround(FE_UPWARD);
            resultado.posterior = (double) pow(basePost, expoente);

            break;
        }

        default:
            printf("Operador inválido.\n");
    }

    return resultado;
}
