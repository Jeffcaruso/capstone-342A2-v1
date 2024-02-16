#!/bin/bash

rm -f a.out

echo "Compiling: g++ *.cpp -lgtest -lgtest_main -pthread"
g++ *.cpp -lgtest -lgtest_main -pthread

echo "Executing: ./a.out"
./a.out