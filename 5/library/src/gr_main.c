#include "gr_main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int hash(int size, char* string){
    int hash = 0;
    for (int i=0; i<strlen(string); i++){
        hash += string[i]*37 + string[i]%37;
    }
    return hash%size;
}

Graph* get_graph(int size){
    Graph* graph = calloc(1, sizeof(Graph));
    graph->msize = size;
    graph->csize = 0;
    graph->nodes = calloc(size, sizeof(Node*));
    return graph;
}

void free_edges(Node* elem){
    Edge* edge = elem->edges;
    Edge* prev = edge;
    while (edge != NULL){
        free(edge->dest);
        edge = edge->next;
        free(prev);
        prev = edge;
    }
}

void free_graph(Graph* graph){
    if (graph == NULL) return;
    for (int i=0; i<graph->msize; i++){
        Node* elem = graph->nodes[i];
        if (elem == NULL) continue;
        free(elem->name);
        free_edges(elem);
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

void extend(Graph* graph){
    int newsize = simple(graph->msize*2);
    Node** newnodes = calloc(newsize, sizeof(Node*));
    for (int i=0; i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if (elem == NULL) continue;
        int index = hash(newsize, elem->name);
        Node* nelem = newnodes[index];
        while (nelem != NULL){
            index = (index + 1)%newsize;
            nelem = newnodes[index];
        }
        newnodes[index] = elem;
    }
    free(graph->nodes);
    graph->nodes = newnodes;
    graph->msize = newsize;
}

int gr_add_node(Graph* graph, char* human){
    int index = hash(graph->msize, human);
    Node* elem = graph->nodes[index];
    int out = GOOD;
    if (elem != NULL){
        while ((elem != NULL) && (elem->state == 1)){
            if (strcmp(elem->name, human) == 0)
                return ELEM_EXIST;
            index = (index + 1)%graph->msize;
            elem = graph->nodes[index];
            out =  COLLISION;
        }
    }
    if (graph->nodes[index] == NULL)
        graph->nodes[index] = calloc(1, sizeof(Node));
    if (graph->nodes[index] != NULL)
        free(graph->nodes[index]->name);
    graph->nodes[index]->name = strdup(human);
    graph->nodes[index]->edges = NULL; 
    graph->nodes[index]->state = 1; 
    graph->csize++;
    if (graph->csize >= ((double)(graph->msize))*(0.75)){
        extend(graph);
    }
    return out;
}

Node* find(Graph* graph, char* human){
    int index = hash(graph->msize, human);
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

int gr_add_edge(Graph* graph, char* human, char* fam, int rel){
    Node* elem = find(graph, human);
    Node* check = find(graph, fam);
    if ((elem == NULL) || (check == NULL)) return ELEM_NOT_FOUND;
    gr_del_edge(graph, human, fam);
    Edge* neww = calloc(1, sizeof(Edge));
    neww->rel = rel;
    neww->dest = strdup(fam);
    neww->next = elem->edges;
    elem->edges = neww;
    return GOOD;
}

int gr_del_node(Graph *graph, char* human){
    Node* elem = find(graph, human);
    if (elem == NULL) return ELEM_NOT_FOUND;
    elem->state = -1;
    free_edges(elem);
    elem->edges = NULL;
    for (int i=0; i<graph->msize;i++){
        Node* iter = graph->nodes[i];
        if ((iter == NULL) || (iter->state == -1)) continue;
        gr_del_edge(graph, iter->name, human);
    }
    graph->csize--;
    return GOOD;
}

int gr_del_edge(Graph *graph, char* human, char* fam){
    Node* elem = find(graph, human);
    if (elem == NULL) return ELEM_NOT_FOUND;
    Edge* edge = elem->edges;
    Edge* prev = NULL;
    if (edge == NULL) return ELEM_NOT_FOUND;
    while (edge != NULL){
        if (strcmp(edge->dest, fam) == 0){
            if (prev == NULL){
                elem->edges = edge->next;
            }
            else{
                prev->next = edge->next;
            }
            free(edge->dest);
            free(edge);
            return GOOD;
        }
        prev = edge;
        edge = edge->next;
    }
    return ELEM_NOT_FOUND;
}

int gr_change_node(Graph* graph, char* human, char* neww){
    Node* elem = find(graph, human);
    if (elem == NULL) return ELEM_NOT_FOUND;
    int index = hash(graph->msize, elem->name);
    while (strcmp(graph->nodes[index]->name, human) != 0){
        index = (index + 1)%graph->msize;
    }
    graph->nodes[index] = NULL;
    free(elem->name);
    elem->name = neww;
    index = hash(graph->msize, neww);
    while ((graph->nodes[index] != NULL) || (graph->nodes[index]->state != -1)){
        index = (index + 1)%graph->msize;
    }
    graph->nodes[index] = elem;
    return GOOD;
}

int gr_change_edge(Graph* graph, char* human, char* fam, int new){
    Node* elem = find(graph, human);
    if (elem == NULL) return ELEM_NOT_FOUND;
    Edge* edge = elem->edges;
    Edge* prev = NULL;
    if (edge == NULL) return ELEM_NOT_FOUND;
     while (edge != NULL){
        if (strcmp(edge->dest, fam) == 0){
            edge->rel = new;
            return GOOD;
        }
        prev = edge;
        edge = edge->next;
    }
    return ELEM_NOT_FOUND;
}
