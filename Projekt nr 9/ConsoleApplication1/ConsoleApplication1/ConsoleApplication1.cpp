#include "pch.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
using namespace std;

double p(double x)
{
	return 1.0;
}

double q(double x)
{
	return 0.0;
}

double r(double x)
{
	return -4.0;
}

double s(double x)
{
	return -1.0*x;
}

double analytical_formula(double x)
{
	return (exp(2.0 - 2.0*x) - 4.0*exp(4.0 - 2.0*x) + 4.0*exp(2.0*x) - exp(2.0 + 2.0*x) - 1.0*x + x * exp(4.0)) / (4.0 - 4.0*exp(4.0));

}

double max_blad(double *w, int n)
{
	double max = fabs(w[0]);
	for (int i = 1; i < n; i++)
		if (fabs(w[i] > max))
			max = fabs(w[i]);
	return max;
}

double *solve(double *a,double *b,double *c,double *d,int n)
{
	n--; // since we start from x0 (not x1)
	c[0] /= b[0];
	d[0] /= b[0];

	for (int i = 1; i < n; i++) {
		c[i] /= b[i] - a[i] * c[i - 1];
		d[i] = (d[i] - a[i] * d[i - 1]) / (b[i] - a[i] * c[i - 1]);
	}

	d[n] = (d[n] - a[n] * d[n - 1]) / (b[n] - a[n] * c[n - 1]);

	for (int i = n; i-- > 0;) {
		d[i] -= c[i] * d[i + 1];
	}
	return d;
}


double *Thomas(double *a, double *b, double *c, double *d, int n) 
{
	double *rozw = new double[n];
	double *beta = new double[n];
	double *gamma = new double[n];
	beta[0] = -c[0] / b[0];
	for (int i = 1; i < n; i++)
		beta[i] = -c[i] / (a[i] * beta[i - 1] + b[i]);
	gamma[0] = d[0] / b[0];
	for (int i = 1; i < n; i++)
		gamma[i] = (d[i] - a[i] * gamma[i - 1]) / (a[i] * beta[i - 1] + b[i]);
	rozw[n - 1] = gamma[n - 1];
	for (int i = n - 2; i >= 0; i--)
		rozw[i] = beta[i] * rozw[i + 1] + gamma[i];
	return rozw;
}

double dyskretyzacja_konwencjonalna(int n, double xpocz, double xkon)
{
	double pkt = xpocz;
	double *a = new double[n];
	double *b = new double[n];
	double *c = new double[n];
	double *d = new double[n];
	double *blad = new double[n];
	double *x = new double[n];
	double h = fabs(xkon - xpocz) / (n - 1);


	a[0] = 0;
	b[0] = 1;
	c[0] = 0;
	d[0] = 1;

	for (int i = 1; i <= n - 1; i++) {


		a[i] = 1.0 / (pow(h, 2.0));
		b[i] =-1.0*(2.0 / pow(h, 2.0))-4.0;
		c[i] = 1.0 / (pow(h, 2.0));
		d[i] = 0.0;
	}

	a[n - 1] = 0;
	b[n - 1] = 1;
	c[n - 1] = 0;
	d[n - 1] = 0;


	x = solve(a, b, c, d, n+1);

	for (int i = 0; i < n; i++) {
		blad[i] = fabs(x[i] - analytical_formula(pkt));
		pkt += h;
	}

	return max_blad(blad, n);
}


double dyskretyzacja_Numerowa(int n, double xpocz, double xkon) 
{
	double pkt = xpocz;
	double *a = new double[n];
	double *b = new double[n];
	double *c = new double[n];
	double *d = new double[n];
	double *blad = new double[n];
	double *x = new double[n];

	//Warunki brzegowe:
	double alfa = 0.0;
	double beta = 1.0;
	double gamma = -1.0;
	double fi = 0.0;
	double psi = 1.0;
	double theta = 0.0;

	double h = fabs(xkon - xpocz) / (n - 1);

	a[0] = 0.0;
	b[0] = 1.0;
	c[0] = 0.0;;
	d[0] = 1.0;
	double xi = xpocz;


	for (int i = 1; i < n - 1; i++) {
		xi += h;

		a[i] = p(xi) / (h*h) + 1. / 12.;
		b[i] = (-2.*p(xi)) / (h*h) + r(xi) * 10. / 12.;
		c[i] = p(xi) / (h*h) + 1. / 12.;
		d[i] = -(s(xi - h) + 10.*s(xi) + s(xi + h)) / 12.;
	}

	a[n - 1] = 0.0;
	b[n - 1] = 1.0;
	c[n - 1] = 0.0;
	d[n - 1] = 0.0;

	x = Thomas(a, b, c, d, n);

	for (int i = 0; i < n; i++) {
		blad[i] = fabs(x[i] - analytical_formula(pkt));
		pkt += h;
	}

	return max_blad(blad, n);
}

template <class typ> void writeToFile(typ x, typ y, int n = 0, string fileName = "wyniki.txt")
{
	static bool first = true;
	static std::fstream file;

	if (first) {
		first = false;
		file.open(fileName.c_str(), ios::out);
	}
	file << setprecision(15) << analytical_formula(x) << "\t\t\t";
	if (n == 1)
		file << setprecision(15) << (double)x << "	" << (double)y;
	if (n == 2)
		file << "	" << setprecision(15) << (double)y << "\n";
}


void dyskretyzacja(int n, int ndelta = 10, int nmax = 3000, double xpocz = 0.0, double xkon = 1.0)
{
	int i = 0;
	double x;
	double hmin = 0.0000000001;
	double hdelta = 0.001;

	double h = fabs(xkon - xpocz) / (n - 1);

	while (n < nmax) {
		h = fabs(xkon - xpocz) / (n - 1);
		n *= 1.5;
		i++;
		writeToFile(h, dyskretyzacja_konwencjonalna(n, 0.0, 1.0), 1);
		writeToFile(0.0, dyskretyzacja_Numerowa(n, 0.0, 1.0), 2);
	}
}


double **create_matrix(int m, int n) {
	double **macierz = new double *[m];
	for (int i = 0; i < m; i++)
		macierz[i] = new double[n];
	return macierz;
}

int main() 
{
	dyskretyzacja(2, 2, 30000);
	cout << "Zakonczono obliczenia.\n";
	system("PAUSE");
}

