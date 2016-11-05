#!/bin/bash

location="binary_op/size"

cd ../../../

dir=$PWD

cd bin/clang-*/release/benchmark/$location
name="$location/mul"


if [ -z ${repetitions+x} ]
then
	repetitions=1
fi

echo "repetitons: $repetitions (set it with 'export repetitions=N')"
param="--benchmark_repetitions=$repetitions --benchmark_format=json"


for benchmark in $(find ./ -maxdepth 1 -executable -type f)
do
	echo "run  $name:${benchmark#./*}"
# 	cset shield --exec $benchmark -- --op=* $param --benchmark_out=mul-${benchmark#./*}.json
	echo "eval $name:${benchmark#./*}"
	lua $dir/script/json2gnuplot.lua mul-${benchmark#./*}.json > mul-${benchmark#./*}.dat
done

echo "plot $name"
gnuplot $dir/benchmark/$location/mul.svg.gnuplot
for f in *.svg
do
    mv -f "$f" "$dir/${location//\//-}-$f"
done
