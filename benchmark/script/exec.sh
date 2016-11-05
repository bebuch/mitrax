#!/bin/bash

./build.sh

# Use cset for better benchmarks
#
# As root:
# $#> for ((i=0;i<$(nproc);++i)); do cpufreq-set -g performance -d 2GHz -u 2GHz -c $i; done
# $#> cset shield -k on -c 1
# $#> export repetitions=20

cd ..

dir=$PWD
for f in $(find benchmark -type d)
do
	cd "$dir/$f"
	for r in $(find ./ -maxdepth 1 -name '*run.sh')
	do
		echo "exec $r"
		$r
	done
done
