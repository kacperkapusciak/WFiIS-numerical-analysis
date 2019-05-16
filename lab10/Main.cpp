#include <math.h>
#include <fstream>

int licznik_zad = 1;

double fun1(double x) {
    return log(pow(x,5) + 3*x*x + x + 9);
}

double fun2(double x) {
    return pow(x,6);
}

void zloty_podzial(double x_a, double x_b, double x_dokl, double (*fun)(double)) {
    std::ofstream file;
    file.open("zad" + std::to_string(licznik_zad) + ".dat");
    licznik_zad++;

    int it = 0;
    double r = (sqrt(5) - 1) / 2;
    double x_min;
    double x_1 = x_a + (r*r) * (x_b - x_a);
    double x_2 = x_a + r * (x_b - x_a);

    while(fabs(x_1 - x_2) > 1e-6) {
        x_1 = x_a + (r*r) * (x_b - x_a);
        x_2 = x_a + r * (x_b - x_a);

        if (fun(x_1) > fun(x_2)) 
            x_a = x_1;
        else 
            x_b = x_2;

        x_min = (x_1 + x_2 ) / 2.0;
        file << it << "\t" << x_min << "\t" << fabs(x_min - x_dokl)<< "\n";
        it++;
    }
    file.close();
}

void rowne_odcinki(double x_a, double x_b, double x_dokl, double (*fun)(double)) {
    std::ofstream file;
    file.open("zad" + std::to_string(licznik_zad) + ".dat");
    licznik_zad++;

    int it = 0;
    double r = (sqrt(5) - 1) / 2;
    double x_min;

    double x_1 = x_a + (1./3.) * (x_b - x_a);
    double x_2 = x_a + (2./3.) * (x_b - x_a);

    while(fabs(x_1 - x_2) > 1e-6) {
        x_1 = x_a + (1./3.) * (x_b - x_a);
        x_2 = x_a + (2./3.) * (x_b - x_a);

        if (fun(x_1) > fun(x_2)) 
            x_a = x_1;
        else 
            x_b = x_2;

        x_min = (x_1 + x_2 ) / 2.0;
        file << it << "\t" << x_min << "\t" << fabs(x_min - x_dokl)<< "\n";
        it++;
    }

    file.close();
}

int main() {
    double x_a = -0.5, x_b = 1.0, x_dokl =-0.1673198;

    zloty_podzial(x_a, x_b, x_dokl, fun1);
    rowne_odcinki(x_a, x_b, x_dokl, fun1);

    x_a = -4.0, x_b = 1.0, x_dokl = 0;

    zloty_podzial(x_a, x_b, x_dokl, fun2);
    rowne_odcinki(x_a, x_b, x_dokl, fun2);

    return 0;
}