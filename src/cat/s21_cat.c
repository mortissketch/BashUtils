// Copyright 2022 Neida Road
#include "s21_cat.h"

int main(int argc, char **argv) {
  type_flag flag = (type_flag){0};
  find_flags(argc, argv, &flag);  // Вызов функции обработки ввода
  read_flags(argc, argv, &flag);  // Вызов функции чтения файла
                                  // char tab = '\n';
  // printf("%d", (int)tab);
}

// Функция обработки ввода
void find_flags(int argc, char **argv, type_flag *flag) {
  // option - результат работы функции getopt_long; option_index - в случае
  // ввода длинных флагов
  int option = 0, option_index = 0;
  const char *short_options = "+bestnvTE";

  // Обработка длинных флагов и замена их на короткую версию
  const struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                        {"number", 0, 0, 'n'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {NULL, 0, NULL, 0}};

  // Цикл нужен для одновременной обработки и длинных и коротких версий флагов +
  // считаем флаги
  while ((option = getopt_long(argc, argv, short_options, long_options,
                               &option_index)) != -1) {
    switch (option) {
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->E = 1;
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->T = 1;
        flag->v = 1;
        break;
      case 'T':
        flag->T = 1;
        break;
      case 'E':
        flag->E = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
    }
  }
}

// Чтение файла
void read_flags(int argc, char **argv, type_flag *flag) {
  int id = optind;
  while (id < argc) {
    FILE *f = fopen(argv[id], "r");
    if (f) {
      int enter = 0, count = 1, str_count = 1, str_count_b = 1, enter_count = 0;
      char current;
      while ((current = fgetc(f)) != EOF) {
        enter_count = current == '\n' ? enter_count + 1 : 0;
        // Обработка символов
        plus_print_cat(count, enter, str_count, enter_count, current,
                       &str_count_b, &flag);
        change_print_cat(current, enter_count, &str_count, &flag);
        count++;
        if (current == '\n') {
          str_count_b++;
          str_count++;
          enter = 1;
        } else {
          enter = 0;
        }
      }
    }
    fclose(f);
    id++;
  }
}
