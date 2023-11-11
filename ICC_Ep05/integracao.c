#include <stdio.h>
#include <stdlib.h>


/*****************************************
 * 
 * função styblinskiTang retorna o resultado
 * da função homônica 
 * 
 * double x = 
 * 
*******************************************/
double styblinskiTang (double x) {

    double output, x2;

    x2 = x*x;
    output = ((x2*x2) - (16*x2) + (5*x))/2;

    return output;
}

/*****************************************
 * 
 * função metodoRetang implementa a integração númerica 
 * por meio do método dos retângulos
 * 
 * (*funcao) = função sobre a qual o método de integração será aplicado
 * double a = limite inferior do intervalo de pontos
 * double b = limite superior do intervalo de pontos
 * int n = quantidade de pontos na amostra
 * 
*******************************************/
double metodoRetang (double (*funcao)(double), double a, double b, int n) {

    // deltaXi = espaçamento entre os pontos ao longo do eixo X
    double deltaXi, soma;

    deltaXi = (b-a)/n;
    soma = 0.0;
    for (int i = 0; i < n; i++) 
        soma += funcao(a + (deltaXi*i));

    return soma*deltaXi;
}

/*****************************************
 * 
 * função mediaMonteCarlo implementa a integração númerica 
 * por meio do método de Monte Carlo pela média
 * 
 * (*funcao) = função sobre a qual o método de integração será aplicado
 * double a = limite inferior do intervalo de pontos
 * double b = limite superior do intervalo de pontos
 * int n = quantidade de pontos na amostra
 * 
*******************************************/
double mediaMonteCarlo (double (*funcao)(double), double a, double b, int n) {

    double x, soma, aleatorio, intervalo;

    soma = 0.0;
    intervalo = b - a;
    for (int i = 0; i < n; i++) {
        aleatorio = ((double) random() / RAND_MAX);
        x = a + aleatorio*intervalo;
        soma += funcao(x);
    }

    return (soma/n)*intervalo;
}