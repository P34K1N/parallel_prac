#!/bin/bash
rm -f *.dat

cd res

for i in {6..9}
do
    rm -f sum_${i}_p.txt
    rm -f max_${i}_p.txt

    for j in {0..4}
    do
        ((n=10**${i}))
        ((m=2**${j}))
        rm -f sum_${i}_${j}_p.txt
        rm -f max_${i}_${j}_p.txt
        for k in {1..5}
        do 
            cat sum_${i}_${j}_${k}_p.txt >> sum_${i}_${j}_p.txt
            cat max_${i}_${j}_${k}_p.txt >> max_${i}_${j}_p.txt
        done
        
        awk '{ total += $1; count++ } END  {print total / count}' sum_${i}_${j}_p.txt >> sum_${i}_p.txt
        awk '{ total += $1; count++ } END  {print total / count}' max_${i}_${j}_p.txt >> max_${i}_p.txt
    done

    awk '{
            elements[NR]=$1
         }
         END {
            for(i=1; i <= NR; i++)
                printf "%s %u %.10f\n", var, i - 1, elements[i]
         }' sum_${i}_p.txt var=${i} >> ../sumtime_grid_p.dat

    awk '{
            elements[NR]=$1
         }
         END {
            for(i=1; i <= NR; i++)
                printf "%s %u %.10f\n", var, i - 1, elements[i]
         }' max_${i}_p.txt var=${i} >> ../maxtime_grid_p.dat

        
    awk '{
            elements[NR]=$1
            if ($1 > largest) {
                largest = $1
            }
         }
         END {
            for(i=1; i <= NR; i++)
                printf "%s %u %.10f\n", var, i - 1, elements[i]/largest
         }' sum_${i}_p.txt var=${i} >> ../sumtime_grid_normed_p.dat

    awk '{
            elements[NR]=$1
            if ($1 > largest) {
                largest = $1
            }
         }
         END {
            for(i=1; i <= NR; i++)
                printf "%s %u %.10f\n", var, i - 1, elements[i]/largest
         }' max_${i}_p.txt var=${i} >> ../maxtime_grid_normed_p.dat
done

