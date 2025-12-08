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
    if (head == NULL) {                         //provjera
        printf("Prazna\n");
        return;
    }

    Poly* temp = head;
    int prvi = 1;

    while (temp != NULL) {                      //popravljen ispis
        if (temp->koef != 0) {
            if (!prvi && temp->koef > 0) {      //poziivni i da nije prvi na redu
                printf("+");
            }
            else if (temp->koef < 0 && !prvi) { //negativni
                printf("-");
                printf("%dx^%d", -temp->koef, temp->exp);
                temp = temp->next;
                prvi = 0;
                continue;
            }
            else if (temp->koef < 0 && prvi) {
                printf("%dx^%d", temp->koef, temp->exp);
                temp = temp->next;
                prvi = 0;
                continue;
            }
            printf("%dx^%d", temp->koef, temp->exp);
            prvi = 0;
        }
        temp = temp->next;
    }
    printf("\n");
}

Poly* SortPoli(Poly* head) {
    if (head == NULL || head->next == NULL){            //nema sorta ako je lista prazna ili ima jedan elem
        return head;
    }

    int zamjena;             //da znan jesan li napravila zamjenu
    Poly* temp;
    Poly* zadnji = NULL;     //zadnji sortirani

    do {
        zamjena = 0;        //na pocetku svakog prolaza nema zamjene
        temp = head;

        while (temp->next != zadnji) {                  //do zadnjeg vec sortiranog
            if (temp->exp < temp->next->exp) {          //od veceg prema manjem BUBBLE

                int tempKoef = temp->koef;              //pamtim koef trenutnog
                int tempExp = temp->exp;                //pamtim exp trenutnog

                temp->koef = temp->next->koef;          //spreman koef iz iduceg u trenutni
                temp->exp = temp->next->exp;            //spreman exp iz iduceg u trenutni

                temp->next->koef = tempKoef;            //u iducen stavljan zapamceni koef trenutnog
                temp->next->exp = tempExp;              //u iducen stavljan zapamceni exp trenutnog

                zamjena = 1;                            //flag potvrde
            }
            temp = temp->next;
        }
        zadnji = temp;                                  //zadnji je sortiran
    } while (zamjena);

    return head;
}

int PomnoziPoli(Poly* head1, Poly* head2) {

    Poly* rez = NULL;

    Poly* temp1 = head1;
    Poly* temp2 = head2;

    while (temp1 != NULL) {
        temp2 = head2;
        while (temp2 != NULL) {

            int noviKoef = temp1->koef * temp2->koef;
            int noviExp = temp1->exp + temp2->exp;

            Poly* temp3 = rez;                          //provjera jel ima neki clan isti exp
            int postoji = 0;

            while (temp3 != NULL) {
                if (temp3->exp == noviExp) {
                    temp3->koef += noviKoef;
                    postoji = 1;                        //flag
                    break;
                }
                temp3 = temp3->next;
            }

            if (!postoji && noviKoef != 0) {            //ako ne postoji sa istin exp, dodajen novi

                Poly* novi = (Poly*)malloc(sizeof(Poly));
                
                if (novi == NULL) {                     //provjera!!!
                    printf("GRESKA\n");
                    return -1;
                }

                novi->koef = noviKoef;                  //novi
                novi->exp = noviExp;
                novi->next = NULL;

                if (rez == NULL) {
                    rez = novi;                         //nema rez, novi clan je prvi
                }
                else {
                    Poly* temp4 = rez;
                    while (temp4->next != NULL) {
                        temp4 = temp4->next;
                    }
                    temp4->next = novi;                 //novi na kraj
                }
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

    printf("Rezultat mnozenja:\n");
    Ispis(rez);

    return 0;
}

int ZbrojPoli(Poly* head1, Poly* head2){

    Poly* temp1 = head1;
    Poly* temp2 = head2;

    while (temp1 != NULL) {                             //opet hodan po prvon polinomu
        temp2 = head2;                                  //resetiran temp2 na pocetak za svaku iteraciju prvog polinoma
        while (temp2 != NULL) {                         //hodan po drugon polinomu
            if (temp1->exp == temp2->exp) {
                temp1->koef = temp1->koef + temp2->koef;    //sve spreman u prvi polinom
                temp2->koef = 0;                            //koef u drugom stavljan u 0 da ih ne zbrojin opet
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;                            //hodan
    }

    temp2 = head2;                                      //resetiran temp2
    temp1 = head1;

    while (temp1->next!=NULL) {
        temp1 = temp1->next;                            //vracan ga u stanje da je na zadnjem elem
    }
    
    while (temp2 != NULL) {
        if (temp2->koef != 0) {
            temp1->next = temp2;
            temp1 = temp1->next;                        //vracan temp1 da mi je opet zadnji
            temp1->next = NULL;
        }
        temp2 = temp2->next;
    }
   
    printf("Rez zbrajanja: \n");
    Ispis(head1);

    return 0;
}

Poly* ReadFile(const char* imeDat) {
    FILE* fp;
    fp = fopen(imeDat, "r");
    if (!fp) {                                           //NE ZABORAVI RADIT PROVJERU
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

    printf("Ispis prvog polinoma: \n");
    Ispis(head1);
    printf("Ispis drugog polinoma: \n");
    Ispis(head2);

    ZbrojPoli(head1, head2);
    PomnoziPoli(head1, head2);
    
}

