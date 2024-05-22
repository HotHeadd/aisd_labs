#include "gr_main.h"
#include "gr_algo.h"
#include <stdlib.h>
#include "structs.h"
#include <stdio.h>
#include <string.h>

#define INF 100000000
#define MINF -100000000
#define WHITE 0
#define GREY 1
#define BLACK 2

void init(Graph* graph, char color, int dist){
    for (int i=0; i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if ((elem != NULL) && (elem->state == 1)){
            elem->color = color;
            elem->dist = dist;
            elem->pred = NULL;
        }
    }
}

Graph* findwide(Graph* graph, char* human, int handshakes){
    if (graph == NULL){
        return NULL;
    }
    Node* elem = find(graph, human);
    if (elem == NULL) return NULL;
    init(graph, WHITE, INF);
    Queue* q = calloc(1, sizeof(Queue));
    elem->color = GREY;
    elem->dist = 0;
    push(q, elem);
    Graph* result = get_graph(SIZE);
    while (!empty(q)){
        Node* current = pop(q);
        if (current->dist <= handshakes){
            gr_add_node(result, current->name);
            Edge* edge = current->edges;
            while (edge){
                elem = find(graph, edge->dest);
                if (elem->color == WHITE){
                    elem->color = GREY;
                    elem->dist = current->dist + 1;
                    push(q, elem);
                }
                edge = edge->next;
            }
        }
        current->color = BLACK;
    }
    free(q);
    return result;
}

int compare(Node* first, Node* second){
    return first->dist - second->dist;
}

Node** dijkstra(Graph* graph, char* first, char* second, int* amount){
    *amount = 0;
    if (graph == NULL){
        return NULL;
    }
    Node* elem;
    Node* start = find(graph, first);
    Node* end = find(graph, second);
    if ((start == NULL) || (end == NULL)) return NULL;
    init(graph, 0, INF);
    start->dist = 0;
    for (int i=0; i<graph->msize;i++){
        elem = graph->nodes[i];
        if ((elem == NULL) || (elem->state != 1)){
            continue;
        }
        Node* Vmin = NULL;
        for (int j=0; j<graph->msize;j++){
            Node* inner = graph->nodes[j];
            if ((inner == NULL) || (inner->state != 1)){
                continue;
            }
            if ((!inner->color) && ((!Vmin) || inner->dist < Vmin->dist)){
                Vmin = inner;
            }
        }
        if (Vmin->dist == INF){
            break;
        }
        Vmin->color = 1;
        Edge* edge = Vmin->edges;
        while (edge){
            elem = find(graph, edge->dest);
            if ((edge->rel > 0) && ((Vmin->dist + 1) < elem->dist)){
                elem->dist = Vmin->dist + 1;
                elem->pred = Vmin;
            }
            edge = edge->next;
        }
    }
    if (end->dist == INF){
        *amount = -1;
        return NULL;
    }
    Node** result = calloc(SIZE, sizeof(Node*));
    elem = end;
    while (elem != start){
        result[*amount] = elem;
        *amount += 1;
        elem = elem->pred;
    }
    result[*amount] = elem;
    *amount += 1;
    return result;
}

void print_res_dj(Node** result, int amount){
    printf("Здравствуйте, ваш %d путь\n", amount);
    for (int i=amount-1;i>=0;i--){
        if (i != amount-1) printf (" -> ");
        printf("\"%s\"", result[i]->name);
    }
    printf("\n");
}

int max(int a, int b){
    if (a > b) return a;
    return b;
}

int find_in_elems(Node** mat, int amount, char* name){
    int index = 0;
    while (strcmp(mat[index]->name, name) != 0) index++;
    return index;
}

Node* floyd_var(Graph* graph, char* human, int* loop_check){
    *loop_check = 0;
    if (graph == NULL){
        return NULL;
    }
    Node* first = find(graph, human);
    if (first == NULL) return NULL;
    int amount = 0, iter = 0;
    for (int i=0;i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if ((elem != NULL) && (elem->state == 1))
            amount++;
    }
    int **mat = calloc(amount, sizeof(int*));
    Node** elems = calloc(amount, sizeof(Node*));
    Node* elem;
    for (int i=0;i<graph->msize;i++){
        elem = graph->nodes[i];
        if ((elem != NULL) && (elem->state == 1)){
            mat[iter] = calloc(amount, sizeof(int));
            for (int j=0; j<amount;j++){
                mat[iter][j] = MINF;
            }
            elems[iter] = elem;
            iter++;
        }
    }
    int index;
    for (int i=0; i<amount; i++){
        mat[i][i] = 0;
        elem = elems[i];
        Edge* edge = elem->edges;
        while (edge){
            index = find_in_elems(elems, amount, edge->dest);
            mat[i][index] = edge->rel;
            edge = edge->next;
        }
    }
    for (int v=0; v<amount; v++){
        for (int a=0; a<amount; a++){
            for (int b=0; b<amount; b++){
                if ((mat[a][v] != MINF) && (mat[v][b] != MINF))
                    mat[a][b] = max(mat[a][v] + mat[v][b], mat[a][b]);
            }
        }
    }
    Node* result = NULL;
    for (int i=0;i<amount;i++){
        if (mat[i][i] != 0){
            *loop_check = 1;
        }
    }
    if (!(*loop_check)){
        int maxval = MINF;
        *loop_check = 2;
        index = find_in_elems(elems, amount, human);
        for (int i=0;i<amount;i++){
            if ((mat[index][i] > maxval) && (index != i)){
                maxval = mat[index][i];
                result = elems[i];
            }
        }
    }
    for (int i=0; i<amount; i++){
        free(mat[i]);
    }
    free(mat);
    free(elems);
    return result;
}
