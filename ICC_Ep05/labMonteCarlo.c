#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

double styblinski_tang(double points[], int dimensoes) {

    double x, x2;
    double sum = 0.0;
    
    for (int i = 0; i < dimensoes; i++) {
      x = points[i];
      x2 = x * x;
      sum += ((x2 * x2) - 16*x2 + 5 * x);
    }
    return sum / 2;
}

double integral_monte_carlo (double a, double b, int n_amostras, int n_dimensoes) {

  double point[n_dimensoes];
  double interval = b-a;
  double volume = pow(interval, n_dimensoes);
  int count = 0;

  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = %d\n", a, b, n_amostras, n_dimensoes);
  
  double t_inicial = timestamp();

  for (int i = 0; i < n_amostras; i++) {
    for (int j = 0; j < n_dimensoes; j++) {
      point[j] = NRAND * interval + a;
    }
    count += styblinski_tang(point, n_dimensoes);
  }
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f ms\n", t_final - t_inicial);

  return ((double)count / n_amostras) * volume;
}

double retangulos_xy(double a, double b, int npontos) {

  double resultado;double soma = 0;

  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d)\n", a, b, npontos);
  
  double t_inicial = timestamp();
  
  // deltaXi = espaçamento entre os pontos ao longo do eixo X
  double deltaXi; double x; double xi2, yj2;

  deltaXi = (b-a)/npontos;
  soma = 0.0;

  for (int i = 0; i < npontos; i++) {
    x = a + i * deltaXi;
    xi2 = x * x;
    soma += (xi2 * xi2 - 16 * xi2 + 5 * x) * npontos;
  }
  resultado = soma * deltaXi * deltaXi;

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
