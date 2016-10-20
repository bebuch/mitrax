set terminal svg size 1000,500 fname 'Verdana' fsize 13
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
set format y "1e%+T"

set key left

## Last datafile plotted: "sobel.dat"
plot \
	'mul-uBLAS_rt_heap.dat' using 1:3:xticlabels(2) linetype -3 notitle, \
	'mul-mitrax_rt_heap.dat' using 1:3 with linespoints title "mitrax rt heap", \
	'mul-mitrax_ct_stack.dat' using 1:3 with linespoints title "mitrax ct stack", \
	'mul-mitrax_ct_heap.dat' using 1:3 with linespoints title "mitrax ct heap", \
	'mul-Eigen_rt_heap.dat' using 1:3 with linespoints title "Eigen rt heap", \
	'mul-Eigen_ct_stack.dat' using 1:3 with linespoints title "Eigen ct stack", \
	'mul-uBLAS_rt_heap.dat' using 1:3 with linespoints title "uBLAS rt heap", \
