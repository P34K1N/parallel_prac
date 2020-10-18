all: multi
multi: main.o multiplications.o
	gcc -o $@ $^ -lm -lpapi -std=c99
main.o: main.c multiplications.o multiplications.h
	gcc -c -o $@ $< -lm -lpapi -std=c99
multiplications.o: multiplications.c multiplications.h
	gcc -c -o $@ $< -lm -std=c99
test: multi
	rm -f test_results.log
	./test_script.sh test_results.log
report: multi
	./report_script.sh
plot: multi
	gnuplot makeplot.sh
my:
	echo "this is a test\n"
clean:
	rm *.o
