#pragma once

#define GOOD 0
#define ROOT_CREATED 2
#define KEY_EXIST 1
#define ELEM_NOT_FOUND 3
#define FILE_ERROR 4 
#define FORMAT_ERROR 5
#define NO_TREE 6
#define MULTIPLE_DATA 7
#define LAST_ELEMENT 8
#define END_INPUT -1

typedef struct info_t{
    struct info_t* next;
    unsigned value;
} info_t;

typedef struct Node{
    char* key;
    info_t* info;
    struct Node* right;
    struct Node* left;
    struct Node* parent;    
} Node;

void free_tree(Node* root);

int insert(Node** root, char* key, unsigned info);
Node* find(Node* root, const char* key);
int delete(Node** root, char* key);

Node* special_find(Node* root, char* key);