#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "basic.h"

void display_matrix(Matrix* matrix){
    printf("\nИсходная матрица:\n");
    Line* line = matrix->mat_head;
    for (int i=0;i<(matrix->amount);i++){
        Node* elem = line->first_elem;
        for (int j=0;j<(line->amount);j++){
            if (j != 0) printf(" ");
            printf("%d", elem->number);
            elem = elem->next_num;
        }
        line = line->next_line;
        printf("\n");
    }
    return;
}

void display_vector(int* vector, int n){
    printf("Результирующий вектор:\n");
    for (int i=0; i<n; i++){
        if (i != 0) printf(" ");
        printf("%d", vector[i]);
    }
    printf("\n");
    return;
}

void free_matrix(Matrix* matrix){
    Line* line;
    Line* prev_line;
    Node* elem;
    Node* prev_elem;
    for (int i=0;i<matrix->amount;i++){
        if (i == 0) line = matrix->mat_head;
        else{
            prev_line = line;
            line = line->next_line;
            free(prev_line);
        }
        if (line->amount == -1) break;
        for (int j=0; j<(line->amount);j++){
            if (j == 0) elem = line->first_elem;
            else{
                prev_elem = elem;
                elem = elem->next_num;
                free(prev_elem);
            }
        }
        if (line->amount) free(elem);
    }
    if (matrix->amount != 0) free(line);
    free(matrix);
    return;
}

Matrix* input_matrix(){
    int m=0, n=0, p=0;
    Matrix* matrix = (Matrix*)calloc(1, sizeof(Matrix));
    Line* prev_line;
	Line* line = NULL;
	Node* elem=NULL;
	Node* prev_elem;
	printf("Введите m -- количество строк матрицы: ");
	int res = custom_int_input(&m, o_n_and_0);
	if (res == -1){
		free_matrix(matrix);
		printf("\nВыхоожу...\n");
		return NULL;
	}
	matrix->amount = m;
	for (int i=0;i<m;i++){
		prev_line = line;
		line = (Line*)calloc(1, sizeof(Line));
		if (i == 0){
			matrix->mat_head = line;
		}
		else{
			prev_line->next_line = line;
		}
		printf("Введите количество элементов в %d строке: ", i+1);
		res = custom_int_input(&n, o_n_and_0);
		if (res == -1){
			line->amount = -1;
			free_matrix(matrix);
			printf("\nВыхоожу...\n");
			return NULL;
		}
		line->amount = n;
		line->next_line = NULL;
		for (int j=0;j<n;j++){
			prev_elem = elem;
			elem = (Node*)malloc(sizeof(Node));
			if (j == 0){
				line->first_elem = elem;
			}
			else{
				prev_elem->next_num = elem;
			}
			elem->next_num = NULL;
			printf("Введите элемент: ");
			res = custom_int_input(&p, always_false);
			elem->number = p;
			if (res == -1){
				line->amount = j+1;
				matrix->amount = i+1;
				free_matrix(matrix);
				printf("\nВыхоожу...\n");
				return NULL;
			}
		}
	}
    return matrix;
}