#!/bin/bash

cd ..

lua lua/json2gnuplot.lua sobel_Eigen.json > sobel_Eigen.dat
lua lua/json2gnuplot.lua sobel_uBLAS.json > sobel_uBLAS.dat
lua lua/json2gnuplot.lua sobel_mitrax.json > sobel_mitrax.dat
# doesn't work yet
# lua lua/json2gnuplot.lua sobel_GIL.json > sobel_GIL.dat

gnuplot script/sobel.plt
