set terminal svg size 1000,500 fname 'Verdana' fsize 10
set output 'mul-plot.svg'

set title "Matrix multiplication Benchmark"
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
	'uBLAS_rt_heap.dat' using 1:3:xticlabels(2) linetype -3 notitle, \
	'mitrax_rt_heap.dat' using 1:3 with linespoints title "mitrax rtdim heap", \
	'mitrax_ct_stack.dat' using 1:3 with linespoints title "mitrax ctdim stack", \
	'mitrax_ct_heap.dat' using 1:3 with linespoints title "mitrax ctdim heap", \
	'Eigen_rt_heap.dat' using 1:3 with linespoints title "Eigen rtdim heap", \
	'Eigen_ct_stack.dat' using 1:3 with linespoints title "Eigen ctdim stack", \
	'uBLAS_rt_heap.dat' using 1:3 with linespoints title "uBLAS rtdim heap", \
