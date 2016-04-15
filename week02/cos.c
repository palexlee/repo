#include <stdio.h>
#include <math.h>

double factorielle (int k);
double somme_partielle(double x, int N);
int demander_chiffre(void);
double demander_x(void);

int main(void) {
	int N = demander_chiffre();
	double nombre = demander_x();
	double result = somme_partielle(nombre, N);
	printf("cos(%lf) = %lf\n", nombre, result);
	return 0;
}

double factorielle (int k) {
	double res = 0;
	if (k <= 1) {
		res = 1;
	} else {
		res = k * factorielle(k-1);
	}
	return res;
}

double somme_partielle(double x, int N) {
	double res = 0;
	for(int i = 0; i <= N; ++i) {
		double un = 1;
		if (i % 2 != 0) {
			un = -1;
		}
		res += pow(x, 2*i) * un / factorielle(2*i);
	}
	return res;
}

int demander_chiffre(void) {
	int borne = 0;
	do {
		printf("Entrez la valeur N : ");
		scanf("%d", &borne);
	} while(borne <= 0.0);
	return borne;
}

double demander_x(void) {
	double x = 0;
	printf("Entrez la valeur x : ");
	scanf("%lf", &x);
	return x;
}