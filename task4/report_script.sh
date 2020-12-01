#!/bin/bash

cd res

n=(512 1024 2048 4096 4096 1024)
m=(512 1024 2048 4096 1024 4096)

gcc -o command_file_gen command_file_gen.c -std=c99
gcc -o map_file_generate map_file_generate.c -std=c99

for i in {0..5}
do
    for j in {5..9}
    do
        ((p=2**${j}))
        #./command_file_gen command.jcf ${p} ${n[i]} ${m[i]} "r" "res_${p}_${n[i]}_${m[i]}_r.txt"
        #llsubmit command.jcf
        ./command_file_gen command.jcf ${p} ${n[i]} ${m[i]} "c" "res_${p}_${n[i]}_${m[i]}_c.txt"
        llsubmit command.jcf
    done
    ((p=512))
    ./map_file_generate ${p}
    #./command_file_gen command.jcf ${p} ${n[i]} ${m[i]} "r" "res_${p}_${n[i]}_${m[i]}_m_r.txt" "r"
    #llsubmit command.jcf
    ./command_file_gen command.jcf ${p} ${n[i]} ${m[i]} "c" "res_${p}_${n[i]}_${m[i]}_m_c.txt" "r"
    llsubmit command.jcf
done



rm -f res.txt


