set terminal svg size 1000,500 fname 'Verdana' fsize 10
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

set key left

## Last datafile plotted: "sobel.dat"
plot \
	'uBLAS_rt_heap.dat' using 0:2:xticlabels(1) linetype -3 notitle, \
	'mitrax_rt_heap.dat' using 0:2 with linespoints title "mitrax rtdim heap", \
	'mitrax_ct_stack.dat' using 0:2 with linespoints title "mitrax ctdim stack", \
	'mitrax_ct_heap.dat' using 0:2 with linespoints title "mitrax ctdim heap", \
	'Eigen_rt_heap.dat' using 0:2 with linespoints title "Eigen rtdim heap", \
	'Eigen_ct_stack.dat' using 0:2 with linespoints title "Eigen ctdim stack", \
	'uBLAS_rt_heap.dat' using 0:2 with linespoints title "uBLAS rtdim heap", \
