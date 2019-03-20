#include "../deps/deps.h"

const int n = 5;

void zainicjalizuj_macierz(float ***A) {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      (*A)[i][j] = sqrt(i + j);
}

void wypisz_macierz(float **A) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      cout << A[i][j] << "\t";
    cout << endl;
  }
  cout << endl;
}

void wpisz_do_pliku(float **A, std::ofstream *file) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      *file << A[i][j] << "\t\t";
    *file << endl;
  }
  *file << endl; 
}

void inicjalizuj_macierz_jednostkowa(float ***I) {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) 
      i == j ? (*I)[i][j] = 1 : (*I)[i][j] = 0;
}

void iloczyn_macierzy(float **A, float **B, float ***wynik) {
  float suma;
  for (int i = 1; i <= n; i++) 
    for (int j = 1; j <= n; j++) {
      suma = 0;
      for (int k = 1; k <= n; k++)
        suma += A[i][k] * B[k][j];
      (*wynik)[i][j] = suma;
    }       
}

double iloczyn_skalarny(float *v1, float *v2) {
  double suma = 0;
  for (int i = 1; i <= n; i++)
    suma += v1[i] * v2[i];
  return suma;
}

void iloczyn_macierz_wektor(float **A, float *wektor, float **wynik) {
  double suma;
  for (int i = 1; i <= n; i++) {
    suma = 0;
    for (int j = 1; j <= n; j++)
      suma += A[i][j] * wektor[j];
    (*wynik)[i] = suma;
  }
}

void wybierz_wektor(float **X, float **wektor_z_kolumny, int nr_kolumny) {
  for (int i = 1; i <= n; i++) {
    (*wektor_z_kolumny)[i] = X[i][nr_kolumny];
  }
}

int main() {
  //inicjalizacja macierzy A
  float **A = matrix(1, n, 1, n);
  zainicjalizuj_macierz(&A);

  wypisz_macierz(A);

  //wektry d oraz e
  float *d, *e;
  d = vector(1, n);
  e = vector(1, n);

  tred2(A, n, d, e);

  wypisz_macierz(A);
  //dopisz do pliku
  // std::ofstream file;
  // file.open("out.dat");
  // file << "Macierz przekształcenia P:" << endl;
  // wpisz_do_pliku(A, &file);


  //macierz Y wektorów własnych macierzy T
  float **Y = matrix(1, n, 1, n);
  inicjalizuj_macierz_jednostkowa(&Y);
  tqli(d, e, n, Y);

  //odtwarzamy wektory własne macierzy A
  float **X = matrix(1, n, 1, n);
  iloczyn_macierzy(A, Y, &X);

  cout << "Wektory własne macierzy A:" << endl;
  wypisz_macierz(X);

  // file << "Wektory własne macierzy A:" << endl;
  // wpisz_do_pliku(X, &file);

  cout << "Wartości własne macierzy A" << endl;
  for (int i = 1; i <= n; i++)
    cout << d[i] << "\t";
  cout << endl;
  
  //przywrócenie macierzy A
  zainicjalizuj_macierz(&A);

  float *iloczyn_A_x = vector(1, n);
  float *B = vector(1, n);
  float *wektor_z_kolumny = vector(1, n);

  for (int i = 1; i <= n; i++) {
    wybierz_wektor(X, &wektor_z_kolumny, i);
    iloczyn_macierz_wektor(A, wektor_z_kolumny, &iloczyn_A_x);

    B[i] = iloczyn_skalarny(wektor_z_kolumny, iloczyn_A_x) / iloczyn_skalarny(wektor_z_kolumny, wektor_z_kolumny);
  }
  

  cout << endl << "Wartości tego B" << endl;
  for (int i = 1; i <= n; i++)
    cout << B[i] << "\t";
  cout << endl;


  //zwalnianie pamieci
  // file.close();
  free_vector(e, 1, n);
  free_vector(d, 1, n);
  free_matrix(A, 1, n, 1, n);
  free_matrix(Y, 1, n, 1, n);
  free_matrix(X, 1, n, 1, n);
  return 0;
}