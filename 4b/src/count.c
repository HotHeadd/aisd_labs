#include "../library/src/tree.h"
#include "../library/src/tree_io.h"
#include "../library/src/basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dop.h"

int main(){
    Tree* tree = NULL;
    char* word = NULL, *filename = NULL;
    while (1){
        filename = g_readline("Введите имя файла (нажмите enter если брать из прошлого): ");
        if (filename == NULL) return eXXit(GOOD, tree, filename, word);
        word = g_readline("Введите искомое слово: ");
        if (word == NULL) return eXXit(GOOD, tree, filename, word);
        unsigned* vector;
        int amount = extra(filename, word, &vector, &tree);
        if (amount == -1){
            printf("Ошибка файла\n");
        }
        if (amount == -2){
            printf("Такого слова нет в файле!\n");
        }
        if (amount == -3){
            printf("Нет предыдущего файла\n");
        }
        if (amount > 0){
            print_vec(vector, amount);
            free(vector);
        }
        free(filename);
        filename = NULL;
        free(word);
        word = NULL;
    }
}