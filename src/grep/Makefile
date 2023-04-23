CC = gcc
FLAGS = -Werror -Wall -Wextra -std=c11 -ggdb

all: s21_grep

s21_grep.o: s21_grep.c
	$(CC) $(FLAGS) -c s21_grep.c -o s21_grep.o

flags_func.o: ../common/flags_func.c
	$(CC) $(FLAGS) -c ../common/flags_func.c -o flags_func.o

s21_grep: s21_grep.o flags_func.o
	$(CC) $(FLAGS) *.o -o s21_grep

rebuild:
	make clean
	make s21_grep

clean:
	rm -rf *.o
	rm -rf s21_grep