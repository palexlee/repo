#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#define START_SIZE 3

typedef struct Node{
	uint32_t adresse;
	struct Node** voisins;
	size_t size;
	size_t allocated;
} Node;


Node* creation(uint8_t c, uint8_t d);
void sont_voisins(Node* n, Node* m);
Node* reallocate(Node* n);
int voisins_communs(Node* n, Node* m);
void affiche(Node const* n);
void affiche_s(Node const* n);
void delete(Node* n);

int main(void) {
	Node* a = creation(1, 1);
	Node* b = creation(1, 2);
	Node* c = creation(1, 3);
	Node* d = creation(2, 1);
	Node* e = creation(2, 3);
	sont_voisins(a,b);
	sont_voisins(a,d);
	sont_voisins(a,e);
	sont_voisins(a,c);
	sont_voisins(b,c);
	affiche(a);
	affiche(b);
	affiche(c);
	int nb = voisins_communs(a,c);
	printf("Voisins commums : %d", nb);
	delete(a);
	delete(b);
	delete(c);
	delete(d);
	delete(e);
	return 0;
}

Node* creation(uint8_t c, uint8_t d) {
	Node* n = malloc(sizeof(Node));
	if (n != NULL) {
		n->voisins = calloc(START_SIZE, sizeof(Node*));
		if (n->voisins != NULL) {
			uint32_t ip  = 192;
			ip = (ip << 8) | 168;
			ip = (ip << 8) | c;
			ip = (ip << 8) | d;
			n->adresse = ip;
			n->size = 0;
			n->allocated = START_SIZE;
		} else {
			puts("error init voisin null");
			n = NULL;
		}
	}
	return n;
}

void sont_voisins(Node* n, Node* m) {
	if(n != NULL && m != NULL) {
		while(n->size+1 >= n->allocated) {
			Node* p = reallocate(n);
			if(p == NULL) {
				return;
			} else {
				n = p;
			}
		}
		while(m->size+1 >= m->allocated) {
			Node* q = reallocate(m);
			if(q == NULL) {
				return;
			} else {
				m = q;
			}
		}
			
		n->voisins[n->size] = (struct Node*)m;
		n->size += 1;
		
		m->voisins[m->size] = (struct Node*)n;
		m->size += 1;
	}

}

Node* reallocate(Node* n) {
	Node* r = n;
	if (r != NULL) {
		struct Node** const old = r->voisins;
		size_t newsize = r->size + START_SIZE;
		newsize *= sizeof(Node*);
		printf("Ancienne taille: %zu\n", r->size);
		printf("Nouvelle taille: %zu", newsize);
		fflush(stdout);
		if(newsize > SIZE_MAX || (r->voisins = realloc(n->voisins, newsize )) == NULL) {
			n->voisins = old;
			r = NULL;
		} else {
			r->allocated = newsize/sizeof(Node*);
		}
	}
	return r;
}

int voisins_communs(Node* n, Node* m) {
	int cnt = 0;
	if(n != NULL && n->voisins != NULL && m!= NULL && m->voisins != NULL) {
		for(int i = 0; i < n->size; ++i) {
			for(int j = 0; j < m->size; ++j) {
				if(m->voisins[i] == m->voisins[j]) {
					cnt += 1;
				}
			}
		}
	}
	return cnt / 2;
}

void affiche(Node const* n) {
	affiche_s(n);
	for(int i = 0; i < n->size; ++i) {
		Node* p = (Node*) n->voisins[i];
		if (p != NULL) {
			affiche_s(p);
		}
		
	}
}
void affiche_s(Node const* n) {
	uint8_t a = n->adresse>>24;
	uint8_t b = n->adresse>>16 & 0xFF;
	uint8_t c = n->adresse>>8 & 0xFF;
	uint8_t d = n->adresse & 0xFF;
	if(n != NULL) {
		printf("%" PRIu8 ".%" PRIu8 ".%" PRIu8 ".%" PRIu8 "\n", a, b, c, d);
	}
}

void delete(Node* n) {
	if(n != NULL && n->voisins != NULL) {
		free(n->voisins);
		n->voisins = NULL;
		n->size = 0;
		n->allocated = 0;
		free(n);
		n = NULL;
	}
}
