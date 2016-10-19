#!/bin/bash

cd ..


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
