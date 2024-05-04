#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "tree_io.h"
#include "stack.h"
#include "splay.h"
#include <math.h>

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

void free_tree(Tree* tree, int mode){
    Node* root = tree->root;
    stack_tm* stack = get_stack(SIZE);
    Node* last = NULL;
    while ((peek(stack) != NULL) || (root != NULL)){
        if (root != NULL){
            push(stack, root);
            root = root->left;
        }
        else{
            Node* pn = peek(stack);
            if (pn->right != NULL && last != pn->right){
                root = pn->right;
            }
            else{
                free_elem(pn, 1);
                pop(stack, &last);
            }
        }
    }
    free_stack(stack);
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

int insert(Tree* tree, char* key, unsigned info){
    if (tree->root == NULL){
        tree->root = calloc(1, sizeof(Node));
        tree->root->key = key;
        tree->root->info = calloc(1, sizeof(info_t));
        tree->root->info->value = info;
        return ROOT_CREATED;
    }
    Node* root = tree->root;
    while (1){
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
            root = root->left;
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
            root = root->right;
        }
    }
}

int delete(Tree* tree, char* key){
    Node* root = tree->root;
    int found;
    Node* elem = find(tree, key, &found);
    if (!found) return ELEM_NOT_FOUND;
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

Node* find(Tree* tree, const char* key, int* found){
    Node* root = tree->root;
    if (root == NULL) {
        *found = 0;
        return NULL;
    }
    while ((root->left != NULL) || (root->right != NULL)){
        int compare = strcmp(key, root->key);
        if (compare == 0){
            *found = 1;
            splay(tree, root);
            return tree->root;
        }
        if ((compare > 0) && (root->right != NULL))
            root = root->right;
        if ((compare < 0) && (root->left != NULL))
            root = root->left;
    }
    if (strcmp(key, root->key) == 0) 
        *found = 1;
    else
        *found = 0;
    splay(tree, root);
    return tree->root;
}

Node* special_find(Tree* tree, char* key){
    Node* root = tree->root;
    if (root == NULL) return NULL;
    while (strcmp(key, root->key) > 0) 
        root = root->right;
    if (root->left != NULL)
        root = root->left;
    else
        return root;
    while (root->right != NULL)
        root = root->right;
    if (root != NULL) splay(tree, root);
    return root;
}