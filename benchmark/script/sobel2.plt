set terminal svg size 1000,500 fname 'Verdana' fsize 16
set output 'sobel2.svg'

set title "Sobel Benchmark"
set xlabel "Number of elements"
set ylabel "Runtime in µs"

set grid y
set boxwidth 0.1 absolute
set offset 0.2, 0.2, 0, 0
set datafile separator '\t'

set log y

set key left

set style line 1 lc rgb '#ff0000' lt 1 lw 1 pt 2 pi 1 ps 1
set style line 2 lc rgb '#A09040' lt 1 lw 1 pt 4 pi 1 ps 1
set style line 3 lc rgb '#0000ff' lt 1 lw 1 pt 6 pi 1 ps 1
set style line 4 lc rgb '#D040D0' lt 1 lw 1 pt 1 pi 1 ps 1
set pointintervalbox 2

## Last datafile plotted: "sobel2.dat"
plot \
	'sobel2_uBLAS.dat' using 0:2:xticlabels(1) linetype -3 notitle, \
	'sobel2_uBLAS.dat' using 0:2 with linespoints ls 4 title "uBLAS", \
	'sobel2_Eigen.dat' using 0:2 with linespoints ls 3 title "Eigen", \
	'sobel2_mitrax.dat' using 0:2 with linespoints ls 1 title "mitrax", \
	'sobel2_mitrax_eigen_adapter.dat' using 0:2 with linespoints ls 2 title "mitrax Eigen adapter", \
