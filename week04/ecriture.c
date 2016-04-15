#include <stdio.h>
#include <string.h>

int main(void) {
	FILE* file = NULL;
	char nom_entree[FILENAME_MAX+1] = "data.dat";

	file = fopen(nom_entree, "a");

	if (file == NULL) {
		fprintf(stderr, "Erreur : impossible de lire le ficheier %s", nom_entree);
	} else {

		#define TAILLE_MAX 10
		char mot[TAILLE_MAX+1];
		int age = 0;

		do {

			printf("Entrez un nom (CTRL+D pour terminer) : ");
			fgets(mot, TAILLE_MAX+1, stdin);
			int len = strlen(mot) -1;
			mot[len] = ' ';
			if (!feof(stdin)) {
				fflush(stdout);
				printf("âge : ");
				int j = scanf("%d", &age);
				if (j == 1 || age < 0) {
					fprintf(file, "%s\t%d\n", mot, age);
				} else {
					printf("Fagget\n");
				}
			}
			while(!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
		} while (!feof(stdin) && !ferror(stdin));
		fclose(file);
	}

	return 0;
}