# EP-04 - Otimização de Código Serial

O objetivo deste exercício é melhorar a performance de funções de multiplicação de matrizes e de vetores, para posteriormente analisar o desempenho referente a tempo, memória, cache, energia e FLOPS.

## Índice

- [Autores]
- [Descrição]
- [Otimizações]
- [Limitações]

## Autores

Joao Pedro Vicente Ramalho - 20224169
Mateus Kater Pombeiro - 20190366

## Descrição

## Documentação da arquitetura do processador utlizado:

CPU name: Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz
CPU type: Intel Coffeelake processor
CPU stepping: 9

---

Hardware Thread Topology

---

Sockets: 1
Cores per socket: 4
Threads per core: 1

---

HWThread Thread Core Socket Available
0 0 0 0 _
1 0 1 0 _
2 0 2 0 _
3 0 3 0 _

---

## Socket 0: ( 0 1 2 3 )

---

Cache Topology

---

Level: 1
Size: 32 kB
Type: Data cache
Associativity: 8
Number of sets: 64
Cache line size: 64
Cache type: Non Inclusive
Shared by threads: 1
Cache groups: ( 0 ) ( 1 ) ( 2 ) ( 3 )

---

Level: 2
Size: 256 kB
Type: Unified cache
Associativity: 4
Number of sets: 1024
Cache line size: 64
Cache type: Non Inclusive
Shared by threads: 1
Cache groups: ( 0 ) ( 1 ) ( 2 ) ( 3 )

---

Level: 3
Size: 6 MB
Type: Unified cache
Associativity: 12
Number of sets: 8192
Cache line size: 64
Cache type: Inclusive
Shared by threads: 4
Cache groups: ( 0 1 2 3 )

---

---

NUMA Topology

---

## NUMA domains: 1

Domain: 0
Processors: ( 0 1 2 3 )
Distances: 10
Free memory: 5254.64 MB
Total memory: 7826.25 MB

---

---

Graphical Topology

---

Socket 0:
+---------------------------------------------+
| +--------+ +--------+ +--------+ +--------+ |
| | 0 | | 1 | | 2 | | 3 | |
| +--------+ +--------+ +--------+ +--------+ |
| +--------+ +--------+ +--------+ +--------+ |
| | 32 kB | | 32 kB | | 32 kB | | 32 kB | |
| +--------+ +--------+ +--------+ +--------+ |
| +--------+ +--------+ +--------+ +--------+ |
| | 256 kB | | 256 kB | | 256 kB | | 256 kB | |
| +--------+ +--------+ +--------+ +--------+ |
| +-----------------------------------------+ |
| | 6 MB | |
| +-----------------------------------------+ |
+---------------------------------------------+

A tarefa consiste em melhorar a performance das operações abaixo, usando as técnicas vistas em aula, inclusive (mas não restritos a) unroll & jam + blocking e usando a ferramenta LIKWID para comparar as performances e tempos com e sem otimização:

multMatVet() --> multiplica uma matriz tipo MatRow por um vetor
multMatMat() --> multiplica duas matrizes de tipo MatRow

São definidos 2 tipos abstratos de dados (vide arquivo matriz.h):

MatRow: tipo para representar uma matriz implementada como um único vetor cujo conteúdo são as linhas da matriz, em sequencia;
Vetor: tipo para representar um vetor simples.

O fator de unroll UF e o fator de blocking BK estão definidos via macros em linguagem C no arquivo matriz.h .

## Otimizações

# Alocação de memória sequencial

As matrizes foram alocadas como um único vetor cujo conteúdo são as linhas da matriz, em sequencia. Dessa forma, ao invés de acessar o conteúdo das matrizes usando dois indices (ex.: A[i][j]),
acessou-se por meio do cáculo A[n*i + j], sendo "n" a ordem da matriz.

# Unroll & Jam

Foi aplicado nas funções multMatVet() e multMatMat(), de forma a atravessar os laços de repetições com stride de UF (fator de unroll, declarado em matriz.h)

# Subexpressões Comuns

Eliminamos as subexpressões recorrentes no código. Por exemplo, optamos por eliminar repetições do tipo

    C[n*i + j] += A[n*i + k] * B[n*k + j];
    C[n*i + j+1] += A[n*i + k] * B[n*k + j+1];
    C[n*i + j+2] += A[n*i + k] * B[n*k + j+2];
    C[n*i + j+3] += A[n*i + k] * B[n*k + j+3];

e declaramos as variáveis NI, NK e NI_K, que recebem n*i, n*k e NI+k respectivamente. Dessa forma, a ocorrência de multiplicações e somas desnecessárias diminuem, resultando em

    C[NI + j] += A[NI_K] * B[NK+ j];
    C[NI + j+1] += A[NI_K] * B[NK+ j+1];
    C[NI + j+2] += A[NI_K] * B[NK+ j+2];
    C[NI + j+3] += A[NI_K] * B[NK+ j+3];

# Alising

Declaramos as tags "restrict" nas funções multMatVet() e multMatMat()

void multMatMat (MatRow restrict A, MatRow restrict B, int n, MatRow restrict C)
void multMatVet (MatRow restrict mat, Vetor restrict v, int m, int n, Vetor restrict res)

pois assim explicitamos ao compilador que não há alias, ou seja, as estruturas de dados passadas como parâmetros não apontam para o mesmo objeto. Dessa forma, o compilador poderá
efetuar eventuais otimizações sem se preocupar com dependências de dados.

# Padding

Foi verificado se o valor de n (ordem das matrizes) é expoente de 2 por meio da função "ehPontenciaDe2()", em caso positivo alocamos "n+1", do contrário alocamos "n". Tal otimização foi realizada para minimizar o desperdício de espaço gerado pelo mal alinhamento dos campos das estruturas de dados na memória.

## Limitações

Durante os testes não foram detectadas limitações do programa.
