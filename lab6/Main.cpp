#include <iostream>
#include <math.h>
#include <fstream>

const int N = 5;

double licz_r(double *a, double *b, int n, double x0) {
    b[n] = 0.0;
    for(int k = n - 1; k >= 0; k--) 
        b[k] = a[k+1] + x0 * b[k+1];
    
    return a[0] + x0 * b[0];;
}

int main() {
    double a[N+1], b[N+1], c[N];
    const int IT_max = 30;
    double x0, x1, x2;
    double Rj, Rj_1;
    int n;

    std::ofstream file;
    file.open("out.dat");

    a[5] = 1.0;
    a[4] = 14.0;
    a[3] = 33.0;
    a[2] = -92.0;
    a[1] = -196.0;
    a[0] = 240.0;

    for (int L = 1; L <= N; L++) {
        n = N - L + 1;
        x0 = 0;

        for (int it = 1; it <= IT_max; it++) {
            Rj = licz_r(a, b, n, x0);
            Rj_1 = licz_r(b, c, n - 1, x0);
            x1 = x0 - Rj / Rj_1;

            file << "L: "<< L << "\tit: " << it << "\tx0: " << x0 << "\tRj: " << Rj << "\tRj_1: " << Rj_1 << std::endl;
            if( fabs(x1 - x0) < 1.0E-7 ) break;

            x0 = x1;
        }
        std::cout << "Miejsce zerowe: " << x0 << std::endl;
        file << std::endl;

        for (int i = 0; i <= n - 1; i++) 
            a[i] = b[i];
        
    }

    file.close();
    return 0;
}