#include<stdio.h>
#include <iostream>
#include<stdlib.h>
using namespace std;

int n;

void dealocirajMatricu(double** matrix) {
	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}
void ispisiMatricu(double** matrix) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%lf ", matrix[i][j]);

		printf("\n");
	}
	printf("\n");
}
void ispisiNiz(double* a) {
	for (int i = 0; i < n; i++) {
		printf("%.6lf " ,a[i]);
	}
	printf("\n");
}
double** alocirajMatricu() {

	double** matrix = (double**)calloc(n, sizeof(double*));

	for (int i = 0; i < n; i++) {
		matrix[i] = (double*)calloc(n, sizeof(double));
	}

	return matrix;
}

double* alocirajNiz() {
	double* array = (double*)(calloc(n, sizeof(double)));
	return array;
}

double sumJ(double** L, double** U, int i, int j) {
	double sum = 0;

	for (int k = 0; k <=(j - 1); k++) {
		sum += L[i][k] * U[k][j];
	}

	return sum;
}

double sumI(double** L, double** U, int i, int j) {

	double sum = 0;

	for (int k = 0; k <=(i - 1); k++) {
		sum += L[i][k] * U[k][j];
	}

	return sum;
}

double sumIK(double** A, double* b, int i)
{
	double sum = 0;
	for (int k = 0; k < i; k++)
	{
		sum += A[i][k] * b[k];
		
	}

	return sum;
}
double sumI(double** A, double* x, int i) {
	double sum = 0;
	for (int k = i+1 ; k < n; k++) {
		sum += A[i][k] * x[k];
	}
	return sum;

}

void KrautovAlgoritam(double** a, double** L, double** U) {
	for (int i = 0; i < n; i++) {
		U[i][i] = 1;
		L[i][0] = a[i][0];
	}

	for (int j = 1; j < n; j++) {
		U[0][j] = a[0][j] / L[0][0];
	}

	for (int j = 1, i = 1; j < n && i < n; j++, i++) {
		for (int x = j; x < n; x++) {
			L[x][j] = a[x][j] - sumJ(L, U, x, j);
		}
		
		for (int y = i + 1; y < n; y++) {
			U[i][y] = 1 / (L[i][i]) * (a[i][y] - sumI(L, U, i, y));
		}	
	}
}

double* formirajB(double** A) {

	double* b = alocirajNiz();
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b[j] += A[i][j];
		}
	}
	return b;
}

void formirajHilberta(double** matrix) {

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n; j++) {

			matrix[i][j] = 1.0 / (i + j + 1);
		}
	}

}

void DulitlovAlgoritam(double** a, double** L, double** U) {

	for (int j = 0; j < n; j++) {
		L[j][j] = 1;
		U[0][j] = a[0][j];
	}
	for (int i = 1; i < n; i++) {
		L[i][0] = a[i][0] / U[0][0];
	}
	for (int j = 1, i = 1; j < n && i < n; j++, i++) {
		for (int y = i; y < n; y++) {
			U[i][y] = a[i][y] - sumI(L, U, i, y);
		}
		for (int x = j + 1; x < n; x++) {
			L[x][j] = 1 / (U[j][j]) * (a[x][j] - sumJ(L, U, x, j));
		}

	}
}





double* resavanjeGornjeTrougaone(double** A, double* b) {
	double* x = (double*)calloc(n, sizeof(double));
	
	for (int i = n-1; i >=0; i--) {
		
		x[i] = (1 / A[i][i]) * (b[i] - sumI(A, x, i));
		
		
	}
	return x;
}

double* resavanjeDonjeTrougaone(double** A, double* b)
{
	double* x = (double*)calloc(n , sizeof(double));

	for (int i = 0; i < n; i++) {
		
		x[i] = (1 / A[i][i]) * (b[i] - sumIK(A, x, i));
	}

	return x;
}
bool check(double* x)
{
	int i = 0;
	while (i < n ) {
		if (fabs(x[i] - 1.0) > 0.00001)return false;
		i++;
	}
	return true;
}
double* ResiKrautom() {

	double**matrix = alocirajMatricu();
	formirajHilberta(matrix);
	//ispisiMatricu(matrix);
	double**L = alocirajMatricu();
	double**U = alocirajMatricu();
	double*b = formirajB(matrix);


	KrautovAlgoritam(matrix, L, U);
	double*y = resavanjeDonjeTrougaone(L, b);
	//ispisiNiz(y);
	double*x = resavanjeGornjeTrougaone(U, y);

	
	free(y);
	free(b);
	dealocirajMatricu(matrix);
	dealocirajMatricu(L);
	dealocirajMatricu(U);
	return x;
}
double* ResiDulitlom() {

	double** matrix = alocirajMatricu();
	formirajHilberta(matrix);
	//ispisiMatricu(matrix);
	double** L = alocirajMatricu();
	double** U = alocirajMatricu();
	double* b = formirajB(matrix);


	DulitlovAlgoritam(matrix, L, U);
	double* y = resavanjeDonjeTrougaone(L, b);
	//ispisiNiz(y);
	double* x = resavanjeGornjeTrougaone(U, y);


	free(y);
	free(b);
	dealocirajMatricu(matrix);
	dealocirajMatricu(L);
	dealocirajMatricu(U);
	return x;

}
int main() {
	int k;
	double** matrix, **L, **U;
	double* b, *x=nullptr,*y;
	cout << "Unesite broj koji odgovara akciji koja zelite da se desi:" << endl;
	cout << "1.RESAVANJE SISTEMA ZA KONKRETNO N KORISCENJEM DULITLOVOG ALGORITMA" << endl;
	cout<< "2.RESAVANJE SISTEMA ZA KONKRETNO N KORISCENJEM KRAUTOVOG ALGORITMA" << endl;
	cout << "3.NALAZENJE NAJVECEG N ZA KOJE JE RESENJE TACNO NA 5 DECIMALA DULITLOVIM ALGORITMOM" << endl;
	cout << "4.NALAZENJE NAJVECEG N ZA KOJE JE RESENJE TACNO NA 5 DECIMALA KRAUTOVIM ALGORITMOM" << endl;
	cin >> k;
	switch (k) {
	case 1:
		printf("Unesite dimenziju Hilberove matrice:\n");
		scanf_s("%d", &n);
		x = ResiDulitlom();
		cout << "Resenje dobijeno Dulitlovim algoritmom:" << endl;
		ispisiNiz(x);
		free(x);
		break;    

	case 2:
		printf("Unesite dimenziju Hilberove matrice:\n");
		scanf_s("%d", &n);
		x = ResiKrautom();
		cout << "Resenje dobijeno Krautovim algoritmom:" << endl;
		ispisiNiz(x);
		free(x);
		break;

	case 3:
		n = 0;
		do {
			if (x) { free(x); }
			n++;
			x = ResiDulitlom();
			ispisiNiz(x);
		} while (check(x));
		cout <<"Najvece n za koje je resenje tacno na 5 decimala dobijeno Dulitlovim algotirmom je "<< (n-1) << endl;
		break;
	case 4:
		n = 0;
		do {
			if (x) { free(x); }
			n++;
			x = ResiKrautom();
			ispisiNiz(x);
		} while (check(x));
		cout << "Najvece n za koje je resenje tecno na 5 decimala dobijeno Krautovim algoritmom je " << (n - 1) << endl;
		break;
	};

	


}