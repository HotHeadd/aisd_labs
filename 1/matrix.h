#pragma once

typedef struct Node{
    int number;
    struct Node* next_num;
} Node;

typedef struct Line{
    int amount;
    struct Node* first_elem;
    struct Line* next_line;
} Line;

typedef struct Matrix{
    int amount;
    struct Line* mat_head;
}Matrix;

void display_matrix(Matrix*);
void free_matrix(Matrix*);
void display_vector(int* vector, int);
Matrix* input_matrix();