#include "pch.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include <iomanip>
#include <windows.h>

using namespace std;

const char *funkcja1 = "Funkcja SINUSA: sin(x/4)^2-x";
const char *funkcja2 = "Funkcja TANGESA: tg(2x)-x-1";

typedef double(*function)(double);

//Funkcje :
//sin((x)/4)^2 -x
double f1(double x)
{
	return sin(x / 4.0) * sin(x / 4.0) - x;
}
//tg(2x)-x-1
double f2(double x)
{
	return tan(2.0 * x) - x - 1.0;
}

//Funkcje pochodne:
// (1/4)*(sin(x/2)-4)
double pochodnaf1(double x)
{
	return (1.0 / 4.0) * (sin(x / 2.0) - 4.0);
}
// -1 + 2/(cos(2x)^2)
double pochodnaf2(double x)
{
	return -1.0 + 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

//Funkcje xi:
// sin(x/4)^2
double xif1(double x)
{
	return sin(x / 4.0) * sin(x / 4.0);
}
// -1 + 2/(cos(2x)^2)
double xif2(double x)
{
	return tan(2 * x) - 1;
}

double Picard(function f, double x, int n_max, double TOLX, double TOLF) {
	/*
	* :funkction: czy jest to sin czy tg
	* :n_max: maxymalna liczba powtorzen
	* :TOLX: ograniczenie estymatora bledu
	* :TOLF: ograniczenie zbyt duzej roznicy wartosci od 0 do wyniku funkcji
	* :x:  x_dane
	* :X0: x_poczatkowe
	*/
	double __estymator = 0;
	double __reziduum = 0;
	double X0 = x;

	//iteracja
	for (int i = 0; i < n_max; i++)
	{
		cout << "iteracja i = " << i;
		X0 = f(X0);						//przypisanie nowej wartosci x-nastepne = wartosc funkcji, bo prosta ma rownanie y=x
		cout << "\t wartosc przyblizona = " << X0;

		__estymator = fabs(X0 - x);		//zmiana estymatora
		x = X0;

		__reziduum = fabs(X0);			//zmiana reziduum
		cout << "\t residuum = " << __reziduum << "\t estymator bledu=" << __estymator << endl;

		//sprawdzanie warunkow
		if ((__estymator <= TOLX && __reziduum <= TOLF) || (__reziduum <= TOLF))
			break;
	}
	return X0;
}

double Bisekcji(function f, double a, double b, int n_max, double TOLX, double TOLF)
{
	/*
	* :a: poczatek przedzialu
	* :b: koniec przedzialu
	* :TOLX: ograniczenie estymatora bledu
	* :TOLF: ograniczenie zbyt duzej roznicy wartosci od 0 do wyniku funkcji
	* :x:  x_dane
	*/
	double c = 0; //srodek przedzialu
	double __estymator = 0;
	double __reziduum = 0;
	for (int i = 0; i < n_max; i++)
	{
		if ((f(a) * f(b)) > 0)
		{
			cout << "Błędny przedział" << endl;
			return EXIT_FAILURE;
		}
		else if ((f(a) * f(b)) < 0)
		{

			c = (a + b) / 2.0;
			__estymator = fabs((b - a) / 2);
			__reziduum = fabs(f(c));
			cout << "iteracja i = " << i << "\t a= " << a << "\t c = " << c << "\t b= " << b << endl;
			cout << "residuum = " << __reziduum << "\t estymator bledu=" << __estymator << endl;
			if ((f(a) * f(c)) < 0)
			{
				b = c;
			}
			else {
				a = c;
			}
		}
		else
		{
			//ktores rowne zero
			if (!f(a) && f(b)) {
				//miejsce zerowe
				return a;
			}
			if (!f(b) && f(a)) {
				return b;
			}
			if (!f(b) && !f(a)) {
				//obydwa miejscami zerowymi
				cout << endl << "x0= " << a << "(" << f(a) << ")" << ", and x0=" << b << "(" << f(b) << ")" << endl;
				return a;
			}
		}
		if (__estymator <= TOLX && __reziduum <= TOLF)
			break;
	}
	return c;
}

double Newtona(function f, function p, double x, int n_max, double TOLX, double TOLF)
{
	/*
	* :funkction: czy jest to sin czy tg
	* :n_max: maxymalna liczba powtorzen
	* :TOLX: ograniczenie estymatora bledu
	* :TOLF: ograniczenie zbyt duzej roznicy wartosci od 0 do wyniku funkcji
	* :X0:  x_poczatkowe
	*/
	double x0 = x;
	double x1 = 0;
	double XX;
	for (int i = 0; i < n_max; i++) {
		double y = f(x0);
		double yp = p(x0);

		if (fabs(yp) < TOLX)
			break;
		x1 = x0 - y / yp;

		if (fabs(x1 - x0) <= TOLF * fabs(x1))
			break;
		XX = x0;
		x0 = x1;

		cout << "iteracja i=" << i;
		cout << "\t wartosc przyblizona = " << x1;
		cout << "\t residuum = " << fabs(x1) << "\t estymator bledu=" << fabs(x1 - XX) << endl;
	}
	return x1;
}

double Siecznych(function f, double x0, double x1, int n_max, double TOLX, double TOLF) {
	/*
	* :funkction: czy jest to sin czy tg
	* :n_max: maxymalna liczba powtorzen
	* :TOLX: ograniczenie estymatora bledu
	* :TOLF: ograniczenie zbyt duzej roznicy wartosci od 0 do wyniku funkcji
	* :X0:  x_poczatkowe
	* :X1: x_koncowe
	*/
	double __estymator = 0;
	double __reziduum = 0;
	double x2 = 0;
	for (int i = 0; i < n_max; i++) {
		x2 = x1 - f(x1) / ((f(x1) - f(x0)) / (x1 - x0));
		__estymator = fabs(x2 - x1);
		__reziduum = fabs(f(x2));
		x0 = x1;
		x1 = x2;

		if (__estymator <= TOLX && __reziduum <= TOLF || __reziduum <= TOLF)
			break;

		cout << "iteracja i=" << i;
		cout << "\twartosc przyblizona = " << x2;
		cout << "\t residuum = " << __reziduum << "\t estymator bledu=" << __estymator << endl;
	}

	return x2;
}


int main() {
	cout.setf(ios::scientific);
	const int max_iteracja = 50;
	double e = 10e-50;

	//	dla sinusa x0=0
	//	dla tangesa x0=0.489823930061471055363

	cout << "Metoda PICARDA:" << endl << funkcja1 << endl;;
	cout << "Wartosc przyblizona = " << Picard(xif1, 0.0001, max_iteracja, e, e) << endl;
	//	Funkcja jest rozbieżna
	cout << endl << funkcja2 << endl;
	cout << "Wartosc przyblizona = " << Picard(xif2, 0.50, max_iteracja, e, e) << endl;

	cout << endl << endl << "Metoda BISEKCJI:" << endl << funkcja1 << endl;
	cout << "Wartosc przyblizona = " << Bisekcji(f1, -0.19, 4.0, max_iteracja, e, e) << endl;
	cout << endl << funkcja2 << endl;
	cout << "Wartosc przyblizona = " << Bisekcji(f2, 0.4, 0.6, max_iteracja, e, e) << endl;

	cout << endl << endl << "Metoda NEWTONA: " << endl;
	cout << funkcja1 << endl;
	cout << "Wartosc przyblizona = " << Newtona(f1, pochodnaf1, -0.5, max_iteracja, e, e) << endl;
	cout << endl << funkcja2 << endl;
	cout << "Wartosc przyblizona = " << Newtona(f2, pochodnaf2, 0.6, max_iteracja, e, e) << endl;

	cout << endl << endl << "Metoda SIECZNYCH: " << endl;
	cout << funkcja1 << endl;
	cout << "Wartosc przyblizona = " << Siecznych(f1, -0.5, 0.6, max_iteracja, e, e) << endl;
	cout << endl << funkcja2 << endl;
	cout << "Wartosc przyblizona = " << Siecznych(f2, 0.4, 0.5, max_iteracja, e, e) << endl;

	system("pause");
	return 0;
}