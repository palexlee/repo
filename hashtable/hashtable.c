#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

typedef struct bucket{
	int valid;
    const char* key;
    const void* value;
    struct bucket* next;
} bucket;

typedef struct {
	int id;
    size_t size; //taille de l'alvéole
    bucket* content; 
} alveole;

typedef struct {
    size_t size;
    size_t nb_alveole;
    int* initialized;
    alveole** content;
} Htable;

#define ALVEOLE_SIZE 10

size_t hash_function(const char* key, size_t size)
{
    size_t hash = 0;
    size_t key_len = strlen(key);
    for (size_t i = 0; i < key_len; ++i) {
        hash += (unsigned char) key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % size;
}

/* ****************************************
 * TODO : add your own code here.
 * **************************************** */
Htable* construct_Htable(size_t size) {
    Htable* h = NULL;

    h = malloc(sizeof(Htable));
    if(h != NULL) {
        //on vérifie que la taille n'est pas trop grande
        size_t space = size/ALVEOLE_SIZE + 1;
        if(space * sizeof(alveole*) > SIZE_MAX || 
            (h->content = calloc(space, sizeof(alveole*))) == NULL) {
            h = NULL;
        } else {
            if((h->initialized = calloc(space, sizeof(int))) == NULL) {
                h = NULL;
            } else {
                h->size = size;
                h->nb_alveole = space;
                for(int i = 0; i < space; ++i) {
                    h->initialized[i] = 0;
                    //h->content[i] = NULL;
                }
            }
            
        }
        if(h == NULL) {
        	fprintf(stderr, "Error: not enough memory to construct the table");
        }
    }
    fflush(stdout);
    return h;
}

alveole* construct_alveole(const Htable* table, const size_t hash) {
    alveole* a = NULL;
    size_t size = 0;
    if((table->size - hash) < ALVEOLE_SIZE) {
        /**
         * si la taille de la table n'est pas un multiple de ALVEOLE_SIZE
         * la dernière alveole de la table aura une taille de (table->size - hash)
         */
        size = table->size - hash; 

    } else {
        size = ALVEOLE_SIZE;
    }
    a = malloc(sizeof(alveole));
    if(a!= NULL) {
		a->content = calloc(size, sizeof(bucket));
		if(a->content!= NULL) {
			for(int i = 0; i < size; ++i) {
				a->content[i].valid = 0;
			}
			a->size = size;
			table->initialized[hash/ALVEOLE_SIZE] = 1;
			a->id = hash/ALVEOLE_SIZE;
		} else {
			a = NULL;
		}
    }
    if(a == NULL) {
        	fprintf(stderr, "Error: not enough memory to construct the table");
        	fflush(stderr);
        }
    return a;
}

void delete_Htable_and_content(Htable* h) {
    if(h != NULL) {
        if (h->content != NULL) {
            for(int i = 0; i < h->nb_alveole; ++i) {
                if(h->initialized[i] != 0) {
					h->initialized[i] = 0;
					if(h->content[i] != NULL) {
						free((h->content[i])->content);
					}
                }
            }
            free(h->content);
            h->content = NULL;
        }
        h-> size = 0;
        free(h);
        h = NULL;
    }
}

void add_Htable_value(Htable* h, const char* key, const void* value) {
    if(h != NULL && h->content != NULL) {
        size_t hash = hash_function(key, h->size);
        size_t pos_alveole = hash / ALVEOLE_SIZE;
        printf("position %zu\n", pos_alveole);
        alveole* a = NULL;
        if(h->initialized[pos_alveole] == 0) {
            a = construct_alveole(h, hash);
            if(a == NULL) {
                fprintf(stderr, "Error: insertion impossible, no more memory");
                return;
            } else {
                h->content[pos_alveole] = a;
            }
        } else {
            a = h->content[pos_alveole];
        }
        size_t pos = hash % ALVEOLE_SIZE;
        printf("alveole: %zu, hash : %zu, modulo: %zu\n",pos_alveole, hash, pos);
        bucket b = {1, key, value, NULL};
        bucket* buck = &a->content[pos];
        if(buck->valid == 0) {
            *buck = b;
        } else {
            if(buck->key == b.key) {
                b.next = buck->next;
                *buck = b;
            } else {
                bucket* prev = buck;
                bucket* curr = buck->next;
                while(curr != NULL) {
                    if(curr->key == b.key) {
                        b.next = curr->next; //update de la valeur pour une clé déjà présente dans la chaine
                        *(prev->next) = b;
                        break;
                    }
                    prev = curr;
                    curr = curr->next;
                }
                if(curr == NULL) { //collision : place à la fin de la chaine
                    *(prev->next) = b;
                }
            }
        }
    }
    
}

void affiche(Htable* table) {
 	if(table != NULL) {
 		for(int i = 0; i < (table -> nb_alveole); ++i) {
 			if(table->initialized[i] == 0) {
 				printf("Alveole %d non init\n", i);
 			} else {
 				alveole* a = table->content[i];
 				if(a == NULL) {
					fprintf(stderr, "Error");
				} else {
					printf("id: %d\n", a->id);
					printf("ptr %d\n", (int)a);
					for(int j = 0; j < a->size; ++j) {
						if(a->content[j].valid == 0) {
							printf("Bucket %d vide\n", i*ALVEOLE_SIZE +j);
						} else {
							printf("Key: %s, Value: %d, ptr: %d\n", a->content[j].key, *(int*)a->content[j].value, (int)&a->content[j]);
							bucket* b = a->content[j].next;
							while(b != NULL) {
								printf("=> Key: %s, Value: %d\n", b->key, *(int*)b->value);
								b = b->next;
							}
						}
					}
				}
 			}
 		}
 	}
}

int main(void) { 
	Htable* table = construct_Htable(600);
	char* s = "sam";
	char* p = "pougne";
	char* x = "rhubarbe";
	int a = 14;
	int b = 42;
	int c = a + b;
	add_Htable_value(table, s, &a);
	add_Htable_value(table, p, &b);
	add_Htable_value(table, p, &a);
	add_Htable_value(table, x, &c);
	add_Htable_value(table, x, &b);
	affiche(table);
	delete_Htable_and_content(table);

	return 0;
}
