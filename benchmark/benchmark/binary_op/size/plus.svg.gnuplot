set terminal svg size 1000,500 fname 'Verdana' fsize 13
set output 'plus-plot.svg'

set title "Matrix plus Benchmark"
set xlabel "Number of elements"
set ylabel "Runtime in µs"

set grid y
set boxwidth 0.1 absolute
set offset 0.5, 0.5, 0, 0
set xtics rotate
set datafile separator '\t'

set log y
set format y "1e%+T"

set key left

## Last datafile plotted: "sobel.dat"
plot \
	'plus-uBLAS_rt_heap.dat' using 1:3:xticlabels(2) linetype -3 notitle, \
	'plus-mitrax_rt_heap.dat' using 1:3 with linespoints title "mitrax rt heap", \
	'plus-mitrax_ct_stack.dat' using 1:3 with linespoints title "mitrax ct stack", \
	'plus-mitrax_ct_heap.dat' using 1:3 with linespoints title "mitrax ct heap", \
	'plus-Eigen_rt_heap.dat' using 1:3 with linespoints title "Eigen rt heap", \
	'plus-Eigen_ct_stack.dat' using 1:3 with linespoints title "Eigen ct stack", \
	'plus-uBLAS_rt_heap.dat' using 1:3 with linespoints title "uBLAS rt heap", \
