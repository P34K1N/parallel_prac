#!/bin/bash
gcc -o matrix_gen_float matrix_gen_float.c
for i in 50 100 150 200 250 300 350 400 450 500
do
    ./big_matrix_gen $i $RANDOM
done

