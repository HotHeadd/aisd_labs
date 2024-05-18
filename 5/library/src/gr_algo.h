#pragma once

#include "gr_main.h"

Node** dijkstra(graph_t* graph, char* first, char* second);
Node** findwide(graph_t* graph, char* human, int handshakes);
Node** floyd_var(graph_t* graph, char* human);