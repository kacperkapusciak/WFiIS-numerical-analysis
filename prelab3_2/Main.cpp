//g++ Main.cpp -L/home/kiper/gsl/lib -I/home/kiper/gsl/include -lgsl -lgslcblas
#include "gsl/gsl_matrix.h"
#include "math.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

const int n = 1000;
const int m = 5;

void zainicjalizuj_macierz(gsl_matrix *A) {
  for (int i = 0; i < n; i++) 
    for(int j = 0; j < n; j++) 
      abs(i - j) <= m 
      ?
        gsl_matrix_set(A, i, j, 1.0 / (1.0 + abs(i - j)))
      :
        gsl_matrix_set(A, i, j, 0);
}

void zainicjalizuj_wektor_b(gsl_vector **b) {
  for(int i = 0; i < n; i++)
    gsl_vector_set(*b, i, i+1);
}

double iloczyn_skalarny(gsl_vector *v1, gsl_vector *v2) {
  double suma = 0;
  for (int i = 0; i < n; i++)
    suma += gsl_vector_get(v1, i) * gsl_vector_get(v2, i);
  return suma;
}

void iloczyn_macierz_wektor(gsl_matrix *A, gsl_vector *wektor, gsl_vector **wynik) {
  double suma;
  for (int i = 0; i < n; i++) {
    suma = 0;
    for (int j = 0; j < n; j++)
      suma += gsl_matrix_get(A, i, j) * gsl_vector_get(wektor, j);
    gsl_vector_set(*wynik, i, suma);
  }
}

double norma(gsl_vector *v) {
  return sqrt(iloczyn_skalarny(v, v));
}
 
int main() {
  //macierz A
  gsl_matrix *A = gsl_matrix_calloc(n, n);
  zainicjalizuj_macierz(A);

  //wektor wyrazow wolnych b
  gsl_vector *b = gsl_vector_calloc(n);
  zainicjalizuj_wektor_b(&b);

  //wektor startowy x
  gsl_vector *x = gsl_vector_calloc(n);  

  //metoda sprzezonego gradientu
    //inicjalizacja
  double alfa, beta, iloczyn_r;
  int liczba_iteracji = 0;
  gsl_vector *r = gsl_vector_calloc(n);
  gsl_vector *v = gsl_vector_calloc(n);
  gsl_vector *iloczyn_A_x = gsl_vector_calloc(n);
  gsl_vector *iloczyn_A_v = gsl_vector_calloc(n); 

    //pierwsza iteracja
  iloczyn_macierz_wektor(A, x, &iloczyn_A_x);
  for (int i = 0; i < n; i++) {
    gsl_vector_set(r, i, gsl_vector_get(b, i) - gsl_vector_get(iloczyn_A_x, i));
    gsl_vector_set(v, i, gsl_vector_get(r, i));
  }

    //kazda kolejna
  while (norma(r) > pow(10, -6)) {
    iloczyn_r = iloczyn_skalarny(r, r); //przechowanie do dalszych obliczen
    iloczyn_macierz_wektor(A, v, &iloczyn_A_v);
    alfa = iloczyn_r / iloczyn_skalarny(v, iloczyn_A_v);

    for (int i = 0; i < n; i++) {
      gsl_vector_set(x, i, gsl_vector_get(x, i) + alfa * gsl_vector_get(v, i));

      gsl_vector_set(r, i, gsl_vector_get(r, i) - alfa * gsl_vector_get(iloczyn_A_v, i));
    }

    beta =  iloczyn_skalarny(r, r)/iloczyn_r;

    for (int i = 0; i < n; i++) 
      gsl_vector_set(v, i, gsl_vector_get(r, i) + beta * gsl_vector_get(v, i));
    
    printf("%d\n", liczba_iteracji++);

    cout << "norma wektora: " << norma(r) << endl;
  }
  
  //zwalnianie pamieci
  gsl_matrix_free(A);
  gsl_vector_free(b);
  gsl_vector_free(x);
  gsl_vector_free(r);
  gsl_vector_free(v);
  gsl_vector_free(iloczyn_A_x);
  gsl_vector_free(iloczyn_A_v);
  return 0;
}