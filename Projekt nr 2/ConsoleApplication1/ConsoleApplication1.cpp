#include "pch.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

double exp_sys(double);
double log_blad(double y, double dokl);
double blad(double, double);
double another_method(double x);

//double yet_another_method(double x, int n);

int main()
{
	int start1, start2;
	string line1, line2, line3;
	ofstream zapis("dane.txt");
	ifstream wej1("danex.txt");
	ifstream wej2("danefunc.txt");
	ifstream wej3("danelog.txt");
	size_t *wsk = nullptr;
	double x, w, fx, fdok, log, logx, error;
	//Pierwsza wersja programu - korzystanie z funkcji systemowej exp():
	cout << "Pierwsza wersja programu:" << endl;
	cout << "W tej wersji do obliczenia wartosci funkcji (1-e^(-x))/x uzywam funkcji exp() dostepnej w C++" << endl;
	cout << "W ponizszych wynikach pierwszach kolumna to wartosci x w zakresie od 10^(-30) az do 10^9" << endl;
	cout << "Druga kolumna to wartosci danej funkcji" << endl;
	cout << "Trzecia kolumna to logarytm dziesietny z wartosci bezwglednej bledu wzglednego dla danych wynikow" << endl;
	cout << "Czwarta kolumna to blad wzgledny" << endl;
	cout << "Nacisnij dowolny przycisk, aby kontynuowac" << endl;
	cin >> start1;
	cout << "           x             f(x)           " << endl;
	if (wej1.good() && wej2.good() && wej3.good()) {
		while (!wej1.eof() && !wej2.eof() && !wej3.eof()) {
			getline(wej1, line1);
			getline(wej2, line2);
			getline(wej3, line3);
			x = stod(line1, nullptr);
			fdok = stod(line2, nullptr);
			logx = stod(line3, nullptr);
			fx = exp_sys(x);
			log = log_blad(fx, fdok);
			error = blad(fx, fdok);



			cout.width(15);
			cout.precision(7);
			cout << x;
			cout.width(15);
			cout.precision(20);
			cout << "\t" << fx;
			cout.width(20);
			cout.precision(10);
			cout << "\t" << log;
			cout.width(20);
			cout.precision(10);
			cout << "\t" << error << endl;
			zapis.width(20);
			zapis.precision(10);
			zapis << logx << "\t\t" << log << endl;
		}
	}
	wej1.close();
	wej2.close();
	wej3.close();
	zapis.close();


	cout << endl << endl;


	wej1 = ifstream("danex.txt");
	wej2 = ifstream("danefunc.txt");
	wej3 = ifstream("danelog.txt");
	ofstream save("final_dane.txt");
	x = 0;
	//Druga wersja programu - korzystamy z funkcji expm1:
	cout << "Druga wersja programu:" << endl;
	cout << "W tej wersji programu uzywamy funkcji expm1, ktora jest implementacja funkcji exp przystosowana dla wartosci od 0 do 1" << endl;
	cout << "Pierwsza kolumna to x, druga kolumna to wartosci funkcji,trzecia kolumna to logarytm wart.bezwgl.bledu wzglednego, a czwarta to blad wzgledny" << endl;
	cout << "Nacisnij dowolny przycisk, aby kontynuowac:" << endl;
	cin >> start2;

	if (wej1.good() && wej2.good()) {
		while (!wej1.eof() && wej2.good()) {
			getline(wej1, line1);
			getline(wej2, line2);
			getline(wej3, line3);
			x = stod(line1, nullptr);
			fdok = stod(line2, nullptr);
			logx = stod(line3, nullptr);
			fx = another_method(x);
			log = log_blad(fx, fdok);
			error = blad(fx, fdok);
			cout.width(15);
			cout.precision(7);
			cout << x;
			cout.width(15);
			cout.precision(20);
			cout << "\t" << fx;
			cout.width(20);
			cout.precision(10);
			cout << "\t" << log;
			cout.width(20);
			cout.precision(10);
			cout << "\t" << error << endl;
			zapis.width(20);
			zapis.precision(10);
			save << logx << "\t\t" << log << endl;
		}
		wej1.close();
		wej2.close();
		wej3.close();
		zapis.close();
		save.close();
		cout << endl << endl;
	}
}
double exp_sys(double x) {
	double w, k, g;
	g = -1.L*x;
	w = 1.L - exp(g);
	k = w / x;
	return k;
}

double another_method(double x) {
	double w, k, g;
	g = -1.L*x;
	w = -expm1(g);
	k = w / x;
	return k;
}

double blad(double y, double dokl) {
	double w;
	w = abs((y - dokl) / dokl);
	return w;
}

double log_blad(double y,double dokl){
	double w;
	w = abs((y - dokl) / dokl);
	return log10(w);
}

/*
double Taylor_function(double x, int n) {
	double result = 1.L;
	double k = 1.L;
	int i = 0;
	bool p = x >= 0;
	do {
		k *= (-1.L)*(x) / ((double)i + 1);
		result += k;
		i++;
	} while (i <= n);
	result=abs(result);
	return p ? result : 1.L / result;
}
*/
/*
double yet_another_method(double x,int n) {
	double w, k, g;
	k=1;
	g = 0;
	w = -x;
	int i = 1;
	do {
		k *= w / (i);
		g += k;
		i++;
	} while (i < n);
	return abs(g);
}*/