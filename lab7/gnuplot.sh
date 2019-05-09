set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "x_t.eps" # nazwa pliku wynikowego
# set title "Wychylenie x(t)" # tytul wykresu
set xlabel "x" # etykieta osi OX
set ylabel "f(x)" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej
plot "out1.dat" u 1:2 w l t "f(x)", "out1.dat" u 1:3 w l t "W(x)"
# plot "out2.dat" w p t "x(t), dt = 0.01"
plot "out2.dat" u 1:2 w l t "f(x)", "out2.dat" u 1:3 w l t "W(x)"
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"
