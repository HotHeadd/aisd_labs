#include <stdio.h>
#include <stdlib.h>
#include "../library/src/basic.h"
#include "../library/src/gr_main.h"
#include "../library/src/gr_algo.h"
#include "../library/src/gr_io.h"

int exxit(Graph* graph, char* human, char* fam, char* filename){
    printf("Выхожу...\n");
    free_graph(graph);
    free(human);
    free(fam);
    free(filename);
    return 0;
}

void menus(){
    printf("\nВыберете опцию\n");
    printf("(1) Вывести граф (в консоль)\n");
    printf("(2) Вывести граф (графический)\n");
    printf("(3) Добавить человека (с уникальным именем)\n");
    printf("(4) Добавить новую оценку\n");
    printf("(5) Удалить человека\n");
    printf("(6) Удалить оценку\n");
    printf("(7) Изменить имя человека (оно должно быть уникальным)\n");
    printf("(8) Изменить оценку\n");
    printf("(o) Вывод в текстовый файл\n");
    printf("(i) Ввод из текстового файла\n");
    printf("(t) (Поиск в ширину) Определение круга знакомств через рукопожатия\n");
    printf("(f) (Алгоритм Дейкстры) Поиск пути между людьми по положительным отношениям\n");
    printf("(s) (Алгоритм Флойда-Варшалла) ...\n");
    printf("--> ");
}

char* ask_name(char* prompt){
    char* key;
    key = g_readline(prompt);
    if (key == NULL) return NULL;
    return key;
}

int main(){
    char choice;
    Graph* graph = get_graph(SIZE);
    char *human = NULL, *fam = NULL, *newname = NULL, *filename = NULL;
    int res, relates, handshakes;
    res = gr_txt_in(&graph, "test");
    menus();
    while ((choice = better_getchar()) != EOF){
        switch(choice){
            case '1':
                gr_out_list(graph);
                break;
            case '2':
                gr_out_gv(graph);
                break;
            case '3':
                free(human);
                human = ask_name("Введите имя: ");
                if (human == NULL) 
                    return exxit(graph, human, fam, filename);
                res = gr_add_node(graph, human);
                if (res == GOOD) printf("Человек добавлен в граф\n");
                if (res == ELEM_EXIST) printf("Человек с таким именем уже есть в графе\n");
                if (res == COLLISION) printf("Колллизия!\n");
                break;
            case '4':
                free(human);
                human = ask_name("Введите имя человека: ");
                if (human == NULL) 
                    return exxit(graph, human, fam, filename);
                free(fam);
                fam = ask_name("Введите имя его знакомого: ");
                if (fam == NULL) 
                    return exxit(graph, human, fam, filename);
                res = custom_int_input("Введите оценку (от -10 до 10): ", &relates, pmten);
                if (res == END_INPUT) 
                    return exxit(graph, human, fam, filename);
                res = gr_add_edge(graph, human, fam, relates);
                if (res == GOOD) printf("Оценка добавлена\n");
                if (res == ELEM_NOT_FOUND) printf("Одного из людей нет в графе\n");
                break;
            case '5':
                free(human);
                human = ask_name("Введите имя человека: ");
                if (human == NULL) 
                    return exxit(graph, human, fam, filename);
                res = gr_del_node(graph, human);
                if (res == GOOD) printf("Человек ликвидирован\n"); 
                if (res == ELEM_NOT_FOUND) printf("Человека нет в дереве\n");
                break;
            case '6':
                free(human);
                human = ask_name("Введите имя человека: ");
                if (human == NULL) 
                    return exxit(graph, human, fam, filename);
                free(fam);
                fam = ask_name("Введите имя его знакомого: ");
                if (fam == NULL) 
                    return exxit(graph, human, fam, filename);
                res = gr_del_edge(graph, human, fam);
                if (res == GOOD) printf("Связь удалена\n"); 
                if (res == ELEM_NOT_FOUND) printf("Одного из людей нет в дереве\n"); 
                break;
            case '7':
                free(human);
                human = ask_name("Введите имя человека: ");
                if (human == NULL) 
                    return exxit(graph, human, fam, filename);
                free(newname);
                newname = ask_name("Введите имя человека: ");
                if (newname == NULL) 
                    return exxit(graph, human, fam, filename);
                res = gr_change_node(graph, human, newname);
                //res dev
                break;
            case '8':
                free(human);
                human = ask_name("Введите имя человека: ");
                if (human == NULL) 
                    return exxit(graph, human, fam, filename);
                free(fam);
                fam = ask_name("Введите имя его знакомого: ");
                if (fam == NULL) 
                    return exxit(graph, human, fam, filename);
                res = custom_int_input("Введите оценку (от -10 до 10): ", &relates, pmten);
                if (res == END_INPUT) 
                    return exxit(graph, human, fam, filename);
                res = gr_change_edge(graph, human, fam, relates);
                //res dev
                break;
            case 'o':
                free(filename);
                filename = g_readline("ВЫВОД Введите имя файла: ");
                if (filename == NULL) 
                    return exxit(graph, human, fam, filename);
                res = gr_txt_out(graph, filename);
                if (res == GOOD) printf("Граф записан в файл %s\n", filename);
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                break;
            case 'i':
                free(filename);
                filename = g_readline("ВВОД Введите имя файла: ");
                if (filename == NULL) 
                    return exxit(graph, human, fam, filename);
                res = gr_txt_in(&graph, filename);
                if (res == GOOD) printf("Граф считан из файла %s\n", filename);
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                break;
            case 't':
                free(human);
                human = ask_name("Введите имя человека: ");
                if (human == NULL) 
                    return exxit(graph, human, fam, filename);
                res = custom_int_input("Введите рукопожатия: ", &handshakes, pmten);
                if (res == END_INPUT) 
                    return exxit(graph, human, fam, filename);
                findwide(graph, human, handshakes);
                // process return type
                // print findwide res
                // res dev
                break;
            case 'f':
                free(human);
                human = ask_name("Введите имя первого: ");
                if (human == NULL) 
                    return exxit(graph, human, fam, filename);
                free(fam);
                fam = ask_name("Введите имя второго: ");
                if (fam == NULL) 
                    return exxit(graph, human, fam, filename);
                dijkstra(graph, human, fam); 
                // process return type
                // print dijkstra res
                // res dev
                break;
            case 's':
                free(human);
                human = ask_name("Введите имя человека: ");
                if (human == NULL) 
                    return exxit(graph, human, fam, filename);
                floyd_var(graph, human);
                // process return type
                // print findwide res
                // res dev
                break;
            default:
                printf("Нет такой опции в меню!\n");
        }
        menus();
    }
    return exxit(graph, human, fam, filename);
}