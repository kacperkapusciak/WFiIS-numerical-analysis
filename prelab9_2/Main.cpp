#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>

double fun1(const double x) {
	return 2 * sin(x) + sin(2 * x) + 2 * sin(3 * x);
}

double fun1Alpha(const double x) {
	const double alpha = rand()/(RAND_MAX + 1.0) - 0.5;
	return 2 * sin(x) + sin(2 * x) + 2 * sin(3 * x) + alpha;
}

double fun2(const double x) {
	return 2 * sin(x) + sin(2 * x) + 2 * cos(x) + cos(2 * x);
}

double fun3(const double x) {
	return 2 * sin(1.1 * x) + sin(2.1 * x) + 2 * sin(3.1 * x);
}

double obliczWspolczynnik(double (*fun)(double), double (*tryg)(double), double j, int N, double xMin, double krok, double L)
{
	double wspolczynnik = 0;
	double x = 0;

	for(int i = 0; i < N; ++i) {
		x = xMin + krok * i;
		wspolczynnik += fun(x) * tryg(x * j);
	}

	return wspolczynnik / L;
}

void aproksymacja(double (*fun)(double), std::string nazwa_pliku, double Ms, double Mc)
{
	double xMin = 0;
	double xMax = 2 * M_PI;
	int N = 100;
	int L = N / 2;
	double krok = (xMax - xMin) / N;


	double wspolczynnik_A0 = 0;
	double wspolczynnik_sin = 0;
	double wspolczynnik_cos = 0;

	wspolczynnik_A0 = obliczWspolczynnik(fun, cos, 0, N, xMin, krok, L);

  std::ofstream file;
  file.open(nazwa_pliku);

	for(double x = xMin; x < xMax; x += 0.01) {
		wspolczynnik_cos = 0;
		wspolczynnik_sin = 0;

		for(int i = 1; i <= Mc; i++)
			wspolczynnik_cos += obliczWspolczynnik(fun, cos, i, N, xMin, krok, L) * cos(i * x);
		

		for(int i = 1; i <= Ms; i++)
			wspolczynnik_sin += obliczWspolczynnik(fun, sin, i, N, xMin, krok, L) * sin(i * x);
		
    file << x << "\t" << wspolczynnik_A0 + wspolczynnik_cos + wspolczynnik_sin << "\t" << fun(x) << std::endl;
	}

	file.close();
}

void aproksymacjaAlpha(double (*fun)(double), std::string nazwa_pliku, double Ms, double Mc)
{
	double xMin = 0;
	double xMax = 2 * M_PI;
	int N = 100;
	int L = N / 2;
	double krok = (xMax - xMin) / N;


	double wspolczynnik_A0 = 0;
	double wspolczynnik_sin = 0;
	double wspolczynnik_cos = 0;

	wspolczynnik_A0 = obliczWspolczynnik(fun, cos, 0, N, xMin, krok, L);

  std::ofstream file;
  file.open(nazwa_pliku);

	for(double x = xMin; x < xMax; x += 0.01) {
		wspolczynnik_cos = 0;
		wspolczynnik_sin = 0;

		for(int i = 1; i <= Mc; i++)
			wspolczynnik_cos += obliczWspolczynnik(fun, cos, i, N, xMin, krok, L) * cos(i * x);
		

		for(int i = 1; i <= Ms; i++)
			wspolczynnik_sin += obliczWspolczynnik(fun, sin, i, N, xMin, krok, L) * sin(i * x);
		
    file << x << "\t" << wspolczynnik_A0 + wspolczynnik_cos + wspolczynnik_sin << "\t" << fun(x) << std::endl;
	}

	file.close();

  std::string nazwaPlikuWspolCos = "Zad4WspolczCos_Mc_" + std::to_string(int(Ms)) + ".txt";
	std::string nazwaPlikuWspolSin = "Zad4WspolczSin_Ms_" + std::to_string(int(Ms)) + ".txt";

  std::fstream plikWspolCos, plikWspolSin;
  plikWspolCos.open(nazwaPlikuWspolCos);
  plikWspolSin.open(nazwaPlikuWspolSin);

	for(int i = 1; i <= Mc; i++)
    plikWspolCos << i << "\t" << obliczWspolczynnik(fun, cos, i, N, xMin, krok, L) << std::endl;


	for(int i = 1; i <= Ms; ++i)
    plikWspolSin << i << "\t" << obliczWspolczynnik(fun, sin, i, N, xMin, krok, L) << std::endl;
	
  plikWspolCos.close();
  plikWspolSin.close();
}


int main() {
  srand(time(0));

	aproksymacja(fun1, "Zad1.dat", 5.0, 5.0);
	aproksymacja(fun2, "Zad2.dat", 5.0, 5.0);
	aproksymacja(fun3, "Zad3a.dat", 5.0, 0.0);
	aproksymacja(fun3, "Zad3b.dat", 5.0, 5.0);
	aproksymacja(fun3, "Zad3c.dat", 10.0, 10.0);

	aproksymacjaAlpha(fun1Alpha, "Zad4a.txt", 5.0, 5.0);
	aproksymacjaAlpha(fun1Alpha, "Zad4b.txt", 30.0, 30.0);
  return 0;
}