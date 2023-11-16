#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

double styblinski_tang(double x[10], int n) {

    double xi2;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        xi2 = x[i] * x[i];
        sum += (xi2 * xi2 - 16 * xi2 + 5 * x[i]);
    }

    return sum * 0.5;
}

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double integral_monte_carlo(double a, double b, int namostras, int d)
{
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = %d\n", a, b, namostras, d);
  
  double t_inicial = timestamp();
  
  int count = 0;
  double interval = (b -a);

  for (int i = 0; i < namostras; i++) {
    double point[10];
    for (int j = 0; j < d; j++) {
      point[j] = ((double)random() / RAND_MAX) * (interval) + a;
    }

    if (styblinski_tang(point, d) <= 0) {
      count++;
    }
  }

  double volume = pow(interval, d);
  double resultado = ((double)count / namostras) * volume;

  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


double retangulos_xy(double a, double b, int npontos) {

  double resultado;
  double soma = 0;

  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d)\n", a, b, npontos);
  
  double t_inicial = timestamp();
  
  // deltaXi = espaçamento entre os pontos ao longo do eixo X
  double deltaXi;
  double point[2];

  deltaXi = (b-a)/npontos;
  soma = 0.0;
  for (int i = 0; i < npontos; i++) {
    point[0] = a + i * deltaXi;
    for (int j = 0; j < npontos; j++) {
      point[1] = a + j * deltaXi;
      soma += styblinski_tang(point, 2);
    }
  }

  resultado = soma*deltaXi*deltaXi;

  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


int main(int argc, char **argv) {

  if (argc < 5) {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  }
  double a = atoi(argv[1]);
  double b = atoi(argv[2]);
  int n_amostras = atoi(argv[3]);
  int n_dimensoes = atoi(argv[4]);

  // INICIAR VALOR DA SEMENTE
  srandom(20232);
    
  // CHAMAR FUNÇÕES DE INTEGRAÇÃO E EXIBIR RESULTADOS
  double area = integral_monte_carlo(a, b,n_amostras,n_dimensoes);
  printf("área utilizando monte carlo = %lf\n", area);
  area = retangulos_xy(a,b,n_amostras);
  printf("área utilizando retangulos = %lf\n", area);
  return 0;
}
