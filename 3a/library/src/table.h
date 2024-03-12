#pragma once

typedef struct stack_t stack_t;

stack_t* get_stack();
void free_stack(stack_t*);

int pop(stack_t*, char**);
int push(stack_t*, char*);
char* check_stack(stack_t* stack);