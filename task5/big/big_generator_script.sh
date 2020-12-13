#!/bin/bash
gcc -o big_matrix_gen big_matrix_gen.c -std=c99

n=(1024 2048 4096)

for i in {0..2}
do
    ./big_matrix_gen ${n[i]} ${n[i]} ${n[i]} $RANDOM
done

