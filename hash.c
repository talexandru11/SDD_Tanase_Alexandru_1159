#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
#define MAX_VALOARE 50

typedef struct Nod {
    int cheie;
    char valoare[MAX_VALOARE];
    struct Nod* next;
} Nod;

Nod* tabelaHash[SIZE];

int hashFunction(int cheie) {
    return cheie % SIZE;
}

void adauga(int cheie, const char valoare[]) {
    int poz = hashFunction(cheie);

    Nod* nou = malloc(sizeof(Nod));
    if (nou == NULL) {
        printf("Eroare la alocarea memoriei!\n");
        return;
    }

    nou->cheie = cheie;
    strncpy(nou->valoare, valoare, MAX_VALOARE - 1);
    nou->valoare[MAX_VALOARE - 1] = '\0';

    nou->next = tabelaHash[poz];
    tabelaHash[poz] = nou;
}

void afisare() {
    for (int i = 0; i < SIZE; i++) {
        printf("%d -> ", i);

        Nod* p = tabelaHash[i];

        while (p != NULL) {
            printf("(%d %s) ", p->cheie, p->valoare);
            p = p->next;
        }

        printf("\n");
    }
}

void eliberareMemorie() {
    for (int i = 0; i < SIZE; i++) {
        Nod* p = tabelaHash[i];

        while (p != NULL) {
            Nod* temp = p;
            p = p->next;
            free(temp);
        }

        tabelaHash[i] = NULL;
    }
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        tabelaHash[i] = NULL;
    }

    adauga(1, "Roman");
    adauga(2, "Poezie");
    adauga(7, "IT");
    adauga(12, "Economie");

    afisare();

    eliberareMemorie();

    return 0;
}