#!/bin/bash

cd ..

# Sobel
echo "Convert sobel_Eigen.json"
lua script/sobel_json2gnuplot.lua sobel_Eigen.json > sobel_Eigen.dat
echo "Convert sobel_uBLAS.json"
lua script/sobel_json2gnuplot.lua sobel_uBLAS.json > sobel_uBLAS.dat
echo "Convert sobel_mitrax.json"
lua script/sobel_json2gnuplot.lua sobel_mitrax.json > sobel_mitrax.dat
# doesn't work yet
# echo "Convert sobel_GIL.json"
# lua script/sobel_json2gnuplot.lua sobel_GIL.json > sobel_GIL.dat

echo "Plot script/sobel.plt"
gnuplot script/sobel.plt


# Matrix multiplication
echo "Convert matrix_mul_Eigen.json"
lua script/binaryop_json2gnuplot.lua matrix_mul_Eigen.json > matrix_mul_Eigen.dat
echo "Convert matrix_mul_Eigen_ctdim.json"
lua script/binaryop_json2gnuplot.lua matrix_mul_Eigen_ctdim.json > matrix_mul_Eigen_ctdim.dat
echo "Convert matrix_mul_mitrax.json"
lua script/binaryop_json2gnuplot.lua matrix_mul_mitrax.json > matrix_mul_mitrax.dat
echo "Convert matrix_mul_mitrax_ctdim.json"
lua script/binaryop_json2gnuplot.lua matrix_mul_mitrax_ctdim.json > matrix_mul_mitrax_ctdim.dat
echo "Convert matrix_mul_mitrax_ctdim_heap.json"
lua script/binaryop_json2gnuplot.lua matrix_mul_mitrax_ctdim_heap.json > matrix_mul_mitrax_ctdim_heap.dat
echo "Convert matrix_mul_uBLAS.json"
lua script/binaryop_json2gnuplot.lua matrix_mul_uBLAS.json > matrix_mul_uBLAS.dat

echo "Plot script/matrix_mul.plt"
gnuplot script/matrix_mul.plt


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
