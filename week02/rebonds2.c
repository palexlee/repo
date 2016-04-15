#include <math.h>
#include <stdio.h>

int main(void) {

	double g = 9.81;
	int rebonds = 0;

	double eps = -1;
	
	do {
		printf("coefficient de rebonds ? ");
		scanf("%lf", &eps);
	} while(1 <= eps || 0 > eps);
	double h0 = -1;
	do{
		printf("hauteur initial ? ");
		scanf("%lf", &h0);
	} while(0 > h0);
	double h_fin;
	printf("hauteur de fin désirée ? ");
	scanf("%lf", &h_fin);

	double hauteur = h0;
	do {
		rebonds++;
		double v = eps*sqrt(2*hauteur*g);
		hauteur = v*v/(2*g);
	} while(hauteur > h_fin);

	printf("Nombre de rebonds : %d\n", rebonds);
	return 0;
}