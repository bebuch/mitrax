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
lua script/matrix_multiplication_json2gnuplot.lua matrix_multiplication_Eigen.json > matrix_multiplication_Eigen.dat
lua script/matrix_multiplication_json2gnuplot.lua matrix_multiplication_Eigen_static.json > matrix_multiplication_Eigen_static.dat
lua script/matrix_multiplication_json2gnuplot.lua matrix_multiplication_mitrax.json > matrix_multiplication_mitrax.dat
lua script/matrix_multiplication_json2gnuplot.lua matrix_multiplication_mitrax_static.json > matrix_multiplication_mitrax_static.dat
lua script/matrix_multiplication_json2gnuplot.lua matrix_multiplication_mitrax_static_heap.json > matrix_multiplication_mitrax_static_heap.dat
lua script/matrix_multiplication_json2gnuplot.lua matrix_multiplication_uBLAS.json > matrix_multiplication_uBLAS.dat

gnuplot script/matrix_multiplication.plt
