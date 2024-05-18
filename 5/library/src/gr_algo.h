#pragma once

#include "gr_main.h"

Node** dijkstra(Graph* graph, char* first, char* second);
Node** findwide(Graph* graph, char* human, int handshakes);
Node** floyd_var(Graph* graph, char* human);