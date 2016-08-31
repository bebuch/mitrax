#!/bin/bash

repetitions=100

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

echo "run matrix_multiplication.Eigen benchmark"
bin/clang-*/release/matrix_multiplication_Eigen --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_multiplication_Eigen.json
echo "run matrix_multiplication.Eigen_static benchmark"
bin/clang-*/release/matrix_multiplication_Eigen --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_multiplication_Eigen_static.json
echo "run matrix_multiplication.mitrax benchmark"
bin/clang-*/release/matrix_multiplication_mitrax --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_multiplication_mitrax.json
echo "run matrix_multiplication.mitrax_static benchmark"
bin/clang-*/release/matrix_multiplication_mitrax_static --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_multiplication_mitrax_static.json
echo "run matrix_multiplication.mitrax_static_heap benchmark"
bin/clang-*/release/matrix_multiplication_mitrax_static_heap --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_multiplication_mitrax_static_heap.json
echo "run matrix_multiplication.uBLAS benchmark"
bin/clang-*/release/matrix_multiplication_uBLAS --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_multiplication_uBLAS.json
