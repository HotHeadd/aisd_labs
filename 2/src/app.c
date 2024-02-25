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

int fill_stack(stack_t* stack){ // отмечены места для вывода стека на экран
    char symbol;
    int res;
    int count=1;//
    char* printable = NULL;//
    printf("Введите формулу в постфиксной нотации\n-> ");
    while ((symbol = getchar()) != '\n'){
        if (symbol == EOF) return -1;
        if ((symbol == ' ') || (symbol == '\t')) continue;
        if (check_symbol(symbol) == 0) return 1;
        count++;//
        printable = realloc(printable, count*sizeof(char));//
        printable[count-2] = symbol;//
        res = push(stack, symbol);
        if (res) {
            free(printable);//
            return 2;
        }
    }
    printable[count-1] = '\0';//
    printf("Введенная фомула (постфиксная нотация):\n");//
    printf("\"%s\"\n", printable);//
    free(printable);
    return 0;
}

char* read_stack(stack_t* stack){
    int res;
    char symbol;
    char* result;
    char* left;
    char* right;
    char* sred;
    res = pop(stack, &symbol);
    if (res == -1) return "Wrong";
    sred = calloc(2, sizeof(char));
    sred[0] = symbol;
    if (isznak(symbol) == 0) return sred;
    left = read_stack(stack);
    if (left == "Wrong"){
        free(sred);
        free(left);
        return "Wrong";
    }
    right = read_stack(stack);
    if (right == "Wrong"){
        free(result);
        return "Wrong";
    }
    result = calloc(1+strlen(left)+1+strlen(right)+2, sizeof(char));
    result[0] = '(';
    strcat(result, right);
    strcat(result, sred);
    strcat(result, left);
    strcat(result, ")");
    free(left);
    free(right);
    free(sred);
    return result;
}

int main(){
    int res=0, size;
    char* result;
    stack_t* stack = get_stack();
    if (stack == NULL) return 0;
    while ((res = fill_stack(stack)) != -1){
        // обработка ввода и ошибок
        if (res > 0){
            if (res == 1) printf("Ошибка формата ввода\n");
            if (res == 2) printf("Стек слишком маленький\n");
            clean_buff();
        }
        else{
            // вывод
            result = read_stack(stack);
            if ((result == "Wrong") || (check_stack(stack) != EOF)){
                printf("Вы ввели невозможную формулу!\n");
            }
            else{
                printf("Формула в инфиксном представлении:\n");
                printf("%s\n", result);
            }
            if (result != "Wrong") free(result);
        }
        free_stack(stack);
        stack = get_stack();
        if (stack == NULL) break;
    }
    printf("Выхожу...\n");
    if (stack != NULL) free_stack(stack);
    return 0;
}