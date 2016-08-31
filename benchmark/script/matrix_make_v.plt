set terminal svg size 1000,500 fname 'Verdana' fsize 10
set output 'matrix_make_v.svg'

set title "make constant matrix Benchmark"
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
	'matrix_make_v_uBLAS.dat' using 0:2:xticlabels(1) linetype -3 notitle, \
	'matrix_make_v_mitrax.dat' using 0:2 with linespoints title "mitrax", \
	'matrix_make_v_mitrax_ctdim.dat' using 0:2 with linespoints title "mitrax ctdim", \
	'matrix_make_v_mitrax_ctdim_heap.dat' using 0:2 with linespoints title "mitrax ctdim heap", \
	'matrix_make_v_Eigen.dat' using 0:2 with linespoints title "Eigen", \
	'matrix_make_v_Eigen_ctdim.dat' using 0:2 with linespoints title "Eigen ctdim", \
	'matrix_make_v_uBLAS.dat' using 0:2 with linespoints title "uBLAS", \
