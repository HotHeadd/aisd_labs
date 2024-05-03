#pragma once
#include <stdio.h>

int o_n_and_0(double);
int always_false(double);
int only_negative(double);

int custom_double_input(double*, int (*fun)(double));
int custom_int_input(int*, int (*fun)(double));
int custom_uns_input(unsigned* poin, int (*fun)(double));

char better_getchar();

char* file_readline(FILE* file);