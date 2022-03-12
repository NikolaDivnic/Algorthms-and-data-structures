#include<stdio.h>
#define MAX 100
typedef struct elem {
	int dignut;
	int hori;
	int vert;
	int niz[MAX];
	int blok1;
	int blok2;
	int duzina;
}Elem;
Elem enQueue(int *rear,int *front,Elem *red,Elem  cvor ) {
		if (*front == -1)
			* front = 0;
		(*rear)++;
		red[*rear] = cvor;
}

Elem deQueue(int *front,int *rear,Elem *red) {
	if (*front == -1)
		printf("\nQueue is Empty!!");
	else {
		printf("\nDeleted : %d", red[*front]);
		(*front)++;
		if (*front > *rear)
			*front = *rear = -1;
	}
}

Elem display(int *rear,int *front,Elem *red) {
	if (*rear == -1)
		printf("\nQueue is Empty!!!");
	else {
		int i;
		for (i = *front; i <= *rear; i++)
			printf("%d\t", red->niz[i]);
	}
}
void dodajdva(int** mat, int br, int k) {
	int l;
	for (l = 0; l < k; l++)
		if (mat[br][l])
			mat[br][l] = 2;
}
void sklonidva(int** mat, int br, int k) {
	int l;
	for (l = 0; l < k; l++)
		if (mat[br][l])
			mat[br][l] = 1;
}
void pocetak(int** mat, int k, int s) {
	int i, j;
	for (i = 0; i < k; i++)
		for (j = 0; j < k; j++)
			if (mat[i][j] == 2)
				mat[i][j]--;
	for (i = 0; i < k; i++)
		if (mat[s - 1][i])
			mat[s - 1][i]++;
}
int napravistazu(int **a, int *k,FILE* ulaz,int *m ,int* n,int *blok1,int *blok2,int *s,int *t)
{
	int i = 0 , j = 0, br = 1,novi = 0,rb =1;
	char c;
	fscanf(ulaz, "%d %d\n ", &i,&j);
	*m = i;
	*n = j;
	a = malloc((*m) * sizeof(int*));
	for (br = 0; br < i; br++)
		a[br] = malloc((*n) * sizeof(int));
	for (i = 0; i < (*m); i++)
		for (j = 0; j < (*n); j++)
			a[i][j] = 0;

	i = j = 0;
	while ((c=fgetc(ulaz)) != EOF)
	{
		
		if (c != '-' && c!='\n')
		{
			(*k)++;
			a[i][j] = rb;
			rb++;
			if (c == 'S')
				*t=*blok1 = *blok2 = a[i][j];
			if (c == 'T')
				*s = a[i][j];
		}
		if (c == '\n') {
			i++;
			j = 0;
		}else
		 j++;
	}
	
	return a;
}
void stampajstazu(int **staza, int blok1, int blok2,int m , int n,int s,int t) {
	int i, j;
	
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			if (staza[i][j]) {
				if (staza[i][j] == blok1 || staza[i][j] == blok2)
					printf("B");
				else {
					if (staza[i][j]==t)
						printf("T");
					else
						if (staza[i][j]==s)
							printf("S");
						else
							printf("o", staza[i][j]);
				}
			}
			else printf("-");
		printf("\n");
	}
}
int** dodajcvor(int **staza, int** mat, int i, int j, int k, int broj,int m,int n) {
	int rb, br, l;
	int** pom = NULL;
	if (!mat) {
		mat = malloc(k * sizeof(int*));
		for (br = 0; br < k; br++)
			mat[br] = malloc(k * sizeof(int));
		for (br = 0; br < k; br++)
			for (l = 0; l < k; l++)
				mat[br][l] = 0;
	}
	else
	{
		mat = realloc(mat, (k + 1) * sizeof(int*));
		for (br = 0; br < k; br++)
			mat[br] = realloc(mat[br], (k + 1) * sizeof(int));
	}
	rb = i * n + j;
	if (rb / n != 0)
		if (staza[i - 1][j])
			mat[broj][(staza[i - 1][j] - 1)] = 1;
	if (rb % n != 0)
		if (staza[i][j - 1])
			mat[broj][(staza[i][j - 1] - 1)] = 1;
	if (rb % n != n-1)
		if (staza[i][j + 1])
			mat[broj][(staza[i][j + 1] - 1)] = 1;
	if (rb / n != m-1)
		if (staza[i + 1][j])
			mat[broj][(staza[i + 1][j] - 1)] = 1;
	return mat;
}
int** napravigraf(int **staza, int** mat, int k,int m,int n,int blok1,int blok2)
{
	int i, j, rb, broj = 0,l;

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++) {
			if (staza[i][j]) {
				mat = dodajcvor(staza, mat, i, j, k, broj,m,n);
				broj++;
			}
		}
	}
	return mat;
}
void stampajmatricu(int** mat, int k)
{
	int i, j;
	for (i = 0; i < k; i++)
	{
		for (j = 0; j < k; j++)
			printf("%d", mat[i][j]);
		printf("\n");
	}
}
void dodajustazi(int **staza, int i, int j,int m,int n) {
	staza[i][j] = 1;
	int k, l, br = 1;
	for (k = 0; k < m; k++)
		for (l = 0; l < n; l++)
			if (staza[k][l])
				staza[k][l] = br++;

}
int** obrisiMat(int** mat, int k) {
	int i;
	for (i = 0; i < k; i++)
		free(mat[i]);
	free(mat);
	mat = NULL;
	return mat;
}
void izbaciIzStaze(int **staza, int i, int j,int m,int n) {
	staza[i][j] = 0;
	int k, l, br = 1;
	for (k = 0; k < m; k++)
		for (l = 0; l < n; l++)
			if (staza[k][l])
				staza[k][l] = br++;
}
int** izbaci(int** mat, int k, int **staza,int m,int n,int *blok1,int *blok2) {
	int i, j, br, l, r;
	printf("Uneisite cvor koji zelite da izbacite\n");
	scanf("%d%d", &i, &j);
	br = staza[i][j] - 1;
	for (l = 0; l < k; l++) {
		for (r = br; r < k; r++)
			mat[l][r] = mat[l][r + 1];
	}

	for (l = br; l < k; l++)
		mat[l] = mat[l + 1];
	izbaciIzStaze(staza, i, j,m,n);
	if (br < *blok1) {
		(*blok1)--;
		(*blok2)--;
	}
	return mat;
}
int** dodajgranu(int** mat) {
	int i, j;
	printf("Unesite granu \n");
	scanf("%d%d", &i, &j);
	mat[i][j] = 1;
	return mat;
}
int** obrisigranu(int** mat) {
	int i, j;
	printf("Uneisite granu\n");
	scanf("%d%d", &i, &j);
	mat[i][j] = 0;
	return mat;
}
int** dodaj(int** mat, int k, int **staza, int* blok1, int* blok2,int m,int n) {
	int i, j, l, br, r, rb;
	printf("Unesite cvor koji da dodate\n");
	scanf("%d%d", &i, &j);
	dodajustazi(staza, i, j,m,n);
	mat = realloc(mat, (k + 1) * sizeof(int*));
	for (l = 0; l < k; l++)
		mat[l] = realloc(mat[l], (k + 1) * sizeof(int));
	br = staza[i][j] - 1;
	for (l = k; l > br; l--) {
		mat[l] = mat[l - 1];
	}
	if (br >= k) {
		mat = realloc(mat, (br + 2) * sizeof(int*));

	}

	if (br < *blok1) {
		(*blok1)++;
		(*blok2)++;
	}
	if (br < k)
		for (r = 0; r < k + 1; r++)
			mat[br + 1][r] = mat[br][r];
	for (r = 0; r < k + 1; r++) {
		for (l = k; l > br; l--)
			mat[r][l] = mat[r][l - 1];
	}
	if (br < k)
		for (l = 0; l < k + 1; l++)
			mat[l][br] = 0;
	else {
		for (l = 0; l < k; l++)
			mat[l][br] = 0;
	}
	mat[br] = malloc((k + 1) * sizeof(int));
	for (l = 0; l < k + 1; l++) {
		mat[br][l] = 0;
	}
	for (l = br; l < k; l++)
		mat[br + 1][l] = mat[br + 1][l + 1];
	rb = i * n + j;
	if (rb / n != 0)
		if (staza[i - 1][j]) {
			mat[br][(staza[i - 1][j] - 1)] = 1;
			mat[(staza[i - 1][j] - 1)][br] = 1;
		}

	if (rb % n != 0)
		if (staza[i][j - 1]) {
			mat[br][(staza[i][j - 1] - 1)] = 1;
			mat[(staza[i][j - 1] - 1)][br] = 1;
		}

	if (rb % n != n-1)
		if (staza[i][j + 1]) {
			mat[br][(staza[i][j + 1] - 1)] = 1;
			mat[(staza[i][j + 1] - 1)][br] = 1;
		}

	if (rb / n != m-1)
		if (staza[i + 1][j])
		{
			mat[br][(staza[i + 1][j] - 1)] = 1;
			mat[(staza[i + 1][j] - 1)][br] = 1;
		}

	for (i = 0; i < k + 1; i++)
	{
		for (j = 0; j < k + 1; j++)
			printf("%d", mat[i][j]);
		printf("\n");
	}
	return mat;
}
void nadjiPoziciju(int* i, int* j, int **staza, int blok1,int m,int n) {
	int kraj;
	kraj = 0;
	for (*i = 0; *i < m; (*i)++) {
		if (kraj) break;
		for (*j = 0; *j < n; (*j)++)
			if (blok1 == staza[*i][*j]) {
				kraj = 1;
				break;
			}
	}
	(*i)--;
}
void dignutdole(int *blok1, int *blok2, int **staza, int** mat, int k, int* pao,int m,int n,int *dignut,int *vert) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	if (staza[i + 1][j] && staza[i + 2][j]) {
		br = staza[i + 1][j] - 1;
		dodajdva(mat, br, k);
		br = staza[i + 2][j] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = staza[i + 1][j];
	*blok2 = staza[i + 2][j];
	*dignut = 0;
	*vert = 1;
	if (*pao) {
		*blok1 = *blok2 = -1; 
	}
}
void vertdole(int *blok1, int *blok2, int **staza, int** mat, int k, int* pao,int m,int n,int *dignut,int *vert,int s,int t) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	br = staza[i + 1][j] - 1;
	sklonidva(mat, br, k);
	if (staza[i + 2][j]) {
		br = staza[i + 2][j] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = *blok2 = staza[i + 2][j];
	*dignut = 1;
	*vert = 0;
	if (*blok1 == t)
	{
		printf("Pobeda\n");
		*blok2 = *blok1 = s;
		pocetak(mat, k, s);
	}
	if (*pao) {
		*blok1 = *blok2 = -1;
	}
}
void horidole(int* blok1, int* blok2, int **staza, int** mat, int k, int* pao,int m ,int n) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	br = staza[i][j + 1] - 1;
	sklonidva(mat, br, k);
	if (staza[i + 1][j] && staza[i + 1][j + 1]) {
		br = staza[i + 1][j] - 1;
		dodajdva(mat, br, k);
		br = staza[i + 1][j + 1] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = staza[i + 1][j];
	*blok2 = staza[i + 1][j + 1];
	if (*pao) {
		*blok1 = *blok2 = -1; 
	}
}
void dignutdesno(int* blok1, int *blok2, int **staza, int** mat, int k, int* pao,int m,int n,int*dignut,int *hori) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	if (staza[i][j + 2] && staza[i][j + 1]) {
		br = staza[i][j + 1] - 1;
		dodajdva(mat, br, k);
		br = staza[i][j + 2] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = staza[i][j + 1];
	*blok2 = staza[i][j + 2];
	*dignut = 0;
	*hori = 1;
	if (*pao) {
		*blok1 = *blok2 = -1;
	}
}
void horidesno(int* blok1, int* blok2, int **staza, int** mat, int k, int* pao,int m ,int n,int *hori,int *dignut,int s,int t) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	br = staza[i][j + 1] - 1;
	sklonidva(mat, br, k);
	if (staza[i][j + 2]) {
		br = staza[i][j + 2] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = *blok2 = staza[i][j + 2];
	*hori = 0;
	*dignut = 1;
	if (*blok1 == t)
	{
		printf("Pobeda\n");
		*blok2 = *blok1 = s;
		pocetak(mat, k, s);
	}
	if (*pao) {
		*blok1 = *blok2 = -1; 
	}
}

void vertdesno(int *blok1, int *blok2, int **staza, int** mat, int k, int* pao,int m,int n) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	br = staza[i + 1][j] - 1;
	sklonidva(mat, br, k);
	if (staza[i][j + 1] && staza[i + 1][j + 1]) {
		br = staza[i][j + 1] - 1;
		dodajdva(mat, br, k);
		br = staza[i + 1][j + 1] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = staza[i][j + 1];
	*blok2 = staza[i + 1][j + 1];
	if (*pao) {
		*blok1 = *blok2 = -1; 
	}
}

void dignutgore(int *blok1, int *blok2, int **staza, int** mat, int k, int* pao ,int m,int n,int *dignut,int *vert) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	if (staza[i - 1][j] && staza[i - 2][j]) {
		br = staza[i - 1][j] - 1;
		dodajdva(mat, br, k);
		br = staza[i - 2][j] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = staza[i - 2][j];
	*blok2 = staza[i - 1][j];
	*dignut = 0;
	*vert = 1;
	if (*pao) {
		*blok1 = *blok2 = -1;
	}
}
void vertgore(int* blok1, int* blok2, int **staza, int** mat, int k, int* pao,int m,int n,int *dignut,int *vert,int s,int t) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	br = staza[i + 1][j] - 1;
	sklonidva(mat, br, k);
	if (staza[i - 1][j]) {
		br = staza[i - 1][j] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = *blok2 = staza[i - 1][j];
	*dignut = 1;
	*vert = 0;
	if (*blok1 == t)
	{
		printf("Pobeda\n");
		*blok2 = *blok1 = s;
		pocetak(mat, k, s);
	}
	if (*pao) {
		*blok1 = *blok2 = -1; 
	}
}
void horigore(int *blok1, int *blok2, int **staza, int** mat, int k, int* pao,int m,int n) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	br = staza[i][j + 1] - 1;
	sklonidva(mat, br, k);
	if (staza[i - 1][j] && staza[i - 1][j + 1]) {
		br = staza[i - 1][j] - 1;
		dodajdva(mat, br, k);
		br = staza[i - 1][j + 1] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = staza[i - 1][j];
	*blok2 = staza[i - 1][j + 1];
	if (*pao) {
		*blok1 = *blok2 = -1; 
	}
}
void dignutlevo(int *blok1, int *blok2, int **staza, int** mat, int k, int* pao,int m,int n,int *dignut,int *hori) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	if (staza[i][j - 2] && staza[i][j - 1]) {
		br = staza[i][j - 1] - 1;
		dodajdva(mat, br, k);
		br = staza[i][j - 2] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = staza[i][j - 2];
	*blok2 = staza[i][j - 1];
	*dignut = 0;
	*hori = 1;
	if (*pao) {
		*blok1 = *blok2 = -1;
	}
}
void vertlevo(int *blok1, int *blok2, int **staza, int** mat, int k, int* pao ,int m,int n) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	br = staza[i + 1][j] - 1;
	sklonidva(mat, br, k);
	if (staza[i][j - 1] && staza[i + 1][j - 1]) {
		br = staza[i][j - 1] - 1;
		dodajdva(mat, br, k);
		br = staza[i + 1][j - 1] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = staza[i][j - 1];
	*blok2 = staza[i + 1][j - 1];
	if (*pao) {
		*blok1 = *blok2 = -1;
	}
}
void horilevo(int *blok1, int *blok2, int **staza, int** mat, int k, int* pao,int m,int n,int *hori,int *dignut,int s,int t) {
	int kraj, i = 0, j = 0, l, br;
	nadjiPoziciju(&i, &j, staza, *blok1,m,n);
	br = staza[i][j] - 1;
	sklonidva(mat, br, k);
	br = staza[i][j + 1] - 1;
	sklonidva(mat, br, k);
	if (staza[i][j - 1]) {
		br = staza[i][j - 1] - 1;
		dodajdva(mat, br, k);
	}
	else {
		printf("Pao je\n");
		*pao = 1;
	}
	*blok1 = *blok2 = staza[i][j - 1];
	*hori = 0;
	*dignut = 1;
	if (*blok1 == t)
	{
		printf("Pobeda\n");
		*blok2 = *blok1 = s;
		pocetak(mat, k, s);
	}
	if (*pao) {
		*blok1 = *blok2 = -1;
	}
}
Elem napunicvor(int blok1, int blok2, int dignut, int hori, int vert, Elem cvor) {
	cvor.blok1 = blok1;
	cvor.blok2 = blok2;
	cvor.dignut = dignut;
	cvor.hori = hori;
	cvor.vert = vert;
	cvor.duzina = 0;
	return cvor;
}
Elem izjednaci(Elem cvor, Elem pred) {
	pred.blok1 = cvor.blok1;
	pred.blok2 = cvor.blok2;
	pred.dignut = cvor.dignut;
	pred.duzina = cvor.duzina;
	pred.hori = cvor.hori;
	pred.vert = cvor.vert;
	for (int i = 0 ; i<cvor.duzina;i++)
	pred.niz[i] = cvor.niz[i];
	return pred;

}
int akoNijePao(int pao,Elem cvor,int *front,int *rear,Elem*red,int broj,int t,int blok1,int blok2) {
	int pobeda = 0;
	if (!pao)
	{
		cvor.niz[cvor.duzina] = broj;
		enQueue(rear, front, red, cvor);
		if (t == blok1 && t == blok2) {
			for (int i = 0; i < cvor.duzina; i++)
				printf("%d ", cvor.niz[i]);
			pobeda = 1;
		}
			
	}
	return pobeda;
}
void resenje(int **staza, int m, int n, int blok1, int blok2, int t,int  dignut,int  vert,int  hori,int **mat,int k,int s) {
	
	int  front = -1, rear = -1,i,pao = 0,broj,pobeda =0;
	Elem red[100] ;
	Elem cvor;
	Elem pred;
	cvor.blok1 = 0;
	cvor.blok2 = 0;
	cvor.dignut = 0;
	cvor.hori = 0;
	cvor.vert = 0;
	cvor.duzina = 0;
	pred.blok1 = 0;
	pred.blok2 = 0;
	pred.dignut = 0;
	pred.hori = 0;
	pred.vert = 0;
	pred.duzina = 0;
	cvor = napunicvor(blok1, blok2, dignut, hori, vert,cvor);
	pred = izjednaci(cvor, pred);
	broj = 1;
	dignutdole(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.vert);
	pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
	pred = izjednaci(pred,cvor);
	broj = 2;
	dignutdesno(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.hori);
	pobeda = akoNijePao(pao, cvor, &front, &rear, red,broj,t,cvor.blok1,cvor.blok2);
	broj = 3;
	pred = izjednaci(pred, cvor);
	dignutgore(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.vert);
	pobeda = akoNijePao(pao, cvor, &front, &rear, red,broj,t,cvor.blok1,cvor.blok2);
	broj = 4;
	pred = izjednaci(pred, cvor);
	dignutlevo(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.hori);
	pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
	while (front != rear) {
		pred = deQueue(&front, &rear, red);
		if (pred.dignut) {
			pred = izjednaci(pred, cvor);
			broj = 1;
			dignutdole(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.vert);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
			pred = izjednaci(pred, cvor);
			broj = 2;
			dignutdesno(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.hori);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
			broj = 3;
			pred = izjednaci(pred, cvor);
			dignutgore(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.vert);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
			broj = 4;
			pred = izjednaci(pred, cvor);
			dignutlevo(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.hori);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
		}
		if (pred.vert) {
			pred = izjednaci(pred, cvor);
			broj = 1;
			vertdole(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.vert, &s, t);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
			pred = izjednaci(pred, cvor);
			broj = 2;
			vertdesno(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
			broj = 3;
			pred = izjednaci(pred, cvor);
			vertgore(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.dignut, &cvor.vert, s, t);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
			broj = 4;
			pred = izjednaci(pred, cvor);
			vertlevo(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
		}
		if (pred.hori) {
			pred = izjednaci(pred, cvor);
			broj = 1;
			horidole(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
			pred = izjednaci(pred, cvor);
			broj = 2;
			horidesno(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.hori, &cvor.dignut, s, t);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
			broj = 3;
			pred = izjednaci(pred, cvor);
			horigore(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
			broj = 4;
			pred = izjednaci(pred, cvor);
			horilevo(&cvor.blok1, &cvor.blok2, staza, mat, k, &pao, m, n, &cvor.hori, &cvor.dignut, s, t);
			pobeda = akoNijePao(pao, cvor, &front, &rear, red, broj, t, cvor.blok1, cvor.blok2);
			if (pobeda) break;
		}

	}
}
int main(int argc, const char**argv) {
	FILE* ulaz = fopen(argv[1], "r");
	int izbor, **staza = NULL, ** mat = NULL, k = 0, i, j, rb, kraj = 0, br, l, pao = 0,m,n,t,s;
	int dignut = 1, vert = 0, hori = 0, blok1, blok2;
	while (1)
	{
		printf("Unesite vas izbor\n"
			"0 izlaz\n"
			"1 napravi graf\n"
			"2 stampaj stazu\n"
			"3 stampaj matricu\n"
			"4 dodaj cvor\n"
			"5 dodaj granu\n"
			"6 obrisi graf\n"
			"7 izbaci cvor\n"
			"8 obrisis granu\n"
			"9 dole\n"
			"10 desno\n"
			"11 gore\n"
			"12 levo\n"
		"13 resenje\n");
		scanf("%d", &izbor);
		switch (izbor)
		{
		case 0:exit(1);
		case 1:
			if (staza== NULL)
				staza = napravistazu(staza, &k, ulaz, &m, &n,&blok1,&blok2,&t,&s);
			mat = napravigraf(staza, mat, k,m,n,blok1,blok2);
			

			for (l = 0; l < k; l++)
				if (mat[blok1 -1][l])
					mat[blok1 -1][l] = 2;
			dignut = 1; vert = 0; hori = 0;
			break;
		case 2:stampajstazu(staza, blok1, blok2,m,n,s,t);	break;
		case 3:if (mat != NULL)
			stampajmatricu(mat, k); break;
		case 4:
			mat = dodaj(mat, k, staza, &blok1, &blok2,m,n);
			s++;
			k++;
			break;
		case 5:mat = dodajgranu(mat);
			break;
		case 6:mat = obrisiMat(mat, k);
			mat = NULL;
				break;
		case 7:if (!k) printf("Nema sta da se izbaci\n");
			   else {
			
			mat = izbaci(mat, k, staza, m, n, &blok1, &blok2); k--; s--; break;
		}
		case 8:mat = obrisigranu(mat);
			break;
		case 9:
			i = j = 0;
			nadjiPoziciju(&i, &j, staza, blok1,m,n);
			if (i == m-1) {
				printf("Ne moze\n");
				break;
			}
			if (dignut)
			{
				nadjiPoziciju(&i, &j, staza, blok1,m,n);
				if (i == m-2) {
					printf("Ne moze\n");
					break;
				}
				dignutdole(&blok1, &blok2, staza, mat, k, &pao,m,n,&dignut,&vert);
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
			if (vert) {
				vertdole(&blok1, &blok2, staza, mat, k, &pao,m,n,&dignut,&vert,s,t);
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
			if (hori) {
				horidole(&blok1, &blok2, staza, mat, k, &pao,m,n);		
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
		case 10:
			i = j = 0;
			nadjiPoziciju(&i, &j, staza, blok1,m,n);
			if (i == n-1) {
				printf("Ne moze\n");
				break;
			}
			if (dignut)
			{
				nadjiPoziciju(&i, &j, staza, blok1,m,n);
				if (i == n-2) {
					printf("Ne moze\n");
					break;
				}
				dignutdesno(&blok1, &blok2, staza, mat, k, &pao,m,n,&dignut,&hori);
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
			if (vert) {
				vertdesno(&blok1, &blok2, staza, mat, k, &pao,m,n);	
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
			if (hori) {
				horidesno(&blok1, &blok2, staza, mat, k, &pao,m,n,&hori,&dignut,s,t);
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
		case 11:
			i = j = 0;
			nadjiPoziciju(&i, &j, staza, blok1,m,n);
			if (i == 0) {
				printf("Ne moze\n");
				break;
			}
			if (dignut)
			{
				nadjiPoziciju(&i, &j, staza, blok1,m,n);
				if (i == 1) {
					printf("Ne moze\n");
					break;
				}
				dignutgore(&blok1, &blok2, staza, mat, k, &pao,m,n,&dignut,&vert);
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
			if (vert) {
				vertgore(&blok1, &blok2, staza, mat, k, &pao,m,n,&dignut,&vert,s,t);
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
			if (hori) {
				horigore(&blok1, &blok2, staza, mat, k, &pao,m,n);	
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
		case 12:
			i = j = 0;
			nadjiPoziciju(&i, &j, staza, blok1,m,n);
			if (j == 0) {
				printf("Ne moze\n");
				break;
			}
			if (dignut)
			{
				nadjiPoziciju(&i, &j, staza, blok1,m,n);
				if (j == 1) {
					printf("Ne moze\n");
					break;
				}
				dignutlevo(&blok1, &blok2, staza, mat, k, &pao,m,n, &dignut, &hori);
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
			if (vert) {
				vertlevo(&blok1, &blok2, staza, mat, k, &pao,m,n);
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
			if (hori) {
				horilevo(&blok1, &blok2, staza, mat, k, &pao,m,n,&hori,&dignut,s,t);
				stampajstazu(staza, blok1, blok2, m, n, s, t);
				break;
			}
			
			break;
		case 13:resenje(staza,m,n,blok1,blok2,t,dignut,vert,hori,mat,k,s);
		default:
			break;
		}
	}
}