#include "pch.h"
/*
								Laboratorium 6.
								Autor: Jan Szewczyk
	Napisz program w jêzyku „C / C++”, realizuj¹cy algorytm Thomasa dla macierzy trój - diagonalnej o
	dowolnych rozmiarach N × N, a nastêpnie zastosuj ten program do rozwi¹zania uk³adu równañ
	Ax = b
*/
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

//Funkcja tworz¹ca macierz
double **nowaMacierz(int n, int m) {
	double **mac;
	mac = new double *[n];

	for (int i = 0; i < n; i++)
		mac[i] = new double[m];
	return mac;
}

//Funkcja wype³niaj¹ca macierz wartoœciami
void wypelnijMacierz(double **A, int m, int n) {
	double tmp[6][6] = {
		{10.0,1.0 / 2.0,0.0,0.0,0.0,0.0},
		{1.0 / 3.0,20.0,1.0 / 4.0,0.0,0.0,0.0},
		{0.0,1.0 / 5.0,30.0,1.0 / 6.0,0.0,0.0},
		{0.0,0.0,1.0 / 7.0,30.0,1.0 / 8.0,0.0},
		{0.0,0.0,0.0,1.0 / 9.0,20.0,1.0 / 10.0},
		{0.0,0.0,0.0,0.0,1.0 / 11.0,10.0}
	};
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = tmp[i][j];
}

//Funkcja wypisuj¹ca macierz  
void wypiszMacierz(double **mac, int m, int n) {
	for (int i = 0; i < m; i++) {
		cout << "| ";
		for (int j = 0; j < n; j++)
			printf("%8.4lf", mac[i][j]);
		cout << "|";
		cout << endl;
	}
}

//Funkcja wypisuj¹ca wektor  
void wypiszWektor(double *mac, int m) {
	for (int i = 0; i < m; i++) {
		cout << "|";
		printf("%10.4lf", mac[i]);
		cout << "|";
		cout << endl;
	}
	cout << endl;
}

//Funkcja rozwi¹zuj¹ca 
double *thomas(double **A, double *b, int n) {
	double *x = new double[n];
	for (int i = 1; i < n; i++) {							//Procedura pierwsza
		A[i][i] = A[i][i] - A[i][i - 1] / A[i - 1][i - 1] * A[i - 1][i];
		b[i] = b[i] - A[i][i - 1] / A[i - 1][i - 1] * b[i - 1];
		A[i][i - 1] = 0;
	}

	x[5] = b[5] / A[5][5];									//Procedura druga 
	for (int j = 4; j >= 0; j--)
		x[j] = (b[j] - A[j][j + 1] * x[j + 1]) / A[j][j];

	return x;
}

//Funkcja usuwaj¹ca macierz
void usunMacierz(double **mac, int n) {
	for (int i = 0; i < n; i++)
		delete[]mac[i];
	delete[]mac;
}

int main(int argc, char** argv) {

	double **A = nowaMacierz(6, 6);
	double b[6] = { 31.0,165.0 / 4.0,917.0 / 30.0,851.0 / 28.0,3637.0 / 90.0,332.0 / 11.0 };
	double* x = new double[6];

	wypelnijMacierz(A, 6, 6);

	cout << "Macierz troj-diagonalna A: " << endl;
	wypiszMacierz(A, 6, 6);

	cout << "\nb : " << endl;
	wypiszWektor(b, 6);

	x = thomas(A, b, 6);

	cout << "Rozwiazanie : " << endl;
	cout << "Wektor x : \n";
	wypiszWektor(x, 6);

	usunMacierz(A, 6);
	delete[] x;

	system("pause");
}