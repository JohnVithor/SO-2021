#!/bin/bash
tentativas=$1
p=$2
soma_tempos=0
for tentativa in $(seq $tentativas)
do
    ./bin/processos matrix1.data matrix2.data $p
    files=$(ls resultado_processos_*)
    tempo=0
    for filename in $files
    do
        new_tempo=$(tail -1 $filename)
        tempo=$(( tempo > new_tempo ? tempo : new_tempo ))
        mv $filename $tentativa"__"$filename
    done
    soma_tempos=$((soma_tempos + tempo))
done
echo $((soma_tempos / tentativas))

