#!/bin/bash

cd ..


# Sobel benchmarks
repetitions=2

echo "run sobel.Eigen benchmark"
bin/clang-*/release/sobel_Eigen --benchmark_repetitions=$repetitions --benchmark_format=json > sobel_Eigen.json
echo "run sobel.uBLAS benchmark"
bin/clang-*/release/sobel_uBLAS --benchmark_repetitions=$repetitions --benchmark_format=json > sobel_uBLAS.json
echo "run sobel.mitrax benchmark"
bin/clang-*/release/sobel_mitrax --benchmark_repetitions=$repetitions --benchmark_format=json > sobel_mitrax.json
# doesn't work yet
# bin/clang-*/release/sobel_GIL --benchmark_repetitions=$repetitions --benchmark_format=json > sobel_GIL.json


# Matrix multiplication
# repetitions=2

echo "run benchmark matrix multiplication binaryop.Eigen"
bin/clang-*/release/binaryop_Eigen --op=* --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_Eigen.json
echo "run benchmark matrix multiplication binaryop.Eigen_ctdim"
bin/clang-*/release/binaryop_Eigen_ctdim --op=* --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_Eigen_ctdim.json
echo "run benchmark matrix multiplication binaryop.mitrax"
bin/clang-*/release/binaryop_mitrax --op=* --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_mitrax.json
echo "run benchmark matrix multiplication binaryop.mitrax_ctdim"
bin/clang-*/release/binaryop_mitrax_ctdim --op=* --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_mitrax_ctdim.json
echo "run benchmark matrix multiplication binaryop.mitrax_ctdim_heap"
bin/clang-*/release/binaryop_mitrax_ctdim_heap --op=* --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_mitrax_ctdim_heap.json
echo "run benchmark matrix multiplication binaryop.uBLAS"
bin/clang-*/release/binaryop_uBLAS --op=* --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_uBLAS.json


# Matrix plus
# repetitions=2

echo "run benchmark matrix plus binaryop.Eigen"
bin/clang-*/release/binaryop_Eigen --op=+ --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_plus_Eigen.json
echo "run benchmark matrix plus binaryop.Eigen_ctdim"
bin/clang-*/release/binaryop_Eigen_ctdim --op=+ --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_plus_Eigen_ctdim.json
echo "run benchmark matrix plus binaryop.mitrax"
bin/clang-*/release/binaryop_mitrax --op=+ --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_plus_mitrax.json
echo "run benchmark matrix plus binaryop.mitrax_ctdim"
bin/clang-*/release/binaryop_mitrax_ctdim --op=+ --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_plus_mitrax_ctdim.json
echo "run benchmark matrix plus binaryop.mitrax_ctdim_heap"
bin/clang-*/release/binaryop_mitrax_ctdim_heap --op=+ --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_plus_mitrax_ctdim_heap.json
echo "run benchmark matrix plus binaryop.uBLAS"
bin/clang-*/release/binaryop_uBLAS --op=+ --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_plus_uBLAS.json
