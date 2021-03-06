set terminal svg size 1000,500 fname 'Verdana' fsize 13
set output 'best-plot.svg'

set title "Sobel-Operator"
set xlabel "Benchmark"
set ylabel "Laufzeit in ms"

set grid y
set boxwidth 0.1 absolute
set offset 0.5, 0.5, 0, 0
set xtics rotate
set datafile separator '\t'

set key left
set yrange [0:]
set style fill solid 1.0

plot \
	'Eigen_ct_stack.dat' using 1:6:xticlabels(2) linetype -3 notitle, \
	'Eigen_ct_stack.dat' using ($1 + 0.00):3 with boxes title "Eigen rt heap + Eigen ct stack" lw 2 lt 4 lc 13, \
	'mitrax_constexpr.dat' using ($1 - 0.15):3 with boxes title "mitrax rt heap + mitrax constexpr" lw 2 lt 1 lc 4, \
