#include <stdio.h>
#include <math.h>

int main(void) {
	double s0 = -1;
	do {
		printf("emprunt (>= 0) ? ");
		scanf("%lf", &s0);
	} while(s0 < 0);

	double r = -1;
	do {
		printf("remboursement (> 0) ? ");
		scanf("%lf", &r);
	} while(r <= 0);

	double ir = -1;
	do {
		printf("taux d'intérêt (0 <= ir < 1) ? ");
		scanf("%lf", &ir);
	} while(ir >= 1 || ir < 0);

	double s = s0;
	int mois = 0;
	double interet = 0.0;
	while(s > 0) {
		mois++;
		double i = ir * s;
		interet += i;
		s -= r;
	} 

	printf("Somme des intérêts encaissés : %lf (sur %d mois)\n.", interet, mois);
	return 0;
}