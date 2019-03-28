#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/tqli.c"
#include "/opt/NR/numerical_recipes.c/tred2.c"
#include "/opt/NR/numerical_recipes.c/pythag.c"


#include "math.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

#define N 7

void zainicjalizuj_macierz(float ***A) {
    for (int i = 1; i <= N; i++) 
        for (int j = 1; j <= N; j++)
            (*A)[i][j] = sqrt(i + j);
 
}

void zainicjalizuj_wektor_jedynkami(float **v) {
    for (int i = 1; i <= N; i++)
        (*v)[i] = 1;
}

void wypisz_macierz(float **A) {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++)
      cout << A[i][j] << "\t";
    cout << endl;
  }
  cout << endl;
}

void wypisz_wektor(float *v) {
    for (int i = 1; i <= N; i++ )
        cout << v[i] << "\t";
    cout << endl;
}


void iloczyn_macierzy(float **A, float **B, float ***wynik) {
  float suma;
  for (int i = 1; i <= N; i++) 
    for (int j = 1; j <= N; j++) {
      suma = 0;
      for (int k = 1; k <= N; k++)
        suma += A[i][k] * B[k][j];
      (*wynik)[i][j] = suma;
    }       
}

double iloczyn_skalarny(float *v1, float *v2) {
  double suma = 0;
  for (int i = 1; i <= N; i++)
    suma += v1[i] * v2[i];
  return suma;
}

void iloczyn_macierz_wektor(float **A, float *wektor, float **wynik) {
  double suma;
  for (int i = 1; i <= N; i++) {
    suma = 0;
    for (int j = 1; j <= N; j++)
      suma += A[i][j] * wektor[j];
    (*wynik)[i] = suma;
  }
}

void iloczyn_wektorow_wynikiem_jest_macierz(float *v1, float *v2, float ***wynik) {
  for (int i = 1; i <= N; i++) 
    for (int j = 1; j <= N; j++) 
        (*wynik)[i][j] = v1[i] * v2[j];        
}

void iloraz_wektor_liczba(float **v, float liczba) {
    for (int i = 1; i <= N; i++)
        (*v)[i] /= liczba;
}

void skopiuj_wektor(float **kopia, float *oryginal) {
    for (int i = 1; i <= N; i++) 
        for (int j = 1; j <= N; j++) 
            (*kopia)[i] = oryginal[i];
}

void inicjalizuj_macierz_jednostkowa(float ***I) {
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) 
      (*I)[i][j] = i == j;
}

void iloczyn_macierz_stala(float ***A, float liczba) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) 
            (*A)[i][j] *= liczba;
}

void roznica_macierzy(float ***A, float **B) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) 
            (*A)[i][j] -= B[i][j];
}

void zapisz_wektor_do_pliku(float *v, std::ofstream *file) {
    for (int i = 1; i <= N; i++ )
        *file << v[i] << "\t";
    *file << endl;
}

int main () {
    float **A = matrix(1, N, 1, N);
    float **Z = matrix(1, N, 1, N);
    float **W = matrix(1, N, 1, N);
    float **wynik = matrix(1, N, 1, N);
    float *poprzedni = vector(1, N);
    float *aktualny = vector(1, N);

    float *d = vector(1, N);
    float *e = vector(1, N);

    float lambda;
    std::ofstream file;
    file.open("out.dat");

    zainicjalizuj_macierz(&A);
    zainicjalizuj_macierz(&W);

    inicjalizuj_macierz_jednostkowa(&Z);

    tred2(A, N, d, e);
    tqli(d, e, N, Z);

    cout << "Wartosci wlasne z Numerical Recipes: " << endl;
    wypisz_wektor(d);
    file << "Wartosci wlasne z Numerical Recipes: " << endl;
    zapisz_wektor_do_pliku(d, &file);
    cout << endl;
    file << endl;

    for (int k = 1; k <= N; k++) {

        zainicjalizuj_wektor_jedynkami(&poprzedni);

        for (int i = 1; i <= 8; i++) {
            iloczyn_macierz_wektor(W, poprzedni, &aktualny);
            lambda = iloczyn_skalarny(aktualny, poprzedni) / iloczyn_skalarny(poprzedni, poprzedni);
            iloraz_wektor_liczba(&aktualny, sqrt(iloczyn_skalarny(aktualny, aktualny)));
            skopiuj_wektor(&poprzedni, aktualny);

            file << lambda << "\t";
            cout << lambda << "\t";
        }
        file << endl;
        cout << endl;

        iloczyn_wektorow_wynikiem_jest_macierz(poprzedni, poprzedni, &wynik);
        iloczyn_macierz_stala(&wynik, lambda);
        roznica_macierzy(&W, wynik);

    }

    free_matrix(A, 1, N, 1, N);
    free_matrix(Z, 1, N, 1, N);
    free_matrix(W, 1, N, 1, N);
    free_matrix(wynik, 1, N, 1, N);

    free_vector(poprzedni, 1, N);
    free_vector(aktualny, 1, N);
    free_vector(d, 1, N);
    free_vector(e, 1, N);

    file.close();
    return 0;
}