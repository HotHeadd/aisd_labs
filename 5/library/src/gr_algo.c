#include "gr_main.h"
#include "gr_algo.h"
#include <stdlib.h>
#include "structs.h"
#include <stdio.h>

#define INF 100000000
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
        *amount++;
        elem = elem->pred;
    }
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

Node** floyd_var(Graph* graph, char* human){
    return NULL;
}
