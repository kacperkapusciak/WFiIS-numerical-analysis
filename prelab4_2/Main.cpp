#include "../deps/deps.h"

const int nx = 20;
const int ny = 20;
const int n = nx * ny;
const int m = 10;
const double t = -0.021;

void zainicjalizuj_macierz(float ***H) {
  int l;
  for (int i = 1; i <= nx; i++) 
    for (int j = 1; j <= ny; j++) {
      l = j + (i - 1) * ny;
      for (int k = 1; k <= n; k++)
        (*H)[l][k] = 0.;
      if (i > 1)
        (*H)[l][l - ny] = t; //dla i=1 nie ma sasiada z lewej strony
      if (i < nx)
        (*H)[l][l + ny] = t; //dla i=nx nie ma sasiada z prawej strony
      (*H)[l][l] = -4 * t;
      if (j > 1)
        (*H)[l][l - 1] = t; //dla j=1 nie ma sasiada ponizej siatki
      if (j < ny)
        (*H)[l][l + 1] = t; //dla j=ny nie ma sasiada powyzej siatki
  }
}

void inicjalizuj_macierz_jednostkowa(float ***I) {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) 
      (*I)[i][j] = i == j;
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

void wpisz_do_pliku(float **X, int *index, std::ofstream *file) {
  int l;
  for (int i = 1; i <= nx; i++) {
    for (int j = 1; j <= ny; j++) {
      l = j + (i - 1) * ny;
      *file << i << "\t" << j << "\t";
      for (int k = 1; k <= m; k++)
        *file << X[l][index[k]] << "\t";
      *file << std::endl;
    }
    *file << std::endl;
  }
}

void sortowanie_energii(float **d, int **index) {
  float e1, e2, l1, l2;
  for (int l = 1; l <= n; l++)
    (*index)[l] = l; // inicjalizacja
  for (int l = 1; l <= n - 1; l++) 
    for (int k = n; k >= l + 1; k--) {
      e1 = (*d)[k - 1];
      e2 = (*d)[k];
      l1 = (*index)[k - 1];
      l2 = (*index)[k];
      //wymieniamy energie i indeksy wektorów miejscami
      if (e2 < e1) { 
        (*d)[k] = e1;
        (*d)[k - 1] = e2;
        (*index)[k] = l1;
        (*index)[k - 1] = l2;
      }
    }

}

int main() {
  //alokacja macierzy i wektorów
  float **H = matrix(1, n, 1, n);
  float **Y = matrix(1, n, 1, n);
  float **X = matrix(1, n, 1, n);
  float *d = vector(1, n);
  float *e = vector(1, n);
  int *index = ivector(1, n);

  zainicjalizuj_macierz(&H);
  tred2(H, n, d, e);

  inicjalizuj_macierz_jednostkowa(&Y);
  tqli(d, e, n, Y);

  iloczyn_macierzy(H, Y, &X);

  std::ofstream file;
  file.open("out.dat");

  sortowanie_energii(&d, &index);
  wpisz_do_pliku(X, index, &file);

  file.close();

  //zwalnianie pamięci
  free_vector(e, 1, n);
  free_vector(d, 1, n);
  free_ivector(index, 1, n);
  free_matrix(H, 1, n, 1, n);
  free_matrix(Y, 1, n, 1, n);
  free_matrix(X, 1, n, 1, n);
  return 0;
}