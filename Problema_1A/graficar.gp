set terminal pngcairo enhanced size 640, 640
set output 'grafico.png'

set title "velocidad v/s angulo theta"
set xlabel "angulo"
set xrange [0:360]
set ylabel "velocidad"
set grid

plot 'datos.dat' ti 'Datos'
