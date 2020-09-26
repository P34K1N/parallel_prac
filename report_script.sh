#!/bin/bash

for j in {0..5}
do
    for i in {0..99}
    do
        ./multi A B C_${j} ${j} >> time_${j}.txt
    done
    
    printf "${j} " >> 2col.dat
    awk '{ total += $1; count++ } END  {print total / count}' time_${j}.txt >> 2col.dat
    rm time_${j}.txt
    rm C_${j}
done

gnuplot -persist <<-EOFMarker
    set terminal svg size 600,500
    set output 'plot.svg'
    set title 'Title'
    plot '2col.dat' with linespoints
EOFMarker

rm 2col.dat

