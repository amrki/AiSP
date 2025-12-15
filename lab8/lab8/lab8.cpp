//8. Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna rezultat.
//Stog je potrebno realizirati preko vezane liste.
//postfiks.txt je 8 2 5 * + 1 3 2 * + / pa bi bilo zapravo (8 + (2 * 5)) / (1 + (3 * 2)) = 2

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _cvor {
	int broj;
	struct _cvor* next;
}Cvor;

Cvor* Push(Cvor* head, int br) {
	Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
	if (!novi) {
		printf("GRESKA u alokaciji!\n");
		return head;
	}
	novi->broj = br;
	novi->next = head;
	return novi;							//vracan novi head
}

int Pop(Cvor** head) {
	if (*head == NULL) {
		printf("Stog je prazan!\n");
		return 0;
	}
	Cvor* temp = *head;
	int vrijednost = temp->broj;
	*head = (*head)->next;					//iduci
	free(temp);
	return vrijednost;
}

int jePrazan(Cvor* head) {
	return head == NULL;					//1 ako prazan, 0 ako nije
}

void ispisiStog(Cvor* head) {
	if (!head) {
		printf("Stog prazan\n");
		return;
	}
	printf("Stog: ");
	Cvor* temp = head;
	while (temp) {
		printf("%d ", temp->broj);
		temp = temp->next;
	}

	printf("\n");
}

int izrPostfiks(const char* imeDat) {
	FILE* fp = fopen(imeDat, "r");
	if (!fp) {
		printf("GRESKA!\n");
		return 0;
	}

	Cvor* stog = NULL;
	char c;
	int broj = 0;
	int imabr = 0;													//flag da znam jesan li procitala broj

	while ((c = fgetc(fp)) != EOF) {
		if (isdigit(c)) {											//ako je znamenka
			broj = broj * 10 + (c - '0');							//moze bit vise znamenki
			imabr = 1;
		}
		else if (c == ' ' || c == '\t' || c == '\n') {				//razmak = kraj broja
			if (imabr) {
				stog = Push(stog, broj);
				printf("Pushano: %d\n", broj);
				broj = 0;
				imabr = 0;
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			if (imabr) {											//ako ima broj prije operatora pusham ga
				stog = Push(stog, broj);
				printf("Pushano: %d\n", broj);
				broj = 0;
				imabr = 0;
			}

			if (jePrazan(stog)) {
				printf("GRESKA! Prazan je stog\n");
				fclose(fp);
				return 0;
			}
			int op2 = Pop(&stog);		//prvi skinem

			if (jePrazan(stog)) {
				printf("GRESKA! Prazan je stok\n");
				fclose(fp);
				return 0;
			}
			int op1 = Pop(&stog);		//drugi skinem

			int rez = 0;

			switch (c) {
			case '+':
				rez = op1 + op2;
				printf("%d + %d = %d\n", op1, op2, rez);
				break;
			case '-':
				rez = op1 - op2;
				printf("%d - %d = %d\n", op1, op2, rez);
				break;
			case '*':
				rez = op1 * op2;
				printf("%d * %d = %d\n", op1, op2, rez);
				break;
			case '/':
				if (op2 == 0) {
					printf("Ne mozes dilit sa 0\n");
					fclose(fp);
					return 0;
				}
				rez = op1 / op2;
				printf("%d / %d = %d\n", op1, op2, rez);
				break;
			}
			stog = Push(stog, rez);		//pusham rez nazad na stog
		}
	}

	fclose(fp);

	if (jePrazan(stog)) {
		printf("Stog prazan na kraju\n");
		return 0;
	}

	int konacniRez = Pop(&stog);

	if (!jePrazan(stog)) {
		printf("Vise od jednog broja ostalo na stogu\n");
		return 0;
	}

	return konacniRez;
}

int main()
{
	int rezultat = izrPostfiks("postfiks.txt");

	printf("Finalni rez: %d\n", rezultat);

	return 0;
}
