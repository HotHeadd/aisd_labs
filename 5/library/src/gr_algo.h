#pragma once

#include "gr_main.h"
#include <stdio.h>

Graph* findwide(Graph* graph, char* human, int handshakes);
Node** dijkstra(Graph* graph, char* first, char* second, int* amount);
Node* floyd_var(Graph* graph, char* human, int* loop_check);

void print_res_dj(Node** result, int amount, FILE* flow);