#include "pch.h"
#include <iostream>
#include <math.h>
using namespace std;

const int N_MAX = 1000;
const int N_MIN = 1;

double exp_first(double, int);
double exp_second(double, int);
double blad_wzgl(double, double);

int main(int argc,char** argv)
{
	double x, fx1, fx2;
	double arr[6] = { -30,-20,-10,10,20,30 };
	// Pierwsza metoda, badanie bledu wzglednego od ilosci iteracji N:
	cout << "Pierwsza metoda, badanie bledu wzglednego od ilosci iteracji N:" << endl;
	cout << "  x      N       f(x)           Blad wzgledny  " << endl;
	for (int j = 0; j < 6; j++) {
		for (int k = 10; k <= N_MAX / 10; k += 15) {
			fx1 = exp_first(arr[j], k);
			cout.width(5);
			cout << arr[j];
			cout.width(7);
			cout << k;
			cout.width(15);
			cout.precision(7);
			cout << fx1;
			cout.width(15);
			cout.precision(4);
			cout << blad_wzgl(arr[j], fx1) << endl;
		}
		cout << endl;
	}

	cout << endl << endl;

	//Druga metoda, badanie zależności błędu względnego od ilości iteracji N:
	cout << "Druga metoda, badanie zaleznosci bledu wzglednego od ilosci iteracji N:" << endl << endl;
	cout << "  x      N       f(x)           Blad wzgledny  " << endl;
	for (int j = 0; j < 6; j++) {
		for (int k = 10; k <= N_MAX; k += 15) {
			fx2 = exp_second(arr[j], k);
			cout.width(5);
			cout << arr[j];
			cout.width(7);
			cout << k;
			cout.width(15);
			cout.precision(7);
			cout << fx2;
			cout.width(15);
			cout.precision(4);
			cout << blad_wzgl(arr[j], fx2) << endl;
		}
		cout << endl;
	}
	
	cout << endl << endl;

	cout << "Wartosci liczone druga metoda:" << endl << endl;
	cout << "  x       f(x)                     Blad wzgledny  " << endl;
	for (x = -30; x <= 30.L; x += 1.L) {
		fx2 = exp_second(x, N_MAX);
		cout.width(5);
		cout << x;
		cout.width(25);
		cout.precision(15);
		cout << fx2;
		cout.width(15);
		cout.precision(4);
		cout << blad_wzgl(x, fx2) << endl;

	}
	cout << endl;
}

double exp_first(double x,int c) {
	double r = 1.L;
	int i = 0;
	double k = 1.L;
	do {
		k *= x / ((double)i + 1.L);
		r += k;
		i++;
	} while (i <= c);
	return r;
}

double exp_second(double x, int c) {
	double r = 1.L;
	int i = 0;
	double k = 1.L;
	bool p = x >= 0;
	x = abs(x);
	do {
		k *= x/((double)i + 1.L);
		r += k;
		i++;
	} while (i <= c);
	return p ? r : 1.L / r;
}

double blad_wzgl(double x, double fx) {
	double f = exp(x);
	return abs((fx - f) / f);
}

