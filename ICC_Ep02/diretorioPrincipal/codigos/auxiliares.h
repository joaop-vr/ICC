#ifndef AUXILIARES_H_
#define AUXILIARES_H_

/***************************
 * Stuct sistemaLinear corresponde a todos os componentes de um sistema linear AX = B de ordem N
 * 
 * N = int ordem
 * A = double** matriz
 * B = double* constantes
 * X = double* solucoes
 * 
 * O componente "struct sistemaLinear* backup" servirá para que possamos solucionar o sistema
 * mais de uma vez
 * 
 * O componente "double* residuos" será utilizado na hora de contabilizar 
 * o resíduo do sistema
 * 
****************************/
struct sistemaLinear {
    int ordem;
    double** matriz;        
    double* constantes;
    double* solucoes;
    struct sistemaLinear* backup;
    double* residuos;
};

// Aloca a struct sistemaLinear e seus respectivos componentes e chama a função preencherSistema()
struct sistemaLinear* montarSistema();

// Aloca dinâmicamente a matriz de ordem N
double** alocarMatriz(int N);

// Aloca dinâmicamente o vetor de ordem N
double* alocarVetor(int N);

// Preenche o sistema com valores passados pelo usuário
void preencherSistema(struct sistemaLinear* sistema, int N);

// Imprime o sistema
void imprimirSistema(struct sistemaLinear* sistema, int N);

// Reinicia o sistema com os valores inicialmente passados pelo usuário
void reiniciarSistema(struct sistemaLinear* sistema);

// Gera na saída padrão a solução do SL, o tempo médio de cálculo da solução e o resíduo
void imprimirSaida(struct sistemaLinear* sistema, int modelo, double dif);

// Calcula o tempo médio de cálculo da solução
double timestamp();

// Calcula o resídup de cada linha do SL
void calcularResiduo(struct sistemaLinear* sistema);

// Libera a memória da matriz de ordem N
void destruirSistema(struct sistemaLinear* sistema);

#endif