#!/bin/bash

cd ..


# Matrix make_v
echo "Convert matrix_make_v_Eigen.json"
lua script/binaryop_json2gnuplot.lua matrix_make_v_Eigen.json > matrix_make_v_Eigen.dat
echo "Convert matrix_make_v_Eigen_ctdim.json"
lua script/binaryop_json2gnuplot.lua matrix_make_v_Eigen_ctdim.json > matrix_make_v_Eigen_ctdim.dat
echo "Convert matrix_make_v_mitrax.json"
lua script/binaryop_json2gnuplot.lua matrix_make_v_mitrax.json > matrix_make_v_mitrax.dat
echo "Convert matrix_make_v_mitrax_ctdim.json"
lua script/binaryop_json2gnuplot.lua matrix_make_v_mitrax_ctdim.json > matrix_make_v_mitrax_ctdim.dat
echo "Convert matrix_make_v_mitrax_ctdim_heap.json"
lua script/binaryop_json2gnuplot.lua matrix_make_v_mitrax_ctdim_heap.json > matrix_make_v_mitrax_ctdim_heap.dat
echo "Convert matrix_make_v_uBLAS.json"
lua script/binaryop_json2gnuplot.lua matrix_make_v_uBLAS.json > matrix_make_v_uBLAS.dat

echo "Plot script/matrix_make_v.plt"
gnuplot script/matrix_make_v.plt
