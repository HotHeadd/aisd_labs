#include "gr_main.h"
#include "gr_algo.h"
#include <stdlib.h>
#include "queue.h"

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


Node** dijkstra(Graph* graph, char* first, char* second){
    return NULL;
}

Node** floyd_var(Graph* graph, char* human){
    return NULL;
}
