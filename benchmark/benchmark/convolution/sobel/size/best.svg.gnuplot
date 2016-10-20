set terminal svg size 1000,500 fname 'Verdana' fsize 16
set output 'best-plot.svg'

set title "Sobel Benchmark"
set xlabel "Number of elements"
set ylabel "Runtime in µs"

set grid y
set boxwidth 0.1 absolute
set offset 0.2, 0.2, 0, 0
set datafile separator '\t'

set key left

set style line 1 lc rgb '#A09040' lt 1 lw 1 pt 4 pi 1 ps 1
set style line 2 lc rgb '#0000ff' lt 1 lw 1 pt 6 pi 1 ps 1
set style line 3 lc rgb '#D040D0' lt 1 lw 1 pt 1 pi 1 ps 1
set pointintervalbox 2

plot \
	'Eigen_ct_stack.dat' using 1:3:xticlabels(2) linetype -3 notitle, \
	'Eigen_ct_stack.dat' using 1:3 with linespoints ls 3 title "Eigen rtdim heap + Eigen ctdim stack", \
	'mitrax_constexpr.dat' using 1:3 with linespoints ls 1 title "mitrax rtdim heap + mitrax constexpr", \
	'mitrax_constexpr_Eigen.dat' using 1:3 with linespoints ls 2 title "mitrax(Eigen) rtdim heap + mitrax constexpr", \
