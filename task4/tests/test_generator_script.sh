#!/bin/bash
gcc -o matrix_gen matrix_gen.c
for i in {0..19}
do
    ./matrix_gen $i $RANDOM
done

