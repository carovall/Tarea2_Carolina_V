set terminal pngcairo enhanced size 800,600
#grafico 1: y vs t
set output 'graph.png'

set title "Posición vs Tiempo"
set xlabel "t"
set ylabel "y(t)"

set xrange [0.0:0.5]
set yrange [0.006:0.0105]

plot 'datos1.dat' using 1:2 with lines title 'Euler h=0.008', \
     'datos2.dat' using 1:2 with lines title 'RK4 h=0.008', \
     'datos3.dat' using 1:2 with lines title 'RK45 h1=0.008', \
     'datos4.dat' using 1:2 with lines title 'Euler h=0.005', \
     'datos5.dat' using 1:2 with lines title 'RK4 h=0.005'

# grafico 2: y' vs t
reset
set output 'graph_vt.png'

set title "Velocidad vs Tiempo"
set xlabel "t"
set ylabel "v(t)"

set xrange [0.0:0.5]
set yrange [-0.02:0.0]

plot 'datos1.dat' using 1:3 with lines title 'Euler h=0.008', \
     'datos2.dat' using 1:3 with lines title 'RK4 h=0.008', \
     'datos3.dat' using 1:3 with lines title 'RK45 h1=0.008', \
     'datos4.dat' using 1:3 with lines title 'Euler h=0.005', \
     'datos5.dat' using 1:3 with lines title 'RK4 h=0.005'

# grafico 3: error vs t
reset
set output 'graph_error.png'

set title "Error absoluto vs Tiempo"
set xlabel "t"
set ylabel "error"

set xrange [0.0:0.5]
set yrange [-0.00001:0.0015]

plot 'datos1.dat' using 1:4 with lines title 'Euler h=0.008', \
     'datos2.dat' using 1:4 with lines title 'RK4 h=0.008', \
     'datos3.dat' using 1:4 with lines title 'RK45 h1=0.008', \
     'datos4.dat' using 1:4 with lines title 'Euler h=0.005', \
     'datos5.dat' using 1:4 with lines title 'RK4 h=0.005'

#guardar
set output
