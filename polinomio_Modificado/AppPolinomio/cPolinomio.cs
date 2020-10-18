using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//UNSAAC
//ESCUELA PROFECIONAL DE ING INFORMATICA Y DE SISTEMAS
//ISAI ISAAC MAMANI CRISPIN
//SEMESTRE 2020-1
//ANALISIS Y DISEÑO DE ALGORITMOS

namespace AppPolinomio
{
    //clse polinomio
    class cPolinomio
    {
        //   atributo privado 
        #region* ATRIBUTOS *
        private float[] aCoeficiente;

        #endregion**** FIN DE ATRIBUTOS ***
        #region*** CONSTRUCTORES ****
        //constructores

        public cPolinomio()
        {
            aCoeficiente = new float[100];
        }
        //creamos un arreglo para un grado
        public  cPolinomio( int pGrado )
        {
            aCoeficiente = new float[pGrado + 1];
            
        }
        //construimos un polinomio
        public static cPolinomio Crear()
        {
            return new cPolinomio();
        }
        //construccion del grado
        public static cPolinomio Crear(int pGrado)
        {
            return new cPolinomio(pGrado);

        }
        #endregion** FIN DE CONSTRUCTORES **
        #region** PROPIEDADES **
        //propiedades
        public int Grado
        {
            get { return aCoeficiente.Length - 1; }
        }
        private float getCoeficiente(int N)
        {
            if ((N >= 0) && (N <= Grado))
                return aCoeficiente[N];
            else
                return 0;
 
        }
        private void SetCoeficiente(int N,float Valor)
        {
            if ((N >= 0) && (N <= Grado))
                aCoeficiente[N] = Valor;
 
        }
        #endregion//********************** FIN DE PROPIEDADES ****************************
    // METODOS
        #region************************ METODOS *************************************
            //metodo mostrar para ver el resultado de la multiplicacion de dos polinomios
        public void Mostrar()
        {
            //creamos un entero   g que sera grado
            int g = Grado;
            Console.WriteLine("EL RESULTADO ES :");
            string Signo = "";
            //inicializamos un bucle  for 
            for (int k = g; k >= 0; k--)
            {
                Signo = aCoeficiente[k] > 0 ? "+" : "-";
                Console.Write(Signo+Math.Abs(aCoeficiente[k]).ToString()+"X^"+k.ToString());
            }
        }
        public void Leer()
        {
            Console.WriteLine("");
            Console.Write("INGRESE EL GRADO DEL POLINOMIO : ");
            int G = int.Parse(Console.ReadLine());
            aCoeficiente = new float[G + 1];
            for (int K = G; K >= 0; K--)
            {
                Console.Write("INGRESE EL COEFICIENTE DE  X^ " + K.ToString() + "=");
                aCoeficiente[K] = float.Parse(Console.ReadLine());
            }
        }
        private float Evaluar(int N , float X)
        {
            return N < Grado ? aCoeficiente[N] + X * Evaluar(N + 1, X) : aCoeficiente[N];
 
        }
        public float Evaluar(float X)
        {
            return Evaluar(0,X);
        }
        private void Agregar(cPolinomio p)
        {
            for (int k = 0; k <= p.Grado; k++)
                aCoeficiente[k] += p.getCoeficiente(k);
        }
        public static cPolinomio operator +(cPolinomio p1, cPolinomio p2)
        {
            int g = p1.Grado >= p2.Grado?p1.Grado : p2.Grado;
            cPolinomio p = new cPolinomio(g);
            p.Agregar(p1);
            p.Agregar(p2);
            return p ;
        }
       // metodo para multiplicar
        public static cPolinomio operator *(cPolinomio p1, cPolinomio p2)
        {
            cPolinomio p = new cPolinomio (p1.Grado+p2.Grado);
            for (int k1 = 0 ; k1<=p1.Grado ; k1++)
                for (int k2 = 0; k2 <= p2.Grado; k2++)
                {
                    float Valor = p.getCoeficiente(k1+ k2);
                    Valor += p1.getCoeficiente(k1) * p2.getCoeficiente(k2);
                    p.SetCoeficiente(k1+k2,Valor);
                }
            return p;
        }
    
    
    
        #endregion********************** FIN DE METODOS ****************************
    }
}
