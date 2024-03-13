#include "basic.h"
#include <stdio.h>
#include <stdlib.h>
#include "table.h"

// ВСЕ ДИАЛОГИ В ПРИКОЛАДНОЙ ПРОГЕ (диалог только для вывода в файл)

// инициализация
table_t* get_table(){
    table_t* table = calloc(1, sizeof(table_t));
    printf("Введите размер таблицы: ");
    int res = custom_int_input(&(table->msize), o_n_and_0);
    if (res == -1){
        free(table);
        return NULL;
    }
    table->ks = calloc(table->msize, sizeof(KeySpace));
    table->csize = 0;
    return table;
}

// очистка
void free_table(table_t* table){
    for (int i=0; i<(table->csize); i++){
        free((table->ks+i)->info);
    }
    table->csize = 0;
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

int compare_find(const KeySpace* a, const int* b){
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
// поиск по ключу (В таблице не может быть двух элементов с одинаковыми значениями ключей.)

char* find(table_t *table, unsigned int key){ // переделать так, чтобы возвращалась таблица
    int res = binsearch\
    (table->ks, &key, table->csize, sizeof(KeySpace), (int (*)(const void*, const void*)) compare_find);
    if (res >= 0) return NULL;
    res = (-1)*(res+1);
    return (table->ks+res)->info;
}
// вывод таблицы в поток
void display(table_t* table){
    printf("Здравствуйте, ваша таблица:\n");
    for (int i=0; i<(table->csize); i++){
        printf("%u %s\n", (table->ks + i)->key, (table->ks)[i].info);
    }
}
// импорт таблицы из текстового

// индивид таск
// удаление из таблицы элементов, заданных диапазоном ключей; в таблице могут отсутствовать
// элементы с ключами, задающими диапазон.

// СКИБИДИ ДОП

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