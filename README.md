# G5-2020-1
# METODO DE GAUUS-JORDAN - COLAB
**_URL Colab:_**
**https://colab.research.google.com/drive/1oE8LVWYCuvRb9JTrqr53nox6_KoLl5kx?usp=sharing**



###### Método de Gauss Jordan.
En este proyecto contiene la implementación de solucionador de ecuaciones con el método de gauus para paralelizar la carga en diferentes subprocesos de cpu. El método de gauss para resolver las ecuaciones lineales es un método iterativo en el que los valores de las variables dadas siguen cambiando hasta que se alcanza un cierto humbral . bueno el objetivo de este método es proporcionar tiempo de solución mas rápido que la versión secuencial del código que todos conocemos .

###### Introduccion y antecedentes.
Los métodos de eliminación de gauus jordan tiene el propósito de elimnar las incognitas de las ecuaciones.

###### Requisitos de los metodos.
Un sistema de ecuaciones lineales Ax=b donde los coeficientes de A forman una matriz de nxn y b es un vector 1xn.

###### Es un metodo iterativo.
No son métodos interativos dan las soluciones de forma directa sin necesidad de hacer cálculos de error en las interaciones que se realizan.

###### Pivote: 
en una matriz el pivote es el primer elemento de una fila a partir de la izquierda que es el destino de cero cuando ocurre que el elemento pivote es cero, antes de normalizar cada renglón , se realiza el pivote parcial en el cual se determina el coeficiente mayor disponible de la columna debajo del pivote , se pude hacer un intercambio entre renglones de este modo el elemento se convertirá en el pivote .
###### Escalamiento:
sirve para estandarizar el tamaño determinante , se utiliza para minimizar errores de redondeo cuando en un sistema algunas ecuaciones tienen coeficientes mucho mayores que otros . se ralizan mediante la multiplicación de cada renglón por una constante distinta de cero.

# CODIGO, C++ EN COLAB.
**1.- haga clic en Tiempo de ejecución > Cambiar > GPU Acelerador de hardware.**

**2.- Actualice la instancia en la nube de CUDA on Server.**

```
!apt-get --purge remove cuda nvidia* libnvidia-*
!dpkg -l | grep cuda- | awk '{print $2}' | xargs -n1 dpkg --purge
!apt-get remove cuda-*
!apt autoremove
!apt-get update
```
**3.- Instalar CUDA Versión 9**
```
!wget https://developer.nvidia.com/compute/cuda/9.2/Prod/local_installers/cuda-repo-ubuntu1604-9-2-local_9.2.88-1_amd64 -O cuda-repo-ubuntu1604-9-2-local_9.2.88-1_amd64.deb
!dpkg -i cuda-repo-ubuntu1604-9-2-local_9.2.88-1_amd64.deb
!apt-key add /var/cuda-repo-9-2-local/7fa2af80.pub
!apt-get update
!apt-get install cuda-9.2
```
**4.- Marque la Versión de CUDA por: ejecutando el comando abajo para obtener la siguiente salida:**
```
!nvcc --version
```
**5.- Salida**
```
nvcc: NVIDIA (R) Cuda compiler driver Copyright (c) 2005-2018 NVIDIA Corporation
```
**6.- Ejecutar el comando dado para instalar una pequeña extensión para ejecutar nvcc desde celdas de Notebook.**
```
!pip install git+git://github.com/andreinechaev/nvcc4jupyter.git
```
**7.- Cargar la extensión usando este código**
```
%load_ext nvcc_plugin
```
**8.- En la primera linea de tu codigo pegar este pequeño fracmento de codigo.**
```
%%cu
```

# CODIGO - METODO DE GAUUS-JORDAN.
```
%%cu
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
```
