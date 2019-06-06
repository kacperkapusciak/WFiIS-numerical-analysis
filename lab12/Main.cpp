#include <cmath>
#include <iostream>

const double a = 0.0, b = 1.0;

double f(double x) {
    return log(x*x*x + 3*x*x + x + 0.1) * sin(18*x);
}

void metodaSimpsona(int n) {
    //przedzial calkowania
    double h, N, suma;
    double tab[n+1][n+1] {0};
    for (int w = 0; w <= n; w++ ) {
        N = pow(2, w+1);
        h = ( (b - a) / N );
        suma = 0;
        for (int i = 0; i <= N/2 - 1; i++) {
            suma += (h / 3) * (f( a + 2*i*h )+ 4*f(a + (2*i+1)*h) + f(a + (2*i+2)*h) );
        }
        tab[w][0] = suma;
    }
    //richardson
    for (int w = 1; w <=n; w++)
        for(int k = 1; k < w+1; k++)
            tab[w][k] = (pow(4,k) * tab[w][k-1] - tab[w-1][k-1])/(pow(4, k) - 1);


    //wypisywanie
    for (int w = 0; w <=n; w++) {
        for(int k = 0; k < w+1; k++)
            std::cout << tab[w][k] << " ";
        std::cout << std::endl;
    }
}

void metodaMilne(int n) {
    double h, N, suma;
    double tab[n+1][n+1] {0};
    for (int w = 0; w <= n; w++ ) {
        N = pow(2, w+2);
        h = ( (b - a) / N );
        suma = 0;
        for (int i = 0; i <= N/4 - 1; i++) {
            suma += (4*h / 90) * (7*f( a + 4*i*h )+ 32*f(a + (4*i+1)*h) + 12*f(a + (4*i+2)*h) + 32*f(a + (4*i+3)*h) + 7*f(a + (4*i+4)*h) );
        }
        tab[w][0] = suma;
    }
    //richardson
    for (int w = 1; w <=n; w++)
        for(int k = 1; k < w+1; k++)
            tab[w][k] = (pow(4,k) * tab[w][k-1] - tab[w-1][k-1])/(pow(4, k) - 1);

    //wypisywanie
    for (int w = 0; w <=n; w++) {
        for(int k = 0; k < w+1; k++)
            std::cout << tab[w][k] << " ";
        std::cout << std::endl;
    }

}


int main() {
    metodaSimpsona(8);
    std::cout << std::endl;
    metodaMilne(8);
    return 0;
}