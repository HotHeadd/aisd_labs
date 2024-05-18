#include <stdio.h>
#include <stdlib.h>
#include "../library/src/basic.h"

// int eXXit(int mistake, Tree* tree, char* filename, char* word){
//     printf("Выхожу...\n");
//     free_tree(tree, 1);
//     free(filename); 
//     free(word);
//     return mistake;
// }

void menus(){
    printf("\nВыберете опцию\n");
    printf("(1) Вывести граф (в консоль)\n");
    printf("(2) Вывести граф (графический)\n");
    printf("(3) Добавить человека (с уникальным именем)\n");
    printf("(4) Добавить новую оценку\n");
    printf("(5) Удалить человека\n");
    printf("(6) Удалить оценку\n");
    printf("(7) Изменить имя человека (оно должно быть уникальным)\n");
    printf("(8) Изменить отношение между людьми\n");
    printf("(t) (Поиск в ширину) Определение круга знакомств через рукопожатия\n");
    printf("(f) (Алгоритм Дейкстры) Поиск пути между людьми по положительным отношениям\n");
    printf("(s) (Алгоритм Флойда-Воршалла) ...\n");
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
    menus();
    char choice;
    while ((choice = better_getchar()) != EOF){
        switch(choice){
            case '1':
                break;
            case '2':
                break;
            case '3':
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
            case '9':
                break;
            default:
                printf("Нет такой опции в меню!\n");
        }
        menus();
    }
    // return eXXit(GOOD, tree, filename, word);
}