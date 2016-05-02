#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REPONSES 10
#define NB_QCM 3
#define MAX_CHAR 100

typedef struct {
	char* question;
	char* reponses[MAX_REPONSES];
	unsigned int nb_rep;
	int solution;
} QCM;

typedef QCM* Examen;

void affiche(const QCM* q) {
	printf("%s\n", q->question);
	for(int i = 0; i < q->nb_rep; ++i) {
		printf("%d- %s\n",i+1,  q->reponses[i]);
	}
}

int demander_nombre(int borne) {
	int c = 0;

	while(c == 0 || c >= borne) {
		printf("Entrez un nombre entier compris entre 1 et %d : ", borne);
		scanf("%d", &c);
	}
	return c;
}

int poser_question(const QCM* q) {
	affiche(q);
	int c = demander_nombre(q->nb_rep);
	if(q->solution == c) {
		return 1;
	} else {
		return 0;
	}
}

Examen* creer_examen(void) {
	Examen* retour = malloc(sizeof(Examen));
	*retour =  calloc(NB_QCM, sizeof(QCM));

	if(*retour != NULL) {
		for(int i = 0; i < NB_QCM; ++i) {
			(*retour)[i].question = malloc(MAX_CHAR);
			for(int j = 0; j < MAX_REPONSES; ++j) {
				(*retour)[i].reponses[j] = malloc(MAX_CHAR);
			}
		}

		strcpy((*retour)[0].question,
         "Combien de dents possède un éléphant adulte");
		  (*retour)[0].nb_rep = 5;
		  strcpy((*retour)[0].reponses[0], "32");
		  strcpy((*retour)[0].reponses[1], "de 6 à 10");
		  strcpy((*retour)[0].reponses[2], "beaucoup");
		  strcpy((*retour)[0].reponses[3], "24");
		  strcpy((*retour)[0].reponses[4], "2");
		  (*retour)[0].solution = 2;

		  strcpy((*retour)[1].question,
		         "Laquelle des instructions suivantes est un prototype de fonction");
		  (*retour)[1].nb_rep = 4;
		  strcpy((*retour)[1].reponses[0], "int f(0);");
		  strcpy((*retour)[1].reponses[1], "int f(int 0);");
		  strcpy((*retour)[1].reponses[2], "int f(int i);");
		  strcpy((*retour)[1].reponses[3], "int f(i);");
		  (*retour)[1].solution = 3;

		  strcpy((*retour)[2].question,
		         "Qui pose des questions stupides");
		  (*retour)[2].nb_rep = 7;
		  strcpy((*retour)[2].reponses[0], "le prof. de math");
		  strcpy((*retour)[2].reponses[1], "mon copain/ma copine");
		  strcpy((*retour)[2].reponses[2], "le prof. de physique");
		  strcpy((*retour)[2].reponses[3], "moi");
		  strcpy((*retour)[2].reponses[4], "le prof. d'info");
		  strcpy((*retour)[2].reponses[5], "personne, il n'y a pas de question stupide");
		  strcpy((*retour)[2].reponses[6], "les sondages");
		  (*retour)[2].solution = 6;
	}
	return retour;
	 
}

void detruire_examen(Examen* exa) {
	for(int i = 0; i < NB_QCM; ++i) {
			free((*exa)[i].question);
			for(int j = 0; j < MAX_REPONSES; ++j) {
				free((*exa)[i].reponses[j]);
			}
		}
	free(*exa);
	free(exa);
}

int main(void) {

	Examen* exa = creer_examen();
	int somme = 0;

	for(int i = 0; i < NB_QCM; ++i) {
		somme += poser_question(&(*exa)[i]);
	}
	printf("Vous avez trouvé %d bonnes réponses sur %d.\n", somme, NB_QCM);

	detruire_examen(exa);

	return 0;
}