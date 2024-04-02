#pragma once

#define GOOD 0
#define KEY_EXIST 1
#define TABLE_OVERFLOW 2
#define ELEM_NOT_FOUND 3
#define FILE_ERROR 4 
#define FORMAT_ERROR 5
#define NO_TABLE 6
#define EOTABLE 7
#define LAST_ELEMENT 8
#define END_INPUT -1

typedef struct KeySpace {
    // ключ элемента
    unsigned key;
    // номер версии элемента
    unsigned release;
    // указатель на информацию
    unsigned *info;
    // указатель на следующий элемент
    struct KeySpace *next;
} KeySpace;

typedef struct table_t {
    // указатель на пространство ключей
    KeySpace *ks;
    // размер области пространства ключей
    int msize; //указать при инициализации
    int csize;
} table_t;

void display(const table_t* table);
table_t* get_table(const int size);
void free_table(table_t * const table);

int to_text(const table_t* table, const char*);
int from_text(table_t** table, const char* filename);

KeySpace* find(const table_t*, const unsigned);
void print_found(const KeySpace*);
void free_elem(KeySpace* elem);
int insert(table_t** table, unsigned info, unsigned);
int delete(table_t*, const unsigned int);