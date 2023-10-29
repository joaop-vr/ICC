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
set key outside right # posição da legenda: outside {left | right}
set xlabel  "N matriz"
unset logscale x
set datafile separator whitespace

set ylabel "%"
set output "cache.png"
set title  "Cache miss L2"
set terminal qt 1 title "Cache miss L2"
plot 'cache.dat' using 1:2 title "matVet" with linespoints, \
     '' using 1:3 title "matVetOpt" with linespoints, '' using 1:4 title "matMat" with linespoints, '' using 1:5 title "matMatOpt" with linespoints

pause -1

set title "Banda de memoria"
set ylabel "MBytes/s"
set output "mem.png"
plot 'mem.dat' using 1:2 title "matVet" with linespoints, \
     '' using 1:3 title "matVetOpt" with linespoints, '' using 1:4 title "matMat" with linespoints, '' using 1:5 title "matMatOpt" with linespoints

pause -1

set ylabel "MFLOP/s"
set output "FLOPS_DP.png"
set title "FLOPS_DP"
plot 'flops.dat' using 1:2 title "matVet" with linespoints, \
     '' using 1:3 title "matVetOpt" with linespoints, '' using 1:4 title "matMat" with linespoints, '' using 1:5 title "matMatOpt" with linespoints

pause -1

set ylabel "J"
set output "Energy.png"
set title "Energy"
plot 'energy.dat' using 1:2 title "matVet" with linespoints, \
     '' using 1:3 title "matVetOpt" with linespoints, '' using 1:4 title "matMat" with linespoints, '' using 1:5 title "matMatOpt" with linespoints

