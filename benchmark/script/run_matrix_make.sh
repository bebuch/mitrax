#!/bin/bash

cd ..


# Matrix make
if [ -z ${repetitions+x} ]
then
	repetitions=2
fi

echo "repetitons: $repetitions (set it with 'export repetitions=N')"

echo "run benchmark make random matrix make.Eigen"
bin/clang-*/release/make_Eigen --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_Eigen.json
echo "run benchmark make random matrix make.Eigen_ctdim"
bin/clang-*/release/make_Eigen_ctdim --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_Eigen_ctdim.json
echo "run benchmark make random matrix make.mitrax"
bin/clang-*/release/make_mitrax --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_mitrax.json
echo "run benchmark make random matrix make.mitrax_ctdim"
bin/clang-*/release/make_mitrax_ctdim --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_mitrax_ctdim.json
echo "run benchmark make random matrix make.mitrax_ctdim_heap"
bin/clang-*/release/make_mitrax_ctdim_heap --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_mitrax_ctdim_heap.json
echo "run benchmark make random matrix make.uBLAS"
bin/clang-*/release/make_uBLAS --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_uBLAS.json
