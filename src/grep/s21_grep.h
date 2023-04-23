// Copyright 2022 Neida Road
#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/flags_func.h"
#include "../common/struct.h"

char *find_options(int argc, char **argv, grep_flag *flag, int *count,
                   char *samples);

void run_utilit(int argc, char **argv, char *samples, int count,
                grep_flag flag);

#endif