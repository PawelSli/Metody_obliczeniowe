#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <conio.h>
using namespace std;
double **create_matrix(int n, int m);
void fill_matrix(double **matrix, int n, int m);
void draw_matrix(double **matrix, int n, int m);
void draw_vector(double *vector, int n);
double *thoma_function(double **matrix, double *b, int n);
void remove_matrix(double **matrix, int n);

/*
Program do zajęć nr 6:
*/
int main(int argc,char **argv)
{
	double **matrix = create_matrix(6, 6);
	double b[6] = { 31.0,165.0 / 4.0,917.0 / 30.0,851.0 / 28.0,3637.0 / 90.0,332.0 / 11.0 };
	double *solution = new double[6];
	fill_matrix(matrix, 6, 6);
	cout << "Macierz troj-diagonalna A:" << endl;
	draw_matrix(matrix, 6, 6);
	cout << "\nWektor b:" << endl;
	draw_vector(b, 6);
	solution = thoma_function(matrix, b, 6);
	cout << "Rozwiazanie: " << endl;
	cout << "Wektor x: " << endl;
	draw_vector(solution, 6);
	remove_matrix(matrix, 6);
	delete[] solution;

}

//Funkcja implementująca metodę Thomasa:
double *thoma_function(double **matrix, double *b, int n)
{
	//Tworzymy wskaźnik,który na końcu będzie zawierał rozwiązanie równania Ax=b:
	double *solution = new double[n];
	//Rozdzielamy nasz algorytm na dwie procedury: jedna dla macierzy , druga dla wektora:
	//Procedura dla macierzy:
	for (int i = 1; i < n; i++)
	{
		//Implementacja wzoru ni_i=d_i - l_i * (ni_i-1)^(-1)*u_i-1 zawartego w instrukcji:
		matrix[i][i] = matrix[i][i] - matrix[i][i - 1] / matrix[i - 1][i - 1] * matrix[i - 1][i];

	}
	//Procedura dla wektora:
	for (int i = 1; i < n; i++)
	{
		//Implementacja wzoru r_i =b_i - l_i *(ni_i-1)^(-1)*r_i-1 zawartego w instrukcji:
		b[i] = b[i] - matrix[i][i - 1] / matrix[i - 1][i - 1] * b[i - 1];
		matrix[i][i - 1] = 0;
	}
	//Następnie wyznaczamy rozwiązanie:
	//Ostatni element można podzielić bezpośrednio:
	solution[5] = b[5] / matrix[5][5];
	//Dla reszty korzystamy ze wzoru x_i= (ni_i)^(-1)*(r_i-u_i*x_i+1)
	int j = 4;
	while (j >= 0)
	{
		solution[j] = (b[j] - matrix[j][j + 1] * solution[j + 1]) / matrix[j][j];
		j--;
	}
	//Zwracamy rozwiązanie:
	return solution;
}


//Funkcja wypisująca podaną macierz o wymiarach n i m:
void draw_matrix(double **matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		cout << "|";
		for (int j = 0; j < m; j++)
			printf("%9.3lf", matrix[i][j]);
		cout << "|" << endl;
	}
}
//Funkcja wypisująca podany wektor o wymiarze n:
void draw_vector(double *vector, int n)
{
	cout << "|";
	for (int i = 0; i < n; i++)
	{
		printf("%9.3lf", vector[i]);
	}
	cout << "|" << endl;
}

//Funkcja tworząca daną macierz o wymiarach n i m:
double **create_matrix(int n, int m)
{
	double **matrix;
	matrix = new double*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new double[m];
	return matrix;
}

//Funkcja czyszcząca wskaźniki:
void remove_matrix(double **matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

//Funkcja wypełniająca podaną macierz wartościami podanymi w zadaniu:
void fill_matrix(double **matrix, int n, int m)
{
	double tmp[6][6] = {
		{10.0,1.0 / 2.0,0.0,0.0,0.0,0.0},
		{1.0 / 3.0,20.0,1.0 / 4.0,0.0,0.0,0.0},
		{0.0,1.0 / 5.0,30.0,1.0 / 6.0,0.0,0.0},
		{0.0,0.0,1.0 / 7.0,30.0,1.0 / 8.0,0.0},
		{0.0,0.0,0.0,1.0 / 9.0,20.0,1.0 / 10.0},
		{0.0,0.0,0.0,0.0,1.0 / 11.0,10.0}
	};
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			matrix[i][j] = tmp[i][j];
		}
	}
}