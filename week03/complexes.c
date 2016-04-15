#include <stdio.h>

typedef struct {
	double re;
	double im;
} Complexe;

void affiche(Complexe z) {
	printf("z = %lf + %lfi\n", z.re, z.im);
}

Complexe addition(Complexe a, Complexe b);

Complexe soustraction(Complexe a, Complexe b);

Complexe multiplication(Complexe a, Complexe b);

Complexe division(Complexe a, Complexe b);

int main(void) {
	Complexe a = {1,0};
	Complexe b = {1,1};
	Complexe c = {0,1};
	Complexe d = {0,2};
	Complexe e = {2, -3};
	affiche(addition(a, c));
	affiche(multiplication(c, c));
	affiche(multiplication(b, b));
	affiche(division(d, c));
	affiche(division(e, b));
}

Complexe addition(Complexe a, Complexe b) {
	Complexe c;
	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return c;
}

Complexe soustraction(Complexe a, Complexe b) {
	Complexe c;
	c.re = - b.re;
	c.im = - b.im;
	return addition(a, c);
}

Complexe multiplication(Complexe a, Complexe b) {
	Complexe c;
	c.re = a.re*b.re - a.im*b.im;
	c.im = a.re*b.im + a.im*b.re;
	return c;
}

Complexe division(Complexe a, Complexe b) {
	Complexe c;
	c.re = (a.re*b.re+a.im*b.im) / (b.re*b.re + b.im*b.im);
	c.im = (a.im*b.re - a.re*b.im) / (b.re*b.re + b.im*b.im);
	return c;
}