main_mpi: main_mpi.c
	mpicc -o main_mpi main_mpi.c -lm
main_pthread: main_pthread.c
	gcc -o main_pthread main_pthread.c -pthread -lm
test: main_mpi main_pthread
	./test_script.sh test_results.log
