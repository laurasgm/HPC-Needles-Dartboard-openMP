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

#define MAX_THREADS 8

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
    int numChunks = MAX_THREADS;
    int chunk = N / numChunks;
    int k=0;
    double pi_ar[iter];
    ScopedTimer p;

    for (int j = 0; j < iter; j++)
    {
        #pragma omp parallel for shared(numChunks, chunk, l) reduction(+:c) private(k, x, y)
        for (int i = 0; i < numChunks; i++)
        {
            for (k = 0; k < chunk; k++) {
                x = (double)rand() / ((double)RAND_MAX * 2); //produces a random number between 0 and 0.5,
                double alpha = ((double)rand() / (double)RAND_MAX) * rpi;
                y = (l / 2.0) * sin(alpha);
                c = c + (x <= y);
            }
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
    cout <<N<<","<<p.elapsed()/1e+6<<","<<pi << "," << err <<endl;
    return 0;
}