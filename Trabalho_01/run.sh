likwid-perfctr -C 3 -g ENERGY -m ./ajustePol < $1 > aux # | grep "Energy \[J\]"
cat aux | tail -n -33 | grep "Energy \[J\]" # | grep "MFLOP/s"
rm -f aux
likwid-perfctr -C 3 -g FLOPS_DP -m ./ajustePol < $1 > aux
cat aux | tail -n -33 | grep "MFLOP/s"
cat aux | head -n 9 | tail -n 4
rm -f aux
