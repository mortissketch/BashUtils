// Copyright 2022 Neida Road
#include "flags_func.h"

/// @brief выводит результат работы флагов b и n
/// @param count счетчик символов
/// @param enter если прошый символ был символом переноса строки то 1, иначе 0
/// @param str_count счетчик строк
/// @param enter_count счетчик идущик подряд переносов строки
/// @param current текущий символ
/// @param str_count_b счетчик непустых символов
/// @param flag структура с флагами утилиты
void plus_print_cat(int count, int enter, int str_count, int enter_count,
                    char current, int *str_count_b, type_flag **flag) {
  if ((*flag)->b && enter == 1) {
    if (enter == 1 && current != '\n') {
      printf("%6d\t", *str_count_b);
    } else {
      if (enter == 1 && current == '\n') {
        *str_count_b -= 1;
      }
      if (count == 1) {
        printf("%6d\t", *str_count_b);
      }
    }
  } else {
    if ((*flag)->b && count == 1 && current != '\n') {
      printf("%6d\t", *str_count_b);
    } else {
      if (count == 1 && current == '\n') {
        *str_count_b -= 1;
      }
    }
    if ((*flag)->n && (count == 1 || enter == 1) && (!(*flag)->b)) {
      if ((*flag)->s) {
        if (enter_count < 3) {
          printf("%6d\t", str_count);
        }
      } else {
        printf("%6d\t", str_count);
      }
    }
  }
}

/// @brief выводит результат работы флагов E, T, s, v, e, t
/// @param current текущий символ
/// @param enter_count счетчик идущик подряд переносов строки
/// @param str_count счетчик строк
/// @param flag структура с флагами утилиты
void change_print_cat(char current, int enter_count, int *str_count,
                      type_flag **flag) {
  if ((*flag)->E && current == '\n') {
    if ((*flag)->b || (*flag)->s) {
      if (enter_count < 3) {
        printf("$");
      } else {
        if ((*flag)->b && !(*flag)->s) printf("$");
      }
    } else {
      printf("$");
    }
  }
  if ((*flag)->T && current == '\t') {
    printf("^I");
  } else {
    if ((*flag)->s && enter_count < 3) {
      if ((*flag)->v && (((int)current >= 0 && (int)current < 32 &&
                          (int)current != 10 && (int)current != 9) ||
                         (int)current == 127)) {
        if ((int)current == 127) {
          printf("^?");
        } else
          printf("^%c", (char)((int)current + 64));
      } else {
        printf("%c", current);
      }
    } else {
      if (!(*flag)->s) {
        if ((*flag)->v && (((int)current >= 0 && (int)current < 32 &&
                            (int)current != 10 && (int)current != 9) ||
                           (int)current == 127)) {
          if ((int)current == 127) {
            printf("^?");
          } else
            printf("^%c", (char)((int)current + 64));
        } else {
          printf("%c", current);
        }
      } else {
        *str_count -= 1;
      }
    }
  }
}

/// @brief вносит шаблоны в массив с шаблонами, если применен флаг e
/// @param optarg сохраняет текущий аргумент флага e
/// @param count счетчик флагов e
/// @param sample_array массив шаблонов
/// @return возвращает адрес массива
char **sample_into_array(char *optarg, int count, char **sample_array) {
  char **array = sample_array;
  if (count != 1) array = realloc(array, (count) * sizeof(char *));
  int len = strlen(optarg);
  array[count - 1] = calloc(len + 1, sizeof(char));
  strcpy(array[count - 1], optarg);
  return array;
}

/// @brief вносит шаблон в массив шаблонов, если отсутствует флаг e
/// @param argv массив элементов введенных в командную строку
/// @param sample_array массив шаблонов
/// @return возвращает адрес массива
char **no_flags_sample_found(char **argv, char **sample_array) {
  char **array = sample_array;
  int len = strlen(argv[optind]);
  *array = calloc(len + 1, sizeof(char));
  strcpy(*array, argv[optind]);
  return array;
}

/// @brief вносит файлы в массив с файлами
/// @param argc кол-во элементов введенных в командную строку
/// @param argv массив этих самых элементов
/// @param files адрес массива с файлами
/// @param count_sample кол-во шаблонов
/// @param i суммарное кол-во файлов
/// @return возвращает адрес массива с файлами
char *samples_connect(char **samples, int count_samples, char *sample_link,
                      grep_flag flag) {
  char *sample = sample_link;
  int len_sample = 0, count = 0;
  char * or = "|";
  count = samples[0] && count_samples == 0 ? 1 : count_samples;
  if (flag.f) {
    len_sample += strlen(or);
    len_sample += strlen(sample);
    sample = realloc(sample, len_sample + 1 * sizeof(char));
    strcat(sample, or);
  }
  for (int i = 0; i < count; i++) {
    len_sample += strlen(samples[i]);
    sample = realloc(sample, len_sample + 1 * sizeof(char));
    strcat(sample, samples[i]);
    if (i != count - 1 && count > 1) {
      len_sample += strlen(or);
      sample = realloc(sample, len_sample + 1 * sizeof(char));
      strcat(sample, or);
    }
  }
  return sample;
}

/// @brief заносит все файлы в массив
/// @param argc кол-во элементов введенных в командную строку
/// @param argv массив этих самых элементов
/// @param files адрес массива с файлами
/// @param count кол-во флагов e
/// @param i счетчик файлов
/// @return возвращает адрес с массивом фалов
char **file_matrix(int argc, char **argv, char **files, int count, int *i,
                   grep_flag flag) {
  char **file = files;
  int len, j;
  if (count == 0) {
    if (flag.f)
      j = 0;
    else
      j = 1;
  } else
    j = 0;
  for (; *i + j + optind < argc; *i += 1) {
    file = realloc(file, (*i + 1) * sizeof(char *));
    len = strlen(argv[*i + j + optind]);
    file[*i] = calloc(len + 1, sizeof(char));
    strcat(file[*i], argv[*i + j + optind]);
  }
  file = realloc(file, *i * sizeof(char *));
  return file;
}

/// @brief заносит из файла шаблоны в строку
/// @param sample_link адрес строки шаблонов
/// @param optarg строка аргумнта флага f
/// @return адрес строки шаблонов
char *samples_for_flag_f(char *sample_link, char *optarg) {
  char *copy_sample_link = sample_link;
  int size = strlen(copy_sample_link);
  char * or = "|", *sample = NULL;
  FILE *f = fopen(optarg, "r");
  if (f) {
    size_t size_sample = 0;
    while (getline(&sample, &size_sample, f) != -1) {
      if (sample[strlen(sample) - 1] == '\n' && strlen(sample) > 2) {
        sample[strlen(sample) - 1] = '\0';
      }
      if (size) {
        size += strlen(or) + size_sample;
        copy_sample_link = realloc(copy_sample_link, size * sizeof(char));
        strcat(copy_sample_link, or);
        strcat(copy_sample_link, sample);
      } else {
        size = strlen(sample);
        copy_sample_link = realloc(copy_sample_link, size * sizeof(char));
        strcpy(copy_sample_link, sample);
      }
    }
    free(sample);
  } else {
    fprintf(stderr, "%s: no such file\n", optarg);
  }
  fclose(f);
  return copy_sample_link;
}

/// @brief открывает файл и проходит по строкам из файла
/// @param sample_link строка с шаблонами
/// @param file адрес массива файлов
/// @param curent_file номер файла в массиве файлов
/// @param count_files кол-во файлов
/// @param flag структура флагов утилиты
void open_file_func(char *sample_link, char **file, int curent_file,
                    int count_files, grep_flag flag) {
  char *curent_string = NULL;
  int status = 0, count_string = 0, count_str_smp = 0, fl = 0, cflag = 0,
      size_line;
  regex_t expr;
  size_t size = 0;
  size_t nmatch = 1;
  regmatch_t pmatch[1];
  FILE *f = fopen(file[curent_file], "r");
  if (f) {
    cflag = flag.i ? REG_NEWLINE | REG_EXTENDED | REG_ICASE
                   : REG_NEWLINE | REG_EXTENDED;
    if (regcomp(&expr, sample_link, cflag) == 0) {
      while ((size_line = getline(&curent_string, &size, f)) != -1) {
        status = regexec(&expr, curent_string, nmatch, pmatch, 0);
        count_string++;
        flag_filter(curent_string, status, file, curent_file, &count_str_smp,
                    count_files, &fl, count_string, size_line, expr, flag);
        if (fl == 1 && flag.l && flag.c) break;
      }
      if (flag.c) {
        if (count_files > 1 && !flag.h) printf("%s:", file[curent_file]);
        printf("%d\n", count_str_smp);
      }
      if (flag.l) {
        if (fl) printf("%s\n", file[curent_file]);
      }
      regfree(&expr);
    }
    fclose(f);
  } else {
    if (!flag.s)
      fprintf(stderr, "grep: %s: No such file or directory\n",
              file[curent_file]);
  }
  free(curent_string);
}

/// @brief частичная обработка флагов
/// @param curent_string текущая строка файла
/// @param print_status результат работы regexec, если 0 то ф-ция нашла
/// совпадения
/// @param file адрес массива файлов
/// @param curent_file номер текущего файла в массиве файлов
/// @param count_str_smp кол-во строк с совпадениями
/// @param count_files кол-во файлов
/// @param fl флаг, связанный с флагом l
/// @param count_string общее кол-во строк в файле
/// @param sample_link строка с шаблонами
/// @param expr переменная с типом regex_t
/// @param flag структура флагов утилиты
void flag_filter(char *curent_string, int print_status, char **file,
                 int curent_file, int *count_str_smp, int count_files, int *fl,
                 int count_string, int size_line, regex_t expr,
                 grep_flag flag) {
  if (print_status == flag.v) {
    if ((!flag.c && !flag.l) && (!flag.o || (flag.o && flag.v))) {
      print_rezult(curent_string, file, curent_file, count_string, count_files,
                   flag);
    } else if ((!flag.c && !flag.l) && (flag.o && !flag.v)) {
      flag_o_print(curent_string, file, curent_file, count_string, count_files,
                   size_line, expr, flag);
    } else if (flag.l && flag.c) {
      *fl = 1;
      *count_str_smp = 1;
    } else {
      *fl = 1;
      *count_str_smp += 1;
    }
  }
}

/// @brief печатает частичный результат работы утилиты
/// @param curent_string текущая строка из файла
/// @param files адрес массива файлов
/// @param curent_file номер текущего файла в массиве файлов
/// @param count_string общее кол-во строк в файле
/// @param count_files общее кол-во файлов в массиве файлов
/// @param flag структура флагов утилиты
void print_rezult(char *curent_string, char **files, int curent_file,
                  int count_string, int count_files, grep_flag flag) {
  if (curent_string[strlen(curent_string) - 1] == '\n') {
    if (flag.n) {
      if (count_files > 1 && !flag.h) printf("%s:", files[curent_file]);
      printf("%d:%s", count_string, curent_string);
    } else {
      if (count_files > 1 && !flag.h) printf("%s:", files[curent_file]);
      printf("%s", curent_string);
    }
  } else {
    if (flag.n) {
      if (count_files > 1 && !flag.h) printf("%s:", files[curent_file]);
      printf("%d:%s\n", count_string, curent_string);
    } else {
      if (count_files > 1 && !flag.h) printf("%s:", files[curent_file]);
      printf("%s\n", curent_string);
    }
  }
}

/// @brief выводит результат работы флага o
/// @param curent_string текущая строка из файла
/// @param file адрес массива файлов
/// @param curent_file номер текущего файла в массиве файлов
/// @param count_string общее кол-во строк в файле
/// @param count_files общее кол-во файлов в массиве файлов
/// @param samples строка шаблонов
/// @param expr переменная с типом regex_t
/// @param flag структура флагов утилиты
void flag_o_print(char *curent_string, char **file, int curent_file,
                  int count_string, int count_files, int size_line,
                  regex_t expr, grep_flag flag) {
  regmatch_t pmatch[1];
  const size_t nmatch = 1;
  int status = regexec(&expr, curent_string, nmatch, pmatch, 0);
  int raz = 0, size_new_string = 0;
  char *only_sample = NULL, *str_without_cur_sample = NULL;
  if (!status) {
    if (pmatch->rm_eo <= size_line) {
      raz = (pmatch->rm_eo - pmatch->rm_so);
      only_sample = calloc(raz + 1, sizeof(char));
      for (int i = pmatch->rm_so, j = 0; i < pmatch->rm_eo; i++, j++) {
        only_sample[j] = curent_string[i];
      }
      print_rezult(only_sample, file, curent_file, count_string, count_files,
                   flag);
      free(only_sample);
      flag.n = 0;
      if ((pmatch->rm_eo + 1) >= size_line)
        free(only_sample);
      else {
        str_without_cur_sample = calloc(1, sizeof(char));
        for (int i = 0; i < pmatch->rm_so; i++) {
          size_new_string++;
          str_without_cur_sample = realloc(
              str_without_cur_sample, (size_new_string + 1) * sizeof(char));
          str_without_cur_sample[i] = curent_string[i];
        }
        for (int i = pmatch->rm_eo + 1; i < size_line; i++) {
          str_without_cur_sample = realloc(
              str_without_cur_sample, (size_new_string + 1) * sizeof(char));
          str_without_cur_sample[size_new_string] = curent_string[i];
          size_new_string++;
        }
        str_without_cur_sample =
            realloc(str_without_cur_sample, (size_new_string) * sizeof(char));
        flag_o_print(str_without_cur_sample, file, curent_file, count_string,
                     count_files, size_line, expr, flag);
        free(str_without_cur_sample);
      }
      // free(only_sample);
    }
  }
}
