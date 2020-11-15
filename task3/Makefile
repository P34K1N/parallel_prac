main_mpi: main_mpi.c
	mpicc -o main_mpi main_mpi.c -lm
main_pthread: main_pthread.c
	gcc -o main_pthread main_pthread.c -pthread -lm -std=c11
test: main_mpi main_pthread
	./test_script.sh test_results.log
report: main_mpi
	./report_script.sh
collect: 
	./collect_script.sh
plot: sumtime_grid_normed.dat maxtime_grid_normed.dat
	gnuplot makeplot.sh
report_p: main_pthread
	./report_script_p.sh
collect_p: 
	./collect_script_p.sh
plot_p: sumtime_grid_normed_p.dat maxtime_grid_normed_p.dat
	gnuplot makeplot_p.sh
