#include "pch.h"
/*
		Laboratorium 5.
		Autor: Jan Szewczyk
Napisz program w języku „C/C++”, realizujący dekompozycję LU macierzy A, przy zastosowaniu
eliminacji Gaussa z częściowym wyborem elementu podstawowego, a następnie rozwiązujący układ
równań Ax = b.
*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

//Funkcja tworząca macierz
long double **nowaMacierz(int n, int m)
{
	long double **mac;
	mac = new long double *[n];

	for (int i = 0; i < n; i++)
		mac[i] = new long double[m];
	return mac;
}

//Funkcja tworząca wektor
long double *nowayWektor(int n)
{
	long double *vec;
	vec = new long double[n];
	return vec;
}

//Funkcja wypełniająca macierz wartościami
void wypelnijMacierz(long double **mac, int m, int n)
{
	long double tmp[4][4] = { { 1,-20,30,-4 },{ 2,-40,-6,50 },{ 9,-180,11,-12 },{ -16,15,-140,13 } };
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			mac[i][j] = tmp[i][j];
}

//Funkcja wypisująca macierz  
void wypiszMacierz(long double **mac, int m, int n) {
	for (int i = 0; i < m; i++) {
		cout << "| ";
		for (int j = 0; j < n; j++)
			printf("%18.10lf", mac[i][j]);
		cout << "|";
		cout << endl;
	}
}

//Funkcja wypisująca macierz  
void wypiszWektor(long double *mac, int m) {
	for (int i = 0; i < m; i++) {
		cout << "| ";
		printf("%18.10lf", mac[i]);
		cout << "|";
		cout << endl;
	}
}

//Funkcja realizację dekompozycji LU macierzy A
void elmnGauss(long double **A, long double **L, long double **U, int elem) {
	int i, j, k;
	for (i = 0; i < elem; i++) L[i][0] = A[i][0] / A[0][0];
	for (i = 0; i < elem; i++) L[i][i] = 1.0;

	for (i = 0; i < elem; i++)
	{
		for (int j = i + 1; j < elem; j++)
		{
			L[i][j] = 0;
			U[j][i] = 0;
		}
	}

	for (i = 0; i < elem; i++)
	{
		for (j = 0; j < elem; j++)
		{
			U[i][j] = 0;
			for (int k = 0; k < i; k++)
			{
				U[i][j] = U[i][j] + L[i][k] * U[k][j];
			}
			U[i][j] = A[i][j] - U[i][j];
		}

		for (j = i + 1; j < elem; j++)
		{
			L[j][i] = 0;
			for (k = 0; k < i; k++)
			{
				L[j][i] = L[j][i] + L[j][k] * U[k][i];
			}
			L[j][i] = (A[j][i] - L[j][i]) / U[i][i];
		}
	}
}

// rozwiazuje LUx=b      => Ly=b  ->y
void macierzL(long double **L, long double *b, long double *y) {
	for (int i = 0; i < 4; i++)
	{
		y[i] = b[i];
		for (int j = 0; j < 4; j++)
			if (i > j)
				y[i] -= L[i][j] * y[j];
	}
}

// rozwiazuje Ux=y -> x
void macierzU(long double **U, long double *y, long double *x) {
	for (int i = 3; i >= 0; i--)
	{
		x[i] = y[i];
		for (int j = 3; j >= 0; j--)
		{
			if (i < j)
				x[i] -= U[i][j] * x[j];

			if (i == j)
				x[i] /= U[i][j];
		}
	}
}

//Funkcja usuwająca macierz
void usunMacierz(long double **mac, int n)
{
	for (int i = 0; i < n; i++)
		delete[]mac[i];
	delete[]mac;
}

int main(int argc, char** argv) {

	long double **A = nowaMacierz(4, 4);
	long double **L = nowaMacierz(4, 4);					//Macierz trójkątna dolna
	long double **U = nowaMacierz(4, 4);					//Macierz trójkątna górna

	//Wektor b
	long double b[4] = { 35, 104, -366, -354 };
	long double *y = nowayWektor(4);
	long double *x = nowayWektor(4);

	wypelnijMacierz(A, 4, 4);
	cout << "\nMacierz A: \n" << endl;
	wypiszMacierz(A, 4, 4);

	elmnGauss(A, L, U, 4);

	cout << "\nMacierz trojkatna dolna: \n" << endl;
	wypiszMacierz(L, 4, 4);
	cout << "\nMacierz trojkatna gorna: \n" << endl;
	wypiszMacierz(U, 4, 4);

	macierzL(L, b, y);
	macierzU(U, y, x);

	cout << "\nY : \n" << endl;
	wypiszWektor(y, 4);
	cout << "\nX : \n" << endl;
	wypiszWektor(x, 4);

	usunMacierz(A, 4);
	usunMacierz(L, 4);
	usunMacierz(U, 4);
	delete[] x;
	delete[] y;


	system("pause");
}