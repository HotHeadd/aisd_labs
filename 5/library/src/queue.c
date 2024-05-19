#include "queue.h"
#include <stddef.h>

int empty(Queue* queue){
    return queue->head == queue->tail;
}

int push(Queue* q, Node* elem){
    if ((q->tail + 1)%QSIZE == q->head){
        return Q_OVERFLOW;
    }
    q->elements[q->tail] = elem;
    q->tail = (q->tail + 1)%QSIZE;
    return GOOD;
}

Node* pop(Queue* q){
    if (empty(q)){
        return NULL;
    }
    Node* elem = q->elements[q->head];
    q->head = (q->head + 1)%QSIZE;
    return elem;
}