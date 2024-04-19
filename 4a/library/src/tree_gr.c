#include "tree.h"
#include "tree_gr.h"
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