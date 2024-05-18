#include "gr_io.h"
#include "gr_main.h"
#include "basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/gvc.h>
#include <unistd.h>

#define EMPTY "&-&-&"

void gr_out_list(const Graph* graph){
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

void output_edges(FILE* output, Node* elem){
    if (elem->edges == NULL) return;
    int amount = 1;
    Edge* edge=elem->edges;
    while ((edge = edge->next) != NULL) amount++;
    if (strlen(elem->name) == 0){
        fprintf(output, "%s\n", EMPTY);
    }
    else fprintf(output, "%s\n", elem->name);
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

int gr_txt_out(const Graph* graph, const char* filename){
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

int gr_txt_in(Graph** graph, const char* filename){
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
        // gr_out_list(*graph);
        // sleep(1);
    }
    free(name);
    fclose(input);
    return GOOD;
}

void fill_agraph(Agraph_t* agv, const Graph* graph){
    Agnode_t *first, *second;
    Agedge_t *Dedge;
    for (int i=0; i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if ((elem != NULL) && (elem->state != -1))
            if (strlen(elem->name) == 0){
                agnode(agv, "", 1);
            }
            else agnode(agv, elem->name, 1);
    }
    for (int i=0; i<graph->msize;i++){
        Node* elem = graph->nodes[i];
        if ((elem != NULL) && (elem->state != -1)){
            if (elem->edges == NULL) continue;
            Edge* edge=elem->edges;
            while (edge != NULL){
                first = agnode(agv, elem->name, 1);
                if (strlen(edge->dest) == 0)
                    second = agnode(agv, "", 1);
                else second = agnode(agv, edge->dest, 1);
                Dedge = agedge(agv, first, second, 0, 1);
                char lab[4] = {'\0'};
                sprintf(lab, "%d", edge->rel);
                agsafeset(Dedge, "label", lab, "");
                edge = edge->next;
            }
        }
    }
}

void gr_out_gv(const Graph* graph){
    if (graph == NULL) return;
    GVC_t *gvc = gvContext();
    Agraph_t *agr = agopen("graph", Agdirected, 0);
    fill_agraph(agr, graph);
    gvLayout(gvc, agr, "dot");
    FILE* out = fopen("image.svg", "w");
    gvRender(gvc, agr, "svg", out); 
    fclose(out);
    system("nomacs image.svg -m frameless"); // просмотр изображения
    remove("image.svg");
    // gvFreeLayout(gvc, agr);
    agclose(agr);
    // gvFreeContext(gvc);
}
