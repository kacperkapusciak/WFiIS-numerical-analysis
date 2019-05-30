set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
 
set term png
 
set grid
set xlabel "i"
set ylabel "FFT[y(i)]"

set style line 1  lc rgb 'black' lt 1 lw 2 
set style line 2  lc rgb 'red' lt 1 lw 2 

set out "test.png"
set title "Czesc rzeczywista Re(FFT[y(i)]) i urojona Im(FFT[y(i)])"
plot "out1.dat" using 1:2 w l ls 1 title "Re(FFT[y(i)]", \
    "out1.dat" using 1:3 w l ls 2 title "Im(FFT[y(i)]", \
 
set out "modul.png"
set title "Modul |Re(FFT[y(i)]) + i \cdot Im(FFT[y(i)])|"
plot "out2.dat" using 1:2 w l ls 1 title "FFT[y(i)]", \
    "out2.dat" using 1:3 w l ls 2 title "Prog dyskryminacji" ,\

set style line 1  lc rgb 'grey' lt 1 lw 2 
set style line 2  lc rgb 'black' lt 1 lw 2 
set style line 3  lc rgb 'red' lt 1 lw 2 

set ylabel "y(i)"
set out "k=8.png"
set title "k=8 => N_k=2^8 probek wejsciowych"
plot "out_dla_k=8.dat" using 1:2 w l ls 1 title "y(i)=y_0(i)+delta", \
    "out_dla_k=8.dat" using 1:3 w l ls 2 title "y_0(i)" ,\
    "out_dla_k=8.dat" using 1:4 w l ls 3title "y(i) po odszumieniu" ,\

set out "k=10.png"
set title "k=10 => N_k=2^10 probek wejsciowych"
plot "out_dla_k=10.dat" using 1:2 w l ls 1 title "y(i)=y_0(i)+delta", \
    "out_dla_k=10.dat" using 1:3 w l ls 2 title "y_0(i)" ,\
    "out_dla_k=10.dat" using 1:4 w l ls 3 title "y(i) po odszumieniu" ,\

set out "k=12.png"
set title "k=12 => N_k=2^12 probek wejsciowych"
plot "out_dla_k=12.dat" using 1:2 w l ls 1 title "y(i)=y_0(i)+delta", \
    "out_dla_k=12.dat" using 1:3 w l ls 2 title "y_0(i)" ,\
    "out_dla_k=12.dat" using 1:4 w l ls 3 title "y(i) po odszumieniu" ,\