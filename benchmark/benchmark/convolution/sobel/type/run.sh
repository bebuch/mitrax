#!/bin/bash

location="convolution/sobel/type"

cd ../../../../

dir=$PWD

cd bin/clang-*/release/benchmark/$location
name="$location"


if [ -z ${repetitions+x} ]
then
	repetitions=2
fi

echo "repetitons: $repetitions (set it with 'export repetitions=N')"
param="--benchmark_repetitions=$repetitions --benchmark_format=json"


for benchmark in $(find ./ -maxdepth 1 -executable -type f)
do
	echo "run  $name:${benchmark#./*}"
	$benchmark $param > ${benchmark#./*}.json
	echo "eval $name:${benchmark#./*}"
	lua $dir/script/json2gnuplot.lua ${benchmark#./*}.json > ${benchmark#./*}.dat
done

echo "plot $name"
gnuplot $dir/benchmark/$location/all-svg.gnuplot
gnuplot $dir/benchmark/$location/best-svg.gnuplot
for f in *.svg
do
    mv -f "$f" "$dir/${name//\//-}-$f"
done
