#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* nume;
	int varsta;
	float salariu;
} Angajat;

Angajat Initializare(const char* nume, int varsta, float salariu) {
	Angajat a;
	a.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy_s(a.nume, strlen(nume) + 1, nume);
	a.varsta = varsta;
	a.salariu = salariu;
	return a;
}



void Afisare(Angajat a) {
	printf("Angajatul %s in varsta de %d ani are un salariu de %5.2f RON.\n", a.nume, a.varsta, a.salariu);
}

void AfisareVector(Angajat* vector, int nrAngajati) {
	for (int i = 0; i < nrAngajati; i++) {
		Afisare(vector[i]);
	}
}

void AdaugareAngajatInVector(Angajat** vector, int* nrAngajati, Angajat angajatNou) {
	Angajat* aux = (Angajat*)malloc(sizeof(Angajat) * (*nrAngajati + 1));
	for (int i = 0; i < (*nrAngajati);i++) {
		aux[i] = (*vector)[i];
	}
	aux[(*nrAngajati)] = angajatNou;
	free(*vector);
	(*vector) = aux;
	(*nrAngajati)++;
}

Angajat citireAngajatFisier(FILE* file) {
	Angajat a;
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, file);
	char* aux;
	aux = strtok(buffer, sep);
	a.nume = (char*)malloc(strlen(aux)+1);
	strcpy(a.nume, aux);
	a.varsta = atoi(strtok(NULL, sep));
	a.salariu = atof(strtok(NULL, sep));
	return a;
}

Angajat* citireVectorAngajatiFisier(const char* numeFisier, int* nrAngajatiCititi) {
	FILE* file = fopen(numeFisier, "r");
	Angajat* angajati = NULL;
	(*nrAngajatiCititi) = 0;
	while (!feof(file)) {
		AdaugareAngajatInVector(&angajati, nrAngajatiCititi, citireAngajatFisier(file));
	}
	fclose(file);
	return angajati;
}

void Dezalocare(Angajat* a) {
	if (a->nume != NULL) {
		free(a->nume);
	};
	a->nume = NULL;
	a->varsta = 0;
	a->salariu = 0;
}

void DezalocareVector(Angajat** angajati, int *nrAngajati) {
	for (int i = 0; i < (*nrAngajati); i++)
	{
		Dezalocare(&(*angajati)[i]);
	}
}

int main() {
	//Angajat a = Initializare("George", 20, 3500);
	//Angajat* angajati = NULL;
	//int nrAngajati = 3;
	//angajati = (Angajat*)malloc((sizeof(Angajat) * nrAngajati));
	//angajati[0] = Initializare("Andrei", 24, 3457);
	//angajati[1] = Initializare("Stefan", 25, 6700);
	//angajati[2] = Initializare("Marius", 40, 24500);
	//Angajat angajatNou = Initializare("Bob", 19, 2000);
	//AdaugareAngajatInVector(&angajati, &nrAngajati, angajatNou);
	//AfisareVector(angajati, nrAngajati);

	int nrAngajati = 0;
	Angajat* angajati = citireVectorAngajatiFisier("angajati.txt", &nrAngajati);
	AfisareVector(angajati, nrAngajati);

}