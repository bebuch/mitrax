set terminal svg size 1000,500 fname 'Verdana' fsize 13
set output 'plot.svg'

set title "Initialisierung mit konstantem Wert"
set xlabel "Anzahl der Elemente"
set ylabel "Laufzeit in ms"

set grid y
set boxwidth 0.1 absolute
set offset 0.5, 0.5, 0, 0
set xtics rotate
set datafile separator '\t'

set log y
set format y "1e%+T"

set key left

plot \
	'uBLAS_rt_heap.dat' using 1:3:xticlabels(2) linetype -3 notitle, \
	'mitrax_rt_heap.dat' using 1:3 with linespoints title "mitrax rt heap" lw 2 ps 1.3 lt 2 lc 3, \
	'mitrax_ct_heap.dat' using 1:3 with linespoints title "mitrax ct heap" lw 2 ps 1.3 lt 6 lc 8, \
	'mitrax_ct_stack.dat' using 1:3 with linespoints title "mitrax ct stack" lw 2 ps 1.3 lt 1 lc 4, \
	'Eigen_rt_heap.dat' using 1:3 with linespoints title "Eigen rt heap" lw 2 ps 1.3 lt 12 lc 5, \
	'Eigen_ct_stack.dat' using 1:3 with linespoints title "Eigen ct stack" lw 2 ps 1.3 lt 4 lc 13, \
	'uBLAS_rt_heap.dat' using 1:3 with linespoints title "uBLAS rt heap" lw 2 ps 1.3 lt 8 lc 7, \
