#pragma once

typedef struct KeySpace {
    // ключ элемента
    unsigned int key;
    // указатель на информацию
    char *info;
} KeySpace;

typedef struct table_t {
    // указатель на пространство ключей
    KeySpace *ks;
    // размер области пространства ключей
    int msize; //указать при инициализации
    int csize;
} table_t;

// typedef struct KeySpace KeySpace;
// typedef struct table_t table_t;
int binsearch\
(void* data, void* inserted, int amount, int size, int(*copmarator)(const void*, const void*));
void display(table_t* table);
int insert(table_t* table, char* info, unsigned int key);
table_t* get_table();
void free_table(table_t*);