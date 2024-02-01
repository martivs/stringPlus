TARGET = s21_sprintf
FLAGS = -std=c11 -pedantic -lm -Wall -Werror -Wextra

all: test s21_string.a gcov_report

test: s21_string.a
	gcc $(FLAGS) test/*.c s21_string.a -o s21_string_test \
	`pkg-config --cflags --libs check`

s21_string.a: 
	gcc $(FLAGS) -c *.c
	ar rc s21_string.a *.o
	ranlib s21_string.a
	rm -rf *.o

gcov_report:
	gcc $(FLAGS) --coverage *.c test/*.c -o gcovreport \
	`pkg-config --cflags --libs check`
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info

style:
	clang-format -i -style=google *.c *.h
	clang-format -i -style=google test/*.c test/*.h

clean: 
	rm -rf $(TARGET) *.o s21_string.a *.gcno *.gcda gcovreport gcovreport.info s21_string_test rm report rm s21_sprintf.dSYM s21_1_ten