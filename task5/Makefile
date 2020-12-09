all: main
main: main.c
	mpicc -o main main.c
test: main
	rm -f test_results.log
	./test_script.sh test_results.log
