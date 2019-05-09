set terminal png

set output "Zad1.png"
set grid
set xlabel "x"
set ylabel "f(x)"
set title "Aproksymacja funkcji f_1(x), parametr alfa=0"  
plot "Zad1.dat" u 1:2 w p t "f_1(x)",\
	"Zad1.dat" u 1:3 w l t "F_1(x), M_s=M_c=5"

set output "Zad2.png"
set grid
set xlabel "x"
set ylabel "f(x)"
set title "Aproksymacja funkcji f_2(x)"  
plot "Zad2.dat" u 1:2 w p t "f_2(x)",\
	"Zad2.dat" u 1:3 w l t "F_2(x), M_s=M_c=5"

set output "Zad3.png"
set grid
set xlabel "x"
set ylabel "f(x)"
set title "Aproksymacja funkcji f_3(x)"  
plot "Zad3a.dat" u 1:2 w p t "f_3(x)",\
	"Zad3a.dat" u 1:2 w l t "F_3(x), M_s=M_c=0",\
    "Zad3b.dat" u 1:2 w l t "F_3(x), M_s=M_c=5",\
    "Zad3c.dat" u 1:2 w l t "F_3(x), M_s=M_c=10"

set output "Zad4a.png"
set grid
set xlabel "x"
set ylabel "f(x)"
set title "Wyniki aproksymacji"  
plot "Zad4a.dat" u 1:2 w p t "f_1(x), alpha losowe",\
    "Zad4a.dat" u 1:3 w l t "F_4(x), M_s=M_c=5",\
    "Zad4b.dat" u 1:3 w l t "F_4(x), M_s=M_c=30",\

set output "Zad4b.png"
set grid
set xlabel "index i"
set ylabel "a_i, b_i"
set title "Wspolczynniki a_i oraz b_i dla M_s=M_c=5"  
plot "Zad4WspolczSin_Ms_5.dat" u 1:2 w l t "a_i, M_s=M_c=5",\
    "Zad4WspolczCos_Mc_5.dat" u 1:2 w l t "b_i, M_s=M_c=5",\

set output "Zad4c.png"
set grid
set xlabel "index i"
set ylabel "a_i, b_i"
set title "Wspolczynniki a_i oraz b_i dla M_s=M_c=30"  
plot "Zad4WspolczSin_Ms_30.dat" u 1:2 w l t "a_i, M_s=M_c=30",\
    "Zad4WspolczCos_Mc_30.dat" u 1:2 w l t "b_i, M_s=M_c=30",\
