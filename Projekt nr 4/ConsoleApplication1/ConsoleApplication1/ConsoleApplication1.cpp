#include "pch.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
double function1(double x, double y, double z); 
double function2(double x, double y);
double function3(double x, double y);
void draw_Vector(double *a, int n);
void generalized_Newton_method(int max_iteration, double TOLF, double TOLX, double *value);

int main()
{
	cout.setf(ios::scientific);
	cout.precision(16);
	//Trzy kryteria zakonczenia iteracji: 
	int max_iteration = 50;	//1. liczba iteracji
	double reziduum_tolerance = 1e-16; //2. tolerancja reziduum
	double error_tolerance = 1e-16; //3. to
	//Przypisujemy wartosci poczatkowe:
	double value[3];
	value[0] = 1.4;
	value[1] = 0.3;
	value[2] = 0.4;

	int i;
	generalized_Newton_method(max_iteration, reziduum_tolerance, error_tolerance, value);
	system("pause");
	return 0;
}
//Funckja równania nr 1:
double function1(double x, double y, double z)
{
	return x * x + y * y + z * z - 2;
}
//Funkcja równania nr 2:
double function2(double x, double y)
{
	return x * x + y * y - 1;
}
//Funckja równania nr 3:
double function3(double x, double y)
{
	return x * x - y;
}
//Funkcja wypisujaca wszystkie elementy wektora:
void draw_Vector(double *a, int n)
{
	cout << fixed;
	cout << "\t[";
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << "]" << endl;
}
//Funkcja reprezentujaca ogolniona metoda Newtona:
void generalized_Newton_method(int max_iteration, double TOLF, double TOLX, double *value)
{
	int count = 0;//liczba przyblizen
	double det = 0;//wyznacznik

	double **reverse_jacobi_matrix;//podwojny wskaznik symbolizujacy macierz odwrotna do macierzy Jacobiego
	reverse_jacobi_matrix = new double*[3];
	for (int i = 0; i < 3; i++)
		reverse_jacobi_matrix[i] = new double[3];
	//Ponizszy wskaznik bedzie symbolizowal f(x_n) w uogolnionym wzorze Newtona:
	double *function_vector;
	//Poniszy wskaznik bedzie wektorem powstalym z wymnozenia macierz (J^D)^T przez wektor f(x_n)
	double *product_vector;
	//Ponizszy wskaznik reprezentuje nowe przyblizenia:
	double *new_value;
	function_vector = new double[3];
	product_vector = new double[3];
	new_value = new double[3];

	do
	{
		//Wyliczamy valuetosc elementow wektora f(x_n)
		function_vector[0] = function1(value[0], value[1], value[2]);
		function_vector[1] = function2(value[0], value[1]);
		function_vector[2] = function3(value[0], value[1]);

		det = 1 / ((-4 * value[0] * value[2]) - (8 * value[0] * value[1] * value[2]));
		//Kazdemu elementowi macierzy przypisujemy wartosc zgodnie z transponowana macierza dopelnien macierzy Jacobiego:
		//Wyznaczenie wzoru tej macierzy znajduje sie w moim zadaniu cwiczeniowym do tego samego laboratorium
		reverse_jacobi_matrix[0][0] = 0;
		reverse_jacobi_matrix[0][1] = (-2 * value[2])*det;
		reverse_jacobi_matrix[0][2] = (-4 * value[1] * value[2])*det;
		reverse_jacobi_matrix[1][0] = 0;
		reverse_jacobi_matrix[1][1] = (-4 * value[0] * value[2])*det;
		reverse_jacobi_matrix[1][2] = (4 * value[0] * value[2]) * det;
		reverse_jacobi_matrix[2][0] = (-2 * value[0] - 4 * value[0] * value[1]) * det;
		reverse_jacobi_matrix[2][1] = (2 * value[0] + 4 * value[0] * value[1]) * det;
		reverse_jacobi_matrix[2][2] = 0;
		//Mnozymy elementy wektora przez macierz zgodnie z uogolnionym wzorem Newtona
		product_vector[0] = (reverse_jacobi_matrix[0][0] * function_vector[0] + reverse_jacobi_matrix[0][1] * function_vector[1] + reverse_jacobi_matrix[0][2] * function_vector[2]);
		product_vector[1] = (reverse_jacobi_matrix[1][0] * function_vector[0] + reverse_jacobi_matrix[1][1] * function_vector[1] + reverse_jacobi_matrix[1][2] * function_vector[2]);
		product_vector[2] = (reverse_jacobi_matrix[2][0] * function_vector[0] + reverse_jacobi_matrix[2][1] * function_vector[1] + reverse_jacobi_matrix[2][2] * function_vector[2]);
		//Przeprowadzamy operacje: wektor x_n - powyzszy wektor
		for (int i = 0; i < 3; i++)
			new_value[i] = value[i] - product_vector[i];

		for (int i = 0; i < 3; i++)//Sprawdzamy kryterium dokladnosci wyznaczenia x_n:
			if (fabs(value[i] - new_value[i]) <= TOLX) 
				break;
		//Sprawdzamy kryterium wiarygodnosci x_n jako przyblizenia pierwiastka dla wszystkich trzech funkcji danego ukladu rownan
		if (fabs(function1(new_value[0], new_value[1], new_value[2])) <= TOLF)
			break;
		if (fabs(function2(new_value[0], new_value[1])) <= TOLF)
			break;
		if (fabs(function3(new_value[0], new_value[1])) <= TOLF)
			break;

		cout << endl << "Iteracja nr : " << count + 1 << endl;
		cout << "\tWartosc przyblizona : ";
		draw_Vector(new_value, 3);
		cout << "\testymator bledu : x = " << fabs(value[0] - new_value[0]) << "\t y = " << fabs(value[1] - new_value[1]) << "\t z = " << fabs(value[2] - new_value[2]) << endl;
		cout << "\treziduum : f1 = " << fabs(function1(new_value[0], new_value[1], new_value[2]))
			<< "\t f2 = " << fabs(function2(new_value[0], new_value[1]))
			<< "\t f3 = " << fabs(function3(new_value[0], new_value[1])) << endl;
		

		for (int i = 0; i < 3; i++)
			value[i] = new_value[i]; //Przypisujemy nowe wartosci
		count++;
	} while (count < max_iteration); //sprawdzamy liczbe iteracji
	//Czyscimy pamiec
	for (int i = 0; i < 3; i++)
		delete[] reverse_jacobi_matrix[i];
	delete[] reverse_jacobi_matrix;
	delete[] function_vector;
	delete[] product_vector;
	delete[] new_value;
}