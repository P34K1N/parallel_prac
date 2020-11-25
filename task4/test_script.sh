#!/bin/bash

errors=0;

gcc -o ./tests/matrix_compare ./tests/matrix_compare.c -std=c11
echo "Performing tests for rowwise version of multiplication and 1 process:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    mpirun -n 1 ./main tests/A${i} tests/b${i} tests/c${i}_ r >> ${1}
    ./tests/matrix_compare tests/c${i}_ tests/c${i} >> ${1}
    errors=$(($errors + $?))
    rm -f ./tests/c${i}_
done
echo "Tests done." >> ${1}

echo "Performing tests for rowwise version of multiplication and 2 processes:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    mpirun -n 2 ./main tests/A${i} tests/b${i} tests/c${i}_ r >> ${1}
    ./tests/matrix_compare tests/c${i}_ tests/c${i} >> ${1}
    errors=$(($errors + $?))
    rm -f ./tests/c${i}_
done
echo "Tests done." >> ${1}

echo "Performing tests for rowwise version of multiplication and 4 processes:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    mpirun -n 4 ./main tests/A${i} tests/b${i} tests/c${i}_ r >> ${1}
    ./tests/matrix_compare tests/c${i}_ tests/c${i} >> ${1}
    errors=$(($errors + $?))
    rm -f ./tests/c${i}_
done
echo "Tests done." >> ${1}

gcc -o ./tests/matrix_compare ./tests/matrix_compare.c -std=c11
echo "Performing tests for columnwise version of multiplication and 1 process:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    mpirun -n 1 ./main tests/A${i} tests/b${i} tests/c${i}_ c >> ${1}
    ./tests/matrix_compare tests/c${i}_ tests/c${i} >> ${1}
    errors=$(($errors + $?))
    rm -f ./tests/c${i}_
done
echo "Tests done." >> ${1}

echo "Performing tests for columnwise version of multiplication and 2 processes:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    mpirun -n 2 ./main tests/A${i} tests/b${i} tests/c${i}_ c >> ${1}
    ./tests/matrix_compare tests/c${i}_ tests/c${i} >> ${1}
    errors=$(($errors + $?))
    rm -f ./tests/c${i}_
done
echo "Tests done." >> ${1}

echo "Performing tests for columnwise version of multiplication and 4 processes:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    mpirun -n 4 ./main tests/A${i} tests/b${i} tests/c${i}_ c >> ${1}
    ./tests/matrix_compare tests/c${i}_ tests/c${i} >> ${1}
    errors=$(($errors + $?))
    rm -f ./tests/c${i}_
done
echo "Tests done." >> ${1}

exit ${errors}
