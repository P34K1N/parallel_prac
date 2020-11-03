#!/bin/bash

errors=0
rm test_results.log
gcc -o tests/compare tests/compare.c -lm
for i in 10 100 1000 10000
do
    ((j=${i}/2))
    mpirun -np 4 ./main_mpi 1 ${i} tests/res.txt >> ${1}
    ./tests/compare 1 ${i} tests/res.txt tests/primes.txt >> ${1}
    errors=$(($errors + $?))
    mpirun -np 4 ./main_mpi ${j} ${i} tests/res.txt >> ${1}
    ./tests/compare ${j} ${i} tests/res.txt tests/primes.txt >> ${1}
    errors=$(($errors + $?))
    ./main_pthread 1 ${i} tests/res.txt 4 >> ${1}
    ./tests/compare 1 ${i} tests/res.txt tests/primes.txt >> ${1}
    errors=$(($errors + $?))
    ./main_pthread ${j} ${i} tests/res.txt 4 >> ${1}
    ./tests/compare ${j} ${i} tests/res.txt tests/primes.txt >> ${1}
    errors=$(($errors + $?))
done

exit ${errors}
