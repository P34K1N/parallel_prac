all: main
main: main.c
	mpicc -o main main.c -std=c99
test: main
	rm -f test_results.log
	./test_script.sh test_results.log
report: main
	./report_script.sh
collect:
	./collect_script.sh
