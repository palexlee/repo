#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

#define HASH_TABLE_LOAD_FACTOR 0.75

#define CSV_MAX_LINE_SIZE 1024
#define CSV_SEPARATOR ','

/* ======================================================================
 * Provided utility functions
 * ======================================================================
 */
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
/** ----------------------------------------------------------------------
 ** Ask for a filename
 **/
void ask_filename(const char* question, char filename[])
{
    size_t len = 0;
    do {
        fputs(question, stdout);
        fflush(stdout);
        fgets(filename, FILENAME_MAX + 1, stdin);
        filename[strcspn(filename, "\r\n")] = '\0';
        len = strlen(filename) - 1;
    } while (len < 1 && !feof(stdin) && !ferror(stdin));
}

/** ----------------------------------------------------------------------
 ** Ask for a filename to open in a given mode
 **/
FILE* ask_filename_and_open(const char* question, const char* mode)
{
    char filename[FILENAME_MAX + 1] = "";

    ask_filename(question, filename);
    FILE* retour = fopen(filename, mode);

    if (retour == NULL) {
        fprintf(stderr, "Oops, je n'ai pas réussi à ouvrir le fichier \"%s\" en mode \"%s\"!\n",
                filename, mode);
    }
    return retour;
}

/** ----------------------------------------------------------------------
 ** Ask for a size
 **/
size_t ask_size_t(const char* question)
{
    size_t v = 0;
    int res = 0;
    do {
        fputs(question, stdout);
        fflush(stdout);
        res = scanf("%zu", & v);
        while (!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
    } while (!feof(stdin) && !ferror(stdin) && res != 1 && v == 0);
    return v;
}

/* ======================================================================
 * Part I -- Hashtable
 * ======================================================================
 */

/** ----------------------------------------------------------------------
 ** Hash a string for a given hashtable size.
 ** See http://en.wikipedia.org/wiki/Jenkins_hash_function
 **/
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
    if((table->size - (table->size % ALVEOLE_SIZE)) < hash) {
        /**
         * si la taille de la table n'est pas un multiple de ALVEOLE_SIZE
         * la dernière alveole de la table aura une taille de (table->size % ALVEOLE_SIZE)
         */
        size = table->size % ALVEOLE_SIZE; 
        

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
						alveole * a = h->content[i];
						
						for(int j = 0; j < a->size; ++j) {
							bucket* ptr = a->content[j].next;
							bucket* next = NULL;
							while(ptr != NULL) {
								next = ptr->next;
								free(ptr);
								ptr = next;
							}	
							ptr = NULL;
							next = NULL;
						
						}
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
                    if(strncmp(curr->key, b.key, 15) == 0) {
                        b.next = curr->next; //update de la valeur pour une clé déjà présente dans la chaine
                        *(prev->next) = b;
                        printf("chaine %s\n", b.key);
                        break;
                    }
                    prev = curr;
                    curr = curr->next;
                }
                if(curr == NULL) { //collision : place à la fin de la chaine
					curr = malloc(sizeof(bucket));
                    if(curr == NULL) {
						fprintf(stderr, "Error: not enough memory");
					} else {
						*curr = b;
						prev->next = curr;  //ne pas oublier de free
					}
                    printf("collision %s\n", curr->key);
                    fflush(stdout);
                }
            }
        }
    }
    
}

const void* get_Htable_value(Htable* h, const char* key) {
	if(h == NULL) {
		return NULL;
	}
	
	size_t hash = hash_function(key, h->size);
	size_t pos_alveole = hash / ALVEOLE_SIZE;
	size_t pos = hash % ALVEOLE_SIZE;
	
	alveole* a = h->content[pos_alveole];
	if(a == NULL) {
		return NULL;
	}
	
	bucket* b = &a->content[pos];
	if(b == NULL) {
		return NULL;
	}
	
	while(b != NULL) {
		if(strncmp(b->key, key, 15) == 0) {
			return b->value;
		} else {
			b = b->next;
		}
	}
	
	return NULL;
}


/* ======================================================================
 * Provided: CSV file parser
 * ======================================================================
 */

typedef char* csv_row;
typedef const char* csv_const_row;

/** ----------------------------------------------------------------------
 ** Allocate and read a CSV row from a file
 **/
csv_row read_row(FILE* f)
{
    char line[CSV_MAX_LINE_SIZE + 1] = "";
    fgets(line, CSV_MAX_LINE_SIZE, f);
    line[strcspn(line, "\r\n")] = '\0'; // remove trailing '\n'
    size_t len = strlen(line);

    assert(len < CSV_MAX_LINE_SIZE); /* We should not have lines that long...
                                      * Not handled in this homework anyway!
                                      * Should be properly handled in real-life appli.
                                      */

    csv_row row;
    if ((row = calloc(len + 1, sizeof(char))) == NULL) {
        return NULL;
    }
    strncpy(row, line, len);

    return row;
}

/** ----------------------------------------------------------------------
 ** Write a CSV row to a file
 **/
void write_row(FILE* out, const csv_const_row row, size_t ignore_index)
{
    size_t len = strlen(row);
    size_t current_element = 0;
    for (size_t i = 0; i < len; ++i) {
        if (row[i] == CSV_SEPARATOR) {
            ++current_element;
        }
        if (current_element != ignore_index && (current_element != ignore_index + 1 || row[i] != CSV_SEPARATOR)) {
            fprintf(out, "%c", row[i]);
        }
    }
}

/** ----------------------------------------------------------------------
 ** Write 2 CSV rows side-by-side to a file
 **/
void write_rows(FILE* out, const csv_const_row row1, const csv_const_row row2, size_t ignore_index)
{
    write_row(out, row1, (size_t) -1);
    fprintf(out, "%c", CSV_SEPARATOR);
    write_row(out, row2, ignore_index);
    fprintf(out, "\n");
}

/** ----------------------------------------------------------------------
 ** Copy and return the i'th element in the row
 **/
char* row_element(const csv_const_row row, size_t index)
{
    size_t len = strlen(row);
    size_t start = 0, end = 0;
    size_t current_element = 0;
    for (size_t i = 0; i < len; ++i) {
        if (row[i] == CSV_SEPARATOR || i == len - 1) {
            ++current_element;
            if (current_element == index) {
                start = i + 1;
            } else if (current_element == index + 1) {
                end = (i == len - 1) ? len : i;
                break;
            }
        }
    }

    if (end > 0) { // success
        size_t elem_len = end - start;
        char* element;
        if ((element = calloc(elem_len + 1, sizeof(char))) == NULL) {
            return NULL;
        }
        element[elem_len] = '\0';
        strncpy(element, &row[start], elem_len);
        return element;
    } else {
        return NULL;
    }
}


/* ======================================================================
 * Part II -- Hashjoin
 * ======================================================================
 */

/* ****************************************
 * TODO : add your own code here.
 * **************************************** */
 
int hash_join(FILE* in1, FILE* in2, FILE* out, size_t col1, size_t col2, size_t memory) {
	Htable* table = NULL;
	int load_factor = (int) memory * HASH_TABLE_LOAD_FACTOR;
	
	csv_row current_r1 = read_row(in1); //rajouter une fonction pour trouver la colonne de jointure !!!!!!!!!!!!!!
	
	if(current_r1 == NULL) {
		fprintf(stderr, "Error: can't read file 1");
		return 1;
	}
	
	csv_row current_r2 = read_row(in2);
	
	if(current_r2 == NULL) {
		fprintf(stderr, "Error: can't read file 2");
		return 1;
	}
	
	write_rows(out, current_r1, current_r2, 3);
	
	if(ferror(out) || feof(out)) {
		fprintf(stderr,"Error I/O");
		return 2;
	}
		
	csv_const_row key = NULL;
	csv_const_row value = NULL;
	
	while(current_r1 != NULL || current_r2 != NULL) {
		table = construct_Htable(4*memory);
		if(table == NULL) {
			fprintf(stderr, "Error: can't create the hashtable");
			delete_Htable_and_content(table);
			return 2;
		} 
		
		if(current_r1 != NULL) {
			for(int i = 0; i < load_factor; ++i) {
				current_r1 = read_row(in1);
				printf("string length %zu\n", strlen(current_r1));
				if(current_r1 == NULL || strlen(current_r1) == 0) {
					current_r1 = NULL;
					fprintf(stderr, "Error: key not parsed r1\n");
					break;
				} else {
					
					printf(">%s<\n", current_r1);
					key = row_element(current_r1, col1);
					if(key == NULL) {
						fprintf(stderr, "Error: can't read data key r1\n");
						delete_Htable_and_content(table);
						return 1;
					}
					printf("key %s\n", key);
					add_Htable_value(table, key, current_r1);
				}

			}
		}
		
		
		if(fseek(in2, 0, SEEK_SET) != 0) {
			fprintf(stderr, "Error I/O");
			delete_Htable_and_content(table);
			return 2;
		} 
		
		if(ferror(in2) || feof(in2)) {
			fprintf(stderr,"Error I/O");
			return 2;
		}
			
		current_r2 = read_row(in2);
	
		if(current_r2 == NULL) {
			fprintf(stderr, "Error: can't read file 2");
			return 1;
		}
		while(current_r2 != NULL) {
			current_r2 = read_row(in2);
			if(current_r2 != NULL || strlen(current_r2) != 0) {
				
				key = row_element(current_r2, col1);
				if(key == NULL) {
					fprintf(stderr, "Error: key not parsed r2\n");
					delete_Htable_and_content(table);
					return 1;
				}

				
				value = get_Htable_value(table, key);/////!!!!!!!
				printf("value %s\n", value);
				if(value != NULL) {
					write_rows(out, value, current_r2, 3);
				}
			} else {
				current_r2 = NULL;
			}
		}
		delete_Htable_and_content(table);
	}
	
	
	return 0;
}


/* ======================================================================
 * Provided: main()
 * ======================================================================
 */

int main(void)
{
    FILE* in1 = ask_filename_and_open("Entrez le nom du premier fichier : ", "r");
    if (in1 == NULL) {
        return EXIT_FAILURE;
    }

    FILE* in2 = ask_filename_and_open("Entrez le nom du second  fichier : ", "r");
    if (in2 == NULL) {
        fclose(in1);
        return EXIT_FAILURE;
    }

    FILE* out = ask_filename_and_open("Entrez le nom du fichier où écrire le résultat : ", "w");
    if (out == NULL) {
        fclose(in1);
        fclose(in2);
        return EXIT_FAILURE;
    }

    size_t col1 = ask_size_t("Entrez l'index de la colonne à joindre dans le premier fichier : "),
           col2 = ask_size_t("Entrez l'index de la colonne à joindre dans le second  fichier : ");

    int success = hash_join(in1, in2, out, col1, col2,
                            ask_size_t("Entrez le budget mémoire autorisé (en octets) : ")
                            );

    fclose(in1);
    fclose(in2);
    fclose(out);

    return success;
}
