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
#define LAST_ELEMENT 11
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

// TODO: CONST DATA TYPE WHERE REQUIRED
void display(const table_t* table);
table_t* get_table(const int size);
void free_table(table_t * const table); // нужно ли писать так?

int to_text(const table_t* table, const char*);
int from_text(table_t** table, const char* filename);

int delete_interval(table_t* table, const int highest, const int lowest);

#ifdef MAIN_TASK
int binsearch\
(void* data, const void* inserted, const int amount, const int size, int(*copmarator)(const void*, const void*));
KeySpace* find(const table_t*, const unsigned int);
void print_found(const KeySpace*);
void free_elem(KeySpace* elem);
int insert(table_t* table, char* info, unsigned int key);
int delete(table_t*, const unsigned int);
#elif DOP_TASK
int iter_compare(const iterator_t first, const iterator_t second);
iterator_t begin(const table_t* table);
iterator_t end(const table_t* table);
iterator_t next(const iterator_t iter);
iterator_t back(const iterator_t iter);
KeySpace* iter_pointer(const iterator_t iter);
unsigned int iter_key(const iterator_t iter);
char* iter_value(const iterator_t iter);
iterator_t find(const table_t *table, const unsigned int key, int* res);
void print_found(const iterator_t iter);
iterator_t insert(table_t* table, char* info, unsigned int key, int* res);
iterator_t delete(table_t*, const unsigned int, int* res);
#endif
