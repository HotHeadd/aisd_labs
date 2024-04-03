#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "../library/src/basic.h"
#include "../library/src/table.h"

void clean_buff(){
    while (getchar() != '\n');
}

int eXXit(int mistake, table_t* table, char* filename){
    printf("Выхожу...\n");
    free_table(table);
    free(filename);
    return mistake;

}

int ask_key(unsigned *key){
    printf("Введите ключ: ");
    int res = custom_int_input(key, o_n_and_0);
    if (res == -1) return END_INPUT;
    return GOOD;
}


int ask_elem(unsigned* key, unsigned* info){
    printf("Введите ключ: ");
    int res = custom_int_input(key, o_n_and_0);
    if (res == -1) return END_INPUT;
    printf("Введите значение: ");
    res = custom_int_input(info, o_n_and_0);
    if (res == -1) return END_INPUT;
    return GOOD;
}


// НЕ КОНЧАЕМ РАБОТУ ДО КОНТРОЛ Д

void menus(){
    printf("\nВыберете опцию\n");
    printf("(1) Создать новую таблицу\n");
    printf("(2) Вывести таблицу\n");
    printf("(3) Вставить элемент в таблицу\n");
    printf("(4) Удалить элемент из таблицы\n");
    printf("(5) Найти элемент в таблице\n");
    printf("(6) Записать таблицу в бинарный файл\n");
    printf("(7) Получить таблицу из бинарного файла\n");
    printf("(8) Индивидуальное задание 1 -- поиск по ключу или версии\n");
    printf("(9) Индивидуальное задание 2 -- реорганизация таблицы\n");
    printf("--> ");
}

int main(){
    char choice;
    void* ret;
    unsigned key;
    unsigned info;
    int res;
    char* filename = NULL;
    int size;
    table_t* table = NULL;
    menus();
    while ((choice = better_getchar()) != EOF){
        switch(choice){
            case '1':
                free_table(table);
                printf("Введите размер таблицы: ");
                res = custom_int_input(&size, only_negative);
                if (res == -1){
                    return 0;
                }
                table = get_table(size);
                break;
            case '2':
                display(table);
                break;
            case '3':
                res = ask_elem(&key, &info);
                if (res == -1) return eXXit(GOOD, table, filename);
                res = insert(&table, info, key);
                if (res == NO_TABLE) printf("Таблицы нет!\n");
                break;
            case '4':
                res = ask_key(&key);
                if (res == -1) return eXXit(GOOD, table, filename);
                res = delete(table, key);
                if (res != GOOD){
                if (res == ELEM_NOT_FOUND) printf("Элемент не найден.\n");
                if (res == NO_TABLE) printf("Таблицы нет!\n");
                }
                else printf("Элемент удален.\n");
                break;
            case '5':
                //res = ask_key(&key);
                if (res == -1) return eXXit(GOOD, table, filename);
                ret = find(table, key);
                if (ret == NULL) printf("Элемент не найден.\n");
                else {
                    print_found(ret);
                    free_elem(ret);
                }
                break;
            case '6':
                free(filename);
                filename = readline("Введите имя файла, в который нужно поместить таблицу: ");
                if (filename == NULL) return eXXit(GOOD, table, filename);
                res = to_binary(table, filename);
                if (res != GOOD){
                if (res == NO_TABLE) printf("Таблицы нет!\n");
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                }
                else printf("Таблица записана\n");
                break;
            case '7':
                free(filename);
                filename = readline("Введите имя файла, из кторого взять таблицу: ");
                if (filename == NULL) return eXXit(GOOD, table, filename);
                //res = from_text(&table, filename);
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                else if (res == FORMAT_ERROR)
                {
                    printf("Ошибка формата данных\n");
                }
                else printf("Таблица записана\n");
                break;
            case '8':
                // indie
                break;
            default:
                printf("Нет такой опции в меню!\n");
        }
        menus();
    }
    return eXXit(GOOD, table, filename);
}