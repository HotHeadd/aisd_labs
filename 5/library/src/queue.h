#pragma once

#include "gr_main.h"
#define Q_OVERFLOW 10

#define QSIZE 256

typedef struct Queue{
    int head;
    int tail;
    Node* elements[QSIZE];
} Queue;

int empty(Queue* queue);

Node* pop(Queue* queue);

int push(Queue* queue, Node* elem);

