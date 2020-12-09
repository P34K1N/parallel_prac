#!/bin/bash
gcc -o matrix_gen_float matrix_gen_float.c
for i in {0..4}
do
    ./matrix_gen_float $i $RANDOM
done

