#pragma once

#define GOOD 0
#define KEY_EXIST 1
#define TABLE_OVERFLOW 2
#define ELEM_NOT_FOUND 3
#define FILE_ERROR 4 
#define FORMAT_ERROR 5
#define END_INPUT -1
#define NO_TABLE 6
#define EOTABLE 10

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

typedef struct iterator_t{
    KeySpace* current;
} iterator_t;

// typedef struct KeySpace KeySpace;
// typedef struct table_t table_t;
// TODO: CONST DATA TYPE WHERE REQUIRED
int binsearch\
(void* data, void* inserted, int amount, int size, int(*copmarator)(const void*, const void*));
void display(table_t* table);
table_t* get_table(int size);
void free_table(table_t*);
int delete(table_t*, unsigned int);

int to_text(table_t* table, char*);
int from_text(table_t** table, char* filename);

int delete_interval(table_t* table, int highest, int lowest);

int iter_compare(iterator_t first, iterator_t second);
iterator_t begin(table_t* table);
iterator_t end(table_t* table);
iterator_t next(iterator_t iter);
iterator_t back(iterator_t iter);
iterator_t null_iter();
KeySpace* iter_pointer(iterator_t iter);
unsigned int iter_key(iterator_t iter);
char* iter_value(iterator_t iter);

#ifdef MAIN_TASK
KeySpace* find(table_t*, unsigned int);
void print_found(KeySpace*);
void free_elem(KeySpace* elem);
int insert(table_t* table, char* info, unsigned int key);
#elif DOP_TASK
iterator_t find(table_t *table, unsigned int key, int* res);
void print_found(iterator_t iter);
iterator_t insert(table_t* table, char* info, unsigned int key, int* res);
#endif