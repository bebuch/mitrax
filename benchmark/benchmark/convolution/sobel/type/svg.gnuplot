set terminal svg size 1000,500 fname 'Verdana' fsize 10
set output 'plot.svg'

set title "Sobel-Operator Benchmark"
set xlabel "Benchmark"
set ylabel "Runtime in µs"

set grid y
set boxwidth 0.1 absolute
set offset 0.5, 0.5, 0, 0
set xtics rotate
set datafile separator '\t'

set log y

set key left

plot \
	'uBLAS_rt_heap.dat' using 1:6:xticlabels(2) linetype -3 notitle, \
	'uBLAS_rt_heap.dat' using ($1 + 0.15):4:5:6:7 with candlesticks title "uBLAS rtdim heap + uBLAS rtdim heap", \
	'Eigen_ct_stack.dat' using ($1 + 0.00):4:5:6:7 with candlesticks title "Eigen rtdim heap + Eigen ctdim stack", \
	'mitrax_constexpr.dat' using ($1 - 0.15):4:5:6:7 with candlesticks title "mitrax rtdim heap + mitrax constexpr", \
