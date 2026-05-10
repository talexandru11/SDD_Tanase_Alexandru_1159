#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student Student;
typedef struct Nod Nod;
typedef struct Stiva Stiva;

struct Student {
	int id;
	char* nume;
	char* facultate;
	float medie;
};

struct Nod {
	Student info;
	Nod* next;
};

struct Stiva {
	Nod* varf;
};

Student creeazaStudent(int id, const char* nume, const char* facultate, float medie) {
	Student s;
	s.id = id;
	s.medie = medie;

	s.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(s.nume, nume);

	s.facultate = (char*)malloc(strlen(facultate) + 1);
	strcpy(s.facultate, facultate);

	return s;
}

void afisareStudent(Student s) {
	printf("ID: %d\n", s.id);
	printf("Nume: %s\n", s.nume);
	printf("Facultate: %s\n", s.facultate);
	printf("Medie: %.2f\n\n", s.medie);
}

void push(Stiva* stiva, Student studentNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = studentNou;
	nou->next = stiva->varf;

	stiva->varf = nou;
}

Student pop(Stiva* stiva) {
	if (stiva->varf == NULL) {
		printf("Stiva este goala!\n");

		Student s;
		s.id = -1;
		s.nume = NULL;
		s.facultate = NULL;
		s.medie = 0;
		return s;
	}

	Nod* aux = stiva->varf;
	Student studentExtras = aux->info;

	stiva->varf = stiva->varf->next;
	free(aux);

	return studentExtras;
}

void afisareStiva(Stiva stiva) {
	Nod* p = stiva.varf;

	while (p) {
		afisareStudent(p->info);
		p = p->next;
	}
}

void dezalocareStudent(Student s) {
	free(s.nume);
	free(s.facultate);
}

void dezalocareStiva(Stiva* stiva) {
	Nod* p = stiva->varf;

	while (p) {
		Nod* aux = p;
		p = p->next;

		dezalocareStudent(aux->info);
		free(aux);
	}

	stiva->varf = NULL;
}

int main() {
	Stiva stiva;
	stiva.varf = NULL;

	Student s1 = creeazaStudent(1, "Andrei Popescu", "Informatica", 9.25f);
	Student s2 = creeazaStudent(2, "Maria Ionescu", "Cibernetica", 8.70f);
	Student s3 = creeazaStudent(3, "Vlad Georgescu", "Economie", 7.95f);
	Student s4 = creeazaStudent(4, "Ioana Marin", "Marketing", 9.60f);

	push(&stiva, s1);
	push(&stiva, s2);
	push(&stiva, s3);
	push(&stiva, s4);

	printf("Stiva initiala:\n\n");
	afisareStiva(stiva);

	printf("Student extras din stiva:\n\n");
	Student extras = pop(&stiva);
	afisareStudent(extras);

	dezalocareStudent(extras);

	printf("Stiva dupa pop:\n\n");
	afisareStiva(stiva);

	dezalocareStiva(&stiva);

	return 0;
}