
// Copyright 2022 Neida Road
#ifndef FLAGS_FUNC_H
#define FLAGS_FUNC_H
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

void plus_print_cat(int count, int enter, int str_count, int enter_count,
                    char current, int *str_count_b, type_flag **flag);

void change_print_cat(char current, int enter_count, int *str_count,
                      type_flag **flag);

char **sample_into_array(char *optarg, int count, char **sample_array);

char **no_flags_sample_found(char **argv, char **sample_array);

char *samples_connect(char **samples, int count_samples, char *sample_link,
                      grep_flag flag);

char **file_matrix(int argc, char **argv, char **files, int count_sample,
                   int *i, grep_flag flag);

void open_file_func(char *sample_link, char **file, int curent_file,
                    int count_files, grep_flag flag);

void print_rezult(char *curent_string, char **files, int curent_file,
                  int count_string, int count_files, grep_flag flag);

void flag_filter(char *curent_string, int print_status, char **file,
                 int curent_file, int *count_str_smp, int count_files, int *fl,
                 int count_string, int size_line, regex_t expr, grep_flag flag);

char *samples_for_flag_f(char *sample_link, char *optarg);

void flag_o_print(char *curent_string, char **file, int curent_file,
                  int count_string, int count_files, int size_line,
                  regex_t expr, grep_flag flag);

#endif