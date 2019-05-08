set terminal png

set output "Zad1.png"
set grid
set xrange [-5:5]
set xlabel "x"
set ylabel "y"
set title "Aproksymacja Padégo funkcji cos(x) M = N = 2"  
plot "Zad1.txt" u 1:2 w l t "cos(x)",\
	"Zad1.txt" u 1:3 w l t "R_2_,_2(x)"

set output "Zad2.png"
set grid
set xrange [-5:5]
set xlabel "x"
set ylabel "y"
set title "Aproksymacja Padégo funkcji cos(x) M = N = 4"  
plot "Zad2.txt" u 1:2 w l t "cos(x)",\
	"Zad2.txt" u 1:3 w l t "R_4_,_4(x)"

set output "Zad3.png"
set grid
set xrange [-5:5]
set xlabel "x"
set ylabel "y"
set title "Aproksymacja Padégo funkcji cos(x) M = N = 6"  
plot "Zad3.txt" u 1:2 w l t "cos(x)",\
	"Zad3.txt" u 1:3 w l t "R_6_,_6(x)"
