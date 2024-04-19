#include <stdlib.h>
#include <string.h>
#include "tree.h"

void free_tree(Node* root){
    return;
}

void addinfo(Node* root, unsigned info){
    return;
}

unsigned* get_info(unsigned info){
    unsigned* to_insert = calloc(1, sizeof(unsigned));
    *to_insert = info;
    return to_insert;
}

int insert(Node** root, char* key, unsigned info){
    unsigned* to_insert;
    if (*root == NULL){
        to_insert = get_info(info);
        *root = calloc(1, sizeof(Node));
        (*root)->key = key;
        (*root)->info = to_insert;
        return ROOT_CREATED;
    }
    int compare = strcmp(key, (*root)->key);
    if (compare == 0){
        addinfo(*root, info);
        return KEY_EXIST;
    }
    if (compare < 0){
        if ((*root)->left == NULL){
            to_insert = get_info(info);
            Node* child = calloc(1, sizeof(Node));
            child->key = key;
            child->info = to_insert;
            child->parent = *root;
            (*root)->left = child;
            return GOOD;
        }
        return insert(&((*root)->left), key, info);
    }
    if (compare > 0){
        if ((*root)->right == NULL){
            to_insert = get_info(info);
            Node* child = calloc(1, sizeof(Node));
            child->key = key;
            child->info = to_insert;
            child->parent = *root;
            (*root)->right = child;
            return GOOD;
        }
        return insert(&((*root)->right), key, info);
    }
}