#include "pch.h"
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	int mantysa_float=0, mantysa_double=0;
	float epsilon_float=1.f;
	double epsilon_double=1.L;
	//FLOAT:
	while ((epsilon_float/(2.f) + 1.f) > 1.f)
	{
		epsilon_float=epsilon_float/2.f;
		mantysa_float++;
	}
	cout << "Liczba bitow mantysy dla typu float: " << mantysa_float << endl;
	cout << "Epsilon dla typu float: " << epsilon_float << endl;
	//DOUBLE:
	while ((epsilon_double/(2.L) + 1.L) > 1.)
	{
		epsilon_double = epsilon_double / 2.;
		mantysa_double++;
	}
	cout << "Liczba bitow mantysy dla typu double: " << mantysa_double << endl;
	cout << "Epsilon dla typu double: " << epsilon_double << endl;
	return 0;
}
