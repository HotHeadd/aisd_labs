#include <stdio.h>
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

int find_closest(Tree*){
    
    return 0;
}