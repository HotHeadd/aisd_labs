#pragma once

#include "gr_main.h"
#include <stdio.h>

void gr_out_list(const Graph* graph, const char* prompt, FILE* flow);
void gr_out_gv(const Graph* graph, const char*, \
    Graph* graphres, char* person, Node** res2, int a, Node* res3, char* source);

int gr_txt_out(const Graph* graph, const char* filename);
int gr_txt_in(Graph** graph, const char* filename);