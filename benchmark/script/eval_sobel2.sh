#!/bin/bash

cd ..


# Sobel
echo "Convert sobel2_Eigen.json"
lua script/binaryop_json2gnuplot.lua sobel2_Eigen.json > sobel2_Eigen.dat
echo "Convert sobel2_uBLAS.json"
lua script/binaryop_json2gnuplot.lua sobel2_uBLAS.json > sobel2_uBLAS.dat
echo "Convert sobel2_mitrax.json"
lua script/binaryop_json2gnuplot.lua sobel2_mitrax.json > sobel2_mitrax.dat

echo "Plot script/sobel2.plt"
gnuplot script/sobel2.plt
