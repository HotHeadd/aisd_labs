#include "tree.h"
#include "tree_io.h"
#include <stdio.h>

void put_data(Node* root){
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

void print_tree(Node* root, int level){
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
int txt_out_rec(Node* root, char* filename){
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
    tree_to_txt(root->left, filename);
    tree_to_txt(root->right, filename);
    return GOOD;
}

int tree_to_txt(Node* root, char* filename){
    FILE* output = fopen(filename, "w");
    if (output == NULL) return FILE_ERROR;
    return txt_out_rec(root, filename);
}