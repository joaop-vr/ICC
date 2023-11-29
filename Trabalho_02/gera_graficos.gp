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

set xlabel "N matriz"
set logscale y
set logscale x
set datafile separator whitespace

set ylabel "ms"
set output "time.png"
set title  "Tempo (gerar sistema)"
set terminal qt 1 title "Tempo (gerar sistema)"
plot 'time_v1.dat' using 1:2 title "v1" with linespoints, \
     'time_v2.dat' using 1:2 title "v2" with linespoints

pause -1

set ylabel "ms"
set output "time.png"
set title  "Tempo (solucao)"
set terminal qt 1 title "Tempo (solucao)"
plot 'time_v1.dat' using 1:3 title "v1" with linespoints, \
     'time_v2.dat' using 1:3 title "v2" with linespoints

pause -1

set ylabel "ms"
set output "time.png"
set title  "Tempo (resíduos)"
set terminal qt 1 title "Tempo (resíduos)"
plot 'time_v1.dat' using 1:4 title "v1" with linespoints, \
     'time_v2.dat' using 1:4 title "v2" with linespoints

pause -1

set ylabel "MFLOP/s"
set output "FLOPS_DP.png"
set title "FLOPS (gerar)"
set terminal qt 1 title "FLOPS (gerar)"
plot 'flops_v1.dat' using 1:2 title "v1" with linespoints, \
     'flops_v2.dat' using 1:2 title "v2" with linespoints

pause -1

set ylabel "MFLOP/s"
set output "FLOPS_DP.png"
set title "FLOPS (solucao)"
set terminal qt 1 title "FLOPS (solucao)"
plot 'flops_v1.dat' using 1:3 title "v1" with linespoints, \
     'flops_v2.dat' using 1:3 title "v2" with linespoints

pause -1

set ylabel "MFLOP/s"
set output "FLOPS_DP.png"
set title "FLOPS (resíduos)"
set terminal qt 1 title "FLOPS (resíduos)"
plot 'flops_v1.dat' using 1:4 title "v1" with linespoints, \
     'flops_v2.dat' using 1:4 title "v2" with linespoints

pause -1

set ylabel "%"
set output "cache.png"
set title  "Cache miss (gerar)"
set terminal qt 1 title "Cache miss (gerar)"
plot 'cache_v1.dat' using 1:2 title "v1" with linespoints, \
     'cache_v2.dat' using 1:2 title "v2" with linespoints

pause -1

set ylabel "%"
set output "cache.png"
set title  "Cache miss (resíduos)"
set terminal qt 1 title "Cache miss (resíduos)"
plot 'cache_v1.dat' using 1:4 title "v1" with linespoints, \
     'cache_v2.dat' using 1:4 title "v2" with linespoints

pause -1

set ylabel "MBytes/s"
set output "mem.png"
set title "Banda de memoria (gerar)"
set terminal qt 1 title "Banda de memoria (gerar)"
plot 'mem_v1.dat' using 1:2 title "v1" with linespoints, \
     'mem_v2.dat' using 1:2 title "v2" with linespoints

pause -1

set ylabel "MBytes/s"
set output "mem.png"
set title "Banda de memoria (resíduos)"
set terminal qt 1 title "Banda de memoria (resíduos)"
plot 'mem_v1.dat' using 1:4 title "v1" with linespoints, \
     'mem_v2.dat' using 1:4 title "v2" with linespoints

pause -1