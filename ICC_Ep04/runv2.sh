# echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# likwid-perfctr -C ${CPU} -g ${k} -m ./teste >${k}_SemOtimiz.log
for function in matVet matMat
do
    > ${function}_time.dat
    for n in 64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000 
    do
        echo "$n " >> ${function}_time.dat
	echo "rodando matriz $n para funcao $function"
        ./matmult $n
        echo $"\n" >> ${function}_time.dat
    done

    > ${function}_mem.dat
    for n in 64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000 
    do
        echo "$n " >> ${function}_mem.dat
        likwid-perfctr -C 3 -g MEM ./matmult $n # nao funciona (???)
        echo $"\n" >> ${function}_mem.dat
    done

    > ${function}_cache.dat
    for n in 64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000 
    do
        echo "$n " >> ${function}_cache.dat
        likwid-perfctr -C 3 -g CACHE ./matmult $n | grep "miss ratio" | cut -d' ' -f9 | tr "\n" " " >> ${function}_cache.dat
        echo $"\n" >> ${function}_cache.dat
    done

    > ${function}_energy.dat
    for n in 64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000 
    do
        echo "$n " >> ${function}_energy.dat
        likwid-perfctr -C 3 -g ENERGY ./matmult $n | grep "Energy Core" | cut -d' ' -f16 | tr "\n" " " >> ${function}_energy.dat
        echo $"\n" >> ${function}_energy.dat
    done

    > ${function}_flops.dat
    for n in 64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000 
    do
        echo "$n " >> ${function}_flops.dat
        likwid-perfctr -C 3 -g ENERGY ./matmult $n
        echo $"\n" >> ${function}_flops.dat
    done
    # echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
done
