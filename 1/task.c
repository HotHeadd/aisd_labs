#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "basic.h"

int null_in(int num){
	if (num == 0) return 0;
	while (num > 0){
		if (num % 10 == 0) return 0;
		num /= 10;
	}
	return 1;
}

int* form_vector(Matrix* matrix){
	int* vector = malloc(sizeof(int)*(matrix->amount));
	Line* line = matrix->mat_head;
	for (int i=0; i<(matrix->amount); i++){
		int sum = 0;
		Node* elem = line->first_elem;
		for (int j=0; j<(line->amount); j++){
			if (null_in(elem->number)){
				sum += elem->number;
			}
			elem = elem->next_num;
		}
		line = line->next_line;
		vector[i] = sum;
	}
	return vector;
}

int main(){
	Matrix* matrix = input_matrix();
	if (matrix == NULL) return 0;
	display_matrix(matrix);
	int* vector = form_vector(matrix);
	display_vector(vector, matrix->amount);
	free(vector);
	free_matrix(matrix);
	return 0;
}
