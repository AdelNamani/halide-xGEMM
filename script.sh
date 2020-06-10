#!/bin/bash

while getopts p: flag
do
    case "${flag}" in
        p) path=${OPTARG};;
    esac
done


echo "Compiling halide_xGEMM.cpp ..."
g++ ./src/halide_xGEMM.cpp -g -L ${path}/bin -I ${path}/include -I ${path}/tools  -lHalide -ldl -lpthread -std=c++11 -o ./bin/halide_xGEMM
echo "Compiling test_halide_xGEMM.c ..."
gcc ./src/test_halide_xGEMM.c -o ./bin/test_halide_xGEMM
echo "Executing halide_xGEMM ..."
LD_LIBRARY_PATH=${path}/bin ./bin/halide_xGEMM || exit 1
echo "Executing test_halide_xGEMM ..."
./bin/test_halide_xGEMM

