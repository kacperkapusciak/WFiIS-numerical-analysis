#include "../deps/nrutil.h"
#include "../deps/nrutil.cpp"
#include "math.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

//zmienne globalne z pełną premedytacją :)
const double V0 = 0;
const double x0 = 1;
const double w = 1;
const int n = 1000;
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

	double * d0 = dvector(0, n);
	double * d1 = dvector(0, n);
	double * d2 = dvector(0, n);
	double * b  = dvector(0, n);

  //inicjalizacja wektorow
  for(int i = 0; i < n; i++) {
    d0[i] = a3;
    d1[i] = a2;
    d2[i] = a1;
    b[i]  = F0 * sin(Omega * h * i) * h*h; 
  }

  d0[0] = 1;    d1[0] =  0;    d2[0] = 0;    b[0] = 1;
	d0[1] = 1;    d1[1] = -1;    d2[0] = 0;    b[1] = 0;

  //wypisz pierwsze 5 elementow wektorow
  cout << "\nd0\t\td1\t\td2\t\tb\t\t" << endl;
  for (int i = 0; i < 5; i++) 
    cout << d0[i] << "\t\t" << d1[i] << "\t\t" 
         << d2[i] << "\t\t" << b[i]  << "\t\t" << endl;
  
  double *xn = dvector(0, n);
  double *xs = dvector(-2, n);

  for(int licznik = 1; licznik < 3000; licznik++)
	{
		for(int i = 0; i < n; ++i) 
			xn[i] = 1/d0[i] * (b[i] - d1[i] * xs[i-1] - d2[i] * xs[i-2]);

		for(int i = 0; i <n; ++i)
			xs[i] = xn[i];
  }

  std::ofstream file;
  std::string nazwa_pliku = "Przyklad" + std::to_string(*nr_przykladu) + ".txt";
  file.open(nazwa_pliku);

  double start = 0.0;
	for(int i = 1; i < n; i++) {
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

