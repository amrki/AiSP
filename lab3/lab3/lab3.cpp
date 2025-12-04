/*3. Prethodnom zadatku dodati funkcije :
a) dinamièki dodaje novi element iza odreðenog elementa,
b) dinamièki dodaje novi element ispred odreðenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) èita listu iz datoteke.*/

//copy pasteala san prosli zadatak i nadopisivala samo

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _osoba {
	char ime[50];
	char prez[50];
	int god_rod;
	struct _osoba* next;
}Osoba;


Osoba* novaOsoba() {
	Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
	if (!nova) {
		printf("GRESKA u alokaciji!");
	}
	printf("Unesi ime: ");
	scanf("%20s", nova->ime);
	printf("Unesi prezime: ");
	scanf("%20s", nova->prez);
	printf("Unesi godinu rodenja: ");
	scanf("%20d", &nova->god_rod);

	nova->next = NULL;

	return nova;
}

Osoba* dodajNaPoc(Osoba* head) {
	Osoba* nova = novaOsoba();
	if (!nova) return head;
	nova->next = head;
	return nova;
}

void ispis(Osoba* head) {
	Osoba* temp = head;
	if (!temp) {
		printf("Prazna lista!");
		return;
	}

	while (temp) {
		printf("%s %s %d\n", temp->ime, temp->prez, temp->god_rod);
		temp = temp->next;  //pomakni na sljedeci element u listi
	}
}

Osoba* dodajNaKraj(Osoba* head) {
	Osoba* nova = novaOsoba();
	if (!nova) return head; //ako nova osoba nije napravljena samo vrati head
	if (!head) return nova; //ako je lista prazna onda je nova osoba prvi elem

	Osoba* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	if (temp->next == NULL) {
		temp->next = nova;
		nova->next = NULL;
	}
	return head;
}

Osoba* trazi(Osoba* head, char* prezime) {
	Osoba* temp = head;
	while (temp) {
		if (strcmp(temp->prez, prezime) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

Osoba* brisi(Osoba* head, char* prezime) {
	Osoba* temp = head;
	Osoba* prev = NULL;

	while (temp) {
		if (strcmp(temp->prez, prezime) == 0) {
			if (prev == NULL) {
				head = head->next; //stavljamo da je head iduci jer cemo taj prvi koji smo nasli pobrisat
			}
			else {
				prev->next = temp->next;
			}
			printf("Osoba %s obrisana!\n", prezime);
			free(temp);
			return head;
		}
		prev = temp; //hodamo
		temp = temp->next;
	}
	return NULL;
}

Osoba* dodajIzaOdredenog(char* prez, Osoba* head) {
	Osoba* nova = novaOsoba();
	if (!nova) return head; //ako nova osoba nije napravljena samo vrati head
	if (!head) return nova; //ako je lista prazna onda je nova osoba prvi elem

	Osoba* temp = head;
	while (strcmp(temp->prez, prez)) {	//ide dok ne nadje prezime koje trebam
		temp = temp->next;
	}
	nova->next = temp->next;
	temp->next = nova;
	return nova;
}

Osoba* dodajIspredOdredenog(char* prez, Osoba* head) {
	Osoba* nova = novaOsoba();
	if (!nova) return head;
	if (!head) return nova;

	Osoba* temp = head;
	Osoba* prev = NULL;

	while (strcmp(temp->prez, prez)){
		prev = temp;
		temp = temp->next;
	}
	if (prev != NULL) {				//ako prev ima vrijednost izvrsava se ovo
		prev->next = nova;
	}
	nova->next = temp;				//i da nema neku vrijednost ovo se odradi
	return nova;
}

int main()
{
	Osoba* head = NULL;
	int unos = 0;
	char prezime[50];
	Osoba* trazena = NULL;
	Osoba* obrisana = NULL;
	Osoba* odredeni = NULL;

	do {
		printf("Izaberi jedan broj:\n");
		printf("0 - izlaz, 1 - dodaj na pocetak, 2 - ispisi listu , 3 - dodaj na kraj, 4 - trazi po prezimenu, 5 - brisi po prezimnu, 6 - dodaj iza odredenog prezimena, 7 - dodaj ispred odredenog prezimena\n");
		scanf("%d", &unos);

		switch (unos) {
		case 0:
			printf("Izlaz...");
			break;
		case 1:
			head = dodajNaPoc(head);
			break;
		case 2:
			ispis(head);
			break;
		case 3:
			head = dodajNaKraj(head);
			break;
		case 4:
			printf("Koga trazite? ");
			scanf("%s", prezime);
			trazena = trazi(head, prezime);
			if (trazena) {
				printf("Pronaden: %s %s %d\n", trazena->ime, trazena->prez, trazena->god_rod);
			}
			else
				printf("Nije pronadena osoba s prezimenom %s!", prezime);
			break;
		case 5:
			printf("Koga brisete? ");
			scanf("%s", prezime);
			obrisana = brisi(head, prezime);
			if (obrisana == NULL) {
				printf("Nije pronadena osoba s prezimenom %s!", prezime);
			}
			break;
		case 6:
			printf("Iza kojeg prezimena zelite dodati novu osobu? ");
			scanf("%s", prezime);
			odredeni = dodajIzaOdredenog(prezime, head);
			if (odredeni) {
				printf("Dodan: %s %s %d\n", odredeni->ime, odredeni->prez, odredeni->god_rod);
			}
			else
				printf("Nije pronadena osoba s prezimenom %s!", prezime);
			break;
		case 7:
			printf("Ispred kojeg prezimena zelite dodati novu osobu? ");
			scanf("%s", prezime);
			odredeni = dodajIspredOdredenog(prezime, head);
			if (odredeni) {
				printf("Dodan: %s %s %d\n", odredeni->ime, odredeni->prez, odredeni->god_rod);
			}
			else
				printf("Nije pronadena osoba s prezimenom %s!", prezime);
			break;
		default:
			printf("NE MOZE!");
		}
	} while (unos != 0);

	return 0;
}