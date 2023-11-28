echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

cd v1
make purge
make
gcc ../gera_entrada.c -o gera_entrada
# ./ajustePol_v1 < ../testes/pontosSlide.in
./gera_entrada 100000 | ./ajustePol_v1 

cd ../v2
make purge
make
gcc ../gera_entrada.c -o gera_entrada
# ./ajustePol_v2 < ../testes/pontosSlide.in
./gera_entrada 100000 | ./ajustePol_v2
