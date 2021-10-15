/*	NELINEARNE JEDNACINE*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double funkcija(double x)
{
	return x * x - 1000 * x + 1;
}

double funkcija_g(double x)
{
	return 0.001 * (x * x + 1);
}

double prvi_izvod(double x)
{
	return 2 * x - 1000;
}

double drugi_izvod(double x)
{
	return 2;
}

int pocetak_iteracije(double a, double b)
{
	if (funkcija(a) * drugi_izvod(a) > 0)
		return a;

	if (funkcija(b) * drugi_izvod(b) > 0)
		return b;
}

bool provera(double a, double b)
{
	if (funkcija(a) * funkcija(b) < 0)
		return true;

	return false;
}

void metoda_polovljenja_intervala(double a, double b, double epsilon)
{
	int p = 0;
	double t, x_0, i, j;
	double prethodni = 0;

	for (i = a, j = b, p = 0; i <= j; p++)
	{
		x_0 = (i + j) / 2;

		printf("%d. iteracija:\n", p);
		printf("%lf\t%lf\n", prethodni, x_0);

		if (funkcija(x_0) == 0)
		{
			printf("Resenje sa tacnoscu %lf je %lf.\n", epsilon, x_0);
			break;
		}
		else
		{
			if (provera(x_0, j))
				i = x_0;

			else
				j = x_0;
		}

		t = prethodni - x_0;

		if (fabs(t) < epsilon)
		{
			printf("Resenje sa tacnoscu %lf je %lf.\n", epsilon, x_0);
			break;
		}

		prethodni = x_0;
	}
}


void metoda_proste_iteracije(double a, double b, double epsilon)
{
	int k = 0;
	double Xk, Xk_1;

	Xk_1 = a;

	printf("Iterativni proces:\n");
	printf("k \t\t X_k\n");
	printf("%d \t\t %lf\n", k, Xk_1);

	Xk = Xk_1;
	Xk_1 = funkcija_g(Xk);
	k++;

	while (fabs(Xk - Xk_1) > epsilon && funkcija_g(Xk_1) != 0)
	{
		printf("%d \t\t %lf\n", k, Xk_1);
		Xk = Xk_1;
		Xk_1 = funkcija_g(Xk);
		k++;
	}

	printf("%d \t\t %lf\n", k, Xk_1);
	printf("Resenje sa tacnoscu %lf je %lf.\n", epsilon, Xk_1);

}

void Njutnova_metoda(double a, double b, double epsilon)
{
	double Xk, Xk_1;
	int k = 0;

	printf("Iterativni proces:\n");

	Xk = pocetak_iteracije(a, b);

	printf("k \t\t Xk\n");
	printf("%d \t\t %lf\n", k, Xk);

	Xk_1 = Xk - funkcija(Xk) / prvi_izvod(Xk);

	while (fabs(Xk - Xk_1) > epsilon && funkcija(Xk_1) != 0)
	{
		k++;
		printf("%d \t\t %lf\n", k, Xk_1);
		Xk = Xk_1;
		Xk_1 = Xk - funkcija(Xk) / prvi_izvod(Xk);
	}

	printf("%d \t\t %lf\n", k + 1, Xk_1);
	printf("Resenje sa tacnoscu %lf je %lf.\n", epsilon, Xk_1);

}

void kvadratna_formula()
{
	double x_1, x_2;
	x_1 = 0.5 * (1000 + sqrt(1000 * 1000 - 4));
	x_2 = 0.5 * (1000 - sqrt(1000 * 1000 - 4));

	if (x_1 < x_2)
		printf("Resenje primenom kvadratne formule je %lf.\n", x_1);
	else
		printf("Resenje primenom kvadratne formule je %lf.\n", x_2);


}
void test(int aktivan_test, double a, double b, double epsilon)
{
	switch (aktivan_test)
	{
	case 1:
		/*METODA POLOVLJENJA INTERVALA*/
		printf("/*========================================*/\n");
		printf("/*METODA POLOVLJENJA INTERVALA*/\n");
		metoda_polovljenja_intervala(a, b, epsilon);
		printf("/*========================================*/\n\n");
		break;
	case 2:
		/*METODA PROSTE ITERACIJE*/
		printf("/*========================================*/\n");
		printf("/*METODA PROSTE ITERACIJE*/\n");
		metoda_proste_iteracije(a, b, epsilon);
		printf("/*========================================*/\n\n");
		break;
	case 3:
		/*NJUTNOVA METODA*/
		printf("/*========================================*/\n");
		printf("/*NJUTNOVA METODA*/\n");
		Njutnova_metoda(a, b, epsilon);
		printf("/*========================================*/\n\n");
		break;
	case 4:
		/*KVADRATNA FORMULA*/
		printf("/*========================================*/\n");
		printf("/*KVADRATNA FORMULA*/\n");
		kvadratna_formula();
		printf("/*========================================*/\n\n");
		break;
	}
}

int main()
{
	double niz[100], epsilon = 0.00001, a, b;
	int testovi[5] = { 1, 2, 3, 4 }, j = 0;

	for (int i = 0; i < 100; i++)
		niz[i] = i;

	while (j < 100)
	{
		if ((funkcija(niz[j]) > 0 && funkcija(niz[j + 1]) < 0) || (funkcija(niz[j]) < 0 && funkcija(niz[j + 1]) > 0))
		{
			a = niz[j];
			b = niz[j + 1];
			break;
		}
		j++;
	}

	for (int i = 0; i < 5; i++)
		test(testovi[i], a, b, epsilon);

}