#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "../library/src/basic.h"
#include "../library/src/table.h"

void clean_buff(){
    while (getchar() != '\n');
}

int eXXit(int mistake, table_t* table){
    printf("Выхожу...\n");
    free_table(table);
    free(table->ks);
    free(table);
    return mistake;

}

// НЕ КОНЧАЕМ РАБОТУ ДО КОНТРОЛ Д

void menus(){
    printf("\nВыберете опцию\n");
    printf("(1) Очистить эту таблицу\n");
    printf("(2) Вывести таблицу\n");
    printf("(3) Вставить элемент в таблицу\n");
    printf("(4) Удалить элемент из таблицы\n");
    printf("(5) Найти элемент в таблице\n");
    printf("--> ");
}

int ask_elem(char** info, unsigned int* key){
    printf("Введите ключ: ");
    int res = custom_int_input(key, only_negative);
    if (res == -1) return END_INPUT;
    *info = readline("Введите строку (значение): ");
    if (*info == NULL) return END_INPUT;
    return GOOD;
}

int ask_key(unsigned int *key){
    printf("Введите значение ключа: ");
    int res = custom_int_input(key, only_negative);
    if (res == -1) return END_INPUT;
    return GOOD;
}

int main(){
    char choice;
    table_t* table = get_table();
    if (table == NULL) return 0;
    unsigned int key;
    char* info;
    int res;
    menus();
    while ((choice = better_getchar()) != EOF){
        switch(choice){
            case '1':
                free_table(table);
                break;
            case '2':
                display(table);
                break;
            case '3':
                res = ask_elem(&info, &key);
                if (res == -1) return eXXit(GOOD, table);
                res = insert(table, info, key);
                if (res == KEY_EXIST) printf("Элемент с таким ключем уже есть!\n");
                if (res == TABLE_OVERFLOW) printf("Таблица переполнена!\n");
                break;
            case '4':
                res = ask_key(&key);
                if (res == -1) return eXXit(GOOD, table);
                //delete
                break;
            case '5':
                res = ask_key(&key);
                if (res == -1) return eXXit(GOOD, table);
                info = find(table, key);
                if (info == NULL) printf("Элемент не найден.\n");
                else printf("Найденный элемент: \"%s\"\n", info);
                break;
            default:
                printf("NIECHEGO\n");
        }
        menus();
    }
    return eXXit(GOOD, table);
}