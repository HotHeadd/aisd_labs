#include "gr_io.h"
#include "basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY "&-&-&"

void gr_out_list(const graph_t* graph){
    if (graph == NULL){
        printf("Графа нет\n");
        return;
    }
    printf("Здравствуйте, ваш граф:\n");
    for (int i=0; i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if (elem != NULL){
            printf("\"%s\"", elem->name);
            Edge* edge = elem->edges;
            while (edge != NULL){
                printf(" -> (\"%s\", %d)", edge->dest, edge->rel);
                edge = edge->next;
            }
            printf("\n");
        }
        else printf("[NULL]\n");
    }
}

void gr_out_gv(const graph_t* graph){
    return;
}

void output_edges(FILE* output, Node* elem){
    if (elem->edges == NULL) return;
    int amount = 1;
    Edge* edge=elem->edges;
    while ((edge = edge->next) != NULL) amount++;
    fprintf(output, "%s\n", elem->name);
    fprintf(output, "%d\n", amount);
    edge = elem->edges;
    while (edge != NULL){
        if (strlen(edge->dest) == 0)
            fprintf(output, "%s\n", EMPTY);
        else fprintf(output, "%s\n", edge->dest);
        fprintf(output, "%d\n", edge->rel);
        edge = edge->next;
    }
}

int gr_txt_out(const graph_t* graph, const char* filename){
    FILE* output = fopen(filename, "w");
    if (output == NULL) return FILE_ERROR;
    for (int i=0; i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if ((elem != NULL) && (elem->state != -1))
            if (strlen(elem->name) == 0){
                fprintf(output, "%s\n", EMPTY);
            }
            else fprintf(output, "%s\n", elem->name);
    }
    fprintf(output, "\n");
    for (int i=0; i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if ((elem != NULL) && (elem->state != -1))
            output_edges(output, elem);
    }
    fclose(output);
    return GOOD;
}

int gr_txt_in(graph_t** graph, const char* filename){
    FILE* input = fopen(filename, "r");
    if (input == NULL) return FILE_ERROR;
    free_graph(*graph);
    *graph = get_graph(SIZE);
    char* name, * fam;
    int amount, relate;
    while (((name = file_readline(input)) != NULL) && (strlen(name) != 0)){
        if (strcmp(name, EMPTY) == 0){
            free(name);
            name = calloc(1, sizeof(char));
        }
        gr_add_node(*graph, name);
        free(name);
    }
    free(name);
    while ((name = file_readline(input)) != NULL){
        if (strcmp(name, EMPTY) == 0){
            free(name);
            name = calloc(1, sizeof(char));
        }
        fscanf(input, "%d%*c", &amount);
        for (int i=0; i<amount;i++){
            fam = file_readline(input);
            if (strcmp(fam, EMPTY) == 0){
                free(fam);
                fam = calloc(1, sizeof(char));
            }
            fscanf(input, "%d%*c", &relate);
            gr_add_edge(*graph, name, fam, relate);
            free(fam);
        }
        free(name);
    }
    free(name);
    fclose(input);
    return GOOD;
}
