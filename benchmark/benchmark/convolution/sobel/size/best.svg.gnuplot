set terminal svg size 1000,500 fname 'Verdana' fsize 16
set output 'best-plot.svg'

set title "Sobel Benchmark"
set xlabel " "
set ylabel "Runtime in ms"

set grid y
set boxwidth 0.1 absolute
set offset 0.2, 0.2, 0, 0
set datafile separator '\t'

set key left
set yrange [0:]
set style fill solid 1.0
unset key

round(x) = x - floor(x) < 0.5 ? floor(x) : ceil(x)
round2(x, n) = round(x*10**n)*10.0**(-n)
print(x) = sprintf('%.2f ms', x)

plot \
	'Eigen_ct_stack.dat' using (1.0):3:xtic("Eigen rt heap\nEigen ct stack") with boxes lw 2 lt 4 lc 13, \
	'mitrax_constexpr_Eigen.dat' using (2.0):3:xtic("mitrax(Eigen) rt heap\nmitrax constexpr") with boxes lw 2 lt 12 lc 10, \
	'mitrax_constexpr.dat' using (3.0):3:xtic("mitrax rt heap\nmitrax constexpr") with boxes lw 2 lt 1 lc 4, \
	'Eigen_ct_stack.dat' using (1.0):($3+4):(print(round2($3, 2))) with labels, \
	'mitrax_constexpr_Eigen.dat' using (2.0):($3+4):(print(round2($3, 2))) with labels, \
	'mitrax_constexpr.dat' using (3.0):($3+4):(print(round2($3, 2))) with labels, \
