#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MIME 20
#define MAX 100
#include<conio.h>
typedef struct node {
	char ime[MIME];
	int rang, rez1, rez2;
	struct node * left;
	struct node * right;
}node;
void dodajured(int* rear, int* front, node* cvor, node **red) {
	if ((*rear + 1) % MAX == *front)
		printf("Red je pun");
	else
	{
		red[*rear] = cvor;
		*rear = (*rear + 1) % MAX;
	}
}
node *napravistablo(node * root, int n) {
	node niz[MAX];
	int i, broj;
	node *t, *levi, *desni, *s;
	getchar();
	for (i = 0; i < n; i++)
	{
		printf("Unesite ime %d-og igraca ", i + 1);
		gets(niz[i].ime);
		niz[i].rang = i + 1;
		niz[i].rez1 = -1;
		niz[i].rez2 = -1;
		niz[i].left = NULL;
		niz[i].right = NULL;
	}
	broj = 1;
	while (broj < n)
		broj *= 2;
	broj /= 2;
	for (i = 0; i < n - broj; i++)
	{
		t = (node*)malloc(sizeof(node));
		levi = (node*)malloc(sizeof(node));
		desni = (node*)malloc(sizeof(node));
		levi->left = NULL;
		levi->right = NULL;
		desni->left = NULL;
		desni->right = NULL;
		t->left = NULL;
		t->right = NULL;
		strcpy(t->ime, niz[(broj - i - 1)].ime);
		strcpy(levi->ime, niz[(broj - i - 1)].ime);
		strcpy(desni->ime, niz[(broj + i)].ime);
		t->rang = niz[(broj - i - 1)].rang;
		t->rez1 = niz[(broj - i - 1)].rez1;
		t->rez2 = niz[(broj - i - 1)].rez1;
		levi->rang = niz[(broj - i - 1)].rang;
		levi->rez1 = niz[(broj - i - 1)].rez1;
		levi->rez2 = niz[(broj - i - 1)].rez2;
		desni->rang = niz[(broj + i)].rang;
		desni->rez1 = niz[(broj + i)].rez1;
		desni->rez2 = niz[(broj + i)].rez2;
		t->left = levi;
		t->right = desni;
		niz[(broj - i - 1)] = *t;
	}
	while (broj != 1)
	{
		for (i = 0; i < broj / 2; i++)
		{
			s = (node*)malloc(sizeof(node));
			levi = (node*)malloc(sizeof(node));
			desni = (node*)malloc(sizeof(node));
			*s = *levi = niz[i];
			s->left = levi;
			*desni = niz[broj - 1 - i];
			s->left = levi;
			s->right = desni;
			niz[i] = *s;
		}
		broj /= 2;
	}
	root = (node*)malloc(sizeof(node));
	root->left = NULL;
	root->right = NULL;
	*root = niz[0];
	return root;
}
node* obrisiuredu(int* front, int* rear, node **red) {
	node* cvor = NULL;
	if (*front == *rear) {
		cvor = NULL;
	}
	else
	{
		cvor = red[*front];
		*front = (*front + 1) % MAX;
	}
	if (*front == *rear)
		*front = *rear = 0;
	return cvor;
}
void ispisi(node * root, int* rear, int* front, node *red, int nivo) {
	if (root == NULL)
		return;
	int kraj, is = 50, i, ni, d;
	ni = d = nivo;
	dodajured(rear, front, root, &red);
	dodajured(rear, front, NULL, &red);
	printf("\n");
	for (i = 0; i < 55; i++)
		printf(" ");
	while (1) {
		if (!ni)
			for (i = 0; i < d; i++) {
				printf("\t");
				ni = 100;
			}

		root = obrisiuredu(front, rear, &red);
		if (root == NULL) {
			printf("\n");
			ni--;
			for (i = 0; i < is; i++)
				printf(" ");
			is /= 3;
			is *= 2;
			if (kraj) break;
			kraj = 1;
			dodajured(rear, front, NULL, &red);
		}
		else {
			printf(" \t %s ", root->ime);
			if (root->rez1 != -1) printf(" %d %d ", root->rez1, root->rez2);
			if (root->left != NULL) dodajured(rear, front, root->left, &red);
			if (root->right != NULL) dodajured(rear, front, root->right, &red);
			kraj = 0;
		}

	}
}
void obrisi(node * root, int* rear, int* front, node *red) {
	if (root == NULL)
		return;
	dodajured(rear, front, root, &red);
	while (1) {

		root = obrisiuredu(front, rear, &red);
		if (root == NULL) break;
		if (root->left != NULL) dodajured(rear, front, root->left, &red);
		if (root->right != NULL) dodajured(rear, front, root->right, &red);
		free(root);
	}
}
void rezultat(node * root, int silazenje, int* rear, int* front, node *red, int n, int brojac) {
	int kraj = 0, x, nivo, rez1, rez2, duz, i;
	if (root == NULL)
		return;
	node* cvor = NULL;
	node* nroot = NULL;
	x = 1;
	while (x < n) x *= 2;
	x /= 2;
	nivo = 0;
	while (x)
	{
		nivo++;
		x /= 2;
	}
	silazenje = 0;
	dodajured(rear, front, root, &red);
	dodajured(rear, front, NULL, &red);
	int prom = nivo - 1 - brojac;
	while (silazenje != prom) {
		nroot = obrisiuredu(front, rear, &red);
		if (nroot == NULL) {
			silazenje++;
			if (kraj) break;
			kraj = 1;
			dodajured(rear, front, cvor, &red);
		}
		else
		{
			if (nroot->left != NULL) dodajured(rear, front, nroot->left, &red);
			if (nroot->right != NULL) dodajured(rear, front, nroot->right, &red);
			kraj = 0;
		}
	}
	while (1)
	{
		rez1 = rez2 = 0;
		nroot = obrisiuredu(front, rear, &red);
		if (nroot == NULL) break;
		if (nroot->left != NULL && nroot->right != NULL) {
			printf("Unesite rezultat izmedju %s i %s ", nroot->left->ime, nroot->right->ime);
			scanf_s("%d %d", &rez1, &rez2);
			if (rez1 < 0 || rez2 < 0) printf("Nepravilan unos");
			else
			{
				if (rez1 > rez2) strcpy(nroot->ime, nroot->left->ime);
				else
					if (rez1 < rez2) strcpy(nroot->ime, nroot->right->ime);
					else printf("Nepravilan unos");
				nroot->rez1 = rez1;
				nroot->rez2 = rez2;
			}
		}
	}
}
void strana(node * root) {
	node* nroot = NULL;
	node* red2[MAX];
	int kraj = 0, rear = 0, front = 0;
	dodajured(&rear, &front, root, &red2);
	dodajured(&rear, &front, NULL, &red2);
	while (1) {
		nroot = obrisiuredu(&front, &rear, &red2);
		if (nroot == NULL)
		{
			if (kraj) break;
			kraj = 1;
		}
		else {
			kraj = 0;
			if (nroot->left == NULL || nroot->right == NULL) printf("  %s   ", nroot->ime);
			else

			{
				if (nroot->rez1 > -1) printf("  %s  ", nroot->ime);
				else {
					dodajured(&rear, &front, nroot->left, &red2);
					dodajured(&rear, &front, nroot->right, &red2);
					dodajured(&rear, &front, NULL, &red2);
				}

			}
		}
	}
}
void kolo(node * root, int broj, int* rear, int* front, node *red) {
	int silazenje = 0, kraj = 0;
	node* nroot = NULL;
	silazenje = 0;
	dodajured(rear, front, root, &red);
	dodajured(rear, front, NULL, &red);
	while (silazenje != broj) {
		nroot = obrisiuredu(front, rear, &red);
		if (nroot == NULL) {
			silazenje++;
			if (kraj) break;
			kraj = 1;
			dodajured(rear, front, NULL, &red);
		}
		else
		{
			if (nroot->left != NULL) dodajured(rear, front, nroot->left, &red);
			if (nroot->right != NULL) dodajured(rear, front, nroot->right, &red);
			kraj = 0;
		}
	}
	while (1)
	{
		nroot = obrisiuredu(front, rear, &red);
		if (nroot == NULL) break;
		strana(nroot->left);
		printf("Protiv");
		strana(nroot->right);
		printf("\n");
	}
}
int main() {
	int n, front, rear, silazenje, nivo, x, dalje, brojac, runda, ni, izbor, brc = 0, izb;
	n = 0;
	front = rear = -1;
	while (1)
	{
		silazenje = 0;
		brojac = 0;
		node* red[MAX];
		node *root;
		root = (node*)malloc(sizeof(node));
		root->left = NULL;
		root->right = NULL;
		front = rear = 0;
		printf("Formiranje stabla broj 1\n");
		printf("Popunjavanje rezultatima broj 2\n");
		printf("Ispis pobednika broj 3\n");
		printf("Ispis stabla broj 4\n");
		printf("Brisanje stabla broj 5\n");
		printf("Broj cvorova broj 6\n");
		printf("Izlaz 0\n");
		scanf_s("%d", &izbor);
		printf("Unesite broj igraca\n");
		scanf_s("%d", &n);
		x = 1;
		while (x < n) x *= 2;
		x /= 2;
		nivo = 0;
		while (x)
		{
			nivo++;
			x /= 2;
		}
		ni = nivo;
		root = napravistablo(root, n);
		izb = izbor;
		izbor = 8;
		while (izbor)
		{

			if (izbor == 1) {
				printf("Unesite broj igraca\n");
				scanf_s("%d", &n);
				x = 1;
				while (x < n) x *= 2;
				x /= 2;
				nivo = 0;
				while (x)
				{
					nivo++;
					x /= 2;
				}
				ni = nivo;
				root = napravistablo(root, n);
			}
			if (izbor == 2) {
				dalje = 1;
				while (dalje && nivo) {
					rezultat(root, silazenje, &rear, &front, &red, n, brojac);
					brojac++;
					nivo--;
					if (nivo) {
						printf("Unesite ako hocete dalje(0 za prikaz ko moze da se sastane u nekoj narednoj rundi) ");
						scanf_s("%d", &dalje);
					}
					if (nivo && !dalje) {
						printf("Unesite broj rundu ");
						scanf_s("%d", &runda);
						runda = ni - runda;
						kolo(root, runda, &rear, &front, &red);
					}
				}
			}
			if (izbor == 3) {
				printf(" %s\n ", root->ime);
			}
			if (izbor == 4) {

				ispisi(root, &rear, &front, &red, ni);
			}
			if (izbor == 5)
				obrisi(root, &rear, &front, &red);
			if (izbor == 6) {
				brc = 2 * n - 1;
				printf("Broj cvorova je %d\n", brc);
			}
			printf("Formiranje stabla broj 1\n");
			printf("Popunjavanje rezultatima broj 2\n");
			printf("Ispis pobednika broj 3\n");
			printf("Ispis stabla broj 4\n");
			printf("Brisanje stabla broj 5\n");
			printf("Broj cvorova broj 6\n");
			printf("Izlaz 0\n");
			scanf_s("%d", &izbor);

		}

	}
}