#!/bin/bash

errors=0;

gcc -o ./tests/matrix_compare ./tests/matrix_compare.c -std=c11
for j in {2..5}
do
    echo "Performing tests for ${j}^3 processes:" >> ${1}
    ((p=j**3))
    for i in {0..4}
    do
        echo "Test number $i:" >> ${1}
        mpirun -n ${p} ./main tests/A${i} tests/B${i} tests/C${i}_ 0 >> ${1}
        ./tests/matrix_compare tests/C${i}_ tests/C${i} >> ${1}
        errors=$(($errors + $?))
        rm ./tests/C${i}_
    done
    echo "Tests done." >> ${1}
done

exit ${errors}
