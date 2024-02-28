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

int eXXit(int mistake, stack_t* stack, char* symbol){
    char* topop;
    if ((mistake > 0) && (mistake < 4)) clean_buff();
    free(symbol);
    while (pop(stack, &topop) != -1) free(topop);
    return mistake;

}

int process(stack_t* stack, char** result){
    char* symbol = calloc(2, sizeof(char));
    char* left, *right, *final=NULL;
    int res;
    printf("Введите формулу в постфиксной нотации\n-> ");
    while ((symbol[0] = getchar()) != '\n'){
        if (symbol[0] == EOF) {
            return eXXit(-1, stack, symbol);
        }
        if ((symbol[0] == ' ') || (symbol[0] == '\t')) continue;
        if (check_symbol(symbol[0]) == 0){
            return eXXit(1, stack, symbol);
        }
        if (isznak(symbol[0]) == 0){
            res = push(stack, symbol);
            if (res == 1) {
                return eXXit(2, stack, symbol);
            }
        }
        else{
            res = pop(stack, &right);
            if (res == -1){
                return eXXit(3, stack, symbol);
            }
            res = pop(stack, &left);
            if (res == -1){
                free(right);
                return eXXit(3, stack, symbol);
            }
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
    res = pop(stack, &left);
    if (res == -1){
        *result = calloc(1, sizeof(char));
        return eXXit(0, stack, symbol);
    }
    if (check_stack(stack) != NULL){    
        free(left);
        return eXXit(4, stack, symbol);
    }
    else *result = left;
    return eXXit(0, stack, symbol);
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
            if (res > 2) printf("Вы ввели невозможную формулу!\n");
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