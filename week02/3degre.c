#include <stdio.h>
#include <math.h>

int main(void) {
	double triple(double q, double a2, double angle);

	double a0;
	double pi = 3.1415;
	printf("Valeur a0 ? ");
	scanf("%lf", &a0);
	double a1;
	printf("Valeur a1 ? ");
	scanf("%lf", &a1);
	double a2;
	printf("Valeur a2 ? ");
	scanf("%lf", &a2);

	double q = (3*a1 - a2*a2)/9;
	double r = (9*a1*a2-27*a0-2*a2*a2*a2)/54;
	double d = q*q*q + r*r;

	if (d < 0) {
		double theta = acos(r/sqrt(-q*q*q));
		for(int i = 0; i < 3; ++i) {
			double z = triple(q, a2, (theta + i*2*pi)/3.0);
			printf("z%d = %lf\n", i+1, z);
		}
	} else {
		double s;
		double t;
		double x = r + sqrt(d);
		double y = r - sqrt(d);
		if (x < 0) {
			s = - pow(-x, 1.0/3.0);
		} else {
			s = pow(x, 1.0/3.0);
		}
		if (y < 0) {
			t = - pow(-y, 1.0/3.0);
		} else {
			t = pow(y, 1.0/3.0);
		}

		double z1 = -1.0/3.0*a2 + (s+t);
		printf("z1 = %lf\n", z1);
		if (d == 0 && s+t != 0) {
			double z2 = -1.0/3.0*a2-1.0/2.0*(s+t);
			
			printf("z2 = %lf\n", z2);
		}

	}
	return 0;
}

double triple (double q, double a2, double angle) {
	return 2*sqrt(-q)*cos(angle)-1.0/3.0*a2;
}