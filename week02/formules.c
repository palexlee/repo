#include <stdio.h>
#include <math.h>

int main(void) {
	double x;
	printf("Entrez un réel : ");
	scanf("%lf", &x);

	int indef[4];
	double res[4];
	//première fonction
	double e1 = exp(x);
	if (e1 == 1) {
		indef[0] = 1;
	} else {
		res[0] = x/(1-e1);
	}

	//deuxième fonction
	if(x <= 1) {
		indef[1] = 1;
	} else {
		res[1] = x*log(x)*exp(2/(x-1));
	}

	//troisième fonction
	if(x < 8) {
		indef[2] = 1;
	} else {
		res[2] = (-x-sqrt(x*x-8*x))/(2-x);
	}

	//quatrième fonction
	double l = sqrt(x*x - 1/x);
 	double s = sin(x) - x/20;
	if(x == 0 || s < 0 || l < 1) {
		indef[3] = 1;
 	} else {
 		res[3] = sqrt(s * log(l));
 	}

 	for(int i = 0; i < 4; ++i) {
 		if (indef[i] == 1) {
 			printf("Expression indéfinie : %d\n", i+1);
 		} else {
 			printf("res %d = %lf\n", i +1, res[i]);
 		}
 	}
	return 0;
}