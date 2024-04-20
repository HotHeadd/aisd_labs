#include "../library/src/tree.h"
#include "../library/src/tree_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    char* key;
    unsigned info;
    int elems;
    Node* root = NULL;
    double time_sum;
    clock_t start, end;
    for (int func=0; func<5; func++){
        for (int i=1; i<=20; i++){
            elems = i*1000;
            for (int j = 0; j<elems; j++){
                key = get_key();
                info = get_info();
                insert(&root, key, info);
            }

        }
    }
}