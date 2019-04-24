#include "../dependencies/deps.h"

#define N 6

void zainicjalizuj_macierz(double (*A)[N]) {
  for (int i = 0; i < N; i++) 
    for (int j = 0; j < N; j++) 
      A[i][j] = 1.0 / (sqrt(2 + abs(i - j)));
}

void wypisz_macierz(double (*A)[N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) 
      printf("\t%3.5g\t", A[i][j]);
    cout << endl;
  }
  cout << endl;
}


void iloczyn_macierzy(double (*A)[N], double (*B)[N], double (*wynik)[N]) {
  double suma;
  for (int i = 0; i < N; i++) 
    for (int j = 0; j < N; j+N) {
      suma = 0;
      for (int k = 0; k < N; k++)
        suma += A[i][k] * B[k][j];
      wynik[i][j] = suma;
    }  
}

void iloczyn_macierz_wektor(double (*A)[N], double *wektor, double *wynik) {
  double suma;
  for (int i = 0; i < N; i++) {
    suma = 0;
    for (int j = 0; j < N; j++)
      suma += A[i][j] * wektor[j];
    wynik[i] = suma;
  }
}

double iloczyn_skalarny(double *v1, double *v2) {
  double suma = 0;
  for (int i = 0; i < N; i++)
    suma += v1[i] * v2[i];
  return suma;
}

// void wpisz_do_pliku

int main()
{
  double A[N][N] = {};
  double X[N][N] = {};
  zainicjalizuj_macierz(A);
  wypisz_macierz(A);
  wypisz_macierz(X);
}
