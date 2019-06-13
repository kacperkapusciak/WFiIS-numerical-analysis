

#include <iostream>
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gauleg.c"
#include "/opt/NR/numerical_recipes.c/gaulag.c"
#include "/opt/NR/numerical_recipes.c/gauher.c"
#include "/opt/NR/numerical_recipes.c/gammln.c"
#include <math.h>
#include <fstream>
using namespace std;

double fun1(double x) {
    return 1.0/(x * sqrt( x*x - 1));
}

double fun2(double x) {
    return log(fabs(x));
}

double fun2b(double x) {
    return log(fabs(x))* exp(-x*x);
}
double fun3(double x) {
    return sin(2*x)*exp(-2*x);
}

void GaussLegandre(double (*f)(double), double a, double b, int n, ofstream &file, double wartosc_dokladna ) {

    for (int obecne_n  = 2; obecne_n <= n; obecne_n++) {
        float *x = vector(1, obecne_n);
        float *w = vector(1, obecne_n);

        gauleg(a, b, x, w, obecne_n);

        double suma = 0;

        for(int k = 1; k <= obecne_n; k++)
            suma += w[k] * f(x[k]);

        file << obecne_n << "\t" << fabs(suma - wartosc_dokladna) << endl;

        free_vector(x, 1, obecne_n);
        free_vector(w, 1, obecne_n);
    }
}

void GaussHermite(double (*f)(double), int n, ofstream &file, double wartosc_dokladna) {

    for (int obecne_n  = 2; obecne_n <= n; obecne_n += 2) {
        float *x = vector(1, obecne_n);
        float *w = vector(1, obecne_n);

        gauher(x, w, obecne_n);

        double suma = 0;

        for(int k = 1; k <= obecne_n; k++)
            suma += w[k] * f(fabs(x[k]));

        suma /= 2;

        file << obecne_n << "\t" << fabs(suma - wartosc_dokladna) << endl;

        free_vector(x, 1, obecne_n);
        free_vector(w, 1, obecne_n);
    }
}

void GaussLaguere(double (*f)(double), int n, ofstream &file, double wartosc_dokladna) {
    for (int obecne_n  = 2; obecne_n <= n; obecne_n++) {
        float *x = vector(1, obecne_n);
        float *w = vector(1, obecne_n);

        gaulag(x, w, obecne_n, 0);

        double suma = 0;

        for(int k = 1; k <= obecne_n; k++)
            suma += w[k] * f(fabs(x[k]));


        file << obecne_n << "\t" << fabs(suma - wartosc_dokladna) << endl;

        free_vector(x, 1, obecne_n);
        free_vector(w, 1, obecne_n);
    }
}

int main() {
    ofstream file("out1.dat"), file2("out2a.dat"), file3("out2b.dat"), file4("out3.dat");

    GaussLegandre(fun1, 1.0, 2.0, 100, file, M_PI / 3);


    GaussHermite(fun2, 100, file2, -0.8700577);

    GaussLegandre(fun2b, 0.0, 5.0, 100, file3, -0.8700577);

    GaussLaguere(fun3, 10, file4, 2.0/13);

    file.close();
    file2.close();
    file3.close();
}