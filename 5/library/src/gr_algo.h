#pragma once

#include "gr_main.h"

Graph* findwide(Graph* graph, char* human, int handshakes);
Node** dijkstra(Graph* graph, char* first, char* second, int* amount);
Node** floyd_var(Graph* graph, char* human);

void print_res_dj(Node** result, int amount);