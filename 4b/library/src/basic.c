#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

int always_false(double x){
	return x && 0;
}

int only_negative(double x){
	return x<=0;
}

int o_n_and_0(double x){
	return x<0;
}

int custom_double_input(double* poin, int (*fun)(double)){
	char tras=0;
	int retu = scanf("%lf", poin);
	scanf("%c", &tras);
	while ((fun(*poin))||(retu<1)||(tras!='\n')){
		if (retu==-1) break;
		while (tras != '\n') scanf("%c", &tras);
		printf("Please, try again: ");
		retu = scanf("%lf", poin);
		scanf("%c", &tras);
	}
	return retu;
}

int custom_int_input(int* poin, int (*fun)(double)){
	char tras=0;
	int retu = scanf("%d", poin);
	scanf("%c", &tras);
	while ((retu<1)||(fun(*poin))||(tras!='\n')){
		if (retu==-1) break;
		while (tras != '\n') scanf("%c", &tras);
		printf("Please, try again: ");
		retu = scanf("%d", poin);
		scanf("%c", &tras);
	}
	return retu;
}
int custom_uns_input(unsigned* poin, int (*fun)(double)){
	char tras=0;
	int retu = scanf("%u", poin);
	scanf("%c", &tras);
	while ((retu<1)||(fun(*poin))||(tras!='\n')){
		if (retu==-1) break;
		while (tras != '\n') scanf("%c", &tras);
		printf("Please, try again: ");
		retu = scanf("%u", poin);
		scanf("%c", &tras);
	}
	return retu;
}

char better_getchar(){
	char buk=0, tras=0;
	int retu = scanf("%c", &buk);
	scanf("%c", &tras);
	while (tras != '\n'){
		if (retu==-1) return EOF;
		while (tras != '\n') scanf("%c", &tras);
		printf("Please, try again: ");
		buk = getchar();
		tras = getchar();
	}
	return buk;
}

char* file_readline(FILE* file){ //достаю из широких штанин функцию из 4 лабы
    int s_len, b_len, res = 1, no_action = 1;
    char *str = (char*)calloc(1, sizeof(char));
    char *buff = calloc(5, sizeof(char));
    res = fscanf(file, "%4[^\n]", buff);
    if (res == -1) {free(buff); free(str); return NULL;}
    while (buff[0] && res!= 0){
		no_action = 0;
		if (res == -1) {free(buff); free(str); return NULL;}
		if (str) s_len = strlen(str); else s_len = 0;
		if (buff) b_len = strlen(buff); else b_len = 0;
		str = (char*)realloc(str, (s_len+b_len)*sizeof(char)+1);
		strcat(str, buff);
		*(str+s_len+b_len) = '\0';
		res = fscanf(file, "%4[^\n]", buff);
    }
    if (buff != NULL) {
		free(buff);
	}
    fscanf(file, "%*c");
    if (no_action){
		free(str);
		str = calloc(7, sizeof(char));
		strcat(str, "(null)");
    }
    return str;
}

char* g_readline(const char* prompt){
	int s_len, b_len, res=1, no_action = 1;
	printf("%s", prompt);
	char *str=(char*)calloc(1, sizeof(char));
	char *buff=calloc(5, sizeof(char));
	res = scanf("%4[^\n]", buff);
	if (res == -1) {free(buff); free(str); return NULL;}
	while (buff[0] && res!= 0){
		no_action = 0;
		if (res == -1) return NULL;
		if (str) s_len = strlen(str); else s_len=0;
		if (buff) b_len = strlen(buff); else b_len=0;
		str = (char*)realloc(str, (s_len+b_len)*sizeof(char)+1);
		strcat(str, buff);
		*(str+s_len+b_len) = '\0';
		res = scanf("%4[^\n]", buff);
	}
	if (buff != NULL) free(buff);
	scanf("%*c");
	if (no_action){
		free(str);
		str = calloc(1, sizeof(char));
	}
	return str;
}
