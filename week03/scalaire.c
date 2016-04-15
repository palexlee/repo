#include <stdio.h>

#define N_MAX 10

typedef double vecteur[N_MAX];

double scalaire(const double u[], const double v[], size_t taille);

void build(vecteur v, int type, size_t taille) {
	for (int i = 0; i < taille; ++i) {
		printf("Entrez v%d_%d : ", type, i);
		scanf("%lf", &v[i]);
	}
}



int main(void) {
	int n = 0;

	vecteur v1;
	vecteur v2;

	do {
		printf("Entrez la taille du tableau (entre 1 et %d) : ", N_MAX);
		scanf("%d", &n);
	} while (n < 1 || n > N_MAX);

	build(v1, 1, n);
	build(v2, 2, n);

	double scal = scalaire(v1, v2, n);
	printf("Le produit scalaire de v1 et v2 = %lf\n", scal);

	return 0;
}

double scalaire(const double u[], const double v[], size_t taille) {
	double sum = 0;
	for (int i  = 0; i < taille; ++i) {
		sum += u[i] * v[i];
	}
	return sum;
}