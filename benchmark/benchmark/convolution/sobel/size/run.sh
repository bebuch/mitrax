#!/bin/bash

location="convolution/sobel/size"

cd ../../../../

dir=$PWD

cd bin/clang-*/release/benchmark/$location
name="$location"


if [ -z ${repetitions+x} ]
then
	repetitions=1
fi

echo "repetitons: $repetitions (set it with 'export repetitions=N')"
param="--benchmark_repetitions=$repetitions --benchmark_format=json"


for benchmark in $(find ./ -maxdepth 1 -executable -type f)
do
	echo "run  $name:${benchmark#./*}"
	if [ -z ${dontexec+x} ]; then
		if [[ $EUID -ne 0 ]]; then
			$benchmark $param --benchmark_out=${benchmark#./*}.json
		else
			cset shield --exec $benchmark -- $param --benchmark_out=${benchmark#./*}.json
		fi	fi
	echo "eval $name:${benchmark#./*}"
	lua $dir/script/json2gnuplot.lua ${benchmark#./*}.json > ${benchmark#./*}.dat
done

echo "plot $name"
gnuplot $dir/benchmark/$location/all.svg.gnuplot
gnuplot $dir/benchmark/$location/best.svg.gnuplot
for f in *.svg
do
    mv -f "$f" "$dir/${location//\//-}-$f"
done
