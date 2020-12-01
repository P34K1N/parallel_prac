all: main
main: main.c
	mpicc -o $@ $^ -std=c99
test: main
	rm -f test_results.log
	./test_script.sh test_results.log
report: main
	./report_script.sh
collect:
	./collect_script.sh
post_proc: time.dat post_proc.c
	gcc -o post_proc post_proc.c
	./post_proc
