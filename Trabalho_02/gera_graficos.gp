#!/usr/bin/gnuplot -c

## set encoding iso_8859_15
set encoding utf

# set terminal qt persist

set grid

set style data point
set style function line
set style line 1 lc 3 pt 7 ps 0.3
set boxwidth 1
set xtics
# set xrange [0:]
set key outside right
set xlabel  "N matriz"
set logscale y
unset logscale x
set datafile separator whitespace

set ylabel "ms"
set output "time.png"
set title  "Tempo de execucao"
set terminal qt 1 title "Tempo de execucao"
plot 'time_v1.dat' using 1:2 title "v1" with linespoints, \
     'time_v2' using 1:2 title "v2" with linespoints

pause -1

set ylabel "%"
set output "cache.png"
set title  "Cache miss L2"
set terminal qt 1 title "Cache miss L2"
plot 'cache_v1.dat' using 1:2 title "v1" with linespoints, \
     'cache_v2.dat' using 1:2 title "v2" with linespoints

pause -1

set title "Banda de memoria"
set ylabel "MBytes/s"
set output "mem.png"
set terminal qt 1 title "Banda de memoria"
plot 'mem_v1.dat' using 1:2 title "v1" with linespoints, \
     'mem_v2.dat' using 1:2 title "v2" with linespoints

pause -1

set ylabel "MFLOP/s"
set output "FLOPS_DP.png"
set title "FLOPS"
set terminal qt 1 title "FLOPS"
plot 'flops.dat' using 1:2 title "matVet FLOPS_DP" with linespoints, \
     '' using 1:4 title "matVetOpt FLOPS_DP" with linespoints, \
     '' using 1:6 title "matMat FLOPS_DP" with linespoints, \
     '' using 1:8 title "matMatOpt FLOPS_DP" with linespoints, \

pause -1