#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "../library/src/basic.h"
#include "../library/src/table.h"

#define GOOD 0
#define FORMAT_ERROR 1
#define STACK_OVERFLOW 2
#define IMPOSSIBLE 3
#define HUGO_FORMULA 4
#define END_INPUT -1

void clean_buff(){
    while (getchar() != '\n');
}

int eXXit(int mistake, table_t* table){
    free_table(table);
    free(table->ks);
    free(table);
    return mistake;

}

// НЕ КОНЧАЕМ РАБОТУ ДО КОНТРОЛ Д

void menus(){
    printf("Выберете опцию\n");
    printf("(1) Очистить эту таблицу\n");
    printf("(2) Вывести таблицу\n");
    printf("(3) Вставить элемент в таблицу\n");
    printf("-->");
}

int ask_elem(char** info, unsigned int* key){
    printf("Введите ключ: ");
    int res = custom_int_input(key, only_negative);
    if (res == -1) return END_INPUT;
    *info = readline("Введите строку (значение): ");
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
                insert(table, info, key);
                break;
            default:
                printf("GOVNK\n");
        }
        menus();
    }
    return eXXit(GOOD, table);
}