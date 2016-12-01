set terminal svg size 1000,500 fname 'Verdana' fsize 13
set output 'best-plot.svg'

set title "Sobel-Operator Benchmark"
set xlabel "Benchmark"
set ylabel "Runtime in ms"

set grid y
set boxwidth 0.1 absolute
set offset 0.5, 0.5, 0, 0
set xtics rotate
set datafile separator '\t'

set key left

plot \
	'Eigen_ct_stack.dat' using 1:6:xticlabels(2) linetype -3 notitle, \
	'Eigen_ct_stack.dat' using ($1 + 0.00):4:5:6:7 with candlesticks title "Eigen rt heap + Eigen ct stack" lw 2 lt 4 lc 13, \
	'mitrax_constexpr.dat' using ($1 - 0.15):4:5:6:7 with candlesticks title "mitrax rt heap + mitrax constexpr" lw 2 lt 1 lc 4, \
