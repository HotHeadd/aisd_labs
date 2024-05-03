#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "splay.h"
#include <math.h>
#include <stdio.h>

Tree* get_tree(){
    Tree* tree = calloc(1, sizeof(tree));
    return tree;
}

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

void free_root(Node* root){
    if (root == NULL) return;
    if (root->left != NULL) free_root(root->left);
    if (root->right != NULL) free_root(root->right);
    free_elem(root, 1);
}

void free_tree(Tree* tree, int mode){
    Node* root = tree->root;
    free_root(root);
    if (mode == 1) free(tree);
    else tree->root = NULL;
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

int insert_rec(Node* root, char* key, unsigned info){
    int compare = strcmp(key, root->key);
    if (compare == 0){
        addinfo(root, info);
        return KEY_EXIST;
    }
    if (compare < 0){
        if (root->left == NULL){
            Node* child = calloc(1, sizeof(Node));
            child->key = key;
            child->info = calloc(1, sizeof(info_t));
            child->info->value = info;
            child->parent = root;
            root->left = child;
            return GOOD;
        }
        return insert_rec(root->left, key, info);
    }
    if (compare > 0){
        if (root->right == NULL){
            Node* child = calloc(1, sizeof(Node));
            child->key = key;
            child->info = calloc(1, sizeof(info_t));
            child->info->value = info;
            child->parent = root;
            root->right = child;
            return GOOD;
        }
        return insert_rec(root->right, key, info);
    }
}

int insert(Tree* tree, char* key, unsigned info){
    if (tree->root == NULL){
        tree->root = calloc(1, sizeof(Node));
        tree->root->key = key;
        tree->root->info = calloc(1, sizeof(info_t));
        tree->root->info->value = info;
        return ROOT_CREATED;
    }
    return insert_rec(tree->root, key, info);
}

Node* find_rec(Node* root, const char* key){
    if (root == NULL) return NULL;
    int compare = strcmp(key, root->key);
    if (compare == 0) return root;
    if (compare < 0) return find_rec(root->left, key);
    return find_rec(root->right, key);
}

Node* find(Tree* tree, const char* key){
    Node* root = tree->root;
    return find_rec(root, key);
}

int delete(Tree* tree, char* key){
    Node* root = tree->root;
    Node* elem = find(tree, key);
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
        tree->root = child;
    else{
        if (parent->left == elem)
            parent->left = child;
        if (parent->right == elem)
            parent->right = child;
        if (child != NULL)
            child->parent = parent;
    }
    free_elem(elem, 1);
    return GOOD;
}


int mycomp(char* first, char* second){
    int len1 = strlen(first);
    int len2 = strlen(second);
    int iter = (int)fmin(len1, len2);
    for (int i=0; i < iter; i++){
        if (first[i] != second[i])
            return first[i] - second[i];
    }
    if (len1 > len2)
        return first[iter];
    if (len1 < len2)
        return second[iter];
    else return 0;
}

Node* special_find(Tree* tree, char* key){
    Node* root = tree->root;
    if (root == NULL) return NULL;
    Node* lelem = root, *relem = root;
    while (relem->right != NULL)
        relem = relem->right;
    while (lelem->left != NULL)
        lelem = lelem->left;
    if (mycomp(key, lelem->key) > mycomp(relem->key, key))
        return lelem;
    return relem;
}