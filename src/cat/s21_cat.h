// Copyright 2022 Neida Road
#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/flags_func.h"
#include "../common/struct.h"

/// @brief Считывает данные введенные в командной строке
/// @param argc кол-во элементов введенных в командную строку
/// @param argv массив этих самых элементов
/// @param flag структура с флагами утилиты
void find_flags(int argc, char **argv, struct type_flag *flag);

/// @brief Считывает файл и выводит результат работы флагов
/// @param argc кол-во элементов введенных в командную строку
/// @param argv массив этих самых элементов
/// @param flag структура с флагами утилиты
void read_flags(int argc, char **argv, struct type_flag *flag);

#endif