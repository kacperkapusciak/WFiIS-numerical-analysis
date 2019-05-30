#include <iostream>
#include <fstream>
#include <ctime>

#include <iostream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_fft_complex.h>
#include <gsl/gsl_errno.h>
#include <math.h>
#include <fstream>



double sygnal_niezaszumiony(double omega, int i) {
    return sin(omega * i) + sin(2 * omega * i) + sin(3 * omega * i);
}

double Delta() {
    return 2 * (rand()/(RAND_MAX + 1.0) ) - 1;
}

double modul(double a, double b) {
    return sqrt(a * a + b * b);
}

void aproksymacja_FFT(int k) {
    const int N = pow(2, k);
    const double omega = 2 * (2* M_PI)/(N);
    double dane[2 * N];
    double niezaszumione[2 * N];
    double zaszumione[2 * N];
    std::ofstream file;
    std::ofstream file2;
    if (k == 8 ) {
        file.open("out1.dat");
        file2.open("out2.dat");
    }


    for (int i = 0; i < N; i++) {
        dane[2 * i] = zaszumione[2*i] =  sygnal_niezaszumiony(omega, i) + Delta();
        niezaszumione[2 * i] = sygnal_niezaszumiony(omega, i);
        dane[2 * i + 1] = niezaszumione[2 * i + 1] = zaszumione[2 * i + 1] = 0;
    }
    gsl_fft_complex_radix2_forward(dane, 1, N);
    if (k == 8) 
        for (int i = 0; i < N; i++)
            file << i << "\t" << dane[2 * i] << "\t" << dane[2 * i + 1] << std::endl;
    

    double max = modul(dane[0], dane[1]);
        for (int i = 1; i < N; i++)
            if (max < modul(dane[2*i], dane[2*i+1]))
                max = modul(dane[2*i], dane[2*i+1]);

    max /= 2;

    if (k == 8)
        for (int i = 0; i < N; i++)
            file2 << i << "\t" << modul(dane[2*i], dane[2*i+1]) << "\t" << max << std::endl;

    for(int i = 0; i < N; i++) 
        if(modul(dane[2 * i], dane[2*i + 1]) < max) {
            dane[2 * i] = 0;
            dane[2 * i + 1] = 0;
        }
    
    gsl_fft_complex_radix2_backward(dane, 1, N);

    for(int i = 0; i < N; i++) {
        dane[2 * i] /= N;
        dane[2 * i + 1] /= N;
    }

    std::ofstream file3("out_dla_k=" + std::to_string(k) + ".dat");
    for (int i = 0; i < N; i++) {
        file3 << i << "\t" << zaszumione[2*i] << "\t" << niezaszumione[2 * i] << "\t" << dane[2 * i] << std::endl;
    }
    if (k == 8) {
        file.close();
        file2.close();
    }
    file3.close();
}


int main() {
    srand(time(NULL));

    aproksymacja_FFT(8);
    aproksymacja_FFT(10);
    aproksymacja_FFT(12);



    return 0;
}