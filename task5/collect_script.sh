#!/bin/bash

rm -f time.dat

for i in {10..12}
do
    for j in {3..5}
    do
        ((n=2**${i}))
        ((p=${j}**3))
        printf "${p} ${n} " >> time.dat
        cat res/res_${p}_${n}.txt >> time.dat
    done
    ((p=5**3))
    printf "${p}_m ${n} " >> time.dat
    cat res/res_${p}_${n}_m.txt >> time.dat
done



rm -f res.txt


