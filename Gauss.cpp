// C++ Implementation for Gauss-Jordan 
//#include <bits/stdc++.h> 
#include <iostream>
#include <stdio.h>
//#include <omp.h>
#include <stdio.h>

#include <ctime> 
using namespace std;

#define M 40

// Función para imprimir la matriz
void PrintMatrix(float a[][M], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

// función para reducir la matriz a reducido
// forma escalonada de fila.
int RealizarOperacion(float a[][M], int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pro = 0;

	// Realización de operaciones elementales
#pragma omp parallel
	{
	#pragma omp for private(i)
		for (i = 0; i < n; i++)
		{
			if (a[i][i] == 0)
			{
				c = 1;
				while ((i + c) < n && a[i + c][i] == 0)
					c++;
				if ((i + c) == n) {
					flag = 1;
					break;
				}
				for (j = i, k = 0; k <= n; k++)
					swap(a[j][k], a[j + c][k]);
			}

			for (j = 0; j < n; j++) {

				// Excluyendo todos i == j 
				if (i != j) {

					// Conversión de Matrix en fila reducida
					// forma escalonada (matriz diagonal)
					float pro = a[j][i] / a[i][i];

					for (k = 0; k <= n; k++)
						a[j][k] = a[j][k] - (a[i][k]) * pro;
				}
			}
		}
	}
	return flag;
}

int PerformOperationSinPa(float a[][M], int n)
{
	int i, j, k = 0, c, flag = 0, m = 0;
	float pro = 0;

	// Realización de operaciones elementales 
	for (i = 0; i < n; i++)
	{
		if (a[i][i] == 0)
		{
			c = 1;
			while ((i + c) < n && a[i + c][i] == 0)
				c++;
			if ((i + c) == n) {
				flag = 1;
				break;
			}
			for (j = i, k = 0; k <= n; k++)
				swap(a[j][k], a[j + c][k]);
		}

		for (j = 0; j < n; j++) {

			// Excluyendo todos i == j
			if (i != j) {

				// Conversión de Matrix en fila reducida
				// forma escalonada (matriz diagonal) 
				float pro = a[j][i] / a[i][i];

				for (k = 0; k <= n; k++)
					a[j][k] = a[j][k] - (a[i][k]) * pro;
			}
		}
	}
	return flag;
}



// Función para imprimir el resultado deseado
// si existen soluciones únicas, de lo contrario
// imprime ninguna solución o infinitas soluciones dependiendo de la entrada dada.
void PrintResult(float a[][M], int n, int flag)
{
	cout << "Result is : ";

	if (flag == 2)
		cout << "Infinite Solutions Exists" << endl;
	else if (flag == 3)
		cout << "No Solution Exists" << endl;


	// Imprimir la solución dividiendo constantes por
	// sus respectivos elementos diagonales
	else {
		for (int i = 0; i < n; i++)
			cout << a[i][n] / a[i][i] << " ";
	}
}

// Para comprobar si infinitas soluciones
//existe o no existe solución
int CheckConsistency(float a[][M], int n, int flag)
{
	int i, j;
	float sum;

	// flag == 2 para una solución infinita
	// flag == 3 para ninguna solución
	flag = 3;
	for (i = 0; i < n; i++)
	{
		sum = 0;
		for (j = 0; j < n; j++)
			sum = sum + a[i][j];
		if (sum == a[i][j])
			flag = 2;
	}
	return flag;
}

int main()
{
	
	float a[M][M] = { { 0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 1, 1, 2, 6,6,7,6,9,8,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 2, 1, 1, 7,8,6,9,3,9,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 2, 1, 1, 7,8,6,9,3,9,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 1, 1, 2, 6,6,7,6,9,8,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 2, 1, 1, 7,8,6,9,3,9,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 2, 1, 1, 7,8,6,9,3,9,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 1, 1, 2, 6,6,7,6,9,8,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 2, 1, 1, 7,8,6,9,3,9,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 2, 1, 1, 7,8,6,9,3,9,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 1, 1, 2, 6,6,7,6,9,8,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 2, 1, 1, 7,8,6,9,3,9,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  },
					  { 2, 1, 1, 7,8,6,9,3,9,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5,0, 2, 1, 4,5,3,5,6,5,5  } };
					  
	
	// Orden de la matriz (n)
	int n = 40, flag = 0;

	// Realización de la transformación de matriz 

	double t0, t1,t2,t3;
	
	t0 = clock();
	flag = RealizarOperacion(a, n);
	t1 = clock();

	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Execution Time pa: " << time << endl;
	
	t2 = clock();
	flag = PerformOperationSinPa(a, n);
	t3 = clock();
	double time2 = (double(t3 - t2) / CLOCKS_PER_SEC);
	cout << "Execution Time sin: " << time2 << endl;
	
	if (flag == 1)
		flag = CheckConsistency(a, n, flag);

	// Impresión de matriz final
	cout << "La matriz aumentada final es: " << endl;
	PrintMatrix(a, n);
	cout << endl;

	// Soluciones de impresión(si existen)
	PrintResult(a, n, flag);
	

	return 0;
}