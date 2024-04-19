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
