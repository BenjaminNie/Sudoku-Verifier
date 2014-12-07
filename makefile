sudoku: sudoku.h sudoku.c
	gcc -pthread -o sudoku sudoku.c
gdb: sudoku.h sudoku.c
	gcc -ggdb -o sudoku_gdb sudoku.c
