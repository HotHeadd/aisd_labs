#include "gr_io.h"
#include <stdio.h>

void gr_out_list(const graph_t* graph){
    if (graph == NULL){
        printf("Графа нет\n");
        return;
    }
    printf("Здравствуйте, ваш граф:\n");
    for (int i=0; i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if (elem != NULL){
            printf("[%s]", elem->name);
            Edge* edge = elem->edges;
            while (edge != NULL){
                printf(" -> [%s, %d]", edge->dest, edge->rel);
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

int gr_txt_out(const graph_t* graph, const char* filename){
    return 0;
}

int gr_txt_in(const graph_t* graph, const char* filename){
    return 0;
}
