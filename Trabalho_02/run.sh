echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

mkdir -p dados
cd dados
# likwid-perfctr -C ${CPU} -g ${k} -m ./teste >${k}_SemOtimiz.log
> time_v1.dat
> mem_v1.dat
> cache_v1.dat
> flops_v1.dat
> time_v2.dat
> mem_v2.dat
> cache_v2.dat
> flops_v2.dat
cd ..
cd v1
make purge
make
gcc ../gera_entrada.c -o gera_entrada

# for n in 64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000
for n in 64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000
do
    echo -n "$n " >> ../dados/time_v1.dat
    echo "Executando ajustePol_v1 com $n e pegando tempo..."
    ./gera_entrada $n | ./ajustePol_v1 >> ../dados/time_v1.dat
    # echo >> time_v1.dat

    echo -n "$n " >> ../dados/mem_v1.dat
    echo "Executando ajustePol_v1 com $n e pegando memoria..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g L3 -m ./ajustePol_v1 | grep "L3 bandwidth" | cut -d',' -f2 | tr "\n" " " >> ../dados/mem_v1.dat 
    echo >> ../dados/mem_v1.dat

    echo -n "$n " >> ../dados/cache_v1.dat
    echo "Executando ajustePol_v1 com $n e pegando cache..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g L2CACHE -m ./ajustePol_v1 | grep "miss ratio" | cut -d',' -f2 | tr "\n" " " >> ../dados/cache_v1.dat
    echo >> ../dados/cache_v1.dat

    echo -n "$n " >> ../dados/flops_v1.dat
    echo "Executando ajustePol_v1 com $n e pegando flops..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g FLOPS_DP -m ./ajustePol_v1 | grep "DP " | cut -d',' -f2 | tr "\n" " " >> ../dados/flops_v1.dat
    echo >> ../dados/flops_v1.dat
done

cd ../v2
make purge
make
gcc ../gera_entrada.c -o gera_entrada

for n in 64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000
# for n in 64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000
do
    echo -n "$n " >> ../dados/time_v2.dat
    echo "Executando ajustePol_v2 com $n e pegando tempo..."
    # echo "rodando matriz $n para funcao $function"
    ./gera_entrada $n | ./ajustePol_v2 >> ../dados/time_v2.dat
    # echo >> ../dados/time_v2.dat

    echo -n "$n " >> ../dados/mem_v2.dat
    echo "Executando ajustePol_v2 com $n e pegando memoria..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g L3 -m ./ajustePol_v2 | grep "L3 bandwidth" | cut -d',' -f2 | tr "\n" " " >> ../dados/mem_v2.dat 
    echo >> ../dados/mem_v2.dat

    echo -n "$n " >> ../dados/cache_v2.dat
    echo "Executando ajustePol_v2 com $n e pegando cache..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g L2CACHE -m ./ajustePol_v2 | grep "miss ratio" | cut -d',' -f2 | tr "\n" " " >> ../dados/cache_v2.dat
    echo >> ../dados/cache_v2.dat

    echo -n "$n " >> ../dados/flops_v2.dat
    echo "Executando ajustePol_v2 com $n e pegando flops..."
    ./gera_entrada $n | likwid-perfctr -O -C 3 -g FLOPS_DP -m ./ajustePol_v2 | grep "DP " | cut -d',' -f2 | tr "\n" " " >> ../dados/flops_v2.dat
    echo >> ../dados/flops_v2.dat
done

cd ..
#./gera_graficos.gp
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
