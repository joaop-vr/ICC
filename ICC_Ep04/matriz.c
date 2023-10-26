#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // Para uso de função 'memset()'

#include "matriz.h"

/**
 * Função que gera valores para para ser usado em uma matriz
 * @param i,j coordenadas do elemento a ser calculado (0<=i,j<n)
*  @return valor gerado para a posição i,j
  */
static inline real_t generateRandomA( unsigned int i, unsigned int j)
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return ( (i==j) ? (real_t)(BASE<<1) : 1.0 )  * (real_t)random() * invRandMax;
}

/**
 * Função que gera valores aleatórios para ser usado em um vetor
 * @return valor gerado
 *
 */
static inline real_t generateRandomB( )
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return (real_t)(BASE<<2) * (real_t)random() * invRandMax;
}



/* ----------- FUNÇÕES ---------------- */

/**
 *  Funcao geraMatRow: gera matriz como vetor único, 'row-oriented'
 * 
 *  @param m     número de linhas da matriz
 *  @param n     número de colunas da matriz
 *  @param zerar se 0, matriz  tem valores aleatórios, caso contrário,
 *               matriz tem valores todos nulos
 *  @return  ponteiro para a matriz gerada
 *
 */

MatRow geraMatRow (int m, int n, int zerar)
{
  MatRow matriz = (real_t *) malloc(m*n*sizeof(real_t));

  if (matriz) {
    if (zerar)
      memset(matriz,0,m*n*sizeof(real_t));
    else
      for (int i=0; i < m; ++i)
	      for (int j=0; j < n; ++j)
	        matriz[i*n + j] = generateRandomA(i, j);
  }
  
  return (matriz);
}


/**
 *  Funcao geraVetor: gera vetor de tamanho 'n'
 * 
 *  @param n  número de elementos do vetor
 *  @param zerar se 0, vetor  tem valores aleatórios, caso contrário,
 *               vetor tem valores todos nulos
 *  @return  ponteiro para vetor gerado
 *
 */

Vetor geraVetor (int n, int zerar)
{
  Vetor vetor = (real_t *) malloc(n*sizeof(real_t));

  if (vetor) {
    if (zerar)
      memset(vetor,0,n*sizeof(real_t));
    else
      for (int i=0; i < n; ++i)
	      vetor[i] = generateRandomB();
  }
  
  return (vetor);
}

/**
 *  \brief: libera vetor
 * 
 *  @param  ponteiro para vetor
 *
 */
void liberaVetor (void *vet)
{
	free(vet);
}


/**
 *  Funcao multMatVet:  Efetua multiplicacao entre matriz 'mxn' por vetor
 *                       de 'n' elementos
 *  @param mat matriz 'mxn'
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *  @param res vetor que guarda o resultado. Deve estar previamente alocado e com
 *             seus elementos inicializados em 0.0 (zero)
 *  @return vetor de 'm' elementos
 *
 */

void multMatVet (MatRow restrict mat, Vetor restrict v, int m, int n, Vetor restrict res)
{
    
  /* Efetua a multiplicação */
  if (res) {
    for (int i=0; i < m; ++i)
      for (int j=0; j < n; ++j)
        res[i] += mat[n*i + j] * v[j];
  }
	#ifdef _DEBUG_
  printf ("======== versao do prof =========\n\n");
  prnMat (mat, n, n);
  prnVetor (v, n);
  printf ("=================================\n\n");
	#endif

  for (int i = 0; i < m; i ++) 
    res[i] = 0;
  
}

void multMatVet_opt(MatRow restrict mat, Vetor restrict v, int m, int n, Vetor restrict res){
  /******** Versão otimizada ****************/
  for (int i=0; i < n-n%UF; i+=UF) {
    for (int j=0; j<n; ++j){
      res[i] += mat[n*i + j] * v[j];
      res[i+1] += mat[n*(i+1) + j] * v[j];
      res[i+2] += mat[n*(i+2) + j] * v[j];
      res[i+3] += mat[n*(i+3) + j] * v[j];
    }
  }
  // resíduo do laço
  int NI;
  for (int i=n-n%UF; i < n; ++i) {
    NI = n*i;
    for (int j=0; j < n; ++j)
      res[i] += mat[NI + j] * v[j];
  }
  
	#ifdef _DEBUG_
  printf ("======== nossa versao  =========\n\n");
  prnMat (mat, n, n);
  prnVetor (v, n);
  printf ("=================================\n\n");
	#endif
}
/**
 *  Funcao multMatMat: Efetua multiplicacao de duas matrizes 'n x n' 
 *  @param A matriz 'n x n'
 *  @param B matriz 'n x n'
 *  @param n ordem da matriz quadrada
 *  @param C   matriz que guarda o resultado. Deve ser previamente gerada com 'geraMatPtr()'
 *             e com seus elementos inicializados em 0.0 (zero)
 *
 */

void multMatMat (MatRow restrict A, MatRow restrict B, int n, MatRow restrict C)
{

  /* Efetua a multiplicação */
  for (int i=0; i < n; ++i)
    for (int j=0; j < n; ++j)
      for (int k=0; k < n; ++k)
	      C[i*n+j] += A[i*n+k] * B[k*n+j];
	#ifdef _DEBUG_
  printf ("======== versao do prof =========\n\n");
  prnMat (A, n, n);
  prnMat (B, n, n);
  prnMat (C,n,n);
	#endif
  for (int i=0; i < n; ++i)
    for (int j=0; j < n; ++j)
      for (int k=0; k < n; ++k)
	      C[i*n+j] = 0;

	#ifdef _DEBUG_
  /*printf ("======== resposta zerada ========\n\n");
  prnMat (A, n, n);
  prnMat (B, n, n);
  prnMat (C,n,n);
  printf ("=================================\n\n");*/
	#endif

}

void multMatMat_opt(MatRow restrict A, MatRow restrict B, int n, MatRow restrict C){
  /******** Versão otimizada ****************/
  int iStart, iEnd, jStart, jEnd, kStart, kEnd, NI, NK;
  for (int ii=0; ii<n/BK; ++ii) {
    iStart=ii*BK; iEnd=iStart+BK;
    for (int jj=0; jj<n/BK; ++jj) {
      jStart=jj*BK; jEnd=jStart+BK;
      for (int kk=0; kk<n/BK; ++kk) {
        kStart=kk*BK; kEnd=kStart+BK;
        for (int i=iStart; i<iEnd; ++i) {
          NI = n*i;
          for (int j=jStart; j<jEnd; j+=UF) {
            C[NI + j] = 0.0;
            C[NI + j+1] = 0.0;
            C[NI + j+2] = 0.0;
            C[NI + j+3]= 0.0;
            for (int k=kStart; k<kEnd; ++k) {
              NK = n*k;
              C[NI + j] += A[NI + k]*B[NK+ j];
              C[NI + j+1] += A[NI + k]*B[NK+ j+1];
              C[NI + j+2] += A[NI + k]*B[NK+ j+2];
              C[NI + j+3] += A[NI + k]*B[NK+ j+3];
            }
            
            for (int j=n-n%BK; j < n; ++j)
              for (int k=0; k < n; ++k)
                C[NI + j] += A[NI + k]*B[NK + j];
          }
        }
      }
    }
  }
	#ifdef _DEBUG_
  printf ("======== nossa versao  =========\n\n");
  prnMat (A, n, n);
  prnMat (B, n, n);
  prnMat (C,n,n);
  printf ("=================================\n\n");
	#endif
}

/**
 *  Funcao prnMat:  Imprime o conteudo de uma matriz em stdout
 *  @param mat matriz
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *
 */

void prnMat (MatRow mat, int m, int n)
{
  for (int i=0; i < m; ++i) {
    for (int j=0; j < n; ++j)
      printf(DBL_FIELD, mat[n*i + j]);
    printf("\n");
  }
  printf(SEP_RES);
}

/**
 *  Funcao prnVetor:  Imprime o conteudo de vetor em stdout
 *  @param vet vetor com 'n' elementos
 *  @param n número de elementos do vetor
 *
 */

void prnVetor (Vetor vet, int n)
{
  for (int i=0; i < n; ++i)
    printf(DBL_FIELD, vet[i]);
  printf(SEP_RES);
}

