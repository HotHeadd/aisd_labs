#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"

void free_tree(Node* root){
    if (root->left != NULL) free_tree(root->left);
    if (root->right != NULL) free_tree(root->right);
    free(root->key);
    info_t* prev = root->info;
    while (root->info != NULL){
        root->info = root->info->next;
        free(prev);
        prev = root->info;
    }
    free(root);
}

void addinfo(Node* root, unsigned info){
    info_t* elem = root->info;
    while (elem->next != NULL){
        elem = elem->next;
    }
    info_t* neww = calloc(1, sizeof(info_t));
    neww->value = info;
    elem->next = neww;
}

int insert(Node** root, char* key, unsigned info){
    if (*root == NULL){
        *root = calloc(1, sizeof(Node));
        (*root)->key = key;
        (*root)->info = calloc(1, sizeof(info_t));
        (*root)->info->value = info;
        return ROOT_CREATED;
    }
    int compare = strcmp(key, (*root)->key);
    if (compare == 0){
        addinfo(*root, info);
        return KEY_EXIST;
    }
    if (compare < 0){
        if ((*root)->left == NULL){
            Node* child = calloc(1, sizeof(Node));
            child->key = key;
            child->info = calloc(1, sizeof(info_t));
            child->info->value = info;
            child->parent = *root;
            (*root)->left = child;
            return GOOD;
        }
        return insert(&((*root)->left), key, info);
    }
    if (compare > 0){
        if ((*root)->right == NULL){
            Node* child = calloc(1, sizeof(Node));
            child->key = key;
            child->info = calloc(1, sizeof(info_t));
            child->info->value = info;
            child->parent = *root;
            (*root)->right = child;
            return GOOD;
        }
        return insert(&((*root)->right), key, info);
    }
}