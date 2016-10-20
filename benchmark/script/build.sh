#!/bin/bash

cd ..
echo "Build benchmarks"
bjam toolset=clang release
