# EP-02 - Sistemas Lineares

Este exercício tem como objetivo implementar 3 variações para o Método de Eliminação de Gauss e comparar performance em tempo e FLOPS.

## Índice

- [Autor]
- [Descrição]
- [O_Programa]
- [Limitações]

## Autores

Joao Pedro Vicente Ramalho - 20224169

## Descrição

Fazer um programa perfEG que lê pela entrada padrão 1 (um) sistema linear (SL) AX = B, de ordem N.
A solução do SL deve ser calculada usando 3 (três) variações do Método de Eliminação de Gauss:

    1)Forma clássica com pivoteamento;
    2)Forma clássica com pivoteamento, sem o cálculo dos multiplicadores;
    3)Forma alternativa onde não usa pivoteamento e que consiste em:

        -Para cada linha  do pivô, dividir todos os  coeficientes pelo pivô  (que fica com o valor 1)
        -Proceder com  a eliminação,  zerando a coluna  do pivô,  sem fazer pivoteamento.
        -Completada   a  triangularização,   calcular  as   incógnitas  por retro-substituição.

## O Programa

Compartimentado em 2 bibliotecas (auxiliares.h, elimGauss.h), o processo se inicia na função main (main.c).

# Auxiliares

    <auxiliares.h>
    <auxiliares.c>

    A estrutura de dados usada neste exercício está definida no arquivo auxiliares.h:
    "struct sistemaLinear": sua função é definir os componentes de um sistema (matiz de coefificentes, de incognitas e resultante). Além disso, foi adicionado um vetor ("double* residuos") para armazenar os resíduos do sistema e um backup do sistema ("struct sistemaLinear* backup") para que se pudesse reiniciá-lo e resolvê-lo novamente utilizando outros métodos.

    As funções que manipulam "struct sistemaLinear" e funções secundárias como "calcularResiduo()" e "imprimirSaida()" também estão definidas nesse arquivo e implementadas em auxiliares.c.

# Main

    <main.c>

    Neste arquivo, são chamadas as funções:
        - elimGaussClassico(), elimGaussSemMulti() e elimGaussAlternativa(): efetuam a Eliminação de Gauss;
        - imprimirSaida(): gera na saída padrão a solução do SL, o tempo médio de cálculo da solução e o resíduo;
        -reiniciarSistema(): reinicia o SL com os valores passados pelo usuário;

# ElimGauss

    <elimGauss.c>

    Neste arquivo, são implementadas as funções:
        - elimGaussClassico(): soluciona o SL através do método 1;
        - elimGaussSemMulti(): soluciona o SL através do método 2;
        - elimGaussAlternativa(): soluciona o SL através do método 3;

    As funções que são chamadas pelas citadas acima também foram implementadas nesse arquivo (ex.: max(), trocarLinha(), retroSubst(), etc...);

## Limitações

Durante os testes não foram detectadas limitações do programa. Tais testes estão presentes em testes.txt
