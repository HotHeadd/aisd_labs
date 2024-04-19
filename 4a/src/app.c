#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "../library/src/basic.h"
#include "../library/src/tree.h"
#include "../library/src/tree_gr.h"

int eXXit(int mistake, Node* root, char* filename){
    printf("Выхожу...\n");
    free_tree(root);
    free(filename);
    return mistake;
}

void menus(){
    printf("\nВыберете опцию\n");
    printf("(1) Вывести дерево (в консоль)\n");
    printf("(2) Вывести дерево (графический)\n");
    printf("(3) Вставить элемент в дерево\n");
    printf("(4) Удалить элемент из дерева\n");
    printf("(5) Обход дерева (в обратном порядке)\n");
    printf("(6) Поиск в дереве по ключу\n");
    printf("(7) Специальный поиск (максимально отличается от заданного)\n");
    printf("(8) Записать дерево в текстовый файл\n");
    printf("(9) Получить дерево из текстового файла\n");
    printf("--> ");
}

int ask_key(unsigned *key){
    printf("Введите ключ: ");
    int res = custom_int_input(key, o_n_and_0);
    if (res == -1) return END_INPUT;
    return GOOD;
}

int ask_elem(char** key, unsigned*info){
    char* keyin;
    int res;
    *key = readline("Введите ключ: ");
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
    char* filename = NULL;
    Node* root = NULL;
    menus();
    while ((choice = better_getchar()) != EOF){
        switch(choice){
            case '1':
                print_tree(root, 0);
                break;
            case '2':
                break;
            case '3':
                ask_elem(&key, &info);
                if (res == -1) return eXXit(GOOD, root, filename);
                res = insert(&root, key, info);
                if (res == GOOD) printf("Элемент вставлен.\n");
                if (res == KEY_EXIST) printf("Ключ существует. Вставлен дубликат\n");
                if (res == ROOT_CREATED) printf("Дерево создано и вставлен элемент.\n");
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            
            default:
                printf("Нет такой опции в меню!\n");
        }
        menus();
    }
    return eXXit(GOOD, root, filename);
}