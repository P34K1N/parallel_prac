all: multi
multi: main.cpp handlr.cpp multiplications.cpp tech.cpp
	g++ -o $@ $^
test: multi
	rm -f test_results.log
	./test_script.sh test_results.log
report: multi
	./report_script.sh
my:
	echo "this is a test\n"
