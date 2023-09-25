#ifndef AUXILIARES_H_
#define AUXILIARES_H_

/***************************
 * Stuct dadosPolinomio corresponde aos dados referente ao polinômio
 * com o qual estamos trabalhando
 * 
 * N = número de conjunto de pontos
 * xe = valor de "xe" passado pelo usuário
 * Px = valor de Pk(xe)
 * limiteSup = limite superior do intervalo de pontos
 * limiteInf = limite inferior do intervalo de pontos
 * vetPontos = vetor com os pontos
 * 
 * O componente "double* vetPontos" está organizado de forma que:
 * X0 e Y0 estão nos indices 0 e 1 do vetor
 * X1 e Y1 estão nos indices 2 e 3 do vetor
 * X2 e Y2 estão nos indices 4 e 5 do vetor
 * (...)
 * Xi e Yi estão nos indices 2*i e 2*i+1
 * 
****************************/
struct tabPontos {
    int N;
    double xe;
    double Px;
    double limiteSup;
    double limiteInf;
    double* vetPontos;
};

// Aloca a struct tabPontos e seus respectivos componentes e chama a função preencherEstruturas()
struct tabPontos* montarEstrutura(char *argv[]);

// Aloca dinâmicamente o vetor de ordem N
double* alocarVetor(int N);

// Preenche a "struct tabPontos" com valores passados pelo usuário
void preencherEstrutura(struct tabPontos* tabela, int N, char *argv[]);

// Imprime o sistema
void imprimir(struct tabPontos* tabela);

// Calcula o tempo médio de cálculo da solução
double timestamp();

// Verifica se "xe" pertence o intervalo da tabela de pontos,
// em caso negativo exibe mensagem de erro em strderr
void verificarIntervalo(struct tabPontos* tabela);

// Desaloca a "struct tabPontos"
void destruirEstrutura(struct tabPontos* tabela);

#endif