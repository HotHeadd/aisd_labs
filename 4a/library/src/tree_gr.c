#include "tree.h"
#include "tree_gr.h"
#include <stdlib.h>
#include <stdio.h>

void put_info(Node* root){
    printf("%d\n", *(root->info));
}

void print_tree(Node* root, char* prefix){
    printf("Здравствуйте, ваше дерево:\n");
    if (root == NULL){
        return;
    }
    printf("%s: ", root->key);
    put_info(root);
    //printf("%s". prefix);
}