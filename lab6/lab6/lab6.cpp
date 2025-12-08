//6. Napisati program koji pomoæu vezanih listi simulira rad :
//a) stoga,
//b) reda.
//Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 - 100.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Cvor {
    int elem;
    struct Cvor* next;
}Cvor;

int Push(Cvor** head) {
    int broj = rand() % 91 + 10;

    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
    if (novi == NULL) {
        printf("GRESKA\n");
        return -1;
    }

    novi->elem = broj;
    novi->next = *head;                         //novi cvor pokazuje na stari vrh
    *head = novi;                               //novi cvor postaje vrh stoga

    printf("Dodan %d\n", broj);
    return 0;
}

int Pop(Cvor** head) {
    if (*head == NULL) {
        printf("Stog je prazan\n");
        return -1;
    }

    Cvor* temp = *head;
    int broj = temp->elem;
    *head = (*head)->next;                      //head pokazuje na sljedeci
    free(temp);

    printf("Uklonjen %d\n", broj);
    return 0;
}

void ispisStog(Cvor* head) {
    if (head == NULL) {                         //provjera
        printf("Stog prazan\n");
        return;
    }

    Cvor* temp = head;
    printf("Stog: ");
    while (temp != NULL) {
        printf("%d ", temp->elem);
        temp = temp->next;
    }
    printf("\n");
}

int enqueue(Cvor** head, Cvor** zadnji) {
    int broj = rand() % 91 + 10;

    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
    if (novi == NULL) {
        printf("GRESKA\n");
        return -1;
    }

    novi->elem = broj;
    novi->next = NULL;

    if (*zadnji == NULL) {                      //red prazan
        *head = novi;
        *zadnji = novi;
    }
    else {                                      //dodajen na kraj
        (*zadnji)->next = novi;
        *zadnji = novi;
    }

    printf("Dodan %d\n", broj);
    return 0;
}

int dequeue(Cvor** head, Cvor** zadnji) {
    if (*head == NULL) {
        printf("Red prazan\n");
        return -1;
    }

    Cvor* temp = *head;
    int broj = temp->elem;
    *head = (*head)->next;                      //glava pokazuje na sljedeci

    if (*head == NULL) {                        //red je sad prazan
        *zadnji = NULL;
    }

    free(temp);

    printf("Uklonjen %d\n", broj);
    return 0;
}

void ispisRed(Cvor* head) {
    if (head == NULL) {
        printf("Red prazan\n");
        return;
    }

    Cvor* temp = head;
    printf("Red: ");
    while (temp != NULL) {
        printf("%d ", temp->elem);
        temp = temp->next;
    }
    printf("\n");
}

void freeMem(Cvor* head) {
    Cvor* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void Stog() {
    printf("1 push\n");
    printf("2 pop\n");
    printf("3 ispis\n");
    printf("0 povratak\n");
    printf("Izaberi: ");
}

void Red() {
    printf("1 enqueue\n");
    printf("2 dequeue\n");
    printf("3 ispis\n");
    printf("0 povrtak\n");
    printf("Izbor: ");
}

void simStog() {
    Cvor* stog = NULL;
    int izbor = 0;

    printf("\n  SIMULACIJA STOGA (LIFO)\n");

    do {
        Stog();
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            Push(&stog);
            break;
        case 2:
            Pop(&stog);
            break;
        case 3:
            ispisStog(stog);
            break;
        case 0:
            printf("Povratak\n");
            break;
        default:
            printf("Neispravan izbor\n");
        }
    } while (izbor != 0);

    freeMem(stog);
}

void simRed() {
    Cvor* head = NULL;
    Cvor* zadnji = NULL;
    int izbor = 0;

    printf("\n  SIMULACIJA REDA (FIFO)\n");

    do {
        Red();
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            enqueue(&head, &zadnji);
            break;
        case 2:
            dequeue(&head, &zadnji);
            break;
        case 3:
            ispisRed(head);
            break;
        case 0:
            printf("Povratak\n");
            break;
        default:
            printf("Neispravan izbor\n");
        }
    } while (izbor != 0);

    freeMem(head);
}

int main()
{
    srand(time(NULL));                          //inic random generatora

    int izbor = 0;

    do {
        printf("1 Simulacija stoga\n");
        printf("2 Simulacija reda\n");
        printf("0 Izlaz\n");
        printf("Izaberi: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            simStog();
            break;
        case 2:
            simRed();
            break;
        case 0:
            printf("Izlaz\n");
            break;
        default:
            printf("Neispravan izbor\n");
        }
    } while (izbor != 0);

    return 0;
}
