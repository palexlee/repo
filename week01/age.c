#include <stdio.h>

int main(void) {
	printf("Quel age avez-vous?");
	int age = 0;
	scanf("%d", &age);
	int annee = 2016 - age;
	printf("Vous etes ne en %d.", annee);
	return 0;
}

