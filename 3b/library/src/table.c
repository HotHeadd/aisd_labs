#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "table.h"

// ВСЕ ДИАЛОГИ В ПРИКОЛАДНОЙ ПРОГЕ (диалог только для вывода в файл)

// инициализация
table_t* get_table(const int size){
    table_t* table = calloc(1, sizeof(table_t));
    table->msize = size;
    table->ks = calloc(table->msize, sizeof(KeySpace));
    table->csize = 0;
    return table;
}

// очистка
void free_table(table_t* const table){
    if (table == NULL) return;
    for (int i=0; i<(table->csize); i++){
        free((table->ks+i)->info);
    }
    table->csize = 0;
    free(table->ks);
    free(table);
}


int to_text(const table_t* table, const char* filename){
    if (table == NULL) return NO_TABLE;
    FILE* output = fopen(filename, "w");
    if (output == NULL) return FILE_ERROR;
    fprintf(output, "%d %d\n", table->msize, table->csize);
    for (int i=0;i<table->csize; i++){
        fprintf(output, "%u\t%s\n", (table->ks+i)->key, (table->ks+i)->info);
    }
    fclose(output);
    return GOOD;
}

char* file_readline(FILE* file){ //переделанный для файлов ридлайн из 5 лабы
    int s_len, b_len, res = 1, no_action = 1;
    char *str = (char*)calloc(1, sizeof(char));
    char *buff = calloc(5, sizeof(char));
    res = fscanf(file, "%4[^\n]", buff);
    if (res == -1) {free(buff); free(str); return NULL;}
    while (buff[0] && res!= 0){
            no_action = 0;
            if (res == -1) return NULL;
            if (str) s_len = strlen(str); else s_len = 0;
            if (buff) b_len = strlen(buff); else b_len = 0;
            str = (char*)realloc(str, (s_len+b_len)*sizeof(char)+1);
            strcat(str, buff);
            *(str+s_len+b_len) = '\0';
            res = fscanf(file, "%4[^\n]", buff);
    }
    if (buff != NULL) free(buff);
    fscanf(file, "%*c");
    if (no_action){
            free(str);
            str = calloc(7, sizeof(char));
            strcat(str, "(null)");
    }
    return str;
}

int from_text(table_t** table, const char* filename){
    free_table(*table);
    int res, size;
    FILE* input = fopen(filename, "r");
    if (input == NULL){
        *table = NULL;
        return FILE_ERROR;
    }
    fscanf(input, "%d", &size);
    *table = get_table(size);
    fscanf(input, "%d%*c", &size);
    (*table)->csize = size;
    if ((*table)->csize > (*table)->msize){
        (*table)->csize = 0;
        free_table(*table);
        *table = NULL;
        return FORMAT_ERROR;
    }
    for (int i=0;i<(*table)->csize;i++){
        res = fscanf(input, "%u%*c", &(((*table)->ks+i)->key));
        if ((res != 1)||((i!=0) && (((*table)->ks+i)->key < ((*table)->ks+i-1)->key))){
            (*table)->csize = i;
            free_table(*table);
            *table = NULL;
            return FORMAT_ERROR;
        }
        ((*table)->ks+i)->info = file_readline(input);
        if (((*table)->ks+i)->info == "NULL"){
            if (res != 1){
                (*table)->csize = i;
                free_table(*table);
                *table = NULL;
                return FORMAT_ERROR;
            }
        }
    }
    char b;
    if (fscanf(input, "%c", &b) == 1){
        (*table)->csize = 0;
        free_table(*table);
        *table = NULL;
        return FORMAT_ERROR;
    }
    fclose(input);
    return GOOD;
}

#ifdef MAIN_TASK
int compare_fd(const KeySpace* a, const int* b){
    return (a->key - *b);
}

int compare_ins(const KeySpace* a, const KeySpace* b){
    return (a->key - b->key);
}
int binsearch\
(void* data, const void* inserted, const int amount, int size, int(*copmarator)(const void*, const void*)){
	if (amount == 0) return 0;
    int left = 0, right = amount, res, index=0;
	void* element = data;
	while (left+1 < right){
		index = (left+right) / 2;
		element = data + index*size;
		res = copmarator(element, inserted);
		if (res == 0) return (-1)*index - 1;
		if (res > 0) right = index;
		else left = index;
	}
	element = data + left*size;
	res = copmarator(element, inserted);
	if (res > 0) return left;
    if (res == 0) return (-1)*left - 1;
	return right;
}
// вывод таблицы в поток
void display(const table_t* table){
    if (table == NULL){
        printf("Никакой таблицы нет");
        return;
    }
    printf("Здравствуйте, ваша таблица:\n");
    for (int i=0; i<(table->csize); i++){
        printf("%u \"%s\"\n", (table->ks + i)->key, (table->ks)[i].info);
    }
}

KeySpace* copy_elem(const KeySpace* elem){
    KeySpace* copy = calloc(1, sizeof(KeySpace));
    copy->key = elem->key;
    copy->info = strdup(elem->info);
    return copy;
}

KeySpace* find(const table_t *table, const unsigned int key){
    if ((table == NULL) || (table->csize == 0)) return NULL;
    int res = binsearch\
    (table->ks, &key, table->csize, sizeof(KeySpace), (int (*)(const void*, const void*)) compare_fd);
    if (res >= 0) return NULL;
    res = (-1)*(res+1);
    KeySpace* copy = copy_elem(table->ks+res);
    return copy;
}

void print_found(const KeySpace* elem){
    printf("Найденный элемент: %u \"%s\"\n", elem->key, elem->info);
}

void free_elem(KeySpace* elem){
    free(elem->info);
    free(elem);
}

int ins_elem(table_t* table, KeySpace elem, int index){
    KeySpace* mass = table->ks;
    for (int i=table->csize; i>index;i--){
        mass[i] = mass[i-1];
    }
    mass[index] = elem;
    return GOOD;
}

int insert(table_t* table, char* info, unsigned int key){
    if (table == NULL){
        return NO_TABLE;
    }
    if (table->msize == table->csize){
        return TABLE_OVERFLOW;
    }
    KeySpace elem;
    elem.key = key;
    elem.info = info;
    int index = binsearch\
    (table->ks, &elem, table->csize, sizeof(KeySpace), (int (*)(const void*, const void*)) compare_ins);
    if (index < 0){
        return KEY_EXIST;
    }
    ins_elem(table, elem, index);
    table->csize += 1;
    return GOOD;
}

int delete(table_t* table, const unsigned int key){
    if (table == NULL) return NO_TABLE;
    int res = binsearch\
    (table->ks, &key, table->csize, sizeof(KeySpace), (int (*)(const void*, const void*)) compare_fd);
    if (res >= 0) return ELEM_NOT_FOUND;
    res = (-1)*(res+1);
    free((table->ks+res)->info);
    for (int i=res; i<table->csize-1;i++){
        (table->ks)[i] = (table->ks)[i+1];
    }
    table->csize -= 1;
    return GOOD;
}

int delete_interval(table_t* table, const int highest, const int lowest){
    for (int i=lowest; i<=highest; i++){
        delete(table, i);
    }
    return GOOD;
}
#elif DOP_TASK
// сравнение итераторов (1 если указывают на один элемент, 0 если нет)
int iter_compare(const iterator_t first, const iterator_t second){
    return first.current == second.current;
}


iterator_t begin(const table_t* table){
    iterator_t result = {result.current = table->ks};
    return result;
}

iterator_t end(const table_t* table){
    iterator_t result = {result.current = table->ks + table->csize};
    return result;
}

iterator_t next(const iterator_t iter){
    iterator_t result = {result.current = iter.current + 1};
    return result;
}

iterator_t back(const iterator_t iter){
    iterator_t result = {result.current = iter.current - 1};
    return result;
}

unsigned int iter_key(const iterator_t iter){
    return (iter.current)->key;
}

char* iter_value(const iterator_t iter){
    return (iter.current)->info;
}

iterator_t null_iter(){
    iterator_t result = {result.current = NULL};
    return result;
}

KeySpace* iter_pointer(const iterator_t iter){
    return iter.current;
}

iterator_t delete(table_t* table, const unsigned int key, int* res){
    int res_find;
    if (table == NULL){
        *res = NO_TABLE;
        return null_iter();
    }
    iterator_t iter = find(table, key, &res_find);
    if (res_find == ELEM_NOT_FOUND){
        *res = ELEM_NOT_FOUND;
        return null_iter();
    }
    free(iter_value(iter));
    for (iterator_t i = iter; iter_compare(i, back(end(table)))==0 ; i = next(i)){
        *iter_pointer(i) = *iter_pointer(next(i));
    }
    table->csize -= 1;
    if (iter_compare(iter, end(table))) {
        *res = LAST_ELEMENT;
        return null_iter();
    }
    return iter;
}

int delete_interval(table_t* table, const int highest, const int lowest){
    int res;
    for (int i=lowest; i<=highest; i++){
        delete(table, i, &res);
    }
    return GOOD;
}

iterator_t find(const table_t *table, const unsigned int key, int* res){
    *res = ELEM_NOT_FOUND;
    if (table == NULL) return null_iter();
    for (iterator_t i = begin(table); iter_compare(i, end(table)) == 0; i = next(i)){
        if (iter_key(i) == key){
            *res = GOOD;
            return i;
        }
        if (iter_key(i) > key){
            return i;
        }
    }
    return end(table);
}

void print_found(iterator_t iter){
    printf("Найденный элемент: %u \"%s\"\n", iter_key(iter), iter_value(iter));
}

void ins_elem(table_t* table, KeySpace elem, iterator_t index){
    for (iterator_t i = end(table); iter_compare(i, index) == 0; i = back(i)){
        *iter_pointer(i) = *iter_pointer(back(i));
    }
    *iter_pointer(index) = elem;
}

// вставка возвращает итератор, указывающий на вставленный элемент
iterator_t insert(table_t* table, char* info, unsigned int key, int* res){
    int result;
    if (table == NULL){
        *res = NO_TABLE;
         return null_iter();
    }
    if (table->msize == table->csize){
        *res = TABLE_OVERFLOW;
        return null_iter();
    }
    KeySpace elem;
    elem.key = key;
    elem.info = info;
    iterator_t index = find(table, key, &result);
    if (result == GOOD){
        *res = KEY_EXIST;
        return null_iter();
    }
    ins_elem(table, elem, index);
    table->csize += 1;
    return index;
}

// Вывод при помощи итераторов
void display(const table_t* table){
    if (table == NULL){
        printf("Никакой таблицы нет");
        return;
    }
    printf("Здравствуйте, ваша таблица:\n");
    for (iterator_t i=begin(table); iter_compare(i, end(table)) == 0; i=next(i)){
        printf("%u \"%s\"\n", iter_key(i), iter_value(i));
    }
}
#endif
