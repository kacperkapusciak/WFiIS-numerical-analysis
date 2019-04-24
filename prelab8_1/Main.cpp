#include "../dependencies/deps.h"
#include <functional>

float policz_pierwsza_pochodna(float x, std::function<float(float)> fun) {
  float deltaX = 0.01;
  return ( (fun(x + deltaX) - fun(x - deltaX)) / (2 * deltaX) );
}

void zainicjalizuj_macierz(float **A, int liczba_wezlow) {
	for(int i = 1; i <= liczba_wezlow; i++) {
		for(int j = 1; j <= liczba_wezlow; j++) {
			if(i == j) {
				A[i][j] = 4;
				if(i > 1 && i < liczba_wezlow) {
					A[i][i + 1] = 1;
					A[i][i - 1] = 1;
				}
			} else {
        A[i][j] = 0;
      }
		}
	}
	A[1][2] = 2;
	A[liczba_wezlow][liczba_wezlow - 1] = 2;
}

void polozenie_wezlow_i_wartosci(float * wezly, float * wartosci, std::function<float(float)> fun, const int liczba_wezlow) {
  double xx[liczba_wezlow+6];

}

void interpolacja_w_bazie(std::function<float(float)> fun, const int liczba_wezlow) {
  float ** A = matrix(1, liczba_wezlow, 1, liczba_wezlow);
	float ** wektor = matrix(1, liczba_wezlow, 1, 1);
	float * wezly = vector(1, liczba_wezlow + 2); 
	float * wartosci = vector(1, liczba_wezlow);
}

int main()
{
  std::function<float(float)> fun1 = [](float x){ return 1.0 / (1.0 + pow(x, 2)); };
  std::function<float(float)> fun2 = [](float x){ return cos(2 * x); };
  int fun1_nodes[] = {5, 6, 10, 20};
  int fun2_nodes[] = {6, 7, 14};

  for (auto wezly: fun1_nodes) {
    interpolacja_w_bazie(fun1, wezly);
  }

  for (auto wezly: fun2_nodes) {
    interpolacja_w_bazie(fun2, wezly);
  }

  return 0;
}

