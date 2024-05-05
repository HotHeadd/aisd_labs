#include "../library/src/tree.h"
#include "../library/src/tree_io.h"
#include "../library/src/basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SEPS " ,;.:!?)(_=+-@#$%^&*<>/|\\{}[]\"\t"

int eXXit(int mistake, Tree* tree, char* filename, char* word){
    printf("Выхожу...\n");
    free_tree(tree, 1);
    free(filename);
    free(word);
    return mistake;
}

char* lower(char* word){
    for (int i=0; i<strlen(word); i++){
        if (isupper(word[i])){
            word[i] = word[i] + 'a' - 'A';
        }
    }
    return word;
}

int form_vector(Node* elem, unsigned** vector){
    int prev = -1, amount = 0;
    info_t* info = elem->info;
    while (info != NULL){
        if (info->value != prev){
            prev = info->value;
            amount++;
        }
        info = info->next;
    }
    *vector = calloc(amount, sizeof(unsigned));
    info = elem->info;
    amount = 0;
    prev = -1;
    while (info != NULL){
        if (info->value != prev){
            prev = info->value;
            (*vector)[amount] = info->value;
            amount++;
        }
        info = info->next;
    }
    return amount;
}

void print_vec(unsigned* vector, int amount){
    printf("Номера строк: [");
    for (int i=0; i<amount; i++){
        if (i != 0) printf(", ");
        printf("%d", vector[i]);
    }
    printf("]\n");
}

int main(){
    Tree* tree = get_tree();
    char* string, *word = NULL;
    char* filename = g_readline("Введите имя файла, из которого взять текст: ");
    if (filename == NULL) return eXXit(GOOD, tree, filename, word);
    FILE* input = fopen(filename, "r");
    if (input == NULL){
        printf("Ошибка файла\n");
        return eXXit(GOOD, tree, filename, word);;
    }
    int num = 1;
    int res;
    while ((string = file_readline(input)) != NULL){
        word = strtok(string, SEPS);
        if (word == NULL){
            free(string);
            continue;
        }
        char *key = strdup(lower(word));
        if ((res = insert(tree, key, num)) == KEY_EXIST){
            free(key);
        }
        while ((word = strtok(NULL, SEPS)) != NULL){
            key = strdup(lower(word));
            if ((res = insert(tree, key, num)) == KEY_EXIST){
                free(key);
            }
        }
        num++;
        free(string);
    }
    fclose(input);
    while ((word = g_readline("Введите искомое слово: ")) != NULL){
        int found;
        Node* elem = find(tree, word, &found);
        if (!found){
            free(word);
            printf("Такое слово не встречалось в файле!\n");
            continue;
        }
        unsigned* vector;
        int amount = form_vector(elem, &vector);
        print_vec(vector, amount);
        free(vector);
        free(word);
    }
    return eXXit(GOOD, tree, filename, word);
}