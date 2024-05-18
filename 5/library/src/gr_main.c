#include "gr_main.h"
#include <stdlib.h>
#include <stdio.h>
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
    Node* elem = graph->nodes[index];
    if (elem != NULL){
        while ((elem != NULL) && (elem->state == 1)){
            if (strcmp(elem->name, human) == 0)
                return ELEM_EXIST;
            index = (index + 1)%graph->msize;
            elem = graph->nodes[index];
        }
        graph->nodes[index]= calloc(1, sizeof(Node));
        graph->nodes[index]->name = strdup(human);
        graph->nodes[index]->state = 1;
        return COLLISION;
    }
    graph->nodes[index] = calloc(1, sizeof(Node));
    graph->nodes[index]->name = strdup(human);
    graph->nodes[index]->state = 1; 
    graph->csize++;
    // if (graph->csize == graph->msize) //0,75 coef
    //     extend(graph);
    return GOOD;
}

Node* find(graph_t* graph, char* human){
    int index = hash(graph, human);
    int start = index;
    Node* elem = graph->nodes[index];
    while (elem != NULL){
        if ((elem->state == 1) && (strcmp(elem->name, human) == 0)){
            return elem;
        }
        index = (index + 1)%graph->msize;
        if (index == start) return NULL;
        elem = graph->nodes[index];
    }
    return NULL;
}

int gr_add_edge(graph_t* graph, char* human, char* fam, int rel){
    Node* elem = find(graph, human);
    Node* check = find(graph, fam);
    if ((elem == NULL) || (check == NULL)) return ELEM_NOT_FOUND;
    Edge* neww = calloc(1, sizeof(Edge));
    neww->rel = rel;
    neww->dest = strdup(fam);
    neww->next = elem->edges;
    elem->edges = neww;
    return GOOD;
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
