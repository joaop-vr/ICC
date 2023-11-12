#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

double styblinski_tang(double x[10], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += 0.5 * (pow(x[i], 4) - 16 * pow(x[i], 2) + 5 * x[i]);
    }
    return sum;
}

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double integral_monte_carlo(double a, double b, int namostras, int d)
{
  double soma = 0.0;
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = %d\n", a, b, namostras, d);
  
  double t_inicial = timestamp();
  

  /*
    
    AQUI IMPLEMENTE O CÁLCULO DA INTEGRAL  PELO
    MÉTODO DE MONTE CARLO
    
  */
  
  int count = 0;

  for (int i = 0; i < namostras; i++) {
      double point[10];
      for (int j = 0; j < d; j++) {
          point[j] = ((double)rand() / RAND_MAX) * (b - a) + a;
      }

      if (styblinski_tang(point, d) <= 0) {
          count++;
      }
  }

  double volume = pow(b - a, d);
  double resultado = ((double)count / namostras) * volume;

  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


double retangulos_xy(double a, double b, int npontos) {

  double h;
  double resultado;
  double soma = 0;
  
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);
  
  double t_inicial = timestamp();
  
  /*
    
    AQUI IMPLEMENTE O CÁLCULO DA INTEGRAL PELO
    MÉTODO DOS RETÂNGULOS
    
  */
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


int main(int argc, char **argv) {

  if (argc < 5) {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  }

  // INICIAR VALOR DA SEMENTE
  srandom(20232);
    
  // CHAMAR FUNÇÕES DE INTEGRAÇÃO E EXIBIR RESULTADOS
  double area = integral_monte_carlo(atoi(argv[1]), atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
  printf("área = %lf\n", area);
  return 0;
}

