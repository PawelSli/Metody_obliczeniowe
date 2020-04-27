#include "pch.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include<vector>
#include<initializer_list>
using namespace std;


void LU_factorization(double **matrix,double **L,double **U)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			U[i][j] = matrix[i][j];
		}
	}
	//Array of permutation (0,1,2,...,n-1):
	int *p;
	p = new int[4];
	for (int i = 0; i < 4; i++)
		p[i] = i;

	for(long k=0;k<4;++k)
	{
		long max = k;
		for(long j=k+1;j<4;++j)
		{
			if (abs(U[p[j]][k] > abs(U[p[max]][k])))
				max = j;
		}
		std:swap(p[k], p[max]);

		for(long i=k+1;i<4;++i)
		{
			double z = U[p[i]][k] / U[p[k]][k];
			U[p[i]][k] = z;
			for (long j = k + 1; j < 4; ++j)
				U[p[i]][j] = U[p[i]][j] - z * U[p[k]][j];
		}

	}
	return;
}



double **create_Matrix(int n,int m)
{
	double **matrix;
	matrix = new double*[n];
	for(int i=0;i<n;i++)
	{
		matrix[i] = new double[m];
	}
	return matrix;
}

double *create_Vector(int n)
{
	double *vector;
	vector = new double[n];
	return vector;
}

void fill_Matrix(double **matrix,int n,int m)
{
	double tmp[4][4] = { { 1.0,-20.0,30.0,-4.0 },{ 2.0,-40.0,-6.0,50.0 },{ 9.0,-180.0,11.0,-12.0 },{ -16.0,15.0,-140.0,13.0 } };
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			matrix[i][j] = tmp[i][j];
		}
	}
}

void show_matrix(double **matrix,int n,int m)
{
	cout << endl;
	for(int i=0;i<n;i++)
	{
		cout << "|";
		for(int j=0;j<m;j++)
		{
			printf("\t%10.4lf", matrix[i][j]);
		}
		cout <<"|"<< endl;
	}
	cout << endl;
}

void show_vector(double *vector,int n)
{
	cout << endl << "[";
	for(int i=0;i<n;i++)
	{
		printf("\t%10.4lf", vector[i]);
	}
	cout<<"]"<< endl;
}

void eliminacja_Gaussa(double **A, double **L, double **U, int elem)
{
	int i, j, k;
	for (i = 0; i < elem; i++) L[i][0] = A[i][0] / A[0][0];
	for (i = 0; i < elem; i++) L[i][i] = 1.0;
	for ( i = 0; i < elem; i++)
	{
		for(int j=i+1;j<elem;j++)
		{
			L[i][j] = 0;
			U[j][i] = 0;
		}
	}

	for(i=0;i<elem;i++)
	{
		for(j=0;j<elem;j++)
		{
			U[i][j] = 0;
			for(int k=0;k < i;k++)
			{
				U[i][j] = U[i][j] + L[i][k] * U[k][j];
			}
			U[i][j] = A[i][j] - U[i][j];
		}

		for(j=i+1;j<elem;j++)
		{
			L[j][i] = 0;
			for(k=0;k<i;k++)
			{
				L[j][i] = L[j][i] + L[j][k] * U[k][i];
			}
			L[j][i] = (A[j][i] - L[j][i]) / U[i][i];
		}
	}
}


void matrixL(double **matrix,double *b,double *y)
{
	for(int i=0;i<4;i++)
	{
		y[i] = b[i];
		for(int j=0;j<4;j++)
		{
			if (i > j)
				y[i] -= matrix[i][j] * y[j];
		}
	}
}

void matrixU(double **matrix,double *y,double *x)
{
	for(int i=3;i>=0;i--)
	{
		x[i] = y[i];
		for(int j=3;j>=0;j--)
		{
			if (i < j)
				x[i] -= matrix[i][j] * x[j];
			if(i==j)
				x[i] /= matrix[i][j];
		}
	}
}

void delete_matrix(double **matrix,int n)
{
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}



int main(int argc,char **argv)
{
	double **A = create_Matrix(4, 4);
	double **L = create_Matrix(4, 4); //Macierz trójkątna dolna
	double **U = create_Matrix(4, 4); //Macierz trójkątna górna

	double b[4]= { 35.0, 104.0, -366.0, -354.0 };
	double *y = create_Vector(4);
	double *x = create_Vector(4);
	fill_Matrix(A, 4, 4);
	cout << "\nMacierz A:";
	show_matrix(A, 4, 4);
	cout << "\nPrzeprowadzamy test:\n------------------------------------\n";

	LU_factorization(A, L, U);



	//cout << "\nMacierz trojkatna dolna: \n" << endl;
	//show_matrix(L, 4, 4);
	cout << "\nMacierz trojkatna gorna: \n" << endl;
	show_matrix(U, 4, 4);
	cout << "\nPrzeprowadzamy test:\n------------------------------------\n";
	
	eliminacja_Gaussa(A, L, U, 4);


	cout << "\nMacierz trojkatna dolna: \n" << endl;
	show_matrix(L, 4, 4);
	cout << "\nMacierz trojkatna gorna: \n" << endl;
	show_matrix(U, 4, 4);

	matrixL(L, b, y);
	matrixU(U, y, x);

	cout << "\nY : \n" << endl;
	show_vector(y, 4);
	cout << "\nX : \n" << endl;
	show_vector(x, 4);

	delete_matrix(A, 4);
	delete_matrix(L, 4);
	delete_matrix(U, 4);
	delete[] x;
	delete[] y;
	system("pause");
}
