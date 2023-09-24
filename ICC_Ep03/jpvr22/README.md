# EP-03 - Interpolação

Este exercício tem como objetivo implementar métodod de Interpolação (Lagrange e Newton) e comparar performance em tempo e FLOPS.

## Índice

- [Autor]
- [Descrição]
- [O_Programa]
- [Limitações]

## Autor

Joao Pedro Vicente Ramalho - 20224169

## Descrição

Fazer um programa interpola que lê pela entrada padrão uma tabela de N pontos (x, f(x))
e gera um polinômio de grau K=N-1 que possa ser usado para calcular o valor aproximado de f(x)
para um valor xe (fornecida como argumento do programa) qualquer não pertencente à tabela de pontos fornecida.

O programa recebe como entrada a quantidade N de pontos da tabela (1ª linha) e a tabela com os pontos (x,f(x)) do tipo double, um par de coordenadas por linha.

## O Programa

Compartimentado em 2 bibliotecas (auxiliares.h, metodosInterpol.h), o processo se inicia na função main (main.c).

# Auxiliares

    <auxiliares.h>
    <auxiliares.c>

    A estrutura de dados usada neste exercício está definida no arquivo auxiliares.h:
      - "struct tabPontos": sua função é definir os componentes do problema:
         N = número de conjunto de pontos;
         xe = valor de "xe" passado pelo usuário;
         Px = valor de Pk(xe);
         limiteSup = limite superior do intervalo de pontos;
         limiteInf = limite inferior do intervalo de pontos;
         vetPontos = vetor com os pontos;

    As funções que manipulam "struct tabPontos" (ex.: "montarEstrutura()", "preencherEstrutura()", etc) e funções secundárias como "verificarIntervalo()" também estão definidas nesse arquivo e implementadas em auxiliares.c.

# Main

    <main.c>

    Neste arquivo, são chamadas as funções:
        - montarEstrutura(): aloca memória para a struct e a preenche com os valores passados pelo usuário;
        - interpolLagrange() e interpolNewton(): efetuam a Interpolação com os respectivos métodos;
        - destruirEstrutura(): libera a memória alocada ao longo do programa;

# metodosInterpol

    <metodosInterpol.c>

    Neste arquivo, são implementadas as funções:
        - interpolLagrange(): realiza o método de Interpolação de Lagrange;
        - interpolNewton(): realiza o método de Interpolação de Newton;
        - calcularDi(): calcula os valores de "Di"s referentes ao método de Newton;

## Limitações

Durante os testes não foram detectadas limitações do programa. Tais testes estão presentes na pasta "testes".
