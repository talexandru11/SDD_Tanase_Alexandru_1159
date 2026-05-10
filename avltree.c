#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	int id;
	char* marca;
	char* model;
	int anFabricatie;
	float pret;
};

struct Nod {
	Masina info;
	Nod* stanga;
	Nod* dreapta;
	int inaltime;
};

Masina creeazaMasina(int id, const char* marca, const char* model, int anFabricatie, float pret) {
	Masina m;
	m.id = id;
	m.anFabricatie = anFabricatie;
	m.pret = pret;

	m.marca = (char*)malloc(strlen(marca) + 1);
	strcpy(m.marca, marca);

	m.model = (char*)malloc(strlen(model) + 1);
	strcpy(m.model, model);

	return m;
}

void afisareMasina(Masina m) {
	printf("ID: %d\n", m.id);
	printf("Marca: %s\n", m.marca);
	printf("Model: %s\n", m.model);
	printf("An fabricatie: %d\n", m.anFabricatie);
	printf("Pret: %.2f\n\n", m.pret);
}

int maxim(int a, int b) {
	return a > b ? a : b;
}

int inaltime(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}

	return radacina->inaltime;
}

int factorEchilibru(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}

	return inaltime(radacina->stanga) - inaltime(radacina->dreapta);
}

Nod* rotireDreapta(Nod* y) {
	Nod* x = y->stanga;
	Nod* T2 = x->dreapta;

	x->dreapta = y;
	y->stanga = T2;

	y->inaltime = maxim(inaltime(y->stanga), inaltime(y->dreapta)) + 1;
	x->inaltime = maxim(inaltime(x->stanga), inaltime(x->dreapta)) + 1;

	return x;
}

Nod* rotireStanga(Nod* x) {
	Nod* y = x->dreapta;
	Nod* T2 = y->stanga;

	y->stanga = x;
	x->dreapta = T2;

	x->inaltime = maxim(inaltime(x->stanga), inaltime(x->dreapta)) + 1;
	y->inaltime = maxim(inaltime(y->stanga), inaltime(y->dreapta)) + 1;

	return y;
}

Nod* inserareAVL(Nod* radacina, Masina masinaNoua) {
	if (radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		nou->inaltime = 1;
		return nou;
	}

	if (masinaNoua.anFabricatie < radacina->info.anFabricatie) {
		radacina->stanga = inserareAVL(radacina->stanga, masinaNoua);
	}
	else if (masinaNoua.anFabricatie > radacina->info.anFabricatie) {
		radacina->dreapta = inserareAVL(radacina->dreapta, masinaNoua);
	}
	else {
		return radacina;
	}

	radacina->inaltime = 1 + maxim(inaltime(radacina->stanga), inaltime(radacina->dreapta));

	int echilibru = factorEchilibru(radacina);

	if (echilibru > 1 && masinaNoua.anFabricatie < radacina->stanga->info.anFabricatie) {
		return rotireDreapta(radacina);
	}

	if (echilibru < -1 && masinaNoua.anFabricatie > radacina->dreapta->info.anFabricatie) {
		return rotireStanga(radacina);
	}

	if (echilibru > 1 && masinaNoua.anFabricatie > radacina->stanga->info.anFabricatie) {
		radacina->stanga = rotireStanga(radacina->stanga);
		return rotireDreapta(radacina);
	}

	if (echilibru < -1 && masinaNoua.anFabricatie < radacina->dreapta->info.anFabricatie) {
		radacina->dreapta = rotireDreapta(radacina->dreapta);
		return rotireStanga(radacina);
	}

	return radacina;
}

void afisareInordine(Nod* radacina) {
	if (radacina) {
		afisareInordine(radacina->stanga);
		afisareMasina(radacina->info);
		afisareInordine(radacina->dreapta);
	}
}

void afisarePreordine(Nod* radacina) {
	if (radacina) {
		afisareMasina(radacina->info);
		afisarePreordine(radacina->stanga);
		afisarePreordine(radacina->dreapta);
	}
}

Nod* cautareDupaAn(Nod* radacina, int anFabricatie) {
	if (radacina == NULL) {
		return NULL;
	}

	if (radacina->info.anFabricatie == anFabricatie) {
		return radacina;
	}

	if (anFabricatie < radacina->info.anFabricatie) {
		return cautareDupaAn(radacina->stanga, anFabricatie);
	}
	else {
		return cautareDupaAn(radacina->dreapta, anFabricatie);
	}
}

void dezalocareMasina(Masina m) {
	free(m.marca);
	free(m.model);
}

void dezalocareAVL(Nod* radacina) {
	if (radacina) {
		dezalocareAVL(radacina->stanga);
		dezalocareAVL(radacina->dreapta);

		dezalocareMasina(radacina->info);
		free(radacina);
	}
}

int main() {
	Nod* radacina = NULL;

	Masina m1 = creeazaMasina(1, "Dacia", "Logan", 2018, 7500.0f);
	Masina m2 = creeazaMasina(2, "BMW", "Seria 3", 2021, 27000.0f);
	Masina m3 = creeazaMasina(3, "Audi", "A4", 2020, 24000.0f);
	Masina m4 = creeazaMasina(4, "Toyota", "Corolla", 2019, 16000.0f);
	Masina m5 = creeazaMasina(5, "Volkswagen", "Golf", 2017, 12000.0f);
	Masina m6 = creeazaMasina(6, "Mercedes", "C Class", 2022, 35000.0f);

	radacina = inserareAVL(radacina, m1);
	radacina = inserareAVL(radacina, m2);
	radacina = inserareAVL(radacina, m3);
	radacina = inserareAVL(radacina, m4);
	radacina = inserareAVL(radacina, m5);
	radacina = inserareAVL(radacina, m6);

	printf("Afisare inordine - masini sortate dupa an:\n\n");
	afisareInordine(radacina);

	printf("Afisare preordine - structura arborelui:\n\n");
	afisarePreordine(radacina);

	printf("Cautare masina fabricata in 2020:\n\n");
	Nod* gasit = cautareDupaAn(radacina, 2020);

	if (gasit) {
		afisareMasina(gasit->info);
	}
	else {
		printf("Masina nu a fost gasita.\n");
	}

	dezalocareAVL(radacina);

	return 0;
}