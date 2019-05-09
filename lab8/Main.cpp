//-lgsl -lgslcblas
//plot "out.dat" u 1 w lp, "" u 2 w lp
#include <iostream>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <math.h>
#include <fstream>

const double lambda = 0.5;
const double mi = 0.5;

double f1(double x) {
    return 1.0 / (1.0 + x * x);
}

double f2(double x) {
    return cos(2 * x);
}



double wyznacz_M(double *x_w, double *y_w, double *m, int n) {
    double h = 10.0 / (n - 1);

    //wypelniono macierz i wektor
    gsl_matrix *A = gsl_matrix_calloc(n, n);
    gsl_vector *d = gsl_vector_calloc(n);

    for (int i = 0; i < n; i++) {
        if ( i > 1 && i < n - 1)
            gsl_vector_set(d, i, 6.0 / (2*h) * ((y_w[i+1] - y_w[i])/h - (y_w[i]-y_w[i-1])/h) );

        for (int j = 0; j < n; j++) {
            if (i == j) 
                gsl_matrix_set(A, i, j, 2);
            if (i == j - 1 || j == i - 1 ) 
                gsl_matrix_set(A, i, j, 0.5);
        }
    }
    gsl_matrix_set(A, 0, 1, 0);
    gsl_matrix_set(A, 0, 0, 1);
    gsl_matrix_set(A, n-2, n-1, 0);
    gsl_matrix_set(A, n-1, n-1, 1);

    //rozwiazanie
    gsl_linalg_HH_svx(A, d);

    //przepisanie do wektora m
    for (int i = 0; i < n; i++) {
        m[i] = gsl_vector_get(d, i);
    }

    //zwolnienie pamieci
    gsl_matrix_free(A);
    gsl_vector_free(d);
}

double wyznacz_S_x(double *x_w, double *y_w, double *m, int n, double x) {
    double h = 10.0 / (liczba_wezlow - 1);

    int i;
    for (i = 1; i < n; i++) 
        if(x >= x_w[i-1] && x <= x_w[i])
            break;
    
    double A = (y_w[i]-y_w[i-1])/h - (h / 6.0) * ( m[i] - m[i - 1] );
    double B = y_w[i - 1] - m[i - 1] * ((h * h) / 6.0);

    double S_x = m[i-1] * (pow(x_w[i]-x, 3)/(6 * h)) + m[i]*(pow(x-x_w[i-1],3)/(6 * h)) + A * (x - x_w[i-1]) + B;
    return S_x;
}

double druga_pochodna(double (*fun)(double), double x) {
    double dx = 0.01;
    return ( fun(x - dx) - 2 * fun(x) + fun(x + dx) )/(dx*dx);
}

double funkcje_sklejane(double (*fun)(double), int liczba_wezlow) {
    double wezly[liczba_wezlow];
    double wartosci[liczba_wezlow];

    double m[liczba_wezlow];

    double h = 10.0 / (liczba_wezlow - 1);

    int j = 0;
    
    for (double i = -5; i < 5; i += h, j++) {
        wezly[j] = i;
        wartosci[j] = fun(i);
    }

    wyznacz_M(wezly, wartosci, m, liczba_wezlow);

    double rozw[liczba_wezlow];
    j = 0;
    for (double i = -5.0; i <= 5.0 + 0.1 * h; i += h, j++) {
        rozw[j] = druga_pochodna(fun, i);
    }

    for (int i = 0; i < liczba_wezlow; i++) {
        std::cout << m[i] << "\t" << rozw[i] <<std::endl;
    } 
}

int main() {
    funkcje_sklejane(f1, 10);
    return 0;
}