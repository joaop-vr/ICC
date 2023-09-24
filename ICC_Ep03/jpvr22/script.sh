#!/bin/bash

METRICA="FLOPS_DP"
CPU="3"

parametrosCompilacao="-lm -O3 -mavx -march=native -I${LIKWID_HOME}/include -DLIKWID_PERFMON -L${LIKWID_HOME}/lib -llikwid"
nomePrograma="interpola"

make purge
gcc -o ${nomePrograma} codigos/main.c codigos/auxiliares.c codigos/auxiliares.h codigos/metodosInterpol.c codigos/metodosInterpol.h ${parametrosCompilacao}

# Verifica se pelo menos um argumento foi passado
if [ $# -lt 1 ]; then
  echo "Uso: $0 <argumento_para_interpola>"
  exit 1
fi

# Listar todos os argumentos passados pelo usuário
echo "Argumentos passados:"
for arg in "$@"; do
  echo "$arg"
done

# Obtém o ponto Xe passado pelo usuário
Pxe="$1"

# Verifica se o segundo argumento (arquivo de entrada) foi passado
if [ -n "$2" ]; then
  pontos="$2"
else
  pontos="/dev/stdin"  # Usar entrada padrão se nenhum arquivo for especificado
fi

# Verifica se o terceiro argumento (arquivo de saída) foi passado
if [ -n "$3" ]; then
  saida="$3"
else
  saida="/dev/stdout"  # Usar saída padrão se nenhum arquivo for especificado
fi

make # só pra garantir que tenha o executável

for k in $METRICA
do

    # Redireciona a saída do programa para aux1.log
    likwid-perfctr -C ${CPU} -g ${k} -m ./interpola ${Pxe} < ${pontos} > aux1.log  
    
    # Remove o cabeçalho de aux1.log e retireciona a saida para aux2.log
    tail -n +6 aux1.log  > aux2.log 
    
    # Passa o conteúdo do aux2.log para o outputFiltrado.log sem
    # últimas 67 linhas do arquivo outputFiltrado.log
    # que correspondem as tabelas geradas pelo likwid-perfctr
    head -n -67 aux2.log  > outputFiltrado.log


    # Imprime MFLOPs para cada método de eliminação
    echo "" >> outputFiltrado.log
    echo "A quantidade de MFLOP/s para os métodos 1 e 2 - respectivamente:" >> outputFiltrado.log
    grep -F "|     DP [MFLOP/s]     |" aux2.log >> outputFiltrado.log

    if [ -n "${saida}" ]; then
        cp outputFiltrado.log "${saida}"
    else
        cat outputFiltrado.log
    fi

done

# Apaga os arquivos auxiliares
rm -f aux1.log aux2.log outputFiltrado.log