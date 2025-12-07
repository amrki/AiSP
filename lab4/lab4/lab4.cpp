//4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se èitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortirani.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Polynom {
    int koef;
    int exp;
    Polynom* next;
}Poly;

void Ispis(Poly* head) {

    Poly* temp = head;
    if (temp == NULL) {
        printf("Prazna lista!");
        return;
    }
    while (temp != NULL) {
        printf("%dx^%d\n", temp->koef, temp->exp);
        temp = temp->next;
    }

    return;
}

int ZbrojPoli(Poly* head1, Poly* head2){
    Poly* suma_koef = 0;

    Poly* temp1 = head1;
    Poly* temp2 = head2;

    while (temp1 != NULL) {                         //hodam po prvom polinomu
        temp2 = head2;                              //resetiram temp2 na pocetak za svaku iteraciju prvog polinoma
        while (temp2 != NULL) {                     //hodam po drugom polinomu
            if (temp1->exp == temp2->exp) {
                temp1->koef = temp1->koef + temp2->koef;    //sve spremamo u prvi polinom
                temp2->koef = 0;                            //koef u drugom stavljamo u 0 da ih ne zbrojimo opet
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;                        //hodam
    }

    temp2 = head2;                              //resetiram temp2
    temp1 = head1;

    while (temp1->next!=NULL) {
        temp1 = temp1->next;                    //vracam ga u stanje da je na zadnjem elem
    }
    
    while (temp2 != NULL) {
        if (temp2->koef != 0) {
            temp1->next = temp2;
            temp1 = temp1->next;                //vracam temp1 da mi je opet zadnji
            temp1->next = NULL;
        }
        temp2 = temp2->next;
    }
   
    Ispis(head1);

    return 0;
}

Poly* ReadFile(const char* imeDat) {
    FILE* fp;
    fp = fopen(imeDat, "r");
    if (!fp) {                      //NE ZABORAVI RADIT PROVJERU
        printf("Ne mogu otvoriti datoteku!\n");
        return NULL;
    }
    Poly* head = NULL;  //head je prvi
    Poly* temp = NULL;  //temp je zadnji

    while (!feof(fp)) {
        Poly* novi = (Poly*)malloc(sizeof(Poly));               //novi polinom u koji ce se spremit iz datoteke
        if (fscanf(fp, "%dx^%d", &novi->koef, &novi->exp) == 2) {
            novi->next = NULL;                                  //jer ide na kraj

            if (head == NULL) {
                head = novi;    //oboje su taj prvi
                temp = novi;
            }
            else {
                temp->next = novi;  //iduci od proslog zadnjeg postaje taj novi
                temp = novi;        //i sada temp postaje taj novi zadnji koji je dodan
            }
        }
    }

    return head;
}

int main()
{
    Poly* head1 = ReadFile("polinom1.txt");
    Poly* head2 = ReadFile("polinom2.txt");

    printf("Ispis prvog polinoma: ");
    Ispis(head1);
    printf("Ispis drugog polinoma: ");
    Ispis(head2);

    ZbrojPoli(head1, head2);
    
}

