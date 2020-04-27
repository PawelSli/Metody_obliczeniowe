#include "pch.h"
#include <iostream>
#include <Math.h>
#include <String>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <limits>
#include <iomanip>

std::fstream fileOUT("OUT.txt", std::ios_base::out);
std::fstream fileOUTnew("OUTnew.txt", std::ios_base::out);


//*************** Poprawione funkcje liczące błędy dla wartości [10 -30 , ~10] ***************//
//Funkcja licząca funkcję exp()
double funExp(double x)
{
	double y;
	return y = (1 - exp(-x)) / x;
}

//Funkcja licząca błąd
void blad()
{
	std::fstream fileIN("IN.txt", std::ios_base::in);

	std::cout.precision(18);
	int i = 0;
	double x;
	double rez;
	double war;

	while (fileIN >> x)
	{
		fileIN >> war;
		rez = funExp(war);
		//std::cout << rez << std::endl;
		fileIN >> x;
		i++;
		fileOUT << i << "\t" << war << "\t" << (fabs(rez - x)) / x << std::endl;
	}

	fileOUT.close();
	fileIN.close();
}

//*************** Poprawione funkcje liczące błędy dla wartości [10 -30 , ~10] ***************//
template<typename T>
double eps()
{
	T e = 1.0;
	int lmant = 0;
	while (e + 1 > 1) {
		e *= 0.5;
		lmant++;
	};
	e *= 2;
	lmant--;
	std::cout << "\nEpsilon: " << e << std::endl;
	std::cout << "Liczba mantys: " << lmant << std::endl;
	return e;
}

double epsilon = eps<double>();

//Funkcja licząca szereg taylora
double taylor(double x)
{
	double elem = 1.0;
	double sum = 0.0;
	int n = 1;
	while (fabs(elem) >= epsilon)
	{
		sum += elem;
		elem *= (-x) / (1 + n);
		n++;
		if (sum > 1E307 || sum != sum) //NaN
		{
			break;
			exit(0);
		}
	}
	return sum;
}

//Funkcja licząca poprawiony błąd
void blad_new()
{
	std::fstream fileIN("IN.txt", std::ios_base::in);

	double x;
	double war;
	double przyblizonaszereg;

	int counter = 0;
	std::cout.precision(18);

	while (fileIN >> x)
	{
		fileIN >> war;
		przyblizonaszereg = taylor(war);
		fileIN >> x;
		counter++;

		fileOUTnew << counter << "\t" << war << "\t" << fabs((przyblizonaszereg - x) / x) << std::endl;
		//std::cout<< counter << std::setw(30) << przyblizonaszereg << std::setw(30) << bladszereg << std::endl;
	}

	fileOUTnew.close();
	fileIN.close();
}

//***************** Funkcja main *****************//
int main(int argc, char** argv) {

	blad();
	blad_new();

	system("pause");
}