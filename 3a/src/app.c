#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
// #include "../library/src/stacklib.h"
#include "../library/src/basic.h"
#include "../library/table.h"

#define GOOD 0
#define FORMAT_ERROR 1
#define STACK_OVERFLOW 2
#define IMPOSSIBLE 3
#define HUGO_FORMULA 4
#define END_INPUT -1

void clean_buff(){
    while (getchar() != '\n');
}

int eXXit(int mistake){
    return mistake;

}

// НЕ КОНЧАЕМ РАБОТУ ДО КОНТРОЛ Д

int main(){
    //menus();
    switch(better_getchar()){
        break;
    }
    return 0;
}