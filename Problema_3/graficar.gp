set term png
set output 'graph.png'


row_start = 1019
row_end = 1119


set title "Temperatura T(x) vs posición x"
set xlabel "x [m]"
set ylabel "T(x) [K]"

datafile = '< sed -n "' . row_start . ',' . row_end . ' p" datos.dat'
plot datafile using 1:2 with lines notitle
