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
