#include <stdio.h>

int main(void) {
	int x = 0;
	double y = 0;
	x = 2;
	y = 4;
	
	double a = 0.0;
	double b = 0.0;
	double c = 0.0;
	double d = 0.0;
	a = x + y;
	b = x - y;
	c = x * y;
	d = x / y;
	
	printf("somme: %lf", a);
	printf("difference: %lf", b);
	printf("produit: %lf", c);
	printf("quotient: %lf", d);
	return 0;
}
