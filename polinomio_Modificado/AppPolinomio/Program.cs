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
    class Program
    {
        public static void Menu()
        {
            Console.WriteLine("");
            


        }
      
       
        public static void MultiplicarPolinomios()
        {
            cPolinomio p1 = cPolinomio.Crear();
            p1.Leer();
            cPolinomio p2 = cPolinomio.Crear();
            p2.Leer();
            cPolinomio P = p1 * p2;
            P.Mostrar();
            Console.ReadKey();

        }
     
        static void Main(string[] args)
        {
            Console.WriteLine(" MULTIPLICACION DE POLINOMIOS ");
            Console.WriteLine("==============================");
            MultiplicarPolinomios();
      
        }
    }
}
