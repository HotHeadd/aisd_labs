#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "splay.h"

void splay(Tree* tree, Node* elem){
    Node* parent = elem->parent;
    if (parent == NULL){ 
        tree->root = elem;
        return;
    }
    Node* grand = elem->parent->parent;
    if (grand == NULL){
        zig(elem);
        tree->root = elem;
        return;
    }
    else{
        int zigzig = (int)((grand->left == parent) == (parent->left == elem));
        if (zigzig){
            zig(parent);
            zig(elem);
        }
        else{
            zig(elem);
            zig(elem);
        }
    }
    return splay(tree, elem);
}

void set_parent(Node* elem, Node* parent){
    if (elem != NULL)  
        elem->parent = parent;
}

void zig(Node* elem){
    Node* grand = elem->parent->parent;
    Node* parent = elem->parent;
    if (grand != NULL){
        if (grand->left == parent)
            grand->left = elem;
        else
            grand->right = elem;
    }
    if (parent->left == elem) {
        parent->left = elem->right;
        elem->right = parent;
    }
    else{
        parent->right = elem->left;
        elem->left= parent;
    }
    set_parent(elem->left, elem);
    set_parent(elem->right, elem);
    set_parent(parent->left, parent);
    set_parent(parent->right, parent);
    elem->parent = grand;
}

Node* merge(Node* neww, Node* left, Node* right){
    set_parent(left, neww);
    set_parent(right, neww);
    if (neww == NULL){
        if (left == NULL)
            return right;
        if (right == NULL)
            return left;
        int found;
        Tree* fake = calloc(1, sizeof(Tree));
        fake->root = right;
        right = find(fake, left->key, &found);
        free(fake);
        right->left = left;
        left->parent = right;
        return right;
    }
    else{
        neww->left = left;
        neww->right = right;
        return neww;
    }
}

Node** split(Tree* tree, char* key){
    Node** res = calloc(2, sizeof(Node*));
    Node* root = tree->root;
    if (root == NULL) return res;
    int compare = strcmp(key, root->key);
    if (compare > 0){
        res[0] = tree->root;
        res[1] = tree->root->right;
        root->right = NULL;
        set_parent(res[1], NULL);
    }
    else{
        res[0] = tree->root->left;
        res[1] = tree->root;
        root->left = NULL;
        set_parent(res[0], NULL);
    }
    return res;
}