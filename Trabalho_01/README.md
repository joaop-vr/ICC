# Trabalho 01 - Ajuste Polinomial de Curvas com Cálculo Intervalar

O objetivo deste trabalho é implementar um programa para calcular um polinômio de grau N que se ajuste a uma curva descrita por K pontos, utilizando aritmética intervalar para representação rigorosa dos valores reais.

## Índice

- [Autores]
- [Descrição]
- [O_Programa]
- [Limitações]

## Autor

Joao Pedro Vicente Ramalho - 20224169
Mateus Kater Pombeiro - 20190366

## Descrição

O trabalho consiste em calcular um ajuste de curva polinomial f(x) de grau N a partir de uma tabela de K pontos (x,y).

Devem ser calculados os coeficientes ai do polinômio f(x) = a0 + a1.x + a2.x2 + (…) + aN.xN utilizando-se do Método dos Mínimos Quadrados. O método da Eliminação de Gauss com pivoteamento parcial deve ser usado para resolver os sistemas lineares provenientes do método.
Para manter a representação rigorosa, todos os valores reais no programa devem ser representados por intervalos.
O programa recebe como entrada a quantidade N de pontos da tabela (1ª linha) e a tabela com os pontos (x,f(x)) do tipo double, um par de coordenadas por linha.

## O Programa

Compartimentado em 5 bibliotecas (estruturas.h, operaEstrutura.h, minimosQuadrados.h, calculoIntervalar.h, auxiliares.h), o processo se inicia na função main (main.c).

# Estruturas

    <estruturas.h>

    Todas as estruturas de dados estão declaradas e comentadas nesse arquivo. São elas:

        - union;
        - operandos;
        - ajustePol;

# OperaEstrutura

    <operaEstrutura.c>
    <operaEstrutura.h>

    Possuem a implementação de todas as funções cujo objetivo é manusear as estruturas de dados. Dentre elas:

        - montarEstrutura(): aloca a estrutura;
        - preencherEstrutura(): preenche a estrutura com os pontos;
        - imprimir(): imprime na tela os metadados da estrutura;
        - destruirEstrutura(): libera a memória da estrutura;

# MinimosQuadrados

    <minimosQuadrados.c>
    <minimosQuadrados.h>

    Apresentam a implementação de todas as principais funções envolvidas no ajuste de curvas pelo método dos mínimos quadrados - inclusive as funções referentes à eliminação de gauss com pivoteamento parcial.

    Além disso, possui a implementação da função polinomio(), que retorna o valor de f(X0), sendo X0 um dos valores que recebe como parâmetro.

# CalculoIntervalar

    <calculoIntervalar.c>
    <calculoIntervalar.h>

    Possuem a implementação das funções relacionadas ao cálculo intervalar e às operações intervalares. Vale apontar que todas essas funções retornam uma "struct operandos", que contém um valor double e seus limites inferior e supeiore.


# Auxiliares

    <auxiliares.c>
    <auxiliares.h>

    Constam com algumas funções complementares ao código, que estão devidamente comentadas no arquivo auxiliares.h.


## Limitações

Durante os testes não foram detectadas limitações do programa. Tais testes estão presentes na pasta "testes".
