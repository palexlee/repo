#include <stdio.h>
#include <math.h>

int main(void) {
	int nombre = 0;
	do {
		printf("test nombre premier ? ");
		scanf("%d", &nombre);
	}while(nombre <= 1);

	double sq = sqrt(nombre);

	int premier = 1;
	int diviseur = 0;
	if(nombre != 2 && nombre % 2 == 0) {
		premier = 0;
		diviseur = 2;
	} else {
		int i = 3;
		while(nombre%i != 0 && i <= sq) {
			i += 2;
		}
		if(i <= sq) {
			premier = 0;
			diviseur = i;
		}
	}

	if(premier == 0) {
		printf("Le nombre n'est pas premier, car il est divisible par %d\n", diviseur);
	} else if (premier == 1) {
		printf("Je crois fortement que ce nombre est premier.\n");
	}
	return 0;
}