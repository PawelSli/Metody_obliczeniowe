#include "pch.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <typeinfo>

using namespace std;
double step = 0.1;
const int number_of_steps = 20;
const int number_of_approximation = 7;

template <typename T> void display_to_screen(T *steps, T **solutions);
template <typename T> T function(T x);
template <typename T> T aprox_prog_2pkt(T x, T h);
template <typename T> T aprox_wstecz_2pkt(T x, T h);
template <typename T> T aprox_centr_2pkt(T x, T h);
template <typename T> T aprox_prog_3pkt(T x, T h);
template <typename T> T aprox_wstecz_3pkt(T x, T h);
template <typename T> T derivative(T x);
template <typename T> void difference(T *steps, T **solutions);
template <typename T> void save_to_file(T *steps, T **solutionsn);

int main()
{
	float *kr_flt, **wy_flt;
	double *kr_dbl, **wy_dbl;

	kr_flt = new float[number_of_steps];
	kr_dbl = new double[number_of_steps];
	wy_flt = new float *[number_of_approximation];
	wy_dbl = new double *[number_of_approximation];

	for (int i = 0; i < number_of_approximation; i++)
	{
		wy_flt[i] = new float[number_of_steps];
		wy_dbl[i] = new double[number_of_steps];
	}

	difference<float>(kr_flt, wy_flt);
	cout << "Ponizej zamieszczamy blad bezwgledny przyblizen roznicowych dla zmiennej typu float." << endl<<endl;
	display_to_screen(kr_flt, wy_flt);
	difference<double>(kr_dbl, wy_dbl);
	cout << "Ponizej zamieszczamy blad bezwgledny przyblizen roznicowych dla zmiennej typu double." << endl << endl;
	display_to_screen(kr_dbl, wy_dbl);
	save_to_file<float>(kr_flt, wy_flt);
	save_to_file<double>(kr_dbl, wy_dbl);
	system("pause");
}

//Implementacja funkcji zadanej w ćwiczeniu:
template <typename T> T function(T x)
{
	return sin(x);
}

//Implementacja przyblizenia różnicowego progresywnego dla 2 punktów:
template <typename T> T aprox_prog_2pkt(T x, T h)
{
	T y = (function(x + h) - function(x)) / h;
	return y;
}

//Implementacja przybliżenia różnicowego wstecznego dla 2 punktów:
template <typename T> T aprox_wstecz_2pkt(T x, T h)
{
	T y = (function(x) - function(x - h)) / h;
	return y;
}

//Implementacja przybliżenia różnicowego centralnego dla 2 punktów:
template <typename T> T aprox_centr_2pkt(T x, T h)
{
	T y= (function(x + h) - function(x - h)) / (2.0 * h);
	return y;
}

//Implementacja przybliżenia różnicowego progresywnego dla 3 punktów:
template <typename T> T aprox_prog_3pkt(T x, T h)
{
	T y= (4.0 * function(x + h) - (3.0 * function(x) + function(x + 2.0 * h))) / (2.0 * h);
	return y;
}

//Implementacja przybliżenia różnicowego wstecznego dla 3 punktów:
template <typename T> T aprox_wstecz_3pkt(T x, T h)
{
	T y = (function(x - 2.0 * h) - 4.0 * function(x - h) + 3.0 * function(x)) / (2.0 * h);
	return y;
}

//Implementacja pochodnej funkcji zadanej w ćwiczeniu (function'(x)=cos(x)):
template <typename T> T derivative(T x)
{
	return cos(x);
}

//Funkcja która dla każdego z występujących przybliżeń różnicowych  wyznacza błąd bezwględny:
template <typename T> void difference(T *steps, T **solutions)
{
	T start = 0.0; //początek przedziału 0
	T cent = M_PI_4; //środek przedziału pi/4
	T end = M_PI_2;  //koniec przedziału pi/2
	T krok = step;

	for (int i = 0; i < number_of_steps; i++)
	{
		steps[i] = krok;
		solutions[0][i] = fabs(derivative(start) - aprox_prog_2pkt(start, krok)); //blad bezwgledny przyblizenia przyblizenia progresywnego dla 2pkt dla punktu poczatkowego
		solutions[1][i] = fabs(derivative(start) - aprox_prog_3pkt(start, krok)); //blad bezwgledny przyblizenia progresywnego dla 3pkt dla punktu poczatkowego
		solutions[2][i] = fabs(derivative(cent) - aprox_wstecz_2pkt(cent, krok)); //blad bezwgledny przyblizenia wstecznego dla 2pkt dla punktu srodkowego
		solutions[3][i] = fabs(derivative(cent) - aprox_centr_2pkt(cent, krok)); //blad bezwgledny przyblizenia centralnego dla 2pkt
		solutions[4][i] = fabs(derivative(cent) - aprox_prog_2pkt(cent, krok)); //blad bezwgledny przyblizenia progresywnego dla 2 pkt dla punktu srodkowego
		solutions[5][i] = fabs(derivative(end) - aprox_wstecz_2pkt(end, krok)); //blad bezwgledny przyblizenia wstecznego dla 2 pkt dla punktu koncowego
		solutions[6][i] = fabs(derivative(end) - aprox_wstecz_3pkt(end, krok)); //blad bezwgledny przyblizenia wstecznego dla 3 pkt dla punktu koncowego
		krok /= 10;
	}
}

//Funkcja wyswietlajaca wartosci bezwglednych przyblizen roznicowych na ekran:
template <typename T> void display_to_screen(T *steps,T **solutions)
{
	string *description1 = new string[8];
	description1[0] = "Krok";
	description1[1] = "POCZ-PR.2PKT"; //przyblizenie progresywne 2-punktowe dla punktu początkowego
	description1[2] = "POCZ-PR.3PKT"; //przyblizenie progresywne 3-punktowe dla punktu początkowego
	description1[3] = "SROD-WS.2PKT"; //przyblizenie wsteczne 2-punktowe dla punktu środkowego
	description1[4] = " SROD-CENTR."; //przybliżenie centralne dla punktu środkowego
	description1[5] = "SROD-PR.2PKT"; //przybliżenie progresywne 2-punktowe dla punktu środkowego
	description1[6] = "KONC-WS.2PKT"; //przybliżenie wsteczne 2-punktowe dla punku końcowego
	description1[7] = "KONC-WS.3PKT"; //przybliżenie wsteczne 3-punktowe dla punktu końcowego

	for(int i=0;i<number_of_approximation+1;i++)
	{
		cout.width(10);
		cout << left <<description1[i]<<"\t";
	}
	cout << endl;
	for(int i=0;i<number_of_steps;i++)
	{
		cout.width(10);
		cout << left << steps[i] << "\t";
		for(int j=0;j<number_of_approximation;j++)
		{
			cout.width(12);
			cout << right << solutions[j][i] << "\t";
		}
		cout << endl;
	}
	cout <<endl<< "Powysze wartosci zostaly nastepnie wpisane jako wartosc logarytmu log10(x) - uzyjemy tego do budowy wykresu zadanego w cwiczeniu." << endl<<endl;
	for (int i = 0; i < number_of_approximation + 1; i++)
	{
		cout.width(10);
		cout << left << description1[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < number_of_steps; i++)
	{
		cout.width(10);
		cout << left << log10(steps[i]) << "\t";
		for (int j = 0; j < number_of_approximation; j++)
		{
			cout.width(12);
			cout << right << log10(solutions[j][i]) << "\t";
		}
		cout << endl;
	}
}


//Funkcja wypisujaca do pliku zaleznosci bezwglednych przyblizen roznicowych od kroku sieci za pomoca skali logarytmicznej
template <typename T> void save_to_file(T *steps, T **solutions)
{
	fstream plik;
	string nazwa = "dane_";
	nazwa += typeid(T).name();
	nazwa += ".txt";
	plik.open(nazwa.c_str(), fstream::out);
	plik.width(6);
	for (int i = 0; i < number_of_steps; i++)
	{
		plik.width(5);
		plik << left << log10(steps[i]) << " ";

		for (int j = 0; j < number_of_approximation; j++)
		{
			plik.width(12);
			plik << left << log10(solutions[j][i]) << " ";
		}

		plik << endl;
	}

	plik.close();
}

