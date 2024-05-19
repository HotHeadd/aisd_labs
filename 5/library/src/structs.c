#include "structs.h"
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



// int hq_compare(Node* first, Node* second){
//     return first->dist - second->dist;
// }

// void swap(HeapPQ* q, int i, int j){
//     Node* buff = q->elements[i];
//     q->elements[i] = q->elements[j];
//     q->elements[j] = buff;
// }

// void siftDown(HeapPQ* q, int i){
//     while ((2*i + 1) < q->size){
//         int left = 2*i + 1;
//         int right = 2*i + 2;
//         int j = left;
//         if ((right < q->size) && (hq_compare(q->elements[right], q->elements[left]) < 0)){
//             j = right;
//         }
//         if (hq_compare(q->elements[i], q->elements[j]) <= 0){
//             break;
//         }
//         swap(q, i, j);
//         i = j;
//     }
// }

// void siftUp(HeapPQ* q, int i){
//     while (hq_compare(q->elements[i], q->elements[(i-1) / 2]) < 0){
//         swap(q, i, (i-1) / 2);
//         i = (i-1) / 2;
//     }
// }

// Node* hq_popmin(HeapPQ* q){
//     Node* ret = q->elements[0];
//     q->size--;
//     q->elements[0] = q->elements[q->size];
//     siftDown(q, 0);
//     return ret;
// }

// void hq_insert(HeapPQ* q, Node* elem){
//     q->elements[q->size] = elem;
//     q->size++;
//     siftUp(q, q->size - 1);
// }