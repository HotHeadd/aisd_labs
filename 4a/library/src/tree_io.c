#include "tree.h"
#include "tree_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void put_data(const Node* root){
    printf("{%s}: [", root->key);
    info_t* elem = root->info;
    int start = 1;
    while (elem != NULL){
        if (start) start -= 1;
        else printf(", ");
        printf("%u", elem->value);
        elem = elem->next;
    }
    printf("]\n");
    return;
}

void print_tree(const Node* root, const int level){
    if (level == 0) printf("Здравствуйте, ваше дерево:\n");
    if (root == NULL){
        if (level != 0){
            for (int i = 0; i < level; i++)
                printf(i == level - 1 ? "|->\n" : "    ");
        }
        return;
    }
    for (int i = 0; i < level; i++)
        printf(i == level - 1 ? "|-> " : "    ");
    put_data(root);
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}
int txt_out_rec(const Node* root, const char* filename){
    if (root == NULL) return NO_TREE;
    FILE* output = fopen(filename, "a");
    int count = 1;
    info_t* elem = root->info;
    while ((elem=elem->next) != NULL) count++;
    elem = root->info;
    fprintf(output, "%s\n", root->key);
    fprintf(output, "%d\n", count);
    while (elem != NULL){
        fprintf(output, "%d\n", elem->value);
        elem = elem->next;
    }
    fclose(output);
    txt_out_rec(root->left, filename);
    txt_out_rec(root->right, filename);
    return GOOD;
}

int tree_to_txt(const Node* root, const char* filename){
    FILE* output = fopen(filename, "w");
    if (output == NULL) return FILE_ERROR;
    fclose(output);
    return txt_out_rec(root, filename);
}

char* file_readline(FILE* file){ //достаю из широких штанин функцию из 4 лабы
    int s_len, b_len, res = 1, no_action = 1;
    char *str = (char*)calloc(1, sizeof(char));
    char *buff = calloc(5, sizeof(char));
    res = fscanf(file, "%4[^\n]", buff);
    if (res == -1) {free(buff); free(str); return NULL;}
    while (buff[0] && res!= 0){
            no_action = 0;
            if (res == -1) return NULL;
            if (str) s_len = strlen(str); else s_len = 0;
            if (buff) b_len = strlen(buff); else b_len = 0;
            str = (char*)realloc(str, (s_len+b_len)*sizeof(char)+1);
            strcat(str, buff);
            *(str+s_len+b_len) = '\0';
            res = fscanf(file, "%4[^\n]", buff);
    }
    if (buff != NULL) free(buff);
    fscanf(file, "%*c");
    if (no_action){
            free(str);
            str = calloc(7, sizeof(char));
            strcat(str, "(null)");
    }
    return str;
}

int tree_from_txt(Node** root, const char* filename){
    free_tree(*root);
    *root = NULL;
    FILE* input = fopen(filename, "r");
    if (input == NULL) return FILE_ERROR;
    char* key;
    unsigned info;
    int count = 0;
    int res = 0;
    while ((key = file_readline(input)) != NULL){
        res = fscanf(input, "%d", &count);
        if (res == 0){
            free_tree(*root);
            return FILE_ERROR;
        }
        for (int _=0; _ < count; _++){
            res = fscanf(input, "%u", &info);
            if (res == 0){
                free_tree(*root);
                return FILE_ERROR;
            }
            insert(root, key, info);
            fscanf(input, "%*c");
        }
    }
    fclose(input);
    return GOOD;
}