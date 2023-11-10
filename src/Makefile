CC = g++
TESTFLAGS = -pthread -lgtest
CPPFLAGS = -g -Wall -Werror -Wextra -std=c++17
LCOVFLAGS = --ignore-errors inconsistent --ignore-errors mismatch

SRC = s21_matrix_oop.cc
LIB_NAME = s21_matrix_oop
TEST_SRC = tests/check.cc

all: $(LIB_NAME).a gcov_report

test: 
	@$(CC) $(TEST_SRC) $(SRC) $(CPPFLAGS) $(TESTFLAGS) -o check
	@./check

s21_matrix_oop.a:
	@$(CC) $(SRC) $(CPPFLAGS) -c -o $(LIB_NAME).o
	@ar rcs $@ $(LIB_NAME).o
	@ranlib $@
	@rm -rf $(LIB_NAME).o

clean:
	@/bin/rm -rf *.o *.a check *.gcno *.gcda report *.info *.dSYM


gcov_report: $(TEST_SRC) $(SRC)
	@$(CC) --coverage $^ $(TESTFLAGS) $(CPPFLAGS) -o check
	@./check
	@lcov -t "check" -o check.info -c -d ./  --no-external $(LCOVFLAGS)
	@genhtml -o report check.info $(LCOVFLAGS)
	open report/index.html

style:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cc *.h tests/*.cc
	rm -rf .clang-format

stylecheck:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cc *.h tests/*.cc
	rm -rf .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.cc

leaks: test
	CK_FORK=no leaks --atExit -- ./check
