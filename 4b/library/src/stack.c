#include <stdlib.h>
#include "stack.h"
#include "tree.h"

typedef struct stack_tm{
    int maxelems;
    int top;
    Node** elements;
} stack_tm;

stack_tm* get_stack(int maxelems){
    stack_tm* stack = malloc(sizeof(stack_tm));
    stack->maxelems = maxelems;
    stack->top = 0;
    stack->elements = malloc(maxelems*sizeof(Node*));
    return stack;
}

void upgrade(stack_tm* stack){
    stack->maxelems = stack->maxelems*2;
    stack->elements = realloc(stack->elements, stack->maxelems*sizeof(Node*));
}

int push(stack_tm* stack, Node* data){
    int tops = stack->top;
    if (tops == stack->maxelems) upgrade(stack);
    stack->elements[tops] = data;
    stack->top += 1;
    return 0;
}

int pop(stack_tm* stack, Node** data){
    if (stack->top == 0) return -1;
    stack->top -= 1;
    *data = stack->elements[stack->top];
    return 0;
}

Node* peek(stack_tm* stack){
    if (stack->top != 0){
        return stack->elements[stack->top - 1];
    }
    return NULL;
}

void free_stack(stack_tm* stack){
    Node* fred;
    if (stack != NULL){
        if (stack->top != 0){
            while (pop(stack, &fred) != -1) free_elem(fred, 1);
        }
        free(stack->elements);
    }
    free(stack);
}