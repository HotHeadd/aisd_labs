#include <stdlib.h>
#include <string.h>
#include "tree.h"

void free_elem(Node* root, int delroot){
    free(root->key);
    info_t* prev = root->info;
    while (root->info != NULL){
        root->info = root->info->next;
        free(prev);
        prev = root->info;
    }
    if (delroot) free(root);
}

void free_tree(Node* root){
    if (root == NULL) return;
    if (root->left != NULL) free_tree(root->left);
    if (root->right != NULL) free_tree(root->right);
    free_elem(root, 1);
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

Node* find(Node* root, char* key){
    if (root == NULL) return NULL;
    int compare = strcmp(key, root->key);
    if (compare == 0) return root;
    if (compare < 0) return find(root->left, key);
    return find(root->right, key);
}

int delete(Node** root, char* key){
    Node* elem = find(*root, key);
    if (elem == NULL) return ELEM_NOT_FOUND;
    if (elem->info->next != NULL){
        info_t* data = elem->info;
        elem->info = elem->info->next;
        free(data);
        return MULTIPLE_DATA;
    }
    Node* parent = elem->parent;
    Node* child = elem->right == NULL ? elem->left : elem->right;
    if (((elem->left != NULL) && (elem->right != NULL))){
        Node* minimum = elem->right;
        while (minimum->left != NULL)
            minimum = minimum->left;
        free_elem(elem, 0);
        elem->key = minimum->key;
        elem->info = minimum->info;
        if (minimum->parent != elem){
            minimum->parent->left = minimum->right;
            if (minimum->right != NULL)
                minimum->right->parent = minimum->parent;
        }
        else
            elem->right = minimum->right;
            if (minimum->right != NULL)
                minimum->right->parent = minimum->parent;
        free(minimum);
        return GOOD;
    }
    if (parent == NULL)
        *root = child;
    else{
        if (parent->left == elem)
            parent->left = child;
        if (parent->right == elem)
            parent->right = child;
        child->parent = parent;
    }
    free_elem(elem, 1);
    return GOOD;
}