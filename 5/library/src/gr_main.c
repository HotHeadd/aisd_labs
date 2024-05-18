#include "gr_main.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

int hash(graph_t* graph, char* string){
    int hash = 0;
    for (int i=0; i<strlen(string); i++){
        hash += string[i]*37 + string[i]%37;
    }
    return hash%(graph->msize);
}

graph_t* get_graph(int size){
    graph_t* graph = calloc(1, sizeof(graph_t));
    graph->msize = size;
    graph->csize = 0;
    graph->nodes = calloc(size, sizeof(Node*));
    return graph;
}
void free_graph(graph_t* graph){
    if (graph == NULL) return;
    for (int i=0; i<graph->msize; i++){
        Node* elem = graph->nodes[i];
        if (elem == NULL) continue;
        free(elem->name);
        Edge* edge = elem->edges;
        Edge* prev = edge;
        while (edge != NULL){
            free(edge->dest);
            edge = edge->next;
            free(prev);
            prev = edge;
        }
        free(elem);
    }
    free(graph->nodes);
    free(graph);
    return;
}

int is_prime(int num){
    for (int i=2; i<(int)(sqrt(num))+1;i++){
        if ((num%i) == 0) return 0;
    }
    return 1;
}

unsigned simple(unsigned size){
    unsigned resault = size;
    while (is_prime(++resault) == 0);
    return resault;
}

graph_t* extend(graph_t* graph){
    graph_t* new_graph = get_graph(simple(graph->msize*2));
    for (int i=0; i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if (elem == NULL) continue;
        ///
    }
    // free_graph(graph);
    return new_graph;
}

int gr_add_node(graph_t* graph, char* human){
    int index = hash(graph, human);
    if (graph->nodes[index] != NULL) return ELEM_EXIST;
    graph->nodes[index] = calloc(1, sizeof(Node));
    graph->nodes[index]->name = strdup(human);
    return GOOD;
}

int gr_add_edge(graph_t* graph, char* human, char* fam, int rel){
    return 0;
}

int gr_del_node(graph_t *graph, char* human){
    return 0;
}

int gr_del_edge(graph_t *graph, char* humanm, char* fam){
    return 0;
}

int gr_change_node(graph_t* graph, char* human, char* neww){
    return 0;
}

int gr_change_edge(graph_t* graph, char* human, char* neww, int rel){
    return 0;
}
