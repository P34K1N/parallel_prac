#!/bin/bash

errors=0;

g++ -o ./tests/matrix_compare ./tests/matrix_compare.cpp
for j in {0..5}
do
    echo "Performing tests for $j version of multiplication:" >> ${1}
    for i in {0..19}
    do
        echo "Test number $i:" >> ${1}
        ./multi tests/A${i} tests/B${i} tests/C${i}_${j} ${j} >> ${1}
        ./tests/matrix_compare tests/C${i}_${j} tests/C${i} >> ${1}
        errors=$(($errors + $?))
        rm ./tests/C${i}_${j}
    done
    echo "Tests done." >> ${1}
done

exit ${errors}
