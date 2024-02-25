#include <stdio.h>
#include <stdlib.h>
#include "stacklib.h"

typedef struct Node{
    char symbol;
    struct Node* next;
} Node;

typedef struct stack_t{
    struct Node* first_elem;
} stack_t;

stack_t* get_stack(){
    stack_t* stack = malloc(sizeof(stack));
    stack->first_elem = NULL;
    return stack;
}

void free_stack(stack_t* stack){
    Node* elem = stack->first_elem;
    Node* prev_elem;
    while (elem != NULL){
        prev_elem = elem;
        elem = elem->next;
        free(prev_elem);
    }
    free(stack);
}

int pop(stack_t* stack, char* symbol){
    if (stack->first_elem == NULL) return -1;
    Node* elem = stack->first_elem;
    *symbol = elem->symbol;
    stack->first_elem = elem->next;
    free(elem);
    return 0;
}
int push(stack_t* stack, char symbol){
    Node* elem = malloc(sizeof(Node));
    Node* prev = stack->first_elem;
    stack->first_elem = elem;
    elem->next = prev;
    elem->symbol = symbol;
    return 0;
}
char check_stack(stack_t* stack){
    if (stack->first_elem != NULL){
        return stack->first_elem->symbol;
    }
    return EOF;
}