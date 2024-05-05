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
    if (tree == NULL) return;
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
    int found;
    Node* elem = find(tree, key, &found);
    if (found){ 
        addinfo(tree->root, info);
        return KEY_EXIST;
    }
    Node* neww = calloc(1, sizeof(Node));
    neww->key = key;
    neww->info = calloc(1, sizeof(info_t)); 
    neww->info->value = info;
    Node** res = split(tree, key);
    tree->root = merge(neww, res[0], res[1]);
    free(res);
    return GOOD;
}

int delete(Tree* tree, char* key){
    int found;
    Node* elem = find(tree, key, &found);
    if (!found) return ELEM_NOT_FOUND;
    if (elem->info->next != NULL){
        info_t* data = elem->info;
        elem->info = elem->info->next;
        free(data);
        return MULTIPLE_DATA;
    }
    tree->root = merge(NULL, elem->left, elem->right);
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
        else if ((compare < 0) && (root->left != NULL))
            root = root->left;
            else break;
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
    Node* last = NULL;
    if (root == NULL) return last;
    while (root != NULL){
        int compare = strcmp(key, root->key);
        if (compare >= 0){
            root = root->right;
        }
        else{
            last = root;
            root = root->left;
        }
    }
    if (last != NULL) splay(tree, last);
    return last;
}