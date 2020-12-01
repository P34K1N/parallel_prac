#!/bin/bash
gcc -o big_matrix_gen big_matrix_gen.c -std=c99

n=(512 1024 2048 4096 4096 1024)
m=(512 1024 2048 4096 1024 4096)

for i in {0..5}
do
    ./big_matrix_gen ${n[i]} ${m[i]} $RANDOM
done

