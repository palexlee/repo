#include <stdlib.h>
#include <stdio.h>

#define ALLOC 100
#define SIZE_MAX 1000

typedef int type_el;

typedef struct {
	size_t size;
	size_t allocated;
	type_el* content;
} dynatab;

dynatab* create_tab(dynatab* d);
void delete_tab(dynatab* d);
size_t append_tab(dynatab* d, type_el element);
dynatab* reallocate(dynatab* d);
void modify(dynatab* d, size_t pos, type_el element);
type_el get(dynatab* d, size_t pos);

int main(void) {
	return 0;
}

dynatab* create_tab(dynatab* d) {
	dynatab* n = d;
	if (n != NULL) {
		n->content = calloc(ALLOC, sizeof(type_el));

		if(n-> content != NULL) {
			n->size = 0;
			n-> allocated = ALLOC;
		} else {
			n = NULL;
		}
	}

	return n;
}

void delete_tab(dynatab* d) {
	if(d != NULL && d->content != NULL) {
		free(d->content);
		d->content = NULL;
		d->size = 0;
		d->allocated = 0;
	}
}

size_t append_tab(dynatab* d, type_el element) {
	dynatab* a = d;
	if (a != NULL) {
		while(a->size >= a->allocated) {
			if(reallocate(a) == NULL) {
				return 0;
			}
		}
		a->content[a->size] = element;
		++(a->size);
		return a->size;
	}
	return 0;
}

dynatab* reallocate(dynatab* d) {
	dynatab* n = d;
	if(n != NULL) {
		type_el* const old = d->content;
		size_t newallocated = d->allocated + ALLOC;
		if(newallocated > SIZE_MAX / sizeof(type_el) || (n->content = realloc(d->content, newallocated*sizeof(type_el))) == NULL) {
			n->content = old;
			n = NULL;
		} else {
			n->allocated = newallocated;
		}
	}
	return n;
}

void modify(dynatab* d, size_t pos, type_el element) {
	if(d != NULL && d->content != NULL && pos < d->size) {
		d->content[pos] = element;
	}
}

type_el get(dynatab* d, size_t pos) {
	type_el e = NULL;
	if(d != NULL && d->content != NULL, pos < d->size) {
		e = d->content[pos];
	}
	return e;
}





