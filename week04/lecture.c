#include <stdio.h>
#include <limits.h>

int main(void) {
	int min = INT_MAX;
	int max = -1;
	int nb = 0;
	double somme = 0.0;
	double moy = 0.0;

	FILE* input = NULL;
	char nom_entree[FILENAME_MAX + 1] = "data.dat";

	input = fopen(nom_entree, "r");

	if(input == NULL) {
		fprintf(stderr, "Erreur : impossible de lire le fichier %s\n", nom_entree);
	} else {
		printf("+-----------------+-----+\n");
		while (!feof(input) && !ferror(input)) {

			char nom[15];
			int age  = 0;
			int j = fscanf(input, "%[^\t]", nom);
			if ( j== 1) {
				fscanf(input, "%d", &age);
				somme += age;
				nb += 1;
				if (age > max) {
					max = age;
				} else if (age < min) {
					min = age;
				}
				printf("| %-15s | %3d |\n", nom, age);
			}
			
			while(!feof(input) && !ferror(input) && getc(input) != '\n');
		}
		moy = somme/nb;
		printf("+-----------------+-----+\n");
		printf("  âge minimum\t: %3d \n", min);
		printf("  âge maximum\t: %3d \n", max);
		printf("%d personnes, âge moyen : %lf\n", nb, moy);
	}

	fclose(input);
	return 0;
}