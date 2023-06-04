CC = gcc
CFLAGS = -Wall

all: run_graph

run_graph: euler rk4 rk45_gsl euler2 rk4_2 graph

euler: euler.c
	$(CC) $(CFLAGS) -o euler euler.c -lm

rk4: rk4.c
	$(CC) $(CFLAGS) -o rk4 rk4.c -lm

rk45_gsl: rk45_gsl.c
	$(CC) $(CFLAGS) -o rk45_gsl rk45_gsl.c -lgsl -lgslcblas -lm

euler2: euler2.c
	$(CC) $(CFLAGS) -o euler2 euler2.c -lm

rk4_2: rk4_2.c
	$(CC) $(CFLAGS) -o rk4_2 rk4_2.c -lm

graph: euler rk4 rk45_gsl euler2 rk4_2
	./euler > datos1.dat
	./rk4 > datos2.dat
	./rk45_gsl > datos3.dat
	./euler2 > datos4.dat
	./rk4_2 > datos5.dat
	gnuplot plot_graph.gp

clean:
	rm -f euler rk4 rk45_gsl euler2 rk4_2 datos1.dat datos2.dat datos3.dat datos4.dat datos5.dat

.PHONY: all clean

