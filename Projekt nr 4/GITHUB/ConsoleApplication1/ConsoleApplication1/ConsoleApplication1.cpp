#include "pch.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
/*
	Przybli¿one wyniki :
	x = -0.79
	Y = 0.61
	z = -1.00
*/
//Funkcja : x^2 + y^2 + z^2 = 2
double f1(double x, double y, double z)
{
	return x * x + y * y + z * z - 2;
}

//Funkcja : x^2 + y^2 = 1
double f2(double x, double y)
{
	return x * x + y * y - 1;
}

//Funkcja : x^2 = y
double f3(double x, double y)
{
	return x * x - y;
}

void printVector(double * elem, int n)
{
	cout << fixed;

	cout << "\t[";

	for (int i = 0; i < n; i++)
	{
		cout << elem[i] << " ";
	}

	cout << "]" << endl;
}

void uogolnionaMetodaNewtonaDlaUkladowRownanNieliniowych(int count_max, double TOLX, double TOLF, double *war)
{
	int count = 0;						//numer iteracji
	double det;

	double ** jacobi;
	jacobi = new double *[3];
	for (int i = 0; i < 3; i++)
		jacobi[i] = new double[3];

	double *warF;
	warF = new double[3];

	double *warH;
	warH = new double[3];

	double *war_new;
	war_new = new double[3];


	do
	{
		//obliczanie wartoœci funkcji
		warF[0] = f1(war[0], war[1], war[2]);
		warF[1] = f2(war[0], war[1]);
		warF[2] = f3(war[0], war[1]);

		//obliczanie det
		det = 1 / ((-4 * war[0] * war[2]) - (8 * war[0] * war[1] * war[2]));

		//ustawienie macierzy jacobiana 
		jacobi[0][0] = 0;
		jacobi[0][1] = (-2 * war[2]) * det;
		jacobi[0][2] = (-4 * war[1] * war[2]) * det;
		jacobi[1][0] = 0;
		jacobi[1][1] = (-4 * war[0] * war[2]) * det;
		jacobi[1][2] = (4 * war[0] * war[2]) * det;
		jacobi[2][0] = (-2 * war[0] - 4 * war[0] * war[1]) * det;
		jacobi[2][1] = (2 * war[0] + 4 * war[0] * war[1]) * det;
		jacobi[2][2] = 0;


		//xn-jaco[]*warF[]/def
		//warH = jaco[]*warF[]/def
		warH[0] = (jacobi[0][0] * warF[0] + jacobi[0][1] * warF[1] + jacobi[0][2] * warF[2]);
		warH[1] = (jacobi[1][0] * warF[0] + jacobi[1][1] * warF[1] + jacobi[1][2] * warF[2]);
		warH[2] = (jacobi[2][0] * warF[0] + jacobi[2][1] * warF[1] + jacobi[2][2] * warF[2]);

		//obliczanie nowej wartoœci przybli¿onej  
		for (int i = 0; i < 3; i++)
			war_new[i] = war[i] - warH[i];

		//Kryteria zakoñczenia iteracji
		for (int j = 0; j < 3; j++)
			if (fabs(war[j] - war_new[j]) <= TOLX)
				break;

		if (fabs(f1(war_new[0], war_new[1], war_new[2])) <= TOLF)
			break;
		if (fabs(f2(war_new[0], war_new[1])) <= TOLF)
			break;
		if (fabs(f3(war_new[0], war_new[1])) <= TOLF)
			break;

		cout << endl << "===>ITERACJA : " << count + 1 << endl;
		cout << "\tWartosc przyblizona : " << endl;
		printVector(war_new, 3);
		cout << "\treziduum : f1 = " << fabs(f1(war_new[0], war_new[1], war_new[2]))
			<< "\t f2 = " << fabs(f2(war_new[0], war_new[1]))
			<< "\t f3 = " << fabs(f3(war_new[0], war_new[1])) << endl;
		cout << "\testymator bledu : x = " << fabs(war[0] - war_new[0]) << "\t y = " << fabs(war[1] - war_new[1]) << "\t z = " << fabs(war[2] - war_new[2]) << endl;

		for (int l = 0; l < 3; l++)
			war[l] = war_new[l];

		count++;
	} while (count < count_max);


	for (int m = 0; m < 3; m++)
		delete[] jacobi[m];
	delete[] jacobi;

	delete[] warF;
	delete[] warH;
	delete[] war_new;
}

int main(int argc, char* argv[])
{
	cout.setf(ios::scientific);
	cout.precision(16);
	int count_max = 50;					//maksymalna iloœæ itericji
	double epsilon = 1e-16;			//epsilon maszynowy 

	double war[3];
	war[0] = 1.4;
	war[1] = 0.3;
	war[2] = 0.4;

	uogolnionaMetodaNewtonaDlaUkladowRownanNieliniowych(count_max, epsilon, epsilon, war);


	std::system("pause");
}
