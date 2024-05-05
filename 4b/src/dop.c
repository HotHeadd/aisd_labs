#include "dop.h"
#include "../library/src/tree.h"
#include "../library/src/basic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SEPS " ,;.:!?)(_=+-@#$%^&*<>/|\\{}[]\"\t"

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

int hash(char* word){
    int hash = 0;
    for (int i=0; i<strlen(word); i++){
        hash += 37*((char)word[i]) + word[i]%37;
    }
    return hash;
}

int extra(char* filename, char* looking, unsigned** vector, Tree** ptr){
    static int prev = -1;
    static Tree* tree = NULL;
    if ((strlen(filename) != 0) && (prev != hash(filename))){
        FILE* input = fopen(filename, "r");
        if (input == NULL){
            return -1;
        }
        free_tree(*ptr, 1);
        tree = get_tree();
        prev = hash(filename);
        *ptr = tree;
        char* string, *word;
        int num = 1;
        int res;
        while ((string = file_readline(input)) != NULL){
            word = strtok(string, SEPS);
            if (word == NULL){
                num++;
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
    }
    if (tree == NULL){
        return -3;
    }
    int found;
    Node* elem = find(tree, looking, &found);
    if (!found){
        return -2;
    }
    return form_vector(elem, vector);
}