#pragma once

#include "gr_main.h"

void gr_out_list(const Graph* graph, const char* prompt);
void gr_out_gv(const Graph* graph);

int gr_txt_out(const Graph* graph, const char* filename);
int gr_txt_in(Graph** graph, const char* filename);