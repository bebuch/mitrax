#!/bin/bash

cd ..


# Matrix make
echo "Convert matrix_make_Eigen.json"
lua script/binaryop_json2gnuplot.lua matrix_make_Eigen.json > matrix_make_Eigen.dat
echo "Convert matrix_make_Eigen_ctdim.json"
lua script/binaryop_json2gnuplot.lua matrix_make_Eigen_ctdim.json > matrix_make_Eigen_ctdim.dat
echo "Convert matrix_make_mitrax.json"
lua script/binaryop_json2gnuplot.lua matrix_make_mitrax.json > matrix_make_mitrax.dat
echo "Convert matrix_make_mitrax_ctdim.json"
lua script/binaryop_json2gnuplot.lua matrix_make_mitrax_ctdim.json > matrix_make_mitrax_ctdim.dat
echo "Convert matrix_make_mitrax_ctdim_heap.json"
lua script/binaryop_json2gnuplot.lua matrix_make_mitrax_ctdim_heap.json > matrix_make_mitrax_ctdim_heap.dat
echo "Convert matrix_make_uBLAS.json"
lua script/binaryop_json2gnuplot.lua matrix_make_uBLAS.json > matrix_make_uBLAS.dat

echo "Plot script/matrix_make.plt"
gnuplot script/matrix_make.plt
