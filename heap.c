#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produs Produs;
typedef struct Heap Heap;

struct Produs {
	int id;
	char* denumire;
	char* categorie;
	float pret;
};

struct Heap {
	Produs* vector;
	int dimensiune;
	int capacitate;
};

Produs creeazaProdus(int id, const char* denumire, const char* categorie, float pret) {
	Produs p;
	p.id = id;
	p.pret = pret;

	p.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(p.denumire, denumire);

	p.categorie = (char*)malloc(strlen(categorie) + 1);
	strcpy(p.categorie, categorie);

	return p;
}

void afisareProdus(Produs p) {
	printf("ID: %d\n", p.id);
	printf("Denumire: %s\n", p.denumire);
	printf("Categorie: %s\n", p.categorie);
	printf("Pret: %.2f\n\n", p.pret);
}

void interschimbare(Produs* p1, Produs* p2) {
	Produs aux = *p1;
	*p1 = *p2;
	*p2 = aux;
}

void filtrareSus(Heap* heap, int index) {
	while (index > 0) {
		int parinte = (index - 1) / 2;

		if (heap->vector[index].pret > heap->vector[parinte].pret) {
			interschimbare(&heap->vector[index], &heap->vector[parinte]);
			index = parinte;
		}
		else {
			break;
		}
	}
}

void filtrareJos(Heap* heap, int index) {
	int stanga = 2 * index + 1;
	int dreapta = 2 * index + 2;
	int maxim = index;

	if (stanga < heap->dimensiune &&
		heap->vector[stanga].pret > heap->vector[maxim].pret) {
		maxim = stanga;
	}

	if (dreapta < heap->dimensiune &&
		heap->vector[dreapta].pret > heap->vector[maxim].pret) {
		maxim = dreapta;
	}

	if (maxim != index) {
		interschimbare(&heap->vector[index], &heap->vector[maxim]);
		filtrareJos(heap, maxim);
	}
}

void inserareHeap(Heap* heap, Produs produsNou) {
	if (heap->dimensiune == heap->capacitate) {
		printf("Heap-ul este plin!\n");
		return;
	}

	heap->vector[heap->dimensiune] = produsNou;
	filtrareSus(heap, heap->dimensiune);
	heap->dimensiune++;
}

Produs extrageMaxim(Heap* heap) {
	if (heap->dimensiune == 0) {
		printf("Heap-ul este gol!\n");

		Produs p;
		p.id = -1;
		p.denumire = NULL;
		p.categorie = NULL;
		p.pret = 0;
		return p;
	}

	Produs maxim = heap->vector[0];

	heap->vector[0] = heap->vector[heap->dimensiune - 1];
	heap->dimensiune--;

	filtrareJos(heap, 0);

	return maxim;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.dimensiune; i++) {
		afisareProdus(heap.vector[i]);
	}
}

void dezalocareProdus(Produs p) {
	free(p.denumire);
	free(p.categorie);
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->dimensiune; i++) {
		dezalocareProdus(heap->vector[i]);
	}

	free(heap->vector);

	heap->vector = NULL;
	heap->dimensiune = 0;
	heap->capacitate = 0;
}

int main() {
	Heap heap;
	heap.dimensiune = 0;
	heap.capacitate = 10;
	heap.vector = (Produs*)malloc(sizeof(Produs) * heap.capacitate);

	Produs p1 = creeazaProdus(1, "Laptop", "Electronice", 3500.0f);
	Produs p2 = creeazaProdus(2, "Mouse", "Electronice", 150.0f);
	Produs p3 = creeazaProdus(3, "Tastatura", "Electronice", 300.0f);
	Produs p4 = creeazaProdus(4, "Monitor", "Electronice", 900.0f);
	Produs p5 = creeazaProdus(5, "Telefon", "Electronice", 4200.0f);

	inserareHeap(&heap, p1);
	inserareHeap(&heap, p2);
	inserareHeap(&heap, p3);
	inserareHeap(&heap, p4);
	inserareHeap(&heap, p5);

	printf("Heap initial max-heap dupa pret:\n\n");
	afisareHeap(heap);

	printf("Produs extras cu pret maxim:\n\n");
	Produs extras = extrageMaxim(&heap);
	afisareProdus(extras);

	dezalocareProdus(extras);

	printf("Heap dupa extragere:\n\n");
	afisareHeap(heap);

	dezalocareHeap(&heap);

	return 0;
}