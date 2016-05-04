#include <stdio.h>
#include <stdlib.h>

#define N 3
#define SIZE_MAX 10

typedef struct {
	int** mat;
	unsigned int ligne;
	unsigned int colonne;
	size_t allocatedX;
	size_t allocatedY;
} Matrice;

Matrice* lire_matrice(Matrice* lue);

Matrice* multiplication(Matrice const* a, Matrice const* b, Matrice* resultat);

int lire_dimension(const char* type);

void affiche_matrice(Matrice const* m);

void push_matrice(Matrice* m, size_t x, size_t y, int elem);

void liberer_matrice(Matrice* m);

Matrice* create();

Matrice* reallocate(Matrice* m);

int main(void) {
	Matrice* m1  = create();
	m1 = lire_matrice(m1);
	Matrice* m2 =  create();
	m2 = lire_matrice(m2);
	Matrice* res = create();

	printf("ok\n");
	res = multiplication(m1, m2, res);
	affiche_matrice(res);
	liberer_matrice(m1);
	liberer_matrice(m2);
	liberer_matrice(res);
	
	return 0;
}

void affiche_matrice(Matrice const* m) {
	if (m != NULL) {
		printf("Résultat :\n");
		for(int i = 0; i < m->ligne; ++i) {
			for(int j = 0; j < m->colonne; ++j) {
				printf("%d ", m->mat[i][j]);
			}
			printf("\n");
		}
	}
}

Matrice* lire_matrice(Matrice* lue) {
	Matrice* M = lue;

	if(M != NULL) {
		unsigned int ligne = lire_dimension("lignes");
		unsigned int colonne = lire_dimension("colonnes");
		if(ligne > M->allocatedY || colonne > M->allocatedX) {
			reallocate(M);
		}

		if(M->mat != NULL) {
			for(int i = 0; i < ligne; ++i) {
				for(int j = 0; j < colonne; ++j) {
					printf("M[%d,%d] = ", i+1, j+1);
					scanf("%d", &M->mat[i][j]);
				}
			}
			M->ligne = ligne;
			M->colonne = colonne;
		} else {
			M = NULL;
		}
		
	}
	
	return M;
}

Matrice* multiplication(Matrice const* a, Matrice const* b, Matrice* resultat) {
	Matrice* M = resultat;
	if (M != NULL && a!= NULL && b != NULL) {
		if(a->colonne != b->ligne) {
			printf("Multiplication de matrices impossible !");
			M = NULL;
		} else {
			M->ligne = a->ligne;
			M->colonne = b->colonne;

			for(int i = 0; i < M->ligne; ++i) {
				for (int j = 0; j < M->colonne; ++j) {
					double sum = 0;
					for(int k = 0; k < a->colonne; ++k) {
						sum += a->mat[i][k] * b->mat[k][j];
					}
					M->mat[i][j] = sum;
				}
			}
		}
		
	} else {
		M = NULL;
	}
	
	return M;
}

int lire_dimension(const char* type) {
	unsigned int n = 0;
	do {
		printf("Entrez le nombre de %s : ", type);
		scanf("%u", &n);
	} while (n < 0 || n > N);
}

void push_matrice(Matrice* m, size_t x, size_t y, int elem) {

}

Matrice* create() {
	Matrice* m = malloc(sizeof(Matrice));
	if(m != NULL) {
		m->mat = calloc(N, sizeof(int*));
		if(m->mat != NULL) {
			for(size_t i = 0; i < N; ++i) {
				if ((m->mat[i] = calloc(N, sizeof(int))) == NULL) {
					m = NULL;
					break;
				}
			}	
			m->allocatedX = N;
			m->allocatedY = N;		
		} else {
			free(m);
			m = NULL;
		}
	}
}

Matrice* reallocate(Matrice* m) {
	Matrice* r = m;
	if(r!= NULL && r->mat!=NULL) {
		int** old = r->mat;
		while(r->ligne > N) {
			if ((r->mat = realloc(r->mat, 2*N * sizeof(int*))) == NULL) {
				r->mat = old;
				r = NULL;
			} else {
				r->allocatedY += N;
			}
		}
		while(r->ligne > N) {
			for(size_t i = 0; i < 2*N; ++i) {
				if((r->mat[i] = realloc(r->mat[i], 2*N*sizeof(int))) == NULL) {
					r->mat = old;
					r = NULL;
					break;
				} else {
					r->allocatedX += N;
				}
			}
		}
	}
}

void liberer_matrice(Matrice* m) {
	if(m != NULL && m->mat != NULL) {
		for(int i = 0; i < m->allocatedY; ++i) {
			free(m->mat[i]);
		}
		free(m->mat);
		m->ligne = 0;
		m->colonne = 0;
		free(m);
		m = NULL;
	}
}