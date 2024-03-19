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

// НЕ КОНЧАЕМ РАБОТУ ДО КОНТРОЛ Д

void menus(){
    printf("\nВыберете опцию\n");
    printf("(1) Создать новую таблицу\n");
    printf("(2) Вывести таблицу\n");
    printf("(3) Вставить элемент в таблицу\n");
    printf("(4) Удалить элемент из таблицы\n");
    printf("(5) Найти элемент в таблице\n");
    printf("(6) Записать таблицу в текстовый файл\n");
    printf("(7) Получить таблицу из текстового файла\n");
    printf("(8) Индивидуальное задание (удалить элементы в диапозоне ключей\n");
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
    void* ret;
    unsigned int key;
    char* info;
    int res;
    char* filename = NULL;
    int size;
    table_t* table = NULL;
    menus();
    #ifdef MAIN_TASK
    while ((choice = better_getchar()) != EOF){
        switch(choice){
            case '1':
                free_table(table);
                printf("Введите размер таблицы: ");
                res = custom_int_input(&size, o_n_and_0);
                if (res == -1){
                    return 0;
                }
                table = get_table(size);
                break;
            case '2':
                display(table);
                break;
            case '3':
                res = ask_elem(&info, &key);
                if (res == -1) return eXXit(GOOD, table, filename);
                res = insert(table, info, key);
                if (res == NO_TABLE) {
                    free(info);
                    printf("Нет таблицы!!\n");
                }
                if (res == KEY_EXIST) printf("Элемент с таким ключем уже есть!\n");
                if (res == TABLE_OVERFLOW) printf("Таблица переполнена!\n");
                break;
            case '4':
                res = ask_key(&key);
                if (res == -1) return eXXit(GOOD, table, filename);
                res = delete(table, key);
                if (res == ELEM_NOT_FOUND) printf("Элемент не найден.\n");
                else printf("Элемент удален.\n");
                break;
            case '5':
                res = ask_key(&key);
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
                res = to_text(table, filename);
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                else printf("Таблица записана\n");
                break;
            case '7':
                free(filename);
                filename = readline("Введите имя файла, из кторого взять таблицу: ");
                if (filename == NULL) return eXXit(GOOD, table, filename);
                res = from_text(&table, filename);
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                else if (res == FORMAT_ERROR)
                {
                    printf("Ошибка формата данных\n");
                }
                else printf("Таблица записана\n");
                break;
            case '8':
                int highest, lowest;
                printf("Введите нижний ключ: ");
                res = custom_int_input(&lowest, only_negative);
                if (res == -1) return eXXit(GOOD, table, filename);
                printf("Введите верхний ключ: ");
                res = custom_int_input(&highest, only_negative);
                if (res == -1) return eXXit(GOOD, table, filename);
                while (highest < lowest){
                    printf("Неправильный верхний ключ!\n");
                    printf("Введите верхний ключ: ");
                    res = custom_int_input(&highest, only_negative);
                    if (res == -1) return eXXit(GOOD, table, filename);
                }
                delete_interval(table, highest, lowest);
                break;
            default:
                printf("NIECHEGO\n");
        }
        menus();
    }
    #elif DOP_TASK
    while ((choice = better_getchar()) != EOF){
        switch(choice){
            case '1':
                free_table(table);
                printf("Введите размер таблицы: ");
                res = custom_int_input(&size, o_n_and_0);
                if (res == -1){
                    return 0;
                }
                table = get_table(size);
                break;
            case '2':
                display(table);
                break;
            case '3':
                res = ask_elem(&info, &key);
                if (res == -1) return eXXit(GOOD, table, filename);
                res = insert(table, info, key);
                if (res == KEY_EXIST) printf("Элемент с таким ключем уже есть!\n");
                if (res == TABLE_OVERFLOW) printf("Таблица переполнена!\n");
                break;
            case '4':
                res = ask_key(&key);
                if (res == -1) return eXXit(GOOD, table, filename);
                res = delete(table, key);
                if (res == ELEM_NOT_FOUND) printf("Элемент не найден.\n");
                else printf("Элемент удален.\n");
                break;
            case '5':
                res = ask_key(&key);
                if (res == -1) return eXXit(GOOD, table, filename);
                iterator_t iter;
                iter = find(table, key);
                if (iter_compare(iter, null_iter(table))) printf("Элемент не найден.\n");
                else {
                    print_found(iter);
                }
                break;
            case '6':
                free(filename);
                filename = readline("Введите имя файла, в который нужно поместить таблицу: ");
                if (filename == NULL) return eXXit(GOOD, table, filename);
                res = to_text(table, filename);
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                else printf("Таблица записана\n");
                break;
            case '7':
                free(filename);
                filename = readline("Введите имя файла, из кторого взять таблицу: ");
                if (filename == NULL) return eXXit(GOOD, table, filename);
                res = from_text(&table, filename);
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                else if (res == FORMAT_ERROR)
                {
                    printf("Ошибка формата данных\n");
                }
                else printf("Таблица записана\n");
                break;
            case '8':
                int highest, lowest;
                printf("Введите нижний ключ: ");
                res = custom_int_input(&lowest, only_negative);
                if (res == -1) return eXXit(GOOD, table, filename);
                printf("Введите верхний ключ: ");
                res = custom_int_input(&highest, only_negative);
                if (res == -1) return eXXit(GOOD, table, filename);
                while (highest < lowest){
                    printf("Неправильный верхний ключ!\n");
                    printf("Введите верхний ключ: ");
                    res = custom_int_input(&highest, only_negative);
                    if (res == -1) return eXXit(GOOD, table, filename);
                }
                delete_interval(table, highest, lowest);
                break;
            default:
                printf("NIECHEGO\n");
        }
        menus();
    }
    #endif
    return eXXit(GOOD, table, filename);
}