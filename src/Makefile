CC= gcc
CFLAGS= -Wall -Werror -Wextra -std=c11 -g
GCOVFLAGS= -fprofile-arcs -ftest-coverage
HEAD= matrix.h
TESTFLAGS= -lcheck -lm

UNIT_TEST= matrix_test.c 

EACH= matrix.c

ifeq ($(shell uname -s), Linux)
	TESTFLAGS+=-lpthread -lrt -lsubunit
endif

all: matrix.a

main:
	$(CC) $(CFLAGS) $(EACH) main.c

matrix.a:
	$(CC) $(CFLAGS) -c $(EACH)
	ar rcs matrix.a *.o
	rm -rf *.o

test: matrix.a $(UNIT_TEST)
	$(CC) $(GCOVFLAGS) $(UNIT_TEST) matrix.a -o test.out $(TESTFLAGS)
	./test.out

gcov_report: matrix.a $(UNIT_TEST)
	$(CC) $(GCOVFLAGS) $(UNIT_TEST) $(EACH) -o report.out $(TESTFLAGS)
	./report.out
	lcov -t "gcov_report" -o coverage_table.info -c -d .
	genhtml -o ./report coverage_table.info

clean: 
	rm -rf *.o *.a
	rm -rf *gcno *.gcda *.info *.out *.gcov
	rm -rf matrix.a
	rm -rf ./report
	rm -rf test.out.dSYM
	clear

style: 
	clang-format -style=Google -i *.c *.h

valgrind: matrix.a $(UNIT_TEST)
	$(CC) $(GCOVFLAGS) $(UNIT_TEST) matrix.a -o test.out $(TESTFLAGS)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file="val_out.txt" ./test.out