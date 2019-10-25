//PARA APRENDER MAS SOBRE ESTOS ALGORITMOS Y EL CODIGO, VISITA ESTE VIDEO >> "https://youtu.be/DQ5qqHukkAc"

#include <iostream> // Libreria para el manejo de entrada y salida de texto y otras cositas
#include <cmath>    // "cmath" es una colección de funciones matemáticas que necesito, como elevar al cuadrado y hacer la raiz cuadrada.
#include <fstream>
#include "timer.hh"

using namespace std; // Para no tener que poner "std" cada 2*3

int main(int argc, char **argv)
{ 
     long long N; // NÚMERO DE PUNTOS ALEATORIOS A LANZAR. ¡ESTA ES LA BAINA QUE PODEMOS CAMBIAR PARA MEJORAR LA PRECISION DEL CALCULO!
     N = (argc > 1) ? atoi(argv[1]) : 100;
     //cin >> N;
     cout<<N;
     
     double r = 1; // RADIO DEL CÍRCULO: Podes cambiar este número si lo deseas; el tamaño de la circunferencia no afecta a pi.

     srand((unsigned)time(0)); // Aqui le estamos dando el tiempo de reloj como semilla para que nuestro PC calcule los números aleatorios
                                   // asi aseguramos que se generen números aleatorios distintos.

     double x; // Defino las coordenadas de cada punto aleatorio. No queremos guardarlas; reescribiremos estas variable.
     double y;

     double c = 0; // Defino el número de puntos dentro del círculo (de la porción). Partimos de 0.

     int iter = 10; // iter. NÚMERO DE REPETICIONES DEL MÉTODO. Podes cambiar este número si lo deseas.

     double pi_ar[iter]; // Defino el arreglo que voy a llenar de los distintos pi's que obtenga.

     for (int j = 0; j < iter; j++)
     { // Primer BUCLE. Repetirá el dardboard algorithm "iter" veces.

          for (int i = 0; i < N; i++)
          { // Segundo BUCLE. En cada vuelta, lanza un dardo.

               x = (double)rand() / (double)RAND_MAX; // Generamos dos números aleatorios desde 0 a 1. Nótese que en los siguientes
               y = (double)rand() / (double)RAND_MAX; // lanzamientos estos números serán reescritos.

               x = x * r; // Dimensiono estos números en base a el radio. Ahora van de 0 a "r". Estas son las coordenadas
               y = y * r; // en las que ha caido un dardo.

               if (x * x + y * y < r * r)
               { // Compruebo si el dardo está o no dentro del circulo. Si es así, c aumentará en uno.
                    c++;
               }
          } // FIN Segundo BUCLE

          pi_ar[j] = 4 * c / N; // Calculo el pi generado en esta tanda y lo guardo en el arreglo.
          c = 0;                // Reinicio el contador de los disparos que cayeron dentro de la circunferencia.

     } // FIN Primer BUCLE

     double pi = 0; // Defino pi y el error de pi. Los inicializo a cero por el método para obtener la media y la SD.
     double err = 0;

     for (int j = 0; j < iter; j++)
     {
          pi = pi_ar[j] / iter + pi; // Hago la media de todos los pi's calculados
     }

     for (int j = 0; j < iter; j++)
     {
          err = err + pow(pi - pi_ar[j], 2) / iter; // Calculo la desviación estándar de los pi's calculados. Consulta su definición
     }                                             // para más info, pero es sumar estos términos y...

     err = sqrt(err); // ... hacer la raiz cuadrada de lo que te salga.
     cout.precision(15); // Establesco el número de digito de presicion que deseo ver en la pantalla.
     cout << pi << " , " << err << " , ";
     return 0; // Y listo cerramos la funcion principal con un return.
}