/**
 * @file muimp
 * 
 * Programme permettant de créer une image numérique simplifiée, 
 * l'afficher (en mode texte), l'écrire et la lire depuis le disque 
 * ainsi que de lui appliquer un filtrage par convolution.
 * 
 */
#include <stdio.h>
#include <string.h>

typedef double Pixel;

/**
 * Dimensions maximales d'une image
 */
#define MAX_IMAGE_HEIGHT 100
#define MAX_IMAGE_WIDTH 100

typedef struct {
	Pixel content[MAX_IMAGE_HEIGHT][MAX_IMAGE_WIDTH];
	int height;
	int width;
} Image;


/**
 * Prototypes
 */
Image diamond(int height, int width, int diagonal);

Image init_image(int height, int width);

void display(FILE* output, Image i);

int write_to_file(char* filename, Image image);

Image read_from_file(char* filename);

Image init_mask();

Image filter(Image image, Image mask);

int main(void) {
	int width = 0;
	int height = 0;
	int diagonal = 0;
	char nom[FILENAME_MAX+1] = "";
	int len = 0;
	Image mask = init_mask();

	/**
	 * Demande à l'utilisateur :
	 *  - le nom du fichier
	 *  - la hauteur de l'image
	 *  - la largueur de l'image
	 *  - la longueur de la diagonal du losange
	 */
	do {
		printf("Entrez un nomn de fichier : ");
		fgets(nom, FILENAME_MAX+1, stdin);
		len = strlen(nom) - 1;
		if ((len >= 0) && nom[len] == '\n') {
			nom[len] = '\0';
		} else {
			while(!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
		}
	} while ((len < 1) && !feof(stdin) && !ferror(stdin));
	
	char c_par = ' ';

	// si c_par != '\n', cela veut dire que l'utilisateur a entré des lettres et des chiffres
	while(height <= 0 || height > MAX_IMAGE_HEIGHT || c_par != '\n') {
		printf("Hauteur de l'image (max : %d) : ", MAX_IMAGE_HEIGHT);
		scanf("%d%c", &height, &c_par);
		if(c_par != '\n') {
			fprintf(stderr, "Erreur: entrez seulement des nombres !\n");
			while(!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
		}
	}

	while(width <= 0 || width > MAX_IMAGE_WIDTH || c_par != '\n') {
		printf("Largeur de l'image (max : %d) : ", MAX_IMAGE_WIDTH);
		scanf("%d%c", &width, &c_par);
		if(c_par != '\n') {
			fprintf(stderr, "Erreur: entrez seulement des nombres !\n");
			while(!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
		}
	}

	if(width % 2 == 0 || height % 2 == 0) {
		if (width == 100) { // si la dimension = 100, elle sera corrigée vers le bas
			width = 99;
		}

		if(height == 100) {
			height = 99;
		}

		width |= 1; //force les valeurs à être impaires
		height |= 1;
		printf("Les dimmensions ont été ajustées à des valeurs impaires. \n");
		printf("Hauteur : %d, Largeur : %d\n", height, width);
	}

	do {
		printf("Diagonal du losange : ");
		scanf("%d%c", &diagonal, &c_par);
		if(c_par != '\n') {
			fprintf(stderr, "Erreur: entrez seulement des nombres !\n");
			while(!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
		}
	} while(diagonal < 0 || (diagonal > height && diagonal > width) || c_par != '\n');

	if(diagonal % 2 == 0 && (diagonal == height + 1 || diagonal == width + 1)) {
		// si la diagonale est égale à une des dimensions entrées (avant ajustement), elle sera corrigée
		diagonal = diagonal - 1; 
	}

	/**
	 * dessin du losange et affichage de l'image
	 */
	Image i = diamond(height, width, diagonal);
	display(stdout, i);

	/**
	 * écriture de l'image dans un fichier puis lecture du fichier
	 */
	write_to_file(nom, i);
	Image r = read_from_file(nom);
	display(stdout, r);

	/**
	 * application du filtre et affichage du résultat
	 */
	Image res = filter(i, mask);
	display(stdout, res);
	
	return 0;
}


/**
 * @brief dessine un losange au centre de l'image
 * 
 * @param height hauteur de l'image
 * @param width largeur de l'image
 * @param diagonal longueur de la diagonal du losange
 * @return image
 */
Image diamond(int height, int width, int diagonal) {
	Image i = init_image(height, width);

	if(diagonal != 0) { //si diagonal = 0, on ne dessine rien
		int centre_x = width/2;
		int centre_y = height/2;

		for(int j = 0; j < centre_y + 1; ++j) {   //calcul de la première moitié du losange par la formule
			int bord = j - centre_y + diagonal/2;
			for (int k = centre_x-bord; k <= centre_x + bord; ++k) {
				i.content[j][k] = 1.0;
			}
		}

		for(int j = centre_y; j < height; ++j) { //calcul de la deuxième moitié par symétrie
			for(int k = 0; k < width; ++k) {
				i.content[j][k] = i.content[height-1-j][k];
			}
		}
	}

	return i;
}

/**
 * @brief initialise une image et son contenu
 * 
 * @param height la longueur de l'image
 * @param width la largeur de l'image
 * 
 * @return l'image initialisée
 */
Image init_image(int height, int width) {
	Image i;
	i.height = height;
	i.width = width;

	for(int j = 0; j < height; ++j) {
		for(int k = 0; k < width; ++k) {
			i.content[j][k] = 0.0;
		}
	}
	return i;
}

/**
 * @brief affiche une image sur une sortie
 * 
 * @param output le fichier de sortie
 * @param image l'image à afficher
 */
void display(FILE* output, Image image) {
	for(int j = 0; j < image.height; ++j) {
		for(int k = 0; k < image.width; ++ k) {
			char c = ' ';
			if (image.content[j][k] == 0.0) {
				c = '.';
			} else if (image.content[j][k] == 1.0) {
				c = '+';
			} else {
				c = '*';
			}
			fprintf(output, "%c ", c);
		}
		fprintf(output, "\n");
	}
	fprintf(output, "\n");
}

/**
 * @brief écrit une image dans un fichier
 * 
 * @param filename le nom du fichier cible
 * @param image l'image à afficher
 * 
 * @return 0 en cas de succès
 */
int write_to_file(char* filename, Image image) {
	FILE* output = NULL;
	output = fopen(filename, "w"); //écriture dans le fichier par écrasement

	if(output == NULL) {
		fprintf(stderr, "Erreur: mpossible d'écrire dans le fichier %s\n", filename);
		return 1;
	} else {
		fprintf(output, "%d", image.width);
		fprintf(output, "\n%d", image.height);
		fprintf(output, "\n");
		display(output, image);
		fclose(output);
		return 0;
	}
}

/**
 * @brief Prend un nom de fichier, lit l'image du fichier et la retourne.
 * 
 * @param filename nom du fichier source
 * @return l'image contenue dans le fichier
 */
Image read_from_file(char* filename) {
	FILE* input = NULL;
	input = fopen(filename, "r");
	int erreur = 0;
	Image image;

	if (input == NULL) {
		fprintf(stderr, "Erreur: impossible de lire le fichier %s\n", filename);
	} else {
		int width = 0;
		int height = 0;

		int j = fscanf(input, " %d", &width); 
		if (j != 1 || width > MAX_IMAGE_WIDTH || width < 0) { //vérification de la validité des dimensions
			fprintf(stderr, "Erreur: largeur invalide");
			while(!feof(input) && !ferror(input) && getc(input) != '\n');
			erreur = 1;
		}

		int k = fscanf(input, " %d", &height);
		if (k != 1 || height > MAX_IMAGE_HEIGHT || height < 0) {
			fprintf(stderr, "Erreur: hauteur invalide");
			while(!feof(input) && !ferror(input) && getc(input) != '\n');
			erreur = 1;
		}

		if(erreur == 0) {
			while(!feof(input) && !ferror(input) && getc(input) != '\n');
			image = init_image(height, width);
			for(int a = 0; a < height && erreur == 0; ++a) {
				
				char temp[2*width+2];
				fgets(temp, 2*width+2, input);
				for(int b = 0; b < 2*width; b = b+2) {
					char c = '*';
					double d = 0.0;
					if (!feof(input) && !ferror(input) && erreur == 0) {
						c = temp[b];
						if((c == '+' || c == '.' || c == '*')) {
							if (c == '+') {
								d = 1.0;
							} else if (c == '.') {
								d = 0.0;
							} else {
								d = 42.0;
							}
							image.content[a][b/2] = d;
							
						} else {
							erreur = 1;
						}

					}
				}

				if(temp[2*width] != '\n') {
					fprintf(stderr, "Erreur: contenu en désaccord avec les dimensions \n");
					erreur = 1;
					while(!feof(input) && !ferror(input) && getc(input) != '\n');
				}
			}
		}

		if(erreur != 0) {
			image.width = 0;
			image.height = 0;
		}
		
		fclose(input);
	}	
	return image;
}

/**
 * @brief initialisation du masque
 * @return le masque
 */
Image init_mask() {
	Image image;
	image.height = 3;
	image.width = 3;
	Pixel c[3][3] = {{-2.0, -2.0, -2.0}, 
					 {0.0, 0.0, 0.0},
					 {2.0, 2.0, 2.0}};
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			image.content[i][j] = c[i][j];
		}
	}
	return image;
}

/**
 * @brief Filtre une image avec un masque par convolution
 * 
 * @param image l'image à filtrer
 * @param mask le masque
 * 
 * @return l'image filtrée
 */
Image filter(Image image, Image mask) {
	Image res;
	res.height = image.height;
	res.width = image.width;

	for(int i = 0; i < res.height; ++i) {
		for(int j = 0; j < res.width; ++j) {
			Pixel sum = 0.0;
			for(int k = 0; k < mask.height; ++k) {
				for(int l = 0; l < mask.width; ++l) {
					int index_h = (i + mask.height/2 - k) % res.height;
					if (index_h < 0) {          //correction du modulo négatif
						index_h = res.height + index_h;
					}
					int index_w = (j + mask.height/2 - l) % res.width;
					if(index_w < 0) {
						index_w = res.width + index_w;
					}
					sum = sum + image.content[index_h][index_w] * mask.content[k][l];
				}
			}
			res.content[i][j] = sum;
		}
	}
	return res;
}