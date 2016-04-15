#include <stdio.h>

#define DIM 10

#define REMPLI '#'
#define VIDE '.'

typedef char Grille[DIM][DIM];

int remplitGrille(Grille grille, size_t ligne, size_t colonne, char direction, size_t longueur);

typedef struct {
	int ligne;
	int colonne;
	char direction;
	int longueur;
} Donnee;

Donnee lire(void);

enum Direction {N = 'N', S = 'S', E = 'E', O = 'O'};

void dessiner(Grille grille, size_t ligne, size_t colonne);

int main(void) {
	Grille grille;
	for(int i = 0; i < DIM; ++i) {
		for(int j = 0; j < DIM; ++j) {
			grille[i][j] = VIDE;
		}
	}
	Donnee d;
	d.longueur = 0;
	do {
		d = lire();
		if(d.longueur >= 0) {
			int s = remplitGrille(grille, d.ligne, d.colonne, d.direction, d.longueur);
			char* c = "";
			if (s == 1) {
				c = "succès";
			} else {
				c = "ECHEC";
			}
			printf("Placement en (%d,%d) direction %c longheur %d -> %s\n", d.ligne, d.colonne, d.direction, d.longueur, c);
		}
	} while (d.longueur >= 0);

	dessiner(grille, DIM, DIM);
}

int remplitGrille(Grille grille, size_t ligne, size_t colonne, char direction, size_t longueur) {
	int valid = 1;
	int si = 0;
	int sj = 0;
	int fi = 0;
	int fj = 0;
	switch(direction) {
		case N :
			if (ligne - longueur +1 < 0) {
				valid = 0;
			} else {
				si = ligne - longueur +1;
				fi = ligne;
				sj = colonne;
				fj = colonne;
			}
			break;
		case S : 
			if (ligne + longueur -1 >= DIM) {
				valid = 0;
			} else {
				si = ligne;
				fi = ligne + longueur -1;
				sj = colonne;
				fj = colonne;
			}
			break;
		case E :
			if (colonne + longueur -1 >= DIM) {
				valid = 0;
			} else {
				si = ligne;
				fi = ligne;
				sj = colonne;
				fj = colonne + longueur -1;
			}
			break;
		case O :
			if (ligne - longueur + 1< 0) {
				valid = 0;
			} else {
				si = ligne;
				fi = ligne;
				sj = colonne - longueur + 1;
				fj = colonne;
			}
			break;
		default :;
	}
	if (valid != 0) {
		for (int i = si; i <= fi; ++i) {
			for(int j = sj; j <= fj; ++j) {
				if (grille[i][j] == REMPLI) {
					valid = 0;
				}
			}
		}
	}

	if (valid != 0) {
		for (int i = si; i <= fi; ++i) {
			for(int j = sj; j <= fj; ++j) {
				grille[i][j] = REMPLI;
			}
		}
	}
	return valid;
	
}

void dessiner(Grille grille, size_t ligne, size_t colonne) {
	for(int i = 0; i < DIM; ++i) {
		for(int j = 0; j < DIM; ++j) {
			printf("%c ",grille[i][j]);
		}
		printf("\n");
	}
}

Donnee lire(void) {
	Donnee d;
	printf("Entrez taille : ");
	scanf("%d", &d.longueur);
	if (d.longueur >= 0) {
		do {
			printf("Entrez coord. x : ");
			scanf("%d", &d.ligne);
		} while(d.ligne > DIM-1 || d.ligne < 0);
		do {
			printf("Entrez coord. y : ");
			scanf("%d", &d.colonne);
		} while(d.colonne > DIM-1 || d.colonne < 0);
		do {
			printf("Entrez direction (N, S, E, O) : ");
			scanf(" %c", &d.direction);
		} while(d.direction != N && d.direction != S && d.direction != E && d.direction != O);
	}
	return d;
}