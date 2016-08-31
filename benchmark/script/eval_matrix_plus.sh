#!/bin/bash

cd ..


# Matrix plus
echo "Convert matrix_plus_Eigen.json"
lua script/binaryop_json2gnuplot.lua matrix_plus_Eigen.json > matrix_plus_Eigen.dat
echo "Convert matrix_plus_Eigen_ctdim.json"
lua script/binaryop_json2gnuplot.lua matrix_plus_Eigen_ctdim.json > matrix_plus_Eigen_ctdim.dat
echo "Convert matrix_plus_mitrax.json"
lua script/binaryop_json2gnuplot.lua matrix_plus_mitrax.json > matrix_plus_mitrax.dat
echo "Convert matrix_plus_mitrax_ctdim.json"
lua script/binaryop_json2gnuplot.lua matrix_plus_mitrax_ctdim.json > matrix_plus_mitrax_ctdim.dat
echo "Convert matrix_plus_mitrax_ctdim_heap.json"
lua script/binaryop_json2gnuplot.lua matrix_plus_mitrax_ctdim_heap.json > matrix_plus_mitrax_ctdim_heap.dat
echo "Convert matrix_plus_uBLAS.json"
lua script/binaryop_json2gnuplot.lua matrix_plus_uBLAS.json > matrix_plus_uBLAS.dat

echo "Plot script/matrix_plus.plt"
gnuplot script/matrix_plus.plt
