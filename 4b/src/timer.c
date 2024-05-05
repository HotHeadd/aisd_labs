#include "../library/src/tree.h"
#include "../library/src/basic.h"
#include "../library/src/tree_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

char rchar(){
    char c = (char)rand()%256;
    return c;
}

char* get_key(){
    int size = rand()%100;
    char* key = calloc(size+1, sizeof(char));
    for (int i=0; i < size; i++){
        key[i] = (char)(rand()%26+97);
    }
    return key;
}

void fill_tree(Tree* tree, int elems){
    char* key;
    unsigned info;
    int res;
    for (int j = 0; j<elems; j++){
        key = get_key();
        info = (unsigned)rand();
        res = insert(tree, key, info);
        if (res == KEY_EXIST) free(key);
    }
}

double timer(int func, int elems){
    double time_sum = 0;
    clock_t start, end;
    Tree* tree = get_tree();
    char* key;
    unsigned info;
    int res;
    int repeats = 20;
    for (int i=0; i<repeats;i++){
        fill_tree(tree, elems);
        if (func == 0){
            for (int j=0; j<100;j++){
                key = get_key();
                info = (unsigned)rand();
                start = clock();
                res = insert(tree, key, info);
                end = clock();
                if (res == KEY_EXIST) free(key);
                time_sum += (double) (end - start);
            }
        }
        if (func == 1){
            for (int j=0; j<100;j++){
                key = get_key();
                start = clock();
                int found;
                find(tree, key, &found);
                end = clock();
                free(key);
                time_sum += (double) (end - start);
            }
        }
        if (func == 2){
            for (int j=0; j<100;j++){
                key = get_key();
                start = clock();
                delete(tree, key);
                end = clock();
                free(key);
                time_sum += (double) (end - start);
            }
        }
        if (func == 3){
            for (int j=0; j<100;j++){
                FILE* filler = fopen("filler.txt", "w");
                start = clock();
                traversal(tree, filler, get_key(), get_key());
                end = clock();
                fclose(filler);
                time_sum += (double) (end - start);
            }
        }
        if (func == 4){
            for (int j=0; j<100;j++){
                key = get_key();
                start = clock();
                special_find(tree, key);
                end = clock();
                free(key);
                time_sum += (double) (end - start);
            }
        }
        free_tree(tree, 0);
    }
    free_tree(tree, 1);
    return time_sum / repeats / CLOCKS_PER_SEC; 
}

int main(){
    printf("Transfer res to python diagram folder? (y/n) ");
    char mode = better_getchar();
    srand(time(NULL));
    int elems;
    double time_sum;
    char* filename;
    int mul = 10000;
    mkdir("testres", 0700);
    for (int func=0; func<5; func++){
        if (func == 0) filename = "testres/insert.txt";
        if (func == 1) filename = "testres/find.txt";
        if (func == 2) filename = "testres/delete.txt";
        if (func == 3) filename = "testres/traversal.txt";
        if (func == 4) filename = "testres/specfind.txt";
        FILE* input = fopen(filename, "w");
        fclose(input);
        for (int i=1; i<=20; i++){
            elems = i*mul;
            if (func == 3) elems /= 100;
            printf("Func %d gdata %d elems %d\n", func, i, elems);
            time_sum = timer(func, elems);
            FILE* input = fopen(filename, "a");
            fprintf(input, "%d %.4lf\n", elems, time_sum*1000);
            fclose(input);
        }
        if (func == 3) remove("filler.txt");
        printf("Done func %d\n", func);
    }
    if (mode == 'y'){
        system("cp -r testres/* ~/working/graphics/testres/");
    }
}