#!/bin/bash

location="binary_op/size"

cd ../../../

dir=$PWD

cd bin/clang-*/release/benchmark/$location
name="$location/plus"


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
			$benchmark --op=+ $param --benchmark_out=plus-${benchmark#./*}.json
		else
			cset shield --exec $benchmark -- --op=+ $param --benchmark_out=plus-${benchmark#./*}.json
		fi
	fi
	echo "eval $name:${benchmark#./*}"
	lua $dir/script/json2gnuplot.lua plus-${benchmark#./*}.json > plus-${benchmark#./*}.dat
done

echo "plot $name"
gnuplot $dir/benchmark/$location/plus.svg.gnuplot
for f in *.svg
do
    mv -f "$f" "$dir/${location//\//-}-$f"
done
