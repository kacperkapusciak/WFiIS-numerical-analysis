#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "math.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

//zmienne globalne z pełną premedytacją :)
const double V0 = 0;
const double x0 = 1;
const double w = 1;
const int n = 2000;
const double h = 0.02;

void metoda_Jakobiego(double, double, double, int *);

int main() {
  double B, F0, Omega;
  int nr_przykladu = 1;

  B = 0.0; F0 = 0.0; Omega = 0.8;
  metoda_Jakobiego(B, F0, Omega, &nr_przykladu);

  B = 0.4; F0 = 0.0; Omega = 0.8;
  metoda_Jakobiego(B, F0, Omega, &nr_przykladu);

  B = 0.4; F0 = 0.1; Omega = 0.8;
  metoda_Jakobiego(B, F0, Omega, &nr_przykladu);

  return 0;
}

void metoda_Jakobiego(double B, double F0, double Omega, int *nr_przykladu) {
  cout << "\n\nPrzyklad " << *nr_przykladu <<": " << endl;
  cout << "B = " << B << ", F0 = " << F0 << ", Omega = " << Omega << endl;

  double a1 = 1;
	double a2 = w*w * h*h - 2 - B * h;
	double a3 = 1 + B * h;

	double * d0 = dvector(0, n+1);
	double * d1 = dvector(0, n+1);
	double * d2 = dvector(0, n+1);
	double * b  = dvector(0, n+1);

  //inicjalizacja wektorow
  for(int i = 0; i <= n; i++) {
    d0[i] = a3;
    d1[i] = a2;
    d2[i] = a1;
    b[i]  = F0 * sin(Omega * h * i) * h*h; 
  }

  d0[0] = 1;    d1[0] =  0;    d2[0] = 0;    b[0] = 1;
	d0[1] = 1;    d1[1] = -1;    d2[0] = 0;    b[1] = 0;

  //wypisz pierwsze 5 elementow wektorow
  cout << "\nWypisanie pierwszych 5 elementow wektorow" << endl;
  cout << "\nd0\t\td1\t\td2\t\tb\t\t" << endl;
  for (int i = 0; i < 5; i++) 
    cout << d0[i] << "\t\t" << d1[i] << "\t\t" 
         << d2[i] << "\t\t" << b[i]  << "\t\t" << endl;
  
  double *xn = dvector(0, n+1);
  double *xs = dvector(-2, n+1);
  int it = 0;



  while (it < 10000)
  {
    it++;
    //i-ty element nowego przyblizenia dysponując przybliżeniem poprzedniej iteracji
		for( int i = 0; i <= n; i++) {
			xn[i] = 1/d0[i] * (b[i] - d1[i] * xs[i-1] - d2[i] * xs[i-2]);
    }

    double sum_xn_sq = 0;
    double sum_xs_sq = 0;
    //liczenie sumy kwadratow elementow
    for ( int i = 0; i <= n; i++) {
      sum_xn_sq += pow(xn[i], 2);
      sum_xs_sq += pow(xs[i], 2);
    }
    
    //warunek zakonczenia petli
    if(fabs(sum_xn_sq - sum_xs_sq) < pow(10,-6)) 
      break;

    //przepisanie wektora xn do wektora xs
		for( int i = 0; i <= n; i++)
			xs[i] = xn[i];
  }

  cout << "Liczba iteracji: " << it << endl;

  std::ofstream file;
  std::string nazwa_pliku = "Przyklad" + std::to_string(*nr_przykladu) + ".txt";
  file.open(nazwa_pliku);

  double start = 0.0;
	for(int i = 1; i <= n; i++) {
		file << start << "\t" << xn[i] << endl;
		start += h;
	}

  file.close();

  free_dvector(d0, 0, n);
	free_dvector(d1, 0, n);
	free_dvector(d2, 0, n);
	free_dvector(b,  0, n);
  free_dvector(xn, 0, n);
  free_dvector(xs, -2, n);
  (*nr_przykladu)++;
}

