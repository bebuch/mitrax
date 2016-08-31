#!/bin/bash

cd ..


# Matrix plus
if [ -z ${repetitions+x} ]
then
	repetitions=2
fi

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
