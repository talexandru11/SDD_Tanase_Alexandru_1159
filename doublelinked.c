#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carte Carte;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Carte {
	int id;
	char* titlu;
	char* autor;
	char* categorie;
	float pret;
};

struct Nod {
	Carte info;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

Carte creeazaCarte(int id, const char* titlu, const char* autor, const char* categorie, float pret) {
	Carte c;
	c.id = id;
	c.pret = pret;

	c.titlu = (char*)malloc(strlen(titlu) + 1);
	strcpy(c.titlu, titlu);

	c.autor = (char*)malloc(strlen(autor) + 1);
	strcpy(c.autor, autor);

	c.categorie = (char*)malloc(strlen(categorie) + 1);
	strcpy(c.categorie, categorie);

	return c;
}

void afisareCarte(Carte c) {
	printf("ID: %d\n", c.id);
	printf("Titlu: %s\n", c.titlu);
	printf("Autor: %s\n", c.autor);
	printf("Categorie: %s\n", c.categorie);
	printf("Pret: %.2f\n\n", c.pret);
}

void afisareLista(ListaDubla lista) {
	Nod* p = lista.prim;
	while (p) {
		afisareCarte(p->info);
		p = p->next;
	}
}

void afisareListaInvers(ListaDubla lista) {
	Nod* p = lista.ultim;
	while (p) {
		afisareCarte(p->info);
		p = p->prev;
	}
}


void adaugareLaFinal(ListaDubla* lista, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;
	nou->next = NULL;
	nou->prev = NULL;

	if (lista->ultim) {
		nou->prev = lista->ultim;
		lista->ultim->next = nou;
		lista->ultim = nou;
	}
	else {
		lista->prim = nou;
		lista->ultim = nou;
	}
}

void adaugareLaInceput(ListaDubla* lista, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;
	nou->next = NULL;
	nou->prev = NULL;

	if (lista->prim) {
		nou->next = lista->prim;
		lista->prim->prev = nou;
		lista->prim = nou;
	}
	else {
		lista->prim = nou;
		lista->ultim = nou;
	}
}

void adaugaLaMijloc(ListaDubla* lista, Carte carteNoua, int pozitie) {
	if (pozitie <= 0) {
		adaugareLaInceput(lista, carteNoua);
		return;
	}

	Nod* p = lista->prim;
	int index = 0;

	while (p && index < pozitie - 1) {
		p = p->next;
		index++;
	}

	if (p == NULL || p == lista->ultim) {
		adaugareLaFinal(lista, carteNoua);
		return;
	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;

	nou->next = p->next;
	nou->prev = p;

	p->next->prev = nou;
	p->next = nou;
}


void dezalocareLista(ListaDubla* lista) {
	Nod* p = lista->prim;

	while (p) {
		Nod* aux = p;
		p = p->next;

		free(aux->info.titlu);
		free(aux->info.autor);
		free(aux->info.categorie);
		free(aux);
	}

	lista->prim = NULL;
	lista->ultim = NULL;
}

int main() {
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	Carte c1 = creeazaCarte(1, "Ion", "Liviu Rebreanu", "Roman", 35.5f);
	Carte c2 = creeazaCarte(2, "Poezii", "Mihai Eminescu", "Poezie", 22.0f);
	Carte c3 = creeazaCarte(3, "Baltagul", "Mihail Sadoveanu", "Roman politist", 28.9f);
	Carte c4 = creeazaCarte(4, "Clean Code", "Robert Martin", "Programare", 80.0f);
	Carte c5 = creeazaCarte(5, "Microeconomie", "Gregory Mankiw", "Economie", 65.5f);

	adaugareLaFinal(&lista, c1);
	adaugareLaFinal(&lista, c2);

	adaugareLaInceput(&lista, c3);

	adaugaLaMijloc(&lista, c4, 1);
	adaugaLaMijloc(&lista, c5, 2);

	printf("Lista afisata normal:\n\n");
	afisareLista(lista);

	printf("Lista afisata invers:\n\n");
	afisareListaInvers(lista);

	dezalocareLista(&lista);

	return 0;
}