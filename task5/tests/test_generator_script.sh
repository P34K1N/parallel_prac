#!/bin/bash
gcc -o matrix_gen_double matrix_gen_double.c
for i in {0..4}
do
    ./matrix_gen_double $i $RANDOM
done

