#!/bin/bash

cd ..


# Sobel benchmarks
if [ -z ${repetitions+x} ]
then
	repetitions=2
fi

echo "repetitons: $repetitions (set it with 'export repetitions=N')"

echo "run sobel.Eigen benchmark"
bin/clang-*/release/sobel_Eigen --benchmark_repetitions=$repetitions --benchmark_format=json > sobel_Eigen.json
echo "run sobel.uBLAS benchmark"
bin/clang-*/release/sobel_uBLAS --benchmark_repetitions=$repetitions --benchmark_format=json > sobel_uBLAS.json
echo "run sobel.mitrax benchmark"
bin/clang-*/release/sobel_mitrax --benchmark_repetitions=$repetitions --benchmark_format=json > sobel_mitrax.json
