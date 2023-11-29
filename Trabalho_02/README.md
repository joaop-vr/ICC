# Trabalho 02 - Otimização do Ajuste Polinomial de Curvas com Cálculo Intervalar

## Índice

- [Autores]
- [Descrição]
- [O_Programa]
- [Limitações]

## Autor

Joao Pedro Vicente Ramalho - 20224169
Mateus Kater Pombeiro - 20190366

## Descrição

O trabalho 2 consiste em implementar modificações ao trabalho 1, a fim de otimizar sua execução. Foram aplicadas alterações como Loop Unrolling, otimização de acesso à cache, redução de operações aritmética, redução de chamada de funções, etc.

## O Programa

O programa foi separado em 2 pastas, "v1" e "v2". A pasta v1 contém o Trabalho 1 (não otimizado), e a pasta v2 contém a versão otimizada do Trabalho 1, com modificações. Ambas as pastas contêm seu próprio Makefile, adaptado para cada versão.

Para executar o programa, foi feito um arquivo script "run.sh". Este script entra em cada uma das pastas (v1 e v2), compila o programa gera_entrada (fornecido pelos professores), compila os arquivos necessários, executa testes com múltiplas quantidades de pontos e exporta os dados coletados para a pasta "dados", sendo necessário apenas a execução do script, para a execução integral do trabalho.

A pasta "dados" conterá todos os dados necessários para geração dos gráficos, após a execução de ambos os programas. Os dados foram organizados em formato {metrica}_{versao}.dat, em que "metrica" é a métrica utilizada, como "tempo", "cache", ou "flops", por exemplo, e "versao" é a versão do programa, podendo ser "v1" ou "v2".

O script "gera_graficos.gp" deve ser executado para gerar os 10 gráficos necessários. O script utiliza os arquivos de dados localizados dentro da pasta "dados", e salva todos os gráficos como imagem, em formato png. 

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

Durante os testes não foram detectadas limitações do programa. Tais testes correspondem ao arquivo teste.in disponibilizado pelo professor.
