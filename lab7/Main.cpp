#include "math.h"
#include <fstream>
#include <iostream>

const int N = 6;

double funkcja(double x) {	
	return (1.0 / (1.0 + pow(x, 2)));
}

void iloraz_roznicowy(double wezly[N+1], double wartosci_funkcji[N+1], double iloraz_roznicowy_tab[N+1]) {
    double wynik;
    double mianownik;
    for(int j = 0; j <= N; j++) {
	    wynik = 0;
        for (int k = 0; k <= j; k++) {
            mianownik = 1.0;
            for (int l = 0; l <= j; l++) 
                if (l != k) 
                    mianownik *= wezly[k] - wezly[l];
            
            wynik += wartosci_funkcji[k] / mianownik;
        }
        iloraz_roznicowy_tab[j] = wynik;
    }
}

double wielomian_interpolacyjny(double wezly[N+1], double wartosci_funkcji[N+1], double x, double iloraz_roznicowy_tab[N+1]) {
    double wynik;
    double suma = 0.0;
    for (int j = 0; j <= N; j++) {
        wynik = 1.0;
        for (int i = 0; i <= j-1; i++) 
           wynik *= x - wezly[i]; 

        suma += iloraz_roznicowy_tab[j] * wynik;
   } 
   return suma;
}

int main() {
    double wezly[N+1] = {-5, -2, -0.5, 0, 0.5, 2, 5};
    // double wezly[N+1];
    double wartosci_funkcji[N+1];
    double iloraz_roznicowy_tab[N+1];

    std::ofstream file, file2, file3;
    file.open("out1.dat");
    file2.open("out2.dat");
    file3.open("rownolegle_nierownolegle.dat");

    // wezly[0] = -5;
    // wezly[7] = 5;

    for (int i = 0; i < N+1; i++) 
        wartosci_funkcji[i] = funkcja(wezly[i]);
    

    iloraz_roznicowy(wezly, wartosci_funkcji, iloraz_roznicowy_tab);

	for(int i = 0; i <= N; i++)
		file3 << iloraz_roznicowy_tab[i] << std::endl;

    for (double x = -5; x <= 5; x += 0.01 ) {
        file << x << "\t" << funkcja(x) << wielomian_interpolacyjny(wezly, wartosci_funkcji, x, iloraz_roznicowy_tab) << std::endl;
    }

    double krok = 10.0 / (double)N ;
    for (int i = 0;  i < N; i++) 
        wezly[i] = -5 + krok * i;
	

    for (int i = 0; i <= N; i++)
		wartosci_funkcji[i] = funkcja(wezly[i]);

	iloraz_roznicowy(wezly, wartosci_funkcji, iloraz_roznicowy_tab);

    for (double x = -5.0; x <= 5; x += 0.01 ) 
        file2 << x << "\t" << funkcja(x) << "\t" << wielomian_interpolacyjny(wezly, wartosci_funkcji, x, iloraz_roznicowy_tab) << std::endl;
    
    file3 << std::endl;
	for(int i = 0; i <= N; i++)
		file3 << iloraz_roznicowy_tab[i] << std::endl;
	

    file.close();
    file2.close();
    file3.close();

    return 0;
}