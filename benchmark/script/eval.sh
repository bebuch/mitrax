#!/bin/bash

cd ..

# Sobel
lua script/sobel_json2gnuplot.lua sobel_Eigen.json > sobel_Eigen.dat
lua script/sobel_json2gnuplot.lua sobel_uBLAS.json > sobel_uBLAS.dat
lua script/sobel_json2gnuplot.lua sobel_mitrax.json > sobel_mitrax.dat
# doesn't work yet
# lua script/sobel_json2gnuplot.lua sobel_GIL.json > sobel_GIL.dat

gnuplot script/sobel.plt


# Matrix multiplication
lua script/binaryop_json2gnuplot.lua matrix_mul_Eigen.json > matrix_mul_Eigen.dat
lua script/binaryop_json2gnuplot.lua matrix_mul_Eigen_ctdim.json > matrix_mul_Eigen_ctdim.dat
lua script/binaryop_json2gnuplot.lua matrix_mul_mitrax.json > matrix_mul_mitrax.dat
lua script/binaryop_json2gnuplot.lua matrix_mul_mitrax_ctdim.json > matrix_mul_mitrax_ctdim.dat
lua script/binaryop_json2gnuplot.lua matrix_mul_mitrax_ctdim_heap.json > matrix_mul_mitrax_ctdim_heap.dat
lua script/binaryop_json2gnuplot.lua matrix_mul_uBLAS.json > matrix_mul_uBLAS.dat

gnuplot script/matrix_mul.plt
