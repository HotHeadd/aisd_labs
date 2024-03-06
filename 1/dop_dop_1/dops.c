#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>
#include "basic.h"
#define END {\
if ((filename != NULL) && (filename != matrix->filename)) free(filename);\
if ((matrix != NULL)&&(matrix->filename != NULL)) free(matrix->filename);\
if (matrix != NULL) free(matrix);\
if (input != NULL) fclose(input);\
if (output != NULL) fclose(output);\
return 0;\
}
#define FUN_EXIT {printf("Выхожу...\n"); fclose(input); return -1;}

typedef struct Matrix{
    char* filename;
    int amount;
} Matrix;

int null_in(int num){
	if (num == 0) return 0;
	while (num > 0){
		if (num % 10 == 0) return 0;
		num /= 10;
	}
	return 1;
}
// GOTO QUESTIONS.TXT
void menu(){
    printf("Выберете опцию\n");
    printf("(1) Ввести матрицу с клавиатуры и вывести в бинарный файл, а потом считать\n");
    printf("(2) Ввести уже существующую матрицу из файла\n");
}

int fill_file(FILE* file, int m){
    int nol = 0, ret_offset;
    fwrite(&m, sizeof(int), 1, file);
    for (int i=0; i<2*m; i++){
        fwrite(&nol, sizeof(int), 1, file);
    }
    ret_offset = (m*2+1)*sizeof(int);
    fseek(file, sizeof(int), SEEK_SET);
    return ret_offset;
}

int take_and_write(char* filename){
    int element_kept=0, offset=0, res=0, mat_strings=0, actual_amount=0;
    FILE* input = fopen(filename, "wb");
    if (input == NULL) FUN_EXIT
    printf("Введите m -- количество строк матрицы: ");
	res = custom_int_input(&mat_strings, o_n_and_0);
    if (res == -1) FUN_EXIT
    offset = fill_file(input, mat_strings);
    for (int i=0; i<mat_strings;i++){
        printf("Введите количество элементов в %d строке: ", i+1);
        int res = custom_int_input(&actual_amount, o_n_and_0);
        if (res == -1) FUN_EXIT
        fwrite(&actual_amount, sizeof(int), 1, input);
        fwrite(&offset, sizeof(int), 1, input);
        fseek(input, offset, SEEK_SET);
        for (int j=0; j<actual_amount; j++){
            printf("Введите элемент: ");
			res = custom_int_input(&element_kept, always_false);
            if (res == -1) FUN_EXIT
            fwrite(&element_kept, sizeof(int), 1, input);
        }
        offset += actual_amount*sizeof(int);
        fseek(input, (1+(i+1)*2)*sizeof(int), SEEK_SET);
    }
    fclose(input);
    return 0;
}

int process_string(FILE* input, FILE* output, int actual_amount){
    int element_kept=0, sum=0, res;
    for (int i=0; i<actual_amount; i++){
        res = fread(&element_kept, sizeof(int), 1, input);
        if (res == 0) return -1;
        if (null_in(element_kept)) sum += element_kept;
        printf("%d ", element_kept);
    }
    printf("\n");
    fwrite(&sum, sizeof(int), 1, output);
    return 0;
}

int display_vector(FILE* output, int amount){
    int element_kept, res;
    fseek(output, 0, SEEK_SET);
    printf("Вектор: ");
    for (int i=0;i<amount;i++){
        res = fread(&element_kept, sizeof(int), 1, output);
        if (res == 0) return -1;
        printf("%d ", element_kept);
    }
    printf("\n");
}

int main(){
    int offset=0, res=0, actual_amount=0, one=1;
    Matrix* matrix = NULL;
    char* filename = NULL;
    FILE* output = NULL;
    FILE* input = NULL;
    filename = readline("Введите имя файла, с которым будет осуществляться работа: ");
    if ((filename == NULL) || (strlen(filename) == 0)){
        free(filename);
        filename = NULL;
        END
    }
    matrix = malloc(sizeof(Matrix));
    matrix->filename = filename;
    menu();
    switch (better_getchar()){
        case '1':
            res = take_and_write(filename);
            if (res == -1)  END
            break;
        case '2':
            break;
        case EOF:
            END
        default:
            printf("Неверный ввод!\n");
    }
    /// open in
    input = fopen(matrix->filename, "rb");
    if (input == NULL) END
    /// open out
    filename = readline("Введите имя файла, к который вывести итоговый вектор: ");
    if (filename == NULL) END
    if (filename == matrix->filename){
        free(filename);
        filename = readline("Mistakes are made. Try again: ");
    }
    output = fopen(filename, "w+b");
    if (output == NULL) END
    //task
    fread(&(matrix->amount), sizeof(int), 1, input);
    fwrite(&one, sizeof(int), 1, output);
    fwrite(&(matrix->amount), sizeof(int), 1, output);
    one = 3*sizeof(int);
    fwrite(&(one), sizeof(int), 1, output);
    if (matrix->amount < 0) {
        printf("Неправильный формат данных\n");
        END
    }
    printf("Матрица: \n");
    for (int i=0; i<matrix->amount; i++){
        res = fread(&actual_amount, sizeof(int), 1, input);
        if ((actual_amount<0)||(res == 0)){
            printf("Неправильный формат данных\n");
            END
        }
        printf("%d\n", actual_amount);
        res = fread(&offset, sizeof(int), 1, input);
        if ((offset <= 0)||(res == 0)){
            printf("Неправильный формат данных\n");
            END
        }
        printf("%d\n", offset);
        fseek(input, offset, SEEK_SET);
        res = process_string(input, output, actual_amount);
        if (res == -1){
            printf("Неправильный формат данных\n");
            END
        }
        fseek(input, (1+(i+1)*2)*sizeof(int), SEEK_SET);
    }
    display_vector(output, matrix->amount);
    END
}