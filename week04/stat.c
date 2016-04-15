#include <stdio.h>
#include <string.h>

FILE* demander_fichier();

size_t taille;

typedef unsigned long int Statistique[taille];

int main(void) {
	FILE* file = demander_fichier();
	fclose(file);
	return 0;
}

FILE* demander_fichier() {
	FILE* file = NULL;
	char nom[FILENAME_MAX+1];
	int i = 3;
	int valid = 0;

	while (i > 0 && file == NULL) {
		i -= 1;
		valid = 1;
		printf("Nom du fichier à lire : ");
		fgets(nom, FILENAME_MAX, stdin);
		int len = strlen(nom)-1;
		nom[len] = '\0';
		file = fopen(nom, "r");
		if(file == NULL) {
			fprintf(stderr, "-> ERREUR, je ne peux pas lire le fichier %s\n", nom);
			valid = 0;
		}
	}

	if (valid == 0) {
		printf("=> j'abandonne\n");
	}
	return file;
}