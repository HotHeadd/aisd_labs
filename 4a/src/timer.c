#include "../library/src/tree.h"
#include "../library/src/tree_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

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

void get_tree(Node** root, int elems){
    char* key;
    unsigned info;
    int res;
    for (int j = 0; j<elems; j++){
        key = get_key();
        info = (unsigned)rand();
        res = insert(root, key, info);
        if (res == KEY_EXIST) free(key);
    }
}

double timer(int func, int elems){
    double time_sum = 0;
    clock_t start, end;
    Node* root=NULL;
    char* key;
    unsigned info;
    int res;
    for (int i=0; i<10;i++){
        get_tree(&root, elems);
        if (func == 0){
            for (int j=0; j<100;j++){
                key = get_key();
                info = (unsigned)rand();
                start = clock();
                res = insert(&root, key, info);
                end = clock();
                if (res == KEY_EXIST) free(key);
                time_sum += (double) (end - start);
            }
        }
        if (func == 1){
            for (int j=0; j<100;j++){
                key = get_key();
                start = clock();
                find(root, key);
                end = clock();
                free(key);
                time_sum += (double) (end - start);
            }
        }
        if (func == 2){
            for (int j=0; j<100;j++){
                key = get_key();
                start = clock();
                delete(&root, key);
                end = clock();
                free(key);
                time_sum += (double) (end - start);
            }
        }
        if (func == 3){
            for (int j=0; j<100;j++){
                FILE* filler = fopen("filler.txt", "w");
                start = clock();
                traversal(root, filler, 0);
                end = clock();
                fclose(filler);
                time_sum += (double) (end - start);
            }
        }
        if (func == 4){
            for (int j=0; j<100;j++){
                key = get_key();
                start = clock();
                special_find(root, key);
                end = clock();
                free(key);
                time_sum += (double) (end - start);
            }
        }
        free_tree(root);
        root = NULL;
    }
    return time_sum / 10 / CLOCKS_PER_SEC; 
}

int main(){
    srand(time(NULL));
    int elems;
    double time_sum;
    char* filename;
    mkdir("./testres", 0700);
    for (int func=0; func<5; func++){
        if (func == 0) filename = "testres/insert.txt";
        if (func == 1) filename = "testres/find.txt";
        if (func == 2) filename = "testres/delete.txt";
        if (func == 3) filename = "testres/traversal.txt";
        if (func == 4) filename = "testres/specfind.txt";
        FILE* input = fopen(filename, "w");
        fclose(input);
        for (int i=1; i<=20; i++){
            elems = i*10000;
            if (func == 3) elems /= 10;
            time_sum = timer(func, elems);
            FILE* input = fopen(filename, "a");
            fprintf(input, "%d %.4lf\n", elems, time_sum*1000);
            fclose(input);
        }
        if (func == 3) remove("filler.txt");
        printf("Done func %d\n", func);
    }
}