echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

for n in (64, 100, 128,  200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000) do
    echo ${n}\t >> matvet
    echo ${n}\t >> matmat
    # likwid-perfctr -C 3 -g ENERGY -m ./matmult < ${n} > aux
    ./matmult < ${n} > aux
    cat aux | cut -f' ' -d 1 >> matvet
    cat aux | cut -f' ' -d 2 >> matmat
    echo \n >> matvet
    echo \n >> matmat
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor