#include "pch.h"
/*
This is a C++ Program to perform LU Decomposition of any matrix. In numerical analysis, LU decomposition (where ‘LU’ stands for ‘Lower Upper’, and also called LU factorization) factors a matrix as the product of a lower triangular matrix and an upper triangular matrix. The product sometimes includes a permutation matrix as well. The LU decomposition can be viewed as the matrix form of Gaussian elimination. Computers usually solve square systems of linear equations using the LU decomposition, and it is also a key step when inverting a matrix, or computing the determinant of a matrix
*/

#include<iostream>
#include<cstdio>

using namespace std;

int main(int argc, char **argv)
{
	void lu(float[][10], float[][10], float[][10], int n);
	void output(float[][10], int);
	float a[10][10], l[10][10], u[10][10];
	int n = 0, i = 0, j = 0;
	cout << "Enter size of 2d array(Square matrix) : ";
	cin >> n;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << "Enter values no:" << i << ", " << j << ": ";
			cin >> a[i][j];
		}
	}
	lu(a, l, u, n);
	cout << "\nL Decomposition\n\n";
	output(l, n);
	cout << "\nU Decomposition\n\n";
	output(u, n);
	return 0;
}
void lu(float a[][10], float l[][10], float u[][10], int n)
{
	int i = 0, j = 0, k = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j < i)
				l[j][i] = 0;
			else
			{
				l[j][i] = a[j][i];
				for (k = 0; k < i; k++)
				{
					l[j][i] = l[j][i] - l[j][k] * u[k][i];
				}
			}
		}
		for (j = 0; j < n; j++)
		{
			if (j < i)
				u[i][j] = 0;
			else if (j == i)
				u[i][j] = 1;
			else
			{
				u[i][j] = a[i][j] / l[i][i];
				for (k = 0; k < i; k++)
				{
					u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
				}
			}
		}
	}
}
void output(float x[][10], int n)
{
	int i = 0, j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%f ", x[i][j]);
		}
		cout << "\n";
	}
}