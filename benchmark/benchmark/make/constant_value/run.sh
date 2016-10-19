#!/bin/bash

cd ..


# Matrix make_v
if [ -z ${repetitions+x} ]
then
	repetitions=2
fi

echo "repetitons: $repetitions (set it with 'export repetitions=N')"

echo "run benchmark make constant matrix make_v.Eigen"
bin/clang-*/release/make_v_Eigen --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_v_Eigen.json
echo "run benchmark make constant matrix make_v.Eigen_ctdim"
bin/clang-*/release/make_v_Eigen_ctdim --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_v_Eigen_ctdim.json
echo "run benchmark make constant matrix make_v.mitrax"
bin/clang-*/release/make_v_mitrax --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_v_mitrax.json
echo "run benchmark make constant matrix make_v.mitrax_ctdim"
bin/clang-*/release/make_v_mitrax_ctdim --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_v_mitrax_ctdim.json
echo "run benchmark make constant matrix make_v.mitrax_ctdim_heap"
bin/clang-*/release/make_v_mitrax_ctdim_heap --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_v_mitrax_ctdim_heap.json
echo "run benchmark make constant matrix make_v.uBLAS"
bin/clang-*/release/make_v_uBLAS --benchmark_repetitions=$repetitions --benchmark_format=json > matrix_make_v_uBLAS.json
