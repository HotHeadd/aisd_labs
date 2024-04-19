#pragma once

#define GOOD 0
#define ROOT_CREATED 2
#define KEY_EXIST 1
#define ELEM_NOT_FOUND 3
#define FILE_ERROR 4 
#define FORMAT_ERROR 5
#define NO_TABLE 6
#define EOTABLE 7
#define LAST_ELEMENT 8
#define END_INPUT -1

typedef struct Node{
    char* key;
    unsigned* info;
    struct Node* right;
    struct Node* left;
    struct Node* parent;    
} Node;

int insert(Node** root, char* key, unsigned info);
void free_tree(Node* root);