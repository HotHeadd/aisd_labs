#pragma once

#include "gr_main.h"

Graph* findwide(Graph* graph, char* human, int handshakes);
Node** dijkstra(Graph* graph, char* first, char* second);
Node** floyd_var(Graph* graph, char* human);