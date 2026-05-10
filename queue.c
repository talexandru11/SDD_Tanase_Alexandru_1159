#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Comanda Comanda;
typedef struct Nod Nod;
typedef struct Coada Coada;

struct Comanda {
	int id;
	char* client;
	char* produs;
	int cantitate;
	float pretTotal;
};

struct Nod {
	Comanda info;
	Nod* next;
};

struct Coada {
	Nod* prim;
	Nod* ultim;
};

Comanda creeazaComanda(int id, const char* client, const char* produs, int cantitate, float pretTotal) {
	Comanda c;
	c.id = id;
	c.cantitate = cantitate;
	c.pretTotal = pretTotal;

	c.client = (char*)malloc(strlen(client) + 1);
	strcpy(c.client, client);

	c.produs = (char*)malloc(strlen(produs) + 1);
	strcpy(c.produs, produs);

	return c;
}

void afisareComanda(Comanda c) {
	printf("ID: %d\n", c.id);
	printf("Client: %s\n", c.client);
	printf("Produs: %s\n", c.produs);
	printf("Cantitate: %d\n", c.cantitate);
	printf("Pret total: %.2f\n\n", c.pretTotal);
}

void enqueue(Coada* coada, Comanda comandaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = comandaNoua;
	nou->next = NULL;

	if (coada->ultim) {
		coada->ultim->next = nou;
		coada->ultim = nou;
	}
	else {
		coada->prim = nou;
		coada->ultim = nou;
	}
}

Comanda dequeue(Coada* coada) {
	if (coada->prim == NULL) {
		printf("Coada este goala!\n");

		Comanda c;
		c.id = -1;
		c.client = NULL;
		c.produs = NULL;
		c.cantitate = 0;
		c.pretTotal = 0;
		return c;
	}

	Nod* aux = coada->prim;
	Comanda comandaExtrasa = aux->info;

	coada->prim = coada->prim->next;

	if (coada->prim == NULL) {
		coada->ultim = NULL;
	}

	free(aux);

	return comandaExtrasa;
}

void afisareCoada(Coada coada) {
	Nod* p = coada.prim;

	while (p) {
		afisareComanda(p->info);
		p = p->next;
	}
}

void dezalocareComanda(Comanda c) {
	free(c.client);
	free(c.produs);
}

void dezalocareCoada(Coada* coada) {
	Nod* p = coada->prim;

	while (p) {
		Nod* aux = p;
		p = p->next;

		dezalocareComanda(aux->info);
		free(aux);
	}

	coada->prim = NULL;
	coada->ultim = NULL;
}

int main() {
	Coada coada;
	coada.prim = NULL;
	coada.ultim = NULL;

	Comanda c1 = creeazaComanda(1, "Andrei Popescu", "Laptop", 1, 3500.0f);
	Comanda c2 = creeazaComanda(2, "Maria Ionescu", "Mouse", 2, 150.0f);
	Comanda c3 = creeazaComanda(3, "Vlad Georgescu", "Tastatura", 1, 300.0f);
	Comanda c4 = creeazaComanda(4, "Ioana Marin", "Monitor", 1, 900.0f);

	enqueue(&coada, c1);
	enqueue(&coada, c2);
	enqueue(&coada, c3);
	enqueue(&coada, c4);

	printf("Coada initiala:\n\n");
	afisareCoada(coada);

	printf("Comanda extrasa din coada:\n\n");
	Comanda extrasa = dequeue(&coada);
	afisareComanda(extrasa);

	dezalocareComanda(extrasa);

	printf("Coada dupa dequeue:\n\n");
	afisareCoada(coada);

	dezalocareCoada(&coada);

	return 0;
}