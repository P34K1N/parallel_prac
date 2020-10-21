#!/bin/bash

errors=0;

gcc -o ./tests/matrix_compare ./tests/matrix_compare.c -std=c11
echo "Performing tests for ijk version of multiplication and block size 32:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    ./multi tests/A${i} tests/B${i} tests/C${i}_ 0 d >> ${1}
    ./tests/matrix_compare tests/C${i}_ tests/C${i} >> ${1}
    errors=$(($errors + $?))
    rm ./tests/C${i}_
done
echo "Tests done." >> ${1}

echo "Performing tests for ikj version of multiplication and block size 32:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    ./multi tests/A${i} tests/B${i} tests/C${i}_ 1 d >> ${1}
    ./tests/matrix_compare tests/C${i}_ tests/C${i} >> ${1}
    errors=$(($errors + $?))
    rm ./tests/C${i}_
done
echo "Tests done." >> ${1}

echo "Performing tests for ikj version of multiplication and optimal block size:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    ./multi tests/A${i} tests/B${i} tests/C${i}_ 1 o >> ${1}
    ./tests/matrix_compare tests/C${i}_ tests/C${i} >> ${1}
    errors=$(($errors + $?))
    rm ./tests/C${i}_
done
echo "Tests done." >> ${1}

echo "Performing tests for ijk version of multiplication and random custom block size:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    ((n=$RANDOM%32+1))
    ((m=$RANDOM%32+1))
    ((k=$RANDOM%32+1))
    ./multi tests/A${i} tests/B${i} tests/C${i}_ 0 i ${n} ${m} ${k} >> ${1}
    ./tests/matrix_compare tests/C${i}_ tests/C${i} >> ${1}
    errors=$(($errors + $?))
    rm ./tests/C${i}_
done
echo "Tests done." >> ${1}

echo "Performing tests for ikj version of multiplication and random custom block size:" >> ${1}
for i in {0..19}
do
    echo "Test number $i:" >> ${1}
    ((n=$RANDOM%32+1))
    ((m=$RANDOM%32+1))
    ((k=$RANDOM%32+1))
    ./multi tests/A${i} tests/B${i} tests/C${i}_ 1 i ${n} ${m} ${k} >> ${1}
    ./tests/matrix_compare tests/C${i}_ tests/C${i} >> ${1}
    errors=$(($errors + $?))
    rm ./tests/C${i}_
done
echo "Tests done." >> ${1}

exit ${errors}
