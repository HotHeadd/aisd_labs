#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "table.h"
#include <math.h>
#include <unistd.h>

// ВСЕ ДИАЛОГИ В ПРИКОЛАДНОЙ ПРОГЕ (диалог только для вывода в файл)

// инициализация
table_t* get_table(const int size){
    table_t* table = calloc(1, sizeof(table_t));
    table->msize = size;
    table->ks = calloc(table->msize, sizeof(KeySpace));
    table->csize = 0;
    return table;
}

// вывод таблицы в поток
void display(const table_t* table){
    KeySpace* elem;
    if (table == NULL){
        printf("Никакой таблицы нет");
        return;
    }
    printf("Здравствуйте, ваша таблица:\n");
    printf(" ------------------------\n");
    for (int i=0; i<(table->msize); i++){
        elem = table->ks + i;
        if (elem->info == NULL) printf("|NULL      |NULL      | 0| --> NULL\n");
        else{
            printf("|%-10u|%-10u|%2u|", elem->key, *elem->info, elem->release);
            while ((elem = elem->next) != NULL){
                printf(" --> |%-10u|%-10u|%2u|", elem->key, *elem->info, elem->release);
            }
            printf(" --> NULL\n");
        }
    }
    printf(" ------------------------\n");
}

// очистка
void free_table(table_t* const table){
    if (table == NULL) return;
    for (int i=0; i<(table->msize); i++){
        KeySpace* elem = table->ks+i;
        KeySpace* prev = NULL;
        int flag = 0;
        while (elem != NULL){
            free(elem->info);
            if (flag != 0){
                prev = elem;
            }
            elem = elem->next;
            free(prev);
            flag++;
        }
    }
    free(table->ks);
    free(table);
}

unsigned hash_func(const table_t* table, const unsigned key){
    return key%(table->msize);
}

int is_prime(int num){
    for (int i=2; i<(int)(sqrt(num))+1;i++){
        if ((num%i) == 0) return 0;
    }
    return 1;
}

unsigned simple(unsigned size){
    unsigned resault = size;
    while (is_prime(++resault) == 0);
    return resault;
}

table_t* extend_table(table_t* table){
    table_t* new_table =  get_table(simple(table->msize));
    for (int i=0;i<table->msize;i++){
        KeySpace* elem = table->ks+i;
        while (elem != NULL){
            if (elem->info != NULL){
                insert(&new_table, *(elem->info), elem->key);
            }
            elem = elem->next;
        }
    }
    printf("Таблица расширена\n");
    free_table(table);
    return new_table;
}

int insert(table_t** table, unsigned info, unsigned key){
    if (*table == NULL){
        return NO_TABLE;
    }
    unsigned* to_input = calloc(1, sizeof(unsigned));
    *to_input = info;
    unsigned index = hash_func(*table, key);
    KeySpace* elem = (*table)->ks + index;
    unsigned release = 0;
    if (elem->info == NULL){
        (*table)->csize++;
        index = hash_func(*table, key);
        elem = (*table)->ks + index;
        elem->key = key;
        elem->info = to_input;
        elem->release = 0;
        if ((*table)->msize == (*table)->csize){
            (*table) = extend_table(*table);
        }
    }
    else{
        KeySpace* neww = calloc(1, sizeof(KeySpace));
        neww->next = elem->next;
        neww->info = elem->info;
        neww->key = elem->key;
        neww->release = elem->release;
        do{
            if (elem->key == key) release++;
        }
        while ((elem = elem->next) != NULL);
        elem = (*table)->ks + index;
        elem->key = key;
        elem->info = to_input;
        elem->release = release;
        elem->next = neww;
    }
    return GOOD;
}

KeySpace* find(const table_t *table, const unsigned int key){
    return NULL;
}

KeySpace* copy_elem(const KeySpace* elem){
    return NULL;
}

void print_found(const KeySpace* elem){
    printf("Найденный элемент: %u \"%u\"\n", elem->key, *elem->info);
}

void free_elem(KeySpace* elem){
    free(elem->info);
    free(elem);
}

int delete(table_t* table, const unsigned key){
    if (table == NULL) return NO_TABLE;
    table->csize--;
    return GOOD;
}