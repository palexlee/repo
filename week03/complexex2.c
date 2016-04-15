#include <stdio.h>
#include <math.h>

typedef struct {
	double re;
	double im;
} Complexe;

typedef struct {
	Complexe z1;
	Complexe z2;
} Solutions;

void affiche(Complexe z) {
	printf("z = %lf + %lfi\n", z.re, z.im);
}

Complexe addition(Complexe a, Complexe b);

Complexe soustraction(Complexe a, Complexe b);

Complexe multiplication(Complexe a, Complexe b);

Complexe division(Complexe a, Complexe b);

Complexe sqrt(Complexe a);

Solutions resoudre_second_degre(Complexe b, Complexe c);

void affiche2(Solutions s) {
	affiche(s.z1);
	affiche(s.z2);
}

int main(void) {
	Complexe a = {1,0};
	Complexe b = {1,1};
	Complexe c = {0,1};
	Complexe d = {0,2};
	Complexe e = {2, -3};
	Complexe f = {-1, 0};
	Complexe p = {0,0};
	Complexe r = {3, -2};
	Complexe s = {-5, 1};
	affiche2(resoudre_second_degre(p, a));
	affiche2(resoudre_second_degre(r, s));
	affiche(sqrt(f));
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

Complexe sqrt(Complexe a) {
	double x = sqrt((sqrt(a.re*a.re+a.im*a.im) +a.re)/2.0);
	int sign = 1;
	if (a.im < 0) sign = -1;
	double y = sign*sqrt((sqrt(a.re*a.re+a.im*a.im) - a.re)/2.0);
	Complexe c = {x,y};
	return c;
}

Solutions resoudre_second_degre(Complexe b, Complexe c) {
	Complexe quatre_c = {c.re * 4, c.im *4}; 
	Complexe moins_b = {- b.re, - b.im};
	Complexe deux_a = {2, 2};

	Complexe delta = sqrt(soustraction(multiplication(b,b), quatre_c));
	Complexe z1;
	Complexe z2;
	if (delta.re == 0 && delta.im == 0) {
		Complexe p = 
		z1 = division(moins_b, deux_a);
		z2 = z1;
	} else {
		z1 = division(addition(moins_b, delta), deux_a);
		z2 = division(soustraction(moins_b, delta), deux_a);
	}
	Solutions s = {z1, z2};
	return s;
}