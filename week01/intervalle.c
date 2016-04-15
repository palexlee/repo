#include <stdio.h>

int main(void) {
	double x;
	printf("Entrez un reel : ");
	scanf ("%lf", &x);
	
	if (((!(x < 2)) && (x < 3)) || (!(x < 0 || x == 0) && (x < 1 || x ==1)) || (!(x < -10) && (x < -2 || x == -2))) {
		printf("%lf appartient à I", x);		
	} else {
		printf("%lf n'appartient pas à I", x);		
	}
	return 0;
}
