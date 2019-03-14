set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "Przyklad1.eps" # nazwa pliku wynikowego
set title "Wychylenie x(t) dla parametrow B = 0, F0 = 0, Omega = 0.8" # tytul wykresu
set xlabel "t" # etykieta osi OX
set ylabel "x(t)" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej
plot "Przyklad1.txt" w p t "x(t), dt = 0.2"

set output "Przyklad2.eps" # nazwa pliku wynikowego
set title "Wychylenie x(t) dla parametrow B = 0.4, F0 = 0, Omega = 0.8" # tytul wykresu
set xlabel "t" # etykieta osi OX
set ylabel "x(t)" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej
plot "Przyklad2.txt" w p t "x(t), dt = 0.2"
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"

set output "Przyklad3.eps" # nazwa pliku wynikowego
set title "Wychylenie x(t) dla parametrow B = 0.4, F0 = 0.1, Omega = 0.8" # tytul wykresu
set xlabel "t" # etykieta osi OX
set ylabel "x(t)" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej
plot "Przyklad3.txt" w p t "x(t), dt = 0.2"
