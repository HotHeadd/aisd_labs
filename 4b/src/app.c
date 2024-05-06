#include <stdio.h>
#include <stdlib.h>
#include "../library/src/basic.h"
#include "../library/src/tree.h"
#include "../library/src/tree_io.h"
#include "dop.h"

int eXXit(int mistake, Tree* tree, char* filename, char* word){
    printf("Выхожу...\n");
    free_tree(tree, 1);
    free(filename); 
    free(word);
    return mistake;
}

void menus(){
    printf("\nВыберете опцию\n");
    printf("(1) Вывести дерево (в консоль)\n");
    printf("(2) Вывести дерево (графический)\n");
    printf("(3) Вставить элемент в дерево\n");
    printf("(4) Удалить элемент из дерева\n");
    printf("(5) Поиск в дереве по ключу\n");
    printf("(6) Специальный поиск (минимально отличается от заданного)\n");
    printf("(7) Обход дерева (в прямом порядке, вне заданного диапозона)\n");
    printf("(8) Записать дерево в текстовый файл\n");
    printf("(9) Получить дерево из текстового файла\n");
    printf("(d) Доп. задание (вывод номеров строк для слова в файле)\n");
    printf("--> ");
}

char* ask_key(char* prompt){
    char* key;
    key = g_readline(prompt);
    if (key == NULL) return NULL;
    return key;
}

int ask_elem(char** key, unsigned* info){
    char* keyin;
    int res;
    *key = g_readline("Введите ключ: ");
    if (*key == NULL) return END_INPUT;
    printf("Введите значение: ");
    res = custom_int_input(info, o_n_and_0);
    if (res == -1) return END_INPUT;
    return GOOD;
}

int main(){
    char choice;
    char* key;
    unsigned info;
    int res = 0;
    char* filename = NULL, *word = NULL;
    Tree* tree = get_tree();
    Node* found;
    menus();
    while ((choice = better_getchar()) != EOF){
        switch(choice){
            case '1':
                print_tree(tree);
                break;
            case '2':
                print_gv(tree);
                break;
            case '3':
                res = ask_elem(&key, &info);
                if (res == -1) return eXXit(GOOD, tree, filename, word);
                res = insert(tree, key, info);
                if (res == GOOD) printf("Элемент вставлен.\n");
                if (res == KEY_EXIST){
                    free(key);
                    printf("Ключ существует. Вставлен дубликат\n");
                }
                if (res == ROOT_CREATED) printf("Дерево создано и вставлен элемент.\n");
                break;
            case '4':
                key = ask_key("Введите ключ: ");
                if (key == NULL) return eXXit(GOOD, tree, filename, word);
                res = delete(tree, key);
                free(key);
                if (res == GOOD) printf("Элемент удален.\n");
                if (res == MULTIPLE_DATA){
                    printf("Несколько элементов по этому ключу. Удален старейший дубликат\n");
                }
                if (res == ELEM_NOT_FOUND) printf("Элемента нет в дереве.\n");
                break;
            case '5':
                key = ask_key("Введите ключ: ");
                if (key == NULL) return eXXit(GOOD, tree, filename, word);
                found = find(tree, key, &res);
                free(key);
                if (res) print_found(found);
                else printf("Элемент не найден.\n");
                break;
            case '6':
                key = ask_key("Введите ключ: ");
                if (key == NULL) return eXXit(GOOD, tree, filename, word);
                found = special_find(tree, key);
                free(key);
                if (found != NULL) print_found(found);
                if (found == NULL) printf("Пустое дерево.\n");
                break;
            case '7':
                char* bottom = ask_key("Введите нижнее значение: ");
                char* top = ask_key("Введите верхнее значение: ");
                traversal(tree, stdout, bottom, top);
                free(top);
                free(bottom);
                break;
            case '8':
                free(filename);
                filename = g_readline("Введите имя файла, в который нужно поместить дерево: ");
                if (filename == NULL) return eXXit(GOOD, tree, filename, word);
                res = tree_to_txt(tree, filename);
                if (res == GOOD) printf("Дерево записано\n");
                if (res == NO_TREE) printf("Дерева нет нет!\n");
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                break;
            case '9':
                free(filename);
                filename = g_readline("Введите имя файла, из которого нужно взять дерево: ");
                if (filename == NULL) return eXXit(GOOD, tree, filename, word);
                res = tree_from_txt(tree, filename);
                if (res == GOOD) printf("Дерево считано\n");
                if (res == FILE_ERROR) printf("Ошибка файла\n");
                if (res == FORMAT_ERROR) printf("Ошибка формата данных\n");
                break;
            case 'd':
                word = NULL;
                filename = g_readline("Введите имя файла (нажмите enter если брать из прошлого): ");
                if (filename == NULL) return eXXit(GOOD, tree, filename, word);
                word = g_readline("Введите искомое слово: ");
                if (word == NULL) return eXXit(GOOD, tree, filename, word);
                unsigned* vector;
                int amount = extra(filename, word, &vector, &tree);
                if (amount == -1){
                    printf("Ошибка файла\n");
                }
                if (amount == -2){
                    printf("Такого слова нет в файле!\n");
                }
                if (amount == -3){
                    printf("Нет предыдущего файла\n");
                }
                if (amount > 0){
                    print_vec(vector, amount);
                    free(vector);
                }
                free(filename);
                filename = NULL;
                free(word);
                word = NULL;
                break;
            default:
                printf("Нет такой опции в меню!\n");
        }
        menus();
    }
    return eXXit(GOOD, tree, filename, word);
}