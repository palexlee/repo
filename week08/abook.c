#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_NUMBER 10
/* un noeud de l'arbre */
typedef struct addr__ addr_t;
struct addr__ {
	/* à compléter */
	char name[MAX_NUMBER];
	char phone_number[MAX_NUMBER];

	addr_t* left;
	addr_t* right;
	addr_t* parent;
};

/* l'arbre, défini par sa racine */
typedef struct book__ {
	addr_t* root;
} book_t;

/* créer un nouveau carnet d'adresses vide */
book_t* book_create(void);

void addr_free(addr_t* a);

/* libérer les ressources associées */
void book_free(book_t* b);

/* lister dans l'ordre tous les noms du carnet d'adresses */
void addr_list(addr_t* a);
void book_list(book_t* b);

/* afficher une entrée du carnet d'adresses */
addr_t* addr_iter(addr_t* a, const char* name);

void book_view(book_t* b, const char* name);

/* ajouter ou modifier une entrée du carnet d'adresse */
void book_add(book_t* b, const char* name, const char* num);

/* supprimer une entrée du carnet d'adresses */
void book_remove(book_t* b, const char* name);

/* remplacer le contenu du carnet d'adresses par celui du fichier */
void book_load(book_t* b, const char* file);

/* sauver le contenu du carnet dans un fichier au format CSV */
void book_save(book_t* b, const char* file);

int main(void) { 
	return 0;
}

book_t* book_create(void) {
	book_t* book = malloc(sizeof(book_t));

	if(book != NULL) {
		book->root = malloc(sizeof(addr_t));

		if(book->root == NULL) {
			free(book);
			book = NULL;
		}
	}

	return book;
}

addr_t* addr_create(const char* name, const char* number, addr_t* parent) {
	addr_t* a = malloc(sizeof(addr_t));
	if(a != NULL) {
		a->parent = parent;
		strncpy(a->name, name, MAX_NAME);
		strncpy(a->phone_number, number, MAX_NUMBER);
	}
	return a;
}

void addr_free(addr_t* a) {
	if(a != NULL) {
		if(a->left != NULL) {
			addr_free(a->left);
		}
		if(a->right != NULL) {
			addr_free(a->right);
		}
		free(a);
	}
}

void book_free(book_t* b) {
	if(b != NULL) {
		addr_free(b->root);
	}

	free(b);
}

void addr_list(addr_t* a) {
	if(a!= NULL) {
		if(a->left != NULL) {
			addr_list(a->left);
		}
		printf("%s\n", a->name);
		if(a->right != NULL) {
			addr_list(a->right);
		}
	}
}

void book_list(book_t* b) {
	if(b->root != NULL) {
		addr_list(b->root);
	}
}

addr_t* addr_iter(addr_t* a, const char* name) {
	if(a != NULL) {
		int cmp = strncmp(a->name, name, MAX_NAME);
		if(cmp == 0) {
			return a;
		} else if(cmp < 0) {
			return addr_iter(a->right, name);
		} else {
			return addr_iter(a->left, name);
		}
	}
	return a->parent;
}

void book_view(book_t* b, const char* name) {
	if(b != NULL) {
		addr_t* match = addr_iter(b->root, name);
		if(match ==  NULL) {
			printf("Entry not found\n");
		} else {
			printf("Name: %s, Phone number : %s\n", match->name, match->phone_number);
		}
	}
}

/* ajouter ou modifier une entrée du carnet d'adresse */
void book_add(book_t* b, const char* name, const char* num) {
	if(b != NULL) {
		addr_t* match = addr_iter(b->root, name);
		if(match != NULL) {
			if(strncpy(match->phone_number, num, MAX_NUMBER) != 0) {
				printf("Error\n");
			}
		} else {
			if(strncmp(match->parent->name, name, MAX_NAME) < 0) {
				match->parent->right = addr_create(name, num, match->parent);
			} else {
				match->parent->right = addr_create(name, num, match->parent);
			}
		}
	}
}

/* supprimer une entrée du carnet d'adresses */
void book_remove(book_t* b, const char* name) {
	addr_t* match = addr_iter(b->root, name);

	
}

/* remplacer le contenu du carnet d'adresses par celui du fichier */
void book_load(book_t* b, const char* file);

/* sauver le contenu du carnet dans un fichier au format CSV */
void book_save(book_t* b, const char* file);