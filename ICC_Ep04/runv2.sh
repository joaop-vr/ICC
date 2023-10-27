# echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# likwid-perfctr -C ${CPU} -g ${k} -m ./teste >${k}_SemOtimiz.log

make purge
make

> time.dat
> mem.dat
> cache.dat
> energy.dat
> flops.dat
for n in 64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000 
do
    echo -n "$n " >> time.dat
    echo "Executando $n e pegando tempo..."
    # echo "rodando matriz $n para funcao $function"
    ./matmult $n
    echo >> time.dat

    # echo -n "$n " >> mem.dat
    # echo "Executando $n e pegando memoria..."
    # likwid-perfctr -O -C 3 -g MEM -m ./matmult $n | grep "Memory bandwidth" | cut -d',' -f2 | tr "\n" " " >> mem.dat # nao funciona (???)
    # echo >> mem.dat

    echo -n "$n " >> cache.dat
    echo "Executando $n e pegando cache..."
    likwid-perfctr -O -C 3 -g CACHE -m ./matmult $n | grep "miss ratio" | cut -d',' -f2 | tr "\n" " " >> cache.dat
    echo >> cache.dat

    echo -n "$n " >> energy.dat
    echo "Executando $n e pegando energia..."
    likwid-perfctr -O -C 3 -g ENERGY -m ./matmult $n | grep -e "Energy Core" -e "Energy \[J\]" | cut -d',' -f2 | tr "\n" " " >> energy.dat
    echo >> energy.dat

    echo -n "$n " >> flops.dat
    echo "Executando $n e pegando flops..."
    likwid-perfctr -O -C 3 -g FLOPS_DP -m ./matmult $n | grep "DP " | cut -d',' -f2 | tr "\n" " " >> flops.dat
    echo >> flops.dat
done

./test.gp
# echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
