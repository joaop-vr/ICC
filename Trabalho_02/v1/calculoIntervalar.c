/***************************
 * Aluno: Joao Pedro Vicente Ramalho, GRR: 20224169
 * Aluno: Mateus Kater Pombeiro, GRR: 20190366
****************************/

#include "calculoIntervalar.h"

// Parâmetros: número float
// Retorno: struct operandos com o intervalo que compreende o número fornecido
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

// Parâmetro: structs operandos X e Y
// Retorno: struct operandos com o resultado da soma de X e Y e seus intervalos
struct operandos calcularSoma(struct operandos x, struct operandos y) {

    struct operandos resultado;

    resultado.num = x.num + y.num;

    fesetround(FE_DOWNWARD);
    resultado.anterior = x.anterior + y.anterior;

    fesetround(FE_UPWARD);
    resultado.posterior = x.posterior + y.posterior;

    return resultado;
}

// Parâmetro: structs operandos X e Y
// Retorno: struct operandos com o resultado da subtração de X por Y e seus intervalos
struct operandos calcularSubtracao(struct operandos x, struct operandos y) {

    struct operandos resultado;

    resultado.num = x.num - y.num;

    fesetround(FE_DOWNWARD);
    resultado.anterior = x.anterior - y.posterior;

    fesetround(FE_UPWARD);
    resultado.posterior = x.posterior - y.anterior;

    return resultado;
}

// Parâmetro: structs operandos X e Y
// Retorno: struct operandos com o resultado da multiplicação entre X e Y e seus intervalos
struct operandos calcularMultiplicacao(struct operandos x, struct operandos y) {

    struct operandos resultado;
    double aux[4];   

    if ((fabs(x.num) < DBL_EPSILON) || (fabs(y.num) < DBL_EPSILON)) {
        resultado.num = 0.0;
        resultado.anterior = 0.0;
        resultado.posterior = 0.0;
    }
    else {

        resultado.num = x.num * y.num;      

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
        
        resultado.anterior = min(aux);
    }

    return resultado;
}

// Parâmetro: structs operandos X e Y
// Retorno: struct operandos com o resultado da divisão de X por Y e seus intervalos
struct operandos calcularDivisao(struct operandos x, struct operandos y) {

    struct operandos resultado;
    Float_t a;
    Float_t b;
    a.f = y.anterior;
    b.f = y.posterior;

    resultado.num = x.num / y.num;

    // Verificando se os intervalos possuem sinais opostos
    if (a.parts.sign != b.parts.sign) {
        resultado.anterior = -INFINITY;
        resultado.posterior = INFINITY;

    } else {

        double aux[4];

        // Realizando operações para o limite inferior
        fesetround(FE_DOWNWARD);
        double dPosterior = 1/y.anterior;
        double dAnterior = 1/y.posterior;

        aux[0] = x.anterior * (dPosterior);
        aux[1] = x.anterior * (dAnterior);
        aux[2] = x.posterior * (dPosterior);
        aux[3] = x.posterior * (dAnterior);

        resultado.anterior = min(aux);

        // Realizando operações para o limite superior
        fesetround(FE_UPWARD);

        aux[0] = x.anterior * (dPosterior);
        aux[1] = x.anterior * (dAnterior);
        aux[2] = x.posterior * (dPosterior);
        aux[3] = x.posterior * (dAnterior);

        resultado.posterior = max(aux);
    }

    return resultado;
}

// Parâmetro: struct operando X e 
// Retorno: struct operandos com o resultado da exponenciação de X por i e seus intervalos
struct operandos calcularExpo(struct operandos x, int expoente) {

    struct operandos resultado;

    Float_t a;
    Float_t b;
    a.f = x.anterior;
    b.f = x.posterior;
    double baseAnt, basePost;

    if (expoente == 0) {   //  [1,1], se expoente = 0 
        resultado.num = 1;
        resultado.anterior = 1;
        resultado.posterior = 1;
        return resultado;
    }
    else if ((expoente % 2) != 0) {    // [a^expoente,b^expoente], se expoente é ímpar
        baseAnt = x.anterior;
        basePost = x.posterior;
    }
    else if (a.parts.sign == 0) {      //  [a^expoente,b^expoente], se expoente é par e a ≥ 0
        baseAnt = x.anterior;
        basePost = x.posterior;
    }
    else if ((b.parts.sign == 1) && (fabs(x.posterior) > DBL_EPSILON)){      // [b^expoente,a^expoente], se expoente é par e b < 0
        baseAnt = x.posterior;
        basePost = x.anterior;
    }
    else if ((a.parts.sign == 1) && ((b.parts.sign == 0) || (fabs(x.posterior) < DBL_EPSILON))) {  // [0,max{a^expoente,b^expoente}], se expoente é par e a < 0 ≤ b 
        
        double max, aExp, bExp;

        fesetround(FE_DOWNWARD);
        aExp = (double) pow(x.anterior, expoente);

        fesetround(FE_UPWARD);
        bExp = (double) pow(x.posterior, expoente);

        // max recebe o maior valor, entre a^expoente e b^expoente
        max = ((aExp - bExp) >= DBL_EPSILON) ? aExp : bExp;

        resultado.num = (double) pow(x.num, expoente);
        resultado.anterior = 0;
        resultado.posterior = max;

        return resultado;
    }

    resultado.num = (double) pow(x.num, expoente);

    fesetround(FE_DOWNWARD);
    resultado.anterior = (double) pow(baseAnt, expoente);

    fesetround(FE_UPWARD);
    resultado.posterior = (double) pow(basePost, expoente);

    return resultado;

}