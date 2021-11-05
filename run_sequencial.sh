#!/bin/bash
tentativas=$1
soma_tempos=0
for tentativa in $(seq $tentativas)
do
    ./bin/sequencial matrix1.data matrix2.data
    files=$(ls resultado_sequencial_*.data)
    tempo=0
    for filename in $files
    do
        tempo=$(tail -1 $filename)
        mv $filename $tentativa"__"$filename
    done
    soma_tempos=$((soma_tempos + tempo))
done
echo $((soma_tempos / tentativas))