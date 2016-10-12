#!/bin/bash

cd ..


# Sobel benchmarks
if [ -z ${repetitions+x} ]
then
	repetitions=2
fi

echo "repetitons: $repetitions (set it with 'export repetitions=N')"

echo "run sobel2.Eigen benchmark"
bin/clang-*/release/sobel2_Eigen --benchmark_repetitions=$repetitions --benchmark_format=json > sobel2_Eigen.json
echo "run sobel2.uBLAS benchmark"
bin/clang-*/release/sobel2_uBLAS --benchmark_repetitions=$repetitions --benchmark_format=json > sobel2_uBLAS.json
echo "run sobel2.mitrax benchmark"
bin/clang-*/release/sobel2_mitrax --benchmark_repetitions=$repetitions --benchmark_format=json > sobel2_mitrax.json
