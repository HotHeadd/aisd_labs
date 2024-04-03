#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "table.h"
#include <math.h>
#include <unistd.h>

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
                insert(&new_table, elem->key, *(elem->info));
            }
            elem = elem->next;
        }
    }
    printf("Таблица расширена\n");
    free_table(table);
    return new_table;
}

int insert(table_t** table, unsigned key, unsigned info){
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
        while ((elem->next) != NULL){
            if (elem->key == key) release++;
            elem = elem->next;
        }
        if (elem->key == key) release++;
        KeySpace* neww = calloc(1, sizeof(KeySpace));
        neww->key = key;
        neww->info = to_input;
        neww->release = release;
        neww->next = NULL;
        elem->next = neww;
    }
    return GOOD;
}

KeySpace copy_elem(const KeySpace* elem){
    KeySpace res;
    unsigned* new_info = calloc(1, sizeof(unsigned));
    *new_info = *(elem->info);
    res.key = elem->key;
    res.release = elem->release;
    res.info = new_info;
    res.next = NULL;
    return res;
}

KeySpace* find(const table_t *table, const unsigned int key){
    if ((table == NULL) || (table->csize == 0)) return NULL;
    unsigned index = hash_func(table, key);
    KeySpace* elem = (table)->ks + index;
    KeySpace* copy = NULL;
    KeySpace* resault = NULL;
    int count=0;
    if (elem->info == NULL) return NULL;
    while (elem != NULL){
        if (elem->key == key) count++;
        elem = elem->next;
    }
    elem = (table)->ks + index;
    if (count > 0) resault = calloc(count, sizeof(KeySpace));
    else return NULL;
    while (elem != NULL){
        if (elem->key == key){
            count--;
            resault[count] = copy_elem(elem);
        }
        elem = elem->next;
    }
    return resault;
}

void free_found(KeySpace* resault){
    if (resault == NULL) return;
    int size = resault->release;
    for (int i=0; i<size+1; i++){
        free((resault+i)->info);
    }
    free(resault);
}

void print_and_free(KeySpace* resault){
    printf("Найденные элементы:\n");
    for (int i=resault->release; i >= 0; i--){
        KeySpace* elem = resault + i;
        printf("|%-10u|%-10u|%2u|\n", elem->key, *elem->info, elem->release);
    }
    free_found(resault);
}

int del_elem(KeySpace* elem){
    if (elem->next == NULL){
        free(elem->info);
        elem->key = 0;
        elem->info = NULL;
        elem->release = 0;
        elem->next = NULL;
    }
    else{
        KeySpace* ne = elem->next;
        elem->next = ne->next;
        elem->key = ne->key;
        elem->release = ne->release;
        free(elem->info);
        elem->info = ne->info;
        free(ne);
    }
    return 1;
}

int delete(table_t* table, const unsigned key){
    if (table == NULL) return NO_TABLE;
    int res = 0;
    unsigned index = hash_func(table, key);
    KeySpace* elem = (table)->ks + index;
    if (elem->info == NULL) return ELEM_NOT_FOUND;
    if ((elem->next == NULL) && (elem->key == key)){
       res = del_elem(elem);
    }
    else{
        while (elem != NULL){
            while ((elem != NULL) && (elem->key == key)){
                res = del_elem(elem);
            }
            while ((elem != NULL) && (elem->next != NULL) && (elem->next->info != NULL) && (elem->next->key == key)){
                res = del_elem(elem->next);
            }
            if ((elem != NULL) && (elem->next != NULL) && (elem->next->info == NULL)){
                free(elem->next);
                elem->next = NULL;
            }
            elem = elem->next;
        }
    }
    if (((table)->ks + index)->info == NULL) table->csize--;
    if (res == 1) return GOOD;
    else return ELEM_NOT_FOUND;
}

int to_binary(const table_t* table, const char* filename ){
    if (table == NULL) return NO_TABLE;
    FILE* output = fopen(filename, "wb");
    if (output == NULL) return FILE_ERROR;
    fwrite(&(table->msize), sizeof(int), 1, output);
    for (int i=0; i<table->msize; i++){
        KeySpace* elem = table->ks+i;
        if (elem->info != NULL){
            while (elem->next != NULL){
                fwrite(&(elem->key), sizeof(unsigned), 1, output);
                fwrite(elem->info, sizeof(unsigned), 1, output);
                elem=elem->next;
            }
            fwrite(&(elem->key), sizeof(unsigned), 1, output);
            fwrite(elem->info, sizeof(unsigned), 1, output);
        }
    }
    fclose(output);
    return GOOD;
}

int from_binary(table_t** table, const char* filename){
    free_table(*table);
    char check;
    int res, size;
    unsigned key, info;
    FILE* input = fopen(filename, "rb");
    if (input == NULL){
        *table = NULL;
        return FILE_ERROR;
    }
    res = fread(&size, sizeof(int), 1, input);
    if ((res == 0) || (size <= 0)) return EOTABLE;
    *table = get_table(size);
    while (fread(&key, sizeof(unsigned), 1, input) != 0){
        res = fread(&info, sizeof(unsigned), 1, input);
        if (res == 0) return  FORMAT_ERROR;
        insert(table, key, info);
    }
    res = fread(&check, sizeof(char), 1, input);
    if (res == 1) return FORMAT_ERROR;
    fclose(input);
    return GOOD;
}

KeySpace* find_special(const table_t *table, const unsigned key, const int release){
    if ((table == NULL) || (table->csize == 0)) return NULL;
    unsigned index = hash_func(table, key);
    KeySpace* elem = (table)->ks + index;
    KeySpace* resault = NULL;
    int count=0;
    if (elem->info == NULL) return NULL;
    while (elem != NULL){
        if (elem->key == key){
            if (elem->release == release) return elem;
            count++;
        }
        elem = elem->next;
    }
    if (release >= 0) return NULL;
    elem = (table)->ks + index;
    if (count == 0) return NULL;
    resault = calloc(count, sizeof(KeySpace));
    while (elem != NULL){
        if (elem->key == key){
            count--;
            resault[count] = *elem;
        }
        elem = elem->next;
    }
    return resault;
}

void print_and_free_spec(KeySpace* resault, int release){
    if (release < 0){
        printf("Найденные элементы:\n");
        for (int i=resault->release; i >= 0; i--){
            KeySpace* elem = resault + i;
            printf("|%-10u|%-10u|%2u|\n", elem->key, *elem->info, elem->release);
        }
        free(resault);
    }
    else{
        printf("Найденный элемент:\n");
        printf("|%-10u|%-10u|%2u|\n", resault->key, *resault->info, resault->release);
    }
}

void flush_list(KeySpace* elem){
    KeySpace* current;
    while (elem != NULL){
        int flag_del = 0;
        current = elem->next;
        while (current != NULL){
            if (current->key == elem->key){
                del_elem(elem);
                flag_del = 1;
                break;
            }
            current = current->next;
        }
        if (flag_del == 0) elem = elem->next;
    }
}

int reorganize(table_t* table){
    KeySpace* elem;
    if (table == NULL) return NO_TABLE;
    for (int i = 0; i < table->msize; i++){
        elem = table->ks + i;
        if (elem->info == NULL) continue;
        flush_list(elem);
    }
}