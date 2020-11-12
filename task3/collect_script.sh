#!/bin/bash
rm -f *.dat

cd res

for i in {1..8}
do
    rm -f sum_${i}.txt
    rm -f max_${i}.txt

    for j in {0..4}
    do
        ((n=10**${i}))
        ((m=2**${j}))
        rm -f sum_${i}_${j}.txt
        rm -f max_${i}_${j}.txt
        for k in {1..5}
        do 
            cat sum_${i}_${j}_${k}.txt >> sum_${i}_${j}.txt
            cat max_${i}_${j}_${k}.txt >> max_${i}_${j}.txt
        done
        
        awk '{ total += $1; count++ } END  {print total / count}' sum_${i}_${j}.txt >> sum_${i}.txt
        awk '{ total += $1; count++ } END  {print total / count}' max_${i}_${j}.txt >> max_${i}.txt
    done
        
    awk '{
            elements[NR]=$1
            if ($1 > largest) {
                largest = $1
            }
         }
         END {
            for(i=1; i <= NR; i++)
                printf "%s %u %.10f\n", var, i - 1, elements[i]/largest
         }' sum_${i}.txt var=${i} >> ../sumtime_grid.dat

    awk '{
            elements[NR]=$1
            if ($1 > largest) {
                largest = $1
            }
         }
         END {
            for(i=1; i <= NR; i++)
                printf "%s %u %.10f\n", var, i - 1, elements[i]/largest
         }' max_${i}.txt var=${i} >> ../maxtime_grid.dat
done

