#include <stdio.h>
#include "../library/src/basic.h"
#include "../library/src/gr_main.h"
#include "../library/src/gr_algo.h"
#include "../library/src/gr_io.h"
#include <time.h>
#include <stdlib.h>

int main(){
    srand(time(NULL));
    FILE* source = fopen("src/bbn.txt", "r");
    if (source == NULL) return 0;
    Graph* graph = get_graph(1500);
    char* names[1000];
    for (int i=0; i<1000;i++){
        char* name = file_readline(source);
        gr_add_node(graph, name);
        names[i] = name;
    }
    fclose(source);
    int connections = 1200;
    for (int i=0; i<connections; i++){
        int index1 = i%1000, index2 = rand()%1000;
        gr_add_edge(graph, names[index1], names[index2], rand()%20-10);
    }
    gr_out_gv(graph); // их библиотечная функция не рендерит граф при таком большом кол-ве связей
    for (int i=0; i<1000;i++){
        free(names[i]);
    }
    free_graph(graph);
    return 0;
}