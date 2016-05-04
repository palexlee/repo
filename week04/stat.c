#include <stdio.h>
#include <string.h>

#define NB_DEMANDES 3
#define TAILLE 256

unsigned char start = 32;
unsigned char stop = 253;

typedef unsigned long int Statistique[TAILLE];


FILE* demander_fichier();

void initialise_stat(Statistique a_initialiser);

unsigned long int collecte_stat(Statistique a_remplir, FILE* fichier);

void affiche(Statistique a_afficher, unsigned long int total, unsigned short int taille);

int main(void) {
	FILE* file = demander_fichier();
	if(file == NULL) {
		printf("J'abandonne !\n");
		return 1;
	}

	Statistique stat;
	initialise_stat(stat);
	affiche(stat, collecte_stat(stat, file), stop - start + 1);
	fclose(file);
	return 0;
}

FILE* demander_fichier() {
	FILE* file = NULL;
	char nom[FILENAME_MAX+1];
	size_t nb = 0;
	size_t taille_lue = 0;

	do {
		++nb;

		do {
			printf("Nom du fichier à lire : ");
			fgets(nom, FILENAME_MAX, stdin);
			taille_lue = strlen(nom)-1;

			if(taille_lue >= 0 && nom[taille_lue] == '\n') {
				nom[taille_lue] = '\0';
			}
		} while(!feof(stdin) && taille_lue == 0);
		
		if(nom[0] == '\0') {
			return NULL;
		}

		file = fopen(nom, "r");

		if(file == NULL) {
			fprintf(stderr, "-> ERREUR, je ne peux pas lire le fichier %s\n", nom);
		}
	} while (nb < NB_DEMANDES && file == NULL) ;

	return file;
}

void initialise_stat(Statistique stat) {
	for(int i = 0; i < TAILLE; ++i) {
		stat[i] = 0;
	}
}

unsigned long int collecte_stat(Statistique stat, FILE* f) {
	int c = 0;
	unsigned long int nb = 0;

	while((c = getc(f)) != EOF) {
		if( ((unsigned char) c) >= start && ((unsigned char) c) <= stop) {
			++stat[c- start];
			++nb;
		}
	}
	return nb;
}

void affiche(Statistique stat, unsigned long int nb, unsigned short int taille) {

	if(nb == 0) {
		for(int i = 0; i < taille; ++i) {
			nb += stat[i];
		}
	}

	printf("STATISTIQUES :\n");
	for(int i = 0; i < taille; ++i) {
		if(stat[i] != 0) {
			printf("%c - %10lu - %6.2f%%\n", (char) (i+start), stat[i], 100.0 * stat[i] / (double) nb);
		}
	}
}