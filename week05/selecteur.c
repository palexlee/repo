#include <stdio.h>

int demander_nombre();

int main(void) {
	double valeur1 = 42;
	double valeur2 = 2.43;
	double valeur3 = 0.0;

	double* choix = NULL;

	int n = demander_nombre();

	switch (n) {
		case 1 :
			choix = &valeur1;
			break;
		case 2 :
			choix = &valeur2;
			break;
		case 3 :
			choix = &valeur3;
			break;
		default: break;
	}

	printf("Vous avez choisi %lf\n", *choix);
}

int demander_nombre() {
	printf("Choisir un nomnbre [1,3] : ");
	int nb = 0;
	do {
		scanf("%d", &nb);
	} while(nb <= 0 || nb > 3);

	return nb;
}