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
        gsl_matrix_set(A, i, j, 1.0 / 1 + abs(i - j))
      :
        gsl_matrix_set(A, i, j, 0);
}

void zainicjalizuj_wektor_b(gsl_vector *b) {
  for(int i = 0; i < n; i++)
    gsl_vector_set(b, i, i+1);
}

int main() {
  //macierz A
  gsl_matrix *A = gsl_matrix_calloc(n, n);
  zainicjalizuj_macierz(A);

  //wektor wyrazow wolnych b
  gsl_vector *b = gsl_vector_calloc(n);
  zainicjalizuj_wektor_b(b);

  //wektor startowy x
  gsl_vector *x = gsl_vector_calloc(n);

  //metoda sprzezonego gradientu
  
  gsl_matrix_free(A);
  return 0;
}