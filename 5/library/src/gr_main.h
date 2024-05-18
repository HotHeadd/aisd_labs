#pragma once

#define SIZE 257

#define END_INPUT -1
#define GOOD 0
#define ELEM_EXIST 1
#define ROOT_CREATED 2
#define ELEM_NOT_FOUND 3
#define FILE_ERROR 4
#define FORMAT_ERROR 5
#define NO_TREE 6
#define MULTIPLE_DATA 7
#define LAST_ELEMENT 8



typedef struct Node{
    char* name;
    struct Edge* edges;
} Node;

typedef struct Edge{
    char* dest;
    int rel;
    struct Edge* next;
} Edge;

typedef struct graph_t{
    int csize;
    int msize;
    Node** nodes;
} graph_t;

graph_t* get_graph(int size);
void free_graph(graph_t* graph);

int gr_add_node(graph_t* graph, char* human);
int gr_add_edge(graph_t* graph, char* human, char* fam, int rel);
int gr_del_node(graph_t *graph, char* human);
int gr_del_edge(graph_t *graph, char* humanm, char* fam);
int gr_change_node(graph_t* graph, char* human, char* neww);
int gr_change_edge(graph_t* graph, char* human, char* neww, int rel);
