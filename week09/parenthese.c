#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct link {
	char val;
	struct link* prev;
} link;

typedef struct {
	link* top;
} stack;

int is_empty(stack* s) {
	if (s->top == NULL) {
		return 0;
	} else {
		return 1;
	}
}

char pop(stack* s) {
	if(is_empty(s) == 0) {
		return ' ';
	} else {
		link* tmp = s->top;
		s->top = s->top->prev;
		char c = tmp->val;
		free(tmp);
		return c;
	}
}

void push(stack* s, char elem) {
	link* l = malloc(sizeof(link));
	l->val = elem;
	l->prev = s->top;
	s->top = l;
}

void affiche(stack* s) {
	link* l = s->top;
	while (l != NULL) {
		printf("%c->", l->val);
		l = l->prev;
	}
	printf("\n");
}

int main(void) {
	printf("Entrez une expression parenthésée :");
	stack s = {NULL};
	char c = ' ';
	while(c != '\n') {
		c = fgetc(stdin);
		affiche(&s);
		if(c != '\n') {
			switch (c) {
				case ')':
					if (pop(&s) != '(') {
						printf("-> Error\n");
						return 0;
					}
					break;
				case ']':
					if (pop(&s) != '[') {
						printf("-> Error\n");
						return 0;
					}
					break;
				case '[':
					push(&s, c);
					break;
				case '(':
					push(&s, c);
					break;
				default:
					break;
			}	
		}
		
	}
	if(is_empty(&s) == 0) {
		printf("-> OK\n");
	} else {
		printf("-> Error\n");
	}


	return 0;
}