#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "table.h"

// ВСЕ ДИАЛОГИ В ПРИКОЛАДНОЙ ПРОГЕ (диалог только для вывода в файл)

// инициализация
table_t* get_table(int size){
    table_t* table = calloc(1, sizeof(table_t));
    table->msize = size;
    table->ks = calloc(table->msize, sizeof(KeySpace));
    table->csize = 0;
    return table;
}

// очистка
void free_table(table_t* table){
    if (table == NULL) return;
    for (int i=0; i<(table->csize); i++){
        free((table->ks+i)->info);
    }
    table->csize = 0;
    free(table->ks);
    free(table);
}

// вставка

// from lab 5 sem 1
int binsearch\
(void* data, void* inserted, int amount, int size, int(*copmarator)(const void*, const void*)){
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

int compare_ins(const KeySpace* a, const KeySpace* b){
    return (a->key - b->key);
}

int compare_fd(const KeySpace* a, const int* b){
    return (a->key - *b);
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
    if (table->msize == table->csize){
        free(info);
        return TABLE_OVERFLOW;
    }
    KeySpace elem;
    elem.key = key;
    elem.info = info;
    int index = binsearch\
    (table->ks, &elem, table->csize, sizeof(KeySpace), (int (*)(const void*, const void*)) compare_ins);
    if (index < 0){
        free(info);
        return KEY_EXIST;
    }
    ins_elem(table, elem, index);
    table->csize += 1;
    return GOOD;
}
// удаление

int delete(table_t* table, unsigned int key){
    int res = binsearch\
    (table->ks, &key, table->csize, sizeof(KeySpace), (int (*)(const void*, const void*)) compare_fd);
    if (res >= 0) return ELEM_NOT_FOUND;
    res = (-1)*(res+1);
    printf("%d\n", res);
    free((table->ks+res)->info);
    for (int i=res; i<table->csize-1;i++){
        (table->ks)[i] = (table->ks)[i+1];
    }
    table->csize -= 1;
    return GOOD;
}

// поиск по ключу (В таблице не может быть двух элементов с одинаковыми значениями ключей.)

KeySpace* find(table_t *table, unsigned int key){ // переделать так, чтобы возвращалась таблица
    int res = binsearch\
    (table->ks, &key, table->csize, sizeof(KeySpace), (int (*)(const void*, const void*)) compare_fd);
    if (res >= 0) return NULL;
    res = (-1)*(res+1);
    // copy?
    return (table->ks+res);
}

void print_found(KeySpace* elem){
    printf("Найденный элемент: %u %s\n", elem->key, elem->info);
}

// вывод таблицы в поток
void display(table_t* table){
    printf("Здравствуйте, ваша таблица:\n");
    for (int i=0; i<(table->csize); i++){
        printf("%u %s\n", (table->ks + i)->key, (table->ks)[i].info);
    }
}
// импорт и экспорт таблицы из текстового

int to_text(table_t* table, char* filename){
    FILE* output = fopen(filename, "w");
    if (output == NULL) return FILE_ERROR;
    fprintf(output, "%d %d\n", table->msize, table->csize);
    for (int i=0;i<table->csize; i++){
        fprintf(output, "%u\t%s\n", (table->ks+i)->key, (table->ks+i)->info);
    }
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

int from_text(table_t** table, char* filename){
    free_table(*table);
    FILE* input = fopen(filename, "r");
    if (input == NULL) return FILE_ERROR;
    int size;
    fscanf(input, "%d", &size);
    *table = get_table(size);
    fscanf(input, "%d%*c", &size);
    (*table)->csize = size;
    for (int i=0;i<(*table)->csize;i++){
        fscanf(input, "%u%*c", &(((*table)->ks+i)->key));
        ((*table)->ks+i)->info = file_readline(input);
        printf("%u \"%s\"\n", ((*table)->ks+i)->key, ((*table)->ks+i)->info);
    }
    return GOOD;
}

// индивид таск
// удаление из таблицы элементов, заданных диапазоном ключей; в таблице могут отсутствовать
// элементы с ключами, задающими диапазон.

// ДОП

// СОЗДАТЬ ИТЕРАТОР (ТИП ДАННЫХ)
// создание итератора
// удаление итератора
// сравнение итераторов (1 если указывают на один элемент, 0 если нет)
// получение итератора, указ на первый элем. таблицы
// получение итератора, указ на следующий элем. таблицы
// получение итератора, указ на последний элем. таблицы

// СОЗЖАТЬ ВТОРОЙ НАБОР ФУНКЦИЙ ДЛЯ ТАБЛИЦЫ
// вставка возвращает итератор, указывающий на вставленный элемент
// Удаление возвращает итератор, который укаызывает на следующий после удаленного элемент
// Поиск возвращает итератор на найденный элемент

// Добавить в мейкфайл выбор реализации с итераторами и без