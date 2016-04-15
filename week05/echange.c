#include <stdio.h>

void echange(int* i, int* j);

int main(void) {
	int i = 10;
	int j = 55;

	printf("Avant : i=%d et j=%d\n", i, j);
	echange(&i, &j);
	printf("Après : i=%d et j=%d\n", i, j);
	return 0;
}

void echange(int* i, int*j) {
	int tmp = *i;
	*i = *j;
	*j = tmp;
}