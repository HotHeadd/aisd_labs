#pragma once

#define GOOD 0
#define KEY_EXIST 1
#define TABLE_OVERFLOW 2
#define ELEM_NOT_FOUND 3
#define FILE_ERROR 4 
#define FORMAT_ERROR 5
#define END_INPUT -1

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
table_t* get_table(int size);
void free_table(table_t*);
KeySpace* find(table_t*, unsigned int);
void print_found(KeySpace*);
void free_elem(KeySpace* elem);
int delete(table_t*, unsigned int);

int to_text(table_t* table, char*);
int from_text(table_t** table, char* filename);

int delete_interval(table_t* table, int highest, int lowest);