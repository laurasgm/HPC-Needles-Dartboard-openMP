 //PARA APRENDER MAS SOBRE ESTOS ALGORITMOS Y EL CODIGO, VISITA ESTE VIDEO >> "https://youtu.be/DQ5qqHukkAc"
 
 /*
    *   N = número de aguajas lanzadas
    *   l = largo de la aguja
    *   x = coordenada en x del centro
    *   y = coordenada en y del extremo de la aguja
    *   alpha = angulo de inclinación de la aguja
    *   c = número de agujas que cruzan una linea
*/
#include <iostream>
#include <cmath>
#include <fstream>
#include "timer.hh"

using namespace std;

const double rpi = 3.1415926535897932384626433832795;

int main(int argc, char **argv)
{
    long long N = 123456;
    N = (argc > 1) ? atoi(argv[1]) : 100;
    double l = 1.0;

    double c = 0;

    srand((unsigned)time(0));

    double x;
    double y;

    int iter = 10;
    double pi_ar[iter];
    ScopedTimer p;

    for (int j = 0; j < iter; j++)
    {
        for (int i = 0; i < N; i++)
        {
            x = (double)rand() / ((double)RAND_MAX * 2);
            double alpha = ((double)rand() / (double)RAND_MAX) * rpi;
            y = (l / 2.0) * sin(alpha);
            c = c + (x <= y);
        }
        pi_ar[j] = 2.0 * N / c;
        c = 0;
    }

    double pi = 0;
    double err = 0;

    for (int j = 0; j < iter; j++)
    {
        pi = pi_ar[j] / iter + pi;
    }

    for (int j = 0; j < iter; j++)
    {
        err = err + pow(pi - pi_ar[j], 2) / iter;
    }

    err = sqrt(err);
    cout.precision(10);
    cout <<N<<","<<p.elapsed()/1e+6<<","<<pi << "," << err;
    return 0;
}