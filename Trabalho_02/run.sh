echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# likwid-perfctr -C ${CPU} -g ${k} -m ./teste >${k}_SemOtimiz.log
> time_v1.dat
> mem_v1.dat
> cache_v1.dat
> flops_v1.dat
> time_v2.dat
> mem_v2.dat
> cache_v2.dat
> flops_v2.dat

cd v1
make purge
make
gcc ../gera_entrada.c -o gera_entrada
for n in 64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000
do
    echo -n "$n " >> ../time.dat
    echo "Executando ajustePol_v1 com $n e pegando tempo..."
    # echo "rodando matriz $n para funcao $function"
    ./matmult $n >> time.dat
    echo >> time.dat

    echo -n "$n " >> ../mem.dat
    echo "Executando ajustePol_v1 com $n e pegando memoria..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g L3 -m ./ajustePol_v1 $n | grep "L3 bandwidth" | cut -d',' -f2 | tr "\n" " " >> ../mem.dat 
    echo >> ../mem.dat

    echo -n "$n " >> ../cache.dat
    echo "Executando ajustePol_v1 com $n e pegando cache..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g L2CACHE -m ./ajustePol_v1 $n | grep "miss ratio" | cut -d',' -f2 | tr "\n" " " >> ../cache.dat
    echo >> ../cache.dat

    echo -n "$n " >> ../flops.dat
    echo "Executando ajustePol_v1 com $n e pegando flops..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g FLOPS_DP -m ./ajustePol_v1 $n | grep "DP " | cut -d',' -f2 | tr "\n" " " >> ../flops.dat
    echo >> ../flops.dat
done
cd ../v2
make purge
make
gcc ../gera_entrada.c -o gera_entrada

for n in 64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000
do
    echo -n "$n " >> ../time.dat
    echo "Executando ajustePol_v2 com $n e pegando tempo..."
    # echo "rodando matriz $n para funcao $function"
    ./matmult $n >> ../time.dat
    echo >> ../time.dat

    echo -n "$n " >> ../mem.dat
    echo "Executando ajustePol_v2 com $n e pegando memoria..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g L3 -m ./ajustePol_v2 $n | grep "L3 bandwidth" | cut -d',' -f2 | tr "\n" " " >> ../mem.dat 
    echo >> ../mem.dat

    echo -n "$n " >> ../cache.dat
    echo "Executando ajustePol_v2 com $n e pegando cache..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g L2CACHE -m ./ajustePol_v2 $n | grep "miss ratio" | cut -d',' -f2 | tr "\n" " " >> ../cache.dat
    echo >> ../cache.dat

    echo -n "$n " >> ../flops.dat
    echo "Executando ajustePol_v2 com $n e pegando flops..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g FLOPS_DP -m ./ajustePol_v2 $n | grep "DP " | cut -d',' -f2 | tr "\n" " " >> ../flops.dat
    echo >> ../flops.dat
done

./gera_graficos.gp
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
