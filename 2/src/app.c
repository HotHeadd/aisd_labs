#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "../library/src/stacklib.h"
#include "../library/src/basic.h"

void clean_buff(){
    while (getchar() != '\n');
}

int isznak(char s){
    return (s == '+') || (s == '-') || (s == '*') || (s == '/');
}

int check_symbol(char s){
    return ((s >= 'a') && (s <= 'z')) || ((s >= 'A') && (s <= 'Z'))\
            || (s == '+') || (s == '-') || (s == '*') || (s == '/');
}


int process(stack_t* stack, char** result){
    char* symbol = calloc(2, sizeof(char));
    char* left, *right, *final;
    int res;
    printf("Введите формулу в постфиксной нотации\n-> ");
    while ((symbol[0] = getchar()) != '\n'){
        if (symbol[0] == EOF) return -1;
        if ((symbol[0] == ' ') || (symbol[0] == '\t')) continue;
        if (check_symbol(symbol[0]) == 0){
            clean_buff();
            return 1;
        }
        if (isznak(symbol[0]) == 0){
            res = push(stack, symbol);
            if (res == 1) {
                clean_buff();
                return 2;
            }
        }
        else{
            res = pop(stack, &right);
            if (res == -1) return 3;
            res = pop(stack, &left);
            if (res == -1) return 3;
            final = calloc(2+strlen(left)+strlen(right)+2, sizeof(char));
            strcat(final, "(");
            strcat(final, left);
            strcat(final, symbol);
            strcat(final, right);
            strcat(final, ")");
            push(stack, final);
            free(left);
            free(right);
            free(symbol);
        }
        symbol = calloc(2, sizeof(char));
    }
    pop(stack, &left);
    if (check_stack(stack) != NULL){
        while (pop(stack, &right) != -1) free(right);
        free(left);
        return 3;
    }
    else *result = left;
    free(symbol);
    return 0;
}

int main(){
    int res=0;
    char* result=NULL;
    stack_t* stack = get_stack();
    if (stack == NULL) return 0;
    while ((res = process(stack, &result)) != -1){
        if (res > 0){
            if (res == 1) printf("Ошибка формата ввода\n");
            if (res == 2) printf("Стек слишком маленький\n");
            if (res == 3) printf("Вы ввели невозможную формулу!\n");
        }
        else{
            printf("Формула в инфиксном представлении:\n");
            printf("%s\n", result);
        }
        free(result);
        result = NULL;
        free_stack(stack);
        stack = get_stack();
        if (stack == NULL) break;
    }
    free_stack(stack);
    printf("Выхожу...\n");
    return 0;
}