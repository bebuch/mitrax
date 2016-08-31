#!/bin/bash

repetitions=2

cd ..

# Sobel benchmarks
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

echo "run binaryop.Eigen matrix multiplication benchmark"
bin/clang-*/release/binaryop_Eigen --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_Eigen.json
echo "run binaryop.Eigen_ctdim matrix multiplication benchmark"
bin/clang-*/release/binaryop_Eigen --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_Eigen_ctdim.json
echo "run binaryop.mitrax matrix multiplication benchmark"
bin/clang-*/release/binaryop_mitrax --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_mitrax.json
echo "run binaryop.mitrax_ctdim matrix multiplication benchmark"
bin/clang-*/release/binaryop_mitrax_ctdim --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_mitrax_ctdim.json
echo "run binaryop.mitrax_ctdim_heap matrix multiplication benchmark"
bin/clang-*/release/binaryop_mitrax_ctdim_heap --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_mitrax_ctdim_heap.json
echo "run binaryop.uBLAS matrix multiplication benchmark"
bin/clang-*/release/binaryop_uBLAS --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_mul_uBLAS.json
