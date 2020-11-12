main_mpi: main_mpi.c
	mpicc -o main_mpi main_mpi.c -lm
main_pthread: main_pthread.c
	gcc -o main_pthread main_pthread.c -pthread -lm
test: main_mpi main_pthread
	./test_script.sh test_results.log
report: main_mpi
	./report_script.sh
collect: res/max_8_4_5.txt res/sum_8_4_5.txt
	./collect_script.sh
plot: sumtime_grid.dat maxtime_grid.dat
	gnuplot makeplot.sh
	
