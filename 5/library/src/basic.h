#pragma once
#include <stdio.h>

int o_n_and_0(double);
int always_false(double);
int only_negative(double);

int custom_double_input(char*, double*, int (*fun)(double));
int custom_int_input(char*, int*, int (*fun)(double));
int custom_uns_input(char*, unsigned* poin, int (*fun)(double));

char better_getchar();

char* file_readline(FILE* file);

char* g_readline(const char* prompt);