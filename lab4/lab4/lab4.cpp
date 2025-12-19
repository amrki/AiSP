//4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se èitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortirani.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK             0
#define ERR_ALLOC      1
#define ERR_FILE       2
#define ERR_EMPTY      3

typedef struct Polynom {
    int koef;
    int exp;
    struct Polynom* next;
} Poly;

// ubaci (koef, exp) u listu silazno soritrano po exp i pdma spoji iste exp
int InsertSortedMerge(Poly** head, int koef, int exp) {
    if (koef == 0) return OK;

    Poly* prev = NULL;
    Poly* curr = *head;

    //silazno sort po exp
    while (curr && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    //ako isti exp sbroji koef
    if (curr && curr->exp == exp) {
        curr->koef += koef;
        //ako bude 0 brisi ga
        if (curr->koef == 0) {
            if (prev) prev->next = curr->next;
            else *head = curr->next;
            free(curr);
        }
        return OK;
    }

    Poly* novi = (Poly*)malloc(sizeof(Poly));
    if (!novi) return ERR_ALLOC;

    novi->koef = koef;
    novi->exp = exp;
    novi->next = curr;

    if (prev) prev->next = novi;
    else *head = novi;

    return OK;
}

void Free(Poly* head) {
    while (head) {
        Poly* next = head->next;
        free(head);
        head = next;
    }
}

void Ispis(Poly* head) {
    if (head == NULL) {
        printf("Prazna\n");
        return;
    }

    Poly* temp = head;
    int prvi = 1;

    while (temp != NULL) {
        if (temp->koef != 0) {
            if (!prvi && temp->koef > 0) printf("+");

            if (temp->exp == 0) {
                printf("%d", temp->koef);
            }
            else if (temp->exp == 1) {
                printf("%dx", temp->koef);
            }
            else {
                printf("%dx^%d", temp->koef, temp->exp);
            }
            prvi = 0;
        }
        temp = temp->next;
    }
    if (prvi) printf("0"); //ako sun svi koef 0
    printf("\n");
}

int ReadFile(const char* imeDat, Poly** head) {
    FILE* fp = fopen(imeDat, "r");
    if (!fp) {
        printf("Ne mogu otvoriti datoteku: %s\n", imeDat);
        return ERR_FILE;
    }

    *head = NULL;

    int koef = 0, exp = 0;
    while (fscanf(fp, "%dx^%d", &koef, &exp) == 2) {
        int st = InsertSortedMerge(head, koef, exp);
        if (st != OK) {
            fclose(fp);
            Free(*head);
            *head = NULL;
            return st;
        }
    }

    fclose(fp);
    if (*head == NULL) return ERR_EMPTY;
    return OK;
}

int ZbrojPoli(Poly* p1, Poly* p2, Poly** rez) {
    *rez = NULL;

    while (p1) {
        int st = InsertSortedMerge(rez, p1->koef, p1->exp);
        if (st != OK) { Free(*rez); *rez = NULL; return st; }
        p1 = p1->next;
    }

    while (p2) {
        int st = InsertSortedMerge(rez, p2->koef, p2->exp);
        if (st != OK) { Free(*rez); *rez = NULL; return st; }
        p2 = p2->next;
    }

    return (*rez == NULL) ? ERR_EMPTY : OK;
}

int PomnoziPoli(Poly* p1, Poly* p2, Poly** rez) {
    *rez = NULL;
    if (!p1 || !p2) return ERR_EMPTY;

    for (Poly* a = p1; a != NULL; a = a->next) {
        for (Poly* b = p2; b != NULL; b = b->next) {
            int noviKoef = a->koef * b->koef;
            int noviExp = a->exp + b->exp;

            int st = InsertSortedMerge(rez, noviKoef, noviExp);
            if (st != OK) { Free(*rez); *rez = NULL; return st; }
        }
    }

    return (*rez == NULL) ? ERR_EMPTY : OK;
}

int main() {
    Poly* head1 = NULL;
    Poly* head2 = NULL;
    Poly* sum = NULL;
    Poly* prod = NULL;

    int st1 = ReadFile("polinom1.txt", &head1);
    int st2 = ReadFile("polinom2.txt", &head2);

    if (st1 != OK || st2 != OK) {
        printf("Problem pri citanju datoteka\n");
        if (st1 == ERR_FILE || st2 == ERR_FILE) printf(" - datoteka\n");
        if (st1 == ERR_ALLOC || st2 == ERR_ALLOC) printf(" - alokacija\n");
        if (st1 == ERR_EMPTY || st2 == ERR_EMPTY) printf(" - prazno\n");
        Free(head1);
        Free(head2);
        return 1;
    }

    printf("Ispis prvog polinoma: \n");
    Ispis(head1);
    printf("Ispis drugog polinoma: \n");
    Ispis(head2);

    int st = ZbrojPoli(head1, head2, &sum);
    if (st == OK) {
        printf("Rezultat zbrajanja: \n");
        Ispis(sum);
    }
    else {
        printf("Zbrajanje nije uspilo\n");
    }

    st = PomnoziPoli(head1, head2, &prod);
    if (st == OK) {
        printf("Rezultat mnozenja: \n");
        Ispis(prod);
    }
    else {
        printf("Mnozenje nije uspilo\n");
    }

    Free(head1);
    Free(head2);
    Free(sum);
    Free(prod);

    return 0;
}
