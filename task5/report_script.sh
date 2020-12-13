#!/bin/bash

cd res

gcc -o command_file_gen command_file_gen.c -std=c99
gcc -o map_file_generate map_file_generate.c -std=c99

for i in {10..12}
do
    for j in {3..5}
    do
        ((n=2**${i}))
        ((p=${j}**3))
        ./command_file_gen command.jcf ${p} ${n} "res_${p}_${n}.txt"
        llsubmit command.jcf
    done
    ((p=5**3))
    ./map_file_generate ${p}
    ./command_file_gen command.jcf ${p} ${n} "res_${p}_${n}_m.txt" "r"
    llsubmit command.jcf
done

rm -f c
