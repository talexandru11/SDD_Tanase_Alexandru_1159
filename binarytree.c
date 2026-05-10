#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;

struct Angajat {
	int id;
	char* nume;
	char* departament;
	float salariu;
};

struct Nod {
	Angajat info;
	Nod* stanga;
	Nod* dreapta;
};

Angajat creeazaAngajat(int id, const char* nume, const char* departament, float salariu) {
	Angajat a;
	a.id = id;
	a.salariu = salariu;

	a.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(a.nume, nume);

	a.departament = (char*)malloc(strlen(departament) + 1);
	strcpy(a.departament, departament);

	return a;
}

void afisareAngajat(Angajat a) {
	printf("ID: %d\n", a.id);
	printf("Nume: %s\n", a.nume);
	printf("Departament: %s\n", a.departament);
	printf("Salariu: %.2f\n\n", a.salariu);
}

Nod* inserareArbore(Nod* radacina, Angajat angajatNou) {
	if (radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = angajatNou;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		return nou;
	}

	if (angajatNou.salariu < radacina->info.salariu) {
		radacina->stanga = inserareArbore(radacina->stanga, angajatNou);
	}
	else {
		radacina->dreapta = inserareArbore(radacina->dreapta, angajatNou);
	}

	return radacina;
}

void afisareInordine(Nod* radacina) {
	if (radacina) {
		afisareInordine(radacina->stanga);
		afisareAngajat(radacina->info);
		afisareInordine(radacina->dreapta);
	}
}

void afisarePreordine(Nod* radacina) {
	if (radacina) {
		afisareAngajat(radacina->info);
		afisarePreordine(radacina->stanga);
		afisarePreordine(radacina->dreapta);
	}
}

void afisarePostordine(Nod* radacina) {
	if (radacina) {
		afisarePostordine(radacina->stanga);
		afisarePostordine(radacina->dreapta);
		afisareAngajat(radacina->info);
	}
}

Nod* cautareDupaSalariu(Nod* radacina, float salariu) {
	if (radacina == NULL) {
		return NULL;
	}

	if (radacina->info.salariu == salariu) {
		return radacina;
	}

	if (salariu < radacina->info.salariu) {
		return cautareDupaSalariu(radacina->stanga, salariu);
	}
	else {
		return cautareDupaSalariu(radacina->dreapta, salariu);
	}
}

void dezalocareAngajat(Angajat a) {
	free(a.nume);
	free(a.departament);
}

void dezalocareArbore(Nod* radacina) {
	if (radacina) {
		dezalocareArbore(radacina->stanga);
		dezalocareArbore(radacina->dreapta);

		dezalocareAngajat(radacina->info);
		free(radacina);
	}
}

int main() {
	Nod* radacina = NULL;

	Angajat a1 = creeazaAngajat(1, "Andrei Popescu", "IT", 5500.0f);
	Angajat a2 = creeazaAngajat(2, "Maria Ionescu", "HR", 4200.0f);
	Angajat a3 = creeazaAngajat(3, "Vlad Georgescu", "Financiar", 7000.0f);
	Angajat a4 = creeazaAngajat(4, "Ioana Marin", "Marketing", 4800.0f);
	Angajat a5 = creeazaAngajat(5, "Radu Stan", "Vanzari", 6200.0f);

	radacina = inserareArbore(radacina, a1);
	radacina = inserareArbore(radacina, a2);
	radacina = inserareArbore(radacina, a3);
	radacina = inserareArbore(radacina, a4);
	radacina = inserareArbore(radacina, a5);

	printf("Afisare inordine - salarii crescatoare:\n\n");
	afisareInordine(radacina);

	printf("Afisare preordine:\n\n");
	afisarePreordine(radacina);

	printf("Afisare postordine:\n\n");
	afisarePostordine(radacina);

	printf("Cautare angajat cu salariul 6200:\n\n");
	Nod* gasit = cautareDupaSalariu(radacina, 6200.0f);

	if (gasit) {
		afisareAngajat(gasit->info);
	}
	else {
		printf("Angajatul nu a fost gasit.\n");
	}

	dezalocareArbore(radacina);

	return 0;
}