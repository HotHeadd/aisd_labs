#pragma once

#define SIZE 5 //257

#define END_INPUT -1
#define GOOD 0
#define ELEM_EXIST 1
#define COLLISION 2
#define ELEM_NOT_FOUND 3
#define FILE_ERROR 4
#define FORMAT_ERROR 5
#define NO_TREE 6
#define MULTIPLE_DATA 7
#define LAST_ELEMENT 8

typedef struct Node{
    char* name;
    struct Edge* edges;
    short state;
} Node;

typedef struct Edge{
    char* dest;
    int rel;
    struct Edge* next;
} Edge;

typedef struct Graph{
    int csize;
    int msize;
    Node** nodes;
} Graph;

Graph* get_graph(int size);
void free_graph(Graph* graph);

int gr_add_node(Graph* graph, char* human);
int gr_add_edge(Graph* graph, char* human, char* fam, int rel);
int gr_del_node(Graph *graph, char* human);
int gr_del_edge(Graph *graph, char* humanm, char* fam);
int gr_change_node(Graph* graph, char* human, char* neww);
int gr_change_edge(Graph* graph, char* human, char* neww, int rel);
