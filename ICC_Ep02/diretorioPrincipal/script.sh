#!/bin/bash

METRICA="FLOPS_DP"
CPU="3"

LIKWID_HOME=/usr/local
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

for k in $METRICA
do

    # Redireciona a saída do programa para aux.log
    likwid-perfctr -C ${CPU} -g ${k} -m ./perfEG > outputCompleto.log

    # Passa o conteúdo do outputCompleto.log para o aux.log sem
    # últimas 100 linhas do arquivo aux.log
    # que correspondem as tabelas geradas pelo likwid-perfctr
    head -n -100 outputCompleto.log > outputFiltrado.log

    # Imprime MFLOPs para cada método de eliminação
    echo "" >> outputFiltrado.log
    echo "####################" >> outputFiltrado.log
    echo "" >> outputFiltrado.log
    echo "A quantidade de MFLOP/s para os métodos 1, 2 e 3 - respectivamente:" >> outputFiltrado.log
    echo "" >> outputFiltrado.log

    grep -F "|     DP [MFLOP/s]     |" outputCompleto.log >> outputFiltrado.log

done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# Imprime no terminal a saída filtrada
cat outputFiltrado.log

# Apaga os arquivos auxiliares
rm -f *.log