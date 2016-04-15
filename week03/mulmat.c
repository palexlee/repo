#include <stdio.h>

#define N 10

typedef struct {
	int mat[N][N];
	unsigned int ligne;
	unsigned int colonne;
} Matrice;

Matrice lire_matrice(void);

Matrice multiplication(const Matrice a, const Matrice b);

int lire_dimension(const char* type);

void affiche_matrice(const Matrice m);

int main(void) {
	Matrice M1 = lire_matrice();
	Matrice M2 = lire_matrice();

	if(M1.colonne != M2.ligne) {
		printf("Multiplication de matrices impossible !");
	} else {
		Matrice M = multiplication(M1, M2);
		affiche_matrice(M);
	}
	return 0;
}

void affiche_matrice(const Matrice m) {
	printf("Résultat :\n");
	for(int i = 0; i < m.ligne; ++i) {
		for(int j = 0; j < m.colonne; ++j) {
			printf("%d ", m.mat[i][j]);
		}
		printf("\n");
	}
}

Matrice lire_matrice(void) {
	Matrice M;
	unsigned int ligne = lire_dimension("lignes");
	unsigned int colonne = lire_dimension("colonnes");

	for(int i = 0; i < ligne; ++i) {
		for(int j = 0; j < colonne; ++j) {
			printf("M[%d,%d] = ", i+1, j+1);
			scanf("%d", &M.mat[i][j]);
		}
	}
	M.ligne = ligne;
	M.colonne = colonne;
	return M;
}

Matrice multiplication(const Matrice a, const Matrice b) {
	Matrice M;
	M.ligne = a.ligne;
	M.colonne = b.colonne;

	for(int i = 0; i < M.ligne; ++i) {
		for (int j = 0; j < M.colonne; ++j) {
			double sum = 0;
			for(int k = 0; k < a.colonne; ++k) {
				sum += a.mat[i][k] * b.mat[k][j];
			}
			M.mat[i][j] = sum;
		}
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