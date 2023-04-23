CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11

all: s21_cat

cat.o: s21_cat.c
	$(CC) $(FLAGS) -c s21_cat.c -o s21_cat.o

flags_func.o: ../common/flags_func.c
	$(CC) $(FLAGS) -c ../common/flags_func.c -o flags_func.o

s21_cat: cat.o flags_func.o
	$(CC) $(FLAGS) *.o  -o s21_cat


rebuild:
	make clean
	make s21_cat

clean:
	rm -rf *.o
	rm -rf s21_cat 