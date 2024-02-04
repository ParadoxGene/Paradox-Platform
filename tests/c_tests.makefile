all:
	gcc -std=c11 -o c_tests.out -I../source/c/include ./tests.c ../source/c/io.c