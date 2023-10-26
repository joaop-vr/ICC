#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>
#include <getopt.h>    /* getopt */
#include <time.h>
#include <likwid.h>
#include "matriz.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
  exit(1);
}

double timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (double) tp.tv_sec*1.0e3 + (double) tp.tv_nsec*1.0e-6 );
}

/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main (int argc, char *argv[]) 
{

  LIKWID_MARKER_INIT;

  int n=DEF_SIZE;
  double start, end;
  MatRow mRow_1, mRow_2, resMat;
  Vetor vet, res;
  
  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  if (argc < 2)
    usage(argv[0]);

  n = atoi(argv[1]);
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  srandom(20232);
      
  res = geraVetor (n, 0); // (real_t *) malloc (n*sizeof(real_t));
  resMat = geraMatRow(n, n, 1);
    
  mRow_1 = geraMatRow (n, n, 0);
  mRow_2 = geraMatRow (n, n, 0);

  vet = geraVetor (n, 0);

  if (!res || !resMat || !mRow_1 || !mRow_2 || !vet) {
    fprintf(stderr, "Falha em alocação de memória !!\n");
    liberaVetor ((void*) mRow_1);
    liberaVetor ((void*) mRow_2);
    liberaVetor ((void*) resMat);
    liberaVetor ((void*) vet);
    liberaVetor ((void*) res);
    exit(2);
  }
    
#ifdef _DEBUG_
    prnMat (mRow_1, n, n);
    prnMat (mRow_2, n, n);
    prnVetor (vet, n);
    printf ("=================================\n\n");
#endif /* _DEBUG_ */
  LIKWID_MARKER_START("matVet");
  FILE* matvet = fopen("matVet_time.dat","a");
  start = timestamp();
  multMatVet (mRow_1, vet, n, n, res);
  end = timestamp();
  fprintf(matvet,"%d %lf\n", n, end-start);
  fclose(matvet);
  LIKWID_MARKER_STOP("matVet");

  LIKWID_MARKER_START("matVetOpt");
  FILE* matvetopt = fopen("matVetOpt_time.dat","a");
  start = timestamp();
  multMatVet_opt (mRow_1, vet, n, n, res);
  end = timestamp();
  fprintf(matvetopt,"%d %lf\n", n, end-start);
  fclose(matvetopt);
  LIKWID_MARKER_STOP("matVetOpt");

  LIKWID_MARKER_START("matMat");
  FILE* matmat = fopen("matMat_time.dat","a");
  start = timestamp();
  multMatMat (mRow_1, mRow_2, n, resMat);
  end = timestamp();
  fprintf(matmat,"%d %lf\n", n, end-start);
  fclose(matmat);
  LIKWID_MARKER_STOP("matMat");
  
  LIKWID_MARKER_START("matMatOpt");
  FILE* matmatopt = fopen("matMatOpt_time.dat","a");
  start = timestamp();
  multMatMat (mRow_1, mRow_2, n, resMat);
  end = timestamp();
  fprintf(matmatopt,"%d %lf\n", n, end-start);
  fclose(matmatopt);
  LIKWID_MARKER_STOP("matMatOpt");

#ifdef _DEBUG_
    prnVetor (res, n);
    prnMat (resMat, n, n);
#endif /* _DEBUG_ */

  liberaVetor ((void*) mRow_1);
  liberaVetor ((void*) mRow_2);
  liberaVetor ((void*) resMat);
  liberaVetor ((void*) vet);
  liberaVetor ((void*) res);
  
  LIKWID_MARKER_CLOSE;
  return 0;
}

