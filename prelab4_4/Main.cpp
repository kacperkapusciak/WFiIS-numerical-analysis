//g++ Main.cpp -L/home/kiper/gsl/lib -I/home/kiper/gsl/include -lgsl -lgslcblas -lm
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_linalg.h"
#include "gsl/gsl_complex.h"
#include "gsl/gsl_complex_math.h"
#include "gsl/gsl_eigen.h"
#include <math.h>
#include <fstream>


const double L = 20.0;
const int n = 200;
const double N = 1.0;
const double delta_x = L / (n + 1);

void zainicjalizuj_macierz(gsl_matrix **A, int alfa) {
  double x_i;
  auto deltaKr = [](int i, int j) { return i == j; };
  auto ro = [](double alfa, double x) { return 1 + 4 * alfa * x * x; };

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      x_i = -L / 2.0 + delta_x * (i + 1);
      gsl_matrix_set(*A, i, j, 
          ( -deltaKr(i, j + 1) + 2 * deltaKr(i, j) - deltaKr(i, j - 1) * N) / ( ro(alfa, x_i) * pow(delta_x, 2) ));
    }
}

void wpisz_do_pliku(gsl_matrix_complex **evec, std::ofstream *file) {
  double x_i;
  for ( int i = 0; i < n; i++ ) {
		x_i = -L / 2.0 + delta_x * (i + 1);

    *file << x_i << "\t";
		for ( int k = 0; k < 6; k++ ) 
			*file << GSL_REAL( gsl_matrix_complex_get( *evec, i, k) ) << "\t";
		*file << std::endl;
	}
}

int main() {
  //otwarcie plików
  std::ofstream out;
  out.open("out.dat");
  std::ofstream wektory_alfa_0;
  wektory_alfa_0.open("wektory_alfa_0.dat");
  std::ofstream wektory_alfa_100;
  wektory_alfa_100.open("wektory_alfa_100.dat");

  //alokacja macierzy
  gsl_matrix *A = gsl_matrix_calloc( n, n );
  gsl_vector_complex *eval= gsl_vector_complex_calloc( n );
	gsl_matrix_complex *evec= gsl_matrix_complex_calloc( n, n );
	gsl_eigen_nonsymmv_workspace *w = gsl_eigen_nonsymmv_alloc( n );

  for ( int alfa = 0; alfa <= 100; alfa += 2 ) {
    zainicjalizuj_macierz( &A, alfa );

    //rozwiazanie problemu wlasnego
    gsl_eigen_nonsymmv( A, eval, evec, w );
    //sortowanie wartości i wektorów własnych
    gsl_eigen_nonsymmv_sort( eval, evec, GSL_EIGEN_SORT_ABS_ASC );

    //zapisanie do pliku wartości pierwiastków 6 kolejnych najmniejszych wartości własnych
    out << alfa << "\t";
		for ( int k = 0; k < 6; k++ ) 
			out << sqrt( GSL_REAL( gsl_vector_complex_get(eval, k) ) ) << "\t";
		out << std::endl;

    // a == 0 oraz a = 100 zapisać do pliku wektory własne odpowiadające 6 najniższym wartościom własnym
    if (alfa == 0)
      wpisz_do_pliku(&evec, &wektory_alfa_0);
    else if (alfa == 100)
      wpisz_do_pliku(&evec, &wektory_alfa_100);

    }


  //zwolnienie pamięci
  gsl_matrix_free(A);
  gsl_vector_complex_free(eval);
  gsl_matrix_complex_free(evec);
  gsl_eigen_nonsymmv_free(w);

  //zamkniecie plików
  out.close();
  wektory_alfa_0.close();
  wektory_alfa_100.close();

  return 0;
}
