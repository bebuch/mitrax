#!/bin/bash

cd ..


# Matrix multiplication
if [ -z ${repetitions+x} ]
then
	repetitions=2
fi

echo "repetitons: $repetitions (set it with 'export repetitions=N')"

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
