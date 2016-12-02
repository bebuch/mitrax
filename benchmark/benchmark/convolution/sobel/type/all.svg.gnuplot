set terminal svg size 1000,500 fname 'Verdana' fsize 13
set output 'all-plot.svg'

set title "Sobel-Operator"
set xlabel "Benchmark"
set ylabel "Laufzeit in ms"

set grid y
set boxwidth 0.1 absolute
set offset 0.5, 0.5, 0, 0
set xtics rotate
set datafile separator '\t'

set log y
set format y "1e%+T"
set style fill solid 1.0

set key left

plot \
	'uBLAS_rt_heap.dat' using 1:6:xticlabels(2) linetype -3 notitle, \
	'uBLAS_rt_heap.dat' using ($1 + 0.15):3 with boxes title "uBLAS rt heap + uBLAS ct stack" lw 2 lt 8 lc 7, \
	'Eigen_ct_stack.dat' using ($1 + 0.00):3 with boxes title "Eigen rt heap + Eigen ct stack" lw 2 lt 4 lc 13, \
	'mitrax_constexpr.dat' using ($1 - 0.15):3 with boxes title "mitrax rt heap + mitrax constexpr" lw 2 lt 1 lc 4, \
