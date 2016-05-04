#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_FUNCTION 5
#define MAX_NAME 10

typedef int (*function)(double*, double*);

int quit(double* a, double* b) {
	printf("Bye!\n");
	return 1;
}

int pop(double* r1, double* r2) {
	*r1= *r2;
	return 0;
}

int push(double* r1, double* r2) {
	double d;
	int j = 0;
	do {
		printf("Valeur ? ");
		j = scanf("%lf", &d);
		if(j != 1) {
			while(!ferror(stdin) && !feof(stdin) && getc(stdin) != '\n');
		}
	} while (!ferror(stdin) && !feof(stdin) && j!= 1);

	pop(r2, r1);
	*r1 = d;
	return 0;
}

int add(double* r1, double* r2) {
	*r1 += *r2;
	return 0;
}

int print(double* r1, double* r2) {
	printf("-> %.1lf\n", *r1);
	return 0;
}

function interprete(const char* name) {
	if(strncmp("quit", name, MAX_NAME) == 0) {
		return quit;
	}

	if(strncmp("pop", name, MAX_NAME) == 0) {
		return pop;
	}

	if(strncmp("push", name, MAX_NAME) == 0) {
		return push;
	}

	if(strncmp("print", name, MAX_NAME) == 0) {
		return print;
	}

	if(strncmp("add", name, MAX_NAME) == 0) {
		return add;
	}

	return quit;
}

int main(void) {

	int q = 0;
	double reg[2] = {0.0, 0.0};

	while(q == 0) {
		char name[MAX_NAME]; 
		printf("Entrez une commande (print, add, push, pop, quit) : ");
		scanf("%s" , name);

		function f = interprete((const char*) name);
		q = f(&reg[0], &reg[1]);

	}

}