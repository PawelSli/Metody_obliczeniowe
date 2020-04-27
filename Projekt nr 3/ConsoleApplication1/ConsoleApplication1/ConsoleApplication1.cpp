#include "pch.h"
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

double function1(double x);
double function2(double x);
double derivative_func1(double x);
double derivative_func2(double x);
double xi_function1(double x);
double xi_function2(double x);
double Picard_method(int i, double x, int n_max_approximation, double TOLX, double TOFL);
double Bisection_method(int i, double a, double b, int n_max_approximation, double TOLX, double TOLF);
double Newton_method(int i, double x, int n_max_approximation, double TOLX, double TOLF);
double Secant_method(int i, double X_0, double X_1, int n_max_approximation, double TOLX, double TOLF);

int main(int argc,char *argv[])
{
	cout.setf(ios::scientific);
	int max_iteration = 50;
	double error_estimator = 10e-50;
	double reziduum_estimator = 10e-50;

	cout << "Metoda Picarda:" << endl;
	cout << "Funkcja 1: sin(x/4)^2-1" << endl;
	cout << "Wartosc przyblizona: " << Picard_method(1, 0.0001, max_iteration, error_estimator, reziduum_estimator) << endl;
	cout << "Funkcja 2: tg(2x)-x-1" << endl;
	cout << "Wartosc przyblizona: " << Picard_method(2, 0.50, max_iteration, error_estimator, reziduum_estimator) << endl<<endl;

	cout << "Metoda Bisekcji:" << endl;
	cout << "Funkcja 1: sin(x/4)^2-1" << endl;
	cout << "Wartosc przyblizona: " << Bisection_method(1, -0.19, 4.0, max_iteration, error_estimator, reziduum_estimator) << endl;
	cout << "Funkcja 2: tg(2x)-x-1" << endl;
	cout << "Wartosc przyblizona: " << Bisection_method(2, 0.4, 0.6, max_iteration, error_estimator, reziduum_estimator) << endl << endl;

	cout << "Metoda Siecznych:" << endl;
	cout << "Funkcja 1: sin(x/4)^2-1" << endl;
	cout << "Wartosc przyblizona: " << Secant_method(1, -0.5, 0.6, max_iteration, error_estimator, reziduum_estimator) << endl;
	cout << "Funkcja 2: tg(2x)-x-1" << endl;
	cout << "Wartosc przyblizona: " << Secant_method(2, 0.4, 0.5, max_iteration, error_estimator, reziduum_estimator) << endl << endl;

	cout << "Metoda Newtona:" << endl;
	cout << "Funkcja 1: sin(x/4)^2-1" << endl;
	cout << "Wartosc przyblizona: " << Newton_method(1, -0.5, max_iteration, error_estimator, reziduum_estimator) << endl;
	cout << "Funkcja 2: tg(2x)-x-1" << endl;
	cout << "Wartosc przyblizona: " << Newton_method(2, 0.6, max_iteration, error_estimator, reziduum_estimator) << endl << endl;
	system("pause");
	return 0;
}

//Funkcja w pierwszym równaniu nieliniowym:
double function1(double x)
{
	double w = pow(sin(x / 4.0), 2.0);
	return w - x;
}
//Funkcja w drugim równaniu nieliniowym:
double function2(double x)
{
	double w = tan(2.0 * x);
	return w - x - 1.0;
}
//Pochodna funkcji pierwszego równania liniowego:
double derivative_func1(double x)
{
	double w = sin(x / 2.0);
	return (w - 4.0) / 4.0;
}
//Pochodna funkcji drugiego równania liniowego:
double derivative_func2(double x)
{
	double w = pow(cos(2.0*x), 2.0);
	return (2 / w) - 1;
}
//Wyznaczenia funkcji ksi i pochodnych funkcji dla rownan znajduje sie w moim zadaniu cwiczeniowym do tego laboratoriun
//Funkcja ksi dla pierwszego rownania uzywana w metodzie Picarda
double xi_function1(double x)
{
	double w = sin(x / 4.0);
	return pow(w, 2.0);
}
//Funkcja ksi dla drugiego rownania uzywana w metodzie Picarda
double xi_function2(double x)
{
	double w = tan(2.0*x);
	return w - 1;
}
//Implementacja metody Picarda:
double Picard_method(int i, double x, int n_max_approximation, double TOLX, double TOFL)
{
	//Parametr i sluzy do implementacji dwoch wersji metody Picard- jednej dla funkcji pierwszej, drugiej dla funkcji drugiej
	//Parametr n_max_approximation okresla maksymalna liczbe iteracji
	//Parametr TOLX okresla zadana tolerancje bledu
	//Parametr TOFL okresla zadana tolerancje reziduum
	double estymator = 0.0;
	double reziduum = 0.0;
	double X0 = x;

	switch (i)
	{
	case 1:
		for (int j = 0; j < n_max_approximation; j++)
		{
			cout << "Iteracja stopnia j = " << j;
			X0 = xi_function1(x); //przypisujemy nowe przyblizenie z funkcji ksi
			cout << "\tPrzyblizona wartosc = " << X0;
			estymator = fabs(X0 - x); //wyznaczamy estymator bledu
			x = X0;
			reziduum = fabs(X0); //wyznaczamy reziduum rownania nieliniowego
			cout << "\tReziduum = " << reziduum << "\t Estymator bledu = " << estymator << endl;
			if ((estymator <= TOLX && reziduum <= TOFL) || (reziduum <= TOFL)) //sprawdzamy warunki tolerancji bledu i tolerancji reziduum
				break;
		}
		break;
	case 2:
		for (int j = 0; j < n_max_approximation; j++)
		{
			cout << "Iteracja stopnia j = " << j;
			X0 = xi_function2(x);//przypisujemy nowe przyblizenie z funkcji ksi
			cout << "\tPrzyblizona wartosc = " << X0;
			estymator = fabs(X0 - x);//wyznaczamy estymator bledu
			x = X0;
			reziduum = fabs(X0);//wyznaczamy reziduum rownania nieliniowego
			cout << "\tReziduum = " << reziduum << "\t Estymator bledu = " << estymator << endl;
			if ((estymator <= TOLX && reziduum <= TOFL) || (reziduum <= TOFL))//sprawdzamy warunki tolerancji bledu i tolerancji reziduum
				break;
		}
		break;
	}
	return X0;
}
//Implementacja metody bisekcji:
double Bisection_method(int i, double a, double b, int n_max_approximation, double TOLX, double TOLF)
{
	//parametr i sluzy do instrukcji switch, aby moc jednoczesnie stworzyc funkcje dla dwoch rownan nieliniowych
	//a i b to granice przedzialu
	//Parametr n_max_approximation okresla maksymalna liczbe iteracji
	//Parametr TOLX okresla zadana tolerancje bledu
	//Parametr TOFL okresla zadana tolerancje reziduum
	double c = 0.0;
	double estymator = 0.0;
	double reziduum = 0.0;
	switch (i)
	{
	case 1:
		for (int j = 0; j < n_max_approximation; j++)
		{
			if (function1(a)*function1(b) > 0) // f(a) i f(b) sa tego samego znaku,co nie spelnia zalozen bisekcji
			{
				cout << "Bledny przedzial!" << endl;
				return EXIT_FAILURE;
			}
			else if (function1(a)*function1(b) < 0) // f(a) i f(b) roznego znaku
			{
				c = (a + b) / 2.0; //liczymy srodek przedzialu
				estymator = fabs((b - a) / 2.0); // wyliczamy estymator bledu
				reziduum = fabs(function1(c)); // wyliczamy reziduum rownania nieliniowego
				cout << "Iteracja stopnia j = " << j << "\t a = " << a << "\t c = " << c << "\t b = " << b << endl;
				cout << "Reziduum = " << reziduum << "\t Estymator bledu = " << estymator << endl;
				//Wybieramy podprzedzial, gdzie wartosci f(x) dla krancow sa roznego znaku
				if (function1(a)*function1(c) < 0)
				{
					b = c;
				}
				else
				{
					a = c;
				}

			}
			else //przypadek gdy iloczyn f(a) i f(b) daje zero
			{
				if ((function1(a) == 0) && (function1(b) == 0)) //przypadek, gdy dla a i b f(x) daje zero
				{
					cout << endl << "XO = " << a << "(" << function1(a) << ")" << ", oraz XO = " << b << "(" << function1(b) << ")" << endl;
					return a;
				}
				else if (function1(a) == 0.0) // przypadek, gdy f(x) dla a daje 0
				{
					return a;
				}
				else if (function1(b) == 0.0) // przypadek, gdy f(x) dla b daje 0
				{
					return b;
				}

			}
			if (estymator <= TOLX && reziduum <= TOLF) // sprawdzamy kryteria reziduum i tolerancji bledu
				break;
		}
		break;
	case 2:
		for (int j = 0; j < n_max_approximation; j++)
		{
			if (function2(a)*function2(b) > 0) // f(a) i f(b) sa tego samego znaku,co nie spelnia zalozen bisekcji
			{
				cout << "Bledny przedzial!" << endl;
				return EXIT_FAILURE;
			}
			else if (function2(a)*function2(b) < 0) // f(a) i f(b) roznego znaku
			{
				c = (a + b) / 2.0; //liczymy srodek przedzialu
				estymator = fabs((b - a) / 2.0); // wyliczamy estymator bledu
				reziduum = fabs(function2(c)); // wyliczamy reziduum rownania nieliniowego
				cout << "Iteracja stopnia j = " << j << "\t a = " << a << "\t c = " << c << "\t b = " << b << endl;
				cout << "Reziduum = " << reziduum << "\t Estymator bledu = " << estymator << endl;
				//Wybieramy podprzedzial, gdzie wartosci f(x) dla krancow sa roznego znaku
				if (function2(a)*function2(c) < 0)
				{
					b = c;
				}
				else
				{
					a = c;
				}

			}
			else //przypadek gdy iloczyn f(a) i f(b) daje zero
			{
				if ((function2(a) == 0) && (function2(b) == 0)) //przypadek, gdy dla a i b f(x) daje zero
				{
					cout << endl << "XO = " << a << "(" << function2(a) << ")" << ", oraz XO = " << b << "(" << function2(b) << ")" << endl;
					return a;
				}
				else if (function2(a) == 0.0) // przypadek, gdy f(x) dla a daje 0
				{
					return a;
				}
				else if (function2(b) == 0.0) // przypadek, gdy f(x) dla b daje 0
				{
					return b;
				}

			}
			if (estymator <= TOLX && reziduum <= TOLF) // sprawdzamy kryteria reziduum i tolerancji bledu
				break;
		}
		break;
	}
	return c; //zwracamy przyblizenie pierwiastka
}
//Funkcja implementujaca metode Newtona:
double Newton_method(int i, double x, int n_max_approximation, double TOLX, double TOLF)
{
	//parametr i sluzy do instrukcji switch, aby moc jednoczesnie stworzyc funkcje dla dwoch rownan nieliniowych
	//Parametr n_max_approximation okresla maksymalna liczbe iteracji
	//Parametr TOLX okresla zadana tolerancje bledu
	//Parametr TOFL okresla zadana tolerancje reziduum
	double X_0 = x;
	double X_1 = 0.0;
	double XX;
	double estymator = 0.0;
	double reziduum = 0.0;
	switch (i)
	{
	case 1:
		for (int j = 0; j < n_max_approximation; j++)
		{
			double y = function1(X_0); //wyliczamy wartosc funkcji dla danego przyblizenia
			double y_derivative = derivative_func1(X_0); //wyliczamy wartosc pochodnej funkcji dla danego przyblizenia
			X_1 = X_0 - y / y_derivative; //wyliczamy kolejne przyblizenie ze wzoru Newtona
			XX = X_0;
			X_0 = X_1; //obecny wyraz posluzy nam przy kolejnej iteracji,itd.
			estymator = fabs(X_1 - XX); //wyliczamy estymator bledu
			reziduum = fabs(X_1); //wyliczamy reziduum
			cout << "Iteracja stopnia j = " << j;
			cout << "\t Wartosc przyblizona = " << X_1;
			cout << "\tReziduum = " << reziduum << "\t Estymator bledu = " << estymator << endl;
			if (estymator <= TOLX || reziduum <= TOLF)//sprawdzamy warunki tolerancji bledu i tolerancji reziduum
				break;

		}
		break;
	case 2:
		for (int j = 0; j < n_max_approximation; j++)
		{
			double y = function2(X_0);//wyliczamy wartosc funkcji dla danego przyblizenia
			double y_derivative = derivative_func2(X_0);//wyliczamy wartosc pochodnej funkcji dla danego przyblizenia
			X_1 = X_0 - y / y_derivative;//wyliczamy kolejne przyblizenie ze wzoru Newtona
			XX = X_0;
			X_0 = X_1; //obecny wyraz posluzy nam przy kolejnej iteracji,itd.
			estymator = fabs(X_1 - XX); //wyliczamy estymator bledu
			reziduum = fabs(X_1);
			cout << "Iteracja stopnia j = " << j;
			cout << "\t Wartosc przyblizona = " << X_1;
			cout << "\tReziduum = " << reziduum << "\t Estymator bledu = " << estymator << endl;
			if (estymator <= TOLX ||  reziduum <= TOLF)//sprawdzamy warunki tolerancji bledu i tolerancji reziduum
				break;
		}
		break;
	}
	return X_1;
}
//Implementacja metody siecznych:
double Secant_method(int i, double X_0, double X_1, int n_max_approximation, double TOLX, double TOLF)
{
	//parametr i sluzy do instrukcji switch, aby moc jednoczesnie stworzyc funkcje dla dwoch rownan nieliniowych
	//Parametr n_max_approximation okresla maksymalna liczbe iteracji
	//Parametr TOLX okresla zadana tolerancje bledu
	//Parametr TOFL okresla zadana tolerancje reziduum
	double estymator = 0.0;
	double reziduum = 0.0;
	double X_2 = 0.0;
	switch (i)
	{
	case 1:
		for (int j = 0; j < n_max_approximation; j++)
		{
			X_2 = X_1 - function1(X_1) / ((function1(X_1) - function1(X_0)) / (X_1 - X_0)); //wyliczamy wartosc kolejnego przyblizenia ze wzoru metody siecznych
			estymator = fabs(X_2 - X_1); //wyliczamy estymator bledu
			reziduum = fabs(function1(X_2)); //wyliczamy reziduum
			X_0 = X_1;
			X_1 = X_2;
			if ((estymator <= TOLX && reziduum <= TOLF) || (reziduum <= TOLF)) //sprawdzamy,czy kryteria tolerancji bledu i tolerancji reziduum sa spelnione
				break;
			cout << "Iteracja stopnia j = " << j;
			cout << "\t Wartosc przyblizona = " << X_2;
			cout << "\tReziduum = " << reziduum << "\t Estymator bledu = " << estymator << endl;
		}
		break;
	case 2:
		for (int j = 0; j < n_max_approximation; j++)
		{
			X_2 = X_1 - function2(X_1) / ((function2(X_1) - function2(X_0)) / (X_1 - X_0));//wyliczamy wartosc kolejnego przyblizenia ze wzoru metody siecznych
			estymator = fabs(X_2 - X_1); //wyliczamy estymator bledu
			reziduum = fabs(function2(X_2)); //wyliczamy reziduum
			X_0 = X_1;
			X_1 = X_2;
			if ((estymator <= TOLX && reziduum <= TOLF) || (reziduum <= TOLF)) //sprawdzamy,czy kryteria tolerancji bledu i tolerancji reziduum sa spelnione
				break;
			cout << "Iteracja stopnia j = " << j;
			cout << "\t Wartosc przyblizona = " << X_2;
			cout << "\tReziduum = " << reziduum << "\t Estymator bledu = " << estymator << endl;
		}
		break;
	}
	return X_2;
}