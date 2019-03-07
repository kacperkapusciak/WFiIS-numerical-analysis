#include "deps.h"
#include <vector>

#define N 4

void inicjalizuj_macierz(float ***A){
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) 
      (*A)[i][j] = 1.0/(i+j);
}

void wypisz_macierz(float **A){
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++)
      printf("\t%3.3g\t", A[i][j]);
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

float wyznacznik(float **A) {
  float wynik = 1.0;
  for (int i = 1; i <= N; i++)
    wynik *= A[i][i];
  return wynik;
}

void wyzeruj_wektor(float **v){
  for (int i = 1; i <= N; i++) 
    (*v)[i] = 0;
}

void wypisz_wektor(float *v) {
  for (int i = 1; i <= N; i++) 
    printf("%3.4g\n", v[i]);
  cout << endl;
}

void zainicjalizuj_wektory(std::vector<float *> &tab) {
  for (int i = 0; i < N; i++) {
    wyzeruj_wektor(&tab[i]);
    for (int j = 1; j <= N; j++)
      if (i+1 == j)
        tab[i][j] = 1;
  }
}

void macierz_odwrotna(float **A, int *v, std::vector<float *> &tab, float ***A_inv) {
  for(int i = 1; i <= N; i++) {
    lubksb(A, N, v, tab[i-1]);
    for(int j = 1; j <= N; j++)
      (*A_inv)[j][i] = tab[i-1][j];
  }
  zainicjalizuj_wektory(tab);
}

void iloczyn_macierzy(float **A, float **B, float ***wynik) {
  wyzeruj_macierz(wynik);
  for (int i = 1; i <= N; i++) 
    for (int j = 1; j <= N; j++) 
      for (int k = 1; k <= N; k++)
        (*wynik)[i][j] += A[i][k] * B[k][j];
}

float matrix_max(float **A) {
  float max = abs(A[1][1]);
  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++)
      if (max < abs(A[i][j]))
        max = abs(A[i][j]);

  return max;
}

int main() {
  float **A = matrix(1, N, 1, N);
  inicjalizuj_macierz(&A);
  cout << "Macierz A:" << endl;
  wypisz_macierz(A);

  // 1. Znaleźć rozkład LU macierzy A przy użyciu procedury ludcmp
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

  float wyznacznikA = wyznacznik(L_A) * wyznacznik(U_A);
  cout << "Wyznacznik macierzy A: " << wyznacznikA << endl;

  /*2. Zapisać do pliku: elementy diagonalne macierzy U oraz wyznacznik macierzy A*/
  std::ofstream file;
  file.open("../wyniki.txt");

  file << "Elementy diagonalne macierzy U:" << endl;
  for (int i = 1; i <= N; i++) 
    file << U_A[i][i] << "\t";
  file << endl << endl;

  file << "Wyznacznik macierzy A: " << wyznacznikA << endl;

  /* 3. Znaleźć macierz odwrotną A −1 rozwiązując n układów równań z wektorami wyrazów wolnych */
  std::vector<float *> tab_wektorow;
  
  for (int i = 0; i < N; i++) 
    tab_wektorow.emplace_back(vector(1,N)); //tricky ale działa perfekcyjnie
  zainicjalizuj_wektory(tab_wektorow);

  for (int i = 1; i<=N; i++) {
    cout << "Wektor b" << i << endl;
    wypisz_wektor(tab_wektorow[i-1]);
  }

  float **A_inv = matrix(1,N,1,N);
  wyzeruj_macierz(&A_inv);
  macierz_odwrotna(A, v_A, tab_wektorow, &A_inv);
  cout << "Macierz odwrotna do macierzy A:" << endl;
  wypisz_macierz(A_inv); 

  inicjalizuj_macierz(&A);
  float **iloczyn_A = matrix(1, N, 1, N);
  iloczyn_macierzy(A, A_inv, &iloczyn_A);
  cout << "Iloczyn macierzy A*A^-1:" << endl;
  wypisz_macierz(iloczyn_A);

  float wskaznik_uwar_A = matrix_max(A) * matrix_max(A_inv);
  cout << "Wskaznik uwarunkowania macierzy A wynosi: " << wskaznik_uwar_A << endl << endl;
  file << "Wskaznik uwarunkowania macierzy A wynosi: " << wskaznik_uwar_A << endl;
  file.close();
  return 0;
}