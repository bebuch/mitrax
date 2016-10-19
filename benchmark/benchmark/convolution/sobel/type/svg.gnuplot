set terminal svg size 1000,500 fname 'Verdana' fsize 10
set output 'sobel.svg'

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

## Last datafile plotted: "sobel.dat"
plot \
	'sobel_uBLAS.dat' using 1:5:xticlabels(2) linetype -3 notitle, \
	'sobel_mitrax.dat' using ($1 - 0.15):3:4:5:6 with candlesticks title "mitrax", \
	'sobel_Eigen.dat' using ($1 + 0.00):3:4:5:6 with candlesticks title "Eigen", \
	'sobel_uBLAS.dat' using ($1 + 0.15):3:4:5:6 with candlesticks title "uBLAS", \
