set terminal svg size 1000,500 fname 'Verdana' fsize 10
set output 'matrix_plus.svg'

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
	'matrix_plus_uBLAS.dat' using 0:2:xticlabels(1) linetype -3 notitle, \
	'matrix_plus_mitrax.dat' using 0:2 with linespoints title "mitrax", \
	'matrix_plus_mitrax_ctdim.dat' using 0:2 with linespoints title "mitrax ctdim", \
	'matrix_plus_mitrax_ctdim_heap.dat' using 0:2 with linespoints title "mitrax ctdim heap", \
	'matrix_plus_Eigen.dat' using 0:2 with linespoints title "Eigen", \
	'matrix_plus_Eigen_ctdim.dat' using 0:2 with linespoints title "Eigen ctdim", \
	'matrix_plus_uBLAS.dat' using 0:2 with linespoints title "uBLAS", \
