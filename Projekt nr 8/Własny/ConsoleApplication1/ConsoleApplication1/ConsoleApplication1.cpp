#include "pch.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <typeinfo>
#define USE_MATH_DEFINES
using namespace std;
double step = 0.1;
const int number_of_steps = 20;
const int number_of_approximation = 7;

template <typename T> T function(T x);
template <typename T> T prog_aprox_2p(T x, T h);
template <typename T> T back_aprox_2p(T x, T h);
template <typename T> T cent_aprox_2p(T x, T h);
template <typename T> T prog_aprox_3p(T x, T h);
template <typename T> T back_aprox_3p(T x, T h);
template <typename T> T derivative(T x);

int main()
{
    
}

//Funkcja reprezentująca równanie cos(x / 2)
template <typename T> T function(T x)
{
	return sin(x);
}

//Funkcja reprezentująca przybliżenia różnicowe progresywne dwupunktowe
template <typename T> T prog_aprox_2p(T x, T h)
{
	return (function(x + h) - function(x)) / h;
}

//Funkcja reprezentująca przybliżenia różnicowe wsteczne dwupunktowe
template <typename T> T back_aprox_2p(T x, T h)
{
	return (function(x) - function(x - h)) / h;
}

//Funkcja reprezentująca przybliżenia różnicowe centralne dwupunktowe
template <typename T> T cent_aprox_2p(T x, T h)
{
	return (function(x + h) - function(x - h)) / (2.0 * h);
}

//Funkcja reprezentująca przybliżenia różnicowe progresywne trzypunktowe
template <typename T> T prog_aprox_3p(T x, T h)
{
	return (4.0 * function(x + h) - (3.0 * function(x) + function(x + 2.0 * h))) / (2.0 * h);
}

//Funkcja reprezentująca przybliżenia różnicowe wsteczne trzypunktowe
template <typename T> T back_aprox_3p(T x, T h)
{
	return (function(x - 2.0 * h) - 4.0 * function(x - h) + 3.0 * function(x)) / (2.0 * h);
}

//Implementacja pochodnej funkcji danej w zadaniu:
template <typename T> T derivative(T x)
{
	return cos(x);
}

template <typename T>
void difference(T *kroki, T **wyniki)
{
	T start = 0.0;
	T cent = M_PI_4;
	T end = M_PI_2;
	T krok = KR;

	for (int i = 0; i < I_KR; i++)
	{
		kroki[i] = krok;

		wyniki[0][i] = fabs(fprim(start) - r_prog(start, krok));
		wyniki[1][i] = fabs(fprim(start) - r_prog_3pkt(start, krok));

		wyniki[2][i] = fabs(fprim(cent) - r_wste(cent, krok));
		wyniki[3][i] = fabs(fprim(cent) - r_cent(cent, krok));
		wyniki[4][i] = fabs(fprim(cent) - r_prog(cent, krok));

		wyniki[5][i] = fabs(fprim(end) - r_wste(end, krok));
		wyniki[6][i] = fabs(fprim(end) - r_wste_3pkt(end, krok));

		krok /= 10;
	}
}