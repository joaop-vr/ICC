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
set xlabel  "N matriz"
set ylabel "metrics"

set key outside right # posição da legenda: outside {left | right}
unset logscale x
set datafile separator whitespace
set ylabel  "<metrica 1>"
set title   "<campo[marcador 1]>"
set terminal qt 1 title "<campo[marcador 1]>"
plot 'cache.dat' using 1:2 title "matVet" with linespoints, \
     '' using 1:3 title "matVetOpt" with linespoints, '' using 1:4 title "matMat" with linespoints, '' using 1:5 title "matMatOpt" with linespoints

pause -1