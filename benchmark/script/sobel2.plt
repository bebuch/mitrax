set terminal svg size 1000,500 fname 'Verdana' fsize 16
set output 'sobel2.svg'

set title "Sobel Benchmark"
set xlabel "Number of elements"
set ylabel "Runtime in µs"

set grid y
set boxwidth 0.1 absolute
set offset 0.5, 0.5, 0, 0
set datafile separator '\t'

set log y

set key left

## Last datafile plotted: "sobel2.dat"
plot \
	'sobel2_uBLAS.dat' using 0:2:xticlabels(1) linetype -3 notitle, \
	'sobel2_mitrax.dat' using 0:2 with linespoints title "mitrax", \
	'sobel2_Eigen.dat' using 0:2 with linespoints title "Eigen", \
	'sobel2_uBLAS.dat' using 0:2 with linespoints title "uBLAS", \
