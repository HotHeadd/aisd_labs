#include "../library/src/tree.h"
#include "../library/src/tree_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <ctype.h>

int eXXit(int mistake, Node* root, char* filename){
    printf("Выхожу...\n");
    free_tree(root);
    free(filename);
    return mistake;
}

char* add_to_word(char* word, char letter){
    word = realloc(word, (strlen(word)+2)*sizeof(char));
    int len = strlen(word);
    word[len] = letter;
    word[len+1] = '\0';
    return word;
}

unsigned get_info(Node* elem){
    return elem->info->value;
}

int main(){
    Node* root = NULL;
    char* filename = readline("Введите имя файла, из которого взять текст: ");
    if (filename == NULL) return eXXit(GOOD, root, filename);
    FILE* input = fopen(filename, "r");
    if (input == NULL){
        printf("Ошибка файла\n");
        return eXXit(GOOD, root, filename);;
    }
    Node* elem;
    char letter;
    char* word = calloc(1, sizeof(char));
    int res;
    unsigned info = 1;
    do{
        letter = getc(input);
        if (isalpha(letter)){
            if (isupper(letter))
                letter += 'a' - 'A';
            word = add_to_word(word, letter);
        }
        else{
            if(strlen(word) != 0){
                elem = find(root, word);
                if (elem != NULL){
                    info = get_info(elem) + 1;
                    delete(&root, word);
                }
                insert(&root, word, info);
                info = 1;
                word = calloc(1, sizeof(char));
            }
            
        }
    } while (letter != EOF);
    free(word);
    fclose(input);
    free(filename);
    filename = readline("Введите имя файла, в который вывести результат работы: ");
    if (filename == NULL) return eXXit(GOOD, root, filename);
    FILE* output = fopen(filename, "w");
    if (output == NULL){
        printf("Ошибка файла\n");
        return eXXit(GOOD, root, filename);;
    }
    traversal(root, output, 0);
    fclose(output);
    return eXXit(GOOD, root, filename);
}