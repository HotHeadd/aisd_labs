#include <stdio.h>
#include "basic.h"
#include <stdlib.h>
#include <math.h>
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
	return retu;}

int InputArray(int **poin){
	printf("Input array length (only positive length): ");
	int len=0, retu = custom_int_input(&len, only_negative);
	if (retu==-1) return -1;
	int* data = (int*)malloc((len)*sizeof(int));
	if (data != NULL) *poin = data;
	else return -2;
	for (int i=0; i<len;i++){
		printf("Input array elem: ");
		retu = custom_int_input(*poin+i, always_false);
		if (retu==-1) return -1;
	}
	return len;
}

int OutputArray(int *data, int len){
	printf("[");
	for (int i=0; i < len; i++){
		printf("%d", *(data+i));
		if (i != (len-1)) printf(", ");
	}
	printf("]\n");
	return 0;
}

char better_getchar(){
	char buk=0, tras=0;
	int retu = scanf("%c", &buk);
	scanf("%c", &tras);
	while (tras != '\n'){
		if (retu==-1) return EOF;
		while (tras != '\n') scanf("%c", &tras);
		printf("Please, try again: ");
		buk = getchar(); tras = getchar();
	}
	return buk;
}
