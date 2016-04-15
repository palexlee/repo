#include <math.h>
#include <stdio.h>

int main(void) {

	double g = 9.81;

	int nbr;
	printf("nombre de rebonds ? ");
	scanf("%d", &nbr);
	double eps;
	printf("coefficient de rebonds ? ");
	scanf("%lf", &eps);
	double h0;
	printf("hauteur initial ? ");
	scanf("%lf", &h0);

	for (int i = 0; i < nbr; ++i) {
		double v = eps*sqrt(2*h0*g);
		h0 = v*v/(2*g);
	}

	printf("Au %dème rebond, la hauteur sera de %lf m.\n", nbr, h0);
	return 0;
}