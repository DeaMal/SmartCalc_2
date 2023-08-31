CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic
LFLAGS = -lstdc++
LDFLAGS = -lgtest
LIB = s21_calc.a
APP_NAME = s21_calculator
SOURCES = s21_calc_model.cc
LEAK_1 = leaks
LEAK_2 = leaks1
DVI_1 = dvi
DVI_2 = dvi1
ifeq ($(shell uname -s), Linux)
	LDFLAGS += -lm -lsubunit
	SRC_ICO = s21_calc.png
	LEAK_1 = leaks1
	LEAK_2 = leaks
	DVI_1 = dvi1
	DVI_2 = dvi
else ifeq ($(shell uname -s), Darwin)
	SRC_ICO = s21_calc.icns
else
	SRC_ICO = s21_calc.ico
endif
INST_SRC = *.cc *.h *.ui $(SRC_ICO) $(APP_NAME).pro
SRC_TEST = gtest_calc.cc
OBJECTS = *.o

all: $(LIB)

install:
	mkdir ../build
	cp $(INST_SRC) ../build
	cd ../build && qmake $(APP_NAME).pro && make
	cd ../build && ln -s $$PWD/$(APP_NAME).app ~/Desktop/

uninstall:
	rm -rf ../build
	rm -rf ~/Desktop/$(APP_NAME).app

clean:
	rm -f *.o *.a *.gcda *.gcno *.gcov *.out *.html *.info
	rm -f test
	rm -rf $(APP_NAME)_report *.dSYM
	rm -rf ~/Desktop/$(APP_NAME).tar.gz

$(DVI_1):
	open calc.pdf

$(DVI_2): calc.dvi

pdf: calc.pdf

dist: install
	cd ../ && tar -cvzf ~/Desktop/$(APP_NAME).tar.gz build

test: clean $(LIB)
	$(CC) $(CFLAGS) $(SRC_TEST) $(LIB) $(LDFLAGS) -o test $(LFLAGS)
	./test
	make clean

$(LIB):
	$(CC) $(CFLAGS) -c $(SOURCES) $(LFLAGS)
	ar rc $(LIB) $(OBJECTS)
	ranlib $(LIB)
	rm -f $(OBJECTS)
	
calc.dvi:
	texi2dvi calc.texi
	
calc.pdf:
	texi2pdf calc.texi

fsanit: clean $(LIB)
	$(CC) $(CFLAGS) -fsanitize=address -fsanitize=leak $(SRC_TEST) $(LIB) $(LDFLAGS) $(LFLAGS)
	./a.out
	make clean

format: 
	clang-format --style=Google -n s21_calc_*.cc s21_calc_*.h main.cc $(SRC_TEST)

$(LEAK_1): clean $(LIB)
	$(CC) $(CFLAGS) $(SRC_TEST) $(LIB) $(LDFLAGS) -o test $(LFLAGS)
	leaks -atExit -- ./test
	make clean

$(LEAK_2): clean $(LIB)
	$(CC) $(CFLAGS) $(SRC_TEST) $(LIB) $(LDFLAGS) -o test $(LFLAGS)
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt ./test
	grep "ERROR" valgrind-out.txt
	make clean

gcov_report: for_report
	lcov -t "$(APP_NAME)" -o $(APP_NAME).info -c -d . --rc lcov_branch_coverage=1
	genhtml -o $(APP_NAME)_report $(APP_NAME).info --rc lcov_branch_coverage=1
	rm -f *.gcda *.gcno *.gcov *.info test
	open $(APP_NAME)_report/index.html

gcov_report1: for_report
	gcov *.gcda
	gcovr
	mkdir $(APP_NAME)_report
	gcovr --html-details $(APP_NAME)_report/index.html
	rm -f *.gcov *.gcda *.gcno test
	open $(APP_NAME)_report/index.html

for_report: clean
	$(CC) $(CFLAGS) -c --coverage $(SOURCES) $(LFLAGS)
	$(CC) $(CFLAGS) -c $(SRC_TEST) $(LFLAGS)
	$(CC) $(CFLAGS) $(OBJECTS) --coverage $(LDFLAGS) -o test $(LFLAGS)
	./test
	
rebuild: clean all
