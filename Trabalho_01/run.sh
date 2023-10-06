likwid-perfctr -C 3 -g FLOPS_DP -m ./ajustePol < $1 | grep "MFLOPS"
likwid-perfctr -C 3 -g ENERGY -m ./ajustePol < $1 | grep "Energy \[J\]"