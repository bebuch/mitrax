#!/bin/bash

./build.sh

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
