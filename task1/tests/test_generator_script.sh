#!/bin/bash
gcc -o matrix_gen_double matrix_gen_double.c
for i in {0..9}
do
    ./matrix_gen_double $i $RANDOM
done

gcc -o matrix_gen_float matrix_gen_float.c
for i in {10..19}
do
    ./matrix_gen_float $i $RANDOM
done

