//7. Napisati program koji pomoæu vezanih listi simulira rad: 
//a) cirkularnog stoga (maksimalni broj elemenata na stogu definira korisnik kad se program pokrene), 
//b) reda s prioritetom (prioritet može biti od 1-5 i generira se sluèajno, a veæi broj znaèi i veæi prioritet). 
//Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10-100.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Stog {
    int elem;
    struct Stog* next;
}Stog;

typedef struct Red {
    int elem;
    int prioritet;
    struct Red* next;
}Red;

int velicinaStoga(Stog* head) {
    if (head == NULL) {
        return 0;
    }

    int brojac = 1;
    Stog* temp = head;

    while (temp->next != head) {
        brojac++;
        temp = temp->next;
    }
    return brojac;
}

Stog* Push(Stog* head, int maxVelicina) {
    int slucBr = rand() % 91 + 10;        //gen broj od 10-100

    Stog* novi = (Stog*)malloc(sizeof(Stog));
    if (novi == NULL) {
        printf("GRESKA!\n");
        return head;
    }

    novi->elem = slucBr;

    if (head == NULL) {                         //ako je stog prazan
        novi->next = novi;                      //pokazuje sam na sebe
        printf("Stog je prazan\n");
        printf("PUSH: %d\n", slucBr);
        return novi;
    }

    int trenutnaVelicina = velicinaStoga(head);

    if (trenutnaVelicina >= maxVelicina) {      //stog je pun = brisemo najstariji
        Stog* temp = head;
        Stog* prev = NULL;

        while (temp->next != head) {            //idemo do zadnjeg
            prev = temp;
            temp = temp->next;
        }

        if (temp == head) {                     //ako ima samo jedan elem
            head = novi;
            novi->next = novi;
            printf("PUSH: %d\n", slucBr);
            printf("Obrisan najstariji %d\n", temp->elem);
            free(temp);
        }
        else {
            prev->next = head;                  //predzadnji pokazuje na head
            novi->next = head;                  //novi na head
            printf("PUSH: %d\n", slucBr);
            printf("Obrisan najstariji %d\n", temp->elem);
            free(temp);
            return novi;                        //novi je novi head
        }
    }
    else {                                      //ima mista na stogu
        novi->next = head;                      //novi pokazuje na head

        Stog* temp = head;
        while (temp->next != head) {            //idemo do zadnjeg
            temp = temp->next;
        }
        temp->next = novi;                      //zadnji pokazuje na novi
        printf("PUSH: %d\n", slucBr);
        return novi;                            //novi postaje head
    }

    return head;
}

int Pop(Stog** head) {
    if (*head == NULL) {
        printf("Stog prazan\n");
        return -1;
    }

    Stog* temp = *head;
    int vrijednost = temp->elem;

    if (temp->next == temp) {                   //ako ima samo jedan elem
        *head = NULL;
        free(temp);
        printf("Stog prazan\n");
        printf("POP: %d\n", vrijednost);
        return vrijednost;
    }

    Stog* zadnji = *head;
    while (zadnji->next != *head) {             //idemo do zadnjeg
        zadnji = zadnji->next;
    }

    *head = temp->next;                         //head postaje iduci
    zadnji->next = *head;                       //zadnji pokazuje na novi head
    free(temp);

    printf("POP: %d\n", vrijednost);
    return vrijednost;
}

void ispisStoga(Stog* head) {
    if (head == NULL) {
        printf("Stog je prazan\n");
        return;
    }

    Stog* temp = head;
    printf("Stog: ");

    do {
        printf("%d ", temp->elem);
        temp = temp->next;
    } while (temp != head);                     //dok ne dodemo opet do heada

    printf("\n");
}

void obrisiStog(Stog* head) {
    if (head == NULL) return;

    Stog* temp = head;
    Stog* next;

    do {
        next = temp->next;
        free(temp);
        temp = next;
    } while (temp != head);
}

Red* Enqueue(Red* head) {
    int slucBr = rand() % 91 + 10;              //opet gen broj od 10-100
    int slucPrioritet = rand() % 5 + 1;         //gen prioritet od 1-5

    Red* novi = (Red*)malloc(sizeof(Red));
    if (novi == NULL) {
        printf("GRESKA!\n");
        return head;
    }

    novi->elem = slucBr;
    novi->prioritet = slucPrioritet;
    novi->next = NULL;

    if (head == NULL || head->prioritet < slucPrioritet) {                  //ako je lista prazna ili novi ima veci prioritet
        novi->next = head;
        printf("Prioritet: % d\n", slucPrioritet);
        printf("ENQUEUE: %d\n", slucBr);
        return novi;
    }

    Red* temp = head;
    while (temp->next != NULL && temp->next->prioritet >= slucPrioritet) {  //trazimo misto po prioritetu
        temp = temp->next;
    }

    novi->next = temp->next;
    temp->next = novi;

    printf("Prioritet: % d\n", slucPrioritet);
    printf("ENQUEUE: %d\n", slucBr);
    return head;
}

int Dequeue(Red** head) {
    if (*head == NULL) {
        printf("Red je prazan\n");
        return -1;
    }

    Red* temp = *head;
    int value = temp->elem;
    int prioritet = temp->prioritet;

    *head = temp->next;
    free(temp);

    printf("DEQUEUE: %d\n", value);
    return value;
}

void ispisReda(Red* head) {
    if (head == NULL) {
        printf("Red prazan\n");
        return;
    }

    Red* temp = head;
    printf("Red: ");

    while (temp != NULL) {
        printf("%d(P:%d) ", temp->elem, temp->prioritet);
        temp = temp->next;
    }

    printf("\n");
}

void obrisiRed(Red* head) {
    Red* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    srand(time(NULL));                          //za random brojeve

    Stog* stog = NULL;
    Red* red = NULL;
    int unos = 0;
    int maxVelicina = 0;

    printf("Unesite max vel cirk stoga: ");
    scanf("%d", &maxVelicina);

    if (maxVelicina <= 0) {
        printf("Moraa bit veca od 0\n");
        return 1;
    }

    do {
        printf("CIRKULARNI STOG:\n");
        printf("1 - PUSH\n");
        printf("2 - POP\n");
        printf("3 - Ispis stoga\n");
        printf("RED S PRIORITETOM:\n");
        printf("4 - ENQUEUE\n");
        printf("5 - DEQUEUE\n");
        printf("6 - Ispis reda\n");
        printf("0 - Izlaz\n");
        printf("\nIzbor: ");
        scanf("%d", &unos);

        switch (unos) {
        case 0:
            printf("Izlaz\n");
            break;
        case 1:
            stog = Push(stog, maxVelicina);
            break;
        case 2:
            Pop(&stog);
            break;
        case 3:
            ispisStoga(stog);
            break;
        case 4:
            red = Enqueue(red);
            break;
        case 5:
            Dequeue(&red);
            break;
        case 6:
            ispisReda(red);
            break;
        default:
            printf("NE MOZE\n");
        }
    } while (unos != 0);

    obrisiStog(stog);
    obrisiRed(red);

    return 0;
}
