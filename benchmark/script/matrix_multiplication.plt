set terminal svg size 1000,500 fname 'Verdana' fsize 10
set output 'matrix_multiplication.svg'

set title "Matrix multiplication Benchmark"
set xlabel "Number of elements"
set ylabel "Laufzeit in µs"

set grid y
set boxwidth 0.1 absolute
set offset 0.5, 0.5, 0, 0
set xtics rotate
set datafile separator '\t'

set log y

set key left

## Last datafile plotted: "sobel.dat"
plot \
	'matrix_multiplication_mitrax_static_heap.dat' using 0:2:xticlabels(1) linetype -3 notitle, \
	'matrix_multiplication_mitrax.dat' using 0:2 with linespoints title "mitrax", \
	'matrix_multiplication_mitrax_static.dat' using 0:2 with linespoints title "mitrax static", \
	'matrix_multiplication_mitrax_static_heap.dat' using 0:2 with linespoints title "mitrax static heap", \
	'matrix_multiplication_Eigen.dat' using 0:2 with linespoints title "Eigen", \
	'matrix_multiplication_Eigen_static.dat' using 0:2 with linespoints title "Eigen static", \
	'matrix_multiplication_uBLAS.dat' using 0:2 with linespoints title "uBLAS", \
