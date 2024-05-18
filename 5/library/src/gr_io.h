#pragma once

#include "gr_main.h"

void gr_out_list(const graph_t* graph);
void gr_out_gv(const graph_t* graph);

int gr_txt_out(const graph_t* graph, const char* filename);
int gr_txt_in(const graph_t* graph, const char* filename);