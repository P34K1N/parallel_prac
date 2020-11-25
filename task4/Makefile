all: main
main: main.c
	mpicc -o $@ $^
test: main
	rm -f test_results.log
	./test_script.sh test_results.log
