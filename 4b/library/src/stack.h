#pragma once

#include "tree.h"

#define SIZE 256

typedef struct stack_tm stack_tm;

stack_tm* get_stack(int maxelems);
void free_stack(stack_tm* stack);

int pop(stack_tm* stack, Node** data);
int push(stack_tm* stack, Node* data);
Node* peek(stack_tm* stack);