#include <stdio.h>

int demander_nombre(int min, int max);

int main(void) {
	int nombre = demander_nombre(4, 4);
	printf("Votre nombre : %d\n", nombre);
	return 0;
}

int demander_nombre(int min, int max) {
	if (min > max) {
		int tmp = max;
		max = min;
		min = tmp;
	}
	int nombre;
	do {
		printf("Entrez un nombre ");
		if (min == max) {
			printf("plus grand que %d : ", min);
		} else {
			printf(" entre %d et %d : ", min, max);
		}
		scanf("%d", &nombre);
	} while(nombre < min || nombre > max);
	
	return nombre;
}