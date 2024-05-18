#pragma once
#include <stdio.h>

#define GOOD 0
#define ROOT_CREATED 2
#define KEY_EXIST 1
#define ELEM_NOT_FOUND 3
#define FILE_ERROR 4
#define FORMAT_ERROR 5
#define NO_TREE 6
#define MULTIPLE_DATA 7
#define LAST_ELEMENT 8
#define END_INPUT -1

int o_n_and_0(double);
int always_false(double);
int only_negative(double);

int custom_double_input(double*, int (*fun)(double));
int custom_int_input(int*, int (*fun)(double));
int custom_uns_input(unsigned* poin, int (*fun)(double));

char better_getchar();

char* file_readline(FILE* file);

char* g_readline(const char* prompt);