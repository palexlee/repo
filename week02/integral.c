#include <stdio.h>
#include <math.h>

int demander_borne(int id);

double f(double x);

double integre(int a, int b);

int main(void) {
	int a = demander_borne(0);
	int b = demander_borne(1);
	double res = integre(a,b);
	printf("res = %lf\n", res);
	return 0;
}

int demander_borne(int id) {
	int borne;
	printf("Entrez la borne ");
	if (id == 0) {
		printf("a : ");
	} else {
		printf("b : ");
	}
	scanf("%d", &borne);
	return borne;
}

double f(double x) {
	return sin(x);
}

double integre(int a, int b) {
	double tmp = 41*f(a)+216*f((5*a+b)/6.0)+27*f((2*a+b)/3.0)+272*f((a+b)/2.0)
				+27*f((a+2*b)/3.0)+216*f((a+5*b)/6.0)+41*f(b);
	return tmp * (b-a)/840.0;
}