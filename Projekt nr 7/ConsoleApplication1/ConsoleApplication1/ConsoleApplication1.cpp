#include "pch.h"
#include <iostream>
#include <math.h>
using namespace std;

const int N = 4;
const int I_MAX = 100;
const double EPS = 1.0e-08;

double **create_matrix(int n);
void clean_matrix(double **M, int n);
void fill_matrix(double **M, int n);
void show_matrix(double **M, int n);
double *create_vector(int n);
void fill_vector(double *v, double *tmp, int n);
void show_vector(double *v, int n);
double estimator(double *x, double *x1);
double reziduum(double **A, double *b, double *x);
void jacobi_method(double ** M, double *b, double *x);
void gauss_seidel_method(double **M, double *b, double *x);
void succesive_over_relaxation(double **M, double *b, double *x);


int main()
{
	double **A = create_matrix(N);
	double *b = create_vector(N);
	double *x = create_vector(N);

	double tmp_b[] = { 116.0, -226.0, 912.0, -1174.0 };
	double x0[] = { 2.0, 2.0, 2.0, 2.0 };

	fill_matrix(A, N);
	fill_vector(b, tmp_b, N);
	fill_vector(x, x0, N);

	cout << "Macierz A:\n";
	show_matrix(A, N);
	cout << "\nWektor b:\n";
	show_vector(b, N);
	cout << "\Przyblizenie poczatkowe x0:\n";
	show_vector(x, N);
	cout << endl;

	jacobi_method(A, b, x);

	fill_matrix(A, N);
	fill_vector(b, tmp_b, N);
	fill_vector(x, x0, N);

	gauss_seidel_method(A, b, x);

	fill_matrix(A, N);
	fill_vector(b, tmp_b, N);
	fill_vector(x, x0, N);

	succesive_over_relaxation(A, b, x);

	system("pause");
}

//Tworzenie nowej macierzy kwadratowej o n dlugosci:
double **create_matrix(int n)
{
	double **M;
	M = new double *[n];

	for (int i = 0; i < n; i++)
	{
		M[i] = new double[n];
	}

	return M;
}

//Czyszczenie macierzy:
void clean_matrix(double **M, int n)
{
	for (int i = 0; i < n; i++)
		delete M[i];

	delete M;
}



//Funkcja wypełnia macierz wartosciami podanymi w tresci zadania:
void fill_matrix(double **M, int n)
{
	double tmp[N][N] = { { 100.0, -1.0, 2.0, -3.0 },{ 1.0, 200.0, -4.0, 5.0 },{ -2.0, 4.0, 300.0, -6.0 },{ 3.0, -5.0, 6.0, 400.0 } };

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			M[i][j] = tmp[i][j];
	}
}

//Wypisywanie macierzy na ekran:
void show_matrix(double **M, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << M[i][j] << "\t";
		}
		cout << endl;
	}
}

//Tworzenie nowego wektora o dlugosci n:
double *create_vector(int n)
{
	double *v = new double[n];

	return v;
}

//Kopiowanie wartosci z jednego wektora do drugiego:
void fill_vector(double *v, double *tmp, int n)
{
	for (int i = 0; i < n; i++)
		v[i] = tmp[i];
}

//Wypisywanie wartosci wektora;  
void show_vector(double *v, int n)
{
	for (int i = 0; i < n; i++)
		cout << v[i] << "\t";
	cout << endl;
}

//Liczenie estymatora błedu:
double estimator(double *x, double *x1)
{
	double max;

	x[0] = fabs(x[0] - x1[0]);
	x[1] = fabs(x[1] - x1[1]);
	x[2] = fabs(x[2] - x1[2]);
	x[3] = fabs(x[3] - x1[3]);

	max = x[0];

	if (x[1] > max)
		max = x[1];
	if (x[2] > max)
		max = x[2];
	if (x[3] > max)
		max = x[3];

	return max;
}

//Liczenie reziduum:
double reziduum(double **A, double *b, double *x)
{
	double r[N];
	double max = r[0];

	r[0] = fabs((A[0][0] * x[0] + A[0][1] * x[1] + A[0][2] * x[2] + A[0][3] * x[3]) - b[0]);
	r[1] = fabs((A[1][0] * x[0] + A[1][1] * x[1] + A[1][2] * x[2] + A[1][3] * x[3]) - b[1]);
	r[2] = fabs((A[2][0] * x[0] + A[2][1] * x[1] + A[2][2] * x[2] + A[2][3] * x[3]) - b[2]);
	r[3] = fabs((A[3][0] * x[0] + A[3][1] * x[1] + A[3][2] * x[2] + A[3][3] * x[3]) - b[3]);

	if (r[1] > max)
		max = r[1];
	if (r[2] > max)
		max = r[2];
	if (r[3] > max)
		max = r[3];

	return max;
}

//Implementacja metody iteracyjnej Jacobiego:
void jacobi_method(double ** M, double *b, double *x)
{
	double *next = new double[N];
	double est = 1.0, rez = 1.0, suma = 0.0;
	int it = 0;

	cout << "\nMetoda Jacobiego\n";
	cout << "i\tx1\tx2\tx3\tx4\test\trez" << endl;

	while ((it < I_MAX) && ((fabs(est) >= EPS) && (fabs(rez) >= EPS)))
	{
		for (int i = 0; i < N; i++)
		{
			suma = 0.0;
			for (int j = 0; j < N; j++)
			{
				if (j != i) suma += M[i][j] * x[j];
			}
			next[i] = (1.0 / M[i][i]) * (b[i] - suma); //wyliczanie kolejnej iteracji
		}
		est = estimator(x, next); //liczenie estymatora danej iteracji
		rez = reziduum(M, b, next); //liczenie reziduum danej iteracji

		for (int i = 0; i < N; i++)
		{
			x[i] = next[i];
		}

		cout << it + 1 << "\t" << next[0] << "\t" << next[1] << "\t" << next[2] << "\t" << next[3] << "\t" << est << "\t" << rez << endl;

		it++;
	}
}

//Implemtancja metody iteracyjnej Gaussa_Seidala
void gauss_seidel_method(double **M, double *b, double *x)
{
	double *prev = new double[N];
	double est = 1.0, rez = 1.0, sum = 0.0;
	int it = 0;

	cout << "\nMetoda Gaussa-Seidela\n";
	cout << "i\tx1\tx2\tx3\tx4\test\trez\n";

	while ((it < I_MAX) && (fabs(est) >= EPS) && (fabs(rez) >= EPS))
	{
		for (int i = 0; i < N; i++)
		{
			sum = 0.0;
			for (int j = 0; j < N; j++)
				if (j != i)
					sum += M[i][j] * x[j];

			prev[i] = x[i];
			x[i] = (1.0 / M[i][i]) * (b[i] - sum); //wyliczanie kolejnej iteracji
		}

		est = estimator(prev, x); //liczenie estymatora danej iteracji
		rez = reziduum(M, b, x); //liczenie reziduum danej iteracji

		cout << it + 1 << "\t" << x[0] << "\t" << x[1] << "\t" << x[2] << "\t" << x[3] << "\t" << est << "\t" << rez << endl;

		it++;
	}
}

//Implementacja metody iteracyjnej sukcysywnej nadrealizacji:
void succesive_over_relaxation(double **M, double *b, double *x)
{
	double *next = new double[N];
	double *prev = new double[N];
	double est = 1.0, rez = 1.0, sum = 0.0, omega = 0.5;
	int it = 0;

	cout << "\nMetoda sukcesywnej nadrelaksacji (succesive_over_relaxation)\n";
	cout << "    i\t\tx1\t\tx2\t\tx3\t\tx4\t\test\t\trez\n";

	while ((it < I_MAX) && (fabs(est) >= EPS) && (fabs(rez) >= EPS))
	{
		for (int i = 0; i < N; i++)
		{
			sum = 0.0;
			for (int j = 0; j < N; j++)
				if (j != i)
					sum += M[i][j] * x[j];

			prev[i] = x[i];
			next[i] = (1.0 - omega) * x[i] + (omega / M[i][i]) * (b[i] - sum); //wyliczanie kolejnej iteracji
			x[i] = next[i];
		}

		est = estimator(prev, next); //liczenie estymatora danej iteracji
		rez = reziduum(M, b, next); //liczenie reziduum danej iteracji
		cout.width(5);
		cout.precision(4);
		cout << right << it + 1 << "\t\t" << right << x[0] << "\t\t" << right << x[1] << "\t\t" << right << x[2] << "\t\t" << right << x[3] << "\t\t" << right << est << "  \t\t" << left << rez << endl;

		it++;
	}
}
