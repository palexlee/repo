#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct link {
	int val;
	struct link* prev;
} link;

typedef struct {
	size_t size;
	link* top;
} stack;

int is_empty(stack* s) {
	if (s->top == NULL) {
		return 0;
	} else {
		return 1;
	}
}

int pop(stack* s) {
	if(is_empty(s) == 0) {
		return ' ';
	} else {
		link* tmp = s->top;
		s->size = s->size - 1;
		s->top = s->top->prev;
		int c = tmp->val;
		free(tmp);
		return c;
	}
}

void push(stack* s, char elem) {
	link* l = malloc(sizeof(link));
	s->size = s->size + 1;
	l->val = elem;
	l->prev = s->top;
	s->top = l;
}

void affiche(stack* s) {
	link* l = s->top;
	while (l != NULL) {
		printf("%d->", l->val);
		l = l->prev;
	}
	printf("\n");
}

int main(void) {
	printf("Entrez une expression à évaluer :");
	stack s = {0, NULL};
	char c = ' ';
	while(c != '\n') {
		c = fgetc(stdin);
		affiche(&s);
		if(c != '\n' && c != ' ') {
			if((c >= '0') && (c <= '9')) {
				push(&s, (int)(c - '0'));
			} else {
				if(s.size < 2) {
					printf(" -> error\n");
					return 1;
				}
				int a = 0;
				int b = 0;

				switch (c) {
					case '/':
						a = pop(&s);
						b = pop(&s);
						push(&s, b / a);
						break;
					case '*':
						a = pop(&s);
						b = pop(&s);
						push(&s, b * a);
						break;
					case '+':
						a = pop(&s);
						b = pop(&s);
						push(&s, b + a);
						break;
					case '-':
						a = pop(&s);
						b = pop(&s);
						push(&s, b - a);
						break;
					default:
						break;
				}
			}
		}		
		
	}
	printf(" -> résultat : %d\n", pop(&s));

	return 0;
}