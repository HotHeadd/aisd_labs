#include <stdio.h>
#include "../library/src/basic.h"
#include "../library/src/gr_main.h"
#include "../library/src/gr_algo.h"
#include "../library/src/gr_io.h"
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

void dop_print(Graph* graph, Node** res2, int d_am, char* person){
    if (graph != NULL){
        FILE* output = fopen("testres/wide.txt", "w");
        fprintf(output, "\"%s\"\n", person);
        gr_out_list(graph, "HEHEH\n", output);
        fclose(output);
    }
    else{
        FILE* output = fopen("testres/dijkstra.txt", "w");
        print_res_dj(res2, d_am, output);
        fclose(output);
    }
}

int main(){
    int amount = 1000;
    int connections = 1150;
    int seed = 1716366288;
    srand(seed);
    FILE* source = fopen("src/bbn.txt", "r");
    if (source == NULL) return 0;
    Graph* graph = get_graph(1500);
    char** names = calloc(amount, sizeof(char*));
    for (int i=0; i<amount;i++){
        char* name = file_readline(source);
        gr_add_node(graph, name);
        names[i] = name;
    }
    fclose(source);
    for (int i=0; i<connections; i++){
        int index1 = i%amount, index2 = rand()%amount;
        gr_add_edge(graph, names[index1], names[index2], rand()%21-10);
    }
    mkdir("testres", 0700);
    mkdir("testpics", 0700);
    for (int i = 0; i<3; i++){
        if (i == 0){
            char* person = "Everly";
            Graph* res1 = findwide(graph, person, 10);
            gr_out_gv(graph, "testpics/wide.svg", res1, person, NULL, 0, NULL, NULL);
            dop_print(res1, NULL, 0, person);
            free_graph(res1);
        }
        if (i == 1){
            int d_am;
            Node** res2 = dijkstra(graph, "Delaney", "Margaret", &d_am);
            gr_out_gv(graph, "testpics/dijkstra.svg", NULL, NULL, res2, d_am, NULL, NULL);
            dop_print(NULL, res2, d_am, NULL);
            free(res2);
        }
        if (i == 2){
            int loop_check;
            Node* res3 = floyd_var(graph, "Aliana", &loop_check);
            gr_out_gv(graph, "testpics/floyd.svg", NULL, NULL, NULL, 0, res3, "Aliana");
            // Алиана слева посередине, Дрю справа повыше
            printf("%d\n", loop_check);
        }
    }
    for (int i=0; i<amount;i++){
        free(names[i]);
    }
    free(names);
    free_graph(graph);
    return 0;
}