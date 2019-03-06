#include "deps.h"
#include <iostream>
#include <fstream>
#include <vector>
using std::cout;
using std::endl;
#define N 3

void inicjalizuj_macierz(float ***A){
  int licznik = 1;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) 
      (*A)[i][j] = licznik++;
}

void wypisz_macierz(float **A){
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++)
      printf("\t%3.4g\t", A[i][j]);
    cout << endl;
  }
  cout << endl;
}

void wyzeruj_macierz(float ***A){
  for(int i=1; i<=N; i++)
    for (int j=1; j<=N; j++)
      (*A)[i][j] = 0;
}

void wydziel_L(float ***L, float **A) {
  wyzeruj_macierz(L);
  for(int i=1; i<=N; i++){
    (*L)[i][i] = 1;
    for (int j=1; j<=N; j++)
      if(i > j) 
        (*L)[i][j] = A[i][j];
  }
}

void wydziel_U(float ***U, float **A) {
  wyzeruj_macierz(U);
  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++)
      if (i <= j) 
        (*U)[i][j] = A[i][j];
}

void wyzeruj_wektor(float **v){
  for (int i = 1; i <= N; i++) 
    (*v)[i] = 0;
}

void zainicjalizuj_wektory(std::vector<float *> &tab) {
  for (int i = 0; i < N; i++) {
    wyzeruj_wektor(&tab[i]);
    for (int j = 1; j <= N; j++)
      if (i+1 == j)
        tab[i][j] = 1;
  }
}

void wypisz_wektor(float *v) {
  for (int i = 1; i <= N; i++) 
    printf("%3.4g\n", v[i]);
  cout << endl;
}

void macierz_odwrotna(float **A, int *v, std::vector<float *> &tab, float ***A_inv) {
  for(int i = 1; i <= N; i++) {
    lubksb(A, N, v, tab[i-1]);
    // wypisz_wektor(tab[i-1]);
    for(int j = 1; j <= N; j++)
      (*A_inv)[j][i] = tab[i-1][j];
  }
  zainicjalizuj_wektory(tab);
}

float matrix_max(float **A) {
  float max = A[1][1];
  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++)
      if (max < A[i][j])
        max = A[i][j];

  return max;
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

void wpisz_macierz_do_pliku(float **A, std::ofstream *file) {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++)
      *file << (int)A[i][j] << "\t";
    *file << endl;
  }
  *file << endl;
}

int main() {
  float **A = matrix(1,N,1,N);
  float **B = matrix(1,N,1,N);

  inicjalizuj_macierz(&A);
  inicjalizuj_macierz(&B);
  B[1][1] = 1.1;

  cout << "Macierz A"<< endl;
  wypisz_macierz(A);
  
  cout << "Macierz B"<< endl;
  wypisz_macierz(B);
  //1. Znaleźć rozkłady LU macierzy A i B -------------- START
  int* v_A = ivector(1,N);
  float d_A;

  /* LU macierzy A */
  ludcmp(A, N, v_A, &d_A);
  cout << "Macierz LU od macierzy A" << endl;
  wypisz_macierz(A);

  float **L_A = matrix(1,N,1,N);
  wydziel_L(&L_A, A);
  cout << "Macierz L_A" << endl;
  wypisz_macierz(L_A);

  float **U_A = matrix(1,N,1,N);
  wydziel_U(&U_A, A);
  cout << "Macierz U_A" << endl;
  wypisz_macierz(U_A);

  /* LU macierzy B */
  int* v_B = ivector(1,N);
  float d_B;
  ludcmp(B, N, v_B, &d_B);
  cout << "Macierz LU od macierzy B" << endl;
  wypisz_macierz(B);

  float **L_B = matrix(1,N,1,N);
  wydziel_L(&L_B, B);
  cout << "Macierz L_B" << endl;
  wypisz_macierz(L_B);

  float **U_B = matrix(1,N,1,N);
  wydziel_U(&U_B, B);
  cout << "Macierz U_B" << endl;
  wypisz_macierz(U_B);

  //1. Znaleźć rozkłady LU macierzy A i B -------------- END

  // 2. Znaleźć macierze A^−1 oraz B^−1 -------------- START
  cout << "***********2***********" << endl << endl;

  float *b1 = vector(1,N);
  float *b2 = vector(1,N);
  float *b3 = vector(1,N);


  std::vector<float *> tab_wektorow;
  tab_wektorow.emplace_back(b1);
  tab_wektorow.emplace_back(b2);
  tab_wektorow.emplace_back(b3);

  zainicjalizuj_wektory(tab_wektorow);

  for (int i = 1; i<=N; i++) {
    cout << "Wektor b" << i << endl;
    wypisz_wektor(tab_wektorow[i-1]);
  }
  /*liczenie macierzy odwrotnej */
  float **A_inv = matrix(1,N,1,N);
  wyzeruj_macierz(&A_inv);
  macierz_odwrotna(A, v_A, tab_wektorow, &A_inv);
  cout << "Macierz odwrotna do macierzy A nie moze powstać ponieważ wyznacznik A wynosi 0" << endl;
  wypisz_macierz(A_inv); 

  float **B_inv = matrix(1,N,1,N);
  wyzeruj_macierz(&B_inv);
  macierz_odwrotna(B, v_B, tab_wektorow, &B_inv);
  cout << "Macierz odwrotna do macierzy B" << endl;
  wypisz_macierz(B_inv); 

  //3. Obliczyć wskaźniki uwarunkowania macierzy A i macierzy B -------------- START
  cout << "***********3***********" << endl << endl;
  float wskaznik_uwar_A = matrix_max(A) * matrix_max(A_inv);
  float wskaznik_uwar_B = matrix_max(B) * matrix_max(B_inv);
  cout << "Wskaznik uwarunkowania macierzy A wynosi: " << wskaznik_uwar_A << endl << endl;
  cout << "Wskaznik uwarunkowania macierzy B wynosi: " << wskaznik_uwar_B << endl << endl;

  //4.

  float **iloczyn_A = matrix(1,N,1,N);
  wyzeruj_macierz(&iloczyn_A);
  inicjalizuj_macierz(&A); //do przywrocenia A do stanu poczatkowego
  iloczyn_macierzy(A, A_inv, &iloczyn_A);

  float **iloczyn_B = matrix(1,N,1,N);
  wyzeruj_macierz(&iloczyn_B);
  inicjalizuj_macierz(&B); //do przywrocenia B do stanu poczatkowego
  B[1][1] = 1.1;
  iloczyn_macierzy(B, B_inv, &iloczyn_B);

  std::ofstream file;
  file.open("../wyniki.txt");
  file << "Wskaznik uwarunkowania macierzy A wynosi: " << wskaznik_uwar_A << endl << endl;
  file << "Wskaznik uwarunkowania macierzy B wynosi: " << wskaznik_uwar_B << endl << endl;

  file << endl << "Iloczyn macierzy A*A^-1:" << endl;
  wpisz_macierz_do_pliku(iloczyn_A, &file);

  file << endl << "Iloczyn macierzy B*B^-1:" << endl;
  wpisz_macierz_do_pliku(iloczyn_B, &file);

  file.close();
  return 0;
}
