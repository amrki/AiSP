/*Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata zapisanih u
datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura studenata (ime, prezime,
bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime, prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Student {
	char ime[50];
	char prez[50];
	int bodovi;
};

int main()
{
	int max_bodovi = 150;
	const char *path = "C:\\Users\\mrkia\\Desktop\\FESB\\Strukture podataka\\AiSP\\lab1\\x64\\Debug\\studenti.txt";

	FILE* f = fopen(path, "r");

	if (f == NULL) {
		printf("GRESKA! Ne mogu otvorit datoteku!\n");
		return 1;
	}
	char buffer[100];
	int br_red = 0;

	while (fgets(buffer, sizeof(buffer), f) != NULL) {

		if (strlen(buffer) > 0) {
			br_red++;
		}
	}
	fclose(f);

	if (br_red == 0) {
		printf("Datoteka je prazna!");
	}
	printf("Datoteka ima %d studenata.\n", br_red);
	
	struct Student *niz = (struct Student*)malloc(br_red*sizeof(Student));

	f = fopen(path, "r");
	if (f == NULL) {
		printf("GRESKA! Ne mogu otvorit datoteku!\n");
		return 1;
	}

	int i = 0;
	while (i < br_red && fgets(buffer, sizeof(buffer), f) != NULL) {
		if (sscanf(buffer, "%s %s %d", niz[i].ime, niz[i].prez, &niz[i].bodovi)==3) {
			i++;
		}
		else {
			printf("GRESKA! Na redu %d.", i+1);
		}
	}
	fclose(f);

	int k = 0;
	int najbolji_bodovi = 0;
	while (k < br_red) {
		if (niz[k].bodovi > najbolji_bodovi) {
			najbolji_bodovi = niz[k].bodovi;
		}
		k++;
	}

	int j = 0;
	printf("%-20s %-20s %-20s %-20s\n", "Ime", "Prezime", "Apsolutni", "Relativni");
	while (j<br_red) {
		if (najbolji_bodovi > 0) {
			double rel = niz[j].bodovi*100.0/ najbolji_bodovi;
			printf("%-20s %-20s %-20d %-20f\n", niz[j].ime, niz[j].prez, niz[j].bodovi, rel);
		}
		else {
			double rel = 0.0;
			printf("%-20s %-20s %-20d %-20f\n", niz[j].ime, niz[j].prez, niz[j].bodovi, rel);
		}
		j++;
	}
	free(niz);
	return 0;
}

