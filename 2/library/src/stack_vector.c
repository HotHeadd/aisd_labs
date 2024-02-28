#include <stdlib.h>
#include <stdio.h>
#include "basic.h"
#include "./stacklib.h"

typedef struct stack_t{
    int size;
    int top;
    char** elements;
} stack_t;

stack_t* get_stack(){
    int size, res;
    printf("Введите размер стека: ");
    res = custom_int_input(&size, only_negative);
    if (res == -1) return NULL;
    stack_t* stack = malloc(sizeof(stack_t));
    stack->size = size;
    stack->top = 0;
    stack->elements = malloc(size*sizeof(char*));
    return stack;
}

int push(stack_t* stack, char* symbol){
    int tops = stack->top;
    if (tops == stack->size) return 1;
    (stack->elements)[tops] = symbol;
    (stack->top) += 1;
    return 0;
}

int pop(stack_t* stack, char** symbol){
    if (stack->top == 0) return -1;
    stack->top -= 1;
    *symbol = (stack->elements)[stack->top];
    return 0;
}

char* check_stack(stack_t* stack){
    if (stack->top != 0){
        return (stack->elements)[stack->top - 1];
    }
    return NULL;
}

void free_stack(stack_t* stack){
    char* fred;
    if (stack != NULL){
        if (stack->elements != 0){
            while (pop(stack, &fred) != -1) free(fred);
        }
        free(stack->elements);
    }
    free(stack);
}
