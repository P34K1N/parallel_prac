#!/bin/bash
gcc -o parse parse.c -std=c99

mkdir res
cd res

for i in {1..8}
do
    for j in {0..4}
    do
        ((n=10**${i}))
        ((m=2**${j}))
        for k in {1..5}
        do 
            bsub -n ${m} -oo res_n.txt mpirun ../main_mpi 1 ${n} res.txt sum_${i}_${j}_${k}.txt max_${i}_${j}_${k}.txt
        done
        sleep 10s
    done
done

rm res.txt


