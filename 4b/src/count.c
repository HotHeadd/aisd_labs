#include "../library/src/tree.h"
#include "../library/src/tree_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int eXXit(int mistake, Tree* tree, char* filename){
    printf("Выхожу...\n");
    free_tree(tree, 1);
    free(filename);
    return mistake;
}

int main(){
    Tree* tree = get_tree();
    char* filename = g_readline("Введите имя файла, из которого взять текст: ");
    if (filename == NULL) return eXXit(GOOD, tree, filename);
    FILE* input = fopen(filename, "r");
    if (input == NULL){
        printf("Ошибка файла\n");
        return eXXit(GOOD, tree, filename);;
    }
    // task here
    fclose(input);
    free(filename);
    filename = g_readline("Введите имя файла, в который вывести результат работы: ");
    if (filename == NULL) return eXXit(GOOD, tree, filename);
    FILE* output = fopen(filename, "w");
    if (output == NULL){
        printf("Ошибка файла\n");
        return eXXit(GOOD, tree, filename);;
    }
    // output res here
    fclose(output);
    return eXXit(GOOD, tree, filename);
}