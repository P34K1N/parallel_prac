#!/bin/bash

n=(512 1024 2048 4096 4096 1024)
m=(512 1024 2048 4096 1024 4096)

rm -f time.dat

for i in {0..5}
do
    for j in {5..9}
    do
        ((p=2**${j}))
        printf "${p} ${n[i]} ${m[i]} r " >> time.dat
        cat res/res_${p}_${n[i]}_${m[i]}_r.txt >> time.dat
        printf "${p} ${n[i]} ${m[i]} c " >> time.dat
        cat res/res_${p}_${n[i]}_${m[i]}_c.txt >> time.dat 
    done
    ((p=512))
    printf "${p}_m ${n[i]} ${m[i]} r " >> time.dat
    cat res/res_${p}_${n[i]}_${m[i]}_m_r.txt >> time.dat
    printf "${p}_m ${n[i]} ${m[i]} c " >> time.dat
    cat res/res_${p}_${n[i]}_${m[i]}_m_c.txt >> time.dat
done



rm -f res.txt


