#!/bin/bash
gcc -o parse parce.c -std=c99

rm *.dat

for j in 50 100 150 200 250 300 350 400 450 500
do
    for i in {0..20}
    do
        ./multi big/A${j} big/B${j} big/C 0 d >> tmp.txt
        ./parse 5 tmp.txt wtime.txt l1miss.txt l2miss.txt totcyc.txt flop.txt
        rm tmp.txt
        rm big/C
    done

    ./avg.sh ${j} wtime_ijk_32.dat wtime.txt
    ./avg.sh ${j} l1miss_ijk_32.dat l1miss.txt
    ./avg.sh ${j} l2miss_ijk_32.dat l2miss.txt
    ./avg.sh ${j} totcyc_ijk_32.dat totcyc.txt
    ./avg.sh ${j} flop_ijk_32.dat flop.txt
done

for j in 50 100 150 200 250 300 350 400 450 500
do
    for i in {0..20}
    do
        ./multi big/A${j} big/B${j} big/C 1 d >> tmp.txt
        ./parse 5 tmp.txt wtime.txt l1miss.txt l2miss.txt totcyc.txt flop.txt
        rm tmp.txt
        rm big/C
    done

    ./avg.sh ${j} wtime_ikj_32.dat wtime.txt
    ./avg.sh ${j} l1miss_ikj_32.dat l1miss.txt
    ./avg.sh ${j} l2miss_ikj_32.dat l2miss.txt
    ./avg.sh ${j} totcyc_ikj_32.dat totcyc.txt
    ./avg.sh ${j} flop_ikj_32.dat flop.txt
done

for j in 50 100 150 200 250 300 350 400 450 500
do
    for i in {0..20}
    do
        ./multi big/A${j} big/B${j} big/C 1 o >> tmp.txt
        ./parse 5 tmp.txt wtime.txt l1miss.txt l2miss.txt totcyc.txt flop.txt
        rm tmp.txt
        rm big/C
    done

    ./avg.sh ${j} wtime_ikj_opt.dat wtime.txt
    ./avg.sh ${j} l1miss_ikj_opt.dat l1miss.txt
    ./avg.sh ${j} l2miss_ikj_opt.dat l2miss.txt
    ./avg.sh ${j} totcyc_ikj_opt.dat totcyc.txt
    ./avg.sh ${j} flop_ikj_opt.dat flop.txt
done

rm big/C


