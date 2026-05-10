#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Oras Oras;
typedef struct Graf Graf;

struct Oras {
	int id;
	char* nume;
	int populatie;
};

struct Graf {
	Oras* vectorOrase;
	int** matriceAdiacenta;
	int nrOrase;
};

Oras creeazaOras(int id, const char* nume, int populatie) {
	Oras o;
	o.id = id;
	o.populatie = populatie;

	o.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(o.nume, nume);

	return o;
}

void afisareOras(Oras o) {
	printf("ID: %d\n", o.id);
	printf("Nume oras: %s\n", o.nume);
	printf("Populatie: %d\n\n", o.populatie);
}

Graf initializareGraf(int nrOrase) {
	Graf g;
	g.nrOrase = nrOrase;

	g.vectorOrase = (Oras*)malloc(sizeof(Oras) * nrOrase);

	g.matriceAdiacenta = (int**)malloc(sizeof(int*) * nrOrase);
	for (int i = 0; i < nrOrase; i++) {
		g.matriceAdiacenta[i] = (int*)malloc(sizeof(int) * nrOrase);

		for (int j = 0; j < nrOrase; j++) {
			g.matriceAdiacenta[i][j] = 0;
		}
	}

	return g;
}

void adaugaMuchie(Graf* g, int index1, int index2) {
	if (index1 >= 0 && index1 < g->nrOrase &&
		index2 >= 0 && index2 < g->nrOrase) {

		g->matriceAdiacenta[index1][index2] = 1;
		g->matriceAdiacenta[index2][index1] = 1;
	}
}

void afisareMatriceAdiacenta(Graf g) {
	printf("Matrice de adiacenta:\n\n");

	for (int i = 0; i < g.nrOrase; i++) {
		for (int j = 0; j < g.nrOrase; j++) {
			printf("%d ", g.matriceAdiacenta[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

void afisareGraf(Graf g) {
	for (int i = 0; i < g.nrOrase; i++) {
		printf("Orasul %s este conectat cu: ", g.vectorOrase[i].nume);

		int areVecini = 0;

		for (int j = 0; j < g.nrOrase; j++) {
			if (g.matriceAdiacenta[i][j] == 1) {
				printf("%s ", g.vectorOrase[j].nume);
				areVecini = 1;
			}
		}

		if (areVecini == 0) {
			printf("niciun oras");
		}

		printf("\n");
	}
}

void dezalocareOras(Oras o) {
	free(o.nume);
}

void dezalocareGraf(Graf* g) {
	for (int i = 0; i < g->nrOrase; i++) {
		dezalocareOras(g->vectorOrase[i]);
	}

	free(g->vectorOrase);

	for (int i = 0; i < g->nrOrase; i++) {
		free(g->matriceAdiacenta[i]);
	}

	free(g->matriceAdiacenta);

	g->vectorOrase = NULL;
	g->matriceAdiacenta = NULL;
	g->nrOrase = 0;
}

int main() {
	Graf graf = initializareGraf(5);

	graf.vectorOrase[0] = creeazaOras(1, "Bucuresti", 1800000);
	graf.vectorOrase[1] = creeazaOras(2, "Brasov", 250000);
	graf.vectorOrase[2] = creeazaOras(3, "Cluj", 320000);
	graf.vectorOrase[3] = creeazaOras(4, "Iasi", 290000);
	graf.vectorOrase[4] = creeazaOras(5, "Constanta", 280000);

	adaugaMuchie(&graf, 0, 1);
	adaugaMuchie(&graf, 0, 3);
	adaugaMuchie(&graf, 1, 2);
	adaugaMuchie(&graf, 2, 4);
	adaugaMuchie(&graf, 3, 4);

	printf("Orasele din graf:\n\n");
	for (int i = 0; i < graf.nrOrase; i++) {
		afisareOras(graf.vectorOrase[i]);
	}

	afisareMatriceAdiacenta(graf);

	printf("Conexiunile grafului:\n\n");
	afisareGraf(graf);

	dezalocareGraf(&graf);

	return 0;
}