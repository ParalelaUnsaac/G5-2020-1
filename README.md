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


