#include <stdio.h>
#include <math.h>

int main(void) {
	printf("Tables de multiplication\n");
	for(int i = 2; i < 11; ++i) {
		printf("Table de %d\n", i);
		for(int j = 0; j < 11; ++j) {
			printf("%d * %d = %d\n" , j, i, i*j);
		}
	}
	return 0;
}