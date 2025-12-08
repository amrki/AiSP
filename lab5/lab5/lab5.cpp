// 5. Za dvije sortirane liste L1 i L2 (mogu se pročitati iz datoteke ili unijeti ručno, bitno je samo da su
//sortirane), napisati program koji stvara novu vezanu listu tako da računa :
//a) L1∪L2,
//b) L1∩ L2.
//Liste osim pokazivača na slijedeću strukturu imaju i jedan cjelobrojni element, po kojem su
//sortirane
//

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Cvor {
    int elem;
    struct Cvor* next;
}Cvor;

void Ispis(Cvor* head) {
    if (head == NULL) {                         //provjeraaa
        printf("Lista je prazna\n");
        return;
    }

    Cvor* temp = head;

    printf("Lista: ");
    while (temp != NULL) {                      //prolazin kroz listu
        printf("%d ", temp->elem);
        temp = temp->next;
    }
    printf("\n");
}

int Unos(Cvor** head, int broj) {
    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));

    if (novi == NULL) {
        printf("GRESKA!\n");
        return -1;
    }
    novi->elem = broj;
    novi->next = NULL;

    if (*head == NULL || (*head)->elem >= broj) {   //ako je lista prazna ili novi element ide na pocetak
        novi->next = *head;
        *head = novi;
        return 0;
    }

    Cvor* temp = *head;
    while (temp->next != NULL && temp->next->elem < broj) {
        temp = temp->next;
    }

    novi->next = temp->next;
    temp->next = novi;

    return 0;
}

Cvor* unosListe(int brListe) {
    Cvor* head = NULL;
    int n = 0;
    int broj = 0;

    printf("\nUnos liste L%d\n", brListe);
    printf("Koliko elem zelite unit? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Lista ostaje prazna\n");
        return NULL;
    }

    printf("Unesite %d sortiranih br (od manjeg prema vecem): \n", n);
    for (int i = 0; i < n; i++) {
        printf("Elem %d: ", i + 1);
        scanf("%d", &broj);
        Unos(&head, broj);                       //dodala elem na sortirano misto
    }

    return head;
}

Cvor* Unija(Cvor* L1, Cvor* L2) {
    Cvor* rez = NULL;
    Cvor* temp1 = L1;
    Cvor* temp2 = L2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->elem < temp2->elem) {        //ako je elem iz l1 manji ide u rez
            Unos(&rez, temp1->elem);
            temp1 = temp1->next;
        }
        else if (temp1->elem > temp2->elem) {   //ako je elem iz l1 manji ide u rez
            Unos(&rez, temp2->elem);
            temp2 = temp2->next;
        }
        else {
            Unos(&rez, temp1->elem);            //ako jednaki dodajemo jedan od njih
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) {                     //dodat ostale iz l1
        Unos(&rez, temp1->elem);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {                     //dodat ostale iz l2
        Unos(&rez, temp2->elem);
        temp2 = temp2->next;
    }

    return rez;
}
Cvor* Presjek(Cvor* L1, Cvor* L2) {
    Cvor* rez = NULL;
    Cvor* temp1 = L1;
    Cvor* temp2 = L2;

    while (temp1 != NULL && temp2 != NULL) {

        if (temp1->elem < temp2->elem) {        //preskacemo ga ako je manji
            temp1 = temp1->next;
        }
        else if (temp1->elem > temp2->elem) {   //prekacemo ga ako je manji
            temp2 = temp2->next;
        }
        else {                                  //nalaze se u obe lste
            Unos(&rez, temp1->elem);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    return rez;
}

void freeMem(Cvor* head) {
    Cvor* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    Cvor* L1 = NULL;
    Cvor* L2 = NULL;
    Cvor* unijaRez = NULL;
    Cvor* presjekRez = NULL;

    L1 = unosListe(1);
    printf("\nUnesena ");
    Ispis(L1);

    L2 = unosListe(2);
    printf("\nUnesena ");
    Ispis(L2);

    unijaRez = Unija(L1, L2);
    printf("\nL1 U L2 (Unija): ");
    Ispis(unijaRez);

    presjekRez = Presjek(L1, L2);
    printf("L1 n L2 (Presjek): ");
    Ispis(presjekRez);

    freeMem(L1);
    freeMem(L2);
    freeMem(unijaRez);
    freeMem(presjekRez);

    return 0;
}

